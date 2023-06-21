.include "macros.inc"

.section .data, "wa"
.balign 0x8
lbl_803AB6A0:
	.string "Invalid app_id [%d]\n"
    .balign 4
lbl_803AB6B8:
	.string "bta_hh_co_open()\n"
    .balign 4
lbl_803AB6CC:
	.string "bta_hh_co_close()\n"
    .balign 4

# TEMP!!!!!!!!!
.global lbl_803ab6e0
lbl_803ab6e0:
	.string "<< RVL_SDK - AI \trelease build: Nov 30 2006 03:26:11 (0x4199_60831) >>"
	.balign 4

.section .text, "ax"
.global bta_hh_co_data
bta_hh_co_data:
/* 801034E8 000FE3E8  28 08 00 03 */	cmplwi r8, 3
/* 801034EC 000FE3EC  3C C0 80 43 */	lis r6, _wcb@ha
/* 801034F0 000FE3F0  38 C6 92 20 */	addi r6, r6, _wcb@l
/* 801034F4 000FE3F4  40 82 00 18 */	bne lbl_8010350C
/* 801034F8 000FE3F8  81 86 06 EC */	lwz r12, 0x6ec(r6)
/* 801034FC 000FE3FC  2C 0C 00 00 */	cmpwi r12, 0
/* 80103500 000FE400  4D 82 00 20 */	beqlr 
/* 80103504 000FE404  7D 89 03 A6 */	mtctr r12
/* 80103508 000FE408  4E 80 04 20 */	bctr 
lbl_8010350C:
/* 8010350C 000FE40C  3C 60 80 3B */	lis r3, lbl_803AB6A0@ha
/* 80103510 000FE410  7D 04 43 78 */	mr r4, r8
/* 80103514 000FE414  38 63 B6 A0 */	addi r3, r3, lbl_803AB6A0@l
/* 80103518 000FE418  4C C6 31 82 */	crclr 6
/* 8010351C 000FE41C  48 00 00 30 */	b WUD_DEBUGPrint
/* 80103520 000FE420  4E 80 00 20 */	blr 

.global bta_hh_co_open
bta_hh_co_open:
/* 80103524 000FE424  3C 60 80 3B */	lis r3, lbl_803AB6B8@ha
/* 80103528 000FE428  38 63 B6 B8 */	addi r3, r3, lbl_803AB6B8@l
/* 8010352C 000FE42C  4C C6 31 82 */	crclr 6
/* 80103530 000FE430  48 00 00 1C */	b WUD_DEBUGPrint

.global bta_hh_co_close
bta_hh_co_close:
/* 80103534 000FE434  3C 60 80 3B */	lis r3, lbl_803AB6CC@ha
/* 80103538 000FE438  38 63 B6 CC */	addi r3, r3, lbl_803AB6CC@l
/* 8010353C 000FE43C  4C C6 31 82 */	crclr 6
/* 80103540 000FE440  48 00 00 0C */	b WUD_DEBUGPrint

.global bta_dm_co_get_compress_memory
bta_dm_co_get_compress_memory:
/* 80103544 000FE444  38 60 00 00 */	li r3, 0
/* 80103548 000FE448  4E 80 00 20 */	blr 
