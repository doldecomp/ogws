#include <types.h>
#include <Pack/RPKernel.h>

struct RPGrpModelPair {
    // total size: 0x8
    RPGrpModel* pRealModel;        // offset 0x0, size 0x4
    RPGrpModel* pReflectionModel;  // offset 0x4, size 0x4
};

class RPBowActiveBall : public RP_DEBUG_STUB_1 {
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

    void fn_8032ADF4(void);
    void SetModelSet(u32 index, RPGrpModel* modelA, RPGrpModel* modelB);
    void ResetRenderState();
    void RenderModelSet();
};

struct PhysicsBodyState {
    // total size: 0xF4

    nw4r::math::VEC3 position;           // offset 0x0, size 0xC
    nw4r::math::VEC3 linearVelocity;     // offset 0xC, size 0xC
    nw4r::math::VEC3 previousPosition;   // offset 0x18, size 0xC

    nw4r::math::VEC3 minPositionDelta;   // offset 0x24, size 0xC
    nw4r::math::VEC3 maxPositionDelta;   // offset 0x30, size 0xC

    nw4r::math::VEC3 minVelocityDelta;   // offset 0x3C, size 0xC
    nw4r::math::VEC3 maxVelocityDelta;   // offset 0x48, size 0xC

    f32 linearDamping;                   // offset 0x54, size 0x4

    nw4r::math::VEC3 basisX;             // offset 0x58, size 0xC
    nw4r::math::VEC3 basisY;             // offset 0x64, size 0xC
    nw4r::math::VEC3 basisZ;             // offset 0x70, size 0xC

    nw4r::math::VEC3 angularVelXY;       // offset 0x7C, size 0xC
    nw4r::math::VEC3 angularVelYZ;       // offset 0x88, size 0xC
    nw4r::math::VEC3 angularVelZX;       // offset 0x94, size 0xC

    nw4r::math::VEC3 minAngularDeltaXY;  // offset 0xA0, size 0xC
    nw4r::math::VEC3 maxAngularDeltaXY;  // offset 0xAC, size 0xC

    nw4r::math::VEC3 minAngularDeltaYZ;  // offset 0xB8, size 0xC
    nw4r::math::VEC3 maxAngularDeltaYZ;  // offset 0xC4, size 0xC

    nw4r::math::VEC3 minAngularDeltaZX;  // offset 0xD0, size 0xC
    nw4r::math::VEC3 maxAngularDeltaZX;  // offset 0xDC, size 0xC

    f32 angularDamping;                  // offset 0xE8, size 0x4
    f32 angularResponseScale;            // offset 0xEC, size 0x4
    f32 interactionRadius;               // offset 0xF0, size 0x4
};

struct PhysicsBody {
    // total size: 0xFC

    // first 0x8 bytes of vtable taken by rtti or something like that.
    virtual void VF_0x08();
    virtual void VF_0x0C();
    virtual void VF_0x10();
    virtual void VF_0x14();
    virtual void VF_0x18();

    PhysicsBodyState state;  // offset 0x4, size 0xF4
    u8 flags;                // offset 0xF8, size 0x1
    u8 pad_F9[0x3];          // offset 0xF9, size 0x3

    void fn_8032A81C();
    void fn_80329088(float, float, float, float);
};

struct PinSubVecs {
    // total size: 0x1C
    nw4r::math::VEC3 vec1;  // offset 0x0, size 0xC
    nw4r::math::VEC3 vec2;  // offset 0xC, size 0xC
    float field_0x18;       // offset 0x18, size 0x4
};

struct PinPhysicsBody : public PhysicsBody {
    // total size: 0x2B4
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

    PinPhysicsBody();
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

class RPBowPinSetterModel : public RP_DEBUG_STUB_1 {
public:
    // total size: 0x4C
    virtual ~RPBowPinSetterModel();

    RPGrpModel* mpModel[2];  // offset 0x4, size 0x8
    nw4r::math::MTX34 mMtx;  // offset 0xC, size 0x30
    int mPrimaryState;       // offset 0x3C, size 0x4
    int mSequencePhase;      // offset 0x40, size 0x4
    float mAngle;            // offset 0x44, size 0x4
    float mFrameTimer;       // offset 0x48, size 0x4

    void fn_80323790();

    void SetModels(RPGrpModel* pModel0, RPGrpModel* pModel1);
    void Reset();
    void SetOffsetXZ(f32 x, f32 z);
    void Calc();
};

struct ThrowContext {
    // total size: 0x108
    int throwState;             // offset 0x0, size 0x4
    nw4r::math::MTX34 ballMtx;  // offset 0x4, size 0x30
    u8 pad_0x34[0x24];          // offset 0x34, size 0x24
    u8 field_0x58;              // offset 0x58, size 0x1
    u8 pad_0x59[0x3];           // offset 0x59, size 0x3
    u8 pad_0x5C[0x4];           // offset 0x5C, size 0x4
    float field_0x60;           // offset 0x60, size 0x4
    u8 pad_0x64[0x18];          // offset 0x64, size 0x18
    float field_0x7C;           // offset 0x7C, size 0x4
    u32 field_0x80;             // offset 0x80, size 0x4
    float field_0x84;           // offset 0x84, size 0x4
    float field_0x88;           // offset 0x88, size 0x4
    float field_0x8C;           // offset 0x8C, size 0x4
    float field_0x90;           // offset 0x90, size 0x4
    float field_0x94;           // offset 0x94, size 0x4
    float field_0x98;           // offset 0x98, size 0x4
    float field_0x9C;           // offset 0x9C, size 0x4
    u8 flag_0xA0;               // offset 0xA0, size 0x1
    u8 pad_0xA1[0x3];           // offset 0xA1, size 0x3
    float field_0xA4;           // offset 0xA4, size 0x4
    u8 flag_0xA8;               // offset 0xA8, size 0x1
    u8 flag_0xA9;               // offset 0xA9, size 0x1
    u8 isGutterBall;            // offset 0xAA, size 0x1
    u8 flag_0xAB;               // offset 0xAB, size 0x1
    u8 pad_0xAC[0x8];           // offset 0xAC, size 0x8
    u8 flag_0xB4;               // offset 0xB4, size 0x1
    u8 pad_0xB5[0x3];           // offset 0xB5, size 0x3
    u8 pad_0xB8[0x8];           // offset 0xB8, size 0x8
    int animationMode;          // offset 0xC0, size 0x4
    u8 pad_0xC4[0x8];           // offset 0xC4, size 0x8
    int field_0xCC;             // offset 0xCC, size 0x4
    u8 pad_0xD0[0x4];           // offset 0xD0, size 0x4
    nw4r::math::VEC3 vec_0xD4;  // offset 0xD4, size 0xC
    u8 pad_0xE0[0x24];          // offset 0xE0, size 0x24
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

struct BallPhysicsState {
    // total size: 0x118
    u8 pad_00[0x10];        // offset 0x0, size 0x10
    f32 previousState[19];  // offset 0x10, size 0x4C
    f32 field_5C;           // offset 0x5C, size 0x4
    u32 unk_60;             // offset 0x60, size 0x4
    f32 currentState[38];   // offset 0x64, size 0x98
    u8 pad_FC[0x18];        // offset 0xFC, size 0x18
    u8 flag_114;            // offset 0x114, size 0x1
    u8 pad_115[3];          // offset 0x115, size 0x3
};

struct RPBowBallHistoryEntry {
    // total size: 0x118
    RPBowBallHistoryEntry();
    ~RPBowBallHistoryEntry();

    u32 unk_0;              // offset 0x0, size 0x4
    f32 currentState[38];   // offset 0x4, size 0x98
    f32 previousState[19];  // offset 0x9C, size 0x4C
    u32 index20A;           // offset 0xE8, size 0x4
    u32 throwCount;         // offset 0xEC, size 0x4
    nw4r::math::VEC3 vec1;  // offset 0xF0, size 0xC
    nw4r::math::VEC3 vec2;  // offset 0xFC, size 0xC
    nw4r::math::VEC3 vec3;  // offset 0x108, size 0xC
    u8 flag_114;            // offset 0x114, size 0x1
    u8 pad_115[3];          // offset 0x115, size 0x3
};

struct ThrowPosState_A {
    // total size: 0x20
    ThrowPosState_A();
    ~ThrowPosState_A();

    u32 field_00;  // offset 0x0, size 0x4
    f32 field_04;  // offset 0x4, size 0x4
    f32 field_08;  // offset 0x8, size 0x4
    f32 field_0C;  // offset 0xC, size 0x4
    f32 field_10;  // offset 0x10, size 0x4
    f32 field_14;  // offset 0x14, size 0x4
    f32 field_18;  // offset 0x18, size 0x4
    f32 field_1C;  // offset 0x1C, size 0x4
};

struct ThrowPosState_B {
    // total size: 0x20
    ThrowPosState_B();

    u32 field_00;           // offset 0x0, size 0x4
    u8 flag_04;             // offset 0x4, size 0x1
    u8 pad_5[3];            // offset 0x5, size 0x3
    nw4r::math::VEC3 vec1;  // offset 0x8, size 0xC
    nw4r::math::VEC3 vec2;  // offset 0x14, size 0xC
};

class RPBowBallHistoryManager {
public:
    // total size: 0x2C
    u32 unk00;                            // offset 0x0, size 0x4
    ThrowPosState_A* pArray20A;           // offset 0x4, size 0x4
    u32 maxCount;                         // offset 0x8, size 0x4
    RPBowBallHistoryEntry* pEntries;      // offset 0xC, size 0x4
    u32 currentIndex;                     // offset 0x10, size 0x4
    RPBowBallHistoryEntry* pActiveEntry;  // offset 0x14, size 0x4
    u32 maxCount8;                        // offset 0x18, size 0x4
    u32 index20A;                         // offset 0x1C, size 0x4
    u32 limit20B;                         // offset 0x20, size 0x4
    u32 index20B;                         // offset 0x24, size 0x4
    ThrowPosState_B* pArray20B;           // offset 0x28, size 0x4

