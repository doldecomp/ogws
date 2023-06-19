#pragma ipa file
#include "g3d_anmvis.h"
#include "ut_algorithm.h"

namespace nw4r
{
    namespace g3d
    {
        NW4R_G3D_TYPE_OBJ_DEF(AnmObjVis);
        NW4R_G3D_TYPE_OBJ_DEF(AnmObjVisNode);
        NW4R_G3D_TYPE_OBJ_DEF(AnmObjVisOR);
        NW4R_G3D_TYPE_OBJ_DEF(AnmObjVisRes);

        AnmObjVis::AnmObjVis(MEMAllocator *allocator, u16 *bindBuffer, int numBinds)
            : AnmObj(allocator, NULL), mBinds(bindBuffer), mNumBinds(numBinds)
        {
            Release();
        }

        bool AnmObjVis::TestDefined(u32 idx) const
        {
            return (mBinds[idx] & 0x8000) == 0;
        }

        bool AnmObjVis::TestExistence(u32 idx) const
        {
            return (mBinds[idx] & 0xC000) == 0;
        }

        void AnmObjVis::Release()
        {
            for (int i = 0; i < mNumBinds; i++)
            {
                mBinds[i] = 0x8000;
            }

            SetAnmFlag(ANMFLAG_ISBOUND, false);
        }

        AnmObjVisRes * AnmObjVis::Attach(int idx, AnmObjVisRes *pRes)
        {
            return NULL;
        }

        AnmObjVisRes * AnmObjVis::Detach(int idx)
        {
            return NULL;
        }

        void AnmObjVis::DetachAll()
        {
            for (int i = 0; i < MAX_RESOURCES; i++)
            {
                Detach(i);
            }
        }

        void AnmObjVis::G3dProc(u32 task, u32 taskArg1, void *taskArg2)
        {
            switch(task)
            {
                case G3DPROC_UPDATEFRAME:
                    SetAnmFlag(ANMFLAG_2, true);
                    break;
                case G3DPROC_DETACH_PARENT:
                    SetParent(NULL);
                    break;
                case G3DPROC_ATTACH_PARENT:
                    SetParent((G3dObj *)taskArg2);
                    break;
            }
        }

        namespace
        {
            void UNUSED_FUNC_ORDER_ANMVIS_0(AnmObjVis *vis)
            {
                vis->~AnmObjVis();
            }
        }

        AnmObjVisNode::~AnmObjVisNode()
        {
            DetachAll();
        }

        AnmObjVisRes * AnmObjVisNode::Attach(int idx, AnmObjVisRes *pRes)
        {
            AnmObjVisRes *backup = Detach(idx);

            bool isAttach = false;
            for (u32 i = 0; i < mNumBinds; i++)
            {
                if (pRes->TestDefined(i))
                {
                    isAttach = true;
                    mBinds[i] = 0x0000;
                }
            }

            if (isAttach) SetAnmFlag(ANMFLAG_ISBOUND, true);

            mResources[idx] = pRes;
            pRes->G3dProc(G3DPROC_ATTACH_PARENT, 0, this);

            return backup;
        }

        AnmObjVisRes * AnmObjVisNode::Detach(int idx)
        {
            AnmObjVisRes *backup = mResources[idx];
            if (backup != NULL)
            {
                backup->G3dProc(G3DPROC_DETACH_PARENT, 0, this);
                mResources[idx] = NULL;

                bool b = false;
                for (u32 i = 0; i < mNumBinds; i++)
                {
                    u16 bind = 0x8000;
                    for (int j = 0; j < MAX_RESOURCES; j++)
                    {
                        AnmObjVisRes *res = mResources[j];
                        if (res != NULL && res->TestDefined(i))
                        {
                            b = true;
                            bind = 0x0000;
                            break;
                        }
                    }

                    mBinds[i] = bind;
                }

                if (!b) SetAnmFlag(ANMFLAG_ISBOUND, false);
            }

            return backup;
        }

        void AnmObjVisNode::UpdateFrame()
        {
            for (int i = 0; i < MAX_RESOURCES; i++)
            {
                if (mResources[i] != NULL) mResources[i]->UpdateFrame();
            }
        }

