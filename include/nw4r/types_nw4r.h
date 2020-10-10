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
		struct DrawStrategyBuilder;
		struct Effect;
		struct EffectSystem;
		struct EffectProject;
		struct Emitter;
		struct EmitFormBuilder;
		struct ResEmitter;
		struct EmitterResource;
		struct EmitterInheritSetting;
		struct Particle;
		struct ParticleManager;
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