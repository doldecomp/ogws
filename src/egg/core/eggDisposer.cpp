#include "eggDisposer.h"
#include "eggHeap.h"
#include "ut_list.h"

namespace EGG
{
    using namespace nw4r;

    Disposer::Disposer()
    {
        Heap *myHeap = Heap::findContainHeap(this);
        mHeap = myHeap;
        if (mHeap)
        {
            ut::List_Append(&mHeap->mChildren, this);
        }
    }

    Disposer::~Disposer()
    {
        if (mHeap)
        {
            ut::List_Remove(&mHeap->mChildren, this);
        }
    }
}