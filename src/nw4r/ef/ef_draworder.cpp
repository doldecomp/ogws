#include "ef_draworder.h"
#include "ef_effect.h"

namespace nw4r
{
	using namespace ut;
	
	namespace ef
	{
		void DrawOrder::Draw(Effect * pEffect, const DrawInfo & drawInfo)
		{
			List * pList = &pEffect->UTLIST_0x90;
			ParticleManager * pManager = NULL;
			while (pManager = (ParticleManager *)List_GetNext(pList, pManager))
			{
				pManager->BeginDraw();
				pManager->Draw(drawInfo);
				pManager->EndDraw();
			}
		}
		
		void DrawOrder::Add(Effect * pEffect, ParticleManager * pManager)
		{
			List * pList = &pEffect->UTLIST_0x90;
			ParticleManager * pos = NULL;
			
			while (pos = (ParticleManager *)List_GetPrev(pList, pos))
			{
				if (pos->BYTE_0x89 <= pManager->BYTE_0x89) break;
			}
			
			List_Insert(pList, List_GetNext(pList, pos), pManager);
		}
		
		void DrawOrder::Remove(Effect * pEffect, ParticleManager * pManager)
		{
			List_Remove(&pEffect->UTLIST_0x90, pManager);
		}
	}
}