.include "macros.inc"

.section .text, "ax"
.global OSUTF8to32
OSUTF8to32:
/* 800F5CB8 000F0BB8  88 C3 00 00 */	lbz r6, 0(r3)
/* 800F5CBC 000F0BBC  2C 06 00 00 */	cmpwi r6, 0
/* 800F5CC0 000F0BC0  41 82 00 08 */	beq lbl_800F5CC8
/* 800F5CC4 000F0BC4  38 63 00 01 */	addi r3, r3, 1
lbl_800F5CC8:
/* 800F5CC8 000F0BC8  54 C0 06 31 */	rlwinm. r0, r6, 0, 0x18, 0x18
/* 800F5CCC 000F0BCC  40 82 00 0C */	bne lbl_800F5CD8
/* 800F5CD0 000F0BD0  38 E0 00 00 */	li r7, 0
/* 800F5CD4 000F0BD4  48 00 00 54 */	b lbl_800F5D28
lbl_800F5CD8:
/* 800F5CD8 000F0BD8  54 C0 06 34 */	rlwinm r0, r6, 0, 0x18, 0x1a
/* 800F5CDC 000F0BDC  28 00 00 C0 */	cmplwi r0, 0xc0
/* 800F5CE0 000F0BE0  40 82 00 10 */	bne lbl_800F5CF0
/* 800F5CE4 000F0BE4  54 C6 06 FE */	clrlwi r6, r6, 0x1b
/* 800F5CE8 000F0BE8  38 E0 00 01 */	li r7, 1
/* 800F5CEC 000F0BEC  48 00 00 3C */	b lbl_800F5D28
lbl_800F5CF0:
/* 800F5CF0 000F0BF0  54 C0 06 36 */	rlwinm r0, r6, 0, 0x18, 0x1b
/* 800F5CF4 000F0BF4  28 00 00 E0 */	cmplwi r0, 0xe0
/* 800F5CF8 000F0BF8  40 82 00 10 */	bne lbl_800F5D08
/* 800F5CFC 000F0BFC  54 C6 07 3E */	clrlwi r6, r6, 0x1c
/* 800F5D00 000F0C00  38 E0 00 02 */	li r7, 2
/* 800F5D04 000F0C04  48 00 00 24 */	b lbl_800F5D28
lbl_800F5D08:
/* 800F5D08 000F0C08  54 C0 06 38 */	rlwinm r0, r6, 0, 0x18, 0x1c
/* 800F5D0C 000F0C0C  28 00 00 F0 */	cmplwi r0, 0xf0
/* 800F5D10 000F0C10  40 82 00 10 */	bne lbl_800F5D20
/* 800F5D14 000F0C14  54 C6 07 7E */	clrlwi r6, r6, 0x1d
/* 800F5D18 000F0C18  38 E0 00 03 */	li r7, 3
/* 800F5D1C 000F0C1C  48 00 00 0C */	b lbl_800F5D28
lbl_800F5D20:
/* 800F5D20 000F0C20  38 60 00 00 */	li r3, 0
/* 800F5D24 000F0C24  4E 80 00 20 */	blr 
lbl_800F5D28:
/* 800F5D28 000F0C28  7C E9 03 A6 */	mtctr r7
/* 800F5D2C 000F0C2C  28 07 00 00 */	cmplwi r7, 0
/* 800F5D30 000F0C30  40 81 00 30 */	ble lbl_800F5D60
lbl_800F5D34:
/* 800F5D34 000F0C34  88 A3 00 00 */	lbz r5, 0(r3)
/* 800F5D38 000F0C38  54 C6 30 32 */	slwi r6, r6, 6
/* 800F5D3C 000F0C3C  38 63 00 01 */	addi r3, r3, 1
/* 800F5D40 000F0C40  54 A0 06 32 */	rlwinm r0, r5, 0, 0x18, 0x19
/* 800F5D44 000F0C44  28 00 00 80 */	cmplwi r0, 0x80
/* 800F5D48 000F0C48  41 82 00 0C */	beq lbl_800F5D54
/* 800F5D4C 000F0C4C  38 60 00 00 */	li r3, 0
/* 800F5D50 000F0C50  4E 80 00 20 */	blr 
lbl_800F5D54:
/* 800F5D54 000F0C54  54 A0 06 BE */	clrlwi r0, r5, 0x1a
/* 800F5D58 000F0C58  7C C6 03 78 */	or r6, r6, r0
/* 800F5D5C 000F0C5C  42 00 FF D8 */	bdnz lbl_800F5D34
lbl_800F5D60:
/* 800F5D60 000F0C60  28 06 00 7F */	cmplwi r6, 0x7f
/* 800F5D64 000F0C64  41 81 00 14 */	bgt lbl_800F5D78
/* 800F5D68 000F0C68  2C 07 00 00 */	cmpwi r7, 0
/* 800F5D6C 000F0C6C  41 82 00 3C */	beq lbl_800F5DA8
/* 800F5D70 000F0C70  38 60 00 00 */	li r3, 0
/* 800F5D74 000F0C74  4E 80 00 20 */	blr 
lbl_800F5D78:
/* 800F5D78 000F0C78  28 06 07 FF */	cmplwi r6, 0x7ff
/* 800F5D7C 000F0C7C  41 81 00 14 */	bgt lbl_800F5D90
/* 800F5D80 000F0C80  28 07 00 01 */	cmplwi r7, 1
/* 800F5D84 000F0C84  41 82 00 24 */	beq lbl_800F5DA8
/* 800F5D88 000F0C88  38 60 00 00 */	li r3, 0
/* 800F5D8C 000F0C8C  4E 80 00 20 */	blr 
lbl_800F5D90:
/* 800F5D90 000F0C90  28 06 FF FF */	cmplwi r6, 0xffff
/* 800F5D94 000F0C94  41 81 00 14 */	bgt lbl_800F5DA8
/* 800F5D98 000F0C98  28 07 00 02 */	cmplwi r7, 2
/* 800F5D9C 000F0C9C  41 82 00 0C */	beq lbl_800F5DA8
/* 800F5DA0 000F0CA0  38 60 00 00 */	li r3, 0
/* 800F5DA4 000F0CA4  4E 80 00 20 */	blr 
lbl_800F5DA8:
/* 800F5DA8 000F0CA8  28 06 D8 00 */	cmplwi r6, 0xd800
/* 800F5DAC 000F0CAC  41 80 00 14 */	blt lbl_800F5DC0
/* 800F5DB0 000F0CB0  28 06 DF FF */	cmplwi r6, 0xdfff
/* 800F5DB4 000F0CB4  41 81 00 0C */	bgt lbl_800F5DC0
/* 800F5DB8 000F0CB8  38 60 00 00 */	li r3, 0
/* 800F5DBC 000F0CBC  4E 80 00 20 */	blr 
lbl_800F5DC0:
/* 800F5DC0 000F0CC0  90 C4 00 00 */	stw r6, 0(r4)
/* 800F5DC4 000F0CC4  4E 80 00 20 */	blr 

