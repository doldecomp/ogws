.include "macros.inc"

.section .data, "wa"
.global __vt__Q34nw4r3lyt8Bounding
__vt__Q34nw4r3lyt8Bounding:
    .long 0
    .long 0
    .long __dt__Q34nw4r3lyt8BoundingFv
    .long GetRuntimeTypeInfo__Q34nw4r3lyt8BoundingCFv
    .long CalculateMtx__Q34nw4r3lyt4PaneFRCQ34nw4r3lyt8DrawInfo
    .long Draw__Q34nw4r3lyt4PaneFRCQ34nw4r3lyt8DrawInfo
    .long DrawSelf__Q34nw4r3lyt8BoundingFRCQ34nw4r3lyt8DrawInfo
    .long Animate__Q34nw4r3lyt4PaneFUl
    .long AnimateSelf__Q34nw4r3lyt4PaneFUl
    .long GetVtxColor__Q34nw4r3lyt4PaneCFUl
    .long SetVtxColor__Q34nw4r3lyt4PaneFUlQ34nw4r2ut5Color
    .long GetColorElement__Q34nw4r3lyt4PaneCFUl
    .long SetColorElement__Q34nw4r3lyt4PaneFUlUc
    .long GetVtxColorElement__Q34nw4r3lyt4PaneCFUl
    .long SetVtxColorElement__Q34nw4r3lyt4PaneFUlUc
    .long FindPaneByName__Q34nw4r3lyt4PaneFPCcb
    .long FindMaterialByName__Q34nw4r3lyt4PaneFPCcb
    .long BindAnimation__Q34nw4r3lyt4PaneFPQ34nw4r3lyt13AnimTransformb
    .long UnbindAnimation__Q34nw4r3lyt4PaneFPQ34nw4r3lyt13AnimTransformb
    .long UnbindAllAnimation__Q34nw4r3lyt4PaneFb
    .long UnbindAnimationSelf__Q34nw4r3lyt4PaneFPQ34nw4r3lyt13AnimTransform
    .long FindAnimationLink__Q34nw4r3lyt4PaneFPQ34nw4r3lyt13AnimTransform
    .long SetAnimationEnable__Q34nw4r3lyt4PaneFPQ34nw4r3lyt13AnimTransformbb
    .long GetMaterial__Q34nw4r3lyt4PaneCFv
    .long LoadMtx__Q34nw4r3lyt4PaneFRCQ34nw4r3lyt8DrawInfo
    .long 0

.section .text, "ax"
.global __ct__Q34nw4r3lyt8BoundingFPCQ44nw4r3lyt3res8BoundingRCQ34nw4r3lyt11ResBlockSet
__ct__Q34nw4r3lyt8BoundingFPCQ44nw4r3lyt3res8BoundingRCQ34nw4r3lyt11ResBlockSet:
/* 8007E99C 0007989C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8007E9A0 000798A0  7C 08 02 A6 */	mflr r0
/* 8007E9A4 000798A4  90 01 00 14 */	stw r0, 0x14(r1)
/* 8007E9A8 000798A8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8007E9AC 000798AC  7C 7F 1B 78 */	mr r31, r3
/* 8007E9B0 000798B0  4B FF A9 6D */	bl __ct__Q34nw4r3lyt4PaneFPCQ44nw4r3lyt3res4Pane
/* 8007E9B4 000798B4  3C 80 80 39 */	lis r4, __vt__Q34nw4r3lyt8Bounding@ha
/* 8007E9B8 000798B8  7F E3 FB 78 */	mr r3, r31
/* 8007E9BC 000798BC  38 84 73 D0 */	addi r4, r4, __vt__Q34nw4r3lyt8Bounding@l
/* 8007E9C0 000798C0  90 9F 00 00 */	stw r4, 0(r31)
/* 8007E9C4 000798C4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8007E9C8 000798C8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8007E9CC 000798CC  7C 08 03 A6 */	mtlr r0
/* 8007E9D0 000798D0  38 21 00 10 */	addi r1, r1, 0x10
/* 8007E9D4 000798D4  4E 80 00 20 */	blr 

.global __dt__Q34nw4r3lyt8BoundingFv
__dt__Q34nw4r3lyt8BoundingFv:
/* 8007E9D8 000798D8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8007E9DC 000798DC  7C 08 02 A6 */	mflr r0
/* 8007E9E0 000798E0  2C 03 00 00 */	cmpwi r3, 0
/* 8007E9E4 000798E4  90 01 00 14 */	stw r0, 0x14(r1)
/* 8007E9E8 000798E8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8007E9EC 000798EC  7C 9F 23 78 */	mr r31, r4
/* 8007E9F0 000798F0  93 C1 00 08 */	stw r30, 8(r1)
/* 8007E9F4 000798F4  7C 7E 1B 78 */	mr r30, r3
/* 8007E9F8 000798F8  41 82 00 1C */	beq lbl_8007EA14
/* 8007E9FC 000798FC  38 80 00 00 */	li r4, 0
/* 8007EA00 00079900  4B FF AA 51 */	bl __dt__Q34nw4r3lyt4PaneFv
/* 8007EA04 00079904  2C 1F 00 00 */	cmpwi r31, 0
/* 8007EA08 00079908  40 81 00 0C */	ble lbl_8007EA14
/* 8007EA0C 0007990C  7F C3 F3 78 */	mr r3, r30
/* 8007EA10 00079910  48 02 48 75 */	bl __dl__FPv
lbl_8007EA14:
/* 8007EA14 00079914  7F C3 F3 78 */	mr r3, r30
/* 8007EA18 00079918  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8007EA1C 0007991C  83 C1 00 08 */	lwz r30, 8(r1)
/* 8007EA20 00079920  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8007EA24 00079924  7C 08 03 A6 */	mtlr r0
/* 8007EA28 00079928  38 21 00 10 */	addi r1, r1, 0x10
/* 8007EA2C 0007992C  4E 80 00 20 */	blr 

.global DrawSelf__Q34nw4r3lyt8BoundingFRCQ34nw4r3lyt8DrawInfo
DrawSelf__Q34nw4r3lyt8BoundingFRCQ34nw4r3lyt8DrawInfo:
/* 8007EA30 00079930  4E 80 00 20 */	blr 

.global GetRuntimeTypeInfo__Q34nw4r3lyt8BoundingCFv
GetRuntimeTypeInfo__Q34nw4r3lyt8BoundingCFv:
/* 8007EA34 00079934  38 6D 98 20 */	addi r3, r13, lbl_804BEBA0-_SDA_BASE_
/* 8007EA38 00079938  4E 80 00 20 */	blr 

# __sinit_\lyt_bounding_cpp
.global __sinit_$$3lyt_bounding_cpp
__sinit_$$3lyt_bounding_cpp:
/* 8007EA3C 0007993C  38 0D 97 F8 */	addi r0, r13, lbl_804BEB78-_SDA_BASE_
/* 8007EA40 00079940  90 0D 98 20 */	stw r0, lbl_804BEBA0-_SDA_BASE_(r13)
/* 8007EA44 00079944  4E 80 00 20 */	blr 
