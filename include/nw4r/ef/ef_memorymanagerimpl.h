#ifndef NW4R_EF_MEMORY_MANAGER_IMPL_H
#define NW4R_EF_MEMORY_MANAGER_IMPL_H
#include <nw4r/types_nw4r.h>

#include <nw4r/ef/ef_effect.h>
#include <nw4r/ef/ef_effectsystem.h>
#include <nw4r/ef/ef_emitter.h>
#include <nw4r/ef/ef_memorymanager.h>
#include <nw4r/ef/ef_memorymanagerconfig.h>
#include <nw4r/ef/ef_memorymanagertmp.h>
#include <nw4r/ef/ef_particle.h>
#include <nw4r/ef/ef_particlemanager.h>
#include <nw4r/ut.h>

NW4R_EF_MEMORY_MANAGER_NAMESPACE_OPEN;

class NW4R_EF_MEMORY_MANAGER_CLASS : public ::nw4r::ef::MemoryManagerBase {
    NW4R_EF_MEMORY_MANAGER_MEMBER_ACCESS;
    struct MemInfo {
        MemInfo* prev;      // at 0x0
        MemInfo* next;      // at 0x4
        MemInfo* chainPrev; // at 0x8
        MemInfo* chainNext; // at 0xC
        u32 size;           // at 0x10
        bool active;        // at 0x14
        u8 PADDING_0x15[3]; // at 0x15
    };

    NW4R_EF_MEMORY_MANAGER_MEMBER_ACCESS;
    int mLeastEffect;     // at 0x4
    int mMaxEffect;       // at 0x8
    TEffectOM* mEffectOM; // at 0xC

    int mLeastEmitter;      // at 0x10
    int mMaxEmitter;        // at 0x14
    TEmitterOM* mEmitterOM; // at 0x18

    int mLeastParticleManager;              // at 0x1C
    int mMaxParticleManager;                // at 0x20
    TParticleManagerOM* mParticleManagerOM; // at 0x24

    int mLeastParticle;       // at 0x28
    int mMaxParticle;         // at 0x2C
    TParticleOM* mParticleOM; // at 0x30

    void* mHeapStartAddr; // at 0x34
    void* mHeapEndAddr;   // at 0x38

    MemInfo* mActiveMem;   // at 0x3C
    MemInfo* mFreeMem;     // at 0x40
    MemInfo* mFreeMemTail; // at 0x44
    MemInfo* mAllChain;    // at 0x48

public:
    static u32 CalcMemorySize(u16 maxEffect, u16 maxEmitter,
                              u16 maxParticleManager, u16 maxParticle,
                              u32 maxGroupID) {
        // clang-format off
        return ROUND_UP(sizeof(MemInfo), 32) + ::nw4r::ut::RoundUp<u32>(maxEffect * sizeof(TEffect) + 32, 32) +
               ROUND_UP(sizeof(MemInfo), 32) + ::nw4r::ut::RoundUp<u32>(maxEmitter * sizeof(TEmitter) + 32, 32) +
               ROUND_UP(sizeof(MemInfo), 32) + ::nw4r::ut::RoundUp<u32>(maxParticleManager * sizeof(TParticleManager) + 32, 32) +
               ROUND_UP(sizeof(MemInfo), 32) + ::nw4r::ut::RoundUp<u32>(maxParticle * sizeof(TParticle) + 32, 32) +
               ROUND_UP(sizeof(MemInfo), 32) + ::nw4r::ut::RoundUp<u32>(maxGroupID * sizeof(::nw4r::ef::ActivityList) + 32, 32) +
               ROUND_UP(sizeof(MemInfo), 32) + ROUND_UP(sizeof(TEffectOM), 32) +
               ROUND_UP(sizeof(MemInfo), 32) + ROUND_UP(sizeof(TEmitterOM), 32) +
               ROUND_UP(sizeof(MemInfo), 32) + ROUND_UP(sizeof(TParticleManagerOM), 32) +
               ROUND_UP(sizeof(MemInfo), 32) + ROUND_UP(sizeof(TParticleOM), 32);
        // clang-format on
    }

