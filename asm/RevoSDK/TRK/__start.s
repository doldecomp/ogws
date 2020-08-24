.include "macros.inc"

.section .init, "ax"  # 0x80004000 - 0x800064E0

.global __check_pad3
__check_pad3:
/* 800060E8 000021E8  3C 60 80 00 */	lis r3, 0x800030E4@ha
/* 800060EC 000021EC  A0 03 30 E4 */	lhz r0, 0x800030E4@l(r3)
/* 800060F0 000021F0  70 00 0E EF */	andi. r0, r0, 0xeef
/* 800060F4 000021F4  2C 00 0E EF */	cmpwi r0, 0xeef
/* 800060F8 000021F8  4C 82 00 20 */	bnelr 
/* 800060FC 000021FC  38 60 00 00 */	li r3, 0
/* 80006100 00002200  38 80 00 00 */	li r4, 0
/* 80006104 00002204  38 A0 00 00 */	li r5, 0
/* 80006108 00002208  48 0E D2 20 */	b func_800F3328
/* 8000610C 0000220C  4E 80 00 20 */	blr 

.global __set_debug_bba
__set_debug_bba:
/* 80006110 00002210  38 00 00 01 */	li r0, 1
/* 80006114 00002214  98 0D 9C 60 */	stb r0, -0x63a0(r13)
/* 80006118 00002218  4E 80 00 20 */	blr 

.global __get_debug_bba
__get_debug_bba:
/* 8000611C 0000221C  88 6D 9C 60 */	lbz r3, -0x63a0(r13)
/* 80006120 00002220  4E 80 00 20 */	blr 

