#include "ef_handle.h"

namespace nw4r
{
	namespace ef
	{
		HandleBase::HandleBase() : PTR_0x0(NULL), mPtr(NULL) {}
		
		HandleBase & HandleBase::operator=(const HandleBase & other)
		{
			PTR_0x0 = other.PTR_0x0;
			mPtr = other.mPtr;
			return *this;
		}
		
		HandleBase & HandleBase::operator=(LinkedObject * ptr)
		{
			if (!ptr)
			{
				PTR_0x0 = NULL;
				mPtr = NULL;
			}
			else
			{
				PTR_0x0 = ptr->PTR_0x8;
				mPtr = ptr;
			}
			return *this;
		}
		
		bool HandleBase::IsValid() const
		{
			return !mPtr ? false : PTR_0x0 == mPtr->PTR_0x8;
		}
		
		LinkedObject * HandleBase::GetPtr() const
		{
			return IsValid() ? mPtr : NULL;
		}
	}
}