    NW4R_EF_MEMORY_MANAGER_CLASS(void* pStartAddr, u32 size, int maxEffect,
                                 int maxEmitter, int maxParticleManager,
                                 int maxParticle) {

        u32 headerSize = ::nw4r::ut::RoundUp(sizeof(MemInfo), 32);

        mLeastEffect = 0;
        mLeastEmitter = 0;
        mLeastParticleManager = 0;
        mLeastParticle = 0;

        mMaxEffect = 0;
        mMaxEmitter = 0;
        mMaxParticleManager = 0;
        mMaxParticle = 0;

        mEffectOM = NULL;
        mEmitterOM = NULL;
        mParticleManagerOM = NULL;
        mParticleOM = NULL;

        mActiveMem = NULL;
        mFreeMem = NULL;
        mFreeMemTail = NULL;
        mAllChain = NULL;

        mHeapEndAddr = static_cast<u8*>(pStartAddr) + size;
        mHeapStartAddr = reinterpret_cast<u8*>(
            ::nw4r::ut::RoundUp(reinterpret_cast<u32>(pStartAddr), 32));

        mLeastEffect = maxEffect;
        mLeastEmitter = maxEmitter;
        mLeastParticleManager = maxParticleManager;
        mLeastParticle = maxParticle;

        mMaxEffect = mLeastEffect;
        mMaxEmitter = mLeastEmitter;
        mMaxParticleManager = mLeastParticleManager;
        mMaxParticle = mLeastParticle;

        mFreeMem = static_cast<MemInfo*>(mHeapStartAddr);
        mFreeMem->prev = NULL;
        mFreeMem->next = NULL;
        mFreeMem->chainPrev = NULL;
        mFreeMem->chainNext = NULL;
        mFreeMem->active = false;
        mFreeMem->size = static_cast<u8*>(mHeapEndAddr) -
                         static_cast<u8*>(mHeapStartAddr) - headerSize;

        mAllChain = mFreeMem;
        mActiveMem = NULL;

        // clang-format off
        int numEffects = mLeastEffect;
        TEffect* pEffects = NULL;

        if (numEffects > 0) {
            pEffects = new (AllocHeap(sizeof(TEffect) * numEffects + 32)) TEffect[numEffects];
        }

        mEffectOM = new (AllocHeap(sizeof(TEffectOM)))
            TEffectOM(mLeastEffect, pEffects);

        int numEmitters = mLeastEmitter;
        TEmitter* pEmitters = NULL;

        if (numEmitters > 0) {
            pEmitters = new (AllocHeap(sizeof(TEmitter) * numEmitters + 32)) TEmitter[numEmitters];
        }

        mEmitterOM = new (AllocHeap(sizeof(TEmitterOM)))
            TEmitterOM(mLeastEmitter, pEmitters);

        int numParticleManagers = mLeastParticleManager;
        TParticleManager* pParticleManagers = NULL;

        if (numParticleManagers > 0) {
            pParticleManagers = new (AllocHeap(sizeof(TParticleManager) * numParticleManagers + 32)) TParticleManager[numParticleManagers];
        }

        mParticleManagerOM = new (AllocHeap(sizeof(TParticleManagerOM)))
            TParticleManagerOM(mLeastParticleManager, pParticleManagers);

        int numParticles = mLeastParticle;
        TParticle* pParticles = NULL;

        if (numParticles > 0) {
            pParticles = new (AllocHeap(sizeof(TParticle) * numParticles + 32)) TParticle[numParticles];
        }

        mParticleOM = new (AllocHeap(sizeof(TParticleOM)))
            TParticleOM(mLeastParticle, pParticles);
        // clang-format on
    }

    virtual ~NW4R_EF_MEMORY_MANAGER_CLASS() {} // at 0x8

    virtual void GarbageCollection() {
        void* pPtr =
            ::nw4r::ut::List_GetFirst(&mParticleManagerOM->mLeasedList);

        while (pPtr != NULL) {
            void* pNext = ::nw4r::ut::List_GetNext(
                &mParticleManagerOM->mLeasedList, pPtr);

            TParticleManager* mMgr = static_cast<TParticleManager*>(pPtr);

            TParticle* pPtcl;
            TParticle* pNextPtcl;

            for (pPtcl = static_cast<TParticle*>(
                     mMgr->mActivityList.mClosingList.headObject);
                 pPtcl != NULL; pPtcl = pNextPtcl) {

                // clang-format off
                pNextPtcl = static_cast<TParticle*>(
                    NW4R_UT_LIST_GET_LINK(mMgr->mActivityList.mClosingList, pPtcl)->nextObject);
                // clang-format on

                pPtcl->mParticleManager->ParticleToFree(pPtcl);
                ::nw4r::ut::List_Remove(&mParticleOM->mLeasedList, pPtcl);
                ::nw4r::ut::List_Append(&mParticleOM->mFreeList, pPtcl);
            }

            pPtr = static_cast<TParticleManager*>(pNext);
        }

        if (mParticleManagerOM != NULL) {
            mParticleManagerOM->GarbageCollection();
        }

        if (mEmitterOM != NULL) {
            mEmitterOM->GarbageCollection();
        }

        if (mEffectOM != NULL) {
            mEffectOM->GarbageCollection();
        }
    } // at 0xC

