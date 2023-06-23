#include <OSCache.h>
#include "g3d_resvtx.h"
#include "g3d_cpu.h"

namespace nw4r
{
	namespace g3d
	{
		using namespace detail;
		
		void ResVtxPos::SetArray()
		{
			if (mPos.IsValid()) GXSetArray(GX_VA_POS, GetData(), ref().BYTE_0x1D);
		}
		
		void ResVtxPos::GetArray(const void ** pPtr, u8 * pByte) const
		{
			if (pPtr) *pPtr = GetData();
			
			if (pByte) *pByte = ref().BYTE_0x1D;
		}
		
		UNKTYPE ResVtxPos::CopyTo(void * ptr) const
		{
			if (mPos.IsValid())
			{
				u32 size = ref().SIZE_0x0;
				
				Copy32ByteBlocks(ptr, &ref(), size);
				DCStoreRange(ptr, size);
			}
		}
		
		void ResVtxNrm::SetArray()
		{
			if (mNrm.IsValid()) GXSetArray(GX_VA_NRM, GetData(), ref().BYTE_0x1D);
		}
		
		void ResVtxNrm::GetArray(const void ** pPtr, u8 * pByte) const
		{
			if (pPtr) *pPtr = GetData();
			
			if (pByte) *pByte = ref().BYTE_0x1D;
		}
		
		UNKTYPE ResVtxNrm::CopyTo(void * ptr) const
		{
			if (mNrm.IsValid())
			{
				u32 size = ref().SIZE_0x0;
				
				Copy32ByteBlocks(ptr, &ref(), size);
				DCStoreRange(ptr, size);
			}
		}
		
		void ResVtxClr::SetArray(GXAttr attr)
		{
			if (mClr.IsValid() && (u32)(attr - GX_VA_CLR0) <= (GX_VA_TEX0 - GX_VA_CLR0) - 1) GXSetArray(attr, GetData(), ref().BYTE_0x1C);
		}
		
		void ResVtxClr::GetArray(const void ** pPtr, u8 * pByte) const
		{
			if (pPtr) *pPtr = GetData();
			
			if (pByte) *pByte = ref().BYTE_0x1C;
		}
		
		UNKTYPE ResVtxClr::CopyTo(void * ptr) const
		{
			if (mClr.IsValid())
			{
				u32 size = ref().SIZE_0x0;
				
				Copy32ByteBlocks(ptr, &ref(), size);
				DCStoreRange(ptr, size);
			}
		}
		
		void ResVtxTexCoord::GetArray(const void ** pPtr, u8 * pByte) const
		{
			if (pPtr) *pPtr = GetData();
			
			if (pByte) *pByte = ref().BYTE_0x1D;
		}
		
		UNKTYPE ResVtxPos::DCStore(bool sync)
		{
			void * ptr = &ref();
			u32 size = ref().SIZE_0x0;
			
			if (sync) DCStoreRange(ptr, size);
			else DCStoreRangeNoSync(ptr, size);
		}
		
		UNKTYPE ResVtxNrm::DCStore(bool sync)
		{
			void * ptr = &ref();
			u32 size = ref().SIZE_0x0;
			
			if (sync) DCStoreRange(ptr, size);
			else DCStoreRangeNoSync(ptr, size);
		}
		
		UNKTYPE ResVtxClr::DCStore(bool sync)
		{
			void * ptr = &ref();
			u32 size = ref().SIZE_0x0;
			
			if (sync) DCStoreRange(ptr, size);
			else DCStoreRangeNoSync(ptr, size);
		}
		
		UNKTYPE ResVtxTexCoord::DCStore(bool sync)
		{
			void * ptr = &ref();
			u32 size = ref().SIZE_0x0;
			
			if (sync) DCStoreRange(ptr, size);
			else DCStoreRangeNoSync(ptr, size);
		}
	}
}