#ifndef RVL_SDK_SI_HARDWARE_H
#define RVL_SDK_SI_HARDWARE_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * SI hardware registers
 */
volatile u32 SI_HW_REGS[] : 0xCD006400;

/**
 * Hardware register indexes
 */
typedef enum {
    SI_SIC0OUTBUF, //!< 0xCD006400
    SI_SIC0INBUFH, //!< 0xCD006404
    SI_SIC0INBUFL, //!< 0xCD006408
    SI_SIC1OUTBUF, //!< 0xCD00640C
    SI_SIC1INBUFH, //!< 0xCD006410
    SI_SIC1INBUFL, //!< 0xCD006414
    SI_SIC2OUTBUF, //!< 0xCD006418
    SI_SIC2INBUFH, //!< 0xCD00641C
    SI_SIC2INBUFL, //!< 0xCD006420
    SI_SIC3OUTBUF, //!< 0xCD006424
    SI_SIC3INBUFH, //!< 0xCD006428
    SI_SIC3INBUFL, //!< 0xCD00642C
    SI_SIPOLL,     //!< 0xCD006430
    SI_SICOMSCR,   //!< 0xCD006434
    SI_SISR,       //!< 0xCD006438
    SI_SIEXILK,    //!< 0xCD00643C

    // SI communication RAM
    SI_RAM_BASE = (0xCD006480 - 0xCD006400) / sizeof(u32) //!< 0xCD006480
};

// SIPOLL - SI Poll Register
#define SI_SIPOLL_X (0b1111111111 << 16)
#define SI_SIPOLL_Y (0b11111111 << 8)

// SICOMCSR - SI Communication Control Status Register
#define SI_SICOMCSR_TCINT (1 << 31)
#define SI_SICOMCSR_TCINTMSK (1 << 30)
#define SI_SICOMCSR_COMERR (1 << 29)
#define SI_SICOMCSR_RDSTINT (1 << 28)
#define SI_SICOMCSR_RDSTINTMSK (1 << 27)
#define SI_SICOMCSR_OUTLNGTH (0b1111111 << 16)
#define SI_SICOMCSR_INLNGTH (0b1111111 << 8)
#define SI_SICOMCSR_CHANNEL (0b11 << 1)
#define SI_SICOMCSR_TSTART (1 << 0)

// SISR - SI Status Register
#define SI_SISR_WR (1 << 31)
#define SI_SISR_RDST0 (1 << 29)
#define SI_SISR_WRST0 (1 << 28)
#define SI_SISR_NOREP0 (1 << 27)
#define SI_SISR_COLL0 (1 << 26)
#define SI_SISR_OVRUN0 (1 << 25)
#define SI_SISR_UNRUN0 (1 << 24)
#define SI_SISR_RDST1 (1 << 21)
#define SI_SISR_WRST1 (1 << 20)
#define SI_SISR_NOREP1 (1 << 19)
#define SI_SISR_COLL1 (1 << 18)
#define SI_SISR_OVRUN1 (1 << 17)
#define SI_SISR_UNRUN1 (1 << 16)
#define SI_SISR_RDST2 (1 << 13)
#define SI_SISR_WRST2 (1 << 12)
#define SI_SISR_NOREP2 (1 << 11)
#define SI_SISR_COLL2 (1 << 10)
#define SI_SISR_OVRUN2 (1 << 9)
#define SI_SISR_UNRUN2 (1 << 8)
#define SI_SISR_RDST3 (1 << 5)
#define SI_SISR_WRST3 (1 << 4)
#define SI_SISR_NOREP3 (1 << 3)
#define SI_SISR_COLL3 (1 << 2)
#define SI_SISR_OVRUN3 (1 << 1)
#define SI_SISR_UNRUN3 (1 << 0)

// SISR flags by channel
// Ex: (SISR >> ((SI_MAX_CHAN-1) - chan) * 8)
#define SI_RDST SI_SISR_RDST3
#define SI_WRST SI_SISR_WRST3
#define SI_NOREP SI_SISR_NOREP3
#define SI_COLL SI_SISR_COLL3
#define SI_OVRUN SI_SISR_OVRUN3
#define SI_UNRUN SI_SISR_UNRUN3

#ifdef __cplusplus
}
#endif
#endif
