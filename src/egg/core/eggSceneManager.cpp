#pragma ipa file
#pragma use_lmw_stmw on
#include <GXMisc.h>
#include "eggAssert.h"
#include "eggScene.h"
#include "eggSceneManager.h"
#include "eggSystem.h"
#include "eggExpHeap.h"
#include "eggVideo.h"
#include "eggDisplay.h"
#include "eggColorFader.h"

namespace EGG
{
	SceneManager::SceneManager(SceneCreator * pSceneCreator)
	{
		mSceneCreator = pSceneCreator;
		mCurrentScene = NULL;
		mPreviousSceneID = -1;
		mCurrentSceneID = -1;
		mNextSceneID = -1;
		mAfterFadeType = AFTER_FADE_TYPE_NULL;
		mCurrentFader = NULL;
		INT_0x28 = 1;
		
		createDefaultFader();
		
		#line 60
		EGG_ASSERT(mCurrentFader);
	}
	
	SceneManager::~SceneManager() {}
	
	UNKTYPE SceneManager::fadeIn()
	{
		#line 77
		EGG_ASSERT(mCurrentFader);
		
		mCurrentFader->fadeIn();
	}
	
	bool SceneManager::fadeOut()
	{
		#line 87
		EGG_ASSERT(mCurrentFader);
		
		return mCurrentFader->fadeOut();
	}
	
	void SceneManager::calc()
	{
		calcCurrentScene();
		calcCurrentFader();
	}
	
	void SceneManager::draw()
	{
		drawCurrentScene();
		drawCurrentFader();
	}
	
	void SceneManager::reinitCurrentScene()
	{
		if (mCurrentScene) mCurrentScene->reinit();
	}
	
	bool SceneManager::reinitCurrentSceneAfterFadeOut()
	{
		bool ret = false;
		
		if (mAfterFadeType == AFTER_FADE_TYPE_NULL && fadeOut())
		{
			mAfterFadeType = AFTER_FADE_TYPE_REINIT;
			ret = true;
		}
		
		return ret;
	}
	
	void SceneManager::changeScene(s32 id)
	{
		while (mCurrentScene)
		{
			if (mCurrentScene)
			{
				Scene * pParent = mCurrentScene->getParentScene();
				
				if (pParent)
				{
					destroyScene(pParent->getChildScene());
					
					mNextSceneID = pParent->getSceneID();
					setupNextSceneID();
				}
				else
				{
					destroyScene(mCurrentScene);
					
					mNextSceneID = -1;
					setupNextSceneID();
				}
			}
		}
		
		changeSiblingScene(id);
	}
	
	bool SceneManager::changeSceneAfterFadeOut(s32 id)
	{
		bool ret = false;
		
		if (mAfterFadeType == AFTER_FADE_TYPE_NULL && fadeOut())
		{
			mNextSceneID = id;
			mAfterFadeType = AFTER_FADE_TYPE_CHANGE;
			ret = true;
		}
		
		return ret;
	}
	
	void SceneManager::changeSiblingScene(s32 id)
	{
		mNextSceneID = id;
		
		Scene * pScene = NULL;
		
		if (mCurrentScene) pScene = mCurrentScene->getParentScene();
		
		if (mCurrentScene)
		{
			destroyScene(mCurrentScene);
			
			mCurrentScene = NULL;
		}
		
		setupNextSceneID();
		
		createScene(mCurrentSceneID, pScene);
	}
	
	bool SceneManager::changeSiblingSceneAfterFadeOut(s32 id)
	{
		bool ret = false;
		
		if (mAfterFadeType == AFTER_FADE_TYPE_NULL && fadeOut())
		{
			mNextSceneID = id;
			mAfterFadeType = AFTER_FADE_TYPE_CHANGE_SIBLING;
			ret = true;
		}
		
		return ret;
	}
	