    bool IsActiveEntryNull();
    void Allocate(u32 count);
    void Reset();
    void RecordState(BallPhysicsState* pSrc);
    void SetVectors(nw4r::math::VEC3* pVec1, nw4r::math::VEC3* pVec2, nw4r::math::VEC3* pVec3);
    void AddThrowPosStateA(ThrowPosState_A* pSrcArr, int count);
    void AddThrowPosStateB(u8 val1, nw4r::math::VEC3* pVec1, nw4r::math::VEC3* pVec2);
};

// TODO: this is some kind of class defined in RPUtility, RPKernel or RPSportsCommon, not in Bowling.
struct UnknownField18 {
    // first 0x8 bytes of vtable taken by rtti or something like that.
    virtual void pad_0x8();
    virtual void pad_0xC();
    virtual void pad_0x10();
    virtual void pad_0x14();
    virtual void pad_0x18();
    virtual void pad_0x1C();
    virtual void pad_0x20();
    virtual void pad_0x24();
    virtual void pad_0x28();
    virtual void pad_0x2C();
    virtual void pad_0x30();
    virtual float* vfunc_0x34();
    virtual void vfunc_0x38(EGG::Vector3f*);
    virtual void pad_0x3C();
    virtual void vfunc_0x40(EGG::Vector3f*);
    virtual void pad_0x44();
    virtual void pad_0x48();
    virtual void pad_0x4C();
    virtual void vfunc_0x50(EGG::Vector3f*);
    virtual void pad_0x54();
    virtual void vfunc_0x58(EGG::Vector3f*);
    virtual void pad_0x5C();
    virtual void vfunc_0x60(EGG::Vector3f*);
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
    f32 field_38;        // offset 0x38, size 0x4
    f32 field_3C;        // offset 0x3C, size 0x4
    f32 field_40;        // offset 0x40, size 0x4
    f32 field_44;        // offset 0x44, size 0x4
    f32 field_48;        // offset 0x48, size 0x4
    f32 field_4C;        // offset 0x4C, size 0x4
    f32 field_50;        // offset 0x50, size 0x4
    f32 field_54;        // offset 0x54, size 0x4
    f32 field_58;        // offset 0x58, size 0x4
    f32 field_5C;        // offset 0x5C, size 0x4
    f32 field_60;        // offset 0x60, size 0x4
    f32 field_64;        // offset 0x64, size 0x4
    f32 field_68;        // offset 0x68, size 0x4
    f32 field_6C;        // offset 0x6C, size 0x4
    f32 field_70;        // offset 0x70, size 0x4
    f32 field_74;        // offset 0x74, size 0x4
    f32 field_78;        // offset 0x78, size 0x4
    f32 field_7C;        // offset 0x7C, size 0x4
    f32 field_80;        // offset 0x80, size 0x4
    f32 field_84;        // offset 0x84, size 0x4
    f32 field_88;        // offset 0x88, size 0x4
    f32 field_8C;        // offset 0x8C, size 0x4
    f32 field_90;        // offset 0x90, size 0x4
    f32 field_94;        // offset 0x94, size 0x4
    f32 field_98;        // offset 0x98, size 0x4
    f32 field_9C;        // offset 0x9C, size 0x4
    f32 field_A0;        // offset 0xA0, size 0x4
    f32 field_A4;        // offset 0xA4, size 0x4
    f32 field_A8;        // offset 0xA8, size 0x4
    f32 field_AC;        // offset 0xAC, size 0x4
    f32 field_B0;        // offset 0xB0, size 0x4
    f32 field_B4;        // offset 0xB4, size 0x4
    f32 field_B8;        // offset 0xB8, size 0x4
    f32 field_BC;        // offset 0xBC, size 0x4
    f32 field_C0;        // offset 0xC0, size 0x4
    f32 field_C4;        // offset 0xC4, size 0x4
    f32 field_C8;        // offset 0xC8, size 0x4
    f32 field_CC;        // offset 0xCC, size 0x4
    f32 field_D0;        // offset 0xD0, size 0x4
    f32 field_D4;        // offset 0xD4, size 0x4
    f32 field_D8;        // offset 0xD8, size 0x4
    f32 field_DC;        // offset 0xDC, size 0x4
    f32 field_E0;        // offset 0xE0, size 0x4
    f32 field_E4;        // offset 0xE4, size 0x4
    f32 field_E8;        // offset 0xE8, size 0x4
    f32 field_EC;        // offset 0xEC, size 0x4
    f32 field_F0;        // offset 0xF0, size 0x4
    f32 field_F4;        // offset 0xF4, size 0x4
    f32 field_F8;        // offset 0xF8, size 0x4
    f32 field_FC;        // offset 0xFC, size 0x4
    f32 field_100;       // offset 0x100, size 0x4
    f32 field_104;       // offset 0x104, size 0x4
    f32 field_108;       // offset 0x108, size 0x4
    f32 field_10C;       // offset 0x10C, size 0x4
    f32 field_110;       // offset 0x110, size 0x4
    f32 field_114;       // offset 0x114, size 0x4
    f32 field_118;       // offset 0x118, size 0x4
    f32 field_11C;       // offset 0x11C, size 0x4
    f32 field_120;       // offset 0x120, size 0x4
    f32 field_124;       // offset 0x124, size 0x4
    f32 field_128;       // offset 0x128, size 0x4
    f32 field_12C;       // offset 0x12C, size 0x4
    f32 field_130;       // offset 0x130, size 0x4
    f32 field_134;       // offset 0x134, size 0x4
    f32 field_138;       // offset 0x138, size 0x4
    f32 field_13C;       // offset 0x13C, size 0x4
    f32 field_140;       // offset 0x140, size 0x4
    f32 field_144;       // offset 0x144, size 0x4
    f32 field_148;       // offset 0x148, size 0x4
    f32 field_14C;       // offset 0x14C, size 0x4
    f32 field_150;       // offset 0x150, size 0x4
    f32 field_154;       // offset 0x154, size 0x4
    f32 field_158;       // offset 0x158, size 0x4
    f32 field_15C;       // offset 0x15C, size 0x4
    f32 field_160;       // offset 0x160, size 0x4
    f32 field_164;       // offset 0x164, size 0x4
    f32 field_168;       // offset 0x168, size 0x4
    f32 field_16C;       // offset 0x16C, size 0x4
    f32 field_170;       // offset 0x170, size 0x4
    f32 field_174;       // offset 0x174, size 0x4
    f32 field_178;       // offset 0x178, size 0x4
    f32 field_17C;       // offset 0x17C, size 0x4
    f32 field_180;       // offset 0x180, size 0x4
    f32 field_184;       // offset 0x184, size 0x4
    f32 field_188;       // offset 0x188, size 0x4
    f32 field_18C;       // offset 0x18C, size 0x4
    f32 field_190;       // offset 0x190, size 0x4
    f32 field_194;       // offset 0x194, size 0x4
    f32 field_198;       // offset 0x198, size 0x4
    f32 field_19C;       // offset 0x19C, size 0x4
    f32 field_1A0;       // offset 0x1A0, size 0x4
    f32 field_1A4;       // offset 0x1A4, size 0x4
    f32 field_1A8;       // offset 0x1A8, size 0x4
    f32 field_1AC;       // offset 0x1AC, size 0x4
    f32 field_1B0;       // offset 0x1B0, size 0x4
    f32 field_1B4;       // offset 0x1B4, size 0x4
    f32 field_1B8;       // offset 0x1B8, size 0x4
    f32 field_1BC;       // offset 0x1BC, size 0x4
    f32 field_1C0;       // offset 0x1C0, size 0x4
    f32 field_1C4;       // offset 0x1C4, size 0x4
    f32 field_1C8;       // offset 0x1C8, size 0x4
    f32 field_1CC;       // offset 0x1CC, size 0x4
    f32 field_1D0;       // offset 0x1D0, size 0x4
    f32 field_1D4;       // offset 0x1D4, size 0x4
    f32 field_1D8;       // offset 0x1D8, size 0x4
    f32 field_1DC;       // offset 0x1DC, size 0x4
    f32 field_1E0;       // offset 0x1E0, size 0x4
    f32 field_1E4;       // offset 0x1E4, size 0x4
    f32 field_1E8;       // offset 0x1E8, size 0x4
    f32 field_1EC;       // offset 0x1EC, size 0x4
    f32 field_1F0;       // offset 0x1F0, size 0x4
    f32 field_1F4;       // offset 0x1F4, size 0x4
    f32 field_1F8;       // offset 0x1F8, size 0x4
    f32 field_1FC;       // offset 0x1FC, size 0x4
    f32 field_200;       // offset 0x200, size 0x4
    f32 field_204;       // offset 0x204, size 0x4
    f32 field_208;       // offset 0x208, size 0x4
    f32 field_20C;       // offset 0x20C, size 0x4
    f32 field_210;       // offset 0x210, size 0x4
    f32 field_214;       // offset 0x214, size 0x4
    f32 field_218;       // offset 0x218, size 0x4
    f32 field_21C;       // offset 0x21C, size 0x4
    f32 field_220;       // offset 0x220, size 0x4
    f32 field_224;       // offset 0x224, size 0x4
    f32 field_228;       // offset 0x228, size 0x4
    f32 field_22C;       // offset 0x22C, size 0x4
    f32 field_230;       // offset 0x230, size 0x4
    f32 field_234;       // offset 0x234, size 0x4
    f32 field_238;       // offset 0x238, size 0x4
    f32 field_23C;       // offset 0x23C, size 0x4
    f32 field_240;       // offset 0x240, size 0x4
    u8 field_244;        // offset 0x244, size 0x1
    u8 field_245;        // offset 0x245, size 0x1
    u8 field_246;        // offset 0x246, size 0x1
    u8 field_247;        // offset 0x247, size 0x1
    f32 field_248;       // offset 0x248, size 0x4
    f32 field_24C;       // offset 0x24C, size 0x4
    f32 field_250;       // offset 0x250, size 0x4
    f32 field_254;       // offset 0x254, size 0x4
    f32 field_258;       // offset 0x258, size 0x4
    f32 field_25C;       // offset 0x25C, size 0x4
    f32 field_260;       // offset 0x260, size 0x4
    f32 field_264;       // offset 0x264, size 0x4
    f32 field_268;       // offset 0x268, size 0x4
    f32 floats[20];      // offset 0x26C, size 0x50
    f32 field_2BC;       // offset 0x2BC, size 0x4
    f32 field_2C0;       // offset 0x2C0, size 0x4
    f32 field_2C4;       // offset 0x2C4, size 0x4
    f32 field_2C8;       // offset 0x2C8, size 0x4
    f32 field_2CC;       // offset 0x2CC, size 0x4
};

struct UnknownLaneContextStruct5 {
    // total size: 0x114
    u8 pad_0x00[0x14];  // offset 0x0, size 0x14
    float field_0x14;   // offset 0x14, size 0x4
    u8 pad_0x18[0x74];  // offset 0x18, size 0x74
    float field_0x8C;   // offset 0x8C, size 0x4
    float field_0x90;   // offset 0x90, size 0x4
    u8 pad_0x94[0x7C];  // offset 0x94, size 0x7C
    float field_0x110;  // offset 0x110, size 0x4
};

struct PinMatrixPair {
    // total size: 0x60
    nw4r::math::MTX34 realMtx;        // offset 0x0, size 0x30
    nw4r::math::MTX34 reflectionMtx;  // offset 0x30, size 0x30
};

class RPBowPowerThrowsPinManager : public RP_DEBUG_STUB_1, public IRPGrpModelCallback {
public:
    virtual ~RPBowPowerThrowsPinManager();
    virtual void VF_0x0C();                         // at 0xC
    virtual void VF_0x10();                         // at 0x10
    virtual void CopyMatrices(RPGrpModel* pOther);  // at 0x14

    RPGrpModel* mpModels[2];         // offset 0x8, size 0x8
    PinMatrixPair mMatrixPairs[91];  // offset 0x10, size 0x2220

    RPBowPowerThrowsPinManager();
    void fn_80340304();
    void SetModels(RPGrpModel* pRealModel, RPGrpModel* pReflectionModel);
    void fn_8034021C();
    void UpdateModels();
    void fn_80340194();
    void TransformMatrix(int pinIndex, const nw4r::math::MTX34* pMtx, f32 yOffset);
    void ClearMatrices(int startIndex);
};

struct LaneContextSubClassA {
    // total size: 0xE8
    f32 unkFloats[58];  // offset 0x0, size 0xE8

    LaneContextSubClassA();   // fn_80315560
    ~LaneContextSubClassA();  // fn_80315520
};

struct LaneContextSubClassB {
    // total size: 0x108
    ThrowContext ThrowContext;  // offset 0x0, size 0x108

    LaneContextSubClassB();     // fn_80315504
    ~LaneContextSubClassB();    // fn_803154C4
};

class LaneContext : public IRPSysHostIOSocket {
public:
    // total size: 0x2080. confirmed by RPBowGlobalLaneManager::InitializeLaneContexts.
    // first virtual functions are taken up by rtti and IRPSysHostIOSocket's virtual functions.
    virtual float VF_0x14(); // at 0x14
    virtual void VF_0x18(); // at 0x18
    virtual void VF_0x1C(); // at 0x1C

    PinManager* pPinManager;               // offset 0x4, size 0x4
    LaneBvhData* pLaneBvhData;             // offset 0x8, size 0x4
    RPBowPinSetterModel* pPinSetter;                 // offset 0xC, size 0x4
    RPBowBallHistoryManager* ballHistory;  // offset 0x10, size 0x4
    int pinCount;                          // offset 0x14, size 0x4
    UnknownField18* unkPtr_0x18;           // offset 0x18, size 0x4
    void* unkPtr_0x1C;                     // offset 0x1C, size 0x4
    LaneContextSubClassA arrayA[15];       // offset 0x20, size 0xD98
    LaneContextSubClassB arrayB[15];       // offset 0xDB8, size 0xF78
    PinPhysicsBody* array_0x1D30[100];     // offset 0x1D30, size 0x190
    int field_1EC0;                        // offset 0x1EC0, size 0x4
    int field_1EC4;                        // offset 0x1EC4, size 0x4
    nw4r::math::VEC3 vec_0x1EC8;           // offset 0x1EC8, size 0xC
    nw4r::math::VEC3 vec_0x1ED4;           // offset 0x1ED4, size 0xC
    int field_1EE0;                        // offset 0x1EE0, size 0x4
    int field_1EE4;                        // offset 0x1EE4, size 0x4
    nw4r::math::VEC3 vec_0x1EE8;           // offset 0x1EE8, size 0xC
    int field_1EF4;                        // offset 0x1EF4, size 0x4
    ThrowContext throwContext;             // offset 0x1EF8, size 0x108
    PinStatus pinStatus;                   // offset 0x2000, size 0x14
    float laneXOffset;                     // offset 0x2014, size 0x4
    PinSetterAnimation setterAnimation;    // offset 0x2018, size 0x10
    u32 field_0x2028;                      // offset 0x2028, size 0x4
    void* unkPtr_0x202C;                   // offset 0x202C, size 0x4
    RPSysEffect* effects[16];              // offset 0x2030, size 0x40
    bool flag_0x2070;                      // offset 0x2070, size 0x1
    bool flag_0x2071;                      // offset 0x2071, size 0x1
    u8 pad_0x2071[0x2];                    // offset 0x2072, size 0x2
    float field_0x2074;                    // offset 0x2074, size 0x4
    bool flag_0x2078;                      // offset 0x2078, size 0x1
    u8 pad_0x2079[0x3];                    // offset 0x2079, size 0x3
    int laneStateTarget;                   // offset 0x207C, size 0x4

    void fn_80327858(int a, int b, float f_val, RPBowPinSetterModel* pinSetter);
    void fn_80323F30();
    void fn_8032781C();
    void fn_803277B4();
    void fn_80327558();
    void fn_80327330(PinStatus* status);
    void fn_80327218();
    void fn_80325154();
    nw4r::math::VEC3 fn_80325144();
    nw4r::math::VEC3 fn_803250F8();
    nw4r::math::VEC3 fn_803250E8();
    nw4r::math::VEC3 fn_803250D8();
    void fn_80324B50(const nw4r::math::VEC3* v1, const nw4r::math::VEC3* v2);
    void fn_80324B18(const nw4r::math::VEC3* v);
    int fn_80324B10();
    int fn_803248F8();
    void fn_803252FC();
    void fn_80324DD0(nw4r::math::VEC3* vec, u8 flag);
    void fn_80323DD0();
    void fn_80323D0C(BowlingPhysicsData* bowlingPhysicsData, float* out1, float* out2, float val);
    void fn_80323A60(BowlingPhysicsData* bowlingPhysicsData);
    void fn_803256C4(BowlingPhysicsData* bowlingPhysicsData);
    void fn_803381DC();
    void fn_80338724(PhysicsBody* body, PhysicsBodyState* state);
    void fn_8033C3B0(PinPhysicsBody* r4, UnknownLaneContextStruct5* r5, ThrowContext* r6, void* r7, void* r8, void* r9, float f1);
    void fn_803394C0(PinPhysicsBody* r4, UnknownLaneContextStruct5* r5, ThrowContext* r6, void* r7, void* r8, void* r9, float f1);
    void fn_80338720();
    void fn_8033871C();

    void ResetPinSetterState(u8 isNewRack);
    void TriggerPinSetter(int spawnNewRack);
    int UpdatePinSetter();
    int IsPinSetterActive();
    void fn_803345F0();

