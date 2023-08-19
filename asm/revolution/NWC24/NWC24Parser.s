.include "macros.inc"

.section .data, "wa"
.balign 0x8
lbl_803b78d8:
	.incbin "baserom.dol", 0x3B39D8, 0xD0
MIMETypeStr:
	.incbin "baserom.dol", 0x3B3AA8, 0x28
MIMETypeConv:
	.incbin "baserom.dol", 0x3B3AD0, 0x28
MIMETypeSuffix:
	.incbin "baserom.dol", 0x3B3AF8, 0x28
lbl_803b7a20:
	.incbin "baserom.dol", 0x3B3B20, 0xB0
CharsetStr:
	.incbin "baserom.dol", 0x3B3BD0, 0x40
CharsetConv:
	.incbin "baserom.dol", 0x3B3C10, 0x40
lbl_803b7b4f:
	.incbin "baserom.dol", 0x3B3C50, 0x18
EncodingStr:
	.incbin "baserom.dol", 0x3B3C68, 0x10
EncodingConv:
	.incbin "baserom.dol", 0x3B3C78, 0x10

.section .text, "ax"
.global NWC24GetMIMETypeStr
NWC24GetMIMETypeStr:
/* 80146EB4 00141DB4  3C 80 80 3B */	lis r4, MIMETypeConv@ha
/* 80146EB8 00141DB8  38 00 00 0A */	li r0, 0xa
/* 80146EBC 00141DBC  38 84 79 D0 */	addi r4, r4, MIMETypeConv@l
/* 80146EC0 00141DC0  38 A0 00 00 */	li r5, 0
/* 80146EC4 00141DC4  7C 09 03 A6 */	mtctr r0
lbl_80146EC8:
/* 80146EC8 00141DC8  80 04 00 00 */	lwz r0, 0(r4)
/* 80146ECC 00141DCC  7C 03 00 00 */	cmpw r3, r0
/* 80146ED0 00141DD0  40 82 00 18 */	bne lbl_80146EE8
/* 80146ED4 00141DD4  3C 60 80 3B */	lis r3, MIMETypeStr@ha
/* 80146ED8 00141DD8  54 A0 10 3A */	slwi r0, r5, 2
/* 80146EDC 00141DDC  38 63 79 A8 */	addi r3, r3, MIMETypeStr@l
/* 80146EE0 00141DE0  7C 63 00 2E */	lwzx r3, r3, r0
/* 80146EE4 00141DE4  4E 80 00 20 */	blr 
lbl_80146EE8:
/* 80146EE8 00141DE8  38 84 00 04 */	addi r4, r4, 4
/* 80146EEC 00141DEC  38 A5 00 01 */	addi r5, r5, 1
/* 80146EF0 00141DF0  42 00 FF D8 */	bdnz lbl_80146EC8
/* 80146EF4 00141DF4  38 60 00 00 */	li r3, 0
/* 80146EF8 00141DF8  4E 80 00 20 */	blr 

.global NWC24iGetMIMETypeSuffix
NWC24iGetMIMETypeSuffix:
/* 80146EFC 00141DFC  3C 80 80 3B */	lis r4, MIMETypeConv@ha
/* 80146F00 00141E00  38 00 00 0A */	li r0, 0xa
/* 80146F04 00141E04  38 84 79 D0 */	addi r4, r4, MIMETypeConv@l
/* 80146F08 00141E08  38 A0 00 00 */	li r5, 0
/* 80146F0C 00141E0C  7C 09 03 A6 */	mtctr r0
lbl_80146F10:
/* 80146F10 00141E10  80 04 00 00 */	lwz r0, 0(r4)
/* 80146F14 00141E14  7C 03 00 00 */	cmpw r3, r0
/* 80146F18 00141E18  40 82 00 18 */	bne lbl_80146F30
/* 80146F1C 00141E1C  3C 60 80 3B */	lis r3, MIMETypeSuffix@ha
/* 80146F20 00141E20  54 A0 10 3A */	slwi r0, r5, 2
/* 80146F24 00141E24  38 63 79 F8 */	addi r3, r3, MIMETypeSuffix@l
/* 80146F28 00141E28  7C 63 00 2E */	lwzx r3, r3, r0
/* 80146F2C 00141E2C  4E 80 00 20 */	blr 
lbl_80146F30:
/* 80146F30 00141E30  38 84 00 04 */	addi r4, r4, 4
/* 80146F34 00141E34  38 A5 00 01 */	addi r5, r5, 1
/* 80146F38 00141E38  42 00 FF D8 */	bdnz lbl_80146F10
/* 80146F3C 00141E3C  38 60 00 00 */	li r3, 0
/* 80146F40 00141E40  4E 80 00 20 */	blr 

