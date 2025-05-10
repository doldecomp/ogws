/**
 * For more details, see:
 * https://www.gc-forever.com/yagcd/chap8.html#sec8
 * https://www.gc-forever.com/yagcd/chap5.html#sec5
 * https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoCommon/BPMemory.h
 * https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoCommon/XFMemory.h
 * https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoCommon/OpcodeDecoding.h
 * https://patents.google.com/patent/US6700586B1/en
 * https://patents.google.com/patent/US6639595B1/en
 * https://patents.google.com/patent/US7002591
 * https://patents.google.com/patent/US6697074
 */

#ifndef RVL_SDK_GX_HARDWARE_H
#define RVL_SDK_GX_HARDWARE_H
#include <types.h>

#include <revolution/GX/GXTypes.h>
#ifdef __cplusplus
extern "C" {
#endif

/************************************************************
 *
 *
 * GX FIFO
 *
 *
 ***********************************************************/

/**
 * FIFO write/gather pipe
 */
extern volatile union {
    // 1-byte
    char c;
    unsigned char uc;
    // 2-byte
    short s;
    unsigned short us;
    // 4-byte
    int i;
    unsigned int ui;
    void* p;
    float f;
} WGPIPE AT_ADDRESS(0xCC008000);

/**
 * FIFO commands
 */
typedef enum {
    GX_FIFO_CMD_NOOP = 0x00,

    GX_FIFO_CMD_LOAD_BP_REG = 0x61,
    GX_FIFO_CMD_LOAD_CP_REG = 0x08,
    GX_FIFO_CMD_LOAD_XF_REG = 0x10,

    GX_FIFO_CMD_LOAD_INDX_A = 0x20,
    GX_FIFO_CMD_LOAD_INDX_B = 0x28,
    GX_FIFO_CMD_LOAD_INDX_C = 0x30,
    GX_FIFO_CMD_LOAD_INDX_D = 0x38,

    GX_FIFO_CMD_CALL_DL = 0x40,
    GX_FIFO_CMD_INVAL_VTX = 0x48
} GXFifoCmd;

#define __GX_FIFO_SET_LOAD_INDX_DST(reg, x) ((reg) = GX_BITSET(reg, 20, 12, x))
#define __GX_FIFO_SET_LOAD_INDX_NELEM(reg, x) ((reg) = GX_BITSET(reg, 16, 4, x))
#define __GX_FIFO_SET_LOAD_INDX_INDEX(reg, x) ((reg) = GX_BITSET(reg, 0, 16, x))

#define __GX_FIFO_LOAD_INDX(reg, dst, nelem, index)                            \
    {                                                                          \
        u32 cmd = 0;                                                           \
        __GX_FIFO_SET_LOAD_INDX_DST(cmd, dst);                                 \
        __GX_FIFO_SET_LOAD_INDX_NELEM(cmd, nelem);                             \
        __GX_FIFO_SET_LOAD_INDX_INDEX(cmd, index);                             \
        WGPIPE.c = reg;                                                        \
        WGPIPE.i = cmd;                                                        \
    }

#define GX_FIFO_LOAD_INDX_A(dst, nelem, index)                                 \
    __GX_FIFO_LOAD_INDX(GX_FIFO_CMD_LOAD_INDX_A, dst, nelem, index)

#define GX_FIFO_LOAD_INDX_B(dst, nelem, index)                                 \
    __GX_FIFO_LOAD_INDX(GX_FIFO_CMD_LOAD_INDX_B, dst, nelem, index)

#define GX_FIFO_LOAD_INDX_C(dst, nelem, index)                                 \
    __GX_FIFO_LOAD_INDX(GX_FIFO_CMD_LOAD_INDX_C, dst, nelem, index)

#define GX_FIFO_LOAD_INDX_D(dst, nelem, index)                                 \
    __GX_FIFO_LOAD_INDX(GX_FIFO_CMD_LOAD_INDX_D, dst, nelem, index)

/************************************************************
 *
 *
 * GX Blitting Processor (BP)
 *
 *
 ***********************************************************/

/**
 * Load immediate value into BP register
 */
#define GX_BP_LOAD_REG(data)                                                   \
    WGPIPE.c = GX_FIFO_CMD_LOAD_BP_REG;                                        \
    WGPIPE.i = (data);

/**
 * Set BP command opcode (first 8 bits)
 */
#define GX_BP_SET_OPCODE(cmd, opcode) (cmd) = GX_BITSET(cmd, 0, 8, (opcode))

#define GX_BP_OPCODE_SHIFT 24
#define GX_BP_CMD_SZ (sizeof(u8) + sizeof(u32))

/************************************************************
 *
 *
 * GX Command Processor (CP)
 *
 *
 ***********************************************************/

/**
 * Load immediate value into CP register
 */
#define GX_CP_LOAD_REG(addr, data)                                             \
    WGPIPE.c = GX_FIFO_CMD_LOAD_CP_REG;                                        \
    WGPIPE.c = (addr);                                                         \
    WGPIPE.i = (data);

#define GX_CP_CMD_SZ (sizeof(u8) + sizeof(u8) + sizeof(u32))

/************************************************************
 *
 *
 * GX Transform Unit (XF)
 *
 *
 ***********************************************************/

/**
 * XF memory
 */
typedef enum {
    GX_XF_MEM_POSMTX = 0x0000,
    GX_XF_MEM_NRMMTX = 0x0400,
    GX_XF_MEM_DUALTEXMTX = 0x0500,
    GX_XF_MEM_LIGHTOBJ = 0x0600
} GXXfMem;

/**
 * Header for an XF register load
 */
#define GX_XF_LOAD_REG_HDR(addr)                                               \
    WGPIPE.c = GX_FIFO_CMD_LOAD_XF_REG;                                        \
    WGPIPE.i = (addr);

/**
 * Load immediate value into XF register
 */
#define GX_XF_LOAD_REG(addr, data)                                             \
    GX_XF_LOAD_REG_HDR(addr);                                                  \
    WGPIPE.i = (data);

#define GX_XF_CMD_SZ (sizeof(u8) + sizeof(u32) + sizeof(u32))

/**
 * Load immediate values into multiple XF registers
 */
#define GX_XF_LOAD_REGS(size, addr)                                            \
    {                                                                          \
        u32 cmd = 0;                                                           \
        cmd |= (addr);                                                         \
        cmd |= (size) << 16;                                                   \
        GX_XF_LOAD_REG_HDR(cmd);                                               \
    }

/**
 * Enums for Tex0-Tex7 register fields
 */
typedef enum {
    GX_XF_TEX_PROJ_ST, // (s,t): texmul is 2x4
    GX_XF_TEX_PROJ_STQ // (s,t,q): texmul is 3x4
} GXXfTexProj;

typedef enum {
    GX_XF_TEX_FORM_AB11, // (A, B, 1.0, 1.0) (used for regular texture source)
    GX_XF_TEX_FORM_ABC1  // (A, B, C, 1.0) (used for geometry or normal source)
} GXXfTexForm;

typedef enum {
    GX_XF_TG_REGULAR, // Regular transformation (transform incoming data)
    GX_XF_TG_BUMP,    // Texgen bump mapping

    GX_XF_TG_CLR0, // Color texgen: (s,t)=(r,g:b) (g and b are concatenated),
                   // color0

    GX_XF_TG_CLR1 // Color texgen: (s,t)=(r,g:b) (g and b are concatenated),
                  // color1
} GXXfTexGen;

/**
 * Misc. hardware enums
 */
typedef enum {
    GX_RAS_COLOR0A0,
    GX_RAS_COLOR1A1,
    GX_RAS_ALPHA_BUMP = 5,
    GX_RAS_ALPHA_BUMPN,
    GX_RAS_COLOR_ZERO,

    GX_RAS_MAX_CHANNEL
} GXRasChannelID;

typedef enum {
    GX_TEVREG_COLOR,
    GX_TEVREG_KONST,
} GXTevRegType;

#ifdef __cplusplus
}
#endif
#endif
