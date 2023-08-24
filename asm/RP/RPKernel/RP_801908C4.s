# 
# Debug functionality stubbed for retail.
# May be related to HIO, but who's to say?
# Present in >= Rev 1, but always stubbed
# 

.include "macros.inc"

.section .sbss, "wa"
.balign 0x8
# Singleton instance
.global lbl_804BF530
lbl_804BF530:
	.skip 0x4

.section .text, "ax"
# Only non-scene thing drawn during RP renderer's DebugDraw phase
.global func_801908C4
func_801908C4:
/* 801908C4 0018B7C4  4E 80 00 20 */	blr 

# Updated right before HIO socket manager
.global func_801908C8
func_801908C8:
/* 801908C8 0018B7C8  4E 80 00 20 */	blr 