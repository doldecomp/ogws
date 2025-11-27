#ifndef RP_KERNEL_LAYOUT_H
#define RP_KERNEL_LAYOUT_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel/RPSysLytDynamicAnm.h>

#include <egg/core.h>
#include <egg/math.h>

#include <nw4r/lyt.h>
#include <nw4r/ut.h>

#include <revolution/WPAD.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class RPGrpScreen;
class RPSysKokeshiIcon;
class RPSysLytAnmObj;
class RPSysLytBounding;
class RPSysLytPicture;
class RPSysLytResAccessor;
class RPSysLytTextBox;
class RPSysLytWindow;
class RPSysMessage;

/**
 * @brief NW4R layout wrapper
 * @details Supports dynamic animation, Mii icons, and player slot TEV colors.
 */
class RPSysLayout {
public:
    /**
     * @brief Initializes the layout system
     * @details Initializes the NW4R layout library
     */
    static void initialize();

    /**
     * @brief Creates a layout from the specified binary file
     *
     * @param pHeap Heap to use for allocations
     * @param pAccessor Layout resource accessor
     * @param pName Binary layout file name
     */
    static RPSysLayout* create(EGG::Heap* pHeap, RPSysLytResAccessor* pAccessor,
                               const char* pName);

    /**
     * @brief Creates a animation object from the specified binary file
     *
     * @param pHeap Heap to use for allocations
     * @param pAccessor Layout resource accessor
     * @param pName Binary animation file name
     */
    RPSysLytAnmObj* createAnmObj(EGG::Heap* pHeap,
                                 RPSysLytResAccessor* pAccessor,
                                 const char* pName);

    /**
     * @brief Binds a new animation object to this layout
     *
     * @param pAnmObj Animation object
     */
    void bindAnmObj(RPSysLytAnmObj* pAnmObj);

    /**
     * @brief Unbinds an animation object from this layout
     *
     * @param pAnmObj Animation object
     */
    void unbindAnmObj(RPSysLytAnmObj* pAnmObj);

    /**
     * @brief Unbinds all animation objects from this layout
     */
    void unbindAllAnmObj();

    /**
     * @brief Binds a new animation object to the specified pane
     * @details This function searches the pane tree of this layout
     *
     * @param pAnmObj Animation object
     * @param pName Pane name
     * @param recursive Whether to recursively resolve the animation target
     */
    void bindAnmObjToPane(RPSysLytAnmObj* pAnmObj, const char* pName,
                          bool recursive);

    /**
     * @brief Binds a new animation object to the specified pane
     *
     * @param pAnmObj Animation object
     * @param pPane Target pane
     * @param recursive Whether to recursively resolve the animation target
     */
    static void bindAnmObjToPane(RPSysLytAnmObj* pAnmObj,
                                 nw4r::lyt::Pane* pPane, bool recursive);

    /**
     * @brief Forcibly binds a new animation object to the specified pane
     * @details This function allows binding an animation object that shares a
     * name prefix with the pane.
     *
     * As long as the names match up to the last two characters, this function
     * will correctly find the pane.
     *
     * This function is used to bind animations targeting panes such as
     * `P_MyPane_00` to any pane of the format `P_MyPane_XX`. NW4R requires an
     * exact name match to bind, so this function reimplements
     * `AnimTransformBasic::Bind`.
     *
     * @param pAnmObj Animation object
     * @param pPane Target pane
     * @param recursive Whether to recursively resolve the animation target
     */
    static void forceBindAnmObjToPane(RPSysLytAnmObj* pAnmObj,
                                      nw4r::lyt::Pane* pPane, bool recursive);

    /**
     * @brief Unbinds an animation object from the specified pane
     *
     * @param pAnmObj Animation object
     * @param pPane Target pane
     * @param recursive Whether to also unbind the animation from all children
     */
    static void unbindAnmObjToPane(RPSysLytAnmObj* pAnmObj,
                                   nw4r::lyt::Pane* pPane, bool recursive);

    /**
     * @brief Attempts to dynamic-cast the specified pane to a textbox pane
     *
     * @param pPane Target pane
     * @return Textbox if the cast is valid, otherwise NULL
     */
    static RPSysLytTextBox* castToTextBox(nw4r::lyt::Pane* pPane);

