#include "Pack/RPKernel/RPSysLayout.h"

#include "nw4r/lyt/lyt_pane.h"
#include "nw4r/math/math_types.h"
#include <Pack/RPKernel.h>

#include <nw4r/lyt.h>
#include <nw4r/ut.h>

#include <revolution/GX.h>

#include <cstdio>
#include <cstring>

namespace {

//! Length of the "ID" suffix in panes (N_Pane_XX)
const int ID_LEN = 2;

//! Length of dynamic animation expressions
const int DYN_LEN = 3;

/**
 * @brief Finds the position of the ID suffix in the specified name string
 *
 * @param pName Name string
 * @return Index of the ID suffix
 */
int FindID(const char* pName) {
    int len = NW4R_LYT_RES_NAME_LEN;

    for (int i = 0; i < NW4R_LYT_RES_NAME_LEN; i++) {
        if (pName[i] == '\0') {
            len = i;
            break;
        }
    }

    len -= ID_LEN;

    // OOB when name is shorter than two characters.
    // But that would mean there's no ID anyways??
    if (len < 0) {
        len = 0;
    }

    return len;
}

/**
 * @brief Reads the two character ID from the specified string
 *
 * @param pIdStr ID encoded as a string
 */
u16 ReadID(const char* pIdStr) {
    return *reinterpret_cast<const u16*>(pIdStr);
}

} // namespace

/**
 * @brief Player slot TEV colors
 */
const GXColor RPSysLayout::PLAYER_COLORS[WPAD_MAX_CONTROLLERS] = {
    {0, 140, 255, 255},
    {255, 56, 56, 255},
    {16, 189, 13, 255},
    {255, 156, 0, 255},
};

/**
 * @brief CPU TEV color
 */
const GXColor RPSysLayout::CPU_COLOR = {175, 170, 152, 255};

/**
 * @brief Constructor
 */
RPSysLayout::RPSysLayout()
    : mFlags(0),
      mScaleX(1.0f),
      unk8(1.0f),
      unkC(1.0f),
      mAdjScaleX(1.0f),
      unk14(1.0f),
      unk18(1.0f),
      mpLayout(NULL) {

    NW4R_UT_LIST_INIT(mAnmObjList, RPSysLytAnmObj);
    NW4R_UT_LIST_INIT(mDynamicAnmList, RPSysLytDynamicAnm);
}

/**
 * @brief Initializes the layout system
 * @details Initializes the NW4R layout library
 */
void RPSysLayout::initialize() {
    nw4r::lyt::LytInit();
}

/**
 * @brief Parses the length portion of a dynamic animation string
 *
 * @param pLenStr Length encoded in text form
 */
s16 RPSysLayout::parseDynamicAnmLength(const char* pLenStr) {
    s16 length = 0;

    for (s16 i = 0; i < DYN_LEN - 1; i++, pLenStr++) {
        s16 base = 1;
        for (s16 j = 0; j < (DYN_LEN - 1) - 1 - i; j++) {
            base *= 10;
        }

        if (*pLenStr >= '0' && *pLenStr <= '9') {
            length += (*pLenStr - '0') * base;
        }
    }

    return length;
}

/**
 * @brief Attempts to parse a dynamic animation string from a pane
 * @details The string must be stored in the pane's userdata field
 *
 * @param pPane Pane to check
 * @param[out] pDirection Dynamic animation direction
 * @param[out] pLength Dynamic animation length
 *
 * @return Whether a dynamic animation was found
 */
