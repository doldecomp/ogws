#include <types.h>
#include <Pack/RPKernel.h>

namespace Bowling {

struct RPGrpModelPair {
    // total size: 0x8
    RPGrpModel* pRealModel;        // offset 0x0, size 0x4
    RPGrpModel* pReflectionModel;  // offset 0x4, size 0x4
};

class RPBowActiveBall {
public:
    // total size: 0x88
    virtual ~RPBowActiveBall();          // offset 0x0, size 0x4

    RPGrpModelPair models[8];            // offset 0x4, size 0x40
    nw4r::math::MTX34 mtx;               // offset 0x44, size 0x30
    f32 field_0x74;                      // offset 0x74, size 0x4
    u32 index;                           // offset 0x78, size 0x4
    f32 alpha;                           // offset 0x7C, size 0x4
    RPGrpShadowTexture* pShadowTexture;  // offset 0x80, size 0x4
    BOOL disableShadow;                  // offset 0x84, size 0x4

    void ResetRenderState();
    void RenderModelSet();
};

struct PhysicsBody {
    // total size: 0xFC

    virtual void VF_0x00();  // vtable index 0 (offset 0x0)
    virtual void VF_0x04();  // vtable index 1 (offset 0x4)
    virtual void VF_0x08();  // vtable index 2 (offset 0x8)
    virtual void VF_0x0C();  // vtable index 3 (offset 0xC)

    nw4r::math::VEC3 position;            // offset 0x04, size 0x4
    nw4r::math::VEC3 linearVelocity;      // offset 0x10, size 0x4
    nw4r::math::VEC3 previousPosition;    // offset 0x1C, size 0x4

    nw4r::math::VEC3 minPositionDelta;    // offset 0x28, size 0x4
    nw4r::math::VEC3 maxPositionDelta;    // offset 0x34, size 0x4

    nw4r::math::VEC3 minVelocityDelta;    // offset 0x40, size 0x4
    nw4r::math::VEC3 maxVelocityDelta;    // offset 0x4C, size 0x4

    f32 linearDamping;                    // offset 0x58, size 0x4

    nw4r::math::VEC3 basisX;              // offset 0x5C, size 0x4
    nw4r::math::VEC3 basisY;              // offset 0x68, size 0x4
    nw4r::math::VEC3 basisZ;              // offset 0x74, size 0x4

    nw4r::math::VEC3 angularVelXY;        // offset 0x80, size 0x4
    nw4r::math::VEC3 angularVelYZ;        // offset 0x8C, size 0x4
    nw4r::math::VEC3 angularVelZX;        // offset 0x98, size 0x4

    nw4r::math::VEC3 minAngularDeltaXY;   // offset 0xA4, size 0x4
    nw4r::math::VEC3 maxAngularDeltaXY;   // offset 0xB0, size 0x4

    nw4r::math::VEC3 minAngularDeltaYZ;   // offset 0xBC, size 0x4
    nw4r::math::VEC3 maxAngularDeltaYZ;   // offset 0xC8, size 0x4

    nw4r::math::VEC3 minAngularDeltaZX;   // offset 0xD4, size 0x4
    nw4r::math::VEC3 maxAngularDeltaZX;   // offset 0xE0, size 0x4

    f32 angularDamping;                   // offset 0xEC, size 0x4
    f32 angularResponseScale;             // offset 0xF0, size 0x4
    f32 interactionRadius;                // offset 0xF4, size 0x4

    u8 flags;                             // offset 0xF8, size 0x1
    u8 pad_F9[0x3];                       // offset 0xF9, size 0x3
};

struct PinSubVecs {
    // total size: 0x1C
    nw4r::math::VEC3 vec1;  // offset 0x0, size 0xC
    nw4r::math::VEC3 vec2;  // offset 0xC, size 0xC
    float field_0x18;       // offset 0x18, size 0x4
};

struct PinPhysicsBody : public PhysicsBody {
    // total size: 0x2C0
    // PhysicsBody                  // offset 0x0, size 0xFC
    nw4r::math::VEC3 field_0xFC;    // offset 0xFC, size 0xC
    nw4r::math::VEC3 unkVec_0x108;  // offset 0x108, size 0xC
    nw4r::math::VEC3 unkVec_0x114;  // offset 0x114, size 0xC
    nw4r::math::VEC3 unkVec_0x120;  // offset 0x120, size 0xC
    nw4r::math::VEC3 unkVec_0x12C;  // offset 0x12C, size 0xC
    nw4r::math::VEC3 unkVec_0x138;  // offset 0x138, size 0xC
    nw4r::math::VEC3 unkVec_0x144;  // offset 0x144, size 0xC
    nw4r::math::VEC3 unkVec_0x150;  // offset 0x150, size 0xC
    nw4r::math::VEC3 unkVec_0x15C;  // offset 0x15C, size 0xC
    float field_0x168;              // offset 0x168, size 0x4
    float field_0x16C;              // offset 0x16C, size 0x4
    PinSubVecs pinVecs[8];          // offset 0x170, size 0xE0
    u8 unkFlag_0x250;               // offset 0x250, size 0x1
    u8 isActive;                    // offset 0x251, size 0x1
    u8 pad_0x252[0x2];              // offset 0x252, size 0x2
    void* unkPtr_0x254;             // offset 0x254, size 0x4
    void* unkPtr_0x258;             // offset 0x258, size 0x4
    void* unkPtr_0x25C;             // offset 0x25C, size 0x4
    void* unkPtr_0x260;             // offset 0x260, size 0x4
    f32 field_0x264;                // offset 0x264, size 0x4
    f32 field_0x268;                // offset 0x268, size 0x4
    f32 field_0x26C;                // offset 0x26C, size 0x4
    f32 field_0x270;                // offset 0x270, size 0x4
    f32 field_0x274;                // offset 0x274, size 0x4
    f32 field_0x278;                // offset 0x278, size 0x4
    f32 field_0x27C;                // offset 0x27C, size 0x4
    f32 field_0x280;                // offset 0x280, size 0x4
    f32 field_0x284;                // offset 0x284, size 0x4
    f32 field_0x288;                // offset 0x288, size 0x4
    int mode_0x28C;                 // offset 0x28C, size 0x4
    u8 flag_0x290;                  // offset 0x290, size 0x1
    u8 pad_0x291[0x3];              // offset 0x291, size 0x3
    f32 field_0x294;                // offset 0x294, size 0x4
    void* unkPtr_0x298;             // offset 0x298, size 0x4
    u8 flag_0x29C;                  // offset 0x29C, size 0x1
    u8 pad_0x29D[0x3];              // offset 0x29D, size 0x3
    void* unkPtr_0x2A0;             // offset 0x2A0, size 0x4
    int unkCounter_0x2A4;           // offset 0x2A4, size 0x4
    void* field_0x2A8;              // offset 0x2A8, size 0x4
    int unkCounter_0x2AC;           // offset 0x2AC, size 0x4
    f32 field_0x2B0;                // offset 0x2B0, size 0x4
    f32 field_0x2B4;                // offset 0x2B4, size 0x4
    f32 field_0x2B8;                // offset 0x2B8, size 0x4
    f32 field_0x2BC;                // offset 0x2BC, size 0x4
};

// Rack index order for PinManager's pPinBodies
//  [6] [7] [8] [9]
//    [3] [4] [5]
//      [1] [2]
//        [0]

struct PinManager {
    PinPhysicsBody* pPinBodies[10];  // offset 0x0, size 0x28
};

struct BvhEntryHeader {
    // total size: 0x40
    u32 pEntry;    // offset 0x0, size 0x4
    u32 child[4];  // offset 0x4, size 0x10
    f32 field_14;  // offset 0x14, size 0x4
    u32 field_18;  // offset 0x18, size 0x4
    u32 field_1C;  // offset 0x1C, size 0x4
    u32 field_20;  // offset 0x20, size 0x4
    u32 field_24;  // offset 0x24, size 0x4
    u32 field_28;  // offset 0x28, size 0x4
    u32 field_2C;  // offset 0x2C, size 0x4
    u32 field_30;  // offset 0x30, size 0x4
    u32 field_34;  // offset 0x34, size 0x4
    u32 field_38;  // offset 0x38, size 0x4
    f32 field_3C;  // offset 0x3C, size 0x4