    LaneContext() : IRPSysHostIOSocket() {
        throwContext.field_0x90 = 1.1920929e-07f;
        throwContext.field_0x94 = 1.1920929e-07f;
        throwContext.field_0x98 = 0.0f;
        throwContext.field_0x9C = 0.0f;

        pinStatus.pinBits[0] = pinStatus.pinBits[1] = pinStatus.pinBits[2] = pinStatus.pinBits[3] = -1;
        pinStatus.pinCount = 10;
    }
};

struct LaneContextExt : public LaneContext {
    // LaneContext laneContext                          // offset 0x4, size 0x2080
    float field_0x2080;                                 // offset 0x2080, size 0x4
    float field_0x2084;                                 // offset 0x2084, size 0x4
    float field_0x2088;                                 // offset 0x2088, size 0x4
    float field_0x208C;                                 // offset 0x208C, size 0x4
    float field_0x2090;                                 // offset 0x2090, size 0x4
    float field_0x2094;                                 // offset 0x2094, size 0x4
    float field_0x2098;                                 // offset 0x2098, size 0x4
    float field_0x209C;                                 // offset 0x209C, size 0x4
    float field_0x20A0;                                 // offset 0x20A0, size 0x4
    float field_0x20A4;                                 // offset 0x20A4, size 0x4
    float field_0x20A8;                                 // offset 0x20A8, size 0x4
    float field_0x20AC;                                 // offset 0x20AC, size 0x4
    float field_0x20B0;                                 // offset 0x20B0, size 0x4
    float field_0x20B4;                                 // offset 0x20B4, size 0x4
    float field_0x20B8;                                 // offset 0x20B8, size 0x4
    float field_0x20BC;                                 // offset 0x20BC, size 0x4
    float field_0x20C0;                                 // offset 0x20C0, size 0x4
    float field_0x20C4;                                 // offset 0x20C4, size 0x4
    RPBowPowerThrowsPinManager* powerThrowsPinManager;  // offset 0x20C8, size 0x4
    u8 pad_0x20CC[0x4];                                 // offset 0x20CC, size 0x4
    u8 flag_0x20D0;                                     // offset 0x20D0, size 0x1
    u8 flag_0x20D1;                                     // offset 0x20D1, size 0x1
    u8 flag_0x20D2;                                     // offset 0x20D2, size 0x1
    u8 flag_0x20D3;                                     // offset 0x20D3, size 0x1
    u8 pad_0x20D4[0x878];                               // offset 0x20D4, size 0x878
    int field_0x294C;                                   // offset 0x294C, size 0x4
};

struct SubNpcLaneData {
    // total size: 0x5C
    u32 mState;        // offset 0x0, size 0x4
    int mTimer;        // offset 0x4, size 0x4
    float field_0x8;   // offset 0x8, size 0x4
    u8 pad_0xC[0x4];   // offset 0xC, size 0x4
    float mScale;      // offset 0x10, size 0x4
    float mOffsetZ;    // offset 0x14, size 0x4
    float mRotY;       // offset 0x18, size 0x4
    float mOffsetX;    // offset 0x1C, size 0x4
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

struct KokeshiGroupPair {
    // total size: 0x8
    RPSysKokeshi* realKokeshi;        // offset 0x0, size 0x4
    RPSysKokeshi* reflectionKokeshi;  // offset 0x4, size 0x4
};

class RPBowLaneDataHolder : public IRPSysHostIOSocket {
public:
    // total size: 0x130
    virtual ~RPBowLaneDataHolder();
    virtual void VF_0x08();  // vtable index 2 (offset 0x8)
    virtual void VF_0x0C(int);  // vtable index 3 (offset 0xC)

    void* unkPtr_0x04;            // offset 0x4, size 0x4
    u32 mCurrentGroup;            // offset 0x8, size 0x4
    float field_0x0C;             // offset 0xC, size 0x4
    float field_0x10;             // offset 0x10, size 0x4
    float field_0x14;             // offset 0x14, size 0x4
    float field_0x18;             // offset 0x18, size 0x4
    float field_0x1C;             // offset 0x1C, size 0x4
    float field_0x20;             // offset 0x20, size 0x4
    float field_0x24;             // offset 0x24, size 0x4
    float field_0x28;             // offset 0x28, size 0x4
    float mWaitTime;              // offset 0x2C, size 0x4
    SubNpcLaneData mSubData;      // offset 0x30, size 0x5C
    KokeshiGroupPair mGroups[4];  // offset 0x8C, size 0x20
    u16 mAnimIdA;                 // offset 0xAC, size 0x2
    u16 mAnimIdB;                 // offset 0xAE, size 0x2
    float mAnimFrameA;            // offset 0xB0, size 0x4
    float mAnimFrameB;            // offset 0xB4, size 0x4
    u16 mPrevAnimIdA;             // offset 0xB8, size 0x2
    u16 mPrevAnimIdB;             // offset 0xBA, size 0x2
    float mPrevAnimFrameA;        // offset 0xBC, size 0x4
    float mPrevAnimFrameB;        // offset 0xC0, size 0x4
    float mAnimWeightA;           // offset 0xC4, size 0x4
    float mAnimWeightB;           // offset 0xC8, size 0x4
    float field_0xCC;             // offset 0xCC, size 0x4
    float field_0xD0;             // offset 0xD0, size 0x4
    u16 field_0xD4;               // offset 0xD4, size 0x2
    u16 field_0xD6;               // offset 0xD6, size 0x2
    u16 field_0xD8;               // offset 0xD8, size 0x2
    u8 pad_0xDA[0x2];             // offset 0xDA, size 0x2
    nw4r::math::VEC3 mSpawnPos;   // offset 0xDC, size 0xC
    float field_0xE8;             // offset 0xE8, size 0x4
    float field_0xEC;             // offset 0xEC, size 0x4
    u8 mFlags[0x4];               // offset 0xF0, size 0x4
    void* unkPtr_0xF4;            // offset 0xF4, size 0x4
    float field_0xF8;             // offset 0xF8, size 0x4
    float field_0xFC;             // offset 0xFC, size 0x4
    float field_0x100;            // offset 0x100, size 0x4
    float field_0x104;            // offset 0x104, size 0x4
    float field_0x108;            // offset 0x108, size 0x4
    float field_0x10C;            // offset 0x10C, size 0x4
    float field_0x110;            // offset 0x110, size 0x4
    float field_0x114;            // offset 0x114, size 0x4
    RPGrpModel* mpExtraModel;     // offset 0x118, size 0x4
    float field_0x11C;            // offset 0x11C, size 0x4
    void* mpModelDataArray[0x4];  // offset 0x120, size 0x10

    void Initialize();
    void RegisterGroups(int index, RPSysKokeshi* realKokeshi, RPSysKokeshi* reflectionKokeshi);
    void SetModelData(s16 arg1, s16 arg2, s16 arg3, RPGrpModel* model);
    void SetAnimation(u16 indexA, u16 indexB);
    void Reset(int arg1, int arg2);
    void StartThrow();
    void SetVisibility(bool enable);
    void SetDrawGroup(u8 drawGroup);
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

class RPBowNpcMovementState : public IRPSysHostIOSocket {
public:
    // total size: 0x1C
    virtual ~RPBowNpcMovementState();

    s32 laneIdx;                      // offset 0x4, size 0x4
    s32 npcIdx;                       // offset 0x8, size 0x4
    u8 isMovementComplete;            // offset 0xC, size 0x1
    u8 pad0D[3];                      // offset 0xD, size 0x3
    nw4r::math::VEC3 returnStartPos;  // offset 0x10, size 0xC

    void fn_80346E5C();
    nw4r::math::VEC3 CalculateLaneSeatCenter() const;
    void InitNpcMovementState(int laneIdx, int npcIdx);
    void SetNpcReturnStartPos(const nw4r::math::VEC3 *pCurrentPos);
};

struct NpcActionState {
    // total size: 0x14
    NpcStates npcState;     // offset 0x0, size 0x4
    int stateFrameCounter;  // offset 0x4, size 0x4
    u8 triggerThrow;        // offset 0x8, size 0x1
    u8 triggerTransition;   // offset 0x9, size 0x1
    u8 pad_0x3A[0x2];       // offset 0xA, size 0x2
    s32 field_0x3A;         // offset 0xC, size 0x4
    float targetZPos;       // offset 0x10, size 0x4
};

class RPBowNpcContext : public IRPSysHostIOSocket {
public:
    // total size: 0xA8
    virtual ~RPBowNpcContext();

    RPSysKokeshi* mpKokeshi[2];            // offset 0x4, size 0x8
    void* unkPtr_0xC;                      // offset 0xC, size 0x4
    nw4r::math::VEC3 pos_0x10;             // offset 0x10, size 0xC
    nw4r::math::VEC3 rot_0x1C;             // offset 0x1C, size 0xC
    float field_0x28;                      // offset 0x28, size 0x4
    u8 pad_0x2C[0x4];                      // offset 0x2C, size 0x4
    NpcActionState actionState;            // offset 0x30, size 0x14
    u8 field_0x44;                         // offset 0x44, size 0x1
    u8 pad_0x45[3];                        // offset 0x45, size 0x3
    RPBowNpcMovementState* movementState;  // offset 0x48, size 0x4
    int field_0x4C;                        // offset 0x4C, size 0x4, 0 = Walk to approach area, 1 = Idle at approach area, 2 = Bowl, 3 = Watch ball, 4 = Turn around, 5 = Walk to ball return or seat from approach area, 6 = Idle, 7 = Walk to ball return from seat
    u8 isHoldingBall;                      // offset 0x50, size 0x1
    u8 flag_51;                            // offset 0x51, size 0x1
    u8 flag_52;                            // offset 0x52, size 0x1
    u8 flag_53;                            // offset 0x53, size 0x1
    int laneIdx;                           // offset 0x54, size 0x4
    int npcIdx;                            // offset 0x58, size 0x4
    NpcIdleState subStruct;                // offset 0x5C, size 0x48
    u8 pad_0xA4[0x1];                      // offset 0xA4, size 0x1
    u8 flag_A5;                            // offset 0xA5, size 0x1
    u8 pad_0xA6[0x2];                      // offset 0xA6, size 0x2

    void InitNpcInstance(RPSysKokeshi* realKokeshi, RPSysKokeshi* reflectionKokeshi);
    void InitNpcContext(int laneIdx, int npcIdx);
    void UpdateNpcLane();
    void InitNpcBoundingBoxes(void* unkPtr);
    void ResetNpcState();
    void fn_80334270();
    void fn_80332C60(int val);
    void fn_80332C2C(u8 val);
    void fn_80332C24();
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

    void Init(RPSysKokeshi* realKokeshi, RPSysKokeshi* reflectionKokeshi, int index);
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
    RPSysKokeshi* mModelGroups[2][2];      // offset 0x38, size 0x10
    int mConfigIndex;                      // offset 0x48, size 0x4
    NpcIdleState mIdleState;               // offset 0x4C, size 0x48
    bool isVisible;                        // offset 0x94, size 0x1
    u8 pad_0x95[3];                        // offset 0x95, size 0x3
    s32 mModelGroupSet;                    // offset 0x98, size 0x4

    void fn_8034E96C();
    void InitializeConfig(int index);
    void SetModelGroups(int managerIndex, RPSysKokeshi* realKokeshi, RPSysKokeshi* reflectionKokeshi);
    void fn_8034E83C();
    void Reset();
    void UpdateMovement(nw4r::math::VEC3* outPosition, bool* outStateFlag);
    void Render();
    void fn_8034DD14();
    void fn_8034DD0C();
    void fn_8034DD08();
};

struct CameraProjection {
    // total size: 0x1C
    int field_0x00;    // offset 0x0, size 0x4
    int field_0x04;    // offset 0x4, size 0x4
    float resWidth;    // offset 0x8, size 0x4 - Camera resolution width: 832.0
    float resHeight;   // offset 0xC, size 0x4 - Camera resolution height: 456.0
    float fov;         // offset 0x10, size 0x4
    float tanFov;      // offset 0x14, size 0x4
    float field_0x18;  // offset 0x18, size 0x4
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
    RPBowNpcContext* mpNpcs[3];         // offset 0x18, size 0xC
    RPBowNpcContext* mpCurrentNpc;      // offset 0x24, size 0x4
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
    void Setup(LaneContext* pLaneContext, RPBowNpcContext* pNpc0, RPBowNpcContext* pNpc1, RPBowNpcContext* pNpc2, int laneIdx, RPBowBallReturnRack* pReturnRack, void* pAudioStruct);
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
                pinData->state.basisX.x, pinData->state.basisY.x, pinData->state.basisZ.x, pinData->state.position.x,
                pinData->state.basisX.y, pinData->state.basisY.y, pinData->state.basisZ.y, pinData->state.position.y,
                pinData->state.basisX.z, pinData->state.basisY.z, pinData->state.basisZ.z, pinData->state.position.z
            );
        }
    }
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