bool RPSysLayout::checkDynamicAnmPane(
    nw4r::lyt::Pane* pPane, RPSysLytDynamicAnm::EDirection* pDirection,
    s16* pLength) {

    bool isDynAnm = false;
    const char* pUserData = pPane->GetUserData();
    const char* pUserDataEnd = pUserData + NW4R_LYT_PANE_USERDATA_LEN;

    while (pUserData != pUserDataEnd) {
        switch (*pUserData) {
        case 'u': {
            *pDirection = RPSysLytDynamicAnm::EDirection_Up;
            *pLength = parseDynamicAnmLength(pUserData + 1);
            pUserData += DYN_LEN;
            isDynAnm = true;
            break;
        }

        case 'd': {
            *pDirection = RPSysLytDynamicAnm::EDirection_Down;
            *pLength = parseDynamicAnmLength(pUserData + 1);
            pUserData += DYN_LEN;
            isDynAnm = true;
            break;
        }

        case 'l': {
            *pDirection = RPSysLytDynamicAnm::EDirection_Left;
            *pLength = parseDynamicAnmLength(pUserData + 1);
            pUserData += DYN_LEN;
            isDynAnm = true;
            break;
        }

        case 'r': {
            *pDirection = RPSysLytDynamicAnm::EDirection_Right;
            *pLength = parseDynamicAnmLength(pUserData + 1);
            pUserData += DYN_LEN;
            isDynAnm = true;
            break;
        }

        // This seems to a workaround for many layouts having "43" as the
        // userdata field. (Maybe artists noting a 4:3 aspect ratio?)
        case '4': {
            pUserData += 2;
            break;
        }

        case '\0': {
            // Force the loop to break next iteration
            pUserData = pUserDataEnd;
            break;
        }

        default: {
            break;
        }
        }
    }

    return isDynAnm;
}

/**
 * @brief Create dynamic animation objects for the specified pane
 * @note If the pane contains no dynamic animations, nothing will happen.
 *
 * @param pHeap Heap to use for allocations
 * @param pPane Pane expected to contain a dynamic animation
 */
void RPSysLayout::createDynamicAnm(EGG::Heap* pHeap, nw4r::lyt::Pane* pPane) {
    // TODO(kiwi) Force specific inline depth during recursion
    (void)0;
    (void)0;
    (void)0;

    RPSysLytDynamicAnm::EDirection dir = RPSysLytDynamicAnm::EDirection_None;
    s16 length = 0;

    if (checkDynamicAnmPane(pPane, &dir, &length)) {
        RPSysLytDynamicAnm* pDynamicAnm =
            new (pHeap) RPSysLytDynamicAnm(pPane, dir, length);

        appendDynamicAnm(pDynamicAnm);
    }

    NW4R_UT_LINKLIST_FOREACH (it, pPane->GetChildList(), {
        createDynamicAnm(pHeap, &*it); //
    })
}

/**
 * @brief Allocates a large textbox buffer for the pane and its children
 *
 * @param pPane Root pane
 */
void RPSysLayout::allocStringBuffer(nw4r::lyt::Pane* pPane) {
    nw4r::lyt::TextBox* pTextBox =
        nw4r::ut::DynamicCast<nw4r::lyt::TextBox*>(pPane);

    if (pTextBox != NULL) {
        const wchar_t* pString = pTextBox->GetString();
        pTextBox->AllocStringBuffer(MAX_STRING_LENGTH - 1);

        if (pString != NULL) {
            pTextBox->SetString(pString);
        }
    }

    NW4R_UT_LINKLIST_FOREACH (it, pPane->GetChildList(), {
        allocStringBuffer(&*it); //
    })
}

/**
 * @brief Creates a layout from the specified binary file
 *
 * @param pHeap Heap to use for allocations
 * @param pAccessor Layout resource accessor
 * @param pName Binary layout file name
 */
RPSysLayout* RPSysLayout::create(EGG::Heap* pHeap,
                                 RPSysLytResAccessor* pAccessor,
                                 const char* pName) {
    if (pHeap == NULL) {
        pHeap = EGG::Heap::getCurrentHeap();
    }

    RPSysLayout* p = new (pHeap) RPSysLayout();

    if (p != NULL) {
        p->mpDrawInfo = new (pHeap) nw4r::lyt::DrawInfo();
        p->mpLayout = new (pHeap) nw4r::lyt::Layout();

        // Take ownership of any layout allocations
        RPSysLytAllocator allocator(pHeap);
        nw4r::lyt::Layout::SetAllocator(&allocator);
        {
            void* pBinary = pAccessor->getResource(
                nw4r::lyt::ArcResourceAccessor::RES_TYPE_NAME, pName);

            p->mpLayout->Build(pBinary, pAccessor->mpImpl);

            allocStringBuffer(p->getRootPane());
        }
        nw4r::lyt::Layout::SetAllocator(NULL);

        p->createDynamicAnm(pHeap, p->getRootPane());
        p->mpLayout->SetTagProcessor(RP_GET_INSTANCE(RPSysTagProcessor));

        p->mpDrawInfo->SetViewRect(p->mpLayout->GetLayoutRect());
        nw4r::math::MTX34 ident;
        nw4r::math::MTX34Identity(&ident);
        p->mpDrawInfo->SetViewMtx(ident);
        p->mpDrawInfo->SetLocationAdjust(true);
    }

    return p;
}