    BvhEntryHeader() {
        pEntry = 0;
    }
};

struct LaneBvhData {
    // total size: 0x18
    float field_0x0;        // offset 0x0, size 0x4
    float field_0x4;        // offset 0x4, size 0x4
    float field_0x8;        // offset 0x8, size 0x4
    float field_0xC;        // offset 0xC, size 0x4
    float field_0x10;       // offset 0x10, size 0x4
    float field_0x14;       // offset 0x14, size 0x4
    BvhEntryHeader* pObj1;  // offset 0x18, size 0x4
    BvhEntryHeader* pObj2;  // offset 0x1C, size 0x4
};

struct PinSetter {
    // total size: 0x4C
    void* vtable;       // offset 0x0, size 0x4
    void* field_04;     // offset 0x4, size 0x4
    void* field_08;     // offset 0x8, size 0x4
    float field_0C;     // offset 0xC, size 0x4
    u8 pad_10[0x8];     // offset 0x10, size 0x8
    float positionX;    // offset 0x18, size 0x4
    u8 pad_1c[0x4];     // offset 0x1C, size 0x4
    float field_20;     // offset 0x20, size 0x4
    u8 pad_24[0x10];    // offset 0x24, size 0x10
    float field_34;     // offset 0x34, size 0x4
    float positionZ;    // offset 0x38, size 0x4
    int primaryState;   // offset 0x3C, size 0x4
    int sequencePhase;  // offset 0x40, size 0x4
    float field_44;     // offset 0x44, size 0x4
    float frameTimer;   // offset 0x48, size 0x4
};

struct ThrowContext {
    // total size: 0x108
    int throwState;             // offset 0x0, size 0x4
    nw4r::math::MTX34 ballMtx;  // offset 0x4, size 0x30
    u8 pad_0x34[0x2C];          // offset 0x34, size 0x2C
    float field_0x60;           // offset 0x60, size 0x4
    u8 pad_0x64[0x18];          // offset 0x64, size 0x18
    float field_0x7C;           // offset 0x7C, size 0x4
    void* unkPtr_0x80;          // offset 0x80, size 0x4
    float field_0x84;           // offset 0x84, size 0x4
    float field_0x88;           // offset 0x88, size 0x4
    float field_0x8C;           // offset 0x8C, size 0x4
    u8 pad_0x90[0x4];           // offset 0x90, size 0x4
    float field_0x94;           // offset 0x94, size 0x4
    float field_0x98;           // offset 0x98, size 0x4
    u8 pad_0x9C[0x4];           // offset 0x9C, size 0x4
    u8 flag_0xA0;               // offset 0xA0, size 0x1
    u8 pad_0xA1[0x3];           // offset 0xA1, size 0x3
    float field_0xA4;           // offset 0xA4, size 0x4
    u8 flag_0xA8;               // offset 0xA8, size 0x1
    u8 flag_0xA9;               // offset 0xA9, size 0x1
    u8 isGutterBall;            // offset 0xAA, size 0x1
    u8 flag_0xAB;               // offset 0xAB, size 0x1
    u8 pad_0xAC[0x14];          // offset 0xAC, size 0x14
    int animationMode;          // offset 0xC0, size 0x4
    u8 pad_0xC4[0x40];          // offset 0xC4, size 0x40
    int field_0x104;            // offset 0x104, size 0x4
};

struct PinStatus {
    // total size: 0x14
    u32 pinBits[4];  // 0x0, Bitmask where each bit represents a pin (0=down, 1=standing)
    s32 pinCount;    // 0x10