    void fn_8034D4F0();
    void SetBlurModels(RPGrpModel* pReal1, RPGrpModel* pReal2, RPGrpModel* pReal3, RPGrpModel* pRefl1, RPGrpModel* pRefl2, RPGrpModel* pRefl3);
    void DeactivateBlur();
    void UpdateBlurTransform(const nw4r::math::MTX34* pBaseMtx, f32 speed);
    void DrawBlur(void* pCullingCtx);
};

struct CameraTransformSub {
    // total size: 0xDC. Confirmed by fn_8031C078 in tu4.
    nw4r::math::VEC3 vec0;        // offset 0x0, size 0xC
    nw4r::math::VEC3 target;      // offset 0xC, size 0xC
    u8 pad_0x18[0x10];            // offset 0x18, size 0x10
    float offsetX;                // offset 0x28, size 0x4
    u8 pad_0x2C[0xC];             // offset 0x2C, size 0xC
    float unk_0x38;               // offset 0x38, size 0x4
    u8 pad_0x3C[0x5C];            // offset 0x3C, size 0x5C
    float unk_0x98;               // offset 0x98, size 0x4
    u8 pad_0x9C[0x1C];            // offset 0x9C, size 0x1C
    int curveInterpolationFrame;  // offset 0xB8, size 0x4
    u8 pad_0xBC[0x4];             // offset 0xBC, size 0x4
    float unk_0xC0;               // offset 0xC0, size 0x4
    u8 pad_0xC4[0x10];            // offset 0xC4, size 0x10
    float unk_0xD4;               // offset 0xD4, size 0x4
    bool unk_0xD8;                // offset 0xD8, size 0x1
    u8 pad_0xD9[0x3];             // offset 0xD9, size 0x3
};

enum BowlingCameraStates {
    BOWLING_CAMERA_STATE_NULL = -1,                          // Null
    BOWLING_CAMERA_STATE_NORMAL_INITIAL_DEMO = 0,            // Initial camera demo at the start of the game
    BOWLING_CAMERA_STATE_NORMAL_PLAYER_SCORES = 1,           // Displaying player scores
    BOWLING_CAMERA_STATE_TRAINING_RECORD = 2,                // Displaying player's training mode record
    BOWLING_CAMERA_STATE_ADJUSTING_SHOT = 3,                 // Active bowling gameplay - adjusting shot
    BOWLING_CAMERA_STATE_THROWING = 4,                       // Active bowling gameplay - throwing
    BOWLING_CAMERA_STATE_FAILED_TO_BOWL_ERROR = 5,           // "Failed to bowl properly" error message
    BOWLING_CAMERA_STATE_UNKNOWN_6 = 6,                      // Unknown
    BOWLING_CAMERA_STATE_LANE_TRANSITION = 7,                // Camera shot transitioning to the next lane
    BOWLING_CAMERA_STATE_POWER_THROWS_PIN_TRANSITION = 8,    // Camera shot showing how many pins need to be hit
    BOWLING_CAMERA_STATE_NORMAL_FINAL_DEMO = 9,              // Final camera demo at the end of the game
    BOWLING_CAMERA_STATE_NORMAL_REPLAY = 10,                 // Replay
    BOWLING_CAMERA_STATE_NORMAL_STRIKE_SPLIT_REPLAY_1 = 11,  // Strike/Split Replay 1
    BOWLING_CAMERA_STATE_NORMAL_STRIKE_SPLIT_REPLAY_2 = 12,  // Strike/Split Replay 2
    BOWLING_CAMERA_STATE_POWER_THROWS_REPLAY = 13,           // Replay
    BOWLING_CAMERA_STATE_POWER_THROWS_STRIKE_REPLAY_1 = 14,  // Strike Replay 1
    BOWLING_CAMERA_STATE_POWER_THROWS_STRIKE_REPLAY_2 = 15,  // Strike Replay 2
    BOWLING_CAMERA_STATE_SPIN_CONTROL_REPLAY = 16,           // Replay
    BOWLING_CAMERA_STATE_PICKING_UP_SPARES_REPLAY = 17       // Replay
};

struct CameraAnimNode {
    // total size: 0x74
    u8 name[0x20];               // offset 0x0, size 0x20
    u32 animType;                // offset 0x20, size 0x4
    nw4r::math::VEC3 startPos;   // offset 0x24, size 0xC
    nw4r::math::VEC3 endPos;     // offset 0x30, size 0xC
    f32 startPitch;              // offset 0x3C, size 0x4
    f32 startYaw;                // offset 0x40, size 0x4
    f32 endPitch;                // offset 0x44, size 0x4
    f32 endYaw;                  // offset 0x48, size 0x4
    f32 easeStart;               // offset 0x4C, size 0x4
    f32 easeEnd;                 // offset 0x50, size 0x4
    f32 durationFrames;          // offset 0x54, size 0x4
    f32 fov;                     // offset 0x58, size 0x4
    nw4r::math::VEC3 posOffset;  // offset 0x5C, size 0xC
    u8 flags;                    // offset 0x68, size 0x1
    u8 pad_0x69[3];              // offset 0x69, size 0x3
    f32 normalizationFactor;     // offset 0x6C, size 0x4
    u32 nextNodeIdx;             // offset 0x70, size 0x4
};

struct CameraState {
    // total size: 0x2C
    nw4r::math::VEC3 pos;     // offset 0x0, size 0xC
    nw4r::math::VEC3 target;  // offset 0xC, size 0xC
    nw4r::math::VEC3 up;      // offset 0x18, size 0xC
    f32 fov;                  // offset 0x24, size 0x4
    u32 projType;             // offset 0x28, size 0x4
};

struct CameraTimeState {
    // total size: 0xC
    f32 linearTime;    // offset 0x0, size 0x4
    f32 easedTime;     // offset 0x4, size 0x4
    u8 isPaused;       // offset 0x8, size 0x1
    u8 pad_0x9[0x3];   // offset 0x9, size 0x3
};

class RPBowCameraController {
public:
    // total size: 0x17D0
    void* vtable;               // offset 0x0, size 0x4
    CameraState state;          // offset 0x4, size 0x2C
    u32 currentNodeIdx;         // offset 0x30, size 0x4
    CameraAnimNode nodes[52];   // offset 0x34, size 0x1790
    CameraTimeState timeState;  // offset 0x17C4, size 0xC

    void ResetCameraController();
    void SetCameraAnimationNode(s32 nodeIndex);
    void InitCameraAnimations();
    bool IsCameraAnimFinished();
    void UpdateCameraAnimation();
    void CalculateCameraPose(CameraState* state, CameraAnimNode* node, f32 easedProgress);
    void DebugPrintCameraInfo();

};

/*
struct RPGrpCamera {
    // total size: 0x174
    nw4r::math::MTX34 mViewMtx;         // offset 0x0, size 0x30
    nw4r::math::MTX34 mWorldMtx;        // offset 0x30, size 0x30
    nw4r::math::MTX34 mAnmViewMtx;      // offset 0x60, size 0x30
    nw4r::math::MTX34 mDirectWorldMtx;  // offset 0x90, size 0x30
    nw4r::math::VEC3 mPosition;         // offset 0xC0, size 0xC
    nw4r::math::VEC3 mTarget;           // offset 0xCC, size 0xC
    nw4r::math::VEC3 mRotation;         // offset 0xD8, size 0xC
    f32 mDistance;                      // offset 0xE4, size 0x4
    nw4r::math::VEC3 mRight;            // offset 0xE8, size 0xC
    nw4r::math::VEC3 mUp;               // offset 0xF4, size 0xC
    nw4r::math::VEC3 mForward;          // offset 0x100, size 0xC
    ECameraType mCameraType;            // offset 0x10C, size 0x4
    u16 mFlags;                         // offset 0x110, size 0x2
    nw4r::math::MTX34 mWorldMtxOld;     // offset 0x114, size 0x30
    nw4r::math::MTX34 mSavedViewMtx;    // offset 0x144, size 0x30
};
*/

class RPBowCameraTransform : public RPGrpCamera {
public:
    // total size: 0x348
    CameraProjection* projection;             // offset 0x178, size 0x4
    CameraTransformSub ctSub;                 // offset 0x17C, size 0xDC
    float unk_0x258;                          // offset 0x258, size 0x4
    float unk_0x25C;                          // offset 0x25C, size 0x4
    float unk_0x260;                          // offset 0x260, size 0x4
    float unk_0x264;                          // offset 0x264, size 0x4
    float unk_0x268;                          // offset 0x268, size 0x4
    float unk_0x26C;                          // offset 0x26C, size 0x4
    float unk_0x270;                          // offset 0x270, size 0x4
    float unk_0x274;                          // offset 0x274, size 0x4
    float unk_0x278;                          // offset 0x278, size 0x4
    float unk_0x27C;                          // offset 0x27C, size 0x4
    float unk_0x280;                          // offset 0x280, size 0x4
    float unk_0x284;                          // offset 0x284, size 0x4
    float unk_0x288;                          // offset 0x288, size 0x4
    float unk_0x28C;                          // offset 0x28C, size 0x4
    float unk_0x290;                          // offset 0x290, size 0x4
    float unk_0x294;                          // offset 0x294, size 0x4
    float unk_0x298;                          // offset 0x298, size 0x4
    float unk_0x29C;                          // offset 0x29C, size 0x4
    float unk_0x2A0;                          // offset 0x2A0, size 0x4
    float unk_0x2A4;                          // offset 0x2A4, size 0x4
    float unk_0x2A8;                          // offset 0x2A8, size 0x4
    float unk_0x2AC;                          // offset 0x2AC, size 0x4
    float unk_0x2B0;                          // offset 0x2B0, size 0x4
    float unk_0x2B4;                          // offset 0x2B4, size 0x4
    float unk_0x2B8;                          // offset 0x2B8, size 0x4
    float unk_0x2BC;                          // offset 0x2BC, size 0x4
    float unk_0x2C0;                          // offset 0x2C0, size 0x4
    float unk_0x2C4;                          // offset 0x2C4, size 0x4
    float unk_0x2C8;                          // offset 0x2C8, size 0x4
    float unk_0x2CC;                          // offset 0x2CC, size 0x4
    float unk_0x2D0;                          // offset 0x2D0, size 0x4
    float fovStart;                           // offset 0x2D4, size 0x4
    float unk_0x2D8;                          // offset 0x2D8, size 0x4
    float unk_0x2DC;                          // offset 0x2DC, size 0x4
    float unk_0x2E0;                          // offset 0x2E0, size 0x4
    float unk_0x2E4;                          // offset 0x2E4, size 0x4
    float unk_0x2E8;                          // offset 0x2E8, size 0x4
    float targetY;                            // offset 0x2EC, size 0x4
    float unk_0x2F0;                          // offset 0x2F0, size 0x4
    float unk_0x2F4;                          // offset 0x2F4, size 0x4
    float posY;                               // offset 0x2F8, size 0x4
    float unk_0x2FC;                          // offset 0x2FC, size 0x4
    float fovEnd;                             // offset 0x300, size 0x4
    float posZ;                               // offset 0x304, size 0x4
    float unk_0x308;                          // offset 0x308, size 0x4
    float unk_0x30C;                          // offset 0x30C, size 0x4
    float unk_0x310;                          // offset 0x310, size 0x4
    int unk_0x314;                            // offset 0x314, size 0x4
    float unk_0x318;                          // offset 0x318, size 0x4
    float unk_0x31C;                          // offset 0x31C, size 0x4
    float unk_0x320;                          // offset 0x320, size 0x4
    float unk_0x324;                          // offset 0x324, size 0x4
    BowlingCameraStates state;                // offset 0x328, size 0x4
    int counter;                              // offset 0x32C, size 0x4
    RPBowCameraController* cameraController;  // offset 0x330, size 0x4
    bool animFinished;                        // offset 0x334, size 0x1
    u8 pad_0x335[0x3];                        // offset 0x335, size 0x3
    int powerThrowStage;                      // offset 0x338, size 0x4
    int trainingLaneIndex;                    // offset 0x33C, size 0x4
    bool transitionStyle;                     // offset 0x340, size 0x1
    u8 pad_0x341[0x3];                        // offset 0x341, size 0x3
    int initialDemoType;                      // offset 0x344, size 0x4

    void InitCameraTransformConstants(CameraProjection* proj, RPBowCameraController* ctrl);
    void ResetCameraTransform();
    void ApplyCameraAnimation();
    void CameraProc();
    float fn_8031B3C0();
    float fn_8031B388();
    void UseCamera(int);
    void UseSpinControlReplayCamera();
    void UseReplayCamera(int type);
};

class RPBowAlleyModelManager : public RP_DEBUG_STUB_1 {
public:
virtual ~RPBowAlleyModelManager();
    RPGrpModel* mSlotModels[4];     // offset 0x4, size 0x10
    RPGrpModel* mSlotAltModels[4];  // offset 0x14, size 0x10
    RPGrpModel* mModels[8];         // offset 0x24, size 0x20
    // mModels[0]: Regular alley Lanes model
    // mModels[1]: Power Throws area model. This is the entire Power Throws room, no culling like with the normal alley.
    // mModels[2]: Regular alley static pins model. Pins that are never interacted with and are outside of the 7 active lanes.
    // mModels[3]: Regular alley lounge area model.
    // mModels[4]: Left Power Throws bumper.
    // mModels[6]: Left Power Throws bumper reflection.
    // mModels[5]: Right Power Throws bumper.
    // mModels[7]: Right Power Throws bumper reflection.
    u32 mSceneFlags;                // offset 0x44, size 0x4
    u32 mCurrentSlotIndex;          // offset 0x48, size 0x4
    f32 mBumperPosition;            // offset 0x4C, size 0x4