    /**
     * @brief Attempts to dynamic-cast the specified pane to a picture pane
     *
     * @param pPane Target pane
     * @return Picture if the cast is valid, otherwise NULL
     */
    static RPSysLytPicture* castToPicture(nw4r::lyt::Pane* pPane);

    /**
     * @brief Attempts to dynamic-cast the specified pane to a window pane
     *
     * @param pPane Target pane
     * @return Window if the cast is valid, otherwise NULL
     */
    static RPSysLytWindow* castToWindow(nw4r::lyt::Pane* pPane);

    /**
     * @brief Attempts to dynamic-cast the specified pane to a bounding pane
     *
     * @param pPane Target pane
     * @return Picture if the cast is valid, otherwise NULL
     */
    static RPSysLytBounding* castToBounding(nw4r::lyt::Pane* pPane);

    /**
     * @brief Searches recursively for a pane in this layout matching the
     * specified name
     *
     * @param pName Pane name
     */
    nw4r::lyt::Pane* findPane(const char* pName);

    /**
     * @brief Searches recursively for a textbox pane in this layout matching
     * the specified name
     *
     * @param pName Textbox name
     */
    RPSysLytTextBox* findTextBox(const char* pName);

    /**
     * @brief Searches recursively for a picture pane in this layout matching
     * the specified name
     *
     * @param pName Picture name
     */
    RPSysLytPicture* findPicture(const char* pName);

    /**
     * @brief Searches recursively for a window pane in this layout matching
     * the specified name
     *
     * @param pName Window name
     */
    RPSysLytWindow* findWindow(const char* pName);

    /**
     * @brief Searches recursively for a bounding pane in this layout matching
     * the specified name
     *
     * @param pName Bounding name
     */
    RPSysLytBounding* findBounding(const char* pName);

    /**
     * @brief Searches recursively for a group in this layout matching the
     * specified name
     *
     * @param pName Group name
     */
    nw4r::lyt::Group* findGroup(const char* pName);

    /**
     * @brief Resets the state of this layout and any animations it owns
     * @note This function makes the layout become invisible
     */
    void reset();

    /**
     * @brief Updates the state of this layout and any animations it owns
     * @note The layout is invisible until this function is ran
     */
    void calc();

    /**
     * @brief Configures the GX render state for layout drawing
     */
    static void drawInit();

    /**
     * @brief Draws the contents of this layout
     */
    void draw();

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
    bool changeFontColor(RPSysLytTextBox* pTextBox, u32 id);

    /**
     * @brief Tests whether a point falls within the specified bounding pane
     * @note Hit test is always ignored when the layout is invisible
     *
     * @param pBounding Bounding pane
     * @param rPoint Point to test
     */
    bool isInsideBounding(RPSysLytBounding* pBounding,
                          const EGG::Vector2f& rPoint);

    /**
     * @brief Moves the specified pane to the front of its parent's children
     *
     * @param pChild Child pane
     */
    static void becomeYoungestChild(nw4r::lyt::Pane* pChild);

    /**
     * @brief Draws a Mii icon to the specified pane
     * @details This function defaults to a white material color.
     *
     * @param screen Screen to draw to
     * @param pane Pane to draw on
     * @param icon Mii icon
     */
    static void drawKokeshiIcon(RPGrpScreen* pScreen, nw4r::lyt::Pane* pPane,
                                RPSysKokeshiIcon* pIcon);

    /**
     * @brief Draws a Mii icon to the specified pane
     * @details Uses default white material color
     *
     * @param screen Screen to draw to
     * @param pane Pane to draw on
     * @param icon Mii icon
     * @param matColor Material color
     */
    static void drawKokeshiIcon(RPGrpScreen* pScreen, nw4r::lyt::Pane* pPane,
                                RPSysKokeshiIcon* pIcon, GXColor matColor)
        DECOMP_DONT_INLINE;

    /**
     * @brief Starts playing all dynamic animations inwards
     *
     * @param frame Starting frame (-1 to play from the ending frame)
     */
    void startDynAnmIn(s16 frame);

