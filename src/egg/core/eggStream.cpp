// TODO: REMOVE AFTER REFACTOR
#pragma ipa file

#include <egg/core.h>
#include <egg/prim.h>

#include <cstdarg>
#include <cstdio>
#include <cstring>

namespace EGG {

/******************************************************************************
 *
 * Stream
 *
 ******************************************************************************/

char Stream::sTextBuffer[TEXT_BUFFER_SIZE];

Stream::Stream() : mIsTokenReady(false) {
    mPosition = 0;
    mGroupIndentLevel = 0;

    mTextBufferSize = sizeof(sTextBuffer);
    mTextBuffer = sTextBuffer;

    mAllowComments = false;
}

Stream::~Stream() {}

u8 Stream::read_u8() {
    u8 value;
    int number;

    if (isTextMode()) {
        const char* pToken = getNextToken();
#line 68
        EGG_ASSERT_MSG(pToken != NULL, "Token Error\n");

        std::sscanf(pToken, "%d", &number);
        return static_cast<u8>(number);
    }

    _read(&value, sizeof(u8));
    return value;
}

void Stream::write_u8(u8 value) {
    if (isTextMode()) {
        printf("%d ", value);
    } else {
        _write(&value, sizeof(u8));
    }
}

s8 Stream::read_s8() {
    s8 value;
    int number;

    if (isTextMode()) {
        const char* pToken = getNextToken();
#line 92
        EGG_ASSERT_MSG(pToken != NULL, "Token Error\n");

        std::sscanf(pToken, "%d", &number);
        return static_cast<s8>(number);
    }

    _read(&value, sizeof(s8));
    return static_cast<s8>(value);
}

void Stream::write_s8(s8 value) {
    if (isTextMode()) {
        printf("%d ", value);
    } else {
        _write(&value, sizeof(s8));
    }
}

u16 Stream::read_u16() {
    u16 value;
    int number;

    if (isTextMode()) {
        const char* pToken = getNextToken();
#line 118
        EGG_ASSERT_MSG(pToken != NULL, "Token Error\n");

        std::sscanf(pToken, "%d", &number);
        return static_cast<u16>(number);
    }

    _read(&value, sizeof(u16));
    return value;
}

void Stream::write_u16(u16 value) {
    if (isTextMode()) {
        printf("%d ", value);
    } else {
        _write(&value, sizeof(u16));
    }
}

s16 Stream::read_s16() {
    s16 value;
    int number;

    if (isTextMode()) {
        const char* pToken = getNextToken();
#line 142
        EGG_ASSERT_MSG(pToken != NULL, "Token Error\n");

        std::sscanf(pToken, "%d", &number);
        return static_cast<s16>(number);
    }

    _read(&value, sizeof(s16));
    return value;
}

void Stream::write_s16(s16 value) {
    if (isTextMode()) {
        printf("%d ", value);
    } else {
        _write(&value, sizeof(s16));
    }
}

u32 Stream::read_u32() {
    u32 value;
    int number;

    if (isTextMode()) {
        const char* pToken = getNextToken();
#line 169
        EGG_ASSERT_MSG(pToken != NULL, "Token Error\n");

        std::sscanf(pToken, "%d", &number);
        return static_cast<u32>(number);
    }

    _read(&value, sizeof(u32));
    return value;
}

void Stream::write_u32(u32 value) {
    if (isTextMode()) {
        printf("%d ", value);
    } else {
        _write(&value, sizeof(u32));
    }
}

s32 Stream::read_s32() {
    s32 value;
    int number;

    if (isTextMode()) {
        const char* pToken = getNextToken();
#line 193
        EGG_ASSERT_MSG(pToken != NULL, "Token Error\n");

        std::sscanf(pToken, "%d", &number);
        return static_cast<s32>(number);
    }

    _read(&value, sizeof(s32));
    return value;
}

void Stream::write_s32(s32 value) {
    if (isTextMode()) {
        printf("%d ", value);
    } else {
        _write(&value, sizeof(s32));
    }
}

DECOMP_FORCEACTIVE(eggStream_cpp,
                  "%x",
                  "%04x ",
                  "%08x ");

f32 Stream::read_float() {
    f32 value;
    f32 number;

    if (isTextMode()) {
        const char* pToken = getNextToken();
#line 272
        EGG_ASSERT_MSG(pToken != NULL, "Token Error\n");

        sscanf(pToken, "%f ", &number);
        return number;
    }

    _read(&value, sizeof(f32));
    return value;
}

void Stream::write_float(f32 value) {
    if (isTextMode()) {
        printf("%f ", value);
    } else {
        _write(&value, sizeof(f32));
    }
}

DECOMP_FORCEACTIVE(eggStream_cpp_1,
                  "%s");

void Stream::writeString(char* pStr) {
    int len = std::strlen(pStr);

    if (isTextMode()) {
        bool escape = false;

        for (int i = 0; i < len; i++) {
            if (isUpperSJIS(pStr[i])) {
                i++;
                continue;
            }

            if (isSpace(pStr[i])) {
                escape = true;
            }
        }

        if (escape) {
            _writeByte('\"');

            for (int i = 0; i < len; i++) {
                if (isUpperSJIS(pStr[i])) {
                    _writeByte(pStr[i]);

#line 367
                    EGG_ASSERT_MSG(i + 1 >= len, "SJIS-Assertion : unterminated sjis");
                    _writeByte(pStr[i + 1]);
                    i++;
                } else if (pStr[i] == '\"') {
                    _writeByte('\\');
                    _writeByte('\"');
                } else {
                    _writeByte(pStr[i]);
                }
            }

            _writeByte('\"');
        } else {
            for (int i = 0; i < len; i++) {
                if (isUpperSJIS(pStr[i])) {
                    _writeByte(pStr[i]);

#line 383
                    EGG_ASSERT_MSG(i + 1 >= len, "SJIS-Assertion : unterminated sjis");
                    _writeByte(pStr[i + 1]);
                    i++;
                } else {
                    _writeByte(pStr[i]);
                }
            }
        }
    } else {
        for (int i = 0; i < len; i++) {
            _writeByte(pStr[i]);
        }

        _writeByte('\0');
    }
}

const char* Stream::readString(char* pDst, int maxLen) {
    char buffer[TEXT_BUFFER_SIZE];

    // Token cached
    if (mIsTokenReady) {
        u32 textLen = std::strlen(mTextBuffer);

        if (pDst == NULL) {
            pDst = new char[textLen + 1];
        }

        for (int i = 0; i < textLen + 1; i++) {
            pDst[i] = mTextBuffer[i];
        }

        mIsTokenReady = false;
        return pDst;
    }

    // Text mode (no token cached)
    if (isTextMode()) {
        char delim = skipSpace();
        if (delim == '\"') {
            int size, pos;
            for (size = 0, pos = 0; pos < TEXT_BUFFER_SIZE; pos++) {
                u8 byte = _readByte();

                if (byte == '\"') {
                    break;
                }

                if (byte == '\\') {
#line 453
                    EGG_ASSERT_MSG(_readByte() == '\"', "Yen error\n");
                    buffer[size++] = '\"';
                } else {
                    if (isUpperSJIS(byte)) {
                        buffer[size++] = byte;
                        buffer[size++] = _readByte();
                    } else {
                        buffer[size++] = byte;
                    }
                }
            }

            buffer[size] = '\0';

            int textLen = std::strlen(buffer);
            if (pDst != NULL) {
#line 472
                EGG_ASSERT_MSG(textLen + 1 < maxLen, "readString(%x,%d) overflow\n", pDst, maxLen);
            } else {
                pDst = new char[textLen + 1];
            }

            for (int i = 0; i < textLen + 1; i++) {
                pDst[i] = buffer[i];
            }

            return pDst;
        }

        int size, pos;
        for (size = 0, pos = 0; pos < TEXT_BUFFER_SIZE; pos++) {
            if (eof()) {
                break;
            }

            if (isSpace(delim)) {
                if (mAllowComments || delim != '#') {
                    break;
                }

                skipUntilCRLF();
                break;
            } else if (isUpperSJIS(delim)) {
                buffer[size++] = delim;
                buffer[size++] = _readByte();
            } else {
                buffer[size++] = delim;
            }

            delim = _readByte();
        }

        buffer[size] = '\0';

        int textLen = std::strlen(buffer);
        if (pDst != NULL) {
#line 515
            EGG_ASSERT_MSG(textLen + 1 < maxLen, "readString(%x,%d) overflow\n", pDst, maxLen);
        } else {
            pDst = new char[textLen + 1];
        }

        for (int i = 0; i < textLen + 1; i++) {
            pDst[i] = buffer[i];
        }

        return pDst;
    }

    // Binary mode
    for (int i = 0; i < TEXT_BUFFER_SIZE; i++) {
        u8 byte = _readByte();
        buffer[i] = byte;

        if (byte == '\0') {
            break;
        }
    }

    int textLen = strlen(buffer);
    if (pDst != NULL) {
#line 542
        EGG_ASSERT_MSG(textLen + 1 < maxLen, "readString(%x,%d) overflow\n", pDst, maxLen);
    } else {
        pDst = new char[textLen + 1];
    }

    for (int i = 0; i < textLen + 1; i++) {
        pDst[i] = buffer[i];
    }

    return pDst;
}

DECOMP_FORCEACTIVE(eggStream_cpp_2,
                  "buffer overflow\n[%s]\n",
                  "# %s\r\n",
                  "{\r\n",
                  "}\r\n");

void Stream::_read(void* pDst, u32 size) {
#line 743
    EGG_ASSERT_MSG(!eof(), "eof::_read (%x,%d) : mPosition %d\n", pDst, size, mPosition);

    read(static_cast<u8*>(pDst), size);
    mPosition += size;
}

void Stream::_write(void* pSrc, u32 size) {
    write(static_cast<u8*>(pSrc), size);
    mPosition += size;

#line 772
    EGG_ASSERT_MSG(!eof(), "eof::_write (%x,%d) : mPosition %d\n", pSrc, size, mPosition);
}

u8 Stream::_readByte() {
    u8 value;
    _read(&value, sizeof(u8));
    return value;
}

void Stream::_writeByte(u8 value) {
    _write(&value, sizeof(u8));
}

void Stream::skipUntilCRLF() {
    while (!eof()) {
        char ch = _readByte();

        if (isUpperSJIS(ch)) {
            ch = _readByte();
        } else if (ch == '\r' || ch == '\n') {
            return;
        }
    }
}

void Stream::copyToTextBuffer() {
    *mTextBuffer = skipSpace();

    int i = 1;
    while (!eof() && i < mTextBufferSize) {
        char ch = _readByte();

        if (isSpace(ch)) {
            mTextBuffer[i] = '\0';

            if (!mAllowComments && ch == '#') {
                skipUntilCRLF();
            }

            return;
        } else {
            mTextBuffer[i++] = ch;

            if (ch == '\0') {
                return;
            }
        }
    }

#line 824
    EGG_ASSERT_MSG(false, "copyToTextBuffer : eof or %d>=%d\n", i, mTextBufferSize);
}

DECOMP_FORCEACTIVE(eggStream_cpp_2,
                  "isBeginGroup is out of support\n",
                  "isEndGroup is out of support\n");

const char* Stream::getNextToken() {
    if (!isTextMode()) {
        return NULL;
    }

    if (mIsTokenReady) {
        mIsTokenReady = false;
        return mTextBuffer;
    }

    copyToTextBuffer();
    return mTextBuffer;
}

bool Stream::isSpace(char ch) {
    return ch == '\t' || ch == '\n' || ch == '\r' || ch == ' ' ||
           !mAllowComments && ch == '#' || ch == '!';
}

bool Stream::isCRLF(char ch) {
    return ch == '\r' || ch == '\n';
}

bool Stream::isUpperSJIS(char ch) {
    u8 byte = static_cast<u8>(ch);
    return byte >= 0x81 && byte <= 0x9F || byte >= 0xE0 && byte <= 0xFC;
}

char Stream::skipSpace() {
    if (isTextMode()) {
        bool skip = false;

        while (!eof()) {
            char ch = _readByte();

            if (skip) {
                if (isUpperSJIS(ch)) {
                    ch = _readByte();
                } else if (isCRLF(ch)) {
                    skip = false;
                }
            } else if (!mAllowComments && ch == '#' || ch == '!') {
                skip = true;
            } else if (!isSpace(ch)) {
                return ch;
            }
        }
    }

    return '\0';
}

void Stream::printf(char* pFmt, ...) {
    char buffer[TEXT_BUFFER_SIZE];

    std::va_list list;
    va_start(list, pFmt);
    std::vsprintf(buffer, pFmt, list);
    va_end(list);

    int len = std::strlen(buffer);

#line 1007
    EGG_ASSERT_MSG(len < TEXT_BUFFER_SIZE, "buffer overflow\n[%s]\n", buffer);

    if (len > 0) {
        for (int i = 0; i < len; i++) {
            _writeByte(buffer[i]);
        }
    }
}

/******************************************************************************
 *
 * RamStream
 *
 ******************************************************************************/

RamStream::RamStream(u8* pBuffer, u32 size)
    : mBuffer(pBuffer), mBufferSize(size) {}

void RamStream::read(u8* pDst, u32 size) {
    for (int i = 0; i < size; i++) {
        pDst[i] = mBuffer[mPosition + i];
    }
}

void RamStream::write(u8* pSrc, u32 size) {
    for (int i = 0; i < size; i++) {
        mBuffer[mPosition + i] = pSrc[i];
    }
}

bool RamStream::eof() {
    return mPosition > mBufferSize;
}

} // namespace EGG
