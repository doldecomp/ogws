#include "g3d_scnobj.h"
#include "math_types.h"
#include "math_geometry.h"
#include <algorithm>

namespace nw4r
{
    namespace g3d
    {
        using namespace math;

        FRUSTUM *gpCullingFrustum;

        void ScnObj::CalcWorldMtx(const MTX34 *mtx, u32 *flags)
        {
            if (flags && (*flags & 1))
            {
                *flags &= ~1;
                return;
            }

            if (mtx)
            {
                if (TestScnObjFlag(FLAG_80000000))
                {
                    MTX34Copy(&mMatrices[MTX_TYPE_WORLD], mtx);
                }
                else
                {
                    MTX34Mult(&mMatrices[MTX_TYPE_WORLD], mtx, &mMatrices[MTX_TYPE_0]);
                }
            }
            else
            {
                MTX34Copy(&mMatrices[MTX_TYPE_WORLD], &mMatrices[MTX_TYPE_0]);
            }

            if (TestScnObjFlag(FLAG_10000000))
            {
                mBounds[BOUNDING_1].Set(&mBounds[BOUNDING_0], &mMatrices[MTX_TYPE_WORLD]);
            }
        }

        void ScnObj::CalcViewMtx(const MTX34 *mtx)
        {
            MTX34Mult(&mMatrices[MTX_TYPE_VIEW], mtx, &mMatrices[MTX_TYPE_WORLD]);
        }

        ScnObj::ScnObj(MEMAllocator *allocator) : G3dObj(allocator, NULL),
            mFlags(0), mPriorityDrawOpa(128), mPriorityDrawXlu(128), BYTE_0xD2(0),
            BYTE_0xD3(0), mCallback(NULL), mTiming(0), BYTE_0xD9(0), mExecOp(0)
        {
            SetScnObjFlag(FLAG_80000000, 1);
            MTX34Identity(&mMatrices[MTX_TYPE_0]);
            MTX34Identity(&mMatrices[MTX_TYPE_WORLD]);
            MTX34Identity(&mMatrices[MTX_TYPE_VIEW]);

            mBounds[BOUNDING_0].min = VEC3(0.0f, 0.0f, 0.0f);
            mBounds[BOUNDING_0].max = VEC3(0.0f, 0.0f, 0.0f);
            mBounds[BOUNDING_1].min = VEC3(0.0f, 0.0f, 0.0f);
            mBounds[BOUNDING_1].max = VEC3(0.0f, 0.0f, 0.0f);
        }

        ScnObj::~ScnObj()
        {
            if (mCallback != NULL)
            {
                switch(BYTE_0xD9)
                {
                    case 1:
                        delete mCallback;
                }
            }
        }

        bool ScnObj::SetScnObjOption(u32 option, u32 set)
        {
            switch(option)
            {
                case 1:
                    SetScnObjFlag(FLAG_10, set);
                    break;
                case 2:
                    SetScnObjFlag(FLAG_1, set);
                    break;
                case 3:
                    SetScnObjFlag(FLAG_2, set);
                    break;
                case 4:
                    SetScnObjFlag(FLAG_4, set);
                    break;
                case 5:
                    SetScnObjFlag(FLAG_8, set);
                    break;
                case 6:
                    SetScnObjFlag(FLAG_20, set);
                    break;
                case 7:
                    SetScnObjFlag(FLAG_40, set);
                    break;
                case 8:
                    SetScnObjFlag(FLAG_80, set);
                    break;
                case 9:
                    SetScnObjFlag(FLAG_10000000, set);
                    break;
                default:
                    return false;
            }

            return true;
        }