    /**
     * @brief Starts playing all dynamic animations outwards
     *
     * @param frame Starting frame (-1 to play from the ending frame)
     */
    void startDynAnmOut(s16 frame);

    /**
     * @brief Flips the direction of all horizonal dynamic animations
     *
     * @param reverse Whether to reverse the horizontal direction
     */
    void reverseAnmHDirection(bool reverse);

    /**
     * @brief Tests whether all dynamic animations have finished animating
     * inwards
     */
    bool isFinishedDynAnmIn();

    /**
     * @brief Tests whether all dynamic animations have finished animating
     * outwards
     */
    bool isFinishedDynAnmOut();

    /**
     * @brief Gets the TEV color used to represent the specified player slot
     *
     * @param idx Player index
     */
    static const GXColor& getPlayerColor(u32 idx);

    /**
     * @brief Gets the TEV color used to represent CPU players
     */
    static const GXColor& getCpuColor();

    /**
     * @brief Accesses the draw info associated with this layout
     */
    nw4r::lyt::DrawInfo* getDrawInfo() {
        return mpDrawInfo;
    }

    /**
     * @brief Accesses the top-most pane in the tree
     */
    nw4r::lyt::Pane* getRootPane() {
        return mpLayout->GetRootPane();
    }

private:
    //! Maximum textbox string length to consider when creating the buffer
    static const int MAX_STRING_LENGTH = 512;

    /**
     * @brief State flags
     */
    enum EFlag {
        EFlag_Visible = 1 << 0,
    };

private:
    /**
     * @brief Constructor
     */
    RPSysLayout();

    /**
     * @brief Parses the length portion of a dynamic animation string
     *
     * @param pLenStr Length encoded in text form
     */
    static s16 parseDynamicAnmLength(const char* pLenStr) DECOMP_DONT_INLINE;

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
    bool checkDynamicAnmPane(nw4r::lyt::Pane* pPane,
                             RPSysLytDynamicAnm::EDirection* pDirection,
                             s16* pLength);

    /**
     * @brief Create dynamic animation objects for the specified pane
     * @note If the pane contains no dynamic animations, nothing will happen.
     *
     * @param pHeap Heap to use for allocations
     * @param pPane Pane expected to contain a dynamic animation
     */
    void createDynamicAnm(EGG::Heap* heap, nw4r::lyt::Pane* pane);

    /**
     * @brief Appends a new dynamic animation to this layout
     *
     * @param pDynamicAnm Dynamic animation
     */
    void appendDynamicAnm(RPSysLytDynamicAnm* pDynamicAnm);

    /**
     * @brief Appends a new animation object to this layout
     *
     * @param pAnmObj Animation object
     */
    void appendAnmObj(RPSysLytAnmObj* pAnmObj);

    /**
     * @brief Removes an animation object from this layout
     *
     * @param pAnmObj Animation object
     */
    void removeAnmObj(RPSysLytAnmObj* pAnmObj);

    /**
     * @brief Allocates a large textbox buffer for the pane and its children
     *
     * @param pPane Root pane
     */
    static void allocStringBuffer(nw4r::lyt::Pane* pPane);

private:
    //! Player slot TEV colors
    static const GXColor PLAYER_COLORS[WPAD_MAX_CONTROLLERS];
    //! CPU TEV color
    static const GXColor CPU_COLOR;

    //! State flags
    u16 mFlags; // at 0x0

    //! Horizontal scale applied to the root pane
    f32 mScaleX; // at 0x4
    f32 unk8;
    f32 unkC;

    //! Horizontal scale applied to panes with location adjust
    f32 mAdjScaleX; // at 0x10
    f32 unk14;
    f32 unk18;

    //! Layout draw info
    nw4r::lyt::DrawInfo* mpDrawInfo; // at 0x1C
    //! Parent layout
    nw4r::lyt::Layout* mpLayout; // at 0x20

    //! List of basic animations
    nw4r::ut::List mAnmObjList; // at 0x24
    //! List of dynamic animations
    nw4r::ut::List mDynamicAnmList; // at 0x30
};

//! @}

#endif
