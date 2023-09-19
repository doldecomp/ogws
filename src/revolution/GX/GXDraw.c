#include <math.h>
#include <revolution/GX.h>

// +1 for null terminator
static GXVtxDescList vcd[GX_VA_MAX_ATTR + 1];
static GXVtxAttrFmtList vat[GX_VA_MAX_ATTR + 1];

void GXDrawCylinder(u8 sides) {
    // Unit-circle vertices
    f32 vx[100];
    f32 vy[100];

    f32 z, zn;
    f32 sectorAngle;
    s32 i;

    // Radius in both directions
    z = 1.0f;
    zn = -z;

    // Backup VAT/VCD
    GXGetVtxDescv(vcd);
    GXGetVtxAttrFmtv(GX_VTXFMT3, vat);

    // Set custom VAT/VCD
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);

    // Calculate vertices
    for (i = 0; i <= sides; i++) {
        sectorAngle = 2.0f * i * M_PI / sides;
        vx[i] = cosf(sectorAngle);
        vy[i] = sinf(sectorAngle);
    }

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT3, (sides + 1) * 2);
    {
        for (i = 0; i <= sides; i++) {
            GXPosition3f32(vx[i], vy[i], zn);
            GXPosition3f32(vx[i], vy[i], 0.0f);
            GXPosition3f32(vx[i], vy[i], z);
            GXPosition3f32(vx[i], vy[i], 0.0f);
        }
    }
    GXEnd();

    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT3, sides + 2);
    {
        GXPosition3f32(0.0f, 0.0f, z);
        GXPosition3f32(0.0f, 0.0f, 1.0f);

        for (i = 0; i <= sides; i++) {

            GXPosition3f32(vx[i], -vy[i], z);
            GXPosition3f32(0.0f, 0.0f, 1.0f);
        }
    }
    GXEnd();

    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT3, sides + 2);
    {
        GXPosition3f32(0.0f, 0.0f, zn);
        GXPosition3f32(0.0f, 0.0f, -1.0f);

        for (i = 0; i <= sides; i++) {
            GXPosition3f32(vx[i], vy[i], zn);
            GXPosition3f32(0.0f, 0.0f, -1.0f);
        }
    }
    GXEnd();

    // Restore old VAT/VCD
    GXSetVtxDescv(vcd);
    GXSetVtxAttrFmtv(GX_VTXFMT3, vat);
}

void GXDrawSphere(u32 stacks, u32 sectors) {
    GXAttrType tex0, tex0_copy;
    f32 radius;
    f32 stackStep, sectorStep;
    f32 stackAngle, stackAngleNext;
    f32 now_xy, next_xy;
    f32 now_z, next_z;
    f32 sectorAngle;
    f32 cosv, sinv;
    int i, j;

    stackStep = M_PI / stacks;
    sectorStep = 2 * M_PI / sectors;
    radius = 1.0f;

    // Check texcoord attributes
    GXGetVtxDesc(GX_VA_TEX0, &tex0);

    // Backup VAT/VCD
    GXGetVtxDescv(vcd);
    GXGetVtxAttrFmtv(GX_VTXFMT3, vat);

    // Set custom VAT/VCD
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);

    // Setup texcoord VAT/VCD if enabled
    if (tex0 != GX_NONE) {
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT3, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    }

    for (i = 0; i < (int)stacks; i++) {
        stackAngle = i * stackStep;
        stackAngleNext = stackAngle + stackStep;

        now_xy = radius * sinf(stackAngle);
        next_xy = radius * sinf(stackAngleNext);
        now_z = radius * cosf(stackAngle);
        next_z = radius * cosf(stackAngleNext);

        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT3, (sectors + 1) * 2);
        {
            tex0_copy = tex0;

            for (j = 0; j <= (int)sectors; j++) {
                sectorAngle = j * sectorStep;
                cosv = cosf(sectorAngle);
                sinv = sinf(sectorAngle);

                // Vertex 2 position
                GXPosition3f32(cosv * next_xy, sinv * next_xy, next_z);
                // Vertex 2 normal
                GXPosition3f32(cosv * next_xy / radius, sinv * next_xy / radius,
                               next_z / radius);

                // Vertex 2 texcoord (S,T)
                if (tex0_copy != GX_NONE) {
                    GXTexCoord2f32((f32)j / sectors, (f32)(i + 1) / stacks);
                }

                // Vertex 1 position
                GXPosition3f32(cosv * now_xy, sinv * now_xy, now_z);
                // Vertex 1 normal
                GXPosition3f32(cosv * now_xy / radius, sinv * now_xy / radius,
                               now_z / radius);

                // Vertex 1 texcoord (S,T)
                if (tex0_copy != GX_NONE) {
                    GXTexCoord2f32((f32)j / sectors, (f32)i / stacks);
                }
            }
        }
        GXEnd();
    }

    // Restore old VAT/VCD
    GXSetVtxDescv(vcd);
    GXSetVtxAttrFmtv(GX_VTXFMT3, vat);
}