        bool ScnObj::GetScnObjOption(u32 option, u32 *pSet) const
        {
            if (pSet == NULL) return false;
            
            switch(option)
            {
                case 1:
                    *pSet = TestScnObjFlag(FLAG_10);
                    break;
                case 2:
                    *pSet = TestScnObjFlag(FLAG_1);
                    break;
                case 3:
                    *pSet = TestScnObjFlag(FLAG_2);
                    break;
                case 4:
                    *pSet = TestScnObjFlag(FLAG_4);
                    break;
                case 5:
                    *pSet = TestScnObjFlag(FLAG_8);
                    break;
                case 6:
                    *pSet = TestScnObjFlag(FLAG_20);
                    break;
                case 7:
                    *pSet = TestScnObjFlag(FLAG_40);
                    break;
                case 8:
                    *pSet = TestScnObjFlag(FLAG_80);
                    break;
                case 9:
                    *pSet = TestScnObjFlag(FLAG_10000000);
                    break;
                default:
                    return false;
            }

            return true;
        }

        bool ScnObj::SetMtx(ScnObjMtxType type, const MTX34 *pMtx)
        {
            if ((u32)type < MTX_TYPE_MAX)
            {
                if (pMtx != NULL)
                {
                    if (type == MTX_TYPE_0)
                    {
                        SetScnObjFlag(FLAG_80000000, 0);
                    }

                    MTX34Copy(&mMatrices[type], pMtx);
                }
                else
                {
                    if (type == MTX_TYPE_0)
                    {
                        SetScnObjFlag(FLAG_80000000, 1);
                    }

                    MTX34Identity(&mMatrices[type]);
                }

                return true;
            }

            return false;
        }

        bool ScnObj::GetMtx(ScnObjMtxType type, MTX34 *pMtx) const
        {
            if (pMtx != NULL && (u32)type < MTX_TYPE_MAX)
            {
                MTX34Copy(pMtx, &mMatrices[type]);
                return true;
            }

            return false;
        }

        f32 ScnObj::GetValueForSortOpa() const
        {
            return -mMatrices[MTX_TYPE_VIEW][2][3];
        }

        f32 ScnObj::GetValueForSortXlu() const
        {
            return mMatrices[MTX_TYPE_VIEW][2][3];
        }

        void ScnObj::SetPriorityDrawOpa(int prio)
        {
            if (prio < 0)
            {
                prio = 0;
            }
            else if (prio > 255)
            {
                prio = 255;
            }

            mPriorityDrawOpa = prio;
        }

        void ScnObj::SetPriorityDrawXlu(int prio)
        {
            if (prio < 0)
            {
                prio = 0;
            }
            else if (prio > 255)
            {
                prio = 255;
            }

            mPriorityDrawXlu = prio;
        }

        void ScnObj::EnableScnObjCallbackTiming(Timing timing)
        {
            if (timing & TIMING_1)
            {
                mTiming |= TIMING_1;
            }

            if (timing & TIMING_2)
            {
                mTiming |= TIMING_2;
            }

            if (timing & TIMING_4)
            {
                mTiming |= TIMING_4;
            }
        }

        void ScnObj::EnableScnObjCallbackExecOp(ExecOp op)
        {
            mExecOp |= (op & 0xFFFF);
        }

        bool ScnObj::SetBoundingVolume(ScnObjBoundingVolumeType type, const AABB *pAABB)
        {
            if (pAABB != NULL)
            {
                if (type < BOUNDING_MAX)
                {
                    mBounds[type] = *pAABB;
                    return SetScnObjOption(9, 1);
                }
                
                return 0;
            }

            return SetScnObjOption(9, 0);
        }

        bool ScnObj::GetBoundingVolume(ScnObjBoundingVolumeType type, AABB *pAABB) const
        {
            if (pAABB != NULL)
            {
                if (type < BOUNDING_MAX)
                {
                    *pAABB = mBounds[type];
                    return true;
                }

                return false;
            }

            return false;
        }

        ScnObj::ForEachResult ScnLeaf::ForEach(ForEachAction action, void *r5, bool b)
        {
            ForEachResult result = (*action)(this, r5);
            return (result != FOREACH_RESULT_1) ? FOREACH_RESULT_0 : FOREACH_RESULT_1;
        }

