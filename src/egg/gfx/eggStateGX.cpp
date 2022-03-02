#include "eggStateGX.h"
#include "eggAssert.h"
#include "g3d_init.h"
#include "g3d_tmem.h"
#include <RevoSDK/GX/GXAttr.h>
#include <RevoSDK/GX/GXBump.h>
#include <RevoSDK/GX/GXGeometry.h>
#include <RevoSDK/GX/GXLight.h>
#include <RevoSDK/GX/GXTexture.h>
#include <RevoSDK/GX/GXTransform.h>

namespace EGG
{
    using namespace nw4r::g3d;

    void StateGX::func_80083E18()
    {
        sStateFlags1 &= ~0x20;

        GXInvalidateTexAll();
        func_80083E5C();
        func_80083EBC();

        sTMemLayout = tmem::TMEM_LAYOUT_1;
        tmem::SetTMemLayout(tmem::TMEM_LAYOUT_1);
    }

    void StateGX::func_80083E5C()
    {
    }

    void StateGX::func_80083EBC()
    {
        func_80084548();
    }

    void StateGX::func_80083EC0()
    {
        func_80083EF8();
        func_80084110();
        func_80084034();
        func_80084188();
        func_8008422C();
        func_800842E0();
        func_80084490();
    }

    void StateGX::func_80083EF8()
    {
        GXSetVtxAttrFmt(0, GX_ATTR_VTX, 1, 4, 0);
        GXSetVtxAttrFmt(0, GX_ATTR_VTX_NRM, 0, 4, 0);
        GXSetVtxAttrFmt(0, GX_ATTR_VTX_CLR, 1, 5, 0);
        GXSetVtxAttrFmt(0, GX_ATTR_VTX_COUNT, 1, 5, 0);
        GXSetVtxAttrFmt(0, GX_ATTR_VTX_TEX_COORD, 1, 3, 7);
        GXSetVtxAttrFmt(0, GX_ATTR_14, 1, 3, 7);
        GXSetVtxAttrFmt(0, GX_ATTR_15, 1, 3, 7);
        GXSetVtxAttrFmt(0, GX_ATTR_16, 1, 3, 7);
        GXSetVtxAttrFmt(0, GX_ATTR_17, 1, 3, 7);
        GXSetVtxAttrFmt(0, GX_ATTR_18, 1, 3, 7);
        GXSetVtxAttrFmt(0, GX_ATTR_19, 1, 3, 7);
        GXSetVtxAttrFmt(0, GX_ATTR_20, 1, 3, 7);
    }

    void StateGX::func_80084034()
    {
        GXSetNumChans(1);

        GXSetChanAmbColor(GX_CHANNEL_ID_4, cAmbColorWhite);
        GXSetChanAmbColor(GX_CHANNEL_ID_5, cAmbColorWhite);
        GXSetChanMatColor(GX_CHANNEL_ID_4, cAmbColorWhite);
        GXSetChanMatColor(GX_CHANNEL_ID_5, cAmbColorWhite);

        GXSetCullMode(2);
        GXSetChanCtrl(GX_CHANNEL_ID_4, 0, 0, 0, 0, 2, 2);
        GXSetChanCtrl(GX_CHANNEL_ID_5, 0, 0, 0, 0, 2, 2);
    }

    void StateGX::func_80084110()
    {
        GXSetNumIndStages(0);

        for (int i = 0; i < 3; i++)
        {
            // TO-DO: This is a 3x4 matrix, but there seems to be 13 floats?
            // GXSetIndTexMtx((GXIndTexMtxID)i, &lbl_80378C68, 1);
        }

        for (int i = 0; i < 3; i++)
        {
            GXSetIndTexCoordScale(GX_IND_TEX_STAGE_0, GX_IND_TEX_SCALE_0, GX_IND_TEX_SCALE_0);
        }
    }

    void StateGX::func_80084188()
    {
        GXTexObj gxTex;
        GXInitTexObj(&gxTex, sTexObjImage, 4, 4, 3, 0, 0, 0);

        GXLoadTexObj(&gxTex, GX_TEX_MAP_ID_0);
        GXLoadTexObj(&gxTex, GX_TEX_MAP_ID_1);
        GXLoadTexObj(&gxTex, GX_TEX_MAP_ID_2);
        GXLoadTexObj(&gxTex, GX_TEX_MAP_ID_3);
        GXLoadTexObj(&gxTex, GX_TEX_MAP_ID_4);
        GXLoadTexObj(&gxTex, GX_TEX_MAP_ID_5);
        GXLoadTexObj(&gxTex, GX_TEX_MAP_ID_6);
        GXLoadTexObj(&gxTex, GX_TEX_MAP_ID_7);
    }

    void StateGX::func_8008422C()
    {
    }

    void StateGX::func_800842E0()
    {
    }

    void StateGX::func_80084490()
    {
    }

    void StateGX::func_80084548()
    {
        sStateFlags2 = 0;
        StateGX::GXSetColorUpdate(true);
        StateGX::GXSetAlphaUpdate(true);
        StateGX::GXSetDither(true);
    }

    void StateGX::GXSetProjection(Mtx mtx, int type)
    {
        switch(type)
        {
            // case 1:
            //     GXSetProjectionv(mtx2);
            // case 0:
            //     GXSetProjectionv(mtx2);
            default:
                EGG_ASSERT(0);
        }
    }

    void StateGX::GXSetProjectionv(const f32 *)
    {
    }

    GXColor StateGX::sDefaultTexColor;
    u16 StateGX::sStateFlags1 = 0x20;
    tmem::TMemLayout StateGX::sTMemLayout = tmem::TMEM_LAYOUT_1;

    u8 StateGX::sTexObjImage[4 * 4];

    const GXColor StateGX::cAmbColorWhite = {255, 255, 255, 255};
}