        void AnmObjVisNode::SetFrame(f32 frame)
        {
            for (int i = 0; i < MAX_RESOURCES; i++)
            {
                if (mResources[i] != NULL) mResources[i]->SetFrame(frame);
            }
        }

        f32 AnmObjVisNode::GetFrame() const
        {
            for (int i = 0; i < MAX_RESOURCES; i++)
            {
                if (mResources[i] != NULL) return mResources[i]->GetFrame();
            }

            return 0.0f;
        }

        void AnmObjVisNode::SetUpdateRate(f32 rate)
        {
            for (int i = 0; i < MAX_RESOURCES; i++)
            {
                if (mResources[i] != NULL) mResources[i]->SetUpdateRate(rate);
            }
        }

        f32 AnmObjVisNode::GetUpdateRate() const
        {
            for (int i = 0; i < MAX_RESOURCES; i++)
            {
                if (mResources[i] != NULL) return mResources[i]->GetUpdateRate();
            }

            return 1.0f;
        }

        bool AnmObjVisNode::Bind(ResMdl mdl)
        {
            bool success = false;
            for (int i = 0; i < MAX_RESOURCES; i++)
            {
                AnmObjVisRes *res = mResources[i];
                if (res != NULL)
                {
                    bool childSuccess = res->Bind(mdl);
                    success = (success || childSuccess);

                    for (u32 j = 0; j < mNumBinds; j++)
                    {
                        if (res->TestDefined(j)) mBinds[j] = 0x0000;
                    }
                }
            }

            SetAnmFlag(ANMFLAG_ISBOUND, true);
            return success;
        }

        void AnmObjVisNode::Release()
        {
            for (int i = 0; i < MAX_RESOURCES; i++)
            {
                if (mResources[i] != NULL) mResources[i]->Release();
            }

            AnmObjVis::Release();
        }

        void AnmObjVisNode::G3dProc(u32 task, u32 taskArg1, void *taskArg2)
        {
            switch(task)
            {
                case G3DPROC_CHILD_DETACHED:
                    for (int i = 0; i < MAX_RESOURCES; i++)
                    {
                        AnmObjVisRes *res = (AnmObjVisRes *)taskArg2;
                        if (mResources[i] == res)
                        {
                            Detach(i);
                            return;
                        }
                    }
                    break;
                case G3DPROC_DETACH_PARENT:
                    SetParent(NULL);
                    break;
                case G3DPROC_ATTACH_PARENT:
                    SetParent((G3dObj *)taskArg2);
                    break;
            }
        }

        AnmObjVisOR * AnmObjVisOR::Construct(MEMAllocator *allocator, u32 *pSize, ResMdl mdl)
        {
            if (!mdl.IsValid()) return NULL;

            u32 numEntries = mdl.GetResNodeNumEntries();
            u32 r4 = numEntries * 2;
            u32 size = r4 + sizeof(AnmObjVisOR);

            if (pSize != NULL) *pSize = size;
            if (allocator == NULL) return NULL;

            u8 *mem = (u8 *)Alloc(allocator, size);
            if (mem == NULL) return NULL;

            u16 *bindBuffer = (u16 *)(mem + sizeof(AnmObjVisOR));
            return new (mem) AnmObjVisOR(allocator, bindBuffer, numEntries);
        }

        bool AnmObjVisOR::GetResult(u32 idx)
        {
            for (int i = 0; i < MAX_RESOURCES; i++)
            {
                if (mResources[i] != NULL && mResources[i]->TestExistence(idx))
                    if (!mResources[i]->GetResult(idx))
                        return false;
            }

            return true;
        }

        AnmObjVisRes * AnmObjVisRes::Construct(MEMAllocator *allocator, u32 *pSize, ResAnmVis vis, ResMdl mdl)
        {
            if (!vis.IsValid() || !mdl.IsValid()) return NULL;
            
            u32 numEntries = mdl.GetResNodeNumEntries();
            u32 r4 = numEntries * 2;
            u32 size = r4 + sizeof(AnmObjVisRes);

            if (pSize != NULL) *pSize = size;
            if (allocator == NULL) return NULL;

            u8 *mem = (u8 *)Alloc(allocator, size);
            if (mem == NULL) return NULL;

            u16 *bindBuffer = (u16 *)(mem + sizeof(AnmObjVisRes));
            return new (mem) AnmObjVisRes(allocator, vis, bindBuffer, numEntries);
        }