    void fn_8031EFE0();
    void SetModels(RPGrpModel* laneModel, RPGrpModel* powerThrowsRoomModel, RPGrpModel* staticPinsModel, RPGrpModel* loungeModel, RPGrpModel* leftBumperModel, RPGrpModel* leftBumperReflModel, RPGrpModel* rightBumperModel, RPGrpModel* rightBumperReflModel);
    void SetModelSlot(int index, RPGrpModel* model, RPGrpModel* altModel) ;
    void ResetSceneParams();
    void UpdateModelsLoop1(nw4r::math::MTX34* mtx);
    void UpdateModelsLoop2(nw4r::math::MTX34* mtx);
    void UpdateModelsLoop3(nw4r::math::MTX34* mtx);
    void UpdateModels();
};

struct Obj208Data {
    // total size: 0x84
    u8 pad_0x00[0x4];      // offset 0x0, size 0x4
    u8 pad_0x04[0x4];      // offset 0x4, size 0x4
    u8 pad_0x08[0x4];      // offset 0x8, size 0x4
    u8 pad_0x0C[0x4];      // offset 0xC, size 0x4
    void* unkPtr_0x10;     // offset 0x10, size 0x4
    void* unkPtr_0x14;     // offset 0x14, size 0x4
    u8 pad_0x18[0x4];      // offset 0x18, size 0x4
    u8 pad_0x1C[0x4];      // offset 0x1C, size 0x4
    u8 pad_0x20[0x4];      // offset 0x20, size 0x4
    u8 pad_0x24[0x4];      // offset 0x24, size 0x4
    u8 pad_0x28[0x4];      // offset 0x28, size 0x4
    u8 pad_0x2C[0x4];      // offset 0x2C, size 0x4
    u8 pad_0x30[0x4];      // offset 0x30, size 0x4
    u8 pad_0x34[0x4];      // offset 0x34, size 0x4
    u8 pad_0x38[0x4];      // offset 0x38, size 0x4
    void* unkPtr_0x3C;     // offset 0x3C, size 0x4
    u8 pad_0x40[0x4];      // offset 0x40, size 0x4
    u8 pad_0x44[0x4];      // offset 0x44, size 0x4
    u8 pad_0x48[0x4];      // offset 0x48, size 0x4
    u8 pad_0x4C[0x4];      // offset 0x4C, size 0x4
    float field_0x50;      // offset 0x50, size 0x4
    float field_0x54;      // offset 0x54, size 0x4
    float field_0x58;      // offset 0x58, size 0x4
    u8 pad_0x5C[0x4];      // offset 0x5C, size 0x4
    u8 pad_0x60[0x4];      // offset 0x60, size 0x4
    u8 pad_0x64[0x4];      // offset 0x64, size 0x4
    float field_0x68;      // offset 0x68, size 0x4
    u8 pad_0x6C[0x4];      // offset 0x6C, size 0x4
    u8 pad_0x70[0x4];      // offset 0x70, size 0x4
    u8 pad_0x74[0x4];      // offset 0x74, size 0x4
    nw4r::math::VEC3 vec;  // offset 0x78, size 0xC
};

class RPBowRegularPinManager : public RP_DEBUG_STUB_1, public IRPGrpModelCallback {
public:
    // total size: 0x3D8
    virtual ~RPBowRegularPinManager();

    RPGrpModel* mModels[2];               // offset 0x8, size 0x8
    nw4r::math::MTX34 mMatrices[10][2];   // offset 0x10, size 0x3C0
    RPGrpShadowTexture* mpShadowTexture;  // offset 0x3D0, size 0x4
    u32 mUseShadows;                      // offset 0x3D4, size 0x4

    void InitializeModels(RPGrpModel* realModel, RPGrpModel* reflectionModel);
    void fn_8034F440();
    void Calc();
    void fn_8034F164();
    void CopyMatricesToModel(RPGrpModel* pModel);
    void CalculatePinTransforms(int index, f32 yOffset, nw4r::math::MTX34* pMtxA, nw4r::math::MTX34* pMtxB, nw4r::math::MTX34* pMtxC);
    void HideExcessPins(int count);
};

struct SceneEntities {
    // total size: 0x1E0
    RPBowAlleyModelManager* alleyModels;           // offset 0x0, size 0x4
    RPBowLaneDataHolder* laneData;                 // offset 0x4, size 0x4
    RPBowTrajectoryGuide* trajectoryGuide;         // offset 0x8, size 0x4
    void* primaryProp;                             // offset 0xC, size 0x4
    RPBowRegularPinManager* pinManagers[7];        // offset 0x10, size 0x1C
    RPBowActiveBall* balls[7];                     // offset 0x2C, size 0x1C
    RPBowNpcContext* npcs[18];                     // offset 0x48, size 0x48
    RPBowPlayerLaneNpc* playerLaneNpcs[4];         // offset 0x90, size 0x10
    RPBowPinSetterModel* setters[7];               // offset 0xA0, size 0x1C
    void* environmentProps[64];                    // offset 0xBC, size 0x100
    RPBowBallReturnRack* ballReturns[4];           // offset 0x1BC, size 0x10
    RPBowBackgroundNpcManager* backgroundNpcs[4];  // offset 0x1CC, size 0x10
    void* unkPtr_0x1DC;                            // offset 0x1DC, size 0x4
};

class RPBowSceneObjectManager {
public:
    // total size: 0x218
    void* vtable;                     // offset 0x0, size 0x4
    SceneEntities entities;           // offset 0x4, size 0x1E0
    u8 bDrawLane;                     // offset 0x1E4, size 0x1
    u8 pad_0x1E5;                     // offset 0x1E5, size 0x1
    u8 bDrawNpcs;                     // offset 0x1E6, size 0x1
    u8 bDrawBalls;                    // offset 0x1E7, size 0x1
    u8 bDrawProps;                    // offset 0x1E8, size 0x1
    u8 bDrawPinSetters;               // offset 0x1E9, size 0x1
    u8 bDrawEnv;                      // offset 0x1EA, size 0x1
    u8 bDrawBallReturns;              // offset 0x1EB, size 0x1
    nw4r::math::MTX34* renderMatrix;  // offset 0x1EC, size 0x4
    u8 isAlternateMode;               // offset 0x1F0, size 0x1
    u8 bDrawPropsActive;              // offset 0x1F1, size 0x1
    u8 bDrawGroupA;                   // offset 0x1F2, size 0x1
    u8 bDrawGroupB;                   // offset 0x1F3, size 0x1
    u8 bDrawGroupC;                   // offset 0x1F4, size 0x1
    u8 pad_0x1F5[0x3];                // offset 0x1F5, size 0x3
    void* pRenderViewA;               // offset 0x1F8, size 0x4
    void* pRenderViewB;               // offset 0x1FC, size 0x4
    void* unkPtr_0x200;               // offset 0x200, size 0x4
    u8 pad_0x204[0x4];                // offset 0x204, size 0x4
    Obj208Data* cameraData;           // offset 0x208, size 0x4
    void* pPanController;             // offset 0x20C, size 0x4
    float panBoundary;                // offset 0x210, size 0x4
    float panScale;                   // offset 0x214, size 0x4

    void SetAlternateMode(bool flag);
    void SetLaneGroupVisibility(int laneIdx, u8 isVisible);
    void fn_80316B04();
    void ResetAllEntities();
    nw4r::math::MTX34* ProcessCamera(CameraProjection* proj, RPBowCameraTransform* transform);
    void fn_80316A44();
    void RenderEntities(CameraProjection* proj, RPBowCameraTransform* transform);
    void fn_80316638();
    void UpdateAllEntities();
    void fn_803165D4();
    void fn_803165D0();
    void UpdateRenderModeAlpha(u32 mode, float fVal);
};

class RPBowGlobalLaneManager {
public:
    // total size: 0x24
    u8 pad_00[0x04];         // offset 0x0, size 0x4
    LaneContext* pLanes[7];  // offset 0x4, size 0x1C
    u8 isInitialized;        // offset 0x20, size 0x1
    u8 field_0x21;           // offset 0x21, size 0x1
    u8 pad_22[0x2];          // offset 0x22, size 0x2

    void InitializeLaneContexts(RPBowSceneObjectManager* objectManager);
    void InitializeBallManagerLanes();
    void SetupBallManagerLaneObjects(void* arg1, void* arg2);
    void ResetLanePinsAndAnimations();
    void SetLaneUnknownState(int value);
    void UpdateBallsPhysics();
    void TickNpcLanes();
    void UpdateLaneItems(RPBowCameraTransform* transform, CameraProjection* pObj, RPBowSceneObjectManager* pObjectManager, bool isPlayerTurn);
    void UpdateBallsMdl(RPBowSceneObjectManager* pObjectManager);
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
    void LinkNpcLanes(RPBowGlobalLaneManager* laneManager, RPBowSceneObjectManager* sceneObjectManager);
    void SetNpcStateFlags(u8 flag);
    void UpdateNpcs();
    void DebugPrintStates();
};

enum BowlingGameStates {
    BOWLING_GAME_STATE_START_GAME_CAMERA_DEMO = 0,  // Initial camera demo at the start of the game
    BOWLING_GAME_STATE_PLAYER_SCORE_VIEW = 1,       // Displaying player scores
    BOWLING_GAME_STATE_MAIN_BOWLING_VIEW = 2,       // Active bowling gameplay (adjusting shot, throwing)
    BOWLING_GAME_STATE_FAILED_BOWL_MESSAGE = 3,     // "Failed to bowl properly" error message
    BOWLING_GAME_STATE_REPLAY = 4,                  // Ball rolling replay
    BOWLING_GAME_STATE_END_GAME_CAMERA_DEMO = 5,    // Final camera demo at the end of the game
    BOWLING_GAME_STATE_UNUSED_6 = 6,                // Unused
    BOWLING_GAME_STATE_SKILL_LEVEL_SCREEN = 7,      // Skill level screen
    BOWLING_GAME_STATE_UNUSED_8 = 8,                // Unused
    BOWLING_GAME_STATE_GAME_FINISHED = 9,           // Game finished screen
};

struct SwingHistoryBuffer {
    // total size: 0x1B8. Confirmed by fn_8031EBC8 in tu5
    float unkFloats_0x0[96];    // offset 0x0, size 0x180
    int field_0x180;            // offset 0x180, size 0x4
    int field_0x184;            // offset 0x184, size 0x4
    int field_0x188;            // offset 0x188, size 0x4
    int unkCounter_0x18C;       // offset 0x18C, size 0x4
    int unkCounterLimit_0x190;  // offset 0x190, size 0x4
    void* unkPtr_0x198;         // offset 0x194, size 0x4
    int field_0x198;            // offset 0x198, size 0x4
    int field_0x19C;            // offset 0x19C, size 0x4
    int field_0x1A0;            // offset 0x1A0, size 0x4
    float unkFloats_0x1A4[5];   // offset 0x1A4, size 0x14

