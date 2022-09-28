#ifndef EGG_GFX_SCREEN_H
#define EGG_GFX_SCREEN_H
#include "types_egg.h"
#include "eggFrustum.h"

namespace EGG
{
    class Screen : public Frustum
    {
    public:
        enum TVMode
        {
            TV_MODE_4_3,
            TV_MODE_16_9,
            TV_MODE_MAX
        };

        typedef void (*ChangeTVModeFunc)(void*);

        struct TVModeRatio
        {
            // Required for static init
            TVModeRatio() {}
            f32 w_ratio;
            f32 h_ratio;
        };

        struct DataEfb
        {
            // Required for struct copy
            struct Viewport
            {
                f32 x1; // at 0x0
                f32 y1; // at 0x4
                f32 x2; // at 0x8
                f32 y2; // at 0xC
                f32 z1; // at 0x10
                f32 z2; // at 0x14
            } vp;

            s32 sc_ox; // at 0x18
            s32 sc_oy; // at 0x1C
        };

    public:
        static void Initialize(const u16* , const u16* , Screen* );
        static void CalcRatio();
        static void SetTVMode(TVMode);
        static void SetTVModeDefault();

        static u16 GetSizeXMax() { return sTVModeWidths[sTVMode]; } 
        static u16 GetSizeYMax() { return sTVModeHeights[sTVMode]; } 

        Screen();
        Screen(f32, f32, f32, f32, const Screen*, CanvasMode);
        Screen(const Screen&);

        virtual ~Screen() {} // at 0x8
        virtual void SetProjectionGX() const; // at 0xC
        virtual void CopyToG3D(nw4r::g3d::Camera) const; // at 0x10

        const Screen* GetParent() const { return mParent; }
        void SetParent(const Screen* parent)
        {
            SetDirty(true);

            if (spRoot == this)
                mParent = NULL;
            else
                mParent = (parent != NULL) ? parent : spRoot;
        }

        void CopyFromAnother(const Screen& other);
        void GetPosSizeInEfb() const;
        const DataEfb& GetDataEfb() const;
        bool IsChangeEfb() const;
        void CalcMatrixForDrawQuad(nw4r::math::MTX34* , f32, f32, f32, f32) const;
        void FillBufferGX(u32, GXColor, u32) const;
        void GetGlobalPos(f32*, f32*) const;

    private:
        void NullSub_0();

        void SetViewGX() const;
        void SetViewG3D(nw4r::g3d::Camera) const;

    private:
        const Screen* mParent; // at 0x3C
        nw4r::math::VEC2 mPosition; // at 0x40
        mutable DataEfb mDataEfb; // at 0x48

        static TVMode sTVMode;
        static u16 sTVModeWidths[TV_MODE_MAX];
        static u16 sTVModeHeights[TV_MODE_MAX];

        static Screen* spRoot;

        static ChangeTVModeFunc sChangeTVModeFunc;
        static void* spChangeTVModeFuncInfo;
        static TVModeRatio sTVModeRatios[Screen::TV_MODE_MAX];

        static nw4r::math::VEC2 sCanvasScale;
        static nw4r::math::VEC2 sCanvasOffset;
    };
}

#endif