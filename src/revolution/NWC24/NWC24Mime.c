#include <revolution/NWC24.h>

static char *MIMEEncStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

NWC24Err Base64Encode(char *inputBuffer, s32 inputLength, u32 *inBytesConsumed, char *outBuffer, s32 outBufferSize, u32 *outBytesWritten) {
    s32 result = NWC24_OK;
    s32 outputIndex;
    s32 inputIndex = 0;
    BOOL hasThird;
    BOOL hasSecond;
    u32 combined;

    for (outputIndex = 0; inputIndex < inputLength; inputIndex += 3) {
        if ((outputIndex + 3) >= outBufferSize) {
            result = NWC24_ERR_OVERFLOW;
            break;
        }
    
        hasThird = FALSE;
        hasSecond = FALSE;
        
        combined = ((unsigned char)inputBuffer[inputIndex]);
        combined <<= 8;
        
        if ((inputIndex + 1) < inputLength) {
            hasSecond = TRUE;
            combined |= ((unsigned char)inputBuffer[inputIndex + 1]);
        }
        
        combined <<= 8;
        
        if ((inputIndex + 2) < inputLength) {
            hasThird = TRUE;
            combined |= ((unsigned char)inputBuffer[inputIndex + 2]);
        }
        
        outBuffer[outputIndex + 0] = MIMEEncStr[(combined >> 18) & 0x3F];
        outBuffer[outputIndex + 1] = MIMEEncStr[(combined >> 12) & 0x3F];
        outBuffer[outputIndex + 2] = MIMEEncStr[(hasSecond) ? ((combined >> 6) & 0x3F) : (0x40)];
        outBuffer[outputIndex + 3] = MIMEEncStr[(hasThird) ? (combined & 0x3F) : (0x40)];
        
        outputIndex += 4;
    }

    *outBytesWritten = outputIndex;

    if (inBytesConsumed != 0) {
        outputIndex = inputLength;
        if (inputLength < inputIndex) {
            inputIndex = inputLength;
        }
        *inBytesConsumed = inputIndex;
    }
    return result;
}

void NWC24Base64Encode(char *inputBuffer, s32 inputLength, char *outBuffer, s32 outBufferSize, u32 *outBytesWritten) {
    Base64Encode(inputBuffer, inputLength, 0, outBuffer, outBufferSize, outBytesWritten);
}

void NWC24InitBase64Table(signed char *codes) {
    int i;
    for (i = 0; i < 256; i++) {
        codes[i] = (char)0xFF;
    }

    for (i = 'A'; i <= 'Z'; i++) {
        codes[i] = (char)(i - 'A');
    }

    for (i = 'a'; i <= 'z'; i++) {
        codes[i] = (char)(26 + i - 'a');
    }

    for (i = '0'; i <= '9'; i++) {
        codes[i] = (char)(52 + i - '0');
    }

    codes['+'] = 62;
    codes['/'] = 63;

    return;
}

NWC24Err QEncode(u8 *outBuffer, u32 outBufferSize, u32 *outBytesWritten, u8 *inputBuffer, u32 inputLength, u32 *inBytesConsumed, s32 maxLineLength) {
    u8 *outputPtr;
    u32 outBytesUsed;
    u32 inputIndex;
    s32 result;
    s32 lineLength;
    u8 encodeBuffer[8];
    s32 bufferIndex;
    BOOL needsSoftBreak;
    s32 emitCount;
    s32 bytesRead;
    s16 currentByte;

    result = NWC24_OK;

    if (outBuffer == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (inputBuffer == 0) {
        return NWC24_ERR_INVALID_VALUE;
    }
    if (inputLength == 0) {
        return NWC24_ERR_OVERFLOW;
    }
    if (inBytesConsumed) {
        *inBytesConsumed = 0;
    }
    if (outBytesWritten) {
        *outBytesWritten = 0;
    }
    outputPtr = outBuffer;
    lineLength = 0;
    outBytesUsed = 0;
    inputIndex = 0;
    while (inputIndex < inputLength) {
        currentByte = *inputBuffer;
        needsSoftBreak = FALSE;

        if (((((char)currentByte) >= '!') && (((char)currentByte) <= '~')) && (((char)currentByte) != '=')) {
            bytesRead = 1;
            emitCount = 1;
            encodeBuffer[0] = *inputBuffer;
        } else {
            if ((((inputIndex + 1) < inputLength) && (((char)currentByte) == '\r')) && (((long)inputBuffer[1]) == '\n')) {
                bytesRead = 2;
                encodeBuffer[0] = *inputBuffer;
                emitCount = 1;
                encodeBuffer[1] = inputBuffer[1];
            } else {
                encodeBuffer[0] = '=';
                if (((*inputBuffer) >> 4) >= 10) {
                    encodeBuffer[1] = (((*inputBuffer) >> 4) % 10) + 'A';
                } else {
                    encodeBuffer[1] = (((*inputBuffer) >> 4) % 10) + '0';
                }
                if (((*inputBuffer) & 0xf) >= 10) {
                    encodeBuffer[2] = (((*inputBuffer) & 0xf) % 10) + 'A';
                } else {
                    encodeBuffer[2] = (((*inputBuffer) & 0xf) % 10) + '0';
                }

                bytesRead = 1;
                emitCount = 3;
            }
        }
        if ((maxLineLength == 0) && ((lineLength + emitCount) >= 75)) {
            needsSoftBreak = TRUE;
            emitCount = emitCount + 3;
        }
        if (((u32)(outBytesUsed + emitCount)) >= outBufferSize) {
            result = NWC24_ERR_OVERFLOW;
            break;
        }
        outBytesUsed = emitCount + outBytesUsed;
        if (needsSoftBreak) {
            *outputPtr = '=';
            outputPtr[1] = '\r';
            outputPtr[2] = '\n';
            outputPtr = outputPtr + 3;
            lineLength = 0;
            emitCount = emitCount - 3;
        }
        lineLength = emitCount + lineLength;
        bufferIndex = 0;
        while (bufferIndex < emitCount) {
            *(outputPtr++) = encodeBuffer[bufferIndex];
            bufferIndex++;
        }

        inputIndex = inputIndex + bytesRead;
        inputBuffer = inputBuffer + bytesRead;
    }

    if (inBytesConsumed) {
        *inBytesConsumed = inputIndex;
    }

    if (outBytesWritten) {
        *outBytesWritten = outBytesUsed;
    }

    return result;
}

s32 NWC24EncodeQuotedPrintable(u8 *outBuffer, u32 outBufferSize, u32 *outBytesWritten, u8 *inputBuffer, u32 inputLength, u32 *inBytesConsumed) {
    return QEncode(outBuffer, outBufferSize, outBytesWritten, inputBuffer, inputLength, inBytesConsumed, 0);
}