    int GetStandingPinCount() const {
        int count = 0;
        for (int i = 0; i < pinCount; ++i) {
            if (pinBits[i / 30] & (1 << (i % 30))) {
                count++;
            }
        }
        return count;
    }
};

struct PinSetterAnimation {
    // total size: 0x10
    int sequenceFrameCount;  // offset 0x0, size 0x4
    float animOffsetZ;       // offset 0x4, size 0x4
    float animRotationY;     // offset 0x8, size 0x4
    u8 isNewRack;            // offset 0xC, size 0x1
    u8 pad_2025;             // offset 0xD, size 0x1
    u8 pad_2026;             // offset 0xE, size 0x1
    u8 pad_2027;             // offset 0xF, size 0x1
};


struct LaneContext {
    // total size: 0x2080
    // void* vtable;                    // offset 0x0, size 0x4

    virtual void VF_0x00(); // at 0x0
    virtual void VF_0x04(); // at 0x4
    virtual void VF_0x08(); // at 0x8
    virtual void VF_0x0C(); // at 0xC
    virtual void VF_0x10(); // at 0x10
    virtual void VF_0x14(); // at 0x14

    PinManager* pPinManager;         // offset 0x4, size 0x4
    LaneBvhData* pLaneBvhData;       // offset 0x8, size 0x4
    PinSetter* pPinSetter;           // offset 0xC, size 0x4
    void* unkPtr_0x10;               // offset 0x10, size 0x4
    int pinCount;                    // offset 0x14, size 0x4
    void* unkPtr_0x18;               // offset 0x18, size 0x4
    void* unkPtr_0x1C;               // offset 0x1C, size 0x4
    u8 pad_0x20[0x1EA0];             // offset 0x20, size 0x1EA0
    int field_1EC0;                  // offset 0x1EC0, size 0x4
    int field_1EC4;                  // offset 0x1EC4, size 0x4
    u8 pad_0x1EC8[0x18];             // offset 0x1EC8, size 0x18
    int field_1EE0;                  // offset 0x1EE0, size 0x4
    int field_1EE4;                  // offset 0x1EE4, size 0x4
    float field_0x1EE8;              // offset 0x1EE8, size 0x4
    float field_0x1EEC;              // offset 0x1EEC, size 0x4
    float field_0x1EF0;              // offset 0x1EF0, size 0x4
    int field_1EF4;                  // offset 0x1EF4, size 0x4
    ThrowContext throwContext;       // offset 0x1EF8, size 0x108
    PinStatus pinStatus;             // offset 0x2000, size 0x4
    float laneXOffset;               // offset 0x2014, size 0x4
    PinSetterAnimation setterAnm;    // offset 0x2018, size 0x10
    u32 field_0x2028;                // offset 0x2028, size 0x4
    void* unkPtr_0x202C;             // offset 0x202C, size 0x4
    void* unkPtr_0x2030;             // offset 0x2030, size 0x4
    void* unkPtr_0x2034;             // offset 0x2034, size 0x4
    void* unkPtr_0x2038;             // offset 0x2038, size 0x4
    void* unkPtr_0x203C;             // offset 0x203C, size 0x4
    void* unkPtr_0x2040;             // offset 0x2040, size 0x4
    void* unkPtr_0x2044;             // offset 0x2044, size 0x4
    void* unkPtr_0x2048;             // offset 0x2048, size 0x4
    void* unkPtr_0x204C;             // offset 0x204C, size 0x4
    void* unkPtr_0x2050;             // offset 0x2050, size 0x4
    void* unkPtr_0x2054;             // offset 0x2054, size 0x4
    void* unkPtr_0x2058;             // offset 0x2058, size 0x4
    void* unkPtr_0x205C;             // offset 0x205C, size 0x4
    void* unkPtr_0x2060;             // offset 0x2060, size 0x4
    void* unkPtr_0x2064;             // offset 0x2064, size 0x4
    void* unkPtr_0x2068;             // offset 0x2068, size 0x4
    void* unkPtr_0x206C;             // offset 0x206C, size 0x4
    bool flag_0x2070;                // offset 0x2070, size 0x1
    u8 pad_0x2071[0x3];              // offset 0x2071, size 0x3
    float field_0x2074;              // offset 0x2074, size 0x4
    bool flag_0x2078;                // offset 0x2078, size 0x1
    u8 pad_0x2079[0x3];              // offset 0x2079, size 0x3
    int laneStateTarget;             // offset 0x207C, size 0x4
};

struct SomeUnkManager0 {
    // total size: 0x30
    void* vtable;       // offset 0x0, size 0x4
    void* unkPtr_0x4;   // offset 0x4, size 0x4
    void* unkPtr_0x8;   // offset 0x8, size 0x4
    void* unkPtr_0xC;   // offset 0xC, size 0x4
    void* unkPtr_0x10;  // offset 0x10, size 0x4
    void* arr[7];       // offset 0x14, size 0x1C
};

struct SubNpcLaneData {
    // total size: 0x5C
    u32 field_0x0;     // offset 0x0, size 0x4
    int counter_0x4;   // offset 0x4, size 0x4
    float field_0x8;   // offset 0x8, size 0x4
    u8 pad_0xC[0x4];   // offset 0xC, size 0x4
    float field_0x10;  // offset 0x10, size 0x4
    float field_0x14;  // offset 0x14, size 0x4
    float field_0x18;  // offset 0x18, size 0x4
    float field_0x1C;  // offset 0x1C, size 0x4
    float field_0x20;  // offset 0x20, size 0x4
    float field_0x24;  // offset 0x24, size 0x4
    float field_0x28;  // offset 0x28, size 0x4
    u8 pad_0x2C[0x4];  // offset 0x2C, size 0x4
    u8 pad_0x30[0x4];  // offset 0x30, size 0x4
    float field_0x34;  // offset 0x34, size 0x4
    u8 pad_0x38[0x4];  // offset 0x38, size 0x4
    u8 pad_0x3C[0x4];  // offset 0x3C, size 0x4
    float field_0x40;  // offset 0x40, size 0x4
    u8 pad_0x44[0x4];  // offset 0x44, size 0x4
    float field_0x48;  // offset 0x48, size 0x4
    u8 pad_0x4C[0x4];  // offset 0x4C, size 0x4
    u8 pad_0x50[0x4];  // offset 0x50, size 0x4
    u8 flag_0x54;      // offset 0x54, size 0x1
    u8 flag_0x55;      // offset 0x55, size 0x1
    u8 flag_0x56;      // offset 0x56, size 0x1
    u8 flag_0x57;      // offset 0x57, size 0x1
    int field_0x58;    // offset 0x58, size 0x4
};

struct NpcModelGroup {
    // total size: 0xB4
    void* vtable;          // offset 0x0, size 0x4
    u8 pad_00[0xA0];       // offset 0x4, size 0xA0
    RPGrpModel* mModelA4;  // offset 0xA4, size 0x4
    RPGrpModel* mModelA8;  // offset 0xA8, size 0x4
    RPGrpModel* mModelAC;  // offset 0xAC, size 0x4
    RPGrpModel* mModelB0;  // offset 0xB0, size 0x4
};

struct ModelGroupPair {
    // total size: 0x8
    NpcModelGroup* groupA;  // offset 0x0, size 0x4
    NpcModelGroup* groupB;  // offset 0x4, size 0x4
};

struct NpcLaneDataHolder {
    // total size: 0x130
    void* vtable;                // offset 0x0, size 0x4
    void* unkPtr_0x04;           // offset 0x4, size 0x4
    u32 field_0x08;              // offset 0x8, size 0x4
    float field_0x0C;            // offset 0xC, size 0x4
    float field_0x10;            // offset 0x10, size 0x4
    float field_0x14;            // offset 0x14, size 0x4
    float field_0x18;            // offset 0x18, size 0x4
    float field_0x1C;            // offset 0x1C, size 0x4
    float field_0x20;            // offset 0x20, size 0x4
    float field_0x24;            // offset 0x24, size 0x4
    float field_0x28;            // offset 0x28, size 0x4
    float field_0x2C;            // offset 0x2C, size 0x4
    SubNpcLaneData subData;      // offset 0x30, size 0x5C
    ModelGroupPair groups[4];    // offset 0x8C, size 0x20
    u16 field_0xAC;              // offset 0xAC, size 0x2
    u16 field_0xAE;              // offset 0xAE, size 0x2
    float field_0xB0;            // offset 0xB0, size 0x4
    float field_0xB4;            // offset 0xB4, size 0x4
    u16 field_0xB8;              // offset 0xB8, size 0x2
    u16 field_0xBA;              // offset 0xBA, size 0x2
    float field_0xBC;            // offset 0xBC, size 0x4
    float field_0xC0;            // offset 0xC0, size 0x4
    float field_0xC4;            // offset 0xC4, size 0x4
    float field_0xC8;            // offset 0xC8, size 0x4
    float field_0xCC;            // offset 0xCC, size 0x4
    float field_0xD0;            // offset 0xD0, size 0x4
    u16 field_0xD4;              // offset 0xD4, size 0x2
    u16 field_0xD6;              // offset 0xD6, size 0x2
    u16 field_0xD8;              // offset 0xD8, size 0x2
    u8 pad_0xDA[0x2];            // offset 0xDA, size 0x2
    nw4r::math::VEC3 vec_0xDC;   // offset 0xDC, size 0xC
    float field_0xE8;            // offset 0xE8, size 0x4
    float field_0xEC;            // offset 0xEC, size 0x4
    u8 flags[0x4];               // offset 0xF0, size 0x4
    void* unkPtr_0xF4;           // offset 0xF4, size 0x4
    float field_0xF8;            // offset 0xF8, size 0x4
    float field_0xFC;            // offset 0xFC, size 0x4
    float field_0x100;           // offset 0x100, size 0x4
    float field_0x104;           // offset 0x104, size 0x4
    float field_0x108;           // offset 0x108, size 0x4
    float field_0x10C;           // offset 0x10C, size 0x4
    float field_0x110;           // offset 0x110, size 0x4
    float field_0x114;           // offset 0x114, size 0x4
    RPGrpModel* unkModel_0x118;  // offset 0x118, size 0x4
    float field_0x11C;           // offset 0x11C, size 0x4
    void* field_0x120[0x4];      // offset 0x120, size 0x10
};

class RPBowTrajectoryGuide : public RP_DEBUG_STUB_1 {
public:
    // total size: 0x6C
    virtual ~RPBowTrajectoryGuide();  // offset 0x0, size 0x4
    RPGrpModel* mpMainModel;          // offset 0x4, size 0x4
    RPGrpModel* mpUnkModel;           // offset 0x8, size 0x4
    RPGrpModel* mpDotModels[16];      // offset 0xC, size 0x40
    u32 mActiveModelIndex;            // offset 0x4C, size 0x4
    u8 mIsVisible;                    // offset 0x50, size 0x1
    u8 pad51[3];                      // offset 0x51, size 0x3
    f32 mStartX;                      // offset 0x54, size 0x4
    f32 mAngle;                       // offset 0x58, size 0x4
    f32 unk_0x5C;                     // offset 0x5C, size 0x4
    u32 unk_0x60;                     // offset 0x60, size 0x4
    f32 mLimitCenter;                 // offset 0x64, size 0x4
    f32 mLimitWidth;                  // offset 0x68, size 0x4

