#ifndef EGG_CORE_STREAM_H
#define EGG_CORE_STREAM_H
#include <egg/types_egg.h>

#include <egg/core/eggBitFlag.h>

namespace EGG {

/******************************************************************************
 *
 * Stream
 *
 ******************************************************************************/

class Stream {
public:
    Stream();
    virtual ~Stream(); // at 0x8

    virtual void read(u8* pDst, u32 size) = 0;  // at 0xC
    virtual void write(u8* pSrc, u32 size) = 0; // at 0x10
    virtual bool eof() = 0;                     // at 0x14

/**
 * @brief Helper for declaring stream functions for primitive types
 */
#define TYPE_FUNC_DECL(T)                                                      \
    T read_##T();                                                              \
    void write_##T(T value);                                                   \
    void read_##T(T& rValue) {                                                 \
        rValue = read_##T();                                                   \
    }

    TYPE_FUNC_DECL(u8);
    TYPE_FUNC_DECL(s8);
    TYPE_FUNC_DECL(u16);
    TYPE_FUNC_DECL(s16);
    TYPE_FUNC_DECL(u32);
    TYPE_FUNC_DECL(s32);
    TYPE_FUNC_DECL(float);

#undef TYPE_FUNC_DECL

    f32 read_f32() {
        return read_float();
    }
    void write_f32(f32 value) {
        write_float(value);
    }
    void read_f32(f32& rValue) {
        rValue = read_f32();
    }

    const char* readString(char* pDst, int maxlen);
    void writeString(char* pStr);

    bool isSpace(char ch);
    bool isCRLF(char ch);
    bool isUpperSJIS(char ch);

    void setTextMode() {
        mFlags.setBit(BIT_TEXT_MODE);
    }
    bool isTextMode() {
        return mFlags.onBit(BIT_TEXT_MODE);
    }
    void setBinMode() {
        mFlags.resetBit(BIT_TEXT_MODE);
    }
    bool isBinMode() {
        return !isTextMode();
    }

    s32 getPosition() const {
        return mPosition;
    }

protected:
    bool mIsTokenReady;    // at 0x4
    s32 mPosition;         // at 0x8
    TBitFlag<u16> mFlags;  // at 0xC
    char* mTextBuffer;     // at 0x10
    s32 mTextBufferSize;   // at 0x14
    u32 mGroupIndentLevel; // at 0x18
    bool mAllowComments;   // at 0x1C

    static const int TEXT_BUFFER_SIZE = 1024;
    static char sTextBuffer[TEXT_BUFFER_SIZE];

private:
    enum {
        BIT_TEXT_MODE,
    };

private:
    void skipUntilCRLF();
    void copyToTextBuffer();
    const char* getNextToken();

    char skipSpace();
    void printf(char* pFmt, ...);

    void _read(void* pDst, u32 size);
    void _write(void* pSrc, u32 size);

    u8 _readByte();
    void _writeByte(u8 value);
};

/******************************************************************************
 *
 * RamStream
 *
 ******************************************************************************/

class RamStream : public Stream {
public:
    RamStream(u8* pBuffer, u32 size);

    virtual void read(u8* pDst, u32 size);  // at 0xC
    virtual void write(u8* pSrc, u32 size); // at 0x10
    virtual bool eof();                     // at 0x14

private:
    u8* mBuffer;     // at 0x20
    u32 mBufferSize; // at 0x24
};

} // namespace EGG

#endif
