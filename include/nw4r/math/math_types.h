#ifndef NW4R_MATH_TYPES_H
#define NW4R_MATH_TYPES_H
#include <RevoSDK/mtx/mtx.h>

namespace nw4r
{
	// TODO: Implement objects accurately
	namespace math
	{
		struct _VEC2
		{
			float x, y;
		};
		
		struct VEC2
		{
			_VEC2 mCoords;
		};
		
		struct _VEC3
		{
			float x, y, z;
		};
		
		struct VEC3
		{
			_VEC3 mCoords;
			
			inline VEC3() {}
			
			inline VEC3(float x, float y, float z)
			{
				mCoords.x = x;
				mCoords.y = y;
				mCoords.z = z;
			}
		};
		
		struct _MTX34
		{
			float tbl[3][4];
		};
		
		struct MTX34
		{
			_MTX34 mEntries;
		};
		
		inline void MTX34Identity(MTX34 * pMtx)
		{
			PSMTXIdentity(pMtx);
		}
		
		inline void MTX34Copy(MTX34 * dest, const MTX34 * src)
		{
			PSMTXCopy(src, dest);
		}
	}
}

#endif