    void SetMainModels(RPGrpModel* pMainModel, RPGrpModel* pUnkModel);
    void SetDotModel(u32 index, RPGrpModel* pDotModel);
    void Initialize();
    void Reset();
    void Draw();
};

struct NpcIdleStateSub {
    // total size: 0x3C
    int idleState;           // offset 0x0, size 0x4
    int frameCounter;        // offset 0x4, size 0x4
    int unk_0x8;             // offset 0x8, size 0x4
    float targetRotation;    // offset 0xC, size 0x4
    float rotationSpeed;     // offset 0x10, size 0x4
    nw4r::math::VEC3 pos;    // offset 0x14, size 0xC
    s32 bouncesRemaining;    // offset 0x20, size 0x4
    float bounceVelocity;    // offset 0x24, size 0x4
    s32 unk_countdown_0x28;  // offset 0x28, size 0x4
    u8 field_0x2C;           // offset 0x2C, size 0x1
    u8 pad_0x2D[3];          // offset 0x2D, size 0x3
    float field_0x30;        // offset 0x30, size 0x4
    float field_0x34;        // offset 0x34, size 0x4
    u8 field_0x38;           // offset 0x38, size 0x1
    u8 pad_0x39[3];          // offset 0x39, size 0x3
};

struct NpcIdleState {
    // total size: 0x48
    void* vtable;         // offset 0x0, size 0x4
    int unk_0x04;         // offset 0x4, size 0x4
    int unk_0x08;         // offset 0x8, size 0x4
    NpcIdleStateSub sub;  // offset 0xC, size 0x3C
};

enum NpcStates {
    NPC_STATE_IDLE = 0,                   // Idle state
    NPC_STATE_WALK_TO_APPROACH_AREA = 1,  // Walking to approach area
    NPC_STATE_UNUSED_2 = 2,               // Unused
    NPC_STATE_BOWL = 3,                   // Bowling action
    NPC_STATE_WALK_TO_BALL_RETURN = 4,    // Walking to ball return
    NPC_STATE_WALK_BACK_TO_SEAT = 5,      // Walking back to seat
};

struct NpcMovementState {
    // total size: 0x1C
    void* vtable;                     // offset 0x0, size 0x4
    s32 laneIdx;                      // offset 0x4, size 0x4
    s32 npcIdx;                       // offset 0x8, size 0x4
    u8 isMovementComplete;            // offset 0xC, size 0x1
    u8 pad0D[3];                      // offset 0xD, size 0x3
    nw4r::math::VEC3 returnStartPos;  // offset 0x10, size 0xC
};

struct NpcContext {
    // total size: 0xA8
    void* vtable;                     // offset 0x0, size 0x4
    RPSysKokeshi* mpKokeshi;          // offset 0x4, size 0x4
    void* field_0x8;                  // offset 0x8, size 0x4
    void* field_0xC;                  // offset 0xC, size 0x4
    nw4r::math::VEC3 pos_0x10;        // offset 0x10, size 0xC
    nw4r::math::VEC3 rot_0x1C;        // offset 0x1C, size 0xC
    float field_0x28;                 // offset 0x28, size 0x4
    u8 pad_0x2C[0x4];                 // offset 0x2C, size 0x4
    NpcStates npcState;               // offset 0x30, size 0x4
    int stateFrameCounter;            // offset 0x34, size 0x4
    u8 triggerThrow;                  // offset 0x38, size 0x1
    u8 triggerTransition;             // offset 0x39, size 0x1
    u8 pad_0x3A[0x2];                 // offset 0x3A, size 0x2
    s32 field_0x3A;                   // offset 0x3C, size 0x4
    float targetZPos;                 // offset 0x40, size 0x4
    u8 field_0x44;                    // offset 0x44, size 0x1
    u8 pad_0x45[3];                   // offset 0x45, size 0x3
    NpcMovementState* movementState;  // offset 0x48, size 0x4
    int field_0x4C;                   // offset 0x4C, size 0x4, 0 = Walk to approach area, 1 = Idle at approach area, 2 = Bowl, 3 = Watch ball, 4 = Turn around, 5 = Walk to ball return or seat from approach area, 6 = Idle, 7 = Walk to ball return from seat
    u8 isHoldingBall;                 // offset 0x50, size 0x1
    u8 flag_51;                       // offset 0x51, size 0x1
    u8 flag_52;                       // offset 0x52, size 0x1
    u8 flag_53;                       // offset 0x53, size 0x1
    int laneIdx;                      // offset 0x54, size 0x4
    int npcIdx;                       // offset 0x58, size 0x4
    NpcIdleState subStruct;           // offset 0x5C, size 0x48
    u8 pad_0xA4[0x1];                 // offset 0xA4, size 0x1
    u8 flag_A5;                       // offset 0xA5, size 0x1
    u8 pad_0xA6[0x2];                 // offset 0xA6, size 0x2
};

class RPBowPlayerLaneNpc : public RP_DEBUG_STUB_1 {
public:
    // total size: 0x78
    virtual ~RPBowPlayerLaneNpc();  // offset 0x0, size 0x4
    void* unkPtr_0x4;               // offset 0x4, size 0x4
    RPSysKokeshi* mKokeshis[2];     // offset 0x8, size 0x8
    u32 index;                      // offset 0x10, size 0x4
    nw4r::math::VEC3 pos;           // offset 0x14, size 0xC
    nw4r::math::VEC3 rot;           // offset 0x20, size 0xC
    u8 isVisible;                   // offset 0x2C, size 0x1
    u8 pad_0x2D[0x3];               // offset 0x2D, size 0x3
    NpcIdleState npcIdleState;      // offset 0x30, size 0x48

