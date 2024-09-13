#ifndef NW4R_G3D_RESVTX_H
#define NW4R_G3D_RESVTX_H
#include <GXAttr.h>
#include "g3d_rescommon.h"

namespace nw4r
{
	namespace g3d
	{
		struct ResVtxPosData
		{
			u32 SIZE_0x0;
			char UNK_0x4[0x4];
			u32 mDataOffset; // at 0x8
			char UNK_0xC[0x11];
			u8 BYTE_0x1D;
		};
		
		struct ResVtxNrmData
		{
			u32 SIZE_0x0;
			char UNK_0x4[0x4];
			u32 mDataOffset; // at 0x8
			char UNK_0xC[0x11];
			u8 BYTE_0x1D;
		};
		
		struct ResVtxClrData
		{
			u32 SIZE_0x0;
			char UNK_0x4[0x4];
			u32 mDataOffset; // at 0x8
			char UNK_0xC[0x10];
			u8 BYTE_0x1C;
		};
		
		struct ResVtxTexCoordData
		{
			u32 SIZE_0x0;
			char UNK_0x4[0x4];
			u32 mDataOffset; // at 0x8
			char UNK_0xC[0x11];
			u8 BYTE_0x1D;
		};
		
		class ResVtxPos : public ResCommon<ResVtxPosData>
		{
		public:
			inline explicit ResVtxPos(void * pData) : ResCommon(pData) {}
			
			inline const void * GetData() const
			{
				return ofs_to_ptr<void>(ref().mDataOffset);
			}
			
			inline UNKTYPE Init()
			{
				DCStore(false);
			}

			void SetArray();
			void GetArray(const void **, u8 *) const;
			UNKTYPE CopyTo(void *) const;
			
			UNKTYPE DCStore(bool);
		};
		
		class ResVtxNrm : public ResCommon<ResVtxNrmData>
		{
		public:
			inline explicit ResVtxNrm(void * pData) : ResCommon(pData) {}
			
			inline const void * GetData() const
			{
				return ofs_to_ptr<void>(ref().mDataOffset);
			}
			
			inline UNKTYPE Init()
			{
				DCStore(false);
			}
	
			void SetArray();
			void GetArray(const void **, u8 *) const;
			UNKTYPE CopyTo(void *) const;
			
			UNKTYPE DCStore(bool);
		};
		
		class ResVtxClr : public ResCommon<ResVtxClrData>
		{
		public:
			inline explicit ResVtxClr(void * pData) : ResCommon(pData) {}
	
			inline const void * GetData() const
			{
				return ofs_to_ptr<void>(ref().mDataOffset);
			}

			inline UNKTYPE Init()
			{
				DCStore(false);
			}

			void SetArray(GXAttr);
			void GetArray(const void **, u8 *) const;
			UNKTYPE CopyTo(void *) const;
			
			UNKTYPE DCStore(bool);
		};
		
		class ResVtxTexCoord : public ResCommon<ResVtxTexCoordData>
		{
		public:
			inline explicit ResVtxTexCoord(void * pData) : ResCommon(pData) {}
			
			inline const void * GetData() const
			{
				return ofs_to_ptr<void>(ref().mDataOffset);
			}
			
			inline UNKTYPE Init()
			{
				DCStore(false);
			}

			void GetArray(const void **, u8 *) const;
			
			UNKTYPE DCStore(bool);
		};
	}
}

#endif