        bool ScnLeaf::SetScnObjOption(u32 option, u32 set)
        {
            switch(option)
            {
                case 0x10001:
                    SetScnObjFlag(FLAG_60, set);
                    break;
                default:
                    return ScnObj::SetScnObjOption(option, set);
            }            

            return true;
        }

        bool ScnLeaf::GetScnObjOption(u32 option, u32 *pSet) const
        {
            if (pSet == NULL) return false;

            switch(option)
            {
                case 0x10001:
                    *pSet = TestScnObjFlag(FLAG_60);
                    break;
                default:
                    return ScnObj::GetScnObjOption(option, pSet);
            }

            return true;
        }

        void ScnLeaf::CalcWorldMtx(const MTX34 *mtx, u32 *flags)
        {
            if (flags && (*flags & 1))
            {
                *flags &= ~1;
            }
            else
            {
                ScnObj::CalcWorldMtx(mtx, flags);
                MTX34Scale(&mMatrices[MTX_TYPE_WORLD], &mMatrices[MTX_TYPE_WORLD], &mScale);

                if (TestScnObjFlag(FLAG_10000000))
                {
                    mBounds[BOUNDING_1].Set(&mBounds[BOUNDING_0], &mMatrices[MTX_TYPE_WORLD]);
                }
            }
        }

        ScnLeaf::ScaleProperty ScnLeaf::GetScaleProperty() const
        {
            if (mScale.x == mScale.y)
            {
                if (mScale.y == mScale.z)
                {
                    if (mScale.x == 1.0f)
                    {
                        return SCALE_PROPERTY_0;
                    }

                    return SCALE_PROPERTY_1;
                }
            }

            return SCALE_PROPERTY_2;
        }

        void ScnLeaf::DefG3dProcScnLeaf(u32 task, u32 taskArg1, void *taskArg2)
        {
            switch(task)
            {
                case G3DPROC_CALC_WORLD:
                    CheckCallback_CALC_WORLD(TIMING_1, taskArg1, taskArg2);
                    CalcWorldMtx((const MTX34 *)taskArg2, &taskArg1);
                    CheckCallback_CALC_WORLD(TIMING_2, taskArg1, taskArg2);
                    CheckCallback_CALC_WORLD(TIMING_4, taskArg1, taskArg2);
                    break;
                case G3DPROC_CALC_MAT:
                    CheckCallback_CALC_MAT(TIMING_1, taskArg1, taskArg2);
                    CheckCallback_CALC_MAT(TIMING_4, taskArg1, taskArg2);
                    break;
                case G3DPROC_CALC_VIEW:
                    CheckCallback_CALC_VIEW(TIMING_1, taskArg1, taskArg2);
                    CalcViewMtx((const MTX34 *)taskArg2);
                    CheckCallback_CALC_VIEW(TIMING_2, taskArg1, taskArg2);
                    CheckCallback_CALC_VIEW(TIMING_4, taskArg1, taskArg2);
                    break;
                case G3DPROC_DETACH_PARENT:
                    SetParent(NULL);
                    break;
                case G3DPROC_ATTACH_PARENT:
                    SetParent((G3dObj *)taskArg2);
                    break;
                case G3DPROC_GATHER_SCNOBJ:
                case G3DPROC_DRAW_OPA:
                case G3DPROC_DRAW_XLU:
                case G3DPROC_UPDATEFRAME:
                case G3DPROC_CHILD_DETACHED:
                case G3DPROC_0x10004:
                    break;
            }
        }

