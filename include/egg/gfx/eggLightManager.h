#ifndef EGG_GFX_LIGHT_MANAGER_H
#define EGG_GFX_LIGHT_MANAGER_H
#include "types_egg.h"
#include "eggIBinary.h"
#include "types_nw4r.h"

namespace EGG
{
    class LightManager : IBinary<LightManager>
    {
    public:
        struct Bin : IBinary::Bin
        {
        };
    
    public:
        LightManager(u32, u32, u8);
        virtual void SetBinaryInner(const Bin&); // at 0x8
        virtual void GetBinaryInner(Bin *) const; // at 0xC
        virtual const char * GetBinaryType() const; // at 0x10
        virtual u32 GetBinarySize() const; // at 0x14
        virtual u8 GetVersion() const = 0; // at 0x18
        virtual ~LightManager(); // at 0x1C

        void Reset();
        void Calc(nw4r::g3d::ScnRoot *);
        void CalcView(const nw4r::math::MTX34&, u8, nw4r::g3d::ScnRoot *);

        void DoneDraw();

        LightObj * GetLightObj(u16 index) const
        {
            #line 157
            EGG_ASSERT(index < GetNum());
            return m_ppLightSet[index];
        }

        u16 GetNum() const { return m_numLight; }
        u8 GetCurrentView() const { return m_currentView; }
        LightTextureManager * GetLightTextureManager() const { return m_pLightTextureManager; }

    private:
        u16 m_numLight; // at 0x4
        char UNK_0x8[0xC - 0x8];
        LightObj **m_ppLightSet; // at 0xC
        char UNK_0X10[0x18 - 0x10];
        u8 m_viewNum; // at 0x18
        u8 m_currentView; // at 0x19
        char UNK_0x1A[0x20 - 0x1A];
        LightTextureManager *m_pLightTextureManager; // at 0x20
    };
}

#endif