.global __start
__start:
/* 80006124 00002224  48 00 01 6D */	bl __init_registers
/* 80006128 00002228  48 00 02 A1 */	bl __init_hardware
/* 8000612C 0000222C  38 00 FF FF */	li r0, -1
/* 80006130 00002230  94 21 FF F8 */	stwu r1, -8(r1)
/* 80006134 00002234  90 01 00 04 */	stw r0, 4(r1)
/* 80006138 00002238  90 01 00 00 */	stw r0, 0(r1)
/* 8000613C 0000223C  48 00 01 E5 */	bl __init_data
/* 80006140 00002240  38 00 00 00 */	li r0, 0
/* 80006144 00002244  3C C0 80 00 */	lis r6, 0x80000044@ha
/* 80006148 00002248  38 C6 00 44 */	addi r6, r6, 0x80000044@l
/* 8000614C 0000224C  90 06 00 00 */	stw r0, 0(r6)
/* 80006150 00002250  3C C0 80 00 */	lis r6, 0x800000F4@ha
/* 80006154 00002254  38 C6 00 F4 */	addi r6, r6, 0x800000F4@l
/* 80006158 00002258  80 C6 00 00 */	lwz r6, 0(r6)
/* 8000615C 0000225C  28 06 00 00 */	cmplwi r6, 0
/* 80006160 00002260  41 82 00 0C */	beq lbl_8000616C
/* 80006164 00002264  80 E6 00 0C */	lwz r7, 0xc(r6)
/* 80006168 00002268  48 00 00 24 */	b lbl_8000618C
lbl_8000616C:
/* 8000616C 0000226C  3C A0 80 00 */	lis r5, 0x80000034@ha
/* 80006170 00002270  38 A5 00 34 */	addi r5, r5, 0x80000034@l
/* 80006174 00002274  80 A5 00 00 */	lwz r5, 0(r5)
/* 80006178 00002278  28 05 00 00 */	cmplwi r5, 0
/* 8000617C 0000227C  41 82 00 4C */	beq lbl_800061C8
/* 80006180 00002280  3C E0 80 00 */	lis r7, 0x800030E8@ha
/* 80006184 00002284  38 E7 30 E8 */	addi r7, r7, 0x800030E8@l
/* 80006188 00002288  80 E7 00 00 */	lwz r7, 0(r7)
lbl_8000618C:
/* 8000618C 0000228C  38 A0 00 00 */	li r5, 0
/* 80006190 00002290  28 07 00 02 */	cmplwi r7, 2
/* 80006194 00002294  41 82 00 24 */	beq lbl_800061B8
/* 80006198 00002298  28 07 00 03 */	cmplwi r7, 3
/* 8000619C 0000229C  38 A0 00 01 */	li r5, 1
/* 800061A0 000022A0  41 82 00 18 */	beq lbl_800061B8
/* 800061A4 000022A4  28 07 00 04 */	cmplwi r7, 4
/* 800061A8 000022A8  40 82 00 20 */	bne lbl_800061C8
/* 800061AC 000022AC  38 A0 00 02 */	li r5, 2
/* 800061B0 000022B0  4B FF FF 61 */	bl __set_debug_bba
/* 800061B4 000022B4  48 00 00 14 */	b lbl_800061C8
lbl_800061B8:
/* 800061B8 000022B8  3C C0 80 0C */	lis r6, lbl_800C59D8@ha
/* 800061BC 000022BC  38 C6 59 D8 */	addi r6, r6, lbl_800C59D8@l
/* 800061C0 000022C0  7C C8 03 A6 */	mtlr r6
/* 800061C4 000022C4  4E 80 00 21 */	blrl 
lbl_800061C8:
/* 800061C8 000022C8  3C C0 80 00 */	lis r6, 0x800000F4@ha
/* 800061CC 000022CC  38 C6 00 F4 */	addi r6, r6, 0x800000F4@l
/* 800061D0 000022D0  80 A6 00 00 */	lwz r5, 0(r6)
/* 800061D4 000022D4  28 05 00 00 */	cmplwi r5, 0
/* 800061D8 000022D8  41 A2 00 60 */	beq+ lbl_80006238
/* 800061DC 000022DC  80 C5 00 08 */	lwz r6, 8(r5)
/* 800061E0 000022E0  28 06 00 00 */	cmplwi r6, 0
/* 800061E4 000022E4  41 A2 00 54 */	beq+ lbl_80006238
/* 800061E8 000022E8  7C C5 32 14 */	add r6, r5, r6
/* 800061EC 000022EC  81 C6 00 00 */	lwz r14, 0(r6)
/* 800061F0 000022F0  28 0E 00 00 */	cmplwi r14, 0
/* 800061F4 000022F4  41 82 00 44 */	beq lbl_80006238
/* 800061F8 000022F8  39 E6 00 04 */	addi r15, r6, 4
/* 800061FC 000022FC  7D C9 03 A6 */	mtctr r14
lbl_80006200:
/* 80006200 00002300  38 C6 00 04 */	addi r6, r6, 4
/* 80006204 00002304  80 E6 00 00 */	lwz r7, 0(r6)
/* 80006208 00002308  7C E7 2A 14 */	add r7, r7, r5
/* 8000620C 0000230C  90 E6 00 00 */	stw r7, 0(r6)
/* 80006210 00002310  42 00 FF F0 */	bdnz lbl_80006200
/* 80006214 00002314  3C A0 80 00 */	lis r5, 0x80000034@ha
/* 80006218 00002318  38 A5 00 34 */	addi r5, r5, 0x80000034@l
/* 8000621C 0000231C  55 E7 00 34 */	rlwinm r7, r15, 0, 0, 0x1a
/* 80006220 00002320  90 E5 00 00 */	stw r7, 0(r5)
/* 80006224 00002324  3C A0 80 00 */	lis r5, 0x80003110@ha
/* 80006228 00002328  38 A5 31 10 */	addi r5, r5, 0x80003110@l
/* 8000622C 0000232C  55 E7 00 34 */	rlwinm r7, r15, 0, 0, 0x1a
/* 80006230 00002330  90 E5 00 00 */	stw r7, 0(r5)
/* 80006234 00002334  48 00 00 0C */	b lbl_80006240
lbl_80006238:
/* 80006238 00002338  39 C0 00 00 */	li r14, 0
/* 8000623C 0000233C  39 E0 00 00 */	li r15, 0
lbl_80006240:
/* 80006240 00002340  48 13 27 D9 */	bl func_80138A18
/* 80006244 00002344  48 0E 65 D5 */	bl func_800EC818
/* 80006248 00002348  3C 80 80 00 */	lis r4, 0x800030E6@ha
/* 8000624C 0000234C  38 84 30 E6 */	addi r4, r4, 0x800030E6@l
/* 80006250 00002350  A0 64 00 00 */	lhz r3, 0(r4)
/* 80006254 00002354  70 65 80 00 */	andi. r5, r3, 0x8000
/* 80006258 00002358  41 82 00 10 */	beq lbl_80006268
/* 8000625C 0000235C  70 63 7F FF */	andi. r3, r3, 0x7fff
/* 80006260 00002360  28 03 00 01 */	cmplwi r3, 1
/* 80006264 00002364  40 82 00 08 */	bne lbl_8000626C
lbl_80006268:
/* 80006268 00002368  4B FF FE 81 */	bl __check_pad3
lbl_8000626C:
/* 8000626C 0000236C  4B FF FE B1 */	bl __get_debug_bba
/* 80006270 00002370  28 03 00 01 */	cmplwi r3, 1
/* 80006274 00002374  40 82 00 08 */	bne lbl_8000627C
/* 80006278 00002378  48 0B F7 F9 */	bl func_800C5A70
lbl_8000627C:
/* 8000627C 0000237C  48 0F 0C D5 */	bl func_800F6F50
/* 80006280 00002380  7D C3 73 78 */	mr r3, r14
/* 80006284 00002384  7D E4 7B 78 */	mr r4, r15
/* 80006288 00002388  48 17 DC 5D */	bl func_80183EE4
/* 8000628C 0000238C  48 0F 0D 2C */	b lbl_800F6FB8

