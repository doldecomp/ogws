#ifndef RVL_SDK_VF_PF_STR_H
#define RVL_SDK_VF_PF_STR_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef s16 (*PF_ConvertCharFunc)(const void* src, void* dst);
typedef size_t (*PF_UnicodeCharWidthFunc)(const void* data);
typedef size_t (*PF_OemCharWidthFunc)(int ch);
typedef BOOL (*PF_IsMBCharFunc)(char ch, u32 mode);

typedef struct PF_VOL_SET {
    char UNK_0x0[0x24];
    PF_ConvertCharFunc convOemToUnicode;
    PF_ConvertCharFunc convUnicodeToOem;
    PF_OemCharWidthFunc oemCharWidth;
    PF_IsMBCharFunc oemIsMBChar;
    PF_UnicodeCharWidthFunc unicodeCharWidth;
    PF_IsMBCharFunc unicodeIsMBChar;
} PF_VOL_SET;

extern PF_VOL_SET VFipf_vol_set;

#ifdef __cplusplus
}
#endif
#endif
