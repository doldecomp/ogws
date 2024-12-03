#ifndef NW4R_G3D_ANMVIS_H
#define NW4R_G3D_ANMVIS_H
#include "types_nw4r.h"
#include "g3d_anmobj.h"
#include "g3d_resanmvis.h"

namespace nw4r
{
    namespace g3d
    {
        void ApplyVisAnmResult(ResMdl, AnmObjVis *);
        void ApplyVisAnmResult(u8 *, ResMdl, AnmObjVis *);

        class AnmObjVis : public AnmObj
        {
        public:
            AnmObjVis(MEMAllocator *, u16 *, int);
            virtual void G3dProc(u32, u32, void *); // at 0xC
            virtual ~AnmObjVis() {} // at 0x10

            virtual void SetFrame(f32) = 0; // at 0x1C
            virtual f32 GetFrame() const = 0; // at 0x20
            virtual void UpdateFrame() = 0; // at 0x24
            virtual void SetUpdateRate(f32) = 0; // at 0x28
            virtual f32 GetUpdateRate() const = 0; // at 0x2C
            virtual bool Bind(ResMdl) = 0; // at 0x30
            virtual void Release(); // at 0x34
            virtual bool GetResult(u32) = 0; // at 0x38
            virtual AnmObjVisRes * Attach(int, AnmObjVisRes *); // at 0x3C
            virtual AnmObjVisRes * Detach(int); // at 0x40

            bool TestDefined(u32 idx) const;
            bool TestExistence(u32 idx) const;
            void DetachAll();

        protected:
            static const int MAX_RESOURCES = 4;

            int mNumBinds; // at 0x10
            u16 *mBinds; // at 0x14

        public:
            NW4R_G3D_RTTI_DECL_DERIVED(AnmObjVis, AnmObj);
        };

        class AnmObjVisNode : public AnmObjVis
        {
        public:
            AnmObjVisNode(MEMAllocator *allocator, u16 *bindBuffer, int numBinds)
                : AnmObjVis(allocator, bindBuffer, numBinds)
            {
                mResources[0] = NULL;
                mResources[1] = NULL;
                mResources[2] = NULL;
                mResources[3] = NULL;
            }

            virtual void G3dProc(u32, u32, void *); // at 0xC
            virtual ~AnmObjVisNode(); // at 0x10

            virtual void SetFrame(f32); // at 0x1C
            virtual f32 GetFrame() const; // at 0x20
            virtual void UpdateFrame(); // at 0x24
            virtual void SetUpdateRate(f32); // at 0x28
            virtual f32 GetUpdateRate() const; // at 0x2C
            virtual bool Bind(ResMdl); // at 0x30
            virtual void Release(); // at 0x34
            virtual bool GetResult(u32) = 0; // at 0x38
            virtual AnmObjVisRes * Attach(int, AnmObjVisRes *); // at 0x3C
            virtual AnmObjVisRes * Detach(int); // at 0x40

        protected:
            AnmObjVisRes *mResources[MAX_RESOURCES]; // at 0x18

        public:
            NW4R_G3D_RTTI_DECL_DERIVED(AnmObjVisNode, AnmObjVis);
        };

        class AnmObjVisOR : public AnmObjVisNode
        {
        public:
            AnmObjVisOR(MEMAllocator *allocator, u16 *bindBuffer, int numBinds)
                : AnmObjVisNode(allocator, bindBuffer, numBinds)
            {
            }

            virtual ~AnmObjVisOR() {} // at 0x10

            virtual bool GetResult(u32); // at 0x38

            static AnmObjVisOR * Construct(MEMAllocator *, u32 *, ResMdl);

        public:
            NW4R_G3D_RTTI_DECL_DERIVED(AnmObjVisOR, AnmObjVisNode);
        };

        class AnmObjVisRes : public AnmObjVis, public FrameCtrl
        {
        public:
            AnmObjVisRes(MEMAllocator *, ResAnmVis, u16 *, int);

            virtual ~AnmObjVisRes() {} // at 0x10

            virtual void SetFrame(f32); // at 0x1C
            virtual f32 GetFrame() const; // at 0x20
            virtual void UpdateFrame(); // at 0x24
            virtual void SetUpdateRate(f32); // at 0x28
            virtual f32 GetUpdateRate() const; // at 0x2C
            virtual bool Bind(ResMdl); // at 0x30
            virtual bool GetResult(u32); // at 0x38

            static AnmObjVisRes * Construct(MEMAllocator *, u32 *, ResAnmVis, ResMdl);

        private:
            ResAnmVis mResAnmVis; // at 0x2C

        public:
            NW4R_G3D_RTTI_DECL_DERIVED(AnmObjVisRes, AnmObjVis);
        };
    }
}

#endif