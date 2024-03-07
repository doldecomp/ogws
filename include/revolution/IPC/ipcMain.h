#ifndef RVL_SDK_IPC_MAIN_H
#define RVL_SDK_IPC_MAIN_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

u32 IPC_HW_REGS[] : 0xCD000000;

inline u32 ACRReadReg(u32 reg) {
    return IPC_HW_REGS[reg / 4];
}

inline void ACRWriteReg(u32 reg, u32 val) {
    IPC_HW_REGS[reg / 4] = val;
}

void IPCInit(void);
u32 IPCReadReg(s32 index);
void IPCWriteReg(s32 index, u32 value);
void* IPCGetBufferHi(void);
void* IPCGetBufferLo(void);
void IPCSetBufferLo(void* lo);

#ifdef __cplusplus
}
#endif
#endif
