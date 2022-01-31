#ifndef NW4R_MATH_GEOMETRY_H
#define NW4R_MATH_GEOMETRY_H

namespace nw4r
{
    namespace math
    {
        struct AABB
        {
            AABB() {}

            void Set(const AABB *, const MTX34 *);

            VEC3 VEC3_0x0;
            VEC3 VEC3_0xC;
        };

        struct FRUSTUM
        {
            
        };
    }
}

#endif