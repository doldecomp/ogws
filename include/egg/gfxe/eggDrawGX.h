#ifndef EGG_GFXE_DRAW_GX_H
#define EGG_GFXE_DRAW_GX_H
#include <egg/types_egg.h>

#include <egg/gfx/eggResTIMG.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

namespace EGG {

// Forward declarations
class Heap;

class DrawGX {
public:
    enum Blend {
        BLEND_NORMAL,    // Sc*Sa + Dc*(1-Sa)
        BLEND_INVERSE,   // Sc*(1-Sa) + Dc*Sa
        BLEND_ADD,       // Sc+Dc
        BLEND_ADD_ALPHA, // Sc*Sa + Dc
        BLEND_MUL_ADD,   // Sc*Dc + Dc
        BLEND_SUB,       // Sc - Dc
        BLEND_MUL,       // Dc*Sc
        BLEND_MUL_INV,   // Dc*(1-Sc)
        BLEND_REPLACE,   // Sc
        BLEND_NONE,      // 1

        BLEND_MAX
    };

    enum Circle {
        CIRCLE_16, // Low detail (16 segments)
        CIRCLE_32, // High detail (32 segments)

        CIRCLE_MAX,
    };

    enum ColorChannel {
        COLORCHAN_LIGHT,
        COLORCHAN_COLOR,
    };

    enum DL {
        DL_LINE_AXIS,
        DL_CUBE,
        DL_CUBE_WIRE,
        DL_SPHERE_4X8,
        DL_SPHERE_8X16,
        DL_LINE_CIRCLE_16,
        DL_LINE_CIRCLE_32,
        DL_CIRCLE_16,
        DL_CIRCLE_32,
        DL_CYLINDER_16,
        DL_CYLINDER_32,
        DL_CONE_16,
        DL_CONE_32,
        DL_QUAD_TEXTURE,
        DL_QUAD,
        DL_BOUNDBOX,
        DL_SCREEN_TEXTURE,
        DL_SCREEN,

        DL_MAX
    };

    enum TevSetting {
        TEVSETTING_COLOR,
        TEVSETTING_TEXTURE,
    };

    enum TexGen {
        TEXGEN_DISABLE,
        TEXGEN_ENABLE,
    };

    enum VtxType {
        VTXTYPE_CUBE,
        VTXTYPE_LINE,
        VTXTYPE_SPHERE,
        VTXTYPE_CYLINDER,
        VTXTYPE_CIRCLE,
        VTXTYPE_CONE,
        VTXTYPE_POLYGON,
        VTXTYPE_QUAD_TEXTURE,
        VTXTYPE_QUAD,
        VTXTYPE_QUAD_SHADOW,
        VTX_TYPE_SCREEN_TEXTURE,
        VTX_TYPE_SCREEN_TEXTURE_FLIP,
        VTX_TYPE_SCREEN,
        VTX_TYPE_SCREEN_FLIP
    };

    enum ZMode {
        ZMODE_ALWAYS, // Always draw without updating the Z-buffer
        ZMODE_OPA,    // For opaque draw
        ZMODE_XLU,    // For translucent draw
        ZMODE_CLEAR,  // Always draw and update the Z-buffer

        ZMODE_MAX
    };

public:
    static void Initialize(Heap* pHeap = NULL);
    static GXLightID GetLightMaskDefault();
    static GXTexMapID GetTexMapDefault();

    static void BeginDrawCube();
    static void BeginDrawSphere();
    static void BeginDrawLine(ColorChannel chan, ZMode zMode);
    static void BeginDrawCornY();
    static void BeginDrawCircleZ(ColorChannel chan, ZMode zMode);
    static void BeginDrawPolygon(ColorChannel chan);
    static void BeginDrawQuad(ColorChannel chan, ZMode zMode, Blend blendMode,
                              bool texture, bool alpha);
    static void BeginDrawScreen(bool flip, bool texture, bool alpha);
    static void BeginDrawShadowVolume(u8 alpha);

