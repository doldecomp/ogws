#ifndef NW4R_MATH_TYPES_H
#define NW4R_MATH_TYPES_H
#include "types_nw4r.h"
#include <RevoSDK/math/mtx.h>
#include <RevoSDK/math/vec.h>
#include <RevoSDK/math/mtxvec.h>

#define NW4R_PI_F32 3.1415927f
#define NW4R_DEG_TO_FIDX (256.0f / 360.0f)
#define	NW4R_FIDX_TO_DEG (2.0f * NW4R_PI_F32 / 256.0f)
#define NW4R_MATH_BLOG_TO_LN 1.442695f
#define NW4R_LN_2 0.6931472f

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

			inline VEC2() {}

			inline VEC2(f32 x, f32 y)
			{
				mCoords.x = x;
				mCoords.y = y;
			}

			inline VEC2 & operator=(const VEC2 & other)
			{
				mCoords = other.mCoords;
				return *this;
			}
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
		
		inline float VEC3Dot(register const VEC3 * vec1, register const VEC3 * vec2)
		{
			register f32 a, b, d, c, e;
			asm
			{
				psq_l a, 0x4(vec1), 0, 0
				psq_l b, 0x4(vec2), 0, 0
				ps_mul a, a, b
				psq_l c, 0(vec1), 1, 0
				psq_l d, 0(vec2), 1, 0
				ps_madd b, c, d, a
				ps_sum0 e, b, a, a
			}
			return e;
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
			
			inline bool operator!=(const VEC3 & other) const
			{
				return mCoords.x != other.mCoords.x || mCoords.y != other.mCoords.y || mCoords.z != other.mCoords.z;
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
		
		struct _MTX33
		{
			float tbl[3][3];
		};

		struct MTX33
		{
			_MTX33 mEntries;

			typedef float (* MtxRef)[3];
			typedef const float (* MtxRefConst)[3];
			
			inline operator MtxRef()
			{
				return mEntries.tbl;
			}
			
			inline operator MtxRefConst() const
			{
				return mEntries.tbl;
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

		struct _MTX44
		{
			float tbl[4][4];
		};

		struct MTX44
		{
			_MTX44 mEntries;

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

		inline void VEC3Cross(VEC3 * out, const VEC3 * in1, const VEC3 * in2)
		{
			PSVECCrossProduct(*in1, *in2, *out);
		}

		void VEC3Maximize(VEC3 *, const VEC3 *, const VEC3 *);
		void VEC3Minimize(VEC3 *, const VEC3 *, const VEC3 *);

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
		
		void MTX33Identity(register MTX33 *);

		int MTX34InvTranspose(register MTX33 *, register const MTX34 *);

		void MTX34ToMTX33(register MTX33 *, register const MTX34 *);

		void MTX34Zero(register MTX34 *);

		inline void MTX34Inv(MTX34 * out, const MTX34 * in)
		{
			PSMTXInverse(*in, *out);
		}
		
		inline void MTX34Mult(MTX34 * outMtx, const MTX34 * inMtx1, const MTX34 * inMtx2)
		{
			PSMTXConcat(*inMtx1, *inMtx2, *outMtx);
		}

		void MTX34Scale(register MTX34 *, register const MTX34 *, register const VEC3 *);

		void MTX34Trans(register MTX34 *, register const MTX34 *, register const VEC3 *);

		MTX34 * MTX34RotAxisFIdx(MTX34 *, const VEC3 *, f32 );

		MTX34 * MTX34RotXYZFIdx(MTX34 *, f32, f32, f32);

		inline void MTX34Identity(MTX34 * mtx)
		{
			PSMTXIdentity(*mtx);
		}
		
		inline void MTX34Copy(MTX34 * out, const MTX34 * in)
		{
			PSMTXCopy(*in, *out);
		}
		
		VEC3 * VEC3TransformNormal(VEC3 *, const MTX34 *, const VEC3 *);

		void MTX44Identity(register MTX44 *);

		void MTX44Copy(register MTX44 *, register const MTX44 *);

		UNKTYPE GetDirMtxY(MTX34 *, const VEC3 &);
		
		MTX34 * MTX34RotXYZFIdx(MTX34 *, float, float, float);
		
		inline void MTX34Scale(MTX34 * outMtx, const VEC3 * vec, const MTX34 * inMtx)
		{
			PSMTXScaleApply(*inMtx, *outMtx, vec->mCoords.x, vec->mCoords.y, vec->mCoords.z);
		}
		
		UNKTYPE MtxGetRotation(const MTX34 &, VEC3 *);
		
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