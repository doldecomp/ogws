#ifndef EGG_CORE_SCENE_MANAGER_H
#define EGG_CORE_SCENE_MANAGER_H
#include "eggHeap.h"
#include "eggFader.h"
#include "eggSceneCreator.h"

namespace EGG
{
	class SceneManager
	{
	public:
		enum eAfterFadeType
		{
			AFTER_FADE_TYPE_CHANGE,
			AFTER_FADE_TYPE_CHANGE_SIBLING,
			AFTER_FADE_TYPE_CREATE_CHILD,
			AFTER_FADE_TYPE_REINIT,
			AFTER_FADE_TYPE_DESTROY_TO_SELECT,
			AFTER_FADE_TYPE_NULL = -1
		};
		
		virtual void calc();
		virtual void draw();
		
		virtual void calcCurrentScene();
		virtual void calcCurrentFader();
		
		virtual void drawCurrentScene();
		virtual void drawCurrentFader();
		
		virtual void createDefaultFader();
		
		SceneManager(SceneCreator *);
		~SceneManager();
		
		UNKTYPE fadeIn();
		bool fadeOut(); //inlined
		
		void reinitCurrentScene(); //inlined
		bool reinitCurrentSceneAfterFadeOut();
		
		void changeScene(s32);
		bool changeSceneAfterFadeOut(s32);
		
		void changeSiblingScene(s32); //inlined
		bool changeSiblingSceneAfterFadeOut(s32);
		
		void createScene(s32, Scene *);
		void createChildScene(s32, Scene *);
		bool createChildSceneAfterFadeOut(s32, Scene *);
		
		void destroyToSelectSceneID(s32); //inlined
		bool destroyToSelectSceneIDAfterFadeOut(s32);
		
		UNKTYPE destroyScene(Scene *);
		
		void incomingCurrentScene(); //inlined
		
		void setupNextSceneID(); //inlined
		
		void outgoingParentScene(Scene *); //inlined
		
		Scene * findParentScene(s32);
		
		inline s32 getCurrentSceneID() const { return mCurrentSceneID; }
		
		static inline Heap * getHeapForCreateScene_Mem1() { return sHeapMem1_ForCreateScene; }
		static inline Heap * getHeapForCreateScene_Mem2() { return sHeapMem2_ForCreateScene; }
		static inline Heap * getHeapForCreateScene_Debug() { return sHeapDebug_ForCreateScene; }
	private:
		SceneCreator * mSceneCreator; // at 0x4
		UNKWORD WORD_0x8; // at 0x8
		Scene * mCurrentScene; // at 0xc
		Scene * PARENT_0x10; // at 0x10
		s32 mNextSceneID; // at 0x14
		s32 mCurrentSceneID; // at 0x18
		s32 mPreviousSceneID; // at 0x1c
		eAfterFadeType mAfterFadeType; // at 0x20
		Fader * mCurrentFader; // at 0x24
		UNKWORD INT_0x28; // at 0x28
		
		static u16 sHeapOptionFlg;
		
		static Heap * sHeapMem1_ForCreateScene;
		static Heap * sHeapMem2_ForCreateScene;
		static Heap * sHeapDebug_ForCreateScene;
	};
}

#endif