.global OSUTF16to32
OSUTF16to32:
/* 800F5DC8 000F0CC8  A0 A3 00 00 */	lhz r5, 0(r3)
/* 800F5DCC 000F0CCC  2C 05 00 00 */	cmpwi r5, 0
/* 800F5DD0 000F0CD0  41 82 00 08 */	beq lbl_800F5DD8
/* 800F5DD4 000F0CD4  38 63 00 02 */	addi r3, r3, 2
lbl_800F5DD8:
/* 800F5DD8 000F0CD8  28 05 D8 00 */	cmplwi r5, 0xd800
/* 800F5DDC 000F0CDC  41 80 00 0C */	blt lbl_800F5DE8
/* 800F5DE0 000F0CE0  28 05 DF FF */	cmplwi r5, 0xdfff
/* 800F5DE4 000F0CE4  40 81 00 0C */	ble lbl_800F5DF0
lbl_800F5DE8:
/* 800F5DE8 000F0CE8  7C A6 2B 78 */	mr r6, r5
/* 800F5DEC 000F0CEC  48 00 00 44 */	b lbl_800F5E30
lbl_800F5DF0:
/* 800F5DF0 000F0CF0  28 05 DB FF */	cmplwi r5, 0xdbff
/* 800F5DF4 000F0CF4  41 81 00 34 */	bgt lbl_800F5E28
/* 800F5DF8 000F0CF8  A0 03 00 00 */	lhz r0, 0(r3)
/* 800F5DFC 000F0CFC  38 63 00 02 */	addi r3, r3, 2
/* 800F5E00 000F0D00  28 00 DC 00 */	cmplwi r0, 0xdc00
/* 800F5E04 000F0D04  41 80 00 1C */	blt lbl_800F5E20
/* 800F5E08 000F0D08  28 00 DF FF */	cmplwi r0, 0xdfff
/* 800F5E0C 000F0D0C  41 81 00 14 */	bgt lbl_800F5E20
/* 800F5E10 000F0D10  54 06 05 BE */	clrlwi r6, r0, 0x16
/* 800F5E14 000F0D14  50 A6 53 2A */	rlwimi r6, r5, 0xa, 0xc, 0x15
/* 800F5E18 000F0D18  3C C6 00 01 */	addis r6, r6, 1
/* 800F5E1C 000F0D1C  48 00 00 14 */	b lbl_800F5E30
lbl_800F5E20:
/* 800F5E20 000F0D20  38 60 00 00 */	li r3, 0
/* 800F5E24 000F0D24  4E 80 00 20 */	blr 
lbl_800F5E28:
/* 800F5E28 000F0D28  38 60 00 00 */	li r3, 0
/* 800F5E2C 000F0D2C  4E 80 00 20 */	blr 
lbl_800F5E30:
/* 800F5E30 000F0D30  90 C4 00 00 */	stw r6, 0(r4)
/* 800F5E34 000F0D34  4E 80 00 20 */	blr 

