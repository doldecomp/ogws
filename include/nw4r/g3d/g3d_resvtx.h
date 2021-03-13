#ifndef NW4R_G3D_RESVTX_H
#define NW4R_G3D_RESVTX_H
#include "types_nw4r.h"
#include "g3d_rescommon.h"

namespace nw4r
{
	namespace g3d
	{
		struct ResVtxPosData
		{
			
		};
		
		struct ResVtxNrmData
		{
			
		};
		
		struct ResVtxClrData
		{
			
		};
		
		struct ResVtxTexCoordData
		{
			
		};
		
		struct ResVtxPos
		{
			ResCommon<ResVtxPosData> mPos;
			
			inline ResVtxPos(void * vptr) : mPos(vptr) {}
			
			inline ResVtxPosData & ref() const
			{
				return mPos.ref();
			}
			
			UNKTYPE GetArray(const void **, u8 *) const;
		};
		
		struct ResVtxNrm
		{
			ResCommon<ResVtxNrmData> mNrm;
			
			inline ResVtxNrm(void * vptr) : mNrm(vptr) {}
			
			inline ResVtxNrmData & ref() const
			{
				return mNrm.ref();
			}
			
			UNKTYPE GetArray(const void **, u8 *) const;
		};
		
		struct ResVtxClr
		{
			ResCommon<ResVtxClrData> mClr;
			
			inline ResVtxClr(void * vptr) : mClr(vptr) {}
			
			inline ResVtxClrData & ref() const
			{
				return mClr.ref();
			}
			
			UNKTYPE GetArray(const void **, u8 *) const;
		};
		
		struct ResVtxTexCoord
		{
			ResCommon<ResVtxTexCoordData> mTexCoord;
			
			inline ResVtxTexCoord(void * vptr) : mTexCoord(vptr) {}
			
			inline ResVtxTexCoordData & ref() const
			{
				return mTexCoord.ref();
			}
			
			UNKTYPE GetArray(const void **, u8 *) const;
		};
	}
}

#endif