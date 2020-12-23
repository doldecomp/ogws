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
		struct DrawStrategy;
		struct DrawStrategyImpl;
		struct DrawStrategyBuilder;
		struct Effect;
		struct EffectSystem;
		struct EffectProject;
		struct Emitter;
		struct EmitFormBuilder;
		struct ResEmitter;
		struct EmitterResource;
		struct EmitterForm;
		struct EmitterInheritSetting;
		struct Particle;
		struct ParticleManager;
		struct MemoryManager;
		struct MemoryManagerBase;
	}
	
	namespace math
	{
		struct VEC2;
		struct VEC3;
		struct MTX34;
	}
	
	namespace snd
	{
		struct FxBase;
		struct SoundPlayer;
		struct SoundHandle;
		struct SeqSoundHandle;
		struct SoundArchive;
		struct SoundArchivePlayer;
		struct Sound3DActor;
		struct Sound3DManager;
		
		namespace detail
		{
			struct BasicSound;
			struct SeqSound;
			struct SeqPlayer;
			struct MmlParser;
			struct MmlSeqTrack;
			struct SeqTrack;
			struct SeqTrackAllocator;
			struct NoteOnCallback;
			struct PlayerHeap;
		}
	}
}

typedef int UNKWORD;
typedef void UNKTYPE;

#endif