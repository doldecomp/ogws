#ifndef TYPES_NW4R_H
#define TYPES_NW4R_H

#define NULL 0

typedef unsigned long u32;
typedef signed long s32;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned char u8;
typedef signed char s8;

namespace nw4r
{
	namespace ut
	{
		template <typename T> struct TextWriterBase;
		template <typename T> struct TagProcessorBase;
	}
}

typedef int UNKWORD;
typedef void UNKTYPE;

#endif