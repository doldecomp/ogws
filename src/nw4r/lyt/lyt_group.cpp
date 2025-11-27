#include <nw4r/lyt.h>
#include <nw4r/ut.h>

#include <cstring>

namespace nw4r {
namespace lyt {

/******************************************************************************
 *
 * Group
 *
 ******************************************************************************/
Group::Group(const res::Group* pRes, Pane* pRootPane) {
    Init();

    std::strncpy(mName, pRes->name, NW4R_LYT_RES_NAME_LEN);
    mName[NW4R_LYT_RES_NAME_LEN] = '\0';

    const char* pNameBase =
        detail::ConvertOffsToPtr<char>(pRes, sizeof(res::Group));

    for (int i = 0; i < pRes->paneNum; i++) {
        Pane* pResult = pRootPane->FindPaneByName(
            pNameBase + i * NW4R_LYT_RES_NAME_LEN, true);

        if (pResult != NULL) {
            AppendPane(pResult);
        }
    }
}

void Group::Init() {
    mbUserAllocated = false;
}

Group::~Group() {
    NW4R_UT_LINKLIST_FOREACH_SAFE (it, mPaneLinkList, {
        mPaneLinkList.Erase(it);
        Layout::FreeMemory(&*it);
    })
}

void Group::AppendPane(Pane* pPane) {
    void* pBuffer = Layout::AllocMemory(sizeof(detail::PaneLink));
    if (pBuffer == NULL) {
        return;
    }

    detail::PaneLink* pLink = new (pBuffer) detail::PaneLink();
    pLink->mTarget = pPane;

    mPaneLinkList.PushBack(pLink);
}

/******************************************************************************
 *
 * GroupContainer
 *
 ******************************************************************************/
GroupContainer::~GroupContainer() {
    NW4R_UT_LINKLIST_FOREACH_SAFE (it, mGroupList, {
        mGroupList.Erase(it);
        
        if (!it->IsUserAllocated()) {
            it->~Group();
            Layout::FreeMemory(&*it);
        }
    })
}

void GroupContainer::AppendGroup(Group* pGroup) {
    mGroupList.PushBack(pGroup);
}

Group* GroupContainer::FindGroupByName(const char* pName) {
    NW4R_UT_LINKLIST_FOREACH (it, mGroupList, {
        if (detail::EqualsResName(it->GetName(), pName)) {
            return &*it;
        }
    })

    return NULL;
}

} // namespace lyt
} // namespace nw4r
