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
            char magic[4]; // at 0x0
            u32 size; // at 0x4
            u8 UNK_0x5[0x8 - 0x5];
            u8 version; // at 0x8
            u8 UNK_0x09[0x10 - 0x9];
        };

        virtual void SetBinaryInner(const Bin&) = 0; // at 0x8
        virtual void GetBinaryInner(Bin *) const = 0; // at 0xC
        virtual const char * GetBinaryType() const = 0; // at 0x10
        virtual u32 GetBinarySize() const { return sizeof(T::Bin); }; // at 0x14
        virtual u8 GetVersion() const = 0; // at 0x18

        void SetBinary(const void *bin)
        {
            #line 93
            EGG_ASSERT(bin);
            Bin *binary = (Bin *)bin;

            EGG_ASSERT_MSG(GetBinaryType()[0] == binary->magic[0]
                && GetBinaryType()[1] == binary->magic[1]
                && GetBinaryType()[2] == binary->magic[2]
                && GetBinaryType()[3] == binary->magic[3],
                "Not for this class.");

            SetBinaryInner(*bin);
        }

        void GetBinary(void *bin) const
        {
            #line 105
            EGG_ASSERT(bin);
            Bin *binary = (Bin *)bin;

            binary->version = GetVersion();
            binary->size = GetBinarySize();
            for (int i = 0; i < sizeof(Bin::magic); i++)
            {
                binary->magic[i] = GetBinaryType()[i];
            }

            GetBinaryInner(binary);
        }

        static void SetBinaryExtension(const char *ext) { sExtension = ext; }

    private:
        static const char *sExtension;
    };
}

#endif