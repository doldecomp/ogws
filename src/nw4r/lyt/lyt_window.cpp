#include <nw4r/lyt.h>

/******************************************************************************
 *
 * Texture-flip implementation
 *
 ******************************************************************************/
namespace {

using namespace nw4r;
using namespace nw4r::lyt;

/******************************************************************************
 * TextureFlipType
 ******************************************************************************/
enum TextureFlipType {
    TEXTUREFLIP_NONE,
    TEXTUREFLIP_H,
    TEXTUREFLIP_V,
    TEXTUREFLIP_90,
    TEXTUREFLIP_180,
    TEXTUREFLIP_270,

    TEXTUREFLIP_MAX
};

/******************************************************************************
 * TextureFlipIndex
 ******************************************************************************/
enum TextureFlipIndex {
    FLIPINDEX_X,
    FLIPINDEX_Y,

    FLIPINDEX_MAX
};

/******************************************************************************
 * TextureFlipInfo
 ******************************************************************************/
struct TextureFlipInfo {
    u8 coords[VERTEXCOLOR_MAX][FLIPINDEX_MAX]; // at 0x0
    u8 idx[FLIPINDEX_MAX];                     // at 0x8
};

// @typo
TextureFlipInfo& GetTexutreFlipInfo(u8 flipType) {
    static TextureFlipInfo flipInfos[TEXTUREFLIP_MAX] = {
        {{{0, 0}, {1, 0}, {0, 1}, {1, 1}}, {0, 1}}, // TEXTUREFLIP_NONE
        {{{1, 0}, {0, 0}, {1, 1}, {0, 1}}, {0, 1}}, // TEXTUREFLIP_H
        {{{0, 1}, {1, 1}, {0, 0}, {1, 0}}, {0, 1}}, // TEXTUREFLIP_V
        {{{0, 1}, {0, 0}, {1, 1}, {1, 0}}, {1, 0}}, // TEXTUREFLIP_90
        {{{1, 1}, {0, 1}, {1, 0}, {0, 0}}, {0, 1}}, // TEXTUREFLIP_180
        {{{1, 0}, {1, 1}, {0, 0}, {0, 1}}, {1, 0}}, // TEXTUREFLIP_270
    };

    return flipInfos[flipType];
}

/******************************************************************************
 * Top-left frame
 ******************************************************************************/
void GetLTFrameSize(math::VEC2* pPoint, Size* pSize, const math::VEC2& rBase,
                    const Size& rWindowSize,
                    const WindowFrameSize& rFrameSize) {

    *pPoint = rBase;

    pSize->width = rWindowSize.width - rFrameSize.r;
    pSize->height = rFrameSize.t;
}

void GetLTTexCoord(math::VEC2* pTexCoords, const Size& rSize,
                   const Size& rTexSize, u8 flipType) {

    const TextureFlipInfo& rInfo = GetTexutreFlipInfo(flipType);

    int ix = rInfo.idx[FLIPINDEX_X];
    int iy = rInfo.idx[FLIPINDEX_Y];

    math::VEC2 texSize(rTexSize.width, rTexSize.height);

    pTexCoords[VERTEXCOLOR_LT][ix] = pTexCoords[VERTEXCOLOR_LB][ix] =
        rInfo.coords[VERTEXCOLOR_LT][ix];

    pTexCoords[VERTEXCOLOR_LT][iy] = pTexCoords[VERTEXCOLOR_RT][iy] =
        rInfo.coords[VERTEXCOLOR_LT][iy];

    // clang-format off
    pTexCoords[VERTEXCOLOR_RB][ix] = pTexCoords[VERTEXCOLOR_RT][ix] =
        rInfo.coords[VERTEXCOLOR_LT][ix] + rSize.width /
        ((rInfo.coords[VERTEXCOLOR_RT][ix] - rInfo.coords[VERTEXCOLOR_LT][ix]) * texSize[ix]);
    
    pTexCoords[VERTEXCOLOR_RB][iy] = pTexCoords[VERTEXCOLOR_LB][iy] =
        rInfo.coords[VERTEXCOLOR_LT][iy] + rSize.height /
        ((rInfo.coords[VERTEXCOLOR_LB][iy] - rInfo.coords[VERTEXCOLOR_LT][iy]) * texSize[iy]);
    // clang-format on
}

/******************************************************************************
 * Top-right frame
 ******************************************************************************/
void GetRTFrameSize(math::VEC2* pPoint, Size* pSize, const math::VEC2& rBase,
                    const Size& rWindowSize,
                    const WindowFrameSize& rFrameSize) {

    *pPoint = math::VEC2(rBase.x + rWindowSize.width - rFrameSize.r, rBase.y);

    pSize->width = rFrameSize.r;
    pSize->height = rWindowSize.height - rFrameSize.b;
}

void GetRTTexCoord(math::VEC2* pTexCoords, const Size& rSize,
                   const Size& rTexSize, u8 flipType) {

    const TextureFlipInfo& rInfo = GetTexutreFlipInfo(flipType);

    int ix = rInfo.idx[FLIPINDEX_X];
    int iy = rInfo.idx[FLIPINDEX_Y];

    math::VEC2 texSize(rTexSize.width, rTexSize.height);

    pTexCoords[VERTEXCOLOR_RT][ix] = pTexCoords[VERTEXCOLOR_RB][ix] =
        rInfo.coords[VERTEXCOLOR_RT][ix];

    pTexCoords[VERTEXCOLOR_RT][iy] = pTexCoords[VERTEXCOLOR_LT][iy] =
        rInfo.coords[VERTEXCOLOR_RT][iy];

    // clang-format off
    pTexCoords[VERTEXCOLOR_LB][ix] = pTexCoords[VERTEXCOLOR_LT][ix] =
        rInfo.coords[VERTEXCOLOR_RT][ix] + rSize.width /
        ((rInfo.coords[VERTEXCOLOR_LT][ix] - rInfo.coords[VERTEXCOLOR_RT][ix]) * texSize[ix]);
    
    pTexCoords[VERTEXCOLOR_LB][iy] = pTexCoords[VERTEXCOLOR_RB][iy] =
        rInfo.coords[VERTEXCOLOR_RT][iy] + rSize.height /
        ((rInfo.coords[VERTEXCOLOR_RB][iy] - rInfo.coords[VERTEXCOLOR_RT][iy]) * texSize[iy]);
    // clang-format on
}

/******************************************************************************
 * Bottom-left frame
 ******************************************************************************/
void GetLBFrameSize(math::VEC2* pPoint, Size* pSize, const math::VEC2& rBase,
                    const Size& rWindowSize,
                    const WindowFrameSize& rFrameSize) {

    *pPoint = math::VEC2(rBase.x, rBase.y + rFrameSize.t);

    pSize->width = rFrameSize.l;
    pSize->height = rWindowSize.height - rFrameSize.t;
}

void GetLBTexCoord(math::VEC2* pTexCoords, const Size& rSize,
                   const Size& rTexSize, u8 flipType) {

    const TextureFlipInfo& rInfo = GetTexutreFlipInfo(flipType);

    int ix = rInfo.idx[FLIPINDEX_X];
    int iy = rInfo.idx[FLIPINDEX_Y];

    math::VEC2 texSize(rTexSize.width, rTexSize.height);

    pTexCoords[VERTEXCOLOR_LB][ix] = pTexCoords[VERTEXCOLOR_LT][ix] =
        rInfo.coords[VERTEXCOLOR_LB][ix];

    pTexCoords[VERTEXCOLOR_LB][iy] = pTexCoords[VERTEXCOLOR_RB][iy] =
        rInfo.coords[VERTEXCOLOR_LB][iy];

    // clang-format off
    pTexCoords[VERTEXCOLOR_RT][ix] = pTexCoords[VERTEXCOLOR_RB][ix] =
        rInfo.coords[VERTEXCOLOR_LB][ix] + rSize.width /
        ((rInfo.coords[VERTEXCOLOR_RB][ix] - rInfo.coords[VERTEXCOLOR_LB][ix]) * texSize[ix]);
    
    pTexCoords[VERTEXCOLOR_RT][iy] = pTexCoords[VERTEXCOLOR_LT][iy] =
        rInfo.coords[VERTEXCOLOR_LB][iy] + rSize.height / 
        ((rInfo.coords[VERTEXCOLOR_LT][iy] - rInfo.coords[VERTEXCOLOR_LB][iy]) * texSize[iy]);
    // clang-format on
}

/******************************************************************************
 * Bottom-right frame
 ******************************************************************************/
void GetRBFrameSize(math::VEC2* pPoint, Size* pSize, const math::VEC2& rBase,
                    const Size& rWindowSize,
                    const WindowFrameSize& rFrameSize) {

    *pPoint = math::VEC2(rBase.x + rFrameSize.l,
                         rBase.y + rWindowSize.height - rFrameSize.b);

    pSize->width = rWindowSize.width - rFrameSize.l;
    pSize->height = rFrameSize.b;
}

void GetRBTexCoord(math::VEC2* pTexCoords, const Size& rSize,
                   const Size& rTexSize, u8 flipType) {

    const TextureFlipInfo& rInfo = GetTexutreFlipInfo(flipType);

    int ix = rInfo.idx[FLIPINDEX_X];
    int iy = rInfo.idx[FLIPINDEX_Y];

    math::VEC2 texSize(rTexSize.width, rTexSize.height);

    pTexCoords[VERTEXCOLOR_RB][ix] = pTexCoords[VERTEXCOLOR_RT][ix] =
        rInfo.coords[VERTEXCOLOR_RB][ix];

    pTexCoords[VERTEXCOLOR_RB][iy] = pTexCoords[VERTEXCOLOR_LB][iy] =
        rInfo.coords[VERTEXCOLOR_RB][iy];

    // clang-format off
    pTexCoords[VERTEXCOLOR_LT][ix] = pTexCoords[VERTEXCOLOR_LB][ix] =
        rInfo.coords[VERTEXCOLOR_RB][ix] + rSize.width /
        ((rInfo.coords[VERTEXCOLOR_LB][ix] - rInfo.coords[VERTEXCOLOR_RB][ix]) * texSize[ix]);

    pTexCoords[VERTEXCOLOR_LT][iy] = pTexCoords[VERTEXCOLOR_RT][iy] =
        rInfo.coords[VERTEXCOLOR_RB][iy] + rSize.height /
        ((rInfo.coords[VERTEXCOLOR_RT][iy] - rInfo.coords[VERTEXCOLOR_RB][iy]) * texSize[iy]);
    // clang-format on
}

} // namespace