.global OSUTF32toANSI
OSUTF32toANSI:
/* 800F5E38 000F0D38  28 03 00 FF */	cmplwi r3, 0xff
/* 800F5E3C 000F0D3C  40 81 00 0C */	ble lbl_800F5E48
/* 800F5E40 000F0D40  38 60 00 00 */	li r3, 0
/* 800F5E44 000F0D44  4E 80 00 20 */	blr 
lbl_800F5E48:
/* 800F5E48 000F0D48  28 03 00 80 */	cmplwi r3, 0x80
/* 800F5E4C 000F0D4C  41 80 00 0C */	blt lbl_800F5E58
/* 800F5E50 000F0D50  28 03 00 9F */	cmplwi r3, 0x9f
/* 800F5E54 000F0D54  40 81 00 0C */	ble lbl_800F5E60
lbl_800F5E58:
/* 800F5E58 000F0D58  54 63 06 3E */	clrlwi r3, r3, 0x18
/* 800F5E5C 000F0D5C  4E 80 00 20 */	blr 
lbl_800F5E60:
/* 800F5E60 000F0D60  28 03 01 52 */	cmplwi r3, 0x152
/* 800F5E64 000F0D64  41 80 00 44 */	blt lbl_800F5EA8
/* 800F5E68 000F0D68  28 03 21 22 */	cmplwi r3, 0x2122
/* 800F5E6C 000F0D6C  41 81 00 3C */	bgt lbl_800F5EA8
/* 800F5E70 000F0D70  3C 80 80 3A */	lis r4, UcsAnsiTable@ha
/* 800F5E74 000F0D74  38 00 00 20 */	li r0, 0x20
/* 800F5E78 000F0D78  38 84 D2 D0 */	addi r4, r4, UcsAnsiTable@l
/* 800F5E7C 000F0D7C  38 A0 00 00 */	li r5, 0
/* 800F5E80 000F0D80  7C 09 03 A6 */	mtctr r0
lbl_800F5E84:
/* 800F5E84 000F0D84  A0 04 00 00 */	lhz r0, 0(r4)
/* 800F5E88 000F0D88  7C 03 00 40 */	cmplw r3, r0
/* 800F5E8C 000F0D8C  40 82 00 10 */	bne lbl_800F5E9C
/* 800F5E90 000F0D90  38 05 00 80 */	addi r0, r5, 0x80
/* 800F5E94 000F0D94  54 03 06 3E */	clrlwi r3, r0, 0x18
/* 800F5E98 000F0D98  4E 80 00 20 */	blr 
lbl_800F5E9C:
/* 800F5E9C 000F0D9C  38 84 00 02 */	addi r4, r4, 2
/* 800F5EA0 000F0DA0  38 A5 00 01 */	addi r5, r5, 1
/* 800F5EA4 000F0DA4  42 00 FF E0 */	bdnz lbl_800F5E84
lbl_800F5EA8:
/* 800F5EA8 000F0DA8  38 60 00 00 */	li r3, 0
/* 800F5EAC 000F0DAC  4E 80 00 20 */	blr 

