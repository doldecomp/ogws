.include "macros.inc"

.section .sdata2, "a"
.balign 0x8
sAllocatorFunc$733:
	.long AllocatorAllocForExpHeap_
	.long AllocatorFreeForExpHeap_
sAllocatorFunc$741:
	.long AllocatorAllocForFrmHeap_
	.long AllocatorFreeForFrmHeap_

.section .text, "ax"
.global AllocatorAllocForExpHeap_
AllocatorAllocForExpHeap_:
/* 800E7460 000E2360  7C 65 1B 78 */	mr r5, r3
/* 800E7464 000E2364  80 63 00 04 */	lwz r3, 4(r3)
/* 800E7468 000E2368  80 A5 00 08 */	lwz r5, 8(r5)
/* 800E746C 000E236C  4B FF F5 14 */	b MEMAllocFromExpHeapEx

.global AllocatorFreeForExpHeap_
AllocatorFreeForExpHeap_:
/* 800E7470 000E2370  80 63 00 04 */	lwz r3, 4(r3)
/* 800E7474 000E2374  4B FF F7 A8 */	b MEMFreeToExpHeap

.global AllocatorAllocForFrmHeap_
AllocatorAllocForFrmHeap_:
/* 800E7478 000E2378  7C 65 1B 78 */	mr r5, r3
/* 800E747C 000E237C  80 63 00 04 */	lwz r3, 4(r3)
/* 800E7480 000E2380  80 A5 00 08 */	lwz r5, 8(r5)
/* 800E7484 000E2384  4B FF FA C8 */	b MEMAllocFromFrmHeapEx

.global AllocatorFreeForFrmHeap_
AllocatorFreeForFrmHeap_:
/* 800E7488 000E2388  4E 80 00 20 */	blr 

.global MEMAllocFromAllocator
MEMAllocFromAllocator:
/* 800E748C 000E238C  80 A3 00 00 */	lwz r5, 0(r3)
/* 800E7490 000E2390  81 85 00 00 */	lwz r12, 0(r5)
/* 800E7494 000E2394  7D 89 03 A6 */	mtctr r12
/* 800E7498 000E2398  4E 80 04 20 */	bctr 

.global MEMFreeToAllocator
MEMFreeToAllocator:
/* 800E749C 000E239C  80 A3 00 00 */	lwz r5, 0(r3)
/* 800E74A0 000E23A0  81 85 00 04 */	lwz r12, 4(r5)
/* 800E74A4 000E23A4  7D 89 03 A6 */	mtctr r12
/* 800E74A8 000E23A8  4E 80 04 20 */	bctr 

.global MEMInitAllocatorForExpHeap
MEMInitAllocatorForExpHeap:
/* 800E74AC 000E23AC  38 C2 97 90 */	addi r6, r2, sAllocatorFunc$733-_SDA2_BASE_
/* 800E74B0 000E23B0  38 00 00 00 */	li r0, 0
/* 800E74B4 000E23B4  90 C3 00 00 */	stw r6, 0(r3)
/* 800E74B8 000E23B8  90 83 00 04 */	stw r4, 4(r3)
/* 800E74BC 000E23BC  90 A3 00 08 */	stw r5, 8(r3)
/* 800E74C0 000E23C0  90 03 00 0C */	stw r0, 0xc(r3)
/* 800E74C4 000E23C4  4E 80 00 20 */	blr 

.global MEMInitAllocatorForFrmHeap
MEMInitAllocatorForFrmHeap:
/* 800E74C8 000E23C8  38 C2 97 98 */	addi r6, r2, sAllocatorFunc$741-_SDA2_BASE_
/* 800E74CC 000E23CC  38 00 00 00 */	li r0, 0
/* 800E74D0 000E23D0  90 C3 00 00 */	stw r6, 0(r3)
/* 800E74D4 000E23D4  90 83 00 04 */	stw r4, 4(r3)
/* 800E74D8 000E23D8  90 A3 00 08 */	stw r5, 8(r3)
/* 800E74DC 000E23DC  90 03 00 0C */	stw r0, 0xc(r3)
/* 800E74E0 000E23E0  4E 80 00 20 */	blr 