    void Init(RPSysKokeshi* kokeshi1, RPSysKokeshi* kokeshi2, int index);
    void SetSeatPosition();
    void HideActiveBowler();
    void UpdateModels();
};

struct BallReturnBall {
    // total size: 0x28
    nw4r::math::VEC3 mPos;        // offset 0x0, size 0xC
    nw4r::math::VEC3 unkVec_0xC;  // offset 0xC, size 0xC
    float mSpeed;                 // offset 0x18, size 0x4
    float mAngle;                 // offset 0x1C, size 0x4
    float mRepulsionForce;        // offset 0x20, size 0x4
    bool mClaimedByNPC;           // offset 0x24, size 0x1
    bool mIsOnRack;               // offset 0x25, size 0x1
    char pad_0x26[0x2];           // offset 0x26, size 0x2
};

class RPBowBallReturnRack {
public:
    // total size: 0xDC
    RPGrpModelPair mModels[4];    // offset 0x0, size 0x20
    void* unkPtr_0x20;            // offset 0x20, size 0x4
    void* unkPtr_0x24;            // offset 0x24, size 0x4
    s32 mSlotIndices[4];          // offset 0x28, size 0x10
    int mRackIndex;               // offset 0x38, size 0x4
    BallReturnBall mBalls[4];     // offset 0x3C, size 0xA0 (Order: Blue, Red, Green, Yellow)