    SwingHistoryBuffer(int param);
};

struct BowlingSwing {
    // total size: 0xDC
    u8 field_0x0;             // offset 0x0, size 0x1
    u8 field_0x1;             // offset 0x1, size 0x1
    u8 field_0x2;             // offset 0x2, size 0x1
    u8 field_0x3;             // offset 0x3, size 0x1
    int field_0x4;            // offset 0x4, size 0x4
    u8 pad_0x8[0x4];          // offset 0x8, size 0x4
    int field_0xC;            // offset 0xC, size 0x4
    int counter_0x10;         // offset 0x10, size 0x4
    float field_0x14;         // offset 0x14, size 0x4
    float field_0x18;         // offset 0x18, size 0x4
    float field_0x1C;         // offset 0x1C, size 0x4
    float field_0x20;         // offset 0x20, size 0x4
    float field_0x24;         // offset 0x24, size 0x4
    float field_0x28;         // offset 0x28, size 0x4
    u8 field_0x2C;            // offset 0x2C, size 0x1
    u8 pad_0x2D[0x3];         // offset 0x2D, size 0x3
    float field_0x30;         // offset 0x30, size 0x4
    u8 pad_0x34[0x4];         // offset 0x34, size 0x4
    int counter_0x38;         // offset 0x38, size 0x4
    float field_0x3C;         // offset 0x3C, size 0x4
    float field_0x40;         // offset 0x40, size 0x4
    float field_0x44;         // offset 0x44, size 0x4
    float field_0x48;         // offset 0x48, size 0x4
    float field_0x4C;         // offset 0x4C, size 0x4
    int int_0x50;             // offset 0x50, size 0x4
    u8 isSwinging;            // offset 0x54, size 0x1
    u8 pad_0x55[0x3];         // offset 0x55, size 0x3
    int field_0x58;           // offset 0x58, size 0x4
    int field_0x5C;           // offset 0x5C, size 0x4
    float field_0x60;         // offset 0x60, size 0x4
    int field_0x64;           // offset 0x64, size 0x4
    int field_0x68;           // offset 0x68, size 0x4
    int field_0x6C;           // offset 0x6C, size 0x4
    u8 pad_0x70[0x14];        // offset 0x70, size 0x14
    float field_0x84;         // offset 0x84, size 0x4
    float field_0x88;         // offset 0x88, size 0x4
    int counter_0x8C;         // offset 0x8C, size 0x4
    float field_0x90;         // offset 0x90, size 0x4
    float field_0x94;         // offset 0x94, size 0x4
    float field_0x98;         // offset 0x98, size 0x4
    float field_0x9C;         // offset 0x9C, size 0x4
    float field_0xA0;         // offset 0xA0, size 0x4
    int counter_0xA4;         // offset 0xA4, size 0x4
    int counter_0xA4_Result;  // offset 0xA8, size 0x4
    u8 pad_0xAC[0x4];         // offset 0xAC, size 0x4
    int counter_0xB0;         // offset 0xB0, size 0x4
    float field_0xB4;         // offset 0xB4, size 0x4
    float field_0xB8;         // offset 0xB8, size 0x4
    float field_0xBC;         // offset 0xBC, size 0x4
    float field_0xC0;         // offset 0xC0, size 0x4
    float field_0xC4;         // offset 0xC4, size 0x4
    float field_0xC8;         // offset 0xC8, size 0x4
    u8 pad_0xCC[0x4];         // offset 0xCC, size 0x4
    float field_0xD0;         // offset 0xD0, size 0x4
    float field_0xD4;         // offset 0xD4, size 0x4
    float field_0xD8;         // offset 0xD8, size 0x4
};

struct BowlingSwingContext {
    // total size: 0x14C
    void* vtable;                      // offset 0x0, size 0x4
    void* unkPtr_0x4;                  // offset 0x4, size 0x4
    SwingHistoryBuffer* swingHistory;  // offset 0x8, size 0x4
    u8 byte_0x0C;                      // offset 0xC, size 0x1
    u8 pad_0xD[0x03];                  // offset 0xD, size 0x3
    BowlingSwing swing;                // offset 0x10, size 0xDC
    float field_0xEC;                  // offset 0xEC, size 0x4
    float field_0xF0;                  // offset 0xF0, size 0x4
    float field_0xF4;                  // offset 0xF4, size 0x4
    float field_0xF8;                  // offset 0xF8, size 0x4
    int field_0xFC;                    // offset 0xFC, size 0x4
    float field_0x100;                 // offset 0x100, size 0x4
    float field_0x104;                 // offset 0x104, size 0x4
    int field_0x108;                   // offset 0x108, size 0x4
    int field_0x10C;                   // offset 0x10C, size 0x4
    int field_0x110;                   // offset 0x110, size 0x4
    bool byte_0x114;                   // offset 0x114, size 0x1
    u8 pad_0x115[3];                   // offset 0x115, size 0x3
    float field_0x118;                 // offset 0x118, size 0x4
    int int_0x11C;                     // offset 0x11C, size 0x4
    int int_0x120;                     // offset 0x120, size 0x4
    int pad_0x124;                     // offset 0x124, size 0x4
    int field_0x128;                   // offset 0x128, size 0x4
    float field_0x12C;                 // offset 0x12C, size 0x4
    int field_0x130;                   // offset 0x130, size 0x4
    float field_0x134;                 // offset 0x134, size 0x4
    float field_0x138;                 // offset 0x138, size 0x4
    int field_0x13C;                   // offset 0x13C, size 0x4
    float field_0x140;                 // offset 0x140, size 0x4
    float field_0x144;                 // offset 0x144, size 0x4
    int field_0x148;                   // offset 0x148, size 0x4
};

struct ControllerWrapper {
    // total size: 0x10
    u32 id;               // offset 0x0, size 0x4
    int controllerIndex;  // offset 0x4, size 0x4
    u8 isActive;          // offset 0x8, size 0x1
    u8 flag_0x9;          // offset 0x9, size 0x1
    u8 pad_0xA[0x2];      // offset 0xA, size 0x2
    int field_0x0C;       // offset 0xC, size 0x4
};

struct ControllerWrapperManager {
    // total size: 0x10
    u8 flag_00;                            // offset 0x0, size 0x1
    u8 flag_01;                            // offset 0x1, size 0x1
    u8 flag_02;                            // offset 0x2, size 0x1
    u8 flag_03;                            // offset 0x3, size 0x1
    u8 flag_04;                            // offset 0x4, size 0x1
    u8 flag_05;                            // offset 0x5, size 0x1
    u8 flag_06;                            // offset 0x6, size 0x1
    u8 flag_07;                            // offset 0x7, size 0x1
    ControllerWrapper* controllerWrapper;  // offset 0x8, size 0x4
    int field_0x0C;                        // offset 0xC, size 0x4
};

struct BowlerState {
    // total size: 0x2C
    float field_0x0;           // offset 0x0, size 0x4
    float playerLaneRotation;  // offset 0x4, size 0x4
    float playerLanePosition;  // offset 0x8, size 0x4
    int playInRotationMode;    // offset 0xC, size 0x4
    u8 field_0x10;             // offset 0x10, size 0x1
    u8 field_0x11;             // offset 0x11, size 0x1
    u8 field_0x12;             // offset 0x12, size 0x1
    u8 field_0x13;             // offset 0x13, size 0x1
    u8 field_0x14;             // offset 0x14, size 0x1
    u8 field_0x15;             // offset 0x15, size 0x1
    u8 field_0x16;             // offset 0x16, size 0x1
    u8 field_0x17;             // offset 0x17, size 0x1
    float field_0x18;          // offset 0x18, size 0x4
    int field_0x1C;            // offset 0x1C, size 0x4
    int unkLaneSideToggle;     // offset 0x20, size 0x4 - Determines whether the ball will have left or right spin based off playerLaneRotation and playerLanePosition.
    u8 pad_0x24[0x4];          // offset 0x24, size 0x4
    int unkCounter_0x28;       // offset 0x28, size 0x4
    u8 pad_0x2C[0x4];          // offset 0x2C, size 0x4
};

struct BowlerContext {
    // total size: 0x528
    void* vtable;                       // offset 0x0, size 0x4
    float field_0x04;                   // offset 0x4, size 0x4
    float field_0x08;                   // offset 0x8, size 0x4
    float field_0x0C;                   // offset 0xC, size 0x4
    u8 pad_0x10[0x488];                 // offset 0x10, size 0x488
    u8 field_0x498;                     // offset 0x498, size 0x1
    u8 pad_0x499[0x13];                 // offset 0x499, size 0x13
    int field_0x4AC;                    // offset 0x4AC, size 0x4
    u8 pad_0x4B0[0x4];                  // offset 0x4B0, size 0x4
    float releaseAngleDeg_Neg_LerpMin;  // offset 0x4B4, size 0x4
    float releaseAngleDeg_Neg_LerpMax;  // offset 0x4B8, size 0x4
    float ballPowerFactor_Neg_Min;      // offset 0x4BC, size 0x4
    float ballPowerFactor_Neg_Max;      // offset 0x4C0, size 0x4
    float releaseAngleDeg_Pos_LerpMin;  // offset 0x4C4, size 0x4
    float releaseAngleDeg_Pos_LerpMax;  // offset 0x4C8, size 0x4
    float ballPowerFactor_Pos_Min;      // offset 0x4CC, size 0x4
    float ballPowerFactor_Pos_Max;      // offset 0x4D0, size 0x4
    u8 pad_0x4D4[0x14];                 // offset 0x4D4, size 0x14
    BowlerState bowlerState;            // offset 0x4E8, size 0x30
    BowlingSwingContext* swingCtx;      // offset 0x518, size 0x4
    LaneContext* laneContext;           // offset 0x51C, size 0x4
    RPBowLaneDataHolder* laneData;      // offset 0x520, size 0x4
    ControllerWrapper* controller;      // offset 0x524, size 0x4
};

struct BowlingRoundData {
    // total size: 0x4C
    u8 throws[3];          // offset 0x0, size 0x3
    u8 pad_0x03[0x1];      // offset 0x3, size 0x1
    int roundScore;        // offset 0x4, size 0x4
    u8 field_0x08;         // offset 0x8, size 0x1
    u8 pad_0x9[0x3];       // offset 0x9, size 0x3
    u8 pad_0x0C[0x4];      // offset 0xC, size 0x4
    PinStatus bonuses[3];  // offset 0x10, size 0x3C
};

class RPBowScoreManager {
public:
    // total size: 0xDC0

    virtual int GetMaxIter();      // offset 0x8 vtable call
    virtual int GetPlayerIndex();  // offset 0xC vtable call

    void* unkPtr_0x4;                      // offset 0x4, size 0x4
    int currentRound;                      // offset 0x8, size 0x4
    int currentRoundThrow;                 // offset 0xC, size 0x4
    int field_0x10;                        // offset 0x10, size 0x4
    int field_0x14;                        // offset 0x14, size 0x4
    int field_0x18;                        // offset 0x18, size 0x4
    u8 wasStrike;                          // offset 0x1C, size 0x1
    u8 wasSpare;                           // offset 0x1D, size 0x1
    u8 pad_0x1E[0x2];                      // offset 0x1E, size 0x2
    int recentPinsKnocked;                 // offset 0x20, size 0x4
    u8 field_0x24;                         // offset 0x24, size 0x1
    u8 pad_0x25[0x3];                      // offset 0x25, size 0x3
    ControllerWrapperManager* cwm;         // offset 0x28, size 0x4
    u8 pad_0x2C[0x4];                      // offset 0x2C, size 0x4
    int consecutiveStrikes;                // offset 0x30, size 0x4
    int field_0x34;                        // offset 0x34, size 0x4
    PinStatus prevBonuses1[2];             // offset 0x38, size 0x28
    float unkFloat_0x60;                   // offset 0x60, size 0x4
    float unkFloat_0x64;                   // offset 0x64, size 0x4
    float unkFloat_0x68;                   // offset 0x68, size 0x4
    float unkFloat_0x6C;                   // offset 0x6C, size 0x4
    float unkFloat_0x70;                   // offset 0x70, size 0x4
    PinStatus prevBonuses2[3];             // offset 0x74, size 0x3C
    BowlingRoundData playerFrames[4][11];  // offset 0xB0, size 0xD10

    void fn_8032B3AC();
    float CalcNewSkill(u32 playerIdx, float currentSkill);
    void fn_8032AE9C();
    float fn_8032AE54();
};

struct DebugOverlaySettings {
    // total size: 0x34
    u8 pad_0x0[0x1];   // offset 0x0, size 0x1
    u8 showScore;      // offset 0x1, size 0x1
    u8 pad_0x2[0x2];   // offset 0x2, size 0x2
    u8 field_0x4;      // offset 0x4, size 0x1
    u8 field_0x5;      // offset 0x5, size 0x1
    u8 pad_0x6[0x2];   // offset 0x6, size 0x2
    u8 field_0x8;      // offset 0x8, size 0x1
    u8 pad_0x9[0x1];   // offset 0x9, size 0x1
    u8 field_0xA;      // offset 0xA, size 0x1
    u8 field_0xB;      // offset 0xB, size 0x1
    u8 pad_0xC[0x2];   // offset 0xC, size 0x2
    u8 showDebugA;     // offset 0xE, size 0x1
    u8 pad_0xF[0x4];   // offset 0xF, size 0x4
    u8 showDebugB;     // offset 0x13, size 0x1
    u8 pad_0x14[0x1];  // offset 0x14, size 0x1
    u8 showDebugC;     // offset 0x15, size 0x1
    u8 pad_0x16[0x2];  // offset 0x16, size 0x2
    u8 showDebugD;     // offset 0x18, size 0x1
    u8 field_0x19;     // offset 0x19, size 0x1
    u8 pad_0x1A[0x8];  // offset 0x1A, size 0x8
    u8 field_0x22;     // offset 0x22, size 0x1
    u8 field_0x23;     // offset 0x23, size 0x1
    u8 pad_0x24[0x4];  // offset 0x24, size 0x4
    int field_0x28;    // offset 0x28, size 0x4
    u8 pad_0x2C[0x4];  // offset 0x2C, size 0x4
    int counter;       // offset 0x30, size 0x4
};

struct UnkModeVal5 {
    void* vtable;      // offset 0x0, size 0x4
    void* unkPtr_0x4;  // offset 0x4, size 0x4
    u8 pad_0x8[0x64];  // offset 0x8, size 0x64
    void* field_0x6C;  // offset 0x6C, size 0x4
};

struct RPBowGameModeState {
    // total size: 0x84
    DebugOverlaySettings current;   // offset 0x0, size 0x34
    DebugOverlaySettings previous;  // offset 0x34, size 0x34

    // Either a RPBowScoreManager or DebugOverlaySub2 can be stored here for some reason.
    void* modeVal1;                 // offset 0x68, size 0x4
    void* modeVal2;                 // offset 0x6C, size 0x4
    void* modeVal3;                 // offset 0x70, size 0x4
    void* modeVal4;                 // offset 0x74, size 0x4

    // Stores some unknown struct
    UnkModeVal5* modeVal5;          // offset 0x78, size 0x4

    int field_0x7C;                 // offset 0x7C, size 0x4
    void* startupModePtr;           // offset 0x80, size 0x4
};

struct PinHitState {
    // total size: 0x8
    f32 hitTimer;  // offset 0x0, size 0x4
    f32 unk_04;    // offset 0x4, size 0x4
};

struct ObstacleDef {
    // total size: 0x10
    f32 scale;    // offset 0x0, size 0x4
    f32 unk_04;   // offset 0x4, size 0x4
    f32 offsetX;  // offset 0x8, size 0x4
    f32 offsetZ;  // offset 0xC, size 0x4
};

struct ObstacleSet {
    // total size: 0x150
    ObstacleDef obstacles[16];  // offset 0x0, size 0x100
    PinHitState pins[10];       // offset 0x100, size 0x50
};

struct CollisionTriangleState {
    // total size: 0x58
    nw4r::math::VEC3 vec0;    // offset 0x0, size 0xC
    nw4r::math::VEC3 vec1;    // offset 0xC, size 0xC
    nw4r::math::VEC3 vec2;    // offset 0x18, size 0xC

    nw4r::math::VEC3 cross0;  // offset 0x24, size 0xC
    nw4r::math::VEC3 cross1;  // offset 0x30, size 0xC
    nw4r::math::VEC3 cross2;  // offset 0x3C, size 0xC
    nw4r::math::VEC3 cross3;  // offset 0x48, size 0xC

    f32 edgeBias;             // offset 0x54, size 0x4
};

struct ObstacleInstance {
    // total size: 0x524
    u8 active;                             // offset 0x0, size 0x1
    u8 pad0[0x3];                          // offset 0x1, size 0x3
    CollisionTriangleState triangles[12];  // offset 0x4, size 0x420
    PhysicsBody body;                      // offset 0x424, size 0xFC
    f32 baseScale;                         // offset 0x520, size 0x4
};

class RPBowObstacleManager {
public:
    // total size: 0x14
    ObstacleInstance* obstacles;  // offset 0x0, size 0x4
    void* unkPointers[2];         // offset 0x4, size 0x8
    void* unkPtr_0xC;             // offset 0xC, size 0x8
    ObstacleSet* dataPtr;         // offset 0x10, size 0x4

    u32 CheckObstacleCollision(u32 obstacleSetIdx, nw4r::math::VEC3* ball);
    u32 CheckObstaclePassed(u32 obstacleSetIdx, nw4r::math::VEC3* ball);
    void ResetLaneObstacles(u32 obstacleSetIdx, u32 isRightSide, f32 spawnZ);
    void UpdateObstacleCollisionBounds();
};

struct unkFrameScore {
    // total size: 0x4c
    PinStatus firstThrowPins;   // 0x00, size: 0x14
    PinStatus secondThrowPins;  // 0x14, size: 0x14
    u8 padding[0x24];           // 0x28 -> 0x4c
};

struct unkPlayerScore {
    // total size: 0x344
    unkFrameScore frames[11];  // 11 frames * 0x4c = 0x344
};

struct unkGameState_8032E2C4 {
    u8 pad00[0x8];
    s32 currentFrame;           // 0x08
    s32 currentThrow;           // 0x0C (0 = None, 1 = First, 2 = Second)
    u32 currentPlayer;          // 0x10
    u8 pad14[0x4];
    s32 targetFrame;            // 0x18
    u8 pad1C[0x58];             // Padding to reach 0x74