    static void DrawLine(const nw4r::math::VEC3* pPoints, u16 num,
                         GXColor color, u8 width);
    static void DrawLineStrip(const nw4r::math::VEC3* pPoints, u16 num,
                              GXColor color, u8 width);
    static void DrawCircle2D(Circle circle, f32 x, f32 y, f32 radius,
                             GXColor color);
    static void DrawCornY(Circle circle, const nw4r::math::MTX34& rMtx,
                          GXColor color);
    static void DrawPolygon(const nw4r::math::VEC3& rP0,
                            const nw4r::math::VEC3& rP1,
                            const nw4r::math::VEC3& rP2, GXColor color);

    static void DrawScreenTexture(const nw4r::math::MTX34& rMtx) {
        GXLoadPosMtxImm(rMtx, GX_PNMTX0);
        GXCallDisplayList(s_DL[DL_SCREEN_TEXTURE].m_list,
                          s_DL[DL_SCREEN_TEXTURE].m_size);
    }
    static void DrawScreenTexture(const nw4r::math::MTX34& rMtx,
                                  GXColor color) {
        DrawDL(DL_SCREEN_TEXTURE, rMtx, color);
    }

    static void BeginDrawShadowVolumeTexture(bool flip, GXColor color,
                                             Blend blendMode);

    static void ClearEfb(const nw4r::math::MTX34& rMtx, bool colorUpdate,
                         bool alphaUpdate, bool texture, GXColor color,
                         bool flip);

    static void ResetMaterial(ColorChannel chan);

    static void SetMat_ColorChannel(ColorChannel chan);
    static void SetMat_TexGen(TexGen texGen);
    static void SetMat_Ind();
    static void SetMat_Tev(GXTevStageID stage, TevSetting setting);
    static void SetMat_PE(ZMode zMode, Blend blendMode);

    static void LoadTexture(const ResTIMG* pRes, GXTexMapID map);
    static void SetVtxState(VtxType vtxType);

    static void DrawDL(DL dl, const nw4r::math::MTX34& rMtx);
    static void DrawDL(DL dl, const nw4r::math::MTX34& rMtx, GXColor color);

    static void DrawDLWorld(DL dl, const nw4r::math::MTX34& rMtx,
                            GXColor color) {
        nw4r::math::MTX34 mtx;
        nw4r::math::MTX34Mult(&mtx, &s_cameraMtx, &rMtx);

        DrawDL(dl, mtx, color);
    }

    static void SetZMode(ZMode zMode);
    static void SetBlendMode(Blend blendMode);

    static void SetCameraMtx(const nw4r::math::MTX34& rMtx) {
        s_cameraMtx = rMtx;
    }

public:
    static const GXColor BLACK;
    static const GXColor WHITE;
    static const GXColor RED;
    static const GXColor GREEN;
    static const GXColor BLUE;
    static const GXColor ORANGE;

private:
    struct DLEntry {
        u8* m_list; // at 0x0
        u32 m_size; // at 0x4
    };

    struct ZModeEntry {
        GXBool m_enableTest;   // at 0x0
        GXCompare m_func;      // at 0x4
        GXBool m_enableUpdate; // at 0x8
    };

    struct BlendEntry {
        GXBlendMode m_blendMode;   // at 0x0
        GXBlendFactor m_srcFactor; // at 0x4
        GXBlendFactor m_dstFactor; // at 0x8
        GXLogicOp m_op;            // at 0xC
    };

    enum { FLAG_INITIALIZE_DISPLAY_LIST = 1 << 0 };

private:
    static void InitClearTexObj();
    static void CreateDisplayList(Heap* pHeap);

private:
    static DLEntry s_DL[DL_MAX];
    static const DL s_circleDLTbl[CIRCLE_MAX];

    static nw4r::math::MTX34 s_cameraMtx;
    static u32 s_flag;
};

} // namespace EGG

#endif
