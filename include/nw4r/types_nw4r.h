#ifndef TYPES_NW4R_H
#define TYPES_NW4R_H
#include <types.h>

namespace nw4r
{
	namespace ut
	{
		template <typename T> struct TextWriterBase;
		template <typename T> struct TagProcessorBase;
	}
	
	namespace ef
	{
		struct DrawOrder;
		struct DrawInfo;
		struct Effect;
		struct EffectSystem;
		struct Emitter;
		struct ResEmitter;
		struct EmitterResource;
		struct EmitterInheritSetting;
		struct Particle;
		struct MemoryManager;
	}
	
	namespace math
	{
		struct VEC2;
		struct VEC3;
		struct MTX34;
	}
}

typedef int UNKWORD;
typedef void UNKTYPE;

#endif