.global OSUTF32toSJIS
OSUTF32toSJIS:
/* 800F5EB0 000F0DB0  3C 00 00 01 */	lis r0, 1
/* 800F5EB4 000F0DB4  7C 03 00 40 */	cmplw r3, r0
/* 800F5EB8 000F0DB8  41 80 00 0C */	blt lbl_800F5EC4
/* 800F5EBC 000F0DBC  38 60 00 00 */	li r3, 0
/* 800F5EC0 000F0DC0  4E 80 00 20 */	blr 
lbl_800F5EC4:
/* 800F5EC4 000F0DC4  3C 80 80 3B */	lis r4, UcsSjisTable@ha
/* 800F5EC8 000F0DC8  54 60 D5 BA */	rlwinm r0, r3, 0x1a, 0x16, 0x1d
/* 800F5ECC 000F0DCC  38 84 8D 10 */	addi r4, r4, UcsSjisTable@l
/* 800F5ED0 000F0DD0  7C 84 00 2E */	lwzx r4, r4, r0
/* 800F5ED4 000F0DD4  2C 04 00 00 */	cmpwi r4, 0
/* 800F5ED8 000F0DD8  41 82 00 10 */	beq lbl_800F5EE8
/* 800F5EDC 000F0DDC  54 60 0D FC */	rlwinm r0, r3, 1, 0x17, 0x1e
/* 800F5EE0 000F0DE0  7C 64 02 2E */	lhzx r3, r4, r0
/* 800F5EE4 000F0DE4  4E 80 00 20 */	blr 
lbl_800F5EE8:
/* 800F5EE8 000F0DE8  38 60 00 00 */	li r3, 0
/* 800F5EEC 000F0DEC  4E 80 00 20 */	blr 


.section .data, "wa"
.balign 0x8
UcsAnsiTable:
	.incbin "baserom.dol", 0x3993D0, 0x40
    
Ucs00:
	.incbin "baserom.dol", 0x399410, 0x200
Ucs03:
	.incbin "baserom.dol", 0x399610, 0x200
Ucs04:
	.incbin "baserom.dol", 0x399810, 0x200
Ucs20:
	.incbin "baserom.dol", 0x399a10, 0x200
Ucs21:
	.incbin "baserom.dol", 0x399c10, 0x200
Ucs22:
	.incbin "baserom.dol", 0x399e10, 0x200
Ucs23:
	.incbin "baserom.dol", 0x39a010, 0x200
Ucs25:
	.incbin "baserom.dol", 0x39a210, 0x200
Ucs26:
	.incbin "baserom.dol", 0x39a410, 0x200
Ucs30:
	.incbin "baserom.dol", 0x39a610, 0x200
Ucs4E:
	.incbin "baserom.dol", 0x39a810, 0x200
Ucs4F:
	.incbin "baserom.dol", 0x39aa10, 0x200
Ucs50:
	.incbin "baserom.dol", 0x39ac10, 0x200
Ucs51:
	.incbin "baserom.dol", 0x39ae10, 0x200
Ucs52:
	.incbin "baserom.dol", 0x39b010, 0x200
Ucs53:
	.incbin "baserom.dol", 0x39b210, 0x200
Ucs54:
	.incbin "baserom.dol", 0x39b410, 0x200
Ucs55:
	.incbin "baserom.dol", 0x39b610, 0x200
Ucs56:
	.incbin "baserom.dol", 0x39b810, 0x200
Ucs57:
	.incbin "baserom.dol", 0x39ba10, 0x200
Ucs58:
	.incbin "baserom.dol", 0x39bc10, 0x200