        ScnObj::ForEachResult ScnGroup::ForEach(ForEachAction action, void *arg2, bool b)
        {
            int ret;

            if (b)
            {
                for (int i = 0; i < Size(); i++)
                {
                    ret = mObjects[i]->ForEach(action, arg2, false);
                    if (ret == FOREACH_RESULT_1) return FOREACH_RESULT_1;
                }

                ret = action(this, arg2);
                return (ret == FOREACH_RESULT_1) ? FOREACH_RESULT_1 : FOREACH_RESULT_0;
            }
            else
            {
                ret = action(this, arg2);
                if (ret == FOREACH_RESULT_0)
                {
                    for (int i = 0; i < Size(); i++)
                    {
                        ret = mObjects[i]->ForEach(action, arg2, false);
                        if (ret == FOREACH_RESULT_1) return FOREACH_RESULT_1;
                    }

                    return FOREACH_RESULT_0;
                }

                return (ret == FOREACH_RESULT_1) ? FOREACH_RESULT_1 : FOREACH_RESULT_0;
            }
        }

        void ScnGroup::ScnGroup_G3DPROC_GATHER_SCNOBJ(u32 arg1, IScnObjGather *gather)
        {
            UNKWORD ret = gather->Add(this,
                !TestScnObjFlag(FLAG_20000000), !TestScnObjFlag(FLAG_40000000));

            if (ret == 0)
            {
                for (int i = 0; i < mSize; i++)
                {
                    mObjects[i]->G3dProc(G3DPROC_GATHER_SCNOBJ, arg1, gather);
                }
            }
            else if (ret == 1)
            {
                FRUSTUM *backup = gpCullingFrustum;
                gpCullingFrustum = NULL;

                for (int i = 0; i < mSize; i++)
                {
                    mObjects[i]->G3dProc(G3DPROC_GATHER_SCNOBJ, arg1, gather);
                }

                gpCullingFrustum = backup;
            }
        }

        void ScnGroup::ScnGroup_G3DPROC_CALC_WORLD(u32 taskArg1, const MTX34 *taskArg2)
        {
            CheckCallback_CALC_WORLD(TIMING_1, taskArg1, (void *)taskArg2);
            CalcWorldMtx(taskArg2, &taskArg1);
            CheckCallback_CALC_WORLD(TIMING_2, taskArg1, (void *)taskArg2);

            const MTX34 *mtxPtr = GetMtxPtr(MTX_TYPE_WORLD);
            for (int i = 0; i < mSize; i++)
            {
                mObjects[i]->G3dProc(G3DPROC_CALC_WORLD, taskArg1, (void *)mtxPtr);
            }

            CheckCallback_CALC_WORLD(TIMING_4, taskArg1, (void *)taskArg2);
        }

        void ScnGroup::ScnGroup_G3DPROC_CALC_MAT(u32 taskArg1, void *taskArg2)
        {
            CheckCallback_CALC_MAT(TIMING_1, taskArg1, taskArg2);
            for (int i = 0; i < mSize; i++)
            {
                mObjects[i]->G3dProc(G3DPROC_CALC_MAT, taskArg1, taskArg2);
            }

            CheckCallback_CALC_MAT(TIMING_4, taskArg1, taskArg2);
        }

        void ScnGroup::ScnGroup_G3DPROC_CALC_VIEW(u32 taskArg1, const MTX34 *taskArg2)
        {
            CheckCallback_CALC_VIEW(TIMING_1, taskArg1, (void *)taskArg2);
            CalcViewMtx(taskArg2);
            CheckCallback_CALC_VIEW(TIMING_2, taskArg1, (void *)taskArg2);

            for (int i = 0; i < mSize; i++)
            {
                mObjects[i]->G3dProc(G3DPROC_CALC_VIEW, taskArg1, (void *)taskArg2);
            }

            CheckCallback_CALC_VIEW(TIMING_4, taskArg1, (void *)taskArg2);
        }

        void ScnGroup::G3dProc(u32 task, u32 taskArg1, void *taskArg2)
        {
            if (!IsG3dProcDisabled(task))
                DefG3dProcScnGroup(task, taskArg1, taskArg2);
        }

