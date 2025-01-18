#pragma ipa file
#pragma use_lmw_stmw on

#include "eggStream.h"
#include "eggAssert.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

namespace EGG
{
    Stream::Stream() :
        mIsTokenReady(false),
        mFlags(),
        mPosition(0),
        WORD_0x18(0),
        mTextBufferSize(sizeof(sTextBuffer)),
        mTextBuffer(sTextBuffer),
        mAllowComments(false)
    {
    }

    Stream::~Stream()
    {
    }

    u8 Stream::read_u8()
    {
        if (isTextMode())
        {
            u32 val;

            const char *token = getNextToken();
            #line 68
            EGG_ASSERT_MSG(token != NULL, "Token Error\n");

            sscanf(token, "%d", &val);
            return val;
        }

        u8 val;
        _read(&val, sizeof(u8));
        return val;
    }

    void Stream::write_u8(u8 data)
    {
        if (isTextMode())
        {
            printf("%d ", data);
            return;
        }

        _write(&data, sizeof(u8));
    }

    s8 Stream::read_s8()
    {
        if (isTextMode())
        {
            u32 val;

            const char *token = getNextToken();
            #line 92
            EGG_ASSERT_MSG(token != NULL, "Token Error\n");

            sscanf(token, "%d", &val);
            return val;
        }

        u8 val;
        _read(&val, sizeof(u8));
        return val;
    }

    void Stream::write_s8(s8 data)
    {
        if (isTextMode())
        {
            printf("%d ", data);
            return;
        }

        _write(&data, sizeof(s8));
    }

    u16 Stream::read_u16()
    {
        if (isTextMode())
        {
            u32 val;

            const char *token = getNextToken();
            #line 118
            EGG_ASSERT_MSG(token != NULL, "Token Error\n");

            sscanf(token, "%d", &val);
            return val;
        }

        u16 val;
        _read(&val, sizeof(u16));
        return val;
    }

    void Stream::write_u16(u16 data)
    {
        if (isTextMode())
        {
            printf("%d ", data);
            return;
        }

        _write(&data, sizeof(u16));
    }

    s16 Stream::read_s16()
    {
        if (isTextMode())
        {
            u32 val;

            const char *token = getNextToken();
            #line 142
            EGG_ASSERT_MSG(token != NULL, "Token Error\n");

            sscanf(token, "%d", &val);
            return val;
        }

        u16 val;
        _read(&val, sizeof(u16));
        return val;
    }

    void Stream::write_s16(s16 data)
    {
        if (isTextMode())
        {
            printf("%d ", data);
            return;
        }

        _write(&data, sizeof(s16));
    }

    u32 Stream::read_u32()
    {
        if (isTextMode())
        {
            // Typo?
            u16 val;

            const char *token = getNextToken();
            #line 169
            EGG_ASSERT_MSG(token != NULL, "Token Error\n");

            sscanf(token, "%d", &val);
            return *(u32 *)&val;
        }

        u32 val;
        _read(&val, sizeof(u32));
        return val;
    }

    void Stream::write_u32(u32 data)
    {
        if (isTextMode())
        {
            printf("%d ", data);
            return;
        }

        _write(&data, sizeof(u32));
    }

    s32 Stream::read_s32()
    {
        if (isTextMode())
        {
            u32 val;

            const char *token = getNextToken();
            #line 193
            EGG_ASSERT_MSG(token != NULL, "Token Error\n");

            sscanf(token, "%d", &val);
            return val;
        }

        u32 val;
        _read(&val, sizeof(u32));
        return val;
    }

    void Stream::write_s32(s32 data)
    {
        if (isTextMode())
        {
            printf("%d ", data);
            return;
        }

        _write(&data, sizeof(s32));
    }

    void UNUSED_STRINGS_EGGSTREAM_0()
    {
        EGG_PRINT("%x");
        EGG_PRINT("%04x ");
        EGG_PRINT("%08x ");
    };

    f32 Stream::read_float()
    {
        if (isTextMode())
        {
            // Typo?
            u16 val;

            const char *token = getNextToken();
            #line 272
            EGG_ASSERT_MSG(token != NULL, "Token Error\n");

            sscanf(token, "%f ", &val);
            return *(f32 *)&val;
        }

        f32 val;
        _read(&val, sizeof(f32));
        return val;
    }

    void Stream::write_float(f32 data)
    {
        if (isTextMode())
        {
            printf("%f ", data);
            return;
        }

        _write(&data, sizeof(f32));
    }

    void UNUSED_STRINGS_EGGSTREAM_1()
    {
        EGG_PRINT("%s");
    };