namespace nw4r {
namespace lyt {

NW4R_UT_RTTI_DEF_DERIVED(Window, Pane);

/******************************************************************************
 *
 * Window
 *
 ******************************************************************************/
Window::Window(const res::Window* pRes, const ResBlockSet& rBlockSet)
    : Pane(pRes) {

    mContentInflation = pRes->inflation;

    const u32* const pMatOffsetTbl = detail::ConvertOffsToPtr<u32>(
        rBlockSet.pMaterialList, sizeof(res::MaterialList));

    const res::WindowContent* pResContent =
        detail::ConvertOffsToPtr<res::WindowContent>(pRes, pRes->contentOffset);

    for (int i = 0; i < VERTEXCOLOR_MAX; i++) {
        mContent.vtxColors[i] = pResContent->vtxCols[i];
    }

    if (pResContent->texCoordNum > 0) {
        u8 num = ut::Min<u8>(pResContent->texCoordNum, GX_MAX_TEXCOORD);
        mContent.texCoordAry.Reserve(num);

        if (!mContent.texCoordAry.IsEmpty()) {
            mContent.texCoordAry.Copy(reinterpret_cast<const u8*>(pResContent) +
                                          sizeof(res::WindowContent),
                                      num);
        }
    }

    void* pMaterialBuf = Layout::AllocMemory(sizeof(Material));

    if (pMaterialBuf != NULL) {
        const res::Material* const pResMaterial =
            detail::ConvertOffsToPtr<res::Material>(
                rBlockSet.pMaterialList,
                pMatOffsetTbl[pResContent->materialIdx]);

        mpMaterial = new (pMaterialBuf) Material(pResMaterial, rBlockSet);
    }

    mFrameNum = 0;
    mFrames = NULL;

    if (pRes->frameNum > 0) {
        mFrames = static_cast<Frame*>(
            Layout::AllocMemory(pRes->frameNum * sizeof(Frame)));

        if (mFrames != NULL) {
            mFrameNum = pRes->frameNum;

            const u32* const pFrmOffsetTbl = detail::ConvertOffsToPtr<u32>(
                pRes, pRes->frameOffsetTableOffset);

            for (int i = 0; i < mFrameNum; i++) {
                const res::WindowFrame* const pResFrame =
                    detail::ConvertOffsToPtr<res::WindowFrame>(
                        pRes, pFrmOffsetTbl[i]);

                mFrames[i].textureFlip = pResFrame->textureFlip;
                mFrames[i].pMaterial = NULL;

                void* pMaterialBuf = Layout::AllocMemory(sizeof(Material));

                if (pMaterialBuf != NULL) {
                    const res::Material* const pResMaterial =
                        detail::ConvertOffsToPtr<res::Material>(
                            rBlockSet.pMaterialList,
                            pMatOffsetTbl[pResFrame->materialIdx]);

                    mFrames[i].pMaterial =
                        new (pMaterialBuf) Material(pResMaterial, rBlockSet);
                }
            }
        }
    }
}

Window::~Window() {
    if (mFrames != NULL) {
        for (int i = 0; i < mFrameNum; i++) {
            mFrames[i].pMaterial->~Material();
            Layout::FreeMemory(mFrames[i].pMaterial);
        }

        Layout::FreeMemory(mFrames);
    }

    if (mpMaterial != NULL && !mpMaterial->IsUserAllocated()) {
        mpMaterial->~Material();
        Layout::FreeMemory(mpMaterial);
        mpMaterial = NULL;
    }

    mContent.texCoordAry.Free();
}

Material* Window::FindMaterialByName(const char* pName, bool recursive) {
    if (mpMaterial != NULL &&
        detail::EqualsMaterialName(mpMaterial->GetName(), pName)) {

        return mpMaterial;
    }

    for (int i = 0; i < mFrameNum; i++) {
        if (detail::EqualsMaterialName(mFrames[i].pMaterial->GetName(),
                                       pName)) {

            return mFrames[i].pMaterial;
        }
    }

    if (recursive) {
        NW4R_UT_LINKLIST_FOREACH(it, mChildList, {
            Material* pMaterial = it->FindMaterialByName(pName, true);
            
            if (pMaterial != NULL) {
                return pMaterial;
            }
        });
    }

    return NULL;
}

AnimationLink* Window::FindAnimationLink(AnimTransform* pAnimTrans) {
    AnimationLink* pAnimLink = Pane::FindAnimationLink(pAnimTrans);

    if (pAnimLink != NULL) {
        return pAnimLink;
    }

    for (int i = 0; i < mFrameNum; i++) {
        AnimationLink* pAnimLink =
            mFrames[i].pMaterial->FindAnimationLink(pAnimTrans);

        if (pAnimLink != NULL) {
            return pAnimLink;
        }
    }

    return NULL;
}

void Window::SetAnimationEnable(AnimTransform* pAnimTrans, bool enable,
                                bool recursive) {

    for (int i = 0; i < mFrameNum; i++) {
        mFrames[i].pMaterial->SetAnimationEnable(pAnimTrans, enable);
    }

    Pane::SetAnimationEnable(pAnimTrans, enable, recursive);
}

ut::Color Window::GetVtxColor(u32 idx) const {
    return mContent.vtxColors[idx];
}

void Window::SetVtxColor(u32 idx, ut::Color color) {
    mContent.vtxColors[idx] = color;
}

u8 Window::GetVtxColorElement(u32 idx) const {
    return detail::GetVtxColorElement(mContent.vtxColors, idx);
}

void Window::SetVtxColorElement(u32 idx, u8 value) {
    detail::SetVtxColorElement(mContent.vtxColors, idx, value);
}

void Window::DrawSelf(const DrawInfo& rInfo) {
    LoadMtx(rInfo);

    WindowFrameSize size = GetFrameSize(mFrameNum, mFrames);
    math::VEC2 base = GetVtxPos();
    DrawContent(base, size, mGlbAlpha);

    switch (mFrameNum) {
    case 1: {
        DrawFrame(base, mFrames[WINDOWFRAME_LT], size, mGlbAlpha);
        break;
    }

    case 4: {
        DrawFrame4(base, mFrames, size, mGlbAlpha);
        break;
    }

    case 8: {
        DrawFrame8(base, mFrames, size, mGlbAlpha);
        break;
    }
    }
}

void Window::AnimateSelf(u32 option) {
    Pane::AnimateSelf(option);

    if (IsVisible() || !(option & ANIMOPTION_SKIP_INVISIBLE)) {
        for (int i = 0; i < mFrameNum; i++) {
            mFrames[i].pMaterial->Animate();
        }
    }
}

void Window::UnbindAnimationSelf(AnimTransform* pAnimTrans) {
    for (int i = 0; i < mFrameNum; i++) {
        mFrames[i].pMaterial->UnbindAnimation(pAnimTrans);
    }

    Pane::UnbindAnimationSelf(pAnimTrans);
}

void Window::DrawContent(const math::VEC2& rBase,
                         const WindowFrameSize& rFrameSize, u8 alpha) {

    bool useVtxColor = mpMaterial->SetupGX(
        detail::IsModulateVertexColor(mContent.vtxColors, alpha), alpha);

    detail::SetVertexFormat(useVtxColor, mContent.texCoordAry.GetSize());

    // clang-format off
    detail::DrawQuad(
        math::VEC2(rBase.x + rFrameSize.l - mContentInflation.l,
                   rBase.y + rFrameSize.t - mContentInflation.t),

        Size(mSize.width - rFrameSize.l + mContentInflation.l - rFrameSize.r + mContentInflation.r,
             mSize.height - rFrameSize.t + mContentInflation.t - rFrameSize.b + mContentInflation.b),

        mContent.texCoordAry.GetSize(),
        mContent.texCoordAry.GetArray(),
        
        useVtxColor ? mContent.vtxColors : NULL,
        alpha);
    // clang-format on
}

void Window::DrawFrame(const math::VEC2& rBase, const Frame& rFrame,
                       const WindowFrameSize& rFrameSize, u8 alpha) {

    if (rFrame.pMaterial->GetTextureNum() == 0) {
        return;
    }

    bool useVtxColor = rFrame.pMaterial->SetupGX(
        detail::IsModulateVertexColor(NULL, alpha), alpha);

    detail::SetVertexFormat(useVtxColor, 1);

    Size texSize = detail::GetTextureSize(rFrame.pMaterial, 0);
    ut::Color vtxColors[VERTEXCOLOR_MAX];
    detail::TexCoord texCoords[1];

    math::VEC2 point;
    Size size;

#define DRAW_FRAME(FRAME, FLIP)                                                \
    Get##FRAME##FrameSize(&point, &size, rBase, mSize, rFrameSize);            \
    Get##FRAME##TexCoord(texCoords[0], size, texSize, FLIP);                   \
                                                                               \
    detail::DrawQuad(point, size, 1, texCoords,                                \
                     useVtxColor ? vtxColors : NULL, alpha);

    DRAW_FRAME(LT, TEXTUREFLIP_NONE);
    DRAW_FRAME(RT, TEXTUREFLIP_H);
    DRAW_FRAME(RB, TEXTUREFLIP_180);
    DRAW_FRAME(LB, TEXTUREFLIP_V);

#undef DRAW_FRAME
}

void Window::DrawFrame4(const math::VEC2& rBase, const Frame* pFrames,
                        const WindowFrameSize& rFrameSize, u8 alpha) {

    ut::Color vtxColors[VERTEXCOLOR_MAX];
    detail::TexCoord texCoords[1];

    math::VEC2 point;
    Size size;

    bool modVtxColor = detail::IsModulateVertexColor(NULL, alpha);

#define DRAW_FRAME(FRAME)                                                      \
    if (pFrames[WINDOWFRAME_##FRAME].pMaterial->GetTextureNum() > 0) {         \
        bool useVtxColor = pFrames[WINDOWFRAME_##FRAME].pMaterial->SetupGX(    \
            modVtxColor, alpha);                                               \
                                                                               \
        Get##FRAME##FrameSize(&point, &size, rBase, mSize, rFrameSize);        \
                                                                               \
        Get##FRAME##TexCoord(                                                  \
            texCoords[0], size,                                                \
            detail::GetTextureSize(pFrames[WINDOWFRAME_##FRAME].pMaterial, 0), \
            pFrames[WINDOWFRAME_##FRAME].textureFlip);                         \
                                                                               \
        detail::SetVertexFormat(useVtxColor, 1);                               \
        detail::DrawQuad(point, size, 1, texCoords,                            \
                         useVtxColor ? vtxColors : NULL, alpha);               \
    }

    DRAW_FRAME(LT);
    DRAW_FRAME(RT);
    DRAW_FRAME(RB);
    DRAW_FRAME(LB);

#undef DRAW_FRAME
}

void Window::DrawFrame8(const math::VEC2& rBase, const Frame* pFrames,
                        const WindowFrameSize& rFrameSize, u8 alpha) {

    ut::Color vtxColors[VERTEXCOLOR_MAX];
    detail::TexCoord texCoords[1];

    Size size;

    bool modVtxColor = detail::IsModulateVertexColor(NULL, alpha);

#define DRAW_FRAME_EX(FRAME, TEXCOORD, SIZE, POINT)                            \
    if (pFrames[WINDOWFRAME_##FRAME].pMaterial->GetTextureNum() > 0) {         \
        bool useVtxColor = pFrames[WINDOWFRAME_##FRAME].pMaterial->SetupGX(    \
            modVtxColor, alpha);                                               \
                                                                               \
        size = SIZE;                                                           \
                                                                               \
        Get##TEXCOORD##TexCoord(                                               \
            texCoords[0], size,                                                \
            detail::GetTextureSize(pFrames[WINDOWFRAME_##FRAME].pMaterial, 0), \
            pFrames[WINDOWFRAME_##FRAME].textureFlip);                         \
                                                                               \
        detail::SetVertexFormat(useVtxColor, 1);                               \
        detail::DrawQuad(POINT, size, 1, texCoords,                            \
                         useVtxColor ? vtxColors : NULL, alpha);               \
    }

#define DRAW_FRAME(FRAME, SIZE, POINT) DRAW_FRAME_EX(FRAME, FRAME, SIZE, POINT)

    // clang-format off
    DRAW_FRAME(LT,
               Size(rFrameSize.l,
                    rFrameSize.t),
               rBase);

    DRAW_FRAME_EX(T, LT,
               Size(mSize.width - rFrameSize.l - rFrameSize.r,
                    rFrameSize.t),
               math::VEC2(rBase.x + rFrameSize.l,
                          rBase.y));

    DRAW_FRAME(RT,
               Size(rFrameSize.r,
                    rFrameSize.t),
               math::VEC2(rBase.x + mSize.width - rFrameSize.r,
                          rBase.y));

    DRAW_FRAME_EX(R, RT,
               Size(rFrameSize.r,
                    mSize.height - rFrameSize.t - rFrameSize.b),
               math::VEC2(rBase.x + mSize.width - rFrameSize.r,
                          rBase.y + rFrameSize.t));

    DRAW_FRAME(RB,
               Size(rFrameSize.r,
                    rFrameSize.b),
               math::VEC2(rBase.x + mSize.width - rFrameSize.r,
                          rBase.y + mSize.height - rFrameSize.b));

    DRAW_FRAME_EX(B, RB,
               Size(mSize.width - rFrameSize.l - rFrameSize.r,
                    rFrameSize.b),
               math::VEC2(rBase.x + rFrameSize.l,
                          rBase.y + mSize.height - rFrameSize.b));

    DRAW_FRAME(LB,
               Size(rFrameSize.l,
                    rFrameSize.b),
               math::VEC2(rBase.x,
                          rBase.y + mSize.height - rFrameSize.b));

    DRAW_FRAME_EX(L, LB,
               Size(rFrameSize.l,
                    mSize.height - rFrameSize.t - rFrameSize.b),
               math::VEC2(rBase.x,
                          rBase.y + rFrameSize.t));
    // clang-format on

#undef DRAW_FRAME
#undef DRAW_FRAME_EX
}

WindowFrameSize Window::GetFrameSize(u8 frameNum, const Frame* pFrames) {
    WindowFrameSize frameSize = {0.0f, 0.0f, 0.0f, 0.0f};

    switch (frameNum) {
    case 1: {
        Size texSize =
            detail::GetTextureSize(pFrames[WINDOWFRAME_LT].pMaterial, 0);

        frameSize.l = texSize.width;
        frameSize.t = texSize.height;

        frameSize.r = texSize.width;
        frameSize.b = texSize.height;
        break;
    }

    case 4:
    case 8: {
        Size texSize =
            detail::GetTextureSize(pFrames[WINDOWFRAME_LT].pMaterial, 0);

        frameSize.l = texSize.width;
        frameSize.t = texSize.height;

        texSize = detail::GetTextureSize(pFrames[WINDOWFRAME_RB].pMaterial, 0);

        frameSize.r = texSize.width;
        frameSize.b = texSize.height;
        break;
    }
    }

    return frameSize;
}

Material* Window::GetContentMaterial() const {
    return GetMaterial();
}

Material* Window::GetFrameMaterial(u32 idx) const {
    if (idx >= mFrameNum) {
        return NULL;
    }

    return mFrames[idx].pMaterial;
}

} // namespace lyt
} // namespace nw4r