	void SceneManager::createScene(s32 id, Scene * pParent)
	{
		BOOL isAllocationDisabled; // at r27
		Heap * pParentHeap_Mem1; // at r26
		Heap * pParentHeap_Mem2; // at r25
		Heap * pParentHeap_Debug; // at r24
		
		if (pParent)
		{
			pParentHeap_Mem1 = pParent->getHeap_Mem1();
			pParentHeap_Mem2 = pParent->getHeap_Mem2();
			pParentHeap_Debug = pParent->getHeap_Debug();
		}
		else
		{
			pParentHeap_Mem1 = BaseSystem::getRootHeapMem1();
			pParentHeap_Mem2 = BaseSystem::getRootHeapMem2();
			pParentHeap_Debug = BaseSystem::getRootHeapDebug();
		}
		
		Heap * pParentHeap = !INT_0x28 ? pParentHeap_Mem1 : pParentHeap_Mem2; // at r28
		
		#line 267
		EGG_ASSERT(pParentHeap_Mem1 && pParentHeap_Mem2);
		isAllocationDisabled = pParentHeap->tstDisableAllocation() ? TRUE : FALSE; // at r27
		
		if (isAllocationDisabled) pParentHeap->enableAllocation();
		
		ExpHeap * pNewHeap = ExpHeap::create(-1, pParentHeap, sHeapOptionFlg); // at r23
		
		ExpHeap * pNewHeap_Mem1; // at r25
		ExpHeap * pNewHeap_Mem2; // at r26
		ExpHeap * pNewHeap_Debug = NULL; // at r22
		
		if (pParentHeap == pParentHeap_Mem2)
		{
			pNewHeap_Mem1 = ExpHeap::create(-1, pParentHeap_Mem1, sHeapOptionFlg);
			pNewHeap_Mem2 = pNewHeap;
		}
		else
		{
			pNewHeap_Mem2 = ExpHeap::create(-1, pParentHeap_Mem2, sHeapOptionFlg);
			pNewHeap_Mem1 = pNewHeap;
		}
		
		if (pParentHeap_Debug)
		{
			pNewHeap_Debug = ExpHeap::create(-1, pParentHeap_Debug, sHeapOptionFlg);
		}
		
		sHeapMem1_ForCreateScene = pNewHeap_Mem1;
		sHeapMem2_ForCreateScene = pNewHeap_Mem2;
		sHeapDebug_ForCreateScene = pNewHeap_Debug;
		
		#line 299
		EGG_ASSERT(pNewHeap && pNewHeap_Mem1 && pNewHeap_Mem2);
		
		if (isAllocationDisabled) pParentHeap->disableAllocation();
		
		pNewHeap->becomeCurrentHeap();
		
		#line 311
		EGG_ASSERT(mSceneCreator);
		Scene * pNewScene = mSceneCreator->create(id);
		EGG_ASSERT(pNewScene);
		
		if (pParent) pParent->setChildScene(pNewScene);
		
		mCurrentScene = pNewScene;
		
		pNewScene->setSceneID(id);
		pNewScene->setParentScene(pParent);
		pNewScene->setSceneMgr(this);
		
		pNewScene->enter();
	}
	
	void SceneManager::createChildScene(s32 id, Scene * pParent)
	{
		outgoingParentScene(pParent);
		
		mNextSceneID = id;
		setupNextSceneID();
		
		createScene(id, pParent);
	}
	
	bool SceneManager::createChildSceneAfterFadeOut(s32 id, Scene * pParent)
	{
		bool ret = false;
		
		if (mAfterFadeType == AFTER_FADE_TYPE_NULL)
		{
			#line 360
			EGG_ASSERT(pParent);
			
			if (fadeOut())
			{
				mNextSceneID = id;
				ret = true;
				PARENT_0x10 = pParent;
				mAfterFadeType = AFTER_FADE_TYPE_CREATE_CHILD;
			}
		}
		
		return ret;
	}
	
	void SceneManager::destroyToSelectSceneID(s32 id)
	{
		Scene * pParent = findParentScene(id);
		
		if (pParent)
		{
			while (pParent->getSceneID() != getCurrentSceneID())
			{
				if (mCurrentScene)
				{
					Scene * pParent = mCurrentScene->getParentScene(); // at r29
					
					if (pParent)
					{
						destroyScene(pParent->getChildScene());
						
						mNextSceneID = pParent->getSceneID();
						setupNextSceneID();
					}
				}
			}
			
			incomingCurrentScene();
		}
	}
	
	bool SceneManager::destroyToSelectSceneIDAfterFadeOut(s32 id)
	{
		bool ret = false;
		
		if (mAfterFadeType == AFTER_FADE_TYPE_NULL && fadeOut() && findParentScene(id))
		{
			mNextSceneID = id;
			ret = true;
			mAfterFadeType = AFTER_FADE_TYPE_DESTROY_TO_SELECT;
		}
		
		return ret;
	}
	
