#ifndef EGG_CORE_SCENE_CREATOR_H
#define EGG_CORE_SCENE_CREATOR_H
#include "types_egg.h"

namespace EGG
{
	struct SceneCreator
	{
		virtual Scene * create(s32) = 0;
		virtual UNKTYPE destroy(s32) = 0;
	};
}

#endif