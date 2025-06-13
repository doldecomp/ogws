#ifndef EGG_CORE_PROCESS_METER_H
#define EGG_CORE_PROCESS_METER_H
#include <egg/types_egg.h>

#include <egg/core/eggBitFlag.h>
#include <egg/core/eggPerformanceView.h>
#include <egg/core/eggStopWatch.h>
#include <egg/core/eggSystem.h>
#include <egg/core/eggThread.h>

#include <egg/prim.h>

#include <nw4r/ut.h>

namespace EGG {

/******************************************************************************
 *
 * ProcessMeter
 *
 ******************************************************************************/
class ProcessMeter : public Thread, public PerformanceView {
public:
    // Forward declarations
    struct CpuGpMonitor;

    /***************************************************************************
     * DrawSync
     ***************************************************************************/
    struct DrawSync {
        void* pWritePtr;          // at 0x0
        u16 token;                // at 0x4
        DrawSync* pNext;          // at 0x8
        CpuGpMonitor* pGpMonitor; // at 0xC
    };

    /***************************************************************************
     * ProcessBar
     ***************************************************************************/
    class ProcessBar {
    public:
        f32 mPosX;  // at 0x0
        f32 mWidth; // at 0x4

        Stopwatch mStopWatch;   // at 0x8
        nw4r::ut::Color mColor; // at 0x10

        f32 mPosY;   // at 0x14
        f32 mHeight; // at 0x18

    public:
        static u16 getLinkOffset() {
            return offsetof(ProcessBar, mLink);
        }

        ProcessBar(nw4r::ut::Color color, f32 posY, f32 height);

        bool update(s32 measureTick);
        bool update(f32 measureTime);

        void draw();
        void draw(f32 posY, f32 height);

        void show() {
            mFlags.resetBit(BIT_HIDDEN);
        }
        void hide() {
            mFlags.setBit(BIT_HIDDEN);
        }

        bool isVisible() {
            return mFlags.offBit(BIT_HIDDEN);
        }

    private:
        enum {
            BIT_HIDDEN,
        };

    private:
        TBitFlag<u8> mFlags;  // at 0x1C
        nw4r::ut::Link mLink; // at 0x20
    };

    /***************************************************************************
     * CpuMonitor
     ***************************************************************************/
    class CpuMonitor {
        friend class ProcessMeter;

    public:
        CpuMonitor(nw4r::ut::Color color, f32 posY);

        virtual void show(); // at 0x8
        virtual void hide(); // at 0xC

        virtual void measureBegin(); // at 0x10
        virtual void measureEnd();   // at 0x14

    protected:
        ProcessBar mCpuProcessBar; // at 0x4
    };

    /***************************************************************************
     * CpuGpMonitor
     ***************************************************************************/
    class CpuGpMonitor : public CpuMonitor {
        friend class ProcessMeter;

    public:
        enum EDrawSyncState { DRAWSYNC_NONE, DRAWSYNC_BEGIN, DRAWSYNC_END };

    public:
        CpuGpMonitor(nw4r::ut::Color cpuColor, nw4r::ut::Color gpColor,
                     f32 cpuPosY, f32 gpPosY);

        virtual void show(); // at 0x8
        virtual void hide(); // at 0xC

        virtual void measureBegin(); // at 0x10
        virtual void measureEnd();   // at 0x14

    protected:
        void doToken(u32 tick);

    protected:
        ProcessBar mGpProcessBar;    // at 0x2C
        u16 mDrawSyncState;          // at 0x54
        ProcessMeter* mProcessMeter; // at 0x58
        DrawSync mBeginDrawSync;     // at 0x5C
        DrawSync mEndDrawSync;       // at 0x68
    };

public:
    explicit ProcessMeter(bool showGp);
    virtual ~ProcessMeter() {} // at 0x8

    virtual void* run(void); // at 0xC

    virtual void setVisible(bool visible); // at 0x44
    virtual bool isVisible();              // at 0x48

    virtual void callbackDrawSync(u16 token); // at 0x4C

    virtual void measureBeginFrame(); // at 0x50
    virtual void measureEndFrame();   // at 0x54

    virtual void measureBeginRender(); // at 0x58
    virtual void measureEndRender();   // at 0x5C

    virtual void draw(); // at 0x60

private:
    enum {
        BIT_VISIBLE,
    };

    static const u32 THREAD_STACK_SIZE = OS_MEM_KB_TO_B(4);
    static const u32 THREAD_MSG_CAPACITY = 4;

    static const u32 GRADUATION_COLOR = 0xCCCCCCFF;
    static const u32 BG_COLOR = 0x000032C8;

    static const u32 CPU_BAR_COLOR = 0xFF5050FF;
    static const u32 CPU_GP_BAR_COLOR = 0x50FF50FF;
    static const u32 GP_BAR_COLOR = 0x5050FFFF;

    static const u32 DRAW_TOKEN_MIN = 0xD000;
    static const u32 DRAW_TOKEN_MAX = 0xDFFF;

private:
    static void callbackDrawSyncStatic(u16 token) {
        BaseSystem::getPerfView()->callbackDrawSync(token);
    }

    void setDrawSync(DrawSync* pDrawSync);

    void append(CpuMonitor* pMonitor);
    void append(CpuGpMonitor* pGpMonitor);

    void draw(f32 fbWidth, f32 efbHeight, u32 tickPerFrame);
    void drawSetting(f32 fbWidth, f32 efbHeight);

private:
    nw4r::ut::Color mGraduationColor;      // at 0x48
    f32 mPosX;                             // at 0x4C
    f32 mPosY;                             // at 0x50
    f32 mWidth;                            // at 0x54
    f32 mHeight;                           // at 0x58
    TNw4rList<ProcessBar> mProcessBarList; // at 0x5C
    DrawSync* mHeadDrawSync;               // at 0x68
    DrawSync* mTailDrawSync;               // at 0x6C
    ProcessBar mBgProcessBar;              // at 0x70
    CpuMonitor mCpuMonitor;                // at 0x98
    CpuGpMonitor mCpuGpMonitor;            // at 0xC4
    f32 mBgBarHeight;                      // at 0x140
    char UNK_0x144[0x4];
    u16 mNextToken;      // at 0x148
    TBitFlag<u8> mFlags; // at 0x14A
};

} // namespace EGG

#endif
