#ifndef EGG_GFX_LIGHT_MANAGER_H
#define EGG_GFX_LIGHT_MANAGER_H
#include "types_egg.h"
#include "eggIBinary.h"

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
        void CalcView(const Matrix34f&, u8, nw4r::g3d::ScnRoot *);

        void DoneDraw();

        LightTextureManager * GetLightTextureManager() const
        {
            return m_pLightTextureManager;
        }

    private:
        char UNK_0x4[0x20 - 0x4];
        LightTextureManager *m_pLightTextureManager; // at 0x20
    };
}

#endif