#ifndef EGG_CORE_ARCHIVE_H
#define EGG_CORE_ARCHIVE_H
#include "types_egg.h"
#include "eggDisposer.h"
#include "eggAssert.h"
#include "ut_list.h"
#include <RevoSDK/TRK/__mem.h>
#include <RevoSDK/ARC/arc.h>

namespace EGG
{
    struct Archive : Disposer
    {
        struct FileInfo
        {
            u32 mArcStartOffset;
            u32 mArcLength;
        };

        inline Archive()
        {
            INT_0x14 = 1;
            INT_0x10 = 0;
            memset(&mHandle, NULL, sizeof(mHandle));

            if (!sIsArchiveListInitialized)
            {
                nw4r::ut::List_Init(&sArchiveList, sizeof(Archive) - sizeof(mNode));
                sIsArchiveListInitialized = true;
            }

            appendList(this);
        }

        inline static void appendList(Archive *p)
        {
            nw4r::ut::List_Append(&sArchiveList, p);
        }

        inline static void removeList(Archive *p)
        {
            nw4r::ut::List_Remove(&sArchiveList, p);
        }

        virtual ~Archive(); // at 0x8
        static Archive * mount(void *, Heap *, int);
        void * getFile(const char *, FileInfo *);

        void *PTR_0x8;
        int INT_0xC;
        int INT_0x10;
        int INT_0x14;
        ARCHandle mHandle; // at 0x18
        nw4r::ut::Node mNode; // at 0x34

        static nw4r::ut::List sArchiveList;
        static bool sIsArchiveListInitialized;
    };
}

#endif