    void InitBallReturnRack(s32 index);
    void InitBallSlotResources(s32 index, RPGrpModel* realModel, RPGrpModel* reflectionModel, s32 slotIndex);
    void ResetRackBallStates();
    int SelectBallForNPC();
    void RemoveBallFromRack(s32 index);
    u8 IsBallOnRack(s32 index);
    void SpawnBallOnRack(s32 index);
    void ReleaseBallFromNPC(s32 index);
    s32 GetBallSlotIndex(s32 index);
    void UpdateBallReturnRack(s32 index);
};

struct BackgroundNpcMovement {
    // total size: 0x30
    nw4r::math::VEC3 position;  // offset 0x0, size 0xC
    nw4r::math::VEC3 rotation;  // offset 0xC, size 0xC
    nw4r::math::VEC3 velocity;  // offset 0x18, size 0xC
    int behaviorState;          // offset 0x24, size 0x4
    int stateTimer;             // offset 0x28, size 0x4
    int animationState;         // offset 0x2C, size 0x4
};

class RPBowBackgroundNpcManager : public RP_DEBUG_STUB_1 {
public:
    // total size: 0x9C
    virtual ~RPBowBackgroundNpcManager();  // offset 0x0, size 0x4
    void* unkPtr_0x04;                     // offset 0x4, size 0x4
    BackgroundNpcMovement mMovement;       // offset 0x8, size 0x30
    NpcModelGroup* mModelGroups[2][2];     // offset 0x38, size 0x10
    int mConfigIndex;                      // offset 0x48, size 0x4
    NpcIdleState mIdleState;               // offset 0x4C, size 0x48
    bool unk_0x94;                         // offset 0x94, size 0x1
    u8 pad_0x95[3];                        // offset 0x95, size 0x3
    s32 mModelGroupSet;                    // offset 0x98, size 0x4

    void fn_8034E96C();
    void InitializeConfig(int index);
    void SetModelGroups(int managerIndex, NpcModelGroup* modelGroup0, NpcModelGroup* modelGroup1);
    void fn_8034E83C();
    void Reset();
    void UpdateMovement(nw4r::math::VEC3* outPosition, bool* outStateFlag);
    void Render();
    void fn_8034DD14();
    void fn_8034DD0C();
    void fn_8034DD08();
};

struct SceneEntities {
    // total size: 0x1E0
    void* unkPtr_0x04;                             // offset 0x0, size 0x4
    NpcLaneDataHolder* npcLaneData;                // offset 0x4, size 0x4
    RPBowTrajectoryGuide* trajectoryGuide;         // offset 0x8, size 0x4
    void* unkPtr_0x10;                             // offset 0xC, size 0x4
    void* unkPtr_0x14;                             // offset 0x10, size 0x4
    void* unkPtr_0x18;                             // offset 0x14, size 0x4
    void* unkPtr_0x1C;                             // offset 0x18, size 0x4
    void* unkPtr_0x20;                             // offset 0x1C, size 0x4
    void* unkPtr_0x24;                             // offset 0x20, size 0x4
    void* unkPtr_0x28;                             // offset 0x24, size 0x4
    void* unkPtr_0x2C;                             // offset 0x28, size 0x4
    RPBowActiveBall* balls[7];                     // offset 0x2C, size 0x1C
    NpcContext* npcs[18];                          // offset 0x48, size 0x48
    RPBowPlayerLaneNpc* playerLaneNpcs[4];         // offset 0x90, size 0x10
    PinSetter* setters[7];                         // offset 0xA0, size 0x1C
    void* unkPtrs2[64];                            // offset 0xBC, size 0x100
    RPBowBallReturnRack* ballReturns[4];           // offset 0x1BC, size 0x10
    RPBowBackgroundNpcManager* BackgroundNpcs[4];  // offset 0x1CC, size 0x10
    void* unkPtr_0x1E0;                            // offset 0x1DC, size 0x4
};

struct SceneObjectManager {
    // total size: 0x218
    void* vtable;            // offset 0x0, size 0x4
    SceneEntities entities;  // offset 0x4, size 0x1E0
    u8 field_0x1E4;          // offset 0x1E4, size 0x1
    u8 pad_0x1E5;            // offset 0x1E5, size 0x1
    u8 field_0x1E6;          // offset 0x1E6, size 0x1
    u8 field_0x1E7;          // offset 0x1E7, size 0x1
    u8 field_0x1E8;          // offset 0x1E8, size 0x1
    u8 field_0x1E9;          // offset 0x1E9, size 0x1
    u8 field_0x1EA;          // offset 0x1EA, size 0x1
    u8 field_0x1EB;          // offset 0x1EB, size 0x1
    void* unkPtr_0x1EC;      // offset 0x1EC, size 0x4
    u8 isComplete;           // offset 0x1F0, size 0x1
    u8 field_0x1F1;          // offset 0x1F1, size 0x1
    u8 field_0x1F2;          // offset 0x1F2, size 0x1
    u8 field_0x1F3;          // offset 0x1F3, size 0x1
    u8 field_0x1F4;          // offset 0x1F4, size 0x1
    u8 pad_0x1F5[0x3];       // offset 0x1F5, size 0x3
    void* unkPtr_0x1F8;      // offset 0x1F8, size 0x4
    void* unkPtr_0x1FC;      // offset 0x1FC, size 0x4
    void* unkPtr_0x200;      // offset 0x200, size 0x4
    u8 pad_0x204[0x4];       // offset 0x204, size 0x4
    void* obj208Data;        // offset 0x208, size 0x4
    void* field_0x20C;       // offset 0x20C, size 0x4
    float field_0x210;       // offset 0x210, size 0x4
    float field_0x214;       // offset 0x214, size 0x4
};

class RPBowGlobalLaneManager {
public:
    // total size: 0x24
    u8 pad_00[0x04];         // offset 0x0, size 0x4
    LaneContext* pLanes[7];  // offset 0x4, size 0x1C
    u8 isInitialized;        // offset 0x20, size 0x1
    u8 field_0x21;           // offset 0x21, size 0x1
    u8 pad_22[0x2];          // offset 0x22, size 0x2

