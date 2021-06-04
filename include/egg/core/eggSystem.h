#ifndef EGG_CORE_SYSTEM_H
#define EGG_CORE_SYSTEM_H
#include "eggHeap.h"

namespace EGG
{
	struct ConfigurationData
	{
		virtual Video * getVideo() = 0; // at 0x8
		virtual UNKTYPE VIRT_0xC(UNKTYPE) = 0; // at 0xc
		virtual Display * getDisplay() = 0; // at 0x10
		virtual XfbManager * getXfbMgr() = 0; // at 0x14
		
		char UNK_0x4[0x14];
		Heap * mRootHeapMem1; // at 0x18
		Heap * mRootHeapMem2; // at 0x1c
		Heap * mRootHeapDebug; // at 0x20
	};
	
	struct BaseSystem
	{
		static ConfigurationData * mConfigData;
		
		static inline Heap * getRootHeapMem1()
		{
			return mConfigData->mRootHeapMem1;
		}
		
		static inline Heap * getRootHeapMem2()
		{
			return mConfigData->mRootHeapMem2;
		}
		
		static inline Heap * getRootHeapDebug()
		{
			return mConfigData->mRootHeapDebug;
		}
		
		static inline Video * getVideo()
		{
			return mConfigData->getVideo();
		}
		
		static inline Display * getDisplay()
		{
			return mConfigData->getDisplay();
		}

		static inline XfbManager * getXfbManager()
		{
			return mConfigData->getXfbMgr();
		}
	};
}

#endif