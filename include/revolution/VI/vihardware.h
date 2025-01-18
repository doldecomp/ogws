#ifndef RVL_SDK_VI_HARDWARE_H
#define RVL_SDK_VI_HARDWARE_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * VI hardware registers
 */
volatile u16 VI_HW_REGS[] : 0xCC002000;

/**
 * Hardware register indexes
 */
typedef enum {
    VI_VTR,    //!< 0xCC002000
    VI_DCR,    //!< 0xCC002002
    VI_HTR0_H, //!< 0xCC002004
    VI_HTR0_L, //!< 0xCC002006
    VI_HTR1_H, //!< 0xCC002008
    VI_HTR1_L, //!< 0xCC00200A
    VI_VTO_H,  //!< 0xCC00200C
    VI_VTO_L,  //!< 0xCC00200E
    VI_VTE_H,  //!< 0xCC002010
    VI_VTE_L,  //!< 0xCC002012
    VI_BBEI_H, //!< 0xCC002014
    VI_BBEI_L, //!< 0xCC002016
    VI_BBOI_H, //!< 0xCC002018
    VI_BBOI_L, //!< 0xCC00201A
    VI_TFBL_H, //!< 0xCC00201C
    VI_TFBL_L, //!< 0xCC00201E
    VI_TFBR_H, //!< 0xCC002020
    VI_TFBR_L, //!< 0xCC002022
    VI_BFBL_H, //!< 0xCC002024
    VI_BFBL_L, //!< 0xCC002026
    VI_BFBR_H, //!< 0xCC002028
    VI_BFBR_L, //!< 0xCC00202A
    VI_DPV,    //!< 0xCC00202C
    VI_DPH,    //!< 0xCC00202E
    VI_DI0_H,  //!< 0xCC002030
    VI_DI0_L,  //!< 0xCC002032
    VI_DI1_H,  //!< 0xCC002034
    VI_DI1_L,  //!< 0xCC002036
    VI_DI2_H,  //!< 0xCC002038
    VI_DI2_L,  //!< 0xCC00203A
    VI_DI3_H,  //!< 0xCC00203C
    VI_DI3_L,  //!< 0xCC00203E
    VI_DL0_H,  //!< 0xCC002040
    VI_DL0_L,  //!< 0xCC002042
    VI_DL1_H,  //!< 0xCC002044
    VI_DL1_L,  //!< 0xCC002046
    VI_HSW,    //!< 0xCC002048
    VI_HSR,    //!< 0xCC00204A
    VI_FCT0_H, //!< 0xCC00204C
    VI_FCT0_L, //!< 0xCC00204E
    VI_FCT1_H, //!< 0xCC002050
    VI_FCT1_L, //!< 0xCC002052
    VI_FCT2_H, //!< 0xCC002054
    VI_FCT2_L, //!< 0xCC002056
    VI_FCT3_H, //!< 0xCC002058
    VI_FCT3_L, //!< 0xCC00205A
    VI_FCT4_H, //!< 0xCC00205C
    VI_FCT4_L, //!< 0xCC00205E
    VI_FCT5_H, //!< 0xCC002060
    VI_FCT5_L, //!< 0xCC002062
    VI_FCT6_H, //!< 0xCC002064
    VI_FCT6_L, //!< 0xCC002066
    VI_0x68,   //!< 0xCC002068
    VI_0x6A,   //!< 0xCC00206A
    VI_VICLK,  //!< 0xCC00206C
    VI_VISEL,  //!< 0xCC00206E
    VI_0x70,   //!< 0xCC002070
    VI_HBE,    //!< 0xCC002072
    VI_HBS,    //!< 0xCC002074
    VI_0x76,   //!< 0xCC002076
    VI_0x78,   //!< 0xCC002078
    VI_0x7A,   //!< 0xCC00207A
    VI_0x7C,   //!< 0xCC00207C
} VIHwReg;

// DCR - Display Configuration Register
#define VI_DCR_ENB (1 << 0)
#define VI_DCR_RST (1 << 1)
#define VI_DCR_NIN (1 << 2)
#define VI_DCR_FMT (0b11 << 8)

// DI{n} - Display Interrupt Register N
#define VI_DI_INT (1 << 15)
#define VI_DI_ENB (1 << 12)

// VICLK - VI Clock Select Register
#define VI_VICLK_SPEED (1 << 0)
typedef enum { VI_VICLK_27MHZ, VI_VICLK_54MHZ } VIClkSpeed;

// HBE - Border HBE
#define VI_HBE_BRDR_EN (1 << 15)

#ifdef __cplusplus
}
#endif
#endif
