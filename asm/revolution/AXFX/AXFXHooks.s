.include "macros.inc"

.section .sdata, "wa"
.balign 0x8
.global __AXFXAlloc
__AXFXAlloc:
	.long __AXFXAllocFunction
.global __AXFXFree
__AXFXFree:
	.long __AXFXFreeFunction

.section .text, "ax"
__AXFXAllocFunction:
/* 8010A9E0 001058E0  7C 64 1B 78 */	mr r4, r3
/* 8010A9E4 001058E4  80 6D 83 60 */	lwz r3, __OSCurrHeap-_SDA_BASE_(r13)
/* 8010A9E8 001058E8  4B FE 2F 64 */	b OSAllocFromHeap

__AXFXFreeFunction:
/* 8010A9EC 001058EC  7C 64 1B 78 */	mr r4, r3
/* 8010A9F0 001058F0  80 6D 83 60 */	lwz r3, __OSCurrHeap-_SDA_BASE_(r13)
/* 8010A9F4 001058F4  4B FE 30 50 */	b OSFreeToHeap

.global AXFXSetHooks
AXFXSetHooks:
/* 8010A9F8 001058F8  90 6D 85 28 */	stw r3, __AXFXAlloc-_SDA_BASE_(r13)
/* 8010A9FC 001058FC  90 8D 85 2C */	stw r4, __AXFXFree-_SDA_BASE_(r13)
/* 8010AA00 00105900  4E 80 00 20 */	blr 

.global AXFXGetHooks
AXFXGetHooks:
/* 8010AA04 00105904  80 0D 85 28 */	lwz r0, __AXFXAlloc-_SDA_BASE_(r13)
/* 8010AA08 00105908  90 03 00 00 */	stw r0, 0(r3)
/* 8010AA0C 0010590C  80 0D 85 2C */	lwz r0, __AXFXFree-_SDA_BASE_(r13)
/* 8010AA10 00105910  90 04 00 00 */	stw r0, 0(r4)
/* 8010AA14 00105914  4E 80 00 20 */	blr 
