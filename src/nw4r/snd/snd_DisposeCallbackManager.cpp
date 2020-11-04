#include "snd_DisposeCallbackManager.h"
#include "ut_interrupt.h"

namespace nw4r
{
	namespace snd
	{
		using namespace ut;
		
		namespace detail
		{
			template struct ut::LinkList<DisposeCallback, 0x0>;
			
			DisposeCallbackManager * DisposeCallbackManager::GetInstance()
			{
				AutoInterruptLock lock;
				
				static DisposeCallbackManager instance;
				
				return &instance;
			}
			
			UNKTYPE DisposeCallbackManager::RegisterDisposeCallback(DisposeCallback * pCallback)
			{
				mList.PushBack(pCallback);
			}
			
			UNKTYPE DisposeCallbackManager::UnregisterDisposeCallback(DisposeCallback * pCallback)
			{
				mList.Erase(pCallback);
			}
			
			UNKTYPE DisposeCallbackManager::Dispose(void * r4_31, u32 r_5, void * r_6)
			{
				u8 * r31 = static_cast<u8 *>(r4_31);
				u8 * r30 = r31 + r_5;
				
				LinkList<DisposeCallback, 0x0>::Iterator iter = GetInstance()->mList.GetBeginIter();
				
				while (iter != GetInstance()->mList.GetEndIter())
				{
					iter++->InvalidateData(r31, r30);
				}
			}
			
			UNKTYPE DisposeCallbackManager::DisposeWave(void * r4_31, u32 r_5, void * r_6)
			{
				u8 * r31 = static_cast<u8 *>(r4_31);
				u8 * r30 = r31 + r_5;
				
				LinkList<DisposeCallback, 0x0>::Iterator iter = GetInstance()->mList.GetBeginIter();
				
				while (iter != GetInstance()->mList.GetEndIter())
				{
					iter++->InvalidateWaveData(r31, r30);
				}
			}
		}
	}
}