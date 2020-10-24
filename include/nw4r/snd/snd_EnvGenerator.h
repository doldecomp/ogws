#ifndef NW4R_SND_ENV_GENERATOR_H
#define NW4R_SND_ENV_GENERATOR_H
#include "types_nw4r.h"
#include "snd_WaveFile.h"
#include "snd_EnvGenerator.h"

namespace nw4r
{
	namespace snd
	{
		namespace detail
		{
			struct EnvGenerator
			{
				UNKTYPE SetAttack(int);
				UNKTYPE SetDecay(int);
				UNKTYPE SetSustain(int);
				UNKTYPE SetRelease(int);
			};
		}
	}
}

#endif