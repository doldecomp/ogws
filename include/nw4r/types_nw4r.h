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
		struct Sound3DListener;
		struct Sound3DManager;
		struct SoundHandle;
		struct StrmSoundHandle;
		struct WaveSoundHandle;

		namespace detail
		{
			struct BasicSound;
			struct BasicPlayer;
			struct SeqSound;
			struct SeqPlayer;
			struct MmlParser;
			struct MmlSeqTrack;
			struct SeqTrack;
			struct SeqTrackAllocator;
			struct NoteOnCallback;
			struct PlayerHeap;
			struct SoundArchiveFileReader;
			struct StrmSound;
			struct WaveSound;
		}
	}
	
	namespace g3d
	{
		struct ResFile;
		struct ResMdl;
		struct ResPltt;
		struct ResTex;
		struct ResMat;
		struct ResTexPlttInfo;
		struct ResShp;
		struct ResAnmChr;
		struct ResAnmVis;
		struct ResAnmClr;
		struct ResAnmTexPat;
		struct ResAnmTexSrt;
		struct ResAnmShp;
		struct ResAnmScn;
		struct ResVtxPos;
		struct ResVtxNrm;
		struct ResVtxClr;
		struct ResVtxTexCoord;
		struct ClrAnmResult;
		struct TexPatAnmResult;
		struct TexSrtAnmResult;
	}

	namespace lyt
	{
		struct DrawInfo;
		struct ResourceAccessor;
		struct ArcResourceAccessor;
	}
}

typedef int UNKWORD;
typedef void UNKTYPE;

#endif