#pragma ipa file

#include "lyt_group.h"
#include "lyt_layout.h"
#include "ut_algorithm.h"
#include "ut_LinkList.h"
#include <string.h>

namespace nw4r
{
    namespace lyt
    {
        using namespace ut;
        using namespace detail;

        Group::Group(const res::Group *res, Pane *pane) : mNode(), mPaneList()
        {
            Init();
            strncpy(mName, res->mName, NW4R_RES_NAME_SIZE);
            mName[NW4R_RES_NAME_SIZE - 1] = '\0';

            const char *base = (const char *)AddOffsetToPtr<u32>(res, 0x1C);
            for (int i = 0; i < res->SHORT_0x18; i++)
            {
                Pane *p = pane->FindPaneByName(base + i * NW4R_RES_NAME_SIZE, true);
                if (p) AppendPane(p);
            }
        }

        // Inlined
        void Group::Init()
        {
            mIsUserAllocated = false;
        }

        Group::~Group()
        {
            LinkList<PaneLink, 0>::Iterator it = mPaneList.GetBeginIter();
            while (it != mPaneList.GetEndIter())
            {
                LinkList<PaneLink, 0>::Iterator temp = it++;
                mPaneList.Erase(temp);
                Layout::DeleteObj<PaneLink>(&*temp);
            }
        }

        // Inlined
        void Group::AppendPane(Pane *pane)
        {
            PaneLink *link = Layout::NewObj<PaneLink>();
            link->PANE_0x8 = pane;
            mPaneList.PushBack(link);
        }

        GroupContainer::~GroupContainer()
        {
            LinkList<Group, 4>::Iterator it = mGroups.GetBeginIter();
            while (it != mGroups.GetEndIter())
            {
                LinkList<Group, 4>::Iterator temp = it++;
                mGroups.Erase(temp);
                if (!temp->mIsUserAllocated) Layout::DeleteObj<Group>(&*temp);
            }
        }

        // Inlined
        void GroupContainer::AppendGroup(Group *g)
        {
            mGroups.PushBack(g);
        }

        Group * GroupContainer::FindGroupByName(const char *name)
        {
            LinkList<Group, 4>::Iterator it = mGroups.GetBeginIter();
            for (; it != mGroups.GetEndIter(); it++)
            {
                if (EqualsResName(it->mName, name)) return &*it;
            }

            return NULL;
        }
    }
}