/**
 * @brief Creates a animation object from the specified binary file
 *
 * @param pHeap Heap to use for allocations
 * @param pAccessor Layout resource accessor
 * @param pName Binary animation file name
 */
RPSysLytAnmObj* RPSysLayout::createAnmObj(EGG::Heap* pHeap,
                                          RPSysLytResAccessor* pAccessor,
                                          const char* pName) {
    if (pHeap == NULL) {
        pHeap = EGG::Heap::getCurrentHeap();
    }

    RPSysLytAnmObj* p = new (pHeap) RPSysLytAnmObj();

    if (p != NULL) {
        // Take ownership of any layout allocations
        RPSysLytAllocator allocator(pHeap);
        nw4r::lyt::Layout::SetAllocator(&allocator);
        {
            void* pBinary = pAccessor->getResource(
                nw4r::lyt::ArcResourceAccessor::RES_TYPE_NAME, pName);

            p->mpAnimTrans =
                mpLayout->CreateAnimTransform(pBinary, pAccessor->mpImpl);

            p->mFrameCtrl.init(p->mpAnimTrans->GetFrameMax() - 1.0f);

            p->mNumAnimContent = p->mpAnimTrans->GetAnimResource()->animContNum;
            p->mpAnimContent =
                new (pHeap) nw4r::lyt::AnimationLink[p->mNumAnimContent];
        }
        nw4r::lyt::Layout::SetAllocator(NULL);

        if (p->mpAnimTrans->IsLoopData()) {
            p->setPlayMode(RPSysFrameCtrl::EPlayMode_Loop);
        } else {
            p->setPlayMode(RPSysFrameCtrl::EPlayMode_OneTime);
        }

        appendAnmObj(p);
    }

    return p;
}

/**
 * @brief Binds a new animation object to this layout
 *
 * @param pAnmObj Animation object
 */
void RPSysLayout::bindAnmObj(RPSysLytAnmObj* pAnmObj) {
    mpLayout->BindAnimation(pAnmObj->mpAnimTrans);
}

/**
 * @brief Unbinds an animation object from this layout
 *
 * @param pAnmObj Animation object
 */
void RPSysLayout::unbindAnmObj(RPSysLytAnmObj* pAnmObj) {
    mpLayout->UnbindAnimation(pAnmObj->mpAnimTrans);
}

/**
 * @brief Unbinds all animation objects from this layout
 */
void RPSysLayout::unbindAllAnmObj() {
    mpLayout->UnbindAllAnimation();
}

/**
 * @brief Binds a new animation object to the specified pane
 * @details This function searches the pane tree of this layout
 *
 * @param pAnmObj Animation object
 * @param pName Pane name
 * @param recursive Whether to recursively resolve the animation target
 */
void RPSysLayout::bindAnmObjToPane(RPSysLytAnmObj* pAnmObj, const char* pName,
                                   bool recursive) {
    nw4r::lyt::Pane* pPane = findPane(pName);

    if (pPane != NULL) {
        pPane->BindAnimation(pAnmObj->mpAnimTrans, recursive);
    }
}

/**
 * @brief Binds a new animation object to the specified pane
 *
 * @param pAnmObj Animation object
 * @param pPane Target pane
 * @param recursive Whether to recursively resolve the animation target
 */
void RPSysLayout::bindAnmObjToPane(RPSysLytAnmObj* pAnmObj,
                                   nw4r::lyt::Pane* pPane, bool recursive) {
    pPane->BindAnimation(pAnmObj->mpAnimTrans, recursive);
}

/**
 * @brief Forcibly binds a new animation object to the specified pane
 * @details This function allows binding an animation object that shares a name
 * prefix with the pane.
 *
 * As long as the names match up to the ID (last two characters), this function
 * will correctly find the pane.
 *
 * This function is used to bind animations targeting panes such as
 * `P_MyPane_00` to any pane of the format `P_MyPane_XX`. NW4R requires an exact
 * name match to bind, so this function reimplements `AnimTransformBasic::Bind`.
 *
 * @param pAnmObj Animation object
 * @param pPane Target pane
 * @param recursive Whether to recursively resolve the animation target
 */
