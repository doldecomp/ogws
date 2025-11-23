#ifndef RVL_SDK_IPC_HARDWARE_H
#define RVL_SDK_IPC_HARDWARE_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * IPC hardware registers
 */
volatile u32 IPC_HW_REGS_PPC[1] DECL_ADDRESS(0xCD000000);
volatile u32 IPC_HW_REGS[1] DECL_ADDRESS(0xCD800000);

/**
 * Hardware register indexes
 */
// clang-format off
#define LIST_OF_REGS                                                           \
    X(IPC_PPCMSG,      0xCD000000)                                             \
    X(IPC_PPCCTRL,     0xCD000004)                                             \
    X(IPC_ARMMSG,      0xCD000008)                                             \
    X(IPC_ARMCTRL,     0xCD00000C)                                             \
    X(TIMER,           0xCD000010)                                             \
    X(ALARM,           0xCD000014)                                             \
    X(PPCIRQFLAG,      0xCD000030)                                             \
    X(PPCIRQMASK,      0xCD000034)                                             \
    X(ARMIRQFLAG,      0xCD000038)                                             \
    X(ARMIRQMASK,      0xCD00003C)                                             \
    X(MEMMIRR,         0xCD000060)                                             \
    X(AHBPROT,         0xCD000064)                                             \
    X(EXICTRL,         0xCD000070)                                             \
    X(GPIO1BOUT,       0xCD0000C0)                                             \
    X(GPIO1BDIR,       0xCD0000C4)                                             \
    X(GPIO1BIN,        0xCD0000C8)                                             \
    X(GPIO1BINTLVL,    0xCD0000CC)                                             \
    X(GPIO1BINTFLAG,   0xCD0000D0)                                             \
    X(GPIO1BINTENABLE, 0xCD0000D4)                                             \
    X(GPIO1BINMIR,     0xCD0000D8)                                             \
    X(GPIO1ENABLE,     0xCD0000DC)                                             \
    X(GPIO1OUT,        0xCD0000E0)                                             \
    X(GPIO1DIR,        0xCD0000E4)                                             \
    X(GPIO1IN,         0xCD0000E8)                                             \
    X(GPIO1INTLVL,     0xCD0000EC)                                             \
    X(GPIO1INTFLAG,    0xCD0000F0)                                             \
    X(GPIO1INTENABLE,  0xCD0000F4)                                             \
    X(GPIO1INMIR,      0xCD0000F8)                                             \
    X(GPIO1OWNER,      0xCD0000FC)                                             \
    X(DIFLAGS,         0xCD000180)                                             \
    X(RESETS,          0xCD000194)                                             \
    X(CLOCKS,          0xCD0001B4)                                             \
    X(GPIO2OUT,        0xCD0001C8)                                             \
    X(GPIO2DIR,        0xCD0001CC)                                             \
    X(GPIO2IN,         0xCD0001D0)                                             \
    X(OTPCMD,          0xCD0001EC)                                             \
    X(OTPDATA,         0xCD0001F0)                                             \
    X(VERSION,         0xCD000214)
// clang-format on

/**
 * Hardware register indexes (IPC)
 */
#define X(NAME, ADDR) IPC_##NAME = (ADDR - 0xCD000000) / 4,
typedef enum { LIST_OF_REGS } IPCHwReg;
#undef X

/**
 * Hardware register indexes (ACR)
 */
#define X(NAME, ADDR) ACR_##NAME = (ADDR - 0xCD000000),
typedef enum { LIST_OF_REGS } ACRHwReg;
#undef X

/**
 * GPIO register flags
 */
typedef enum {
    GPIO_POWER = (1 << 0),
    GPIO_SHUTDOWN = (1 << 1),
    GPIO_FAN = (1 << 2),
    GPIO_DCDC = (1 << 3),
    GPIO_DISPIN = (1 << 4),
    GPIO_SLOTLED = (1 << 5),
    GPIO_EJECTBTN = (1 << 6),
    GPIO_SLOTIN = (1 << 7),
    GPIO_SENSORBAR = (1 << 8),
    GPIO_DOEJECT = (1 << 9),
    GPIO_EEP_CS = (1 << 10),
    GPIO_EEP_CLK = (1 << 11),
    GPIO_EEP_MOSI = (1 << 12),
    GPIO_EEP_MISO = (1 << 13),
    GPIO_AVE_SCL = (1 << 14),
    GPIO_AVE_SDA = (1 << 15),
    GPIO_DEBUG0 = (1 << 16),
    GPIO_DEBUG1 = (1 << 17),
    GPIO_DEBUG2 = (1 << 18),
    GPIO_DEBUG3 = (1 << 19),
    GPIO_DEBUG4 = (1 << 20),
    GPIO_DEBUG5 = (1 << 21),
    GPIO_DEBUG6 = (1 << 22),
    GPIO_DEBUG7 = (1 << 23),
} GPIOFlag;

#undef LIST_OF_REGS

#ifdef __cplusplus
}
#endif
#endif
