#ifdef __DECOMP_NON_MATCHING
#include "g3d_resnode.h"
#include "math_triangular.h"

namespace nw4r
{
    namespace g3d
    {
        void ResNode::PatchChrAnmResult(ChrAnmResult *pAnm) const
        {
            ResNodeData& rNode = mNode.ref();
            
            if (mNode.IsValid())
            {
                u32 newFlags = pAnm->mFlags;
                if (pAnm->mFlags & 0x80)
                {
                    if (rNode.mFlags & 0x8)
                    {
                        newFlags |= 0x18;
                    }
                    else
                    {
                        if (rNode.mFlags & 0x10)
                        {
                            newFlags |= 0x10;
                        }

                        pAnm->VEC3_0x4 = rNode.VEC3_0x20;
                    }
                }

                if (newFlags & 0x100)
                {
                    if (rNode.mFlags & 0x4)
                    {
                        newFlags |= 0x20;
                    }
                    else
                    {
                        math::MTX34RotXYZDeg(&pAnm->mMtx, rNode.VEC3_0x2C.x, rNode.VEC3_0x2C.y, rNode.VEC3_0x2C.z);
                        newFlags &= 0x70;
                    }

                    newFlags |= 0x80000000;
                }

                if (newFlags & 0x200)
                {
                    if (rNode.mFlags & 0x2)
                    {
                        newFlags |= 0x40;
                    }
                    else
                    {
                        newFlags &= 0xE0;

                        pAnm->mMtx[0][3] = rNode.FLOAT_0x38;
                        pAnm->mMtx[1][3] = rNode.FLOAT_0x3C;
                        pAnm->mMtx[2][3] = rNode.FLOAT_0x40;
                    }
                }

                if ((newFlags & 0x20) && (newFlags & 0x40))
                {
                    newFlags |= 0x4;

                    if (newFlags & 0x8)
                    {
                        newFlags |= 0x2;
                    }
                }

                pAnm->mFlags = newFlags & 0x7C0;
            }
        }

        void ResNode::CalcChrAnmResult(ChrAnmResult *pAnm) const
        {
            ResNodeData& rNode = mNode.ref();

            if (mNode.IsValid())
            {
                u32 newFlags = 0;
                if (rNode.mFlags & 0x8)
                {
                    newFlags |= 0x18;

                    pAnm->VEC3_0x4.z = 1.0f;
                    pAnm->VEC3_0x4.y = 1.0f;
                    pAnm->VEC3_0x4.x = 1.0f;
                }
                else
                {
                    if (rNode.mFlags & 0x10)
                    {
                        newFlags |= 0x10;
                    }

                    pAnm->VEC3_0x4 = rNode.VEC3_0x20;
                }

                if (rNode.mFlags & 0x4)
                {
                    PSMTXIdentity(pAnm->mMtx);
                    newFlags |= 0x20;
                }
                else
                {
                    // Can't get these instructions to order properly
                    math::VEC3 stack_0x10;
                    stack_0x10 = rNode.VEC3_0x2C;
                    pAnm->VEC3_0x10 = rNode.VEC3_0x2C;
                    
                    math::MTX34RotXYZDeg(&pAnm->mMtx, rNode.VEC3_0x2C.x, rNode.VEC3_0x2C.y, rNode.VEC3_0x2C.z);
                }

                if (rNode.mFlags & 0x2)
                {
                    newFlags |= 0x40;
                }
                else
                {
                    pAnm->mMtx[0][3] = rNode.FLOAT_0x38;
                    pAnm->mMtx[1][3] = rNode.FLOAT_0x3C;
                    pAnm->mMtx[2][3] = rNode.FLOAT_0x40;
                }

                if (newFlags & 0x20)
                {
                    if (newFlags & 0x40)
                    {
                        newFlags |= 0x4;

                        if (newFlags & 0x8)
                        {
                            newFlags |= 0x2;
                        }
                    }
                }

                newFlags |= 0x80000000;
                newFlags |= 0x1;

                if (rNode.mFlags & 0x20)
                {
                    newFlags |= 0x400;
                }

                if (rNode.mFlags & 0x40)
                {
                    newFlags |= 0x800;
                }

                pAnm->mFlags = newFlags;
            }
        }
    }
}
#else
#error This file has yet to be decompiled accurately. Use "g3d_resnode.s" instead.
#endif