	UNKTYPE SceneManager::destroyScene(Scene * pScene)
	{
		#line 490
		EGG_ASSERT(pScene);
		
		pScene->exit();
		
		if (pScene->getChildScene()) destroyScene(pScene->getChildScene());
		
		GXFlush();
		GXDrawDone();
		
		Scene * pParent = pScene->getParentScene(); // at r31
		
		#line 509
		EGG_ASSERT(mSceneCreator);
		
		mSceneCreator->destroy(pScene->getSceneID());
		
		mCurrentScene = NULL;
		
		if (pParent)
		{
			pParent->setChildScene(NULL);
			mCurrentScene = pParent;
		}
		
		if (pScene->getHeap_Debug())
		{
			#line 523
			EGG_ASSERT(pScene->getHeap() != pScene->getHeap_Debug());
			
			pScene->getHeap_Debug()->destroy();
		}
		
		if (pScene->getHeap_Mem1() == pScene->getHeap())
		{
			pScene->getHeap_Mem2()->destroy();
			pScene->getHeap_Mem1()->destroy();
		}
		else if (pScene->getHeap_Mem2() == pScene->getHeap())
		{
			pScene->getHeap_Mem1()->destroy();
			pScene->getHeap_Mem2()->destroy();
		}
		else
		{
			#line 538
			EGG_ASSERT(0);
		}
		
		Heap * pParentHeap; // at r31
		
		if (pParent)
		{
			pParentHeap = pParent->getHeap();
		}
		else
		{
			pParentHeap = !INT_0x28 ? BaseSystem::getRootHeapMem1() : BaseSystem::getRootHeapMem2();
		}
		
		#line 551
		EGG_ASSERT(pParentHeap != NULL);
		
		pParentHeap->becomeCurrentHeap();
	}
	
	void SceneManager::incomingCurrentScene()
	{
		if (mCurrentScene) mCurrentScene->incoming_childDestroy();
	}
	
	void SceneManager::calcCurrentScene()
	{
		if (mCurrentScene) mCurrentScene->calc();
	}
	
	void SceneManager::calcCurrentFader()
	{
		if (mCurrentFader && mCurrentFader->calc())
		{
			switch (mAfterFadeType)
			{
				case AFTER_FADE_TYPE_CHANGE:
					changeScene(mNextSceneID);
					break;
				case AFTER_FADE_TYPE_CHANGE_SIBLING:
					changeSiblingScene(mNextSceneID);
					break;
				case AFTER_FADE_TYPE_CREATE_CHILD:
					outgoingParentScene(PARENT_0x10);
					
					setupNextSceneID();
					
					createScene(mCurrentSceneID, PARENT_0x10);
					break;
				case AFTER_FADE_TYPE_DESTROY_TO_SELECT:
					destroyToSelectSceneID(mNextSceneID);
					break;
				case AFTER_FADE_TYPE_REINIT:
					reinitCurrentScene();
					break;
			}
			mAfterFadeType = AFTER_FADE_TYPE_NULL;
		}
	}
	
	void SceneManager::drawCurrentScene()
	{
		if (mCurrentScene)
		{
			mCurrentScene->draw();

			Display * pDisplay = BaseSystem::getDisplay();
			Video * pVideo = BaseSystem::getVideo();

			if (pVideo->isBlack() && !pDisplay->isBlack())
			{
				pDisplay->setBlack(true);
			}
		}
	}
	
	void SceneManager::drawCurrentFader()
	{
		if (mCurrentFader) mCurrentFader->draw();
	}
	
	void SceneManager::createDefaultFader()
	{
		mCurrentFader = new ColorFader(0.0f, 0.0f, 640.0f, 480.0f, 0, Fader::STATUS_PREPARE_IN);
	}
	
	void SceneManager::setupNextSceneID()
	{
		mPreviousSceneID = mCurrentSceneID;
		mCurrentSceneID = mNextSceneID;
		mNextSceneID = -1;
	}
	
	void SceneManager::outgoingParentScene(Scene * pParent)
	{
		#line 701
		EGG_ASSERT(pParent);
		
		#line 704
		EGG_ASSERT(pParent->getChildScene() == NULL);
		
		pParent->outgoing_childCreate();
	}
	
	Scene * SceneManager::findParentScene(s32 id)
	{
		bool found = false;
		Scene * pScene = mCurrentScene->getParentScene();
		
		while (pScene)
		{
			if (id == pScene->getSceneID())
			{
				found = true;
				break;
			}
			
			pScene = pScene->getParentScene();
		}
		
		return found ? pScene : NULL;
	}
	
	u16 SceneManager::sHeapOptionFlg;
	
	Heap * SceneManager::sHeapMem1_ForCreateScene;
	Heap * SceneManager::sHeapMem2_ForCreateScene;
	Heap * SceneManager::sHeapDebug_ForCreateScene;
}