#pragma ipa file
#include "eggHeap.h"
#include "ut_list.h"
#include "eggAssert.h"

namespace EGG
{
    using namespace nw4r;

    void Heap::initialize()
    {
        ut::List_Init(&sHeapList, offsetof(Heap, mNode));
        OSInitMutex(&sRootMutex);
        sIsHeapListInitialized = TRUE;
    }

	Heap::Heap(MEMiHeapHead * pHeapHandle)
		: mHeapHandle(pHeapHandle), WORD_0x14(), mParentHeap(NULL)
	{
		ut::List_Init(&mChildren, offsetof(Disposer, mNode));
		
		#line 63
		EGG_ASSERT_MSG(sIsHeapListInitialized, "Please call Heap::initialize()");
		
		OSLockMutex(&sRootMutex);
		ut::List_Append(&sHeapList, this);
		OSUnlockMutex(&sRootMutex);
	}

    Heap::~Heap()
    {
        OSLockMutex(&sRootMutex);
        ut::List_Remove(&sHeapList, this);
        OSUnlockMutex(&sRootMutex);
    }

    void * Heap::alloc(u32 size, int align, Heap *pHeap)
    {
        void *block;

        if (sAllocatableHeap)
        {
            if (sCurrentHeap && !pHeap)
            {
                pHeap = sCurrentHeap;
            }

            if (pHeap != sAllocatableHeap)
            {
                #line 98
                EGG_ASSERT_MSG(false, "cannot allocate from heap %x : %x\n", pHeap, sAllocatableHeap);
                return NULL;
            }
        }

        if (pHeap)
        {
            return pHeap->alloc(size, align); 
        }

        if (sCurrentHeap)
        {
            block = sCurrentHeap->alloc(size, align);
            if (!block)
            {
                EGG_PRINT("heap (%p):(%.1fMBytes) size(%d:%.1fMBytes)\n",
                    sCurrentHeap, sCurrentHeap->getTotalSize() / MB_AS_B, size, size / MB_AS_B);
            }

            return block;
        }
        else
        {
            #line 129
            EGG_ASSERT_MSG(false, "cannot allocate %d from heap %x\n", size, pHeap);
            
            return NULL;
        }

        return block;
    }

    Heap * Heap::findHeap(MEMiHeapHead *handle)
    {
        Heap *containHeap = NULL;
        OSLockMutex(&sRootMutex);
        if (sIsHeapListInitialized)
        {
            Heap *node = NULL;

            while (node = (Heap *)nw4r::ut::List_GetNext(&sHeapList, node))
            {
                if (node->mHeapHandle == handle)
                {
                    containHeap = node;
                    break;
                }
            }
        }
        OSUnlockMutex(&sRootMutex);

        return containHeap;
    }

    Heap * Heap::findParentHeap()
    {
        #line 173
        EGG_ASSERT(mHeapHandle != NULL);

        return mParentHeap;
    }

    Heap * Heap::findContainHeap(const void *p)
    {
        Heap *containHeap = NULL;
        MEMiHeapHead *containHandle = MEMFindContainHeap(p);
        if (containHandle)
        {
            containHeap = findHeap(containHandle);
        }

        return containHeap;
    }

    void Heap::free(void *p, Heap *pHeap)
    {
        if (!pHeap)
        {
            MEMiHeapHead *handle = MEMFindContainHeap(p);
            if (!handle) return;

            pHeap = findHeap(handle);
            if (!pHeap) return;
        }

        pHeap->free(p);
    }

    void Heap::dispose()
    {
        Disposer *node;
        while (node = (Disposer *)ut::List_GetFirst(&mChildren))
        {
            node->~Disposer();
        }
    }

    Heap * Heap::becomeCurrentHeap()
    {
        #line 328
        EGG_ASSERT(this != NULL);

        OSLockMutex(&sRootMutex);
        Heap *oldHeap = sCurrentHeap;
        sCurrentHeap = this;
        OSUnlockMutex(&sRootMutex);

        return oldHeap;
    }

    // .bss
    nw4r::ut::List Heap::sHeapList;
    OSMutex Heap::sRootMutex;
    // .sbss
    Heap *Heap::sCurrentHeap;
    BOOL Heap::sIsHeapListInitialized;
    Heap *Heap::sAllocatableHeap;
}

using namespace EGG;

void * operator new(size_t size)
{
    return Heap::alloc(size, 4, NULL);
}

void * operator new(size_t size, Heap *pHeap, int align)
{
    return Heap::alloc(size, align, pHeap);
}

void * operator new[](size_t size)
{
    return Heap::alloc(size, 4, NULL);
}

void * operator new[](size_t size, int align)
{
    return Heap::alloc(size, align, NULL);
}

void * operator new[](size_t size, Heap *pHeap, int align)
{
    return Heap::alloc(size, align, pHeap);
}

void operator delete(void *p)
{
    Heap::free(p, NULL);
}

void operator delete[](void *p)
{
    Heap::free(p, NULL);
}