void RPSysLayout::forceBindAnmObjToPane(RPSysLytAnmObj* pAnmObj,
                                        nw4r::lyt::Pane* pPane,
                                        bool recursive) {
    const nw4r::lyt::res::AnimationBlock* pRes =
        pAnmObj->mpAnimTrans->GetAnimResource();

    const u32* pContentOffsetTbl = reinterpret_cast<const u32*>(
        reinterpret_cast<const u8*>(pRes) + pRes->animContOffsetsOffset);

    int srcIdx = FindID(pPane->GetName());

    for (u16 idx = 0; idx < pRes->animContNum; idx++) {
        const nw4r::lyt::res::AnimationContent* pContent =
            reinterpret_cast<const nw4r::lyt::res::AnimationContent*>(
                reinterpret_cast<const u8*>(pRes) + pContentOffsetTbl[idx]);

        nw4r::lyt::AnimationLink* pAnmLink = &pAnmObj->mpAnimContent[idx];

        // Copy the name of the animation target...
        char nameWork[NW4R_LYT_RES_NAME_LEN + 1];
        nameWork[NW4R_LYT_RES_NAME_LEN] = '\0';
        std::strncpy(nameWork, pContent->name, NW4R_LYT_RES_NAME_LEN);

        // And transplant the ID from the pane name!
        int dstIdx = FindID(nameWork);
        nameWork[dstIdx + 0] = pPane->GetName()[srcIdx + 0];
        nameWork[dstIdx + 1] = pPane->GetName()[srcIdx + 1];

        // Now the bind will find the specified pane (if it really exists)
        if (pContent->type == nw4r::lyt::res::AnimationContent::ANIMTYPE_PANE) {
            nw4r::lyt::Pane* pResult =
                pPane->FindPaneByName(nameWork, recursive);

            if (pResult != NULL) {
                pAnmLink->SetAnimTransform(pAnmObj->mpAnimTrans, idx);
                pResult->AddAnimationLink(pAnmLink);
            }
        } else /* nw4r::lyt::res::AnimationContent::ANIMTYPE_MATERIAL */ {
            nw4r::lyt::Material* pResult =
                pPane->FindMaterialByName(nameWork, recursive);

            if (pResult != NULL) {
                pAnmLink->SetAnimTransform(pAnmObj->mpAnimTrans, idx);
                pResult->AddAnimationLink(pAnmLink);
            }
        }
    }
}

/**
 * @brief Unbinds an animation object from the specified pane
 *
 * @param pAnmObj Animation object
 * @param pPane Target pane
 * @param recursive Whether to also unbind the animation from all children
 */
void RPSysLayout::unbindAnmObjToPane(RPSysLytAnmObj* pAnmObj,
                                     nw4r::lyt::Pane* pPane, bool recursive) {
    pPane->UnbindAnimation(pAnmObj->mpAnimTrans, recursive);
}

/**
 * @brief Attempts to dynamic-cast the specified pane to a textbox pane
 *
 * @param pPane Target pane
 * @return Textbox if the cast is valid, otherwise NULL
 */
RPSysLytTextBox* RPSysLayout::castToTextBox(nw4r::lyt::Pane* pPane) {
    RPSysLytTextBox* pTextBox = NULL;

    if (pPane != NULL) {
        pTextBox = nw4r::ut::DynamicCast<RPSysLytTextBox*>(pPane);
    }

    return pTextBox;
}

/**
 * @brief Attempts to dynamic-cast the specified pane to a picture pane
 *
 * @param pPane Target pane
 * @return Picture if the cast is valid, otherwise NULL
 */
RPSysLytPicture* RPSysLayout::castToPicture(nw4r::lyt::Pane* pPane) {
    RPSysLytPicture* pPicture = NULL;

    if (pPane != NULL) {
        pPicture = nw4r::ut::DynamicCast<RPSysLytPicture*>(pPane);
    }

    return pPicture;
}

/**
 * @brief Attempts to dynamic-cast the specified pane to a window pane
 *
 * @param pPane Target pane
 * @return Window if the cast is valid, otherwise NULL
 */