    unkPlayerScore players[4];  // 0x74, Array of players
};

struct RPBowGameManager {
    // total size: 0x78
    void* vtable;                               // offset 0x0, size 0x4
    RPBowGameModeState* gameModeState;          // offset 0x4, size 0x4
    RPBowSceneObjectManager* objectManager;     // offset 0x8, size 0x4
    RPBowLaneDataHolder* laneData;              // offset 0xC, size 0x4
    RPBowCameraTransform* cameraTransform;      // offset 0x10, size 0x4
    RPBowScoreManager* bowlingScoreManager;     // offset 0x14, size 0x4
    BowlerContext* bowlerContext;               // offset 0x18, size 0x4
    RPBowGlobalLaneManager* globalLaneManager;  // offset 0x1C, size 0x4
    BowlingSwingContext* swing;                 // offset 0x20, size 0x4

    // ManagerContext is used in all modes except for Spin Control
    union {
        RPBowManagerContext* managerContext;    // offset 0x24, size 0x4
        RPBowObstacleManager* obstacleData;     // offset 0x24, size 0x4
    };
    ControllerWrapper* controllerWrapper;       // offset 0x28, size 0x4
    UnkModeVal5* unkModeVal5;                   // offset 0x2C, size 0x4
    void* unkPtr_0x30;                          // offset 0x30, size 0x4
    void* unkPtr_0x34;                          // offset 0x34, size 0x4
    u8 pad_0x38[0x4];                           // offset 0x38, size 0x4
    BowlingGameStates bowlingGameState;         // offset 0x3C, size 0x4
    int sceneFrameCounter;                      // offset 0x40, size 0x4
    int field_0x44;                             // offset 0x44, size 0x4
    int replayFrameCounter;                     // offset 0x48, size 0x4
    u8 field_0x4C;                              // offset 0x4C, size 0x1
    u8 pad_0x4D[0x03];                          // offset 0x4D, size 0x3
    ControllerWrapperManager* cwm;              // offset 0x50, size 0x4
    u8 field_0x54;                              // offset 0x54, size 0x1
    u8 pad_0x55[0x03];                          // offset 0x55, size 0x3
    float playerLanePosition;                   // offset 0x58, size 0x4
    float playerLaneRotation;                   // offset 0x5C, size 0x4
    int inputIdleTimer;                         // offset 0x60, size 0x4
    u8 pad_0x64[0x4];                           // offset 0x64, size 0x4
    u8 pad_0x68[0x4];                           // offset 0x68, size 0x4
    int field_0x6C;                             // offset 0x6C, size 0x4
    u8 field_0x70;                              // offset 0x70, size 0x1
    u8 field_0x71;                              // offset 0x71, size 0x1
    u8 isScoreViewHidden;                       // offset 0x72, size 0x1
    u8 pad_0x73;                                // offset 0x73, size 0x1
    int field_0x74;                             // offset 0x74, size 0x4

    void InitializeBowlingGameCtx(int arg1, int arg2, ControllerWrapperManager* cwm, u8 arg4, int, int arg5);
    void fn_8032EFF8();
    bool UpdateGameState();
    void ExecuteGameModeUpdateTick(u32 majorState, int minorState);
    void StartGameCameraDemoProc();
    void PlayerScoreViewProc();
    int GetNumRemainingPins(PinStatus* param_1);
    int GetNumDownedPins(PinStatus* param_1);
    bool fn_8032E2C4(unkGameState_8032E2C4* ptr);
    void MainBowlingViewProc();
    void FailedBowlMessageProc();
    void ReplayProc();
    void EndGameProc();
    void SetScoreViewAndCullNpcs(int isScoreViewHidden);
    void UnusedState8Proc();

};

struct DebugOverlaySub1 {
    // total size: 0x3E4
    u8 pad_00[0xD8];       // offset 0x0, size 0xD8
    u32 trackingValue1;    // offset 0xD8, size 0x4
    u8 pad_DC[0x304];      // offset 0xDC, size 0x304
    float trackingValue2;  // offset 0x3E0, size 0x4
};

struct DebugOverlaySub2 {
    // total size: 0xE4
    u8 pad_00[0x10];        // offset 0x0, size 0x10
    u32 validCount;         // offset 0x10, size 0x4
    u8 isValidArray[0xCC];  // offset 0x14, size 0xCC
    float trackingValue3;   // offset 0xE0, size 0x4
};

struct UnkBowlingObj1 {
    // total size: 0x29DC
    u8 pad_0x0[0x4];                // offset 0x0, size 0x4
    u32* unk_0x4;                   // offset 0x4, size 0x4
    nw4r::math::VEC3* vecArray1;    // offset 0x8, size 0x4
    u8 pad_0xC[0x8];                // offset 0xC, size 0x8
    u32 someIndex;                  // offset 0x14, size 0x4
    u8 pad_0x18[0x1FFC];            // offset 0x18, size 0x1FFC
    u32 i_2014;                     // offset 0x2014, size 0x4
    u8 pad_0x2018[0x68];            // offset 0x2018, size 0x68
    f32 f_2080;                     // offset 0x2080, size 0x4
    f32 f_2084;                     // offset 0x2084, size 0x4
    s32 i_2088;                     // offset 0x2088, size 0x4
    f32 f_208C;                     // offset 0x208C, size 0x4
    f32 f_2090;                     // offset 0x2090, size 0x4
    u8 pad_0x2094[0xC];             // offset 0x2094, size 0xC
    f32 f_20A0;                     // offset 0x20A0, size 0x4
    f32 f_20A4;                     // offset 0x20A4, size 0x4
    u8 pad_0x20A8[0x34];            // offset 0x20A8, size 0x34
    int field_0x20DC;               // offset 0x20DC, size 0x4
    int field_0x20E0;               // offset 0x20E0, size 0x4
    u8 pad_0x20E4[0x868];           // offset 0x20E4, size 0x868
    s32 i_294C;                     // offset 0x294C, size 0x4
    u8 pad_0x2950[0x4];             // offset 0x2950, size 0x4
    nw4r::math::VEC3 vec_2954[11];  // offset 0x2954, size 0x84
    u8 flag_0x29D8;                 // offset 0x29D8, size 0x1
    u8 pad29DC[0x3];                // offset 0x29D9, size 0x3
};

struct RPBowSceneDirector : public IRPSysHostIOSocket {
    virtual ~RPBowSceneDirector();

    void* unkPtr_0x4;                         // offset 0x4, size 0x4
    RPBowSceneObjectManager* objectManager;   // offset 0x8, size 0x4
    RPBowCameraController* cameraController;  // offset 0xC, size 0x4
    CameraProjection* cameraProjection;       // offset 0x10, size 0x4
    RPBowCameraTransform* cameraTransform;    // offset 0x14, size 0x4
    RPBowLaneDataHolder* laneData;            // offset 0x18, size 0x4
    LaneContext* laneContext;                 // offset 0x1C, size 0x4
    int frame;                                // offset 0x20, size 0x4

    void fn_8034C8D4(RPBowSceneObjectManager* objectManager, RPBowCameraController* camController, RPBowCameraTransform* cameraTransform, CameraProjection* cameraProjection, RPBowLaneDataHolder* laneData, LaneContext* laneContext);
    void fn_8034C6B0(int param1, int param2, u8* param3, int param4, int frame);
    void fn_8034C6AC();
    void fn_8034C230();
    void fn_8034C1AC(u32 state, int p3);
};

struct SceneContext {
    // total size: 0xC64
    u8 pad_0x0[0x4];      // offset 0x0, size 0x4
    u32 mUnk4;            // offset 0x4, size 0x4
    u8 pad_0x8[0x2C];     // offset 0x8, size 0x2C
    u8 mUnk34;            // offset 0x34, size 0x1
    u8 pad_0x35[0x3];     // offset 0x35, size 0x3
    u8 pad_0x38[0xBE4];   // offset 0x38, size 0xBE4
    u8 mUnkC1C;           // offset 0xC1C, size 0x1
    u8 pad_0xC1D[0x3];    // offset 0xC1D, size 0x3
    PinStatus pinStatus;  // offset 0xC20, size 0x14
    u8 mUnkC34;           // offset 0xC34, size 0x1
    u8 pad_0xC35[0x3];    // offset 0xC35, size 0x3
    s32 field_0xC38;      // offset 0xC38, size 0x4
    s32 field_0xC3C;      // offset 0xC3C, size 0x4
    s32 field_0xC40;      // offset 0xC40, size 0x4
    u8 mUnkC44;           // offset 0xC44, size 0x1
    u8 unkC45[10];        // offset 0xC45, size 0xA
    u8 pad_0xC4F[0x1];    // offset 0xC4F, size 0x1
    s32 unkC50;           // offset 0xC50, size 0x4
    u8 mUnkC54;           // offset 0xC54, size 0x1
    u8 mUnkC55;           // offset 0xC55, size 0x1
    u8 pad_0xC56[0x2];    // offset 0xC56, size 0x2
    s32 field_0xC58;      // offset 0xC58, size 0x4
    u8 pad_0xC5C[0x1];    // offset 0xC5C, size 0x1
    u8 mUnkC5D;           // offset 0xC5D, size 0x1
    u8 pad_0xC5E[0x2];    // offset 0xC5E, size 0x2
    s32 unkC60;           // offset 0xC60, size 0x4
};

struct DummyLayoutBase {
    // total size: 0xC
    virtual void dummy();

    u8 mUnk4;         // offset 0x4, size 0x1
    u8 pad_0x5[0x3];  // offset 0x5, size 0x3
    u8 pad_0x8[0x4];  // offset 0x8, size 0x4
};

struct PlayerFrame {
    // total size: 0x40
    RPSysLayout* layout;            // offset 0x0, size 0x4
    nw4r::lyt::Pane* scoreBG;       // offset 0x4, size 0x4
    nw4r::lyt::Pane* rootPane;      // offset 0x8, size 0x4
    f32 rootX;                      // offset 0xC, size 0x4
    f32 rootY;                      // offset 0x10, size 0x4
    nw4r::lyt::TextBox* throwT[3];  // offset 0x14, size 0xC
    nw4r::lyt::TextBox* totalT;     // offset 0x20, size 0x4
    nw4r::lyt::Pane* strikeP[3];    // offset 0x24, size 0xC
    nw4r::lyt::Pane* spareP[3];     // offset 0x30, size 0xC
    u8 alpha;                       // offset 0x3C, size 0x1
    u8 pad3D[3];                    // offset 0x3D, size 0x3
};

class RPBowScoreLayout : public DummyLayoutBase, public IRPSysHostIOSocket {
public:
    // total size: 0xBD0
    virtual ~RPBowScoreLayout();

    RPSysLayout* mpLayout;               // offset 0x10, size 0x4
    PlayerFrame mFrames[4][11];          // offset 0x14, size 0xB00

    nw4r::lyt::Pane* mpFrameBGP[11];     // offset 0xB14, size 0x2C
    nw4r::lyt::TextBox* mpFrameT[11];    // offset 0xB40, size 0x2C
    nw4r::lyt::Picture* mpPlayerBGP[4];  // offset 0xB6C, size 0x10

    u32 unkB7C;                          // offset 0xB7C, size 0x4
    RPSysKokeshiIcon* mpIcons[4];        // offset 0xB80, size 0x10
    nw4r::lyt::Pane* mpPlayerIconP[4];   // offset 0xB90, size 0x10

    u32 unkBA0;                          // offset 0xBA0, size 0x4
    u32 unkBA4;                          // offset 0xBA4, size 0x4
    u32 unkBA8;                          // offset 0xBA8, size 0x4

    nw4r::math::VEC3 mScoreRoot;         // offset 0xBAC, size 0xC

    nw4r::lyt::Pane* mpScoreRootP;       // offset 0xBB8, size 0x4
    nw4r::lyt::Pane* mpRootPane;         // offset 0xBBC, size 0x4

    f32 unkBC0;                          // offset 0xBC0, size 0x4
    f32 unkBC4;                          // offset 0xBC4, size 0x4

    u32 unkBC8;                          // offset 0xBC8, size 0x4
    u32 unkBCC;                          // offset 0xBCC, size 0x4

    void Init(RPSysLytResAccessor* acc, u32 unk);
    void InitIcons();
    void Reset();
};

class RPBowNormalPinLayout : public DummyLayoutBase, public IRPSysHostIOSocket {
public:
    virtual ~RPBowNormalPinLayout();

    RPSysLayout* mpLayout;            // offset 0x10, size 0x4
    s32 mAnimationState;              // offset 0x14, size 0x4
    nw4r::lyt::Pane* mpRootPane;      // offset 0x18, size 0x4
    nw4r::lyt::Pane* mpPinPanes[10];  // offset 0x1C, size 0x28

    void Init(RPSysLytResAccessor* acc);
    void Reset();
    void Update(SceneContext* pContext);
    void Draw();
    bool IsFinished() const;
};

struct StagePane {
    // total size: 0xC
    nw4r::lyt::Pane* lineBG;   // offset 0x0, size 0x4
    nw4r::lyt::Pane* line;     // offset 0x4, size 0x4
    RPSysLytAnmObj* stageAnm;  // offset 0x8, size 0x4
};

class RPBowPowerThrowsPinLayout : public DummyLayoutBase, public IRPSysHostIOSocket {
public:
    virtual ~RPBowPowerThrowsPinLayout();

    RPSysLayout* mpLayout;        // offset 0x10, size 0x4
    s32 mAnimationState;          // offset 0x14, size 0x4
    nw4r::lyt::Pane* mpRootPane;  // offset 0x18, size 0x4
    StagePane mStages[10];        // offset 0x1C, size 0x78
    nw4r::lyt::Pane* mpPins[91];  // offset 0x94, size 0x16C

