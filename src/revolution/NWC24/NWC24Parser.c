#include <revolution/NWC24.h>

const char* MIMETypeStr[] = {"application/octet-stream",
                             "application/x-wii-minidata",
                             "application/x-wii-msgboard",
                             "image/jpeg",
                             "image/x-wii-picture",
                             "multipart/alternative",
                             "multipart/mixed",
                             "multipart/related",
                             "text/html",
                             "text/plain"};
NWC24MIMEType MIMETypeConv[] = {NWC24_APPLICATION_OCTET_STREAM,
                                NWC24_X_WII_MINIDATA,
                                NWC24_X_WII_MSGBOARD,
                                NWC24_IMAGE_JPEG,
                                NWC24_X_WII_PICTURE,
                                NWC24_MULTIPART_ALTERNATIVE,
                                NWC24_MULTIPART_MIXED,
                                NWC24_MULTIPART_RELATED,
                                NWC24_TEXT_HTML,
                                NWC24_TEXT_PLAIN};
const char* MIMETypeSuffix[] = {"dat", "wii", "wii", "jpg", "wii",
                                "???", "???", "???", "htm", "txt"};

const char* CharsetStr[] = {
    "euc-jp",      "iso-2022-jp", "iso-8859-1", "iso-8859-10",
    "iso-8859-15", "iso-8859-2",  "iso-8859-3", "iso-8859-5",
    "iso-8859-7",  "iso-8859-9",  "shift_jis",  "us-ascii",
    "utf-16be",    "utf-32be",    "utf-8",      "windows-1252"};
NWC24Charset CharsetConv[] = {
    NWC24_EUC_JP,      NWC24_ISO_2022_JP, NWC24_ISO_8859_1, NWC24_ISO_8859_10,
    NWC24_ISO_8859_15, NWC24_ISO_8859_2,  NWC24_ISO_8859_3, NWC24_ISO_8859_5,
    NWC24_ISO_8859_7,  NWC24_ISO_8859_9,  NWC24_SHIFT_JIS,  NWC24_US_ASCII,
    NWC24_UTF_16BE,    NWC24_UTF_32BE,    NWC24_UTF_8,      NWC24_WINDOWS_1252};

const char* EncodingStr[] = {"7bit", "8bit", "base64", "quoted-printable"};
NWC24Encoding EncodingConv[] = {NWC24_ENC_7BIT, NWC24_ENC_8BIT,
                                NWC24_ENC_BASE64, NWC24_ENC_QUOTED_PRINTABLE};

const char* NWC24GetMIMETypeStr(NWC24MIMEType type) {
    NWC24MIMEType* conv;
    int i;

    for (i = 0; i < ARRAY_SIZE(MIMETypeConv); i++) {
        // TODO: Fakematch
        conv = MIMETypeConv;
        conv && !conv;

        if (type == conv[i]) {
            return MIMETypeStr[i];
        }
    }

    return NULL;
}

const char* NWC24iGetMIMETypeSuffix(NWC24MIMEType type) {
    int i;

    for (i = 0; i < ARRAY_SIZE(MIMETypeConv); i++) {
        if (type == MIMETypeConv[i]) {
            return MIMETypeSuffix[i];
        }
    }

    return NULL;
}

const char* NWC24GetCharsetStr(NWC24Charset set) {
    int i;

    for (i = 0; i < ARRAY_SIZE(CharsetConv); i++) {
        if (set == CharsetConv[i]) {
            return CharsetStr[i];
        }
    }

    return NULL;
}

const char* NWC24GetEncodingStr(NWC24Encoding enc) {
    int i;

    for (i = 0; i < ARRAY_SIZE(EncodingConv); i++) {
        if (enc == EncodingConv[i]) {
            return EncodingStr[i];
        }
    }

    return NULL;
}
