.include "macros.inc"

.section .text, "ax"  # 0x800076E0 - 0x80355080 

.global __ct__Q34nw4r3snd15Sound3DListenerFv
__ct__Q34nw4r3snd15Sound3DListenerFv:
/* 800412A8 0003C1A8  C0 02 86 90 */	lfs f0, lbl_804C00B0-_SDA2_BASE_(r2)
/* 800412AC 0003C1AC  D0 03 00 30 */	stfs f0, 0x30(r3)
/* 800412B0 0003C1B0  D0 03 00 34 */	stfs f0, 0x34(r3)
/* 800412B4 0003C1B4  D0 03 00 38 */	stfs f0, 0x38(r3)
/* 800412B8 0003C1B8  4E 80 00 20 */	blr 