Ucs59:
	.incbin "baserom.dol", 0x39be10, 0x200
Ucs5A:
	.incbin "baserom.dol", 0x39c010, 0x200
Ucs5B:
	.incbin "baserom.dol", 0x39c210, 0x200
Ucs5C:
	.incbin "baserom.dol", 0x39c410, 0x200
Ucs5D:
	.incbin "baserom.dol", 0x39c610, 0x200
Ucs5E:
	.incbin "baserom.dol", 0x39c810, 0x200
Ucs5F:
	.incbin "baserom.dol", 0x39ca10, 0x200
Ucs60:
	.incbin "baserom.dol", 0x39cc10, 0x200
Ucs61:
	.incbin "baserom.dol", 0x39ce10, 0x200
Ucs62:
	.incbin "baserom.dol", 0x39d010, 0x200
Ucs63:
	.incbin "baserom.dol", 0x39d210, 0x200
Ucs64:
	.incbin "baserom.dol", 0x39d410, 0x200
Ucs65:
	.incbin "baserom.dol", 0x39d610, 0x200
Ucs66:
	.incbin "baserom.dol", 0x39d810, 0x200
Ucs67:
	.incbin "baserom.dol", 0x39da10, 0x200
Ucs68:
	.incbin "baserom.dol", 0x39dc10, 0x200
Ucs69:
	.incbin "baserom.dol", 0x39de10, 0x200
Ucs6A:
	.incbin "baserom.dol", 0x39e010, 0x200
Ucs6B:
	.incbin "baserom.dol", 0x39e210, 0x200
Ucs6C:
	.incbin "baserom.dol", 0x39e410, 0x200
Ucs6D:
	.incbin "baserom.dol", 0x39e610, 0x200
Ucs6E:
	.incbin "baserom.dol", 0x39e810, 0x200
Ucs6F:
	.incbin "baserom.dol", 0x39ea10, 0x200
Ucs70:
	.incbin "baserom.dol", 0x39ec10, 0x200
Ucs71:
	.incbin "baserom.dol", 0x39ee10, 0x200
Ucs72:
	.incbin "baserom.dol", 0x39f010, 0x200
Ucs73:
	.incbin "baserom.dol", 0x39f210, 0x200
Ucs74:
	.incbin "baserom.dol", 0x39f410, 0x200
Ucs75:
	.incbin "baserom.dol", 0x39f610, 0x200
Ucs76:
	.incbin "baserom.dol", 0x39f810, 0x200
Ucs77:
	.incbin "baserom.dol", 0x39fa10, 0x200
Ucs78:
	.incbin "baserom.dol", 0x39fc10, 0x200
Ucs79:
	.incbin "baserom.dol", 0x39fe10, 0x200
Ucs7A:
	.incbin "baserom.dol", 0x3a0010, 0x200
Ucs7B:
	.incbin "baserom.dol", 0x3a0210, 0x200
Ucs7C:
	.incbin "baserom.dol", 0x3a0410, 0x200
Ucs7D:
	.incbin "baserom.dol", 0x3a0610, 0x200
Ucs7E:
	.incbin "baserom.dol", 0x3a0810, 0x200
Ucs7F:
	.incbin "baserom.dol", 0x3a0a10, 0x200
Ucs80:
	.incbin "baserom.dol", 0x3a0c10, 0x200
Ucs81:
	.incbin "baserom.dol", 0x3a0e10, 0x200
Ucs82:
	.incbin "baserom.dol", 0x3a1010, 0x200
Ucs83:
	.incbin "baserom.dol", 0x3a1210, 0x200
Ucs84:
	.incbin "baserom.dol", 0x3a1410, 0x200
Ucs85:
	.incbin "baserom.dol", 0x3a1610, 0x200
Ucs86:
	.incbin "baserom.dol", 0x3a1810, 0x200
Ucs87:
	.incbin "baserom.dol", 0x3a1a10, 0x200
Ucs88:
	.incbin "baserom.dol", 0x3a1c10, 0x200
Ucs89:
	.incbin "baserom.dol", 0x3a1e10, 0x200
Ucs8A:
	.incbin "baserom.dol", 0x3a2010, 0x200
