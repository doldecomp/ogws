#ifndef EGG_GFX_DRAWGX_H
#define EGG_GFX_DRAWGX_H
#include "types_egg.h"
#include "types_nw4r.h"
#include <revolution/GX.h>


namespace EGG
{
    class DrawGX
    {
    public:
        enum Blend
        {
            BLEND_0,
            BLEND_1,
            BLEND_2,
            BLEND_3,
            BLEND_4,
            BLEND_5,
            BLEND_6,
            BLEND_7,
            BLEND_8,
            BLEND_9,

            BLEND_MAX
        };

        enum Circle
        {
            CIRCLE_0
        };

        enum ColorChannel
        {
            COLOR_CHANNEL_0,
            COLOR_CHANNEL_1,
        };

        enum DL
        {
            DL_0,
            DL_1,
            DL_2,
            DL_3,
            DL_4,
            DL_5,
            DL_6,
            DL_7,
            DL_8,
            DL_9,
            DL_10,
            DL_11,
            DL_12,
            DL_13,
            DL_14,
            DL_15,
            DL_16,
            DL_17,

            DL_MAX
        };

        enum DrawGXFlag
        {
            FLAG_INITIALIZE_DISPLAY_LIST = (1 << 0)
        };

        enum TevSetting
        {
            TEV_SETTING_0,
            TEV_SETTING_1,
        };

        enum TexGen
        {
            TEX_GEN_0,
            TEX_GEN_1,
        };

        enum VtxType
        {
            VTX_TYPE_0,
            VTX_TYPE_1,
            VTX_TYPE_2,
            VTX_TYPE_3,
            VTX_TYPE_4,
            VTX_TYPE_5,
            VTX_TYPE_6,
            VTX_TYPE_7,
            VTX_TYPE_8,
            VTX_TYPE_9,
            VTX_TYPE_10,
            VTX_TYPE_11,
            VTX_TYPE_12,
            VTX_TYPE_13
        };

        enum ZMode
        {
            ZMODE_0,
            ZMODE_1,
            ZMODE_2,
            ZMODE_3,

            ZMODE_MAX
        };

        struct DisplayList
        {
            u8 *m_list; // at 0x0
            u32 m_size; // at 0x4
        };

        struct ZModeEntry
        {
            u8 BYTE_0x0;
            UNKWORD WORD_0x4;
            u8 BYTE_0x8;
        };

        struct BlendEntry
        {
            UNKWORD WORD_0x0;
            UNKWORD WORD_0x4;
            UNKWORD WORD_0x8;
            UNKWORD WORD_0xC;
        };

    public:
        static void Initialize(Heap *);
        static void InitTexObj();
        static GXTexMapID GetTexMapDefault();
        static void BeginDrawVtxType0();
        static void BeginDrawVtxType2();
        static void BeginDrawLine(ColorChannel, ZMode);
        static void BeginDrawVtxType5();
        static void BeginDrawCircleZ(ColorChannel, ZMode);
        static void BeginDrawPolygon(ColorChannel);
        static void BeginDrawQuad(ColorChannel, ZMode, Blend, bool, bool);
        static void BeginDrawScreen(bool, bool, bool);
        static void FUN_80087cd4(bool);
        static void DrawLineStrip(const nw4r::math::VEC3 *, u16, GXColor, u8);
        static void DrawLine(const nw4r::math::VEC3 *, u16, GXColor, u8);
        static void DrawCircle2D(Circle, f32, f32, f32, GXColor, u8);
        static void DrawPoint(const nw4r::math::VEC3 *, u16, GXColor, u8);
        static void DrawPolygon(const nw4r::math::VEC3&, const nw4r::math::VEC3&, const nw4r::math::VEC3&, GXColor);
        static void BeginDrawShadowVolumeTexture(bool, GXColor, Blend);
        static void ClearEfb(const nw4r::math::MTX34&, bool, bool, bool, GXColor, bool);
        static void ResetMaterial(ColorChannel);
        static void SetMat_ColorChannel(ColorChannel);
        static void SetMat_TexGen(TexGen);
        static void SetMat_Ind();
        static void SetMat_Tev(int, TevSetting);
        static void SetMat_PE(ZMode, Blend);
        static void LoadTexture(const ResTIMG *, int);
        static void SetVtxState(VtxType);
        static void CreateDisplayList(Heap *);
        static void DrawDL(DL, const nw4r::math::MTX34&);
        static void DrawDL(DL, const nw4r::math::MTX34&, GXColor);
        static void SetZMode(ZMode);
        static void SetBlendMode(Blend);

        static DisplayList * GetDisplayList(u32 i) { return &s_DL[i]; }

    public:
        static const GXColor scColorBlack;
        static const GXColor scColorWhite;
        static const GXColor scColorRed;
        static const GXColor scColorGreen;
        static const GXColor scColorBlue;
        static const GXColor scColorOrange;

        static nw4r::math::MTX34 s_cameraMtx;

    private:
        static DisplayList s_DL[DL_MAX];
        static GXTexObj sTexObj;
        static u8 sClearTex[] __attribute__ ((aligned (32)));

        static u32 s_flag;
        static GXTexMapID sTexMapDefault;

        static const VtxType sVtxTypeMap[3][3];
        static const ZModeEntry sZModeMap[];
        static const BlendEntry sBlendMap[];
    };
}

#endif