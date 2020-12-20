#ifndef NW4R_SND_SOUND_THREAD_H
#define NW4R_SND_SOUND_THREAD_H
#include <OSMutex.h>
#include "types_nw4r.h"
#include "ut_LinkList.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			struct SoundThread
			{
				struct PlayerCallback
				{
					ut::LinkListNode mNode; // at 0x0
					
					inline virtual ~PlayerCallback() {} // at 0x8
					inline virtual void OnUpdateFrameSoundThread() {} // at 0xc
					inline virtual void OnUpdateVoiceSoundThread() {} // at 0x10
					inline virtual void OnShutdownSoundThread() {} // at 0x14
				};
				
				char UNK_0x0[0x354];
				
				OSMutex mMutex; // at 0x354
				
				static SoundThread * GetInstance();
				
				UNKTYPE RegisterPlayerCallback(PlayerCallback *);
				UNKTYPE UnregisterPlayerCallback(PlayerCallback *);
				
				struct AutoLock
				{
					inline AutoLock()
					{
						OSLockMutex(&GetInstance()->mMutex);
					}
					
					inline ~AutoLock()
					{
						OSUnlockMutex(&GetInstance()->mMutex);
					}
				};
			};
		}
	}
}

#endif