    virtual TEffect* AllocEffect() {
        if (mEffectOM == NULL) {
            return NULL;
        } else {
            return mEffectOM->Alloc();
        }
    } // at 0x10

    virtual void FreeEffect(void* pObj) {
        if (mEffectOM != NULL) {
            mEffectOM->Free(static_cast<TEffect*>(pObj));
        }
    } // at 0x14

    virtual u32 GetNumAllocEffect() const {
        if (mEffectOM == NULL) {
            return 0;
        } else {
            return mEffectOM->GetNumAllocObject();
        }
    } // at 0x18

    virtual u32 GetNumActiveEffect() const {
        if (mEffectOM == NULL) {
            return 0;
        } else {
            return mEffectOM->GetNumActiveObject();
        }
    } // at 0x1C

    virtual u32 GetNumFreeEffect() const {
        if (mEffectOM == NULL) {
            return 0;
        } else {
            return mEffectOM->GetNumFreeObject();
        }
    } // at 0x20

    virtual TEmitter* AllocEmitter() {
        if (mEmitterOM == NULL) {
            return NULL;
        } else {
            return mEmitterOM->Alloc();
        }
    } // at 0x24

    virtual void FreeEmitter(void* pObj) {
        if (mEmitterOM != NULL) {
            mEmitterOM->Free(static_cast<TEmitter*>(pObj));
        }
    } // at 0x28

    virtual u32 GetNumAllocEmitter() const {
        if (mEmitterOM == NULL) {
            return 0;
        } else {
            return mEmitterOM->GetNumAllocObject();
        }
    } // at 0x2C

    virtual u32 GetNumActiveEmitter() const {
        if (mEmitterOM == NULL) {
            return 0;
        } else {
            return mEmitterOM->GetNumActiveObject();
        }
    } // at 0x30

    virtual u32 GetNumFreeEmitter() const {
        if (mEmitterOM == NULL) {
            return 0;
        } else {
            return mEmitterOM->GetNumFreeObject();
        }
    } // at 0x34

    virtual TParticleManager* AllocParticleManager() {
        if (mParticleManagerOM == NULL) {
            return NULL;
        } else {
            return mParticleManagerOM->Alloc();
        }
    } // at 0x38

    virtual void FreeParticleManager(void* pObj) {
        if (mParticleManagerOM != NULL) {
            mParticleManagerOM->Free(static_cast<TParticleManager*>(pObj));
        }
    } // at 0x3C

    virtual u32 GetNumAllocParticleManager() const {
        if (mParticleManagerOM == NULL) {
            return 0;
        } else {
            return mParticleManagerOM->GetNumAllocObject();
        }
    } // at 0x40

    virtual u32 GetNumActiveParticleManager() const {
        if (mParticleManagerOM == NULL) {
            return 0;
        } else {
            return mParticleManagerOM->GetNumActiveObject();
        }
    } // at 0x44

    virtual u32 GetNumFreeParticleManager() const {
        if (mParticleManagerOM == NULL) {
            return 0;
        } else {
            return mParticleManagerOM->GetNumFreeObject();
        }
    } // at 0x48

    virtual TParticle* AllocParticle() {
        if (mParticleOM == NULL) {
            return NULL;
        } else {
            return mParticleOM->Alloc();
        }
    } // at 0x4C

    virtual void FreeParticle(void* pObj) {
        if (mParticleOM != NULL) {
            mParticleOM->Free(static_cast<TParticle*>(pObj));
        }
    } // at 0x50

    virtual u32 GetNumAllocParticle() const {
        if (mParticleOM == NULL) {
            return 0;
        } else {
            return mParticleOM->GetNumAllocObject();
        }
    } // at 0x54

    virtual u32 GetNumActiveParticle() const {
        if (mParticleOM == NULL) {
            return 0;
        } else {
            return mParticleOM->GetNumActiveObject();
        }
    } // at 0x58

    virtual u32 GetNumFreeParticle() const {
        if (mParticleOM == NULL) {
            return 0;
        } else {
            return mParticleOM->GetNumFreeObject();
        }
    } // at 0x5C