RPSysLytWindow* RPSysLayout::castToWindow(nw4r::lyt::Pane* pPane) {
    RPSysLytWindow* pWindow = NULL;

    if (pPane != NULL) {
        pWindow = nw4r::ut::DynamicCast<RPSysLytWindow*>(pPane);
    }

    return pWindow;
}

/**
 * @brief Attempts to dynamic-cast the specified pane to a bounding pane
 *
 * @param pPane Target pane
 * @return Picture if the cast is valid, otherwise NULL
 */
RPSysLytBounding* RPSysLayout::castToBounding(nw4r::lyt::Pane* pPane) {
    RPSysLytBounding* pBounding = NULL;

    if (pPane != NULL) {
        pBounding = nw4r::ut::DynamicCast<RPSysLytBounding*>(pPane);
    }

    return pBounding;
}

/**
 * @brief Searches recursively for a pane in this layout matching the
 * specified name
 *
 * @param pName Pane name
 */
nw4r::lyt::Pane* RPSysLayout::findPane(const char* pName) {
    return getRootPane()->FindPaneByName(pName, true);
}

/**
 * @brief Searches recursively for a textbox pane in this layout matching
 * the specified name
 *
 * @param pName Textbox name
 */
RPSysLytTextBox* RPSysLayout::findTextBox(const char* pName) {
    RPSysLytTextBox* pTextBox = NULL;

    nw4r::lyt::Pane* pPane = findPane(pName);
    if (pPane != NULL) {
        pTextBox = castToTextBox(pPane);
    }

    return pTextBox;
}

/**
 * @brief Searches recursively for a picture pane in this layout matching
 * the specified name
 *
 * @param pName Picture name
 */
RPSysLytPicture* RPSysLayout::findPicture(const char* pName) {
    RPSysLytPicture* pPicture = NULL;

    nw4r::lyt::Pane* pPane = findPane(pName);
    if (pPane != NULL) {
        pPicture = castToPicture(pPane);
    }

    return pPicture;
}

/**
 * @brief Searches recursively for a window pane in this layout matching
 * the specified name
 *
 * @param pName Window name
 */
RPSysLytWindow* RPSysLayout::findWindow(const char* pName) {
    RPSysLytWindow* pWindow = NULL;

    nw4r::lyt::Pane* pPane = findPane(pName);
    if (pPane != NULL) {
        pWindow = castToWindow(pPane);
    }

    return pWindow;
}

/**
 * @brief Searches recursively for a bounding pane in this layout matching
 * the specified name
 *
 * @param pName Bounding name
 */
RPSysLytBounding* RPSysLayout::findBounding(const char* pName) {
    RPSysLytBounding* pBounding = NULL;

    nw4r::lyt::Pane* pPane = findPane(pName);
    if (pPane != NULL) {
        pBounding = castToBounding(pPane);
    }

    return pBounding;
}

/**
 * @brief Searches recursively for a group in this layout matching the
 * specified name
 *
 * @param pName Group name
 */
nw4r::lyt::Group* RPSysLayout::findGroup(const char* pName) {
    return mpLayout->GetGroupContainer()->FindGroupByName(pName);
}

/**
 * @brief Appends a new dynamic animation to this layout
 *
 * @param pDynamicAnm Dynamic animation
 */
void RPSysLayout::appendDynamicAnm(RPSysLytDynamicAnm* pDynamicAnm) {
    nw4r::ut::List_Append(&mDynamicAnmList, pDynamicAnm);
}

/**
 * @brief Appends a new animation object to this layout
 *
 * @param pAnmObj Animation object
 */
void RPSysLayout::appendAnmObj(RPSysLytAnmObj* pAnmObj) {
    nw4r::ut::List_Append(&mAnmObjList, pAnmObj);
}

/**
 * @brief Removes an animation object from this layout
 *
 * @param pAnmObj Animation object
 */
void RPSysLayout::removeAnmObj(RPSysLytAnmObj* pAnmObj) {
    nw4r::ut::List_Remove(&mAnmObjList, pAnmObj);
}

/**
 * @brief Resets the state of this layout and any animations it owns
 */
