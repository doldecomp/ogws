#ifndef NW4R_EF_MEMORY_MANAGER_TMP_H
#define NW4R_EF_MEMORY_MANAGER_TMP_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/ef_effect.h>
#include <nw4r/ef/ef_effectsystem.h>
#include <nw4r/ef/ef_emitter.h>
#include <nw4r/ef/ef_memorymanager.h>
#include <nw4r/ef/ef_memorymanagerconfig.h>
#include <nw4r/ef/ef_particle.h>
#include <nw4r/ef/ef_particlemanager.h>
#include <nw4r/ut.h>

NW4R_EF_MEMORY_MANAGER_NAMESPACE_OPEN;

template <typename T> class NW4R_EF_MEMORY_MANAGER_TMP_CLASS {
    friend class NW4R_EF_MEMORY_MANAGER_CLASS;

    NW4R_EF_MEMORY_MANAGER_MEMBER_ACCESS;
    T* mHead;                     // at 0x0
    ::nw4r::ut::List mFreeList;   // at 0x4
    ::nw4r::ut::List mLeasedList; // at 0x10
    int mStructSize;              // at 0x1C

public:
    static const u32 OBJECT_ID_BASE = 0x10000;

public:
    NW4R_EF_MEMORY_MANAGER_TMP_CLASS(int aCount, T* aHeap) {
        u16 offset = offsetof(T, mMemoryLink);
        int structSize = sizeof(T);

        ::nw4r::ut::List_Init(&mFreeList, offset);
        ::nw4r::ut::List_Init(&mLeasedList, offset);

        mStructSize = structSize;
        mHead = aHeap;

        for (u32 i = 0; i < aCount; i++) {
            aHeap[i].mObjectID = i;
            ::nw4r::ut::List_Append(&mFreeList, &aHeap[i]);
        }
    }

    virtual void AssignObjectID(void* pObj) {
        static_cast< ::nw4r::ef::LinkedObject*>(pObj)->mObjectID +=
            OBJECT_ID_BASE;
    } // at 0x8

    // Not implemented for Particle
    void GarbageCollection();

    T* Alloc() {
        void* pPtr = ::nw4r::ut::List_GetFirst(&mFreeList);
        if (pPtr == NULL) {
            return NULL;
        }

        AssignObjectID(pPtr);
        ::nw4r::ut::List_Remove(&mFreeList, pPtr);
        ::nw4r::ut::List_Append(&mLeasedList, pPtr);

        return static_cast<T*>(pPtr);
    }

    void Free(T* pObj) {
        ::nw4r::ut::List_Remove(&mLeasedList, pObj);
        ::nw4r::ut::List_Append(&mFreeList, pObj);
    }

    u32 GetNumAllocObject() const {
        return GetNumActiveObject() + GetNumFreeObject();
    }

    u32 GetNumActiveObject() const {
        return ::nw4r::ut::List_GetSize(&mLeasedList);
    }

    u32 GetNumFreeObject() const {
        return ::nw4r::ut::List_GetSize(&mFreeList);
    }
};

// Shorthand for MemoryManagerTmp specializations (also used by MemoryManager)
typedef NW4R_EF_MEMORY_MANAGER_TMP_CLASS<TEffect> TEffectOM;
typedef NW4R_EF_MEMORY_MANAGER_TMP_CLASS<TEmitter> TEmitterOM;
typedef NW4R_EF_MEMORY_MANAGER_TMP_CLASS<TParticleManager> TParticleManagerOM;
typedef NW4R_EF_MEMORY_MANAGER_TMP_CLASS<TParticle> TParticleOM;

template <> inline void TEffectOM::GarbageCollection() {
    void* pPtr = ::nw4r::ut::List_GetFirst(&mLeasedList);

    if (pPtr != NULL) {
        void* pNext = ::nw4r::ut::List_GetNext(&mLeasedList, pPtr);

        while (pPtr != NULL) {
            TEffect* pObj = static_cast<TEffect*>(pPtr);

            if (pObj->GetLifeStatus() ==
                    ::nw4r::ef::ReferencedObject::NW4R_EF_LS_CLOSING &&
                pObj->GetRefCount() == 0) {

                pObj->mManagerES->mActivityList[pObj->mGroupID].ToFree(pObj);
                ::nw4r::ut::List_Remove(&mLeasedList, pObj);
                ::nw4r::ut::List_Append(&mFreeList, pObj);
            }

            pPtr = pNext;
            pNext = ::nw4r::ut::List_GetNext(&mLeasedList, pPtr);
        }
    }
}

template <> inline void TEmitterOM::GarbageCollection() {
    void* pPtr = ::nw4r::ut::List_GetFirst(&mLeasedList);

    if (pPtr != NULL) {
        void* pNext = ::nw4r::ut::List_GetNext(&mLeasedList, pPtr);

        while (pPtr != NULL) {
            TEmitter* pObj = static_cast<TEmitter*>(pPtr);

            if (pObj->GetLifeStatus() ==
                    ::nw4r::ef::ReferencedObject::NW4R_EF_LS_CLOSING &&
                pObj->GetRefCount() == 0) {

                pObj->mManagerEF->mActivityList.ToFree(pObj);
                ::nw4r::ut::List_Remove(&mLeasedList, pObj);
                ::nw4r::ut::List_Append(&mFreeList, pObj);
            }

            pPtr = pNext;
            pNext = ::nw4r::ut::List_GetNext(&mLeasedList, pPtr);
        }
    }
}

template <> inline void TParticleManagerOM::GarbageCollection() {
    void* pPtr = ::nw4r::ut::List_GetFirst(&mLeasedList);

    if (pPtr != NULL) {
        void* pNext = ::nw4r::ut::List_GetNext(&mLeasedList, pPtr);

        while (pPtr != NULL) {
            TParticleManager* pObj = static_cast<TParticleManager*>(pPtr);

            if (pObj->GetLifeStatus() ==
                    ::nw4r::ef::ReferencedObject::NW4R_EF_LS_CLOSING &&
                pObj->GetRefCount() == 0) {

                pObj->mManagerEM->mActivityList.ToFree(pObj);
                ::nw4r::ut::List_Remove(&mLeasedList, pObj);
                ::nw4r::ut::List_Append(&mFreeList, pObj);
            }

            pPtr = pNext;
            pNext = ::nw4r::ut::List_GetNext(&mLeasedList, pPtr);
        }
    }
}

#if !defined(NONMATCHING)
template <> inline void TParticleOM::GarbageCollection() {}
#endif

NW4R_EF_MEMORY_MANAGER_NAMESPACE_CLOSE;

#endif