    virtual void* AllocHeap(u32 size) {
        u32 headerSize = ::nw4r::ut::RoundUp(sizeof(MemInfo), 32);
        size = ::nw4r::ut::RoundUp(size, 32);

        for (MemInfo* pIt = mFreeMem; pIt != NULL; pIt = pIt->next) {
            if (pIt->size < size) {
                continue;
            }

            if (pIt->size < size + headerSize + 32) {
                if (pIt->prev != NULL) {
                    pIt->prev->next = pIt->next;
                } else {
                    mFreeMem = pIt->next;
                }

                if (pIt->next != NULL) {
                    pIt->next->prev = pIt->prev;
                }

                if (mActiveMem != NULL) {
                    mActiveMem->prev = pIt;
                }

                pIt->next = mActiveMem;
                pIt->prev = NULL;
                pIt->active = true;
                mActiveMem = pIt;
            } else {
                MemInfo* pNewFree = reinterpret_cast<MemInfo*>(
                    (reinterpret_cast<u8*>(pIt) + headerSize + size));

                pNewFree->prev = pIt->prev;
                pNewFree->next = pIt->next;
                pNewFree->size = pIt->size - size - headerSize;
                pNewFree->active = false;
                pNewFree->chainNext = pIt->chainNext;

                if (pIt->chainNext != NULL) {
                    pIt->chainNext->chainPrev = pNewFree;
                }

                pNewFree->chainPrev = pIt;
                pIt->chainNext = pNewFree;

                if (pIt->prev != NULL) {
                    pIt->prev->next = pNewFree;
                } else {
                    mFreeMem = pNewFree;
                }

                if (pIt->next != NULL) {
                    pNewFree->next->prev = pNewFree;
                }

                if (mActiveMem != NULL) {
                    mActiveMem->prev = pIt;
                }

                pIt->next = mActiveMem;
                pIt->prev = NULL;
                pIt->size = size;
                pIt->active = true;
                mActiveMem = pIt;
            }

            return reinterpret_cast<u8*>(pIt) + headerSize;
        }

        return NULL;
    } // at 0x60

    virtual void FreeHeap(void* pPtr) {
        u32 headerSize = ::nw4r::ut::RoundUp(sizeof(MemInfo), 32);

        MemInfo* pInfo =
            reinterpret_cast<MemInfo*>(static_cast<u8*>(pPtr) - headerSize);

        if (pInfo->prev != NULL) {
            pInfo->prev->next = pInfo->next;
        } else {
            mActiveMem = pInfo->next;
        }

        if (pInfo->next != NULL) {
            pInfo->next->prev = pInfo->prev;
        }

        MemInfo* pPrev = NULL;
        if (pInfo->chainPrev != NULL && !pInfo->chainPrev->active) {
            pPrev = pInfo->chainPrev;
        }

        MemInfo* pNext = NULL;
        if (pInfo->chainNext != NULL && !pInfo->chainNext->active) {
            pNext = pInfo->chainNext;
        }

        if (pPrev != NULL) {
            if (pNext != NULL) {
                if (pNext->prev != NULL) {
                    pNext->prev->next = pNext->next;
                } else {
                    mFreeMem = pNext->next;
                }

                if (pNext->next != NULL) {
                    pNext->next->prev = pNext->prev;
                }

                pPrev->size +=
                    pNext->size + pInfo->size + headerSize + headerSize;

                pPrev->chainNext = pNext->chainNext;

                if (pNext->chainNext != NULL) {
                    pNext->chainNext->chainPrev = pPrev;
                }
            } else {
                pPrev->size += pInfo->size + headerSize;
                pPrev->chainNext = pInfo->chainNext;

                if (pInfo->chainNext != NULL) {
                    pInfo->chainNext->chainPrev = pPrev;
                }
            }
        } else if (pNext != NULL) {
            if (pNext->prev != NULL) {
                pNext->prev->next = pInfo;
            } else {
                mFreeMem = pInfo;
            }

            if (pNext->next != NULL) {
                pNext->next->prev = pInfo;
            }

            pInfo->prev = pNext->prev;
            pInfo->next = pNext->next;
            pInfo->size += pNext->size + headerSize;
            pInfo->active = false;
            pInfo->chainNext = pNext->chainNext;

            if (pNext->chainNext != NULL) {
                pNext->chainNext->chainPrev = pPrev;
            }
        } else {
            if (mFreeMem != NULL) {
                mFreeMem->prev = pInfo;
            }

            pInfo->next = mFreeMem;
            pInfo->prev = 0;
            pInfo->active = false;
            mFreeMem = pInfo;
        }
    } // at 0x64
};

NW4R_EF_MEMORY_MANAGER_NAMESPACE_CLOSE;

#endif
