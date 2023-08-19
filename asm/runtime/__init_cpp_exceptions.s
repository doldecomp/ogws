.include "macros.inc"

.section .ctors$10, "a"
# __init_cpp_exceptions_reference
.global global_ctors
global_ctors:
.4byte func_800B2288 # __init_cpp_exceptions

.section .dtors$10, "a"
.global global_dtors
global_dtors:
# __destroy_global_chain_reference
.4byte func_800B184C # __destroy_global_chain

# TO-DO: Put this in .dtors$15
.section .dtors$10, "a"
# __fini_cpp_exceptions_reference
.4byte func_800B22C4 # __fini_cpp_exceptions

# _dtors$99?
.long 0

.section .sdata, "wa"
.balign 0x8
.global fragmentID
fragmentID:
	.long -2

.section .text, "ax"
# __init_cpp_exceptions
.global func_800B2288
func_800B2288:
/* 800B2288 000AD188  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800B228C 000AD18C  7C 08 02 A6 */	mflr r0
/* 800B2290 000AD190  90 01 00 14 */	stw r0, 0x14(r1)
/* 800B2294 000AD194  80 0D 81 B0 */	lwz r0, fragmentID-_SDA_BASE_(r13)
/* 800B2298 000AD198  2C 00 FF FE */	cmpwi r0, -2
/* 800B229C 000AD19C  40 82 00 18 */	bne lbl_800B22B4
/* 800B22A0 000AD1A0  3C 60 80 00 */	lis r3, _eti_init_info_@ha
/* 800B22A4 000AD1A4  7C 44 13 78 */	mr r4, r2
/* 800B22A8 000AD1A8  38 63 76 B8 */	addi r3, r3, _eti_init_info_@l
/* 800B22AC 000AD1AC  48 00 00 4D */	bl __register_fragment
/* 800B22B0 000AD1B0  90 6D 81 B0 */	stw r3, fragmentID-_SDA_BASE_(r13)
lbl_800B22B4:
/* 800B22B4 000AD1B4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800B22B8 000AD1B8  7C 08 03 A6 */	mtlr r0
/* 800B22BC 000AD1BC  38 21 00 10 */	addi r1, r1, 0x10
/* 800B22C0 000AD1C0  4E 80 00 20 */	blr 

# __fini_cpp_exceptions
.global func_800B22C4
func_800B22C4:
/* 800B22C4 000AD1C4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800B22C8 000AD1C8  7C 08 02 A6 */	mflr r0
/* 800B22CC 000AD1CC  90 01 00 14 */	stw r0, 0x14(r1)
/* 800B22D0 000AD1D0  80 6D 81 B0 */	lwz r3, fragmentID-_SDA_BASE_(r13)
/* 800B22D4 000AD1D4  2C 03 FF FE */	cmpwi r3, -2
/* 800B22D8 000AD1D8  41 82 00 10 */	beq lbl_800B22E8
/* 800B22DC 000AD1DC  48 00 00 51 */	bl __unregister_fragment
/* 800B22E0 000AD1E0  38 00 FF FE */	li r0, -2
/* 800B22E4 000AD1E4  90 0D 81 B0 */	stw r0, fragmentID-_SDA_BASE_(r13)
lbl_800B22E8:
/* 800B22E8 000AD1E8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800B22EC 000AD1EC  7C 08 03 A6 */	mtlr r0
/* 800B22F0 000AD1F0  38 21 00 10 */	addi r1, r1, 0x10
/* 800B22F4 000AD1F4  4E 80 00 20 */	blr 
