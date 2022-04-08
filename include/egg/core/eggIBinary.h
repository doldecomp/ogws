#ifndef EGG_CORE_IBINARY_H
#define EGG_CORE_IBINARY_H
#include "types_egg.h"
#include "eggAssert.h"

namespace EGG
{
    template <typename T>
    class IBinary
    {
    public:
        struct Bin
        {
            char magic[4];
        };

        virtual void SetBinaryInner(const Bin&) = 0; // at 0x8
        virtual void GetBinaryInner(Bin *) const = 0; // at 0xC
        virtual const char * GetBinaryType() const = 0; // at 0x10
        virtual u32 GetBinarySize() const { return sizeof(T::Bin); }; // at 0x14
        virtual u8 GetVersion() const = 0; // at 0x18

        void Mount(const Bin *bin)
        {
            #line 93
            EGG_ASSERT(bin);
            EGG_ASSERT_MSG(GetBinaryType()[0] == bin->magic[0]
                && GetBinaryType()[1] == bin->magic[1]
                && GetBinaryType()[2] == bin->magic[2]
                && GetBinaryType()[3] == bin->magic[3],
                "Not for this class.");

            SetBinaryInner(*bin);
        }

        static void SetBinaryExtension(const char *ext) { sExtension = ext; }

    private:
        static const char *sExtension;
    };
}

#endif