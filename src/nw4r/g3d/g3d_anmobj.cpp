#include "g3d_anmobj.h"
#include "math_equation.h"
#include <STL/math.h>

namespace nw4r
{
    namespace g3d
    {
        f32 FrameCtrl::smBaseUpdateRate = 1.0f;

        f32 PlayPolicy_Onetime(f32 f1, f32 f2, f32 f3)
        {
            return f3;
        }

        f32 PlayPolicy_Loop(f32 f1, f32 f2, f32 f3)
        {
            f32 diff = f2 - f1;

            if (f3 >= 0.0f)
            {
                return fmod(f3, diff);
            }
            else
            {
                f32 mod = fmod(f3 + diff, diff);
                return math::FSelect(mod, 0.0f, diff) + mod;
            }
        }

        AnmObj::~AnmObj()
        {

        }

        void AnmObj::SetAnmFlag(AnmFlag flag, bool value)
        {
            if (value)
            {
                this->mFlags |= flag;
            }
            else
            {
                this->mFlags &= ~flag;
            }
        }

        bool AnmObj::TestAnmFlag(AnmFlag flag) const
        {
            return this->mFlags & flag;
        }

        bool AnmObj::IsDerivedFrom(const TypeObj& rhs) const
        {
            // Check base class too
            return (rhs == GetTypeObjStatic()) ? true : G3dObj::IsDerivedFrom(rhs);
        }

        const G3dObj::TypeObj AnmObj::GetTypeObj() const
        {
            return TypeObj(TYPE_NAME);
        }

        const G3dObj::TypeObj AnmObj::GetTypeObjStatic()
        {
            return TypeObj(TYPE_NAME);
        }

        const char * AnmObj::GetTypeName() const
        {
            return GetTypeObj().GetTypeName();
        }

        NW4R_G3D_TYPE_OBJ_DEF(AnmObj);
    }
}