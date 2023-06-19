.include "macros.inc"

.section .text, "ax"
.global copysign
copysign:
/* 800C07EC 000BB6EC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800C07F0 000BB6F0  D8 21 00 08 */	stfd f1, 8(r1)
/* 800C07F4 000BB6F4  D8 41 00 10 */	stfd f2, 0x10(r1)
/* 800C07F8 000BB6F8  80 61 00 08 */	lwz r3, 8(r1)
/* 800C07FC 000BB6FC  80 01 00 10 */	lwz r0, 0x10(r1)
/* 800C0800 000BB700  54 00 00 00 */	rlwinm r0, r0, 0, 0, 0
/* 800C0804 000BB704  50 60 00 7E */	rlwimi r0, r3, 0, 1, 0x1f
/* 800C0808 000BB708  90 01 00 08 */	stw r0, 8(r1)
/* 800C080C 000BB70C  C8 21 00 08 */	lfd f1, 8(r1)
/* 800C0810 000BB710  38 21 00 20 */	addi r1, r1, 0x20
/* 800C0814 000BB714  4E 80 00 20 */	blr 
