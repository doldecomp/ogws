#ifndef NW4R_EF_RES_ANIM_CURVE_H
#define NW4R_EF_RES_ANIM_CURVE_H
#include <nw4r/types_nw4r.h>

#include <nw4r/math.h>

#define NW4R_EF_MAGIC_ANIMCURVE 0xAC
#define NW4R_EF_MAGIC_ANIMBAKED 0xAB

namespace nw4r {
namespace ef {

enum AnimCurveType {
    AC_TYPE_PARTICLE_U8 = 0,
    AC_TYPE_PARTICLE_F32 = 3,
    AC_TYPE_PARTICLE_ROTATE = 6,
    AC_TYPE_PARTICLE_TEXTURE = 4,
    AC_TYPE_CHILD = 5
};

enum AnimCurveTarget {
    // AC_TYPE_PARTICLE_U8
    AC_TARGET_COLOR0PRI,
    AC_TARGET_ALPHA0PRI,
    AC_TARGET_COLOR0SEC,
    AC_TARGET_ALPHA0SEC,
    AC_TARGET_COLOR1PRI,
    AC_TARGET_ALPHA1PRI,
    AC_TARGET_COLOR1SEC,
    AC_TARGET_ALPHA1SEC,
    AC_TARGET_ACMPREF0,
    AC_TARGET_ACMPREF1,

    // AC_TYPE_PARTICLE_F32
    AC_TARGET_SIZE,
    AC_TARGET_SCALE,
    AC_TARGET_12,
    AC_TARGET_TEXTURE1SCALE = 17,
    AC_TARGET_TEXTURE1ROTATE,
    AC_TARGET_TEXTURE1TRANSLATE,
    AC_TARGET_TEXTURE2SCALE,
    AC_TARGET_TEXTURE2ROTATE,
    AC_TARGET_TEXTURE2TRANSLATE,
    AC_TARGET_TEXTUREINDSCALE,
    AC_TARGET_TEXTUREINDROTATE,
    AC_TARGET_TEXTUREINDTRANSLATE,

    AC_TARGET_UNK32 = 32,
    AC_TARGET_FIELD_SPEED,
    AC_TARGET_UNK34,
    AC_TARGET_UNK35,
    AC_TARGET_UNK36,
    AC_TARGET_UNK38 = 38, // FieldSpin?
    AC_TARGET_UNK39,
    AC_TARGET_EMIT_COMMONPARAM = 64,
    AC_TARGET_EMIT_SCALE,
    AC_TARGET_EMIT_ROTATE,
    AC_TARGET_EMIT_TRANSLATE,
    AC_TARGET_EMIT_SPEED_ORIG,
    AC_TARGET_EMIT_SPEED_YAXIS,
    AC_TARGET_EMIT_SPEED_RANDOM,
    AC_TARGET_EMIT_SPEED_NORMAL,
    AC_TARGET_EMIT_SPEED_SPECDIR,
    AC_TARGET_EMIT_EMISSION,

    // AC_TYPE_PARTICLE_ROTATE
    AC_TARGET_ROTATE = 12,

    // Texture target
    // AC_TARGET_TEXTURE1 = 23,
    // AC_TARGET_TEXTURE2 = 24,
    // AC_TARGET_TEXTUREIND = 25,

    // Child target
    // AC_TARGET_CHILD = 26,

    // Field target
    // AC_TARGET_FIELD_GRAVITY = 27,
    // AC_TARGET_FIELD_SPEED = 28,
    // AC_TARGET_FIELD_MAGNET = 29,
    // AC_TARGET_FIELD_NEWTON = 30,
    // AC_TARGET_FIELD_VORTEX = 31,
    // AC_TARGET_FIELD_SPIN = 32,
    // AC_TARGET_FIELD_RANDOM = 33,
    // AC_TARGET_FIELD_TAIL = 34,

    // Postfield target
    // AC_TARGET_POSTFIELD_SIZE = 35,
    // AC_TARGET_POSTFIELD_ROTATE = 36,
    // AC_TARGET_POSTFIELD_TRANSLATE = 37,
};

struct AnimCurveHeader {
    enum ProcessFlag {
        PROC_FLAG_SYNC = (1 << 2),
        PROC_FLAG_STOP = (1 << 3),
        PROC_FLAG_TIMING = (1 << 4),
        PROC_FLAG_INFLOOP = (1 << 5),
        PROC_FLAG_TURN = (1 << 6),
        PROC_FLAG_FITTING = (1 << 7),
    };

    u8 magic;        // at 0x0
    u8 kindType;     // at 0x1
    u8 curveFlag;    // at 0x2
    u8 kindEnable;   // at 0x3
    u8 processFlag;  // at 0x4
    u8 loopCount;    // at 0x5
    u16 randomSeed;  // at 0x6
    u16 frameLength; // at 0x8
    u16 PADDING_0xA; // at 0xA
    u32 keyTable;    // at 0xC
    u32 rangeTable;  // at 0x10
    u32 randomTable; // at 0x14
    u32 nameTable;   // at 0x18
    u32 infoTable;   // at 0x1C
};

struct AnimCurveKey {
    u16 count;       // at 0x0
    u16 PADDING_0x2; // at 0x2
    u8 datas[1];     // at 0x4
};

struct AnimCurveRandom {
    u16 count;       // at 0x0
    u16 PADDING_0x2; // at 0x2
    u8 datas[1];     // at 0x4
};

struct AnimCurveRandomTable {
    u16 count;       // at 0x0
    u16 PADDING_0x2; // at 0x2
    u8 datas[1];     // at 0x4
};

struct AnimCurveNameTable {
    struct Name {
        u32 work; // at 0x0
    };

    u16 count;       // at 0x0
    u16 PADDING_0x2; // at 0x2
    Name datas[1];   // at 0x4
};

class ResAnimCurve {
private:
    u8* mAnimCurveData; // at 0x0
};

} // namespace ef
} // namespace nw4r

#endif