Ucs8B:
	.incbin "baserom.dol", 0x3a2210, 0x200
Ucs8C:
	.incbin "baserom.dol", 0x3a2410, 0x200
Ucs8D:
	.incbin "baserom.dol", 0x3a2610, 0x200
Ucs8E:
	.incbin "baserom.dol", 0x3a2810, 0x200
Ucs8F:
	.incbin "baserom.dol", 0x3a2a10, 0x200
Ucs90:
	.incbin "baserom.dol", 0x3a2c10, 0x200
Ucs91:
	.incbin "baserom.dol", 0x3a2e10, 0x200
Ucs92:
	.incbin "baserom.dol", 0x3a3010, 0x200
Ucs93:
	.incbin "baserom.dol", 0x3a3210, 0x200
Ucs94:
	.incbin "baserom.dol", 0x3a3410, 0x200
Ucs95:
	.incbin "baserom.dol", 0x3a3610, 0x200
Ucs96:
	.incbin "baserom.dol", 0x3a3810, 0x200
Ucs97:
	.incbin "baserom.dol", 0x3a3a10, 0x200
Ucs98:
	.incbin "baserom.dol", 0x3a3c10, 0x200
Ucs99:
	.incbin "baserom.dol", 0x3a3e10, 0x200
Ucs9A:
	.incbin "baserom.dol", 0x3a4010, 0x200
Ucs9B:
	.incbin "baserom.dol", 0x3a4210, 0x200
Ucs9C:
	.incbin "baserom.dol", 0x3a4410, 0x200
Ucs9D:
	.incbin "baserom.dol", 0x3a4610, 0x200
Ucs9E:
	.incbin "baserom.dol", 0x3a4810, 0x200
Ucs9F:
	.incbin "baserom.dol", 0x3a4a10, 0x200
UcsFF:
	.incbin "baserom.dol", 0x3a4c10, 0x200

UcsSjisTable:
    .long Ucs00
    .long 0
    .long 0
    .long Ucs03
    .long Ucs04
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long Ucs20
    .long Ucs21
    .long Ucs22
    .long Ucs23
    .long 0
    .long Ucs25
    .long Ucs26
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long Ucs30
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long Ucs4E
    .long Ucs4F
    .long Ucs50
    .long Ucs51
    .long Ucs52
    .long Ucs53
    .long Ucs54
    .long Ucs55
    .long Ucs56
    .long Ucs57
    .long Ucs58
    .long Ucs59
    .long Ucs5A
    .long Ucs5B
    .long Ucs5C
    .long Ucs5D
    .long Ucs5E
    .long Ucs5F
    .long Ucs60
    .long Ucs61
    .long Ucs62
    .long Ucs63
    .long Ucs64
    .long Ucs65
    .long Ucs66
    .long Ucs67
    .long Ucs68
    .long Ucs69
    .long Ucs6A
    .long Ucs6B
    .long Ucs6C
    .long Ucs6D
    .long Ucs6E
    .long Ucs6F
    .long Ucs70
    .long Ucs71
    .long Ucs72
    .long Ucs73
    .long Ucs74
    .long Ucs75
    .long Ucs76
    .long Ucs77
    .long Ucs78
    .long Ucs79
    .long Ucs7A
    .long Ucs7B
    .long Ucs7C
    .long Ucs7D
    .long Ucs7E
    .long Ucs7F
    .long Ucs80
    .long Ucs81
    .long Ucs82
    .long Ucs83
    .long Ucs84
    .long Ucs85
    .long Ucs86
    .long Ucs87
    .long Ucs88
    .long Ucs89
    .long Ucs8A
    .long Ucs8B
    .long Ucs8C
    .long Ucs8D
    .long Ucs8E
    .long Ucs8F
    .long Ucs90
    .long Ucs91
    .long Ucs92
    .long Ucs93
    .long Ucs94
    .long Ucs95
    .long Ucs96
    .long Ucs97
    .long Ucs98
    .long Ucs99
    .long Ucs9A
    .long Ucs9B
    .long Ucs9C
    .long Ucs9D
    .long Ucs9E
    .long Ucs9F
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long 0
    .long UcsFF