.global __init_registers
__init_registers:
/* 80006290 00002390  38 00 00 00 */	li r0, 0
/* 80006294 00002394  38 60 00 00 */	li r3, 0
/* 80006298 00002398  38 80 00 00 */	li r4, 0
/* 8000629C 0000239C  38 A0 00 00 */	li r5, 0
/* 800062A0 000023A0  38 C0 00 00 */	li r6, 0
/* 800062A4 000023A4  38 E0 00 00 */	li r7, 0
/* 800062A8 000023A8  39 00 00 00 */	li r8, 0
/* 800062AC 000023AC  39 20 00 00 */	li r9, 0
/* 800062B0 000023B0  39 40 00 00 */	li r10, 0
/* 800062B4 000023B4  39 60 00 00 */	li r11, 0
/* 800062B8 000023B8  39 80 00 00 */	li r12, 0
/* 800062BC 000023BC  39 C0 00 00 */	li r14, 0
/* 800062C0 000023C0  39 E0 00 00 */	li r15, 0
/* 800062C4 000023C4  3A 00 00 00 */	li r16, 0
/* 800062C8 000023C8  3A 20 00 00 */	li r17, 0
/* 800062CC 000023CC  3A 40 00 00 */	li r18, 0
/* 800062D0 000023D0  3A 60 00 00 */	li r19, 0
/* 800062D4 000023D4  3A 80 00 00 */	li r20, 0
/* 800062D8 000023D8  3A A0 00 00 */	li r21, 0
/* 800062DC 000023DC  3A C0 00 00 */	li r22, 0
/* 800062E0 000023E0  3A E0 00 00 */	li r23, 0
/* 800062E4 000023E4  3B 00 00 00 */	li r24, 0
/* 800062E8 000023E8  3B 20 00 00 */	li r25, 0
/* 800062EC 000023EC  3B 40 00 00 */	li r26, 0
/* 800062F0 000023F0  3B 60 00 00 */	li r27, 0
/* 800062F4 000023F4  3B 80 00 00 */	li r28, 0
/* 800062F8 000023F8  3B A0 00 00 */	li r29, 0
/* 800062FC 000023FC  3B C0 00 00 */	li r30, 0
/* 80006300 00002400  3B E0 00 00 */	li r31, 0
/* 80006304 00002404  3C 20 80 4D */	lis r1, 0x804D6A20@h
/* 80006308 00002408  60 21 6A 20 */	ori r1, r1, 0x804D6A20@l
/* 8000630C 0000240C  3C 40 80 4C */	lis r2, 0x804C7A20@h
/* 80006310 00002410  60 42 7A 20 */	ori r2, r2, 0x804C7A20@l
/* 80006314 00002414  3D A0 80 4C */	lis r13, lbl_804C5380@h
/* 80006318 00002418  61 AD 53 80 */	ori r13, r13, lbl_804C5380@l
/* 8000631C 0000241C  4E 80 00 20 */	blr 

