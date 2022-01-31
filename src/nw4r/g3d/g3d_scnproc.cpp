#include "g3d_scnproc.h"
#include "g3d_state.h"

namespace nw4r
{
    namespace g3d
    {
        ScnProc * ScnProc::Construct(MEMAllocator *allocator, u32 *pSize,
            DrawProc proc, bool r6, bool r7, u32 r8)
        {
            ScnProc *scnProc = NULL;

            u32 size1 = align4(r8);
            u32 scnProcSize = align4(sizeof(ScnProc));
            u32 size = align4(size1 + scnProcSize);

            if (pSize != NULL) *pSize = size;

            if (allocator != NULL)
            {
                u8 *start = (u8 *)Alloc(allocator, size);
                if (start != NULL)
                {
                    u8 *end = (size1 != 0) ? (start + scnProcSize) : NULL;
                    scnProc = new (start) ScnProc(allocator, proc, end, r6, r7);
                }
            }

            return scnProc;
        }

        void ScnProc::G3dProc(u32 task, u32 taskArg1, void *taskArg2)
        {
            if (!IsG3dProcDisabled(task))
            {
                switch(task)
                {
                    case G3DPROC_GATHER_SCNOBJ:
                        IScnObjGather *gather = (IScnObjGather *)taskArg2;
                        bool b2 = (mFlags & 0x2) ? true : false;
                        bool b1 = (mFlags & 0x1) ? true : false;
                        gather->Add(this, b1, b2);
                        break;
                    case G3DPROC_DRAW_OPA:
                        if (mDrawProc != NULL)
                        {
                            G3DState::Invalidate(0x7FF);
                            mDrawProc(this, true);
                        }
                        break;
                    case G3DPROC_DRAW_XLU:
                        if (mDrawProc != NULL)
                        {
                            G3DState::Invalidate(0x7FF);
                            mDrawProc(this, false);
                        }
                        break;
                    default:
                        DefG3dProcScnLeaf(task, taskArg1, taskArg2);
                }
            }
        }

        namespace
        {
            void UNUSED_FUNC_ORDER_SCNPROC(ScnProc *proc)
            {
                proc->~ScnProc();
                (void)proc->GetTypeObj();
                (void)proc->GetTypeName();
                (void)proc->IsDerivedFrom(proc->GetTypeObjStatic());
            }
        }

        NW4R_G3D_TYPE_OBJ_DEF(ScnProc);
    }
}