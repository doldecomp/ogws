#ifndef NW4R_MATH_GEOMETRY_H
#define NW4R_MATH_GEOMETRY_H

namespace nw4r
{
    namespace math
    {
        struct AABB
        {
            AABB() {}
            
            inline AABB& operator=(const AABB& other)
            {
				struct VEC3i { int coords[3]; };
				*(VEC3i *)&this->VEC3_0x0 = *(VEC3i *)&other.VEC3_0x0;
				*(VEC3i *)&this->VEC3_0xC = *(VEC3i *)&other.VEC3_0xC;
				return *this;
            }

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