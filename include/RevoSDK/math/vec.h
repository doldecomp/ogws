#ifndef REVOSDK_MATH_VEC_H
#define REVOSDK_MATH_VEC_H
#ifdef __cplusplus
extern "C" {
#endif
#include <types.h>

struct Vec
{
	float x;
	float y;
	float z;
};

void PSVECNormalize(const struct Vec *, struct Vec *);
float PSVECSquareDistance(const struct Vec *, const struct Vec *);
float PSVECMag(const struct Vec *);

#ifdef __cplusplus
}
#endif
#endif