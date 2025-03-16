#ifndef RVL_SDK_WPAD_MEM_H
#define RVL_SDK_WPAD_MEM_H
#include <types.h>

#include <revolution/WPAD/WPAD.h>
#ifdef __cplusplus
extern "C" {
#endif

#define WM_MEM_ADDR(ADDR) ((ADDR) & 0xFFFF)

#define WM_EXT_REG_ADDR(TYPE, ADDR)                                            \
    (((ADDR) & 0xFFFF) | ((WPAD_EXT_REG_##TYPE) << 16) | (1 << 26))

typedef enum {
    WPAD_EXT_REG_SPEAKER = 0xA2,
    WPAD_EXT_REG_EXTENSION = 0xA4,
    WPAD_EXT_REG_MOTION_PLUS = 0xA6,
    WPAD_EXT_REG_DPD = 0xB0
} WPADExtRegType;

typedef struct WPADMemBlock {
    int at_0x00;          // at 0x00
    int at_0x04;          // at 0x04
    s16 at_0x08;          // at 0x08
    int at_0x0c;          // at 0x0C
    WPADCallback at_0x10; // at 0x10
} WPADMemBlock;

typedef struct WPADGameInfo {
    s64 timestamp;        // at 0x0
    u16 gameName[16 + 1]; // at 0x8
    char gameID[4];       // at 0x2A
    u8 gameType;          // at 0x2E
    u8 checksum;          // at 0x2F
    u8 UNK_0x30[8];
} WPADGameInfo;

#ifdef __cplusplus
}
#endif
#endif
