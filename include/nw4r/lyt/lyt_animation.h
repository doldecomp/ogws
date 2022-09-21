#ifndef NW4R_LYT_ANIMATION_H
#define NW4R_LYT_ANIMATION_H
#include "types_nw4r.h"
#include "ut_LinkList.h"
#include "lyt_resourceAccessor.h"

namespace nw4r
{
    namespace lyt
    {
        namespace res
        {
            struct AnimationBlock
            {
                
            };
        }

        struct AnimResource
        {
            inline AnimResource() : OFFSET_0x0(0), mResourceBlock(0), OFFSET_0x8(0), OFFSET_0xC(0) {}

            u32 OFFSET_0x0;
            u32 mResourceBlock;
            u16 mFrameSize;
            u16 OFFSET_0xA;
            u32 OFFSET_0xC;
        };

        struct AnimTransform
        {
            inline AnimTransform() : mNode(), mResource(NULL), FLOAT_0x10(0.0f) {}

            u16 GetFrameSize() const;
            bool IsLoopData() const;

            ut::LinkListNode mNode; // at 0x0
            AnimResource *mResource; // at 0xC
            f32 FLOAT_0x10;
        };

        struct AnimTransformBasic : AnimTransform
        {
            AnimTransformBasic();
            virtual ~AnimTransformBasic();
            virtual UNKTYPE SetResource(const res::AnimationBlock *, ResourceAccessor *);
            virtual UNKTYPE Bind(Pane *, bool);
            virtual UNKTYPE Bind(Material *);
            virtual UNKTYPE Animate(u32, Pane *);
            virtual UNKTYPE Animate(u32, Material *);

            u32 INT_0x14;
            u32 INT_0x18;
            u16 INT_0x1C;
        };

        struct AnimationLink
        {
            inline AnimationLink() : mNode()
            {
                Reset();
            }

            inline void Reset()
            {
                Set(NULL, 0, false);
            }

            inline void Set(AnimTransform *pTransform, u16 us, bool b)
            {
                mTransform = pTransform;
                SHORT_0xC = us;
                BOOL_0xE = b;
            }

            ut::LinkListNode mNode; // at 0x0
            AnimTransform *mTransform; // at 0x8
            u16 SHORT_0xC;
            bool BOOL_0xE;
        };
    }
}

#endif