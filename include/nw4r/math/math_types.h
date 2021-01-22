#ifndef NW4R_MATH_TYPES_H
#define NW4R_MATH_TYPES_H
#include "types_nw4r.h"
#include <RevoSDK/math/mtx.h>
#include <RevoSDK/math/vec.h>
#include <RevoSDK/math/mtxvec.h>

#define NW4R_PI_F32 3.1415927f

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
		
		inline void VEC3Add(register VEC3 * destVec, register const VEC3 * srcVec1, register const VEC3 * srcVec2)
		{
			asm
			{
				psq_l f2, 0x0(srcVec1), 0, 0
				psq_l f2, 0x0(srcVec2), 0, 0
				ps_add f0, f2, f1
				psq_l f2, 0x8(srcVec1), 1, 0
				psq_l f2, 0x8(srcVec2), 1, 0
				psq_st f0, 0x0(destVec), 0, 0
				ps_add f0, f2, f1
				psq_st f0, 0x8(destVec), 1, 0
			}
		}
		
		inline void VEC3Sub(register VEC3 * destVec, register const VEC3 * srcVec1, register const VEC3 * srcVec2)
		{
			asm
			{
				psq_l f2, 0x0(srcVec1), 0, 0
				psq_l f2, 0x0(srcVec2), 0, 0
				ps_sub f0, f2, f1
				psq_l f2, 0x8(srcVec1), 1, 0
				psq_l f2, 0x8(srcVec2), 1, 0
				psq_st f0, 0x0(destVec), 0, 0
				ps_sub f0, f2, f1
				psq_st f0, 0x8(destVec), 1, 0
			}
		}
		
		inline void VEC3Scale(register VEC3 * outVec, register const VEC3 * inVec, register float scalar)
		{
			asm
			{
				psq_l f2, 0x0(inVec), 0, 0
				ps_muls0 f1, f2, scalar
				psq_l f2, 0x8(inVec), 0, 1
				psq_st f1, 0x0(outVec), 0, 0
				ps_muls0 f1, f2, scalar
				psq_st f1, 0x8(outVec), 1, 0
			}
		}
		
		struct VEC3
		{
			_VEC3 mCoords;
			
			inline VEC3() {}
			
			inline VEC3(const VEC3 & other) : mCoords(other.mCoords) {}
			
			inline VEC3 & operator=(const VEC3 & other)
			{
				mCoords = other.mCoords;
				return *this;
			}
			
			inline VEC3(float x, float y, float z)
			{
				mCoords.x = x;
				mCoords.y = y;
				mCoords.z = z;
			}
			
			inline VEC3 operator-(register const VEC3 & other) const
			{
				VEC3 ret;
				
				VEC3Sub(&ret, this, &other);
				
				return ret;
			}
			
			inline operator Vec *()
			{
				return reinterpret_cast<Vec *>(this);
			}
			
			inline operator const Vec *() const
			{
				return reinterpret_cast<const Vec *>(this);
			}
		};
		
		struct _MTX34
		{
			float tbl[3][4];
		};
		
		struct MTX34
		{
			_MTX34 mEntries;
			
			typedef float (* MtxRef)[4];
			typedef const float (* MtxRefConst)[4];
			
			inline operator MtxRef()
			{
				return mEntries.tbl;
			}
			
			inline operator MtxRefConst() const
			{
				return mEntries.tbl;
			}
		};
		
		inline void VEC3Normalize(VEC3 * out, const VEC3 * in)
		{
			PSVECNormalize(*in, *out);
		}
		
		inline float VEC3DistSq(const VEC3 * point1, const VEC3 * point2)
		{
			return PSVECSquareDistance(*point1, *point2);
		}
		
		inline void VEC3Transform(VEC3 * outVec, const MTX34 * mtx, const VEC3 * inVec)
		{
			PSMTXMultVec(*mtx, *inVec, *outVec);
		}
		
		inline void MTX34Inv(MTX34 * out, const MTX34 * in)
		{
			PSMTXInverse(*in, *out);
		}
		
		inline void MTX34Mult(MTX34 * outMtx, const MTX34 * inMtx1, const MTX34 * inMtx2)
		{
			PSMTXConcat(*inMtx1, *inMtx2, *outMtx);
		}
		
		inline void MTX34Identity(MTX34 * mtx)
		{
			PSMTXIdentity(*mtx);
		}
		
		inline void MTX34Copy(MTX34 * out, const MTX34 * in)
		{
			PSMTXCopy(*in, *out);
		}
		
		UNKTYPE GetDirMtxY(MTX34 *, const VEC3 &);
		
		UNKTYPE MTX34RotXYZFIdx(MTX34 *, float, float, float);
		
		UNKTYPE MTX34Scale(MTX34 *, const MTX34 *, const VEC3 *);
		
		inline void MTX34Scale(MTX34 * outMtx, const VEC3 * vec, const MTX34 * inMtx)
		{
			PSMTXScaleApply(*inMtx, *outMtx, vec->mCoords.x, vec->mCoords.y, vec->mCoords.z);
		}
		
		UNKTYPE MtxGetRotation(const MTX34 &, VEC3 *);
		
		UNKTYPE MTX34Trans(MTX34 *, const MTX34 *, const VEC3 *);
		
		float FrSqrt(float);
		
		inline float FSqrt(float f)
		{
			return f * FrSqrt(f);
		}
		
		inline float VEC3Len(const VEC3 * in)
		{
			return PSVECMag(*in);
		}
	}
}

#endif