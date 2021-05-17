#ifndef EGG_CORE_FADER_H
#define EGG_CORE_FADER_H
#include "types_egg.h"

namespace EGG
{
	struct Fader
    {
        enum EStatus
        {
			STATUS_PREPARE_IN,
			STATUS_PREPARE_OUT,
			STATUS_FADE_IN,
			STATUS_FADE_OUT
        };

        virtual void setStatus(EStatus) = 0;
        virtual EStatus getStatus() const = 0;
        virtual bool fadeIn() = 0;
        virtual bool fadeOut() = 0;
        virtual bool calc() = 0;
        virtual void draw() = 0;
    };
}

#endif