        AnmObjVisRes::AnmObjVisRes(MEMAllocator *allocator, ResAnmVis vis, u16 *bindBuffer, int numBinds)
            : AnmObjVis(allocator, bindBuffer, numBinds),
            FrameCtrl(0.0f, vis.GetNumFrame(), GetAnmPlayPolicy(vis.GetAnmPolicy())),
            mResAnmVis(vis)
        {
        }

        void AnmObjVisRes::SetFrame(f32 frame)
        {
            SetFrm(frame);
            G3dProc(G3DPROC_UPDATEFRAME, 0, NULL);
        }
        
        f32 AnmObjVisRes::GetFrame() const
        {
            return GetFrm();
        }

        void AnmObjVisRes::SetUpdateRate(f32 rate)
        {
            SetRate(rate);
        }

        f32 AnmObjVisRes::GetUpdateRate() const
        {
            return GetRate();
        }

        void AnmObjVisRes::UpdateFrame()
        {
            UpdateFrm();
            G3dProc(G3DPROC_UPDATEFRAME, 0, NULL);
        }

        bool AnmObjVisRes::Bind(ResMdl mdl)
        {
            int numNode = mResAnmVis.GetNumNode();
            bool success = false;
            for (u16 i = 0; i < numNode; i++)
            {
                const ResAnmVisNodeData *nodeAnm = mResAnmVis.GetNodeAnm(i);
                ResName name((char *)ut::AddOffsetToPtr(nodeAnm, nodeAnm->WORD_0x0) - 4);
                ResNode node(mdl.GetResNode(name));
                if (node.IsValid())
                {

                    mBinds[node.GetID()] = i;
                    success = true;
                }
            }

            SetAnmFlag(ANMFLAG_ISBOUND, true);
            return success;
        }

        bool AnmObjVisRes::GetResult(u32 idx)
        {
            u16 bind = mBinds[idx];
            if (bind & 0x4000 || bind & 0x8000) return true;

            return mResAnmVis.GetAnmResult(bind, GetFrm());
        }

        void ApplyVisAnmResult(ResMdl mdl, AnmObjVis *vis)
        {
            u32 numEntries = mdl.GetResNodeNumEntries();
            for (u32 i = 0; i < numEntries; i++)
            {
                if (vis->TestExistence(i))
                {
                    ResNode node = mdl.GetResNode(i);
                    node.SetVisibility(vis->GetResult(i));
                }
            }
        }

        void ApplyVisAnmResult(u8 *byteVec, ResMdl mdl, AnmObjVis *vis)
        {
            u32 numEntries = mdl.GetResNodeNumEntries();
            for (u32 i = 0; i < numEntries; i++)
            {
                if (vis->TestExistence(i))
                {
                    byteVec[i] = vis->GetResult(i);
                }
            }
        }

        namespace
        {
            void UNUSED_FUNC_ORDER_ANMVIS_1(AnmObjVis *vis)
            {
                AnmObjVisRes *visRes = (AnmObjVisRes *)vis;
                AnmObjVisOR *visOr = (AnmObjVisOR *)vis;
                AnmObjVisNode *visNode = (AnmObjVisNode *)vis;

                (void)visRes->IsDerivedFrom(AnmObjVisRes::GetTypeObjStatic());
                (void)vis->IsDerivedFrom(AnmObjVis::GetTypeObjStatic());
                (void)visRes->GetTypeName();
                (void)visRes->GetTypeObj();
                visRes->~AnmObjVisRes();
                (void)visOr->IsDerivedFrom(AnmObjVisOR::GetTypeObjStatic());
                (void)visNode->IsDerivedFrom(AnmObjVisNode::GetTypeObjStatic());
                (void)visOr->GetTypeName();
                (void)visOr->GetTypeObj();
                visOr->~AnmObjVisOR();
                (void)visNode->GetTypeName();
                (void)visNode->GetTypeObj();
                (void)vis->GetTypeName();
                (void)vis->GetTypeObj();
            }
        }
    }
}