void RPSysLayout::reset() {
    mFlags = 0;

    NW4R_UT_LIST_FOREACH (RPSysLytAnmObj, it, mAnmObjList, {
        it->mFrameCtrl.reset(); //
    })

    NW4R_UT_LIST_FOREACH (RPSysLytDynamicAnm, it, mDynamicAnmList, {
        it->reset(); //
    })

    mpLayout->Animate();
    mpLayout->CalculateMtx(*mpDrawInfo);
}

/**
 * @brief Updates the state of this layout and any animations it owns
 */
void RPSysLayout::calc() {
    NW4R_UT_LIST_FOREACH (RPSysLytAnmObj, it, mAnmObjList, {
        it->calc(); //
    })

    mpLayout->Animate();

    NW4R_UT_LIST_FOREACH (RPSysLytDynamicAnm, it, mDynamicAnmList, {
        it->calc(); //
    })

    f32 current = RPGrpScreen::GetSizeXMax();
    f32 standard = RPGrpScreen::GetSizeYMax(RPGrpScreen::TV_MODE_STD);

    mScaleX = current / standard;
    mAdjScaleX = 1.0f / mScaleX;

    // Fix the stretch effect on panes with location adjust enabled
    nw4r::math::VEC2 adjScale(mAdjScaleX, 1.0f);
    mpDrawInfo->SetLocationAdjustScale(adjScale);

    // Scale the root pane to position all panes for the aspect ratio
    nw4r::math::VEC2 paneScale(mScaleX, 1.0f);
    getRootPane()->SetScale(paneScale);

    mpLayout->CalculateMtx(*mpDrawInfo);
    mFlags |= EFlag_Visible;
}

/**
 * @brief Configures the GX render state for layout drawing
 */
void RPSysLayout::drawInit() {
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_FALSE, GX_NEVER, GX_FALSE);
    GXSetClipMode(GX_CLIP_ENABLE);
}

/**
 * @brief Draws the contents of this layout
 */
void RPSysLayout::draw() {
    if (!(mFlags & EFlag_Visible)) {
        return;
    }

    mpLayout->Draw(*mpDrawInfo);
}

/**
 * @brief Attempts to change the font color of the specified textbox by
 * fetching an alternate version matching the ID
 * @details This function relies on the same `Name_XX` pattern as
 * `forceBindAnmObjToPane`.
 *
 * @param pTextBox Textbox whose font color should be changed
 * @param id ID suffix of the textbox to fetch
 * @return Success
 */
bool RPSysLayout::changeFontColor(RPSysLytTextBox* pTextBox, u32 id) {
    bool success = false;

    // Before the null check?
    const char* pGroupName = pTextBox->GetName();

    if (pTextBox != NULL) {
        nw4r::lyt::Group* pGroup = findGroup(pGroupName);

        if (pGroup != NULL) {
            NW4R_UT_LINKLIST_FOREACH (it, pGroup->GetPaneList(), {
                const RPSysLytTextBox* pChild = castToTextBox(it->mTarget);

                if (pChild != NULL) {
                    const char* pChildName = pChild->GetName();
                    bool copy = false;

                    char name[2 + 1];
                    std::snprintf(name, sizeof(name), "%02d", id);

                    if (ReadID(pChildName + FindID(pChildName)) == ReadID(name)) {
                        copy = true;
                    }

                    if (copy) {
                        pTextBox->copyFontColor(*pChild);
                        success = true;
                    }
                }

                if (success) {
                    break;
                }
            })
        }
    }

    return success;
}

/**
 * @brief Tests whether a point falls within the specified bounding pane
 * @note Hit test is always ignored when the layout is invisible
 *
 * @param pBounding Bounding pane
 * @param rPoint Point to test
 */
bool RPSysLayout::isInsideBounding(RPSysLytBounding* pBounding,
                                   const EGG::Vector2f& rPoint) {

    bool inside = false;

    if (mFlags & EFlag_Visible) {
        inside = pBounding->isInsideBounding(*mpDrawInfo, rPoint);
    }

    return inside;
}

/**
 * @brief Moves the specified pane to the front of its parent's children
 *
 * @param pChild Child pane
 */
void RPSysLayout::becomeYoungestChild(nw4r::lyt::Pane* pChild) {
    nw4r::lyt::Pane* pParent = pChild->GetParent();
    pParent->RemoveChild(pChild);
    pParent->AppendChild(pChild);
}