.global __init_data
__init_data:
/* 80006320 00002420  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80006324 00002424  7C 08 02 A6 */	mflr r0
/* 80006328 00002428  90 01 00 24 */	stw r0, 0x24(r1)
/* 8000632C 0000242C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80006330 00002430  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80006334 00002434  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80006338 00002438  3F A0 80 00 */	lis r29, init_info@ha
/* 8000633C 0000243C  3B BD 64 20 */	addi r29, r29, init_info@l
lbl_80006340:
/* 80006340 00002440  83 DD 00 08 */	lwz r30, 8(r29)
/* 80006344 00002444  2C 1E 00 00 */	cmpwi r30, 0
/* 80006348 00002448  41 82 00 38 */	beq lbl_80006380
/* 8000634C 0000244C  80 9D 00 00 */	lwz r4, 0(r29)
/* 80006350 00002450  83 FD 00 04 */	lwz r31, 4(r29)
/* 80006354 00002454  41 82 00 24 */	beq lbl_80006378
/* 80006358 00002458  7C 1F 20 40 */	cmplw r31, r4
/* 8000635C 0000245C  41 82 00 1C */	beq lbl_80006378
/* 80006360 00002460  7F E3 FB 78 */	mr r3, r31
/* 80006364 00002464  7F C5 F3 78 */	mr r5, r30
/* 80006368 00002468  4B FF DC 99 */	bl memcpy
/* 8000636C 0000246C  7F E3 FB 78 */	mr r3, r31
/* 80006370 00002470  7F C4 F3 78 */	mr r4, r30
/* 80006374 00002474  48 00 00 79 */	bl __flush_cache
lbl_80006378:
/* 80006378 00002478  3B BD 00 0C */	addi r29, r29, 0xc
/* 8000637C 0000247C  4B FF FF C4 */	b lbl_80006340
lbl_80006380:
/* 80006380 00002480  3F A0 80 00 */	lis r29, bss_info@ha
/* 80006384 00002484  3B BD 64 B0 */	addi r29, r29, bss_info@l
lbl_80006388:
/* 80006388 00002488  80 BD 00 04 */	lwz r5, 4(r29)
/* 8000638C 0000248C  2C 05 00 00 */	cmpwi r5, 0
/* 80006390 00002490  41 82 00 1C */	beq lbl_800063AC
/* 80006394 00002494  80 7D 00 00 */	lwz r3, 0(r29)
/* 80006398 00002498  41 82 00 0C */	beq lbl_800063A4
/* 8000639C 0000249C  38 80 00 00 */	li r4, 0
/* 800063A0 000024A0  4B FF DD 65 */	bl memset
lbl_800063A4:
/* 800063A4 000024A4  3B BD 00 08 */	addi r29, r29, 8
/* 800063A8 000024A8  4B FF FF E0 */	b lbl_80006388
lbl_800063AC:
/* 800063AC 000024AC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800063B0 000024B0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800063B4 000024B4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800063B8 000024B8  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800063BC 000024BC  7C 08 03 A6 */	mtlr r0
/* 800063C0 000024C0  38 21 00 20 */	addi r1, r1, 0x20
/* 800063C4 000024C4  4E 80 00 20 */	blr 