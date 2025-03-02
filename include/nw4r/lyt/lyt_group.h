#ifndef NW4R_LYT_GROUP_H
#define NW4R_LYT_GROUP_H
#include <nw4r/types_nw4r.h>

#include <nw4r/lyt/lyt_resources.h>

#include <nw4r/ut.h>

namespace nw4r {
namespace lyt {

// Forward declarations
class Pane;

namespace detail {

/******************************************************************************
 *
 * PaneLink
 *
 ******************************************************************************/
struct PaneLink {
    NW4R_UT_LINKLIST_NODE_DECL(); // at 0x4
    Pane* mTarget;                // at 0x8
};

NW4R_UT_LINKLIST_TYPEDEF_DECL(PaneLink);

} // namespace detail

namespace res {

/******************************************************************************
 *
 * GRP1 binary layout
 *
 ******************************************************************************/
struct Group {
    static const u32 SIGNATURE = 'grp1';

    DataBlockHeader blockHeader;      // at 0x0
    char name[NW4R_LYT_RES_NAME_LEN]; // at 0x8
    u16 paneNum;                      // at 0x18
    u8 PADDING_0x1A[0x1C - 0x1A];     // at 0x1A
};

} // namespace res

/******************************************************************************
 *
 * Group
 *
 ******************************************************************************/
class Group {
public:
    Group(const res::Group* pRes, Pane* pRootPane);
    virtual ~Group(); // at 0x8

    void AppendPane(Pane* pPane);

    detail::PaneLinkList& GetPaneList() {
        return mPaneLinkList;
    }

    const char* GetName() const {
        return mName;
    }

    bool IsUserAllocated() const {
        return mbUserAllocated;
    }

public:
    NW4R_UT_LINKLIST_NODE_DECL(); // at 0x4

protected:
    detail::PaneLinkList mPaneLinkList;    // at 0xC
    char mName[NW4R_LYT_RES_NAME_LEN + 1]; // at 0x18
    bool mbUserAllocated;                  // at 0x29
    u8 PADDING_0x2A[0x2C - 0x2A];          // at 0x2A

private:
    void Init();
};

NW4R_UT_LINKLIST_TYPEDEF_DECL(Group);

/******************************************************************************
 *
 * GroupContainer
 *
 ******************************************************************************/
class GroupContainer {
public:
    GroupContainer() {}
    ~GroupContainer();

    void AppendGroup(Group* pGroup);
    Group* FindGroupByName(const char* pName);

    GroupList& GetGroupList() {
        return mGroupList;
    }

protected:
    GroupList mGroupList; // at 0x0
};

} // namespace lyt
} // namespace nw4r

#endif