/**
 * @brief Draws a Mii icon to the specified pane
 * @details This function defaults to a white material color.
 *
 * @param screen Screen to draw to
 * @param pane Pane to draw on
 * @param icon Mii icon
 */
void RPSysLayout::drawKokeshiIcon(RPGrpScreen* pScreen, nw4r::lyt::Pane* pPane,
                                  RPSysKokeshiIcon* pIcon) {

    GXColor white = {255, 255, 255, 255};
    drawKokeshiIcon(pScreen, pPane, pIcon, white);
}

/**
 * @brief Draws a Mii icon to the specified pane
 * @details Uses default white material color
 *
 * @param screen Screen to draw to
 * @param pane Pane to draw on
 * @param icon Mii icon
 * @param matColor Material color
 */
void RPSysLayout::drawKokeshiIcon(RPGrpScreen* pScreen, nw4r::lyt::Pane* pPane,
                                  RPSysKokeshiIcon* pIcon, GXColor matColor) {

    const nw4r::math::MTX34& rGlobalMtx = pPane->GetGlobalMtx();
    nw4r::lyt::Size size = pPane->GetSize();

    nw4r::math::VEC3 tl(-(size.width * 0.5f), size.height * 0.5f, 0.0f);
    nw4r::math::VEC3 br(size.width * 0.5f, -(size.height * 0.5f), 0.0f);

    nw4r::math::VEC3 gtl;
    nw4r::math::VEC3Transform(&gtl, &rGlobalMtx, &tl);

    nw4r::math::VEC3 gbr;
    nw4r::math::VEC3Transform(&gbr, &rGlobalMtx, &br);

    pScreen->BeginDrawQuadTexture(false);
    pScreen->DrawQuadTexture(gtl.x, gtl.y, gbr.x, gbr.y, pIcon->GetResTIMG(),
                             matColor);
}

/**
 * @brief Starts playing all dynamic animations inwards
 *
 * @param frame Starting frame (-1 to play from the ending frame)
 */
void RPSysLayout::startDynAnmIn(s16 frame) {
    NW4R_UT_LIST_FOREACH (RPSysLytDynamicAnm, it, mDynamicAnmList, {
        it->startAnmIn(frame); //
    })
}

/**
 * @brief Starts playing all dynamic animations outwards
 *
 * @param frame Starting frame (-1 to play from the ending frame)
 */
void RPSysLayout::startDynAnmOut(s16 frame) {
    NW4R_UT_LIST_FOREACH (RPSysLytDynamicAnm, it, mDynamicAnmList, {
        it->startAnmOut(frame); //
    })
}

/**
 * @brief Flips the direction of all horizonal dynamic animations
 *
 * @param reverse Whether to reverse the horizontal direction
 */
void RPSysLayout::reverseAnmHDirection(bool reverse) {
    NW4R_UT_LIST_FOREACH (RPSysLytDynamicAnm, it, mDynamicAnmList, {
        it->reverseAnmHDirection(reverse); //
    })
}

/**
 * @brief Tests whether all dynamic animations have finished animating
 * inwards
 */
bool RPSysLayout::isFinishedDynAnmIn() {
    bool finished = true;

    NW4R_UT_LIST_FOREACH (RPSysLytDynamicAnm, it, mDynamicAnmList, {
        if (!it->isFinishedAnmIn()) {
            finished = false;
            break;
        }
    })

    return finished;
}

/**
 * @brief Tests whether all dynamic animations have finished animating
 * outwards
 */
bool RPSysLayout::isFinishedDynAnmOut() {
    bool finished = true;

    NW4R_UT_LIST_FOREACH (RPSysLytDynamicAnm, it, mDynamicAnmList, {
        if (!it->isFinishedAnmOut()) {
            finished = false;
            break;
        }
    })

    return finished;
}

/**
 * @brief Gets the TEV color used to represent the specified player slot
 *
 * @param idx Player index
 */
const GXColor& RPSysLayout::getPlayerColor(u32 idx) {
    return PLAYER_COLORS[idx];
}

/**
 * @brief Gets the TEV color used to represent CPU players
 */
const GXColor& RPSysLayout::getCpuColor() {
    return CPU_COLOR;
}