.global NWC24GetCharsetStr
NWC24GetCharsetStr:
/* 80146F44 00141E44  3C 80 80 3B */	lis r4, CharsetConv@ha
/* 80146F48 00141E48  38 00 00 10 */	li r0, 0x10
/* 80146F4C 00141E4C  38 84 7B 10 */	addi r4, r4, CharsetConv@l
/* 80146F50 00141E50  38 A0 00 00 */	li r5, 0
/* 80146F54 00141E54  7C 09 03 A6 */	mtctr r0
lbl_80146F58:
/* 80146F58 00141E58  80 04 00 00 */	lwz r0, 0(r4)
/* 80146F5C 00141E5C  7C 03 00 00 */	cmpw r3, r0
/* 80146F60 00141E60  40 82 00 18 */	bne lbl_80146F78
/* 80146F64 00141E64  3C 60 80 3B */	lis r3, CharsetStr@ha
/* 80146F68 00141E68  54 A0 10 3A */	slwi r0, r5, 2
/* 80146F6C 00141E6C  38 63 7A D0 */	addi r3, r3, CharsetStr@l
/* 80146F70 00141E70  7C 63 00 2E */	lwzx r3, r3, r0
/* 80146F74 00141E74  4E 80 00 20 */	blr 
lbl_80146F78:
/* 80146F78 00141E78  38 84 00 04 */	addi r4, r4, 4
/* 80146F7C 00141E7C  38 A5 00 01 */	addi r5, r5, 1
/* 80146F80 00141E80  42 00 FF D8 */	bdnz lbl_80146F58
/* 80146F84 00141E84  38 60 00 00 */	li r3, 0
/* 80146F88 00141E88  4E 80 00 20 */	blr 

.global NWC24GetEncodingStr
NWC24GetEncodingStr:
/* 80146F8C 00141E8C  3C 80 80 3B */	lis r4, EncodingConv@ha
/* 80146F90 00141E90  38 00 00 04 */	li r0, 4
/* 80146F94 00141E94  38 84 7B 78 */	addi r4, r4, EncodingConv@l
/* 80146F98 00141E98  38 A0 00 00 */	li r5, 0
/* 80146F9C 00141E9C  7C 09 03 A6 */	mtctr r0
lbl_80146FA0:
/* 80146FA0 00141EA0  80 04 00 00 */	lwz r0, 0(r4)
/* 80146FA4 00141EA4  7C 03 00 00 */	cmpw r3, r0
/* 80146FA8 00141EA8  40 82 00 18 */	bne lbl_80146FC0
/* 80146FAC 00141EAC  3C 60 80 3B */	lis r3, EncodingStr@ha
/* 80146FB0 00141EB0  54 A0 10 3A */	slwi r0, r5, 2
/* 80146FB4 00141EB4  38 63 7B 68 */	addi r3, r3, EncodingStr@l
/* 80146FB8 00141EB8  7C 63 00 2E */	lwzx r3, r3, r0
/* 80146FBC 00141EBC  4E 80 00 20 */	blr 
lbl_80146FC0:
/* 80146FC0 00141EC0  38 84 00 04 */	addi r4, r4, 4
/* 80146FC4 00141EC4  38 A5 00 01 */	addi r5, r5, 1
/* 80146FC8 00141EC8  42 00 FF D8 */	bdnz lbl_80146FA0
/* 80146FCC 00141ECC  38 60 00 00 */	li r3, 0
/* 80146FD0 00141ED0  4E 80 00 20 */	blr 
