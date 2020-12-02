.include "macros.inc"

.section .text, "ax"  # 0x800076E0 - 0x80355080 

.global func_8004124C
func_8004124C:
/* 8004124C 0003C14C  C0 44 00 00 */	lfs f2, 0(r4)
/* 80041250 0003C150  C0 24 00 04 */	lfs f1, 4(r4)
/* 80041254 0003C154  C0 04 00 08 */	lfs f0, 8(r4)
/* 80041258 0003C158  D0 43 00 B8 */	stfs f2, 0xb8(r3)
/* 8004125C 0003C15C  D0 23 00 BC */	stfs f1, 0xbc(r3)
/* 80041260 0003C160  D0 03 00 C0 */	stfs f0, 0xc0(r3)
/* 80041264 0003C164  4E 80 00 20 */	blr 

.global detail_Update__Q34nw4r3snd12Sound3DActorFPvPCQ44nw4r3snd6detail10BasicSound
detail_Update__Q34nw4r3snd12Sound3DActorFPvPCQ44nw4r3snd6detail10BasicSound:
/* 80041268 0003C168  C0 03 00 B8 */	lfs f0, 0xb8(r3)
/* 8004126C 0003C16C  D0 04 00 0C */	stfs f0, 0xc(r4)
/* 80041270 0003C170  C0 03 00 BC */	lfs f0, 0xbc(r3)
/* 80041274 0003C174  D0 04 00 10 */	stfs f0, 0x10(r4)
/* 80041278 0003C178  C0 03 00 C0 */	lfs f0, 0xc0(r3)
/* 8004127C 0003C17C  D0 04 00 14 */	stfs f0, 0x14(r4)
/* 80041280 0003C180  80 03 00 B4 */	lwz r0, 0xb4(r3)
/* 80041284 0003C184  90 04 00 00 */	stw r0, 0(r4)
/* 80041288 0003C188  4E 80 00 20 */	blr 

.global func_8004128C
func_8004128C:
/* 8004128C 0003C18C  80 63 00 04 */	lwz r3, 4(r3)
/* 80041290 0003C190  81 83 00 00 */	lwz r12, 0(r3)
/* 80041294 0003C194  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 80041298 0003C198  7D 89 03 A6 */	mtctr r12
/* 8004129C 0003C19C  4E 80 04 20 */	bctr 

.global $$2168$$2detail_Update__Q34nw4r3snd12Sound3DActorFPvPCQ44nw4r3snd6detail10BasicSound
$$2168$$2detail_Update__Q34nw4r3snd12Sound3DActorFPvPCQ44nw4r3snd6detail10BasicSound:
/* 800412A0 0003C1A0  38 63 FF 58 */	addi r3, r3, -168
/* 800412A4 0003C1A4  4B FF FF C4 */	b detail_Update__Q34nw4r3snd12Sound3DActorFPvPCQ44nw4r3snd6detail10BasicSound
