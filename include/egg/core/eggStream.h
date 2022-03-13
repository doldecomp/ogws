#ifndef EGG_CORE_STREAM_H
#define EGG_CORE_STREAM_H
#include "types_egg.h"
#include "eggBitFlag.h"

namespace EGG
{
    class Stream
    {
    public:
        Stream();
        virtual ~Stream(); // at 0x8
        virtual void read(u8 *, u32) = 0; // at 0xC
        virtual void write(u8 *, u32) = 0; // at 0x10
        virtual bool eof() = 0; // at 0x14

        u8 read_u8();
        void write_u8(u8);
        s8 read_s8();
        void write_s8(s8);
        u16 read_u16();
        void write_u16(u16);
        s16 read_s16();
        void write_s16(s16);
        u32 read_u32();
        void write_u32(u32);
        s32 read_s32();
        void write_s32(s32);
        f32 read_float();
        void write_float(f32);
        const char * readString(char *, int);
        void writeString(char *);

        void copyToTextBuffer();
        char skipSpace();
        void printf(char *, ...);
        void skipUntilCRLF();
        const char * getNextToken();
        bool isSpace(char);
        bool isCRLF(char);
        bool isUpperSJIS(char);

        void setTextMode() { mFlags.setBit(0); }
        bool isTextMode() { return mFlags.onBit(0); }
        void setBinMode() { mFlags.resetBit(0); }
        bool isBinMode() { return !mFlags.onBit(0); }

    protected:
        void _read(void *, u32);
        void _write(void *, u32);
        u8 _readByte();
        void _writeByte(u8);

    protected:
        bool mIsTokenReady; // at 0x4
        u32 mPosition; // at 0x8
        TBitFlag<u16> mFlags; // at 0xC
        char *mTextBuffer; // at 0x10
        u32 mTextBufferSize; // at 0x14
        UNKWORD WORD_0x18;
        bool mAllowComments; // at 0x1C

        static const int sTextBufferSize = 1024;
        static char sTextBuffer[sTextBufferSize];
    };

    class RamStream : public Stream
    {
    public:
        RamStream(u8 *, u32);
        ~RamStream(); // at 0x8
        virtual void read(u8 *, u32); // at 0xC
        virtual void write(u8 *, u32); // at 0x10
        virtual bool eof(); // at 0x14

    private:
        u8 *mDataBlk; // at 0x20
        u32 mDataSize; // at 0x24
    };
}

#endif