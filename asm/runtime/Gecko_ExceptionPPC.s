.include "macros.inc"

.section .bss, "wa"
.balign 0x8
.global fragmentinfo
fragmentinfo:
	.skip 0xC

.section .text, "ax"
.global __register_fragment
__register_fragment:
/* 800B22F8 000AD1F8  3C A0 80 41 */	lis r5, fragmentinfo@ha
/* 800B22FC 000AD1FC  38 A5 B9 50 */	addi r5, r5, fragmentinfo@l
/* 800B2300 000AD200  80 05 00 08 */	lwz r0, 8(r5)
/* 800B2304 000AD204  2C 00 00 00 */	cmpwi r0, 0
/* 800B2308 000AD208  40 82 00 1C */	bne lbl_800B2324
/* 800B230C 000AD20C  90 65 00 00 */	stw r3, 0(r5)
/* 800B2310 000AD210  38 00 00 01 */	li r0, 1
/* 800B2314 000AD214  38 60 00 00 */	li r3, 0
/* 800B2318 000AD218  90 85 00 04 */	stw r4, 4(r5)
/* 800B231C 000AD21C  90 05 00 08 */	stw r0, 8(r5)
/* 800B2320 000AD220  4E 80 00 20 */	blr 
lbl_800B2324:
/* 800B2324 000AD224  38 60 FF FF */	li r3, -1
/* 800B2328 000AD228  4E 80 00 20 */	blr 

.global __unregister_fragment
__unregister_fragment:
/* 800B232C 000AD22C  2C 03 00 00 */	cmpwi r3, 0
/* 800B2330 000AD230  4D 80 00 20 */	bltlr 
/* 800B2334 000AD234  2C 03 00 01 */	cmpwi r3, 1
/* 800B2338 000AD238  4C 80 00 20 */	bgelr 
/* 800B233C 000AD23C  1C 83 00 0C */	mulli r4, r3, 0xc
/* 800B2340 000AD240  3C 60 80 41 */	lis r3, fragmentinfo@ha
/* 800B2344 000AD244  38 00 00 00 */	li r0, 0
/* 800B2348 000AD248  38 63 B9 50 */	addi r3, r3, fragmentinfo@l
/* 800B234C 000AD24C  7C 03 21 6E */	stwux r0, r3, r4
/* 800B2350 000AD250  90 03 00 04 */	stw r0, 4(r3)
/* 800B2354 000AD254  90 03 00 08 */	stw r0, 8(r3)
/* 800B2358 000AD258  4E 80 00 20 */	blr