    void Init(RPSysLytResAccessor* acc);
    void Reset();
    void Update(SceneContext* pContext);
    void Draw();
    bool IsFinished() const;
};

class RPBowGuidanceLayout {
public:
    // total size: 0x24
    void* vtable;                 // offset 0x0, size 0x4
    bool unk04;                   // offset 0x4, size 0x1
    u8 pad_0x5[0x3];              // offset 0x5, size 0x3
    u8 pad_0x8[0x4];              // offset 0x8, size 0x4
    RPSysLayout* mpLayout;        // offset 0xC, size 0x4
    s32 mAnimationState;          // offset 0x10, size 0x4
    RPSysLytAnmObj* mpAnm1;       // offset 0x14, size 0x4
    RPSysLytAnmObj* mpAnm2;       // offset 0x18, size 0x4
    RPSysMessage* mpMessage;      // offset 0x1C, size 0x4
    RPSysLytTextBox* mpTextBox1;  // offset 0x20, size 0x4
    nw4r::lyt::Pane* mpPane1;     // offset 0x24, size 0x4
    u8 mFlag28;                   // offset 0x28, size 0x1
    u8 pad_29[0x3];               // offset 0x29, size 0x3

    void Init(RPSysLytResAccessor* acc, RPSysMessage* msg);
    void Reset();
    void Draw();
    bool IsFinished() const;
};

class RPBowEventTextLayout {
public:
    // total size: 0x24
    void* vtable;                        // offset 0x0, size 0x4
    bool unk04;                          // offset 0x4, size 0x1
    u8 pad_0x5[0x3];                     // offset 0x5, size 0x3
    u8 pad_0x8[0x4];                     // offset 0x8, size 0x4
    RPSysLayout* mpLayout;               // offset 0xC, size 0x4
    RPSysLytTextBox* mpTextBoxes[2][2];  // offset 0x10, size 0x10
    RPSysMessage* mpMessage;             // offset 0x20, size 0x4
    RPSysLytAnmObj* mpAnm1;              // offset 0x24, size 0x4
    RPSysLytAnmObj* mpAnm2;              // offset 0x28, size 0x4
    s32 mAnimationState;                 // offset 0x2C, size 0x4
    nw4r::lyt::Pane* mpPane1;            // offset 0x30, size 0x4
    nw4r::lyt::Pane* mpPane2;            // offset 0x34, size 0x4
    RPSysLytTextBox* mpTextBox5;         // offset 0x38, size 0x4
    RPSysLytTextBox* mpTextBox6;         // offset 0x3C, size 0x4
    RPSysLytAnmObj* mpAnm3;              // offset 0x40, size 0x4
    nw4r::lyt::Pane* mpPane3;            // offset 0x44, size 0x4
    s32 mField48;                        // offset 0x48, size 0x4

    void Init(RPSysLytResAccessor* acc, RPSysMessage* msg);
    void Reset();
    void Update(SceneContext* pContext);
    void Draw();
    bool IsFinished() const;
};

class RPBowTrainingStageLayout {
public:
    // total size: 0x24
    void* vtable;                 // offset 0x0, size 0x4
    bool unk04;                   // offset 0x4, size 0x1
    u8 pad_0x5[0x3];              // offset 0x5, size 0x3
    u8 pad_0x8[0x4];              // offset 0x8, size 0x4
    RPSysLayout* mpLayout;        // offset 0xC, size 0x4
    s32 mAnimationState;          // offset 0x10, size 0x4
    RPSysLytTextBox* mpTextBox1;  // offset 0x14, size 0x4
    RPSysLytTextBox* mpTextBox2;  // offset 0x18, size 0x4
    RPSysMessage* mpMessage;      // offset 0x1C, size 0x4

    void Init(RPSysLytResAccessor* acc, RPSysMessage* msg);
    void Reset();
    void Update(SceneContext* pContext);
    void Draw();
    bool IsFinished() const;
};

class RPBowPowerThrowsStageLayout {
public:
    // total size: 0x24
    void* vtable;                 // offset 0x0, size 0x4
    bool unk04;                   // offset 0x4, size 0x1
    u8 pad_0x5[0x3];              // offset 0x5, size 0x3
    u8 pad_0x8[0x4];              // offset 0x8, size 0x4
    RPSysLayout* mpLayout;        // offset 0xC, size 0x4
    s32 mAnimationState;          // offset 0x10, size 0x4
    RPSysLytTextBox* mpTextBox1;  // offset 0x14, size 0x4
    RPSysLytTextBox* mpTextBox2;  // offset 0x18, size 0x4
    RPSysLytTextBox* mpTextBox3;  // offset 0x1C, size 0x4
    RPSysLytTextBox* mpTextBox4;  // offset 0x20, size 0x4
    RPSysMessage* mpMessage;      // offset 0x24, size 0x4

    void Init(RPSysLytResAccessor* acc, RPSysMessage* msg);
    void Reset();
    void Update(SceneContext* pContext);
    void Draw();
    bool IsFinished() const;
};

class RPBowGameOverLayout {
public:
    // total size: 0x24
    void* vtable;                 // offset 0x0, size 0x4
    bool unk04;                   // offset 0x4, size 0x1
    u8 pad_0x5[0x3];              // offset 0x5, size 0x3
    u8 pad_0x8[0x4];              // offset 0x8, size 0x4
    RPSysLayout* mpLayout;        // offset 0xC, size 0x4
    s32 mAnimationState;          // offset 0x10, size 0x4
    RPSysLytAnmObj* mpUnkAnim;    // offset 0x14, size 0x4
    RPSysLytTextBox* mpTextBox1;  // offset 0x18, size 0x4
    RPSysLytTextBox* mpTextBox2;  // offset 0x1C, size 0x4
    RPSysMessage* mpMessage;      // offset 0x20, size 0x4

    void Init(RPSysLytResAccessor* acc, RPSysMessage* msg);
    void Reset();
    void Update();
    void Draw();
    bool IsFinished() const;
};

class RPBowStrikeLayout {
public:
    // total size: 0x24
    void* vtable;                  // offset 0x0, size 0x4
    bool unk04;                    // offset 0x4, size 0x1
    u8 pad_0x5[0x3];               // offset 0x5, size 0x3
    u8 pad_0x8[0x4];               // offset 0x8, size 0x4
    RPSysLayout* mpLayout;         // offset 0xC, size 0x4
    s32 mAnimationState;           // offset 0x10, size 0x4
    RPSysLytAnmObj* mpStrikeAnim;  // offset 0x14, size 0x4
    RPSysLytTextBox* mpTextBox1;   // offset 0x18, size 0x4
    RPSysLytTextBox* mpTextBox2;   // offset 0x1C, size 0x4
    RPSysMessage* mpMessage;       // offset 0x20, size 0x4

    void Init(RPSysLytResAccessor* pAccessor, RPSysMessage* msg);
    void Reset();
    void Update(SceneContext* pContext);
    void Draw();
    bool IsFinished() const;
};

class RPBowTutorialLayout {
public:
    // total size: 0x30
    void* vtable;              // offset 0x0, size 0x4
    bool unk04;                // offset 0x4, size 0x1
    u8 pad_0x5[0x3];           // offset 0x5, size 0x3
    u8 pad_0x8[0x4];           // offset 0x8, size 0x4
    RPSysLayout* mpLayout;     // offset 0xC, size 0x4
    s32 mAnimationState;       // offset 0x10, size 0x4
    RPSysLytAnmObj* mpObj1;    // offset 0x14, size 0x4
    RPSysLytAnmObj* mpObj2;    // offset 0x18, size 0x4
    RPSysLytAnmObj* mpObj3;    // offset 0x1C, size 0x4
    RPSysMessage* mpMessage;   // offset 0x20, size 0x4
    nw4r::lyt::Pane* mpPane1;  // offset 0x24, size 0x4
    void* mpTutorialHelper;    // offset 0x28, size 0x4
    nw4r::lyt::Pane* mpPane2;  // offset 0x2C, size 0x4

    void Init(RPSysLytResAccessor* acc, RPSysMessage* msg);
    void Reset();
    void Update();
    void Draw();
    bool IsFinished() const;
};

struct TrainingLifePane {
    // total size: 0x28
    RPSysLytAnmObj* bigBallObj;    // offset 0x0, size 0x4
    RPSysLytAnmObj* smallBallObj;  // offset 0x4, size 0x4
    s32 activeIdx1;                // offset 0x8, size 0x4
    RPSysLytAnmObj* colors[5];     // offset 0xC, size 0x14
    s32 activeIdx2;                // offset 0x20, size 0x4
    nw4r::lyt::Pane* pane;         // offset 0x24, size 0x4
};

class RPBowTrainingLivesLayout : public DummyLayoutBase, public IRPSysHostIOSocket {
public:
    virtual ~RPBowTrainingLivesLayout();

    RPSysLayout* mpLayout;          // offset 0x10, size 0x4
    s32 mAnimationState;            // offset 0x14, size 0x4
    nw4r::lyt::Pane* mpRootPane;    // offset 0x18, size 0x4
    TrainingLifePane mAnmPanes[5];  // offset 0x1C, size 0xC8

    void Init(RPSysLytResAccessor* acc);
    void Reset();
    void Update(SceneContext* pContext);
    void Draw();
    bool IsFinished() const;
};

struct PowerThrowsRoundPane {
    // total size: 0x1C
    RPSysLytAnmObj* anmObjs[4];  // offset 0x0, size 0x10
    s32 activeIdx;               // offset 0x10, size 0x4
    nw4r::lyt::Pane* pane1;      // offset 0x14, size 0x4
    nw4r::lyt::Pane* pane2;      // offset 0x18, size 0x4
};

class RPBowPowerThrowsRoundsLayout {
public:
    u8 pad_0[0x4];                       // offset 0x0, size 0x4
    bool unk04;                          // offset 0x4, size 0x1
    u8 pad_5[0x7];                       // offset 0x5, size 0x7
    RPSysLayout* mpLayout;               // offset 0xC, size 0x4
    s32 mAnimationState;                 // offset 0x10, size 0x4
    nw4r::lyt::Pane* mpRootPane;         // offset 0x14, size 0x4
    PowerThrowsRoundPane mAnmPanes[10];  // offset 0x18, size 0x118
    RPSysLytTextBox* mpTextBoxes[2][2];  // offset 0x130, size 0x10
    RPSysMessage* mpMessage;             // offset 0x140, size 0x4

    void Init(RPSysLytResAccessor* acc, RPSysMessage* msg);
    void Reset();
    void Update(SceneContext* pContext);
    void Draw();
    bool IsFinished() const;
};

class RPBowAimGuideLayout : public DummyLayoutBase, public IRPSysHostIOSocket {
public:
    virtual ~RPBowAimGuideLayout();

    RPSysLayout* mpLayout;              // offset 0x10, size 0x4
    u32 mState;                         // offset 0x14, size 0x4
    nw4r::lyt::Pane* mpRootPane;        // offset 0x18, size 0x4
    RPSysLytAnmObj* mpBlinkAnm;         // offset 0x1C, size 0x4
    nw4r::lyt::Pane* mpPlusButton00;    // offset 0x20, size 0x4
    RPSysLytTextBox* mpPlusText00;      // offset 0x24, size 0x4
    RPSysLytTextBox* mpPlusText01;      // offset 0x28, size 0x4
    RPSysLytTextBox* mpAText00;         // offset 0x2C, size 0x4
    RPSysLytTextBox* mpAText01;         // offset 0x30, size 0x4
    RPSysMessage* mpMessage;            // offset 0x34, size 0x4
    u32 mUnk38;                         // offset 0x38, size 0x4
    s32 mUnk3C;                         // offset 0x3C, size 0x4
    u32 mUnk40;                         // offset 0x40, size 0x4
    u32 mUnk44;                         // offset 0x44, size 0x4
    RPSysLytAnmObj* mpChangeAnm[2];     // offset 0x48, size 0x8
    nw4r::lyt::Pane* mpChangePanes[2];  // offset 0x50, size 0x8
    RPSysLytAnmObj* mpOnAnm[2];         // offset 0x58, size 0x8
    RPSysLytAnmObj* mpOffAnm[2];        // offset 0x60, size 0x8
    nw4r::lyt::Pane* mpOnOffPanes[2];   // offset 0x68, size 0x8
    u32 mUnk70;                         // offset 0x70, size 0x4

    void Init(EGG::Heap* pHeap, RPSysMessage* pMsg);
    void Reset();
    void Calc(SceneContext* pContext);
    void Draw();
    bool IsFinished() const;
};

class RPBowPerfectGameUI {
public:
    // total size: 0x24
    u8 pad_0x00[0x4];             // offset 0x0, size 0x4
    u8 mIsVisible;                // offset 0x4, size 0x1
    u8 pad_0x05[0x3];             // offset 0x5, size 0x3
    u32 mDrawGroup;               // offset 0x8, size 0x4
    RPSysLayout* mpLayout;        // offset 0xC, size 0x4
    RPSysEffect* mpHubukiEffect;  // offset 0x10, size 0x4
    s32 mState;                   // offset 0x14, size 0x4
    RPSysLytAnmObj* mpAnmIn;      // offset 0x18, size 0x4
    RPSysLytAnmObj* mpAnmOut;     // offset 0x1C, size 0x4
    nw4r::lyt::Pane* mpRootPane;  // offset 0x20, size 0x4

    void Init(RPSysLytResAccessor* pAccessor, RPSysMessage* pMessage);
    void Reset();
    void Calc();
    void Draw();
};

// Global Data:

struct BallReturnRackConstants {
    // total size: 0x3C
    nw4r::math::VEC3 mPositionOffsets[4];  // offset 0x0, size 0x30
    float mHeightLimit;                    // offset 0x30, size 0x4
    float mRepulsionThreshold;             // offset 0x34, size 0x4
    float mGravity;                        // offset 0x38, size 0x4
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
