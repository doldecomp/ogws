.include "macros.inc"

.section .sbss, "wa"
.balign 8
.global cInvalidHandle__3EGG
cInvalidHandle__3EGG:
	.skip 0x8

.section .ctors, "a"
.4byte __sinit_$$3eggEffect_cpp

.section .text, "ax"
.global ModifierTravFunc_SetSimpleLightType__Q34nw4r2ef15ParticleManagerFPvUl
ModifierTravFunc_SetSimpleLightType__Q34nw4r2ef15ParticleManagerFPvUl:
/* 800B16E0 000AC5E0  98 83 00 6C */	stb r4, 0x6c(r3)
/* 800B16E4 000AC5E4  4E 80 00 20 */	blr 

.global ModifierTravFunc_SetSimpleLightAmbient__Q34nw4r2ef15ParticleManagerFPvUl
ModifierTravFunc_SetSimpleLightAmbient__Q34nw4r2ef15ParticleManagerFPvUl:
/* 800B16E8 000AC5E8  88 04 00 00 */	lbz r0, 0(r4)
/* 800B16EC 000AC5EC  98 03 00 6D */	stb r0, 0x6d(r3)
/* 800B16F0 000AC5F0  88 04 00 01 */	lbz r0, 1(r4)
/* 800B16F4 000AC5F4  98 03 00 6E */	stb r0, 0x6e(r3)
/* 800B16F8 000AC5F8  88 04 00 02 */	lbz r0, 2(r4)
/* 800B16FC 000AC5FC  98 03 00 6F */	stb r0, 0x6f(r3)
/* 800B1700 000AC600  88 04 00 03 */	lbz r0, 3(r4)
/* 800B1704 000AC604  98 03 00 70 */	stb r0, 0x70(r3)
/* 800B1708 000AC608  4E 80 00 20 */	blr

.global ModifierTravFunc_SetScale__Q34nw4r2ef15ParticleManagerFPvUl
ModifierTravFunc_SetScale__Q34nw4r2ef15ParticleManagerFPvUl:
/* 800B170C 000AC60C  C0 04 00 00 */	lfs f0, 0(r4)
/* 800B1710 000AC610  D0 03 00 58 */	stfs f0, 0x58(r3)
/* 800B1714 000AC614  C0 04 00 04 */	lfs f0, 4(r4)
/* 800B1718 000AC618  D0 03 00 5C */	stfs f0, 0x5c(r3)
/* 800B171C 000AC61C  4E 80 00 20 */	blr 

.global ModifierTravFunc_SetRotate__Q34nw4r2ef15ParticleManagerFPvUl
ModifierTravFunc_SetRotate__Q34nw4r2ef15ParticleManagerFPvUl:
/* 800B1720 000AC620  C0 04 00 00 */	lfs f0, 0(r4)
/* 800B1724 000AC624  D0 03 00 60 */	stfs f0, 0x60(r3)
/* 800B1728 000AC628  C0 04 00 04 */	lfs f0, 4(r4)
/* 800B172C 000AC62C  D0 03 00 64 */	stfs f0, 0x64(r3)
/* 800B1730 000AC630  C0 04 00 08 */	lfs f0, 8(r4)
/* 800B1734 000AC634  D0 03 00 68 */	stfs f0, 0x68(r3)
/* 800B1738 000AC638  4E 80 00 20 */	blr 

# __sinit_\eggEffect_cpp
.global __sinit_$$3eggEffect_cpp
__sinit_$$3eggEffect_cpp:
/* 800B173C 000AC63C  38 6D 99 D0 */	addi r3, r13, cInvalidHandle__3EGG-_SDA_BASE_
/* 800B1740 000AC640  4B F6 B3 8C */	b __ct__Q34nw4r2ef10HandleBaseFv
