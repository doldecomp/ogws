.include "macros.inc"

.section .data, "wa"
.balign 0x8
lbl_803b7578:
    .string "<< REX-PPC 1.0.0.2 (RevoEX-1.0plus2) REL 070510173628 >>"

.section .sdata, "wa"
.balign 0x8
NETRexPPCVersionPrintableString:
	.long lbl_803b7578

.section .text, "ax"
.global NETGetRexPPCVersionPrintable
NETGetRexPPCVersionPrintable:
/* 80141E00 0013CD00  80 6D 86 38 */	lwz r3, NETRexPPCVersionPrintableString-_SDA_BASE_(r13)
/* 80141E04 0013CD04  4E 80 00 20 */	blr 