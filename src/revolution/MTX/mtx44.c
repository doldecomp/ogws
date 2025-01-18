#include <math.h>
#include <revolution/MTX.h>

void C_MTXFrustum(Mtx44 mtx, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f) {
    f32 invrange;

    invrange = 1.0f / (r - l);
    mtx[0][0] = 2.0f * n * invrange;
    mtx[0][1] = 0.0f;
    mtx[0][2] = invrange * (r + l);
    mtx[0][3] = 0.0f;

    invrange = 1.0f / (t - b);
    mtx[1][0] = 0.0f;
    mtx[1][1] = 2.0f * n * invrange;
    mtx[1][2] = invrange * (t + b);
    mtx[1][3] = 0.0f;

    invrange = 1.0f / (f - n);
    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = -n * invrange;
    mtx[2][3] = invrange * -(f * n);

    mtx[3][0] = 0.0f;
    mtx[3][1] = 0.0f;
    mtx[3][2] = -1.0f;
    mtx[3][3] = 0.0f;
}

DECOMP_FORCELITERAL(mtx44_c, 0.5f);

void C_MTXPerspective(Mtx44 mtx, f32 fovy, f32 aspect, f32 n, f32 f) {
    f32 rad, cot;
    f32 invrange;

    rad = M_PI / 180.0f * (0.5f * fovy);
    cot = 1.0f / tanf(rad);

    mtx[0][0] = cot / aspect;
    mtx[0][1] = 0.0f;
    mtx[0][2] = 0.0f;
    mtx[0][3] = 0.0f;

    mtx[1][0] = 0.0f;
    mtx[1][1] = cot;
    mtx[1][2] = 0.0f;
    mtx[1][3] = 0.0f;

    invrange = 1.0f / (f - n);
    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = -n * invrange;
    mtx[2][3] = invrange * -(f * n);

    mtx[3][0] = 0.0f;
    mtx[3][1] = 0.0f;
    mtx[3][2] = -1.0f;
    mtx[3][3] = 0.0f;
}

void C_MTXOrtho(Mtx44 mtx, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f) {
    f32 invrange;

    invrange = 1.0f / (r - l);
    mtx[0][0] = 2.0f * invrange;
    mtx[0][1] = 0.0f;
    mtx[0][2] = 0.0f;
    mtx[0][3] = invrange * -(r + l);

    invrange = 1.0f / (t - b);
    mtx[1][0] = 0.0f;
    mtx[1][1] = 2.0f * invrange;
    mtx[1][2] = 0.0f;
    mtx[1][3] = invrange * -(t + b);

    invrange = 1.0f / (f - n);
    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = -1.0f * invrange;
    mtx[2][3] = -f * invrange;

    mtx[3][0] = 0.0f;
    mtx[3][1] = 0.0f;
    mtx[3][2] = 0.0f;
    mtx[3][3] = 1.0f;
}