        void ScnGroup::DefG3dProcScnGroup(u32 task, u32 taskArg1, void *taskArg2)
        {
            switch(task)
            {
                case G3DPROC_GATHER_SCNOBJ:
                    ScnGroup_G3DPROC_GATHER_SCNOBJ(taskArg1, (IScnObjGather *)taskArg2);
                    break;
                case G3DPROC_CALC_WORLD:
                    ScnGroup_G3DPROC_CALC_WORLD(taskArg1, (const MTX34 *)taskArg2);
                    break;
                case G3DPROC_CALC_MAT:
                    ScnGroup_G3DPROC_CALC_MAT(taskArg1, taskArg2);
                    break;
                case G3DPROC_CALC_VIEW:
                    ScnGroup_G3DPROC_CALC_VIEW(taskArg1, (const MTX34 *)taskArg2);
                    break;
                case G3DPROC_DRAW_OPA:
                case G3DPROC_DRAW_XLU:
                    return;
                    break;
                case G3DPROC_CHILD_DETACHED:
                    Remove((ScnObj *)taskArg2);
                    break;
                case G3DPROC_DETACH_PARENT:
                    SetParent(NULL);
                    break;
                case G3DPROC_ATTACH_PARENT:
                    SetParent((G3dObj *)taskArg2);
                    break;
                case G3DPROC_UPDATEFRAME:
                case G3DPROC_0x10004:
                default:
                    for (int i = 0; i < mSize; i++)
                    {
                        mObjects[i]->G3dProc(task, taskArg1, taskArg2);
                    }
            }
        }

        bool ScnGroup::Insert(u32 idx, ScnObj *obj)
        {
            if (idx <= mSize && mSize < mCapacity
                && obj != NULL && obj->GetParent() == NULL)
            {
                ScnObj **pObj = std::find(&mObjects[0], &mObjects[mSize], obj);
                if (pObj == &mObjects[mSize]) {
                    for (u32 i = mSize; i > idx; i--)
                    {
                        mObjects[i] = mObjects[i - 1];
                    }

                    mObjects[idx] = obj;
                    obj->G3dProc(G3DPROC_ATTACH_PARENT, 0, this);
                    
                    mSize++;
                    return true;
                }
            }

            return false;
        }

        ScnObj * ScnGroup::Remove(u32 idx)
        {
            if (idx < mSize)
            {
                ScnObj *obj = mObjects[idx];
                obj->G3dProc(G3DPROC_DETACH_PARENT, 0, this);

                for (; idx < mSize - 1; idx++)
                {
                    mObjects[idx] = mObjects[idx + 1];
                }

                mSize--;
                return obj;
            }

            return NULL;
        }

        bool ScnGroup::Remove(ScnObj *obj)
        {
            ScnObj **pObj = std::find(&mObjects[0], &mObjects[mSize], obj);
            if (pObj != &mObjects[mSize])
            {
                u32 dist = std::distance(&mObjects[0], pObj);
                return Remove(dist) != NULL;
            }

            return false;
        }

        ScnGroup::ScnGroup(MEMAllocator *pAllocator, ScnObj **pObjs, u32 cap) : ScnObj(pAllocator),
            mObjects(pObjs), mCapacity(cap), mSize(0)
        {
            SetScnObjFlag(FLAG_20000000, 1);
            SetScnObjFlag(FLAG_40000000, 1);
        }

        ScnGroup::~ScnGroup()
        {
            Clear();
        }

        namespace
        {
            // Force order of weak functions
            void UNUSED_FUNC_ORDER_SCNOBJ(ScnObj *obj)
            {
                ScnGroup *group = (ScnGroup *)obj;

                (void)obj->GetTypeObj();
                (void)obj->GetTypeName();
                (void)group->GetTypeObj();
                (void)group->GetTypeName();
                (void)obj->IsDerivedFrom(obj->GetTypeObjStatic());
                (void)group->IsDerivedFrom(group->GetTypeObjStatic());
            }
        }

        NW4R_G3D_TYPE_OBJ_DEF(ScnObj);
        NW4R_G3D_TYPE_OBJ_DEF(ScnLeaf);
        NW4R_G3D_TYPE_OBJ_DEF(ScnGroup);
    }
}