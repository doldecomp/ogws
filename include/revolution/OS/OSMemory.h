#ifndef RVL_SDK_OS_MEMORY_H
#define RVL_SDK_OS_MEMORY_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

#define OS_MEM_KB_TO_B(mb) ((mb) * 1024)
#define OS_MEM_B_TO_KB(mb) ((mb) / 1024)

#define OS_MEM_MB_TO_B(mb) ((mb) * 1024 * 1024)
#define OS_MEM_B_TO_MB(mb) ((mb) / 1024 / 1024)

#define OSIsMEM1Region(addr) (((u32)(addr) & 0x30000000) == 0)
#define OSIsMEM2Region(addr) (((u32)(addr) & 0x30000000) == 0x10000000)

#define OS_IS_MEM1_REGION(addr) OSIsMEM1Region(addr)
#define OS_IS_MEM2_REGION(addr) OSIsMEM2Region(addr)

typedef enum OSProtectChannel {
    OS_PROTECT_CHANNEL_0,
    OS_PROTECT_CHANNEL_1,
    OS_PROTECT_CHANNEL_2,
    OS_PROTECT_CHANNEL_3,
} OSProtectChannel;

typedef enum OSProtectControl {
    OS_PROTECT_CONTROL_NONE = 0,
    OS_PROTECT_CONTROL_RD = 1 << 0,
    OS_PROTECT_CONTROL_WR = 1 << 1,
    OS_PROTECT_CONTROL_RDWR = OS_PROTECT_CONTROL_RD | OS_PROTECT_CONTROL_WR,
} OSProtectControl;

u32 OSGetPhysicalMem1Size(void);
u32 OSGetPhysicalMem2Size(void);
u32 OSGetConsoleSimulatedMem1Size(void);
u32 OSGetConsoleSimulatedMem2Size(void);
void __OSInitMemoryProtection(void);
void OSProtectRange(u32 chan, void* pAddr, u32 nBytes, u32 control);

#ifdef __cplusplus
}
#endif
#endif
