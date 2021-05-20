#ifndef EGG_CORE_SCENE_H
#define EGG_CORE_SCENE_H
#include "types_egg.h"

namespace EGG
{
	class Scene
	{
	public:
		Scene();
		
		virtual ~Scene();
		inline virtual void calc() {}
		inline virtual void draw() {}
		inline virtual void enter() {}
		inline virtual void exit() {}
		inline virtual void reinit() {}
		inline virtual void incoming_childDestroy() {}
		inline virtual void outgoing_childCreate() {}
		
		inline Heap * getHeap() const { return mHeap; }
		inline Heap * getHeap_Mem1() const { return mHeap_Mem1; }
		inline Heap * getHeap_Mem2() const { return mHeap_Mem2; }
		inline Heap * getHeap_Debug() const { return mHeap_Debug; }
		inline Scene * getParentScene() const { return mParentScene; }
		inline Scene * getChildScene() const { return mChildScene; }
		inline s32 getSceneID() const { return mSceneID; }
		
		inline void setParentScene(Scene * pParentScene) { mParentScene = pParentScene; }
		inline void setChildScene(Scene * pChildScene) { mChildScene = pChildScene; }
		inline void setSceneID(s32 sceneID) { mSceneID = sceneID; }
		inline void setSceneMgr(SceneManager * pSceneMgr) { mSceneMgr = pSceneMgr; }
	private:
		Heap * mHeap; // at 0x4
		Heap * mHeap_Mem1; // at 0x8
		Heap * mHeap_Mem2; // at 0xc
		Heap * mHeap_Debug; // at 0x10
		Scene * mParentScene; // at 0x14
		Scene * mChildScene; // at 0x18
		s32 mSceneID; // at 0x1c
		SceneManager * mSceneMgr; // at 0x20
	};
}

#endif