    void Stream::writeString(char *str)
    {
        const int len = strlen(str);

        if (isTextMode())
        {
            bool escape = false;
            
            for (int i = 0; i < len; i++)
            {
                if (isUpperSJIS(str[i]))
                {
                    i++;
                    continue;
                }
                
                if (isSpace(str[i])) escape = true;
            }

            if (escape)
            {
                _writeByte('\"');

                for (int i = 0; i < len; i++)
                {
                    if (isUpperSJIS(str[i]))
                    {
                        _writeByte(str[i]);
                        
                        #line 367
                        EGG_ASSERT_MSG(i + 1 >= len, "SJIS-Assertion : unterminated sjis");
                        
                        _writeByte(str[i + 1]);
                        i++;
                    }
                    else if (str[i] == '\"')
                    {
                        _writeByte('\\');
                        _writeByte('\"');
                    }
                    else
                    {
                        _writeByte(str[i]);
                    }
                }

                _writeByte('\"');
            }
            else
            {
                for (int i = 0; i < len; i++)
                {
                    if (isUpperSJIS(str[i]))
                    {
                        _writeByte(str[i]);
                        
                        #line 383
                        EGG_ASSERT_MSG(i + 1 >= len, "SJIS-Assertion : unterminated sjis");
                        
                        _writeByte(str[i + 1]);
                        i++;
                        
                    }
                    else
                    {
                        _writeByte(str[i]);
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < len; i++)
            {
                _writeByte(str[i]);
            }

            _writeByte('\0');
        }
    }

    // Missing stringbase load at 800A90EC/+0x570
    // https://decomp.me/scratch/lpaK6
    const char * Stream::readString(char *buf, int bufSize)
    {
        char local[0x400];
        int pos, size;

        // Token cached
        if (mIsTokenReady)
        {
            const size_t textLen = strlen(mTextBuffer);
            if (buf == NULL) buf = new char[textLen + 1];
            for (int i = 0; i < textLen + 1; i++)
            {
                buf[i] = mTextBuffer[i];
            }

            mIsTokenReady = false;
            return buf;
        }
        // Text mode (no token cached)
        else if (isTextMode())
        {
            char delim = skipSpace();
            if (delim == '\"')
            {
                for (pos = 0, size = 0; pos < 0x400; pos++)
                {
                    u8 next = _readByte();
                    if (next == '\"') break;

                    if (next == '\\')
                    {
                        #line 453
                        EGG_ASSERT_MSG(_readByte() == '\"', "Yen error\n");
                        local[size++] = '\"';
                    }
                    else
                    {
                        if (isUpperSJIS(next))
                        {
                            local[size++] = next;
                            local[size++] = _readByte();
                        }
                        else
                        {
                            local[size++] = next;
                        }
                    }
                }

                local[size] = '\0';
                
                int textLen = strlen(local);
                if (buf != NULL)
                {
                    #line 472
                    EGG_ASSERT_MSG(textLen + 1 < bufSize, "readString(%x,%d) overflow\n", buf, bufSize);   
                }
                else
                {
                    buf = new char[textLen + 1];
                }

                for (int i = 0; i < textLen + 1; i++)
                {
                    buf[i] = local[i];
                }

                return buf;
            }

            for (pos = 0, size = 0; pos < 0x400; pos++)
            {
                if (eof()) break;
                
                if (isSpace(delim))
                {
                    if (mAllowComments || delim != '#') break;
                    skipUntilCRLF();
                }
                else if (isUpperSJIS(delim))
                {
                    local[size++] = delim;
                    local[size++] = _readByte();
                }
                else
                {
                    local[size++] = delim;
                }

                delim = _readByte();
            }

            local[size] = '\0';

            const int textLen = strlen(local);
            if (buf != NULL)
            {
                #line 515
                EGG_ASSERT_MSG(textLen + 1 < bufSize, "readString(%x,%d) overflow\n", buf, bufSize);   
            }
            else
            {
                buf = new char[textLen + 1];
            }
            
            for (int i = 0; i < textLen + 1; i++)
            {
                buf[i] = local[i];
            }
            
            return buf;
        }
        // Binary mode
        else
        {
            for (int i = 0; i < 0x400; i++)
            {
                u8 byte = _readByte();
                local[i] = byte;
                if (byte == '\0') break;
            }
            
            const int textLen = strlen(local);
            if (buf != NULL)
            {
                #line 542
                EGG_ASSERT_MSG(textLen + 1 < bufSize, "readString(%x,%d) overflow\n", buf, bufSize);   
            }
            else
            {
                buf = new char[textLen + 1];
            }
            
            for (int i = 0; i < textLen + 1; i++)
            {
                buf[i] = local[i];
            }    
        }

        return buf;
    }

    void UNUSED_STRINGS_EGGSTREAM_2()
    {
        EGG_PRINT("buffer overflow\n[%s]\n");
        EGG_PRINT("# %s\r\n");
        EGG_PRINT("{\r\n");
        EGG_PRINT("}\r\n");
    };

    void Stream::copyToTextBuffer()
    {
        int i;

        *mTextBuffer = skipSpace();
        for (i = 1; !eof() && i < mTextBufferSize;)
        {
            char c = _readByte();
            if (isSpace(c))
            {
                mTextBuffer[i] = '\0';
                if (!mAllowComments && c == '#')
                {
                    skipUntilCRLF();
                }

                return;
            }
            else
            {
                mTextBuffer[i++] = c;
                if (c == '\0') return;
            }
        }

        #line 824
        EGG_ASSERT_MSG(false, "copyToTextBuffer : eof or %d>=%d\n", i, mTextBufferSize);
    }

    void UNUSED_STRINGS_EGGSTREAM_3()
    {
        EGG_PRINT("isBeginGroup is out of support\n");
        EGG_PRINT("isEndGroup is out of support\n");
    };

    char Stream::skipSpace()
    {       
        if (isTextMode())
        {
            bool skip = false;
            while (!eof())
            {
                char c = _readByte();

                if (skip)
                {
                    if (isUpperSJIS(c))
                    {
                        c = _readByte();
                    }
                    else if (isCRLF(c))
                    {
                        skip = false;
                    }
                }
                else if (!mAllowComments && c == '#' || c == '!')
                {
                    skip = true;
                }
                else if (!isSpace(c))
                {
                    return c;
                }
            }
        }
            
        return '\0';
    }

    void Stream::printf(char *str, ...)
    {
        va_list list;
        char buf[0x400];
        va_start(list, str);
        vsprintf(buf, str, list);
        va_end(list);

        int len = strlen(buf);
        #line 1007
        EGG_ASSERT_MSG(len < 0x400, "buffer overflow\n[%s]\n", buf);

        if (len > 0)
        {
            for (int i = 0; i < len; i++)
            {
                char c = buf[i];
                _write(&c, sizeof(c));
            }
        }
    }

   void Stream::_read(void *buf, u32 len)
   {
       #line 743
       EGG_ASSERT_MSG(!eof(), "eof::_read (%x,%d) : mPosition %d\n", buf, len, mPosition);

       read((u8 *)buf, len);
       mPosition += len;
   }

   void Stream::_write(void *data, u32 len)
   {
       write((u8 *)data, len);
       mPosition += len;

       #line 772
       EGG_ASSERT_MSG(!eof(), "eof::_write (%x,%d) : mPosition %d\n", data, len, mPosition);
   }

    u8 Stream::_readByte()
    {
        u8 val;
        _read(&val, sizeof(u8));
        return val;
    }

    void Stream::_writeByte(u8 data)
    {
        _write(&data, sizeof(u8));
    }

    void Stream::skipUntilCRLF()
    {
        while (!eof())
        {
            char c = _readByte();

            if (isUpperSJIS(c))
            {
                c = _readByte();
            }
            else if (c == '\r' || c == '\n')
            {
                return;
            }
        }
    }

    const char * Stream::getNextToken()
    {
        if (!isTextMode()) return NULL;

        if (mIsTokenReady)
        {
            mIsTokenReady = false;
            return mTextBuffer;
        }

        copyToTextBuffer();
        return mTextBuffer;
    }

    bool Stream::isSpace(char c)
    {
        return (c == '\t' || c == '\n' || c == '\r' || c == ' ')
            || (!mAllowComments && c == '#')
            || (c == '!');
    }

    bool Stream::isCRLF(char c)
    {
        return c == '\r' || c == '\n';
    }

    bool Stream::isUpperSJIS(char c)
    {
        const u8 byte = (u8)c;
        return byte >= 0x81 && byte <= 0x9F || byte >= 0xE0 && byte <= 0xFC;
    }

    RamStream::RamStream(u8 *dataBlk, u32 dataSize) :
        mDataBlk(dataBlk),
        mDataSize(dataSize)
    {
    }

    void RamStream::read(u8 *dataBlk, u32 dataSize)
    {
        for (u32 i = 0; i < dataSize;)
        {
            dataBlk[i++] = mDataBlk[mPosition + i];
        }
    }

    void RamStream::write(u8 *dataBlk, u32 dataSize)
    {
        for (u32 i = 0; i < dataSize;)
        {
            u32 j = i++;
            mDataBlk[mPosition + j] = dataBlk[j];
        }
    }

    bool RamStream::eof()
    {
        return mPosition < mDataSize;
    }

    RamStream::~RamStream()
    {

    }

    char Stream::sTextBuffer[sTextBufferSize];
}
