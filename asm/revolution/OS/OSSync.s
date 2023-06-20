.include "macros.inc"

.section .text, "ax"
.global __OSSystemCallVectorStart
__OSSystemCallVectorStart: # entry of SystemCallVector
.global SystemCallVector
SystemCallVector:
/* 800F3DD0 000EECD0  7D 30 FA A6 */	mfspr r9, 0x3f0
/* 800F3DD4 000EECD4  61 2A 00 08 */	ori r10, r9, 8
/* 800F3DD8 000EECD8  7D 50 FB A6 */	mtspr 0x3f0, r10
/* 800F3DDC 000EECDC  4C 00 01 2C */	isync 
/* 800F3DE0 000EECE0  7C 00 04 AC */	sync 0
/* 800F3DE4 000EECE4  7D 30 FB A6 */	mtspr 0x3f0, r9
/* 800F3DE8 000EECE8  4C 00 00 64 */	rfi 
.global __OSSystemCallVectorEnd
__OSSystemCallVectorEnd: # entry of SystemCallVector
/* 800F3DEC 000EECEC  60 00 00 00 */	nop 

.global __OSInitSystemCall
__OSInitSystemCall:
/* 800F3DF0 000EECF0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800F3DF4 000EECF4  7C 08 02 A6 */	mflr r0
/* 800F3DF8 000EECF8  3C 80 80 0F */	lis r4, __OSSystemCallVectorStart@ha
/* 800F3DFC 000EECFC  3C A0 80 0F */	lis r5, __OSSystemCallVectorEnd@ha
/* 800F3E00 000EED00  90 01 00 14 */	stw r0, 0x14(r1)
/* 800F3E04 000EED04  38 84 3D D0 */	addi r4, r4, __OSSystemCallVectorStart@l
/* 800F3E08 000EED08  38 A5 3D EC */	addi r5, r5, __OSSystemCallVectorEnd@l
/* 800F3E0C 000EED0C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800F3E10 000EED10  3F E0 80 00 */	lis r31, 0x80000C00@ha
/* 800F3E14 000EED14  38 7F 0C 00 */	addi r3, r31, 0x80000C00@l
/* 800F3E18 000EED18  7C A4 28 50 */	subf r5, r4, r5
/* 800F3E1C 000EED1C  4B F1 01 E5 */	bl memcpy
/* 800F3E20 000EED20  38 7F 0C 00 */	addi r3, r31, 0xc00
/* 800F3E24 000EED24  38 80 01 00 */	li r4, 0x100
/* 800F3E28 000EED28  4B FF A3 69 */	bl DCFlushRangeNoSync
/* 800F3E2C 000EED2C  7C 00 04 AC */	sync 0
/* 800F3E30 000EED30  38 7F 0C 00 */	addi r3, r31, 0xc00
/* 800F3E34 000EED34  38 80 01 00 */	li r4, 0x100
/* 800F3E38 000EED38  4B FF A3 DD */	bl ICInvalidateRange
/* 800F3E3C 000EED3C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800F3E40 000EED40  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800F3E44 000EED44  7C 08 03 A6 */	mtlr r0
/* 800F3E48 000EED48  38 21 00 10 */	addi r1, r1, 0x10
/* 800F3E4C 000EED4C  4E 80 00 20 */	blr 
