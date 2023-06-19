.include "macros.inc"

.section .sbss, "wa"
.balign 0x8
.global __global_destructor_chain
__global_destructor_chain:
	.skip 0x4

.section .text, "ax"
# __register_global_object
.global func_800B1834
func_800B1834:
/* 800B1834 000AC734  80 0D 99 D8 */	lwz r0, __global_destructor_chain-_SDA_BASE_(r13)
/* 800B1838 000AC738  90 05 00 00 */	stw r0, 0(r5)
/* 800B183C 000AC73C  90 85 00 04 */	stw r4, 4(r5)
/* 800B1840 000AC740  90 65 00 08 */	stw r3, 8(r5)
/* 800B1844 000AC744  90 AD 99 D8 */	stw r5, __global_destructor_chain-_SDA_BASE_(r13)
/* 800B1848 000AC748  4E 80 00 20 */	blr 

# __destroy_global_chain
.global func_800B184C
func_800B184C:
/* 800B184C 000AC74C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800B1850 000AC750  7C 08 02 A6 */	mflr r0
/* 800B1854 000AC754  90 01 00 14 */	stw r0, 0x14(r1)
/* 800B1858 000AC758  48 00 00 20 */	b lbl_800B1878
lbl_800B185C:
/* 800B185C 000AC75C  80 03 00 00 */	lwz r0, 0(r3)
/* 800B1860 000AC760  38 80 FF FF */	li r4, -1
/* 800B1864 000AC764  90 0D 99 D8 */	stw r0, __global_destructor_chain-_SDA_BASE_(r13)
/* 800B1868 000AC768  81 83 00 04 */	lwz r12, 4(r3)
/* 800B186C 000AC76C  80 63 00 08 */	lwz r3, 8(r3)
/* 800B1870 000AC770  7D 89 03 A6 */	mtctr r12
/* 800B1874 000AC774  4E 80 04 21 */	bctrl 
lbl_800B1878:
/* 800B1878 000AC778  80 6D 99 D8 */	lwz r3, __global_destructor_chain-_SDA_BASE_(r13)
/* 800B187C 000AC77C  2C 03 00 00 */	cmpwi r3, 0
/* 800B1880 000AC780  40 82 FF DC */	bne lbl_800B185C
/* 800B1884 000AC784  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800B1888 000AC788  7C 08 03 A6 */	mtlr r0
/* 800B188C 000AC78C  38 21 00 10 */	addi r1, r1, 0x10
/* 800B1890 000AC790  4E 80 00 20 */	blr 