    void InitializeBallManagerLanes();
    void SetupBallManagerLaneObjects(void* arg1, void* arg2);
    void ResetLanePinsAndAnimations();
    void SetLaneUnknownState(int value);
    void UpdateBallsPhysics();
    void TickNpcLanes();
    void UpdateLaneItems(int val, void* obj, SomeUnkManager0* someMgr, bool isPlayerTurn);
    void UpdateBallsMdl(SceneObjectManager* vballmgr);
};

class RPBowNpcManager: public IRPSysHostIOSocket {
public:
    // Total Size 0x58. See fn_80332B34
    // vtable                           // offset 0x0, size 0x4
    u32 pad_0x04;                       // offset 0x4, size 0x4
    int mStateId;                       // offset 0x8, size 0x4, 0 = Idle, 1 = Walk to approach area, 2 = Idle at approach area, 3 = Bowl, 4 = Watch ball, 5 = Walk to ball return or seat.
    int mStateTimer;                    // offset 0xC, size 0x4
    bool mHasReleasedBall;              // offset 0x10, size 0x1, Set to 1 the moment the first ball is thrown during a turn.
    bool mIsSecondThrow;                // offset 0x11, size 0x1, Set to 1 the moment the NPC walks up to the approach area on the second turn.
    bool mShouldReturnToSeat;           // offset 0x12, size 0x1, Set to 1 after the pins are knocked down and the NPC turns to walk back to their seat.
    u8 field_0x13;                      // offset 0x13, size 0x1
    LaneContext* mpLaneContext;         // offset 0x14, size 0x4
    NpcContext* mpNpcs[3];              // offset 0x18, size 0xC
    NpcContext* mpCurrentNpc;           // offset 0x24, size 0x4
    int mLaneIdx;                       // offset 0x28, size 0x4
    int mCurrentNpcIdx;                 // offset 0x2C, size 0x4
    PinStatus mPinStatus;               // offset 0x30, size 0x14
    void* mpSoundAudioMgr;              // offset 0x44, size 0x4
    bool mHasPlayedGutterSfx;           // offset 0x48, size 0x1
    u8 mDisableResultSfx;               // offset 0x49, size 0x1
    u8 field_0x4A;                      // offset 0x4A, size 0x1
    u8 field_0x4B;                      // offset 0x4B, size 0x1
    RPBowBallReturnRack* mpReturnRack;  // offset 0x4C, size 0x4
    s32 mActiveSubObjIdx;               // offset 0x50, size 0x4
    void* mpSomeAudioStruct;            // offset 0x54, size 0x4

    void InitAudioActors(int laneIdx);
    void Setup(LaneContext* pLaneContext, NpcContext* pNpc0, NpcContext* pNpc1, NpcContext* pNpc2, int laneIdx, RPBowBallReturnRack* pReturnRack, void* pAudioStruct);
    int IsLaneIdle();
    void SetStateFlag(u8 flag);
    void ActivateNpcTurn();
    void Update();
    void DebugPrintNpcState();

    inline RPBowNpcManager() {
        mPinStatus.pinBits[3] = -1;
        mPinStatus.pinBits[2] = -1;
        mPinStatus.pinBits[1] = -1;
        mPinStatus.pinBits[0] = -1;
        mPinStatus.pinCount = 10;
    }

    nw4r::math::MTX34 GetPinWorldMatrix(int pinIndex) const {
        if (pinIndex >= mpLaneContext->pinCount) {
            nw4r::math::MTX34 matrix;
            nw4r::math::MTX34Identity(&matrix);
            return matrix;
        } else {
            PinPhysicsBody* pinData = mpLaneContext->pPinManager->pPinBodies[pinIndex];
            return nw4r::math::MTX34(
                pinData->basisX.x, pinData->basisY.x, pinData->basisZ.x, pinData->position.x,
                pinData->basisX.y, pinData->basisY.y, pinData->basisZ.y, pinData->position.y,
                pinData->basisX.z, pinData->basisY.z, pinData->basisZ.z, pinData->position.z
            );
        }
    }
};

class RPBowManagerContext {
public:
    // total size: 0x34
    void* vtable;                    // offset 0x0, size 0x4
    RPBowNpcManager* mpManagers[6];  // offset 0x4, size 0x18
    int field_0x1C;                  // offset 0x1C, size 0x4
    u8 mIsEnabled;                   // offset 0x20, size 0x1
    u8 pad_0x24[7];                  // offset 0x21, size 0x7
    int field_0x28;                  // offset 0x28, size 0x4
    void* field_0x2C;                // offset 0x2C, size 0x4
    void* field_0x30;                // offset 0x30, size 0x4

    void Initialize();
    void LinkNpcLanes(RPBowGlobalLaneManager* laneManager, SceneObjectManager* sceneObjectManager);
    void SetNpcStateFlags(u8 flag);
    void UpdateNpcs();
    void DebugPrintStates();
};

class RPBowMotionBlur : public RP_DEBUG_STUB_1 {
public:
    // total size: 0xB4
    virtual ~RPBowMotionBlur();     // offset 0x0, size 0x4
    RPGrpModelPair models[3];       // offset 0x4, size 0x18
    nw4r::math::MTX34 blurMtxs[3];  // offset 0x1C, size 0x90
    bool isActive;                  // offset 0xAC, size 0x1
    u8 pad1[3];                     // offset 0xAD, size 0x3
    f32 speed;                      // offset 0xB0, size 0x4

    void SetBlurModels(RPGrpModel* pReal1, RPGrpModel* pReal2, RPGrpModel* pReal3, RPGrpModel* pRefl1, RPGrpModel* pRefl2, RPGrpModel* pRefl3);
    void DeactivateBlur();
    void UpdateBlurTransform(const nw4r::math::MTX34* pBaseMtx, f32 speed);
    void DrawBlur(void* pCullingCtx);
};

// Global Data:

struct BallReturnRackConstants {
    // total size: 0x3C
    nw4r::math::VEC3 mPositionOffsets[4];  // offset 0x0, size 0x30
    float mHeightLimit;                    // offset 0x30, size 0x4
    float mRepulsionThreshold;             // offset 0x34, size 0x4
    float mGravity;                        // offset 0x38, size 0x4
};

struct BowlingPhysicsData {
    // total size: 0x2D0
    u8 flag_00;          // offset 0x0, size 0x1
    u8 flag_01;          // offset 0x1, size 0x1
    u8 flag_02;          // offset 0x2, size 0x1
    u8 flag_03;          // offset 0x3, size 0x1
    u8 flag_04;          // offset 0x4, size 0x1
    u8 flag_05;          // offset 0x5, size 0x1
    u8 flag_06;          // offset 0x6, size 0x1
    u8 flag_07;          // offset 0x7, size 0x1
    f32 field_08;        // offset 0x8, size 0x4
    f32 field_0C;        // offset 0xC, size 0x4
    f32 field_10;        // offset 0x10, size 0x4
    f32 field_14;        // offset 0x14, size 0x4
    f32 field_18;        // offset 0x18, size 0x4
    f32 field_1C;        // offset 0x1C, size 0x4
    f32 field_20;        // offset 0x20, size 0x4
    f32 field_24;        // offset 0x24, size 0x4
    f32 field_28;        // offset 0x28, size 0x4
    f32 field_2C;        // offset 0x2C, size 0x4
    f32 field_30;        // offset 0x30, size 0x4
    f32 field_34;        // offset 0x34, size 0x4
    u8 pad_0x38[0x3C];   // offset 0x38, size 0x3C
    f32 field_74;        // offset 0x74, size 0x4
    f32 field_78;        // offset 0x78, size 0x4
    f32 field_7C;        // offset 0x7C, size 0x4
    f32 field_80;        // offset 0x80, size 0x4
    u8 pad_0x84[0x8];    // offset 0x84, size 0x8
    f32 field_8C;        // offset 0x8C, size 0x4
    f32 field_90;        // offset 0x90, size 0x4
    f32 field_94;        // offset 0x94, size 0x4
    u8 pad_0x98[0x70];   // offset 0x98, size 0x70
    f32 field_108;       // offset 0x108, size 0x4
    f32 field_10C;       // offset 0x10C, size 0x4
    f32 field_110;       // offset 0x110, size 0x4
    f32 field_114;       // offset 0x114, size 0x4
    f32 field_118;       // offset 0x118, size 0x4
    f32 field_11C;       // offset 0x11C, size 0x4
    u8 pad_0x120[0x8];   // offset 0x120, size 0x8
    f32 field_128;       // offset 0x128, size 0x4
    u8 pad_0x12C[0x2C];  // offset 0x12C, size 0x2C
    f32 field_158;       // offset 0x158, size 0x4
    u8 pad_0x15C[0x28];  // offset 0x15C, size 0x28
    f32 field_184;       // offset 0x184, size 0x4
    u8 pad_0x188[0x1C];  // offset 0x188, size 0x1C
    f32 field_1A4;       // offset 0x1A4, size 0x4
    u8 pad_0x1A8[0x1C];  // offset 0x1A8, size 0x1C
    f32 field_1C4;       // offset 0x1C4, size 0x4
    u8 pad_0x1C8[0x3C];  // offset 0x1C8, size 0x3C
    f32 field_204;       // offset 0x204, size 0x4
    f32 field_208;       // offset 0x208, size 0x4
    u8 pad_0x20C[0x60];  // offset 0x20C, size 0x60
    f32 floats[20];      // offset 0x26C, size 0x50
    f32 field_2BC;       // offset 0x2BC, size 0x4
    f32 field_2C0;       // offset 0x2C0, size 0x4
    f32 field_2C4;       // offset 0x2C4, size 0x4
    f32 field_2C8;       // offset 0x2C8, size 0x4
    f32 field_2CC;       // offset 0x2CC, size 0x4
};

struct BackgroundNpcConfig {
    // total size: 0x44
    float laneZPositions[4];         // offset 0x0, size 0x10
    float basePosY;                  // offset 0x10, size 0x4
    float seatedPosY;                // offset 0x14, size 0x4
    float mirroredModelZOffset;      // offset 0x18, size 0x4
    float patrolMinX;                // offset 0x1C, size 0x4
    float patrolMaxX;                // offset 0x20, size 0x4
    float minWalkSpeed;              // offset 0x24, size 0x4
    float maxWalkSpeed;              // offset 0x28, size 0x4
    u32 dormantToPatrolChanceDenom;  // offset 0x2C, size 0x4
    u32 patrolToIdleChanceDenom;     // offset 0x30, size 0x4
    u32 idleToPatrolChanceDenom;     // offset 0x34, size 0x4
    float turnLerpRate;              // offset 0x38, size 0x4
    float idleCenterZoneX;           // offset 0x3C, size 0x4
    u32 minStateDuration;            // offset 0x40, size 0x4
};

extern BallReturnRackConstants gBallReturnRackConstants;
extern BowlingPhysicsData gBowlingPhysicsData;

} // namespace Bowling
