.include "macros.inc"

.section .bss, "wa"
.global lbl_803EBC58
lbl_803EBC58:
	.skip 0xC
.global lbl_803EBC64
lbl_803EBC64:
	.skip 0x3C

.section .sbss, "wa"
.global lbl_804BEB28
lbl_804BEB28:
	.skip 0x8

.section .text, "ax"  # 0x800076E0 - 0x80355080 
.global GetInstance__Q44nw4r3snd6detail11TaskManagerFv
GetInstance__Q44nw4r3snd6detail11TaskManagerFv:
/* 8004AFF8 00045EF8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004AFFC 00045EFC  7C 08 02 A6 */	mflr r0
/* 8004B000 00045F00  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004B004 00045F04  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004B008 00045F08  88 0D 97 A8 */	lbz r0, lbl_804BEB28-_SDA_BASE_(r13)
/* 8004B00C 00045F0C  7C 00 07 75 */	extsb. r0, r0
/* 8004B010 00045F10  40 82 00 68 */	bne lbl_8004B078
/* 8004B014 00045F14  3F E0 80 3F */	lis r31, lbl_803EBC64@ha
/* 8004B018 00045F18  3C 80 80 05 */	lis r4, __ct__Q34nw4r2ut35LinkList$$0Q44nw4r3snd6detail4Task$$44$$1Fv@ha
/* 8004B01C 00045F1C  3B FF BC 64 */	addi r31, r31, lbl_803EBC64@l
/* 8004B020 00045F20  3C A0 80 05 */	lis r5, __dt__Q34nw4r2ut35LinkList$$0Q44nw4r3snd6detail4Task$$44$$1Fv@ha
/* 8004B024 00045F24  7F E3 FB 78 */	mr r3, r31
/* 8004B028 00045F28  38 84 B1 50 */	addi r4, r4, __ct__Q34nw4r2ut35LinkList$$0Q44nw4r3snd6detail4Task$$44$$1Fv@l
/* 8004B02C 00045F2C  38 A5 B0 F8 */	addi r5, r5, __dt__Q34nw4r2ut35LinkList$$0Q44nw4r3snd6detail4Task$$44$$1Fv@l
/* 8004B030 00045F30  38 C0 00 0C */	li r6, 0xc
/* 8004B034 00045F34  38 E0 00 03 */	li r7, 3
/* 8004B038 00045F38  48 06 6A 1D */	bl __construct_array
/* 8004B03C 00045F3C  38 00 00 00 */	li r0, 0
/* 8004B040 00045F40  38 7F 00 2C */	addi r3, r31, 0x2c
/* 8004B044 00045F44  90 1F 00 24 */	stw r0, 0x24(r31)
/* 8004B048 00045F48  98 1F 00 28 */	stb r0, 0x28(r31)
/* 8004B04C 00045F4C  48 0A 90 FD */	bl OSInitThreadQueue
/* 8004B050 00045F50  38 7F 00 34 */	addi r3, r31, 0x34
/* 8004B054 00045F54  48 0A 90 F5 */	bl OSInitThreadQueue
/* 8004B058 00045F58  3C 80 80 05 */	lis r4, __dt__Q44nw4r3snd6detail11TaskManagerFv@ha
/* 8004B05C 00045F5C  3C A0 80 3F */	lis r5, lbl_803EBC58@ha
/* 8004B060 00045F60  7F E3 FB 78 */	mr r3, r31
/* 8004B064 00045F64  38 84 B0 94 */	addi r4, r4, __dt__Q44nw4r3snd6detail11TaskManagerFv@l
/* 8004B068 00045F68  38 A5 BC 58 */	addi r5, r5, lbl_803EBC58@l
/* 8004B06C 00045F6C  48 06 67 C9 */	bl func_800B1834
/* 8004B070 00045F70  38 00 00 01 */	li r0, 1
/* 8004B074 00045F74  98 0D 97 A8 */	stb r0, lbl_804BEB28-_SDA_BASE_(r13)
lbl_8004B078:
/* 8004B078 00045F78  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8004B07C 00045F7C  3C 60 80 3F */	lis r3, lbl_803EBC64@ha
/* 8004B080 00045F80  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004B084 00045F84  38 63 BC 64 */	addi r3, r3, lbl_803EBC64@l
/* 8004B088 00045F88  7C 08 03 A6 */	mtlr r0
/* 8004B08C 00045F8C  38 21 00 10 */	addi r1, r1, 0x10
/* 8004B090 00045F90  4E 80 00 20 */	blr 

.global __dt__Q44nw4r3snd6detail11TaskManagerFv
__dt__Q44nw4r3snd6detail11TaskManagerFv:
/* 8004B094 00045F94  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004B098 00045F98  7C 08 02 A6 */	mflr r0
/* 8004B09C 00045F9C  2C 03 00 00 */	cmpwi r3, 0
/* 8004B0A0 00045FA0  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004B0A4 00045FA4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004B0A8 00045FA8  7C 9F 23 78 */	mr r31, r4
/* 8004B0AC 00045FAC  93 C1 00 08 */	stw r30, 8(r1)
/* 8004B0B0 00045FB0  7C 7E 1B 78 */	mr r30, r3
/* 8004B0B4 00045FB4  41 82 00 28 */	beq lbl_8004B0DC
/* 8004B0B8 00045FB8  3C 80 80 05 */	lis r4, __dt__Q34nw4r2ut35LinkList$$0Q44nw4r3snd6detail4Task$$44$$1Fv@ha
/* 8004B0BC 00045FBC  38 A0 00 0C */	li r5, 0xc
/* 8004B0C0 00045FC0  38 84 B0 F8 */	addi r4, r4, __dt__Q34nw4r2ut35LinkList$$0Q44nw4r3snd6detail4Task$$44$$1Fv@l
/* 8004B0C4 00045FC4  38 C0 00 03 */	li r6, 3
/* 8004B0C8 00045FC8  48 06 6A 85 */	bl __destroy_arr
/* 8004B0CC 00045FCC  2C 1F 00 00 */	cmpwi r31, 0
/* 8004B0D0 00045FD0  40 81 00 0C */	ble lbl_8004B0DC
/* 8004B0D4 00045FD4  7F C3 F3 78 */	mr r3, r30
/* 8004B0D8 00045FD8  48 05 81 AD */	bl __dl__FPv
lbl_8004B0DC:
/* 8004B0DC 00045FDC  7F C3 F3 78 */	mr r3, r30
/* 8004B0E0 00045FE0  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8004B0E4 00045FE4  83 C1 00 08 */	lwz r30, 8(r1)
/* 8004B0E8 00045FE8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004B0EC 00045FEC  7C 08 03 A6 */	mtlr r0
/* 8004B0F0 00045FF0  38 21 00 10 */	addi r1, r1, 0x10
/* 8004B0F4 00045FF4  4E 80 00 20 */	blr 

.global __dt__Q34nw4r2ut35LinkList$$0Q44nw4r3snd6detail4Task$$44$$1Fv
__dt__Q34nw4r2ut35LinkList$$0Q44nw4r3snd6detail4Task$$44$$1Fv:
/* 8004B0F8 00045FF8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004B0FC 00045FFC  7C 08 02 A6 */	mflr r0
/* 8004B100 00046000  2C 03 00 00 */	cmpwi r3, 0
/* 8004B104 00046004  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004B108 00046008  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004B10C 0004600C  7C 9F 23 78 */	mr r31, r4
/* 8004B110 00046010  93 C1 00 08 */	stw r30, 8(r1)
/* 8004B114 00046014  7C 7E 1B 78 */	mr r30, r3
/* 8004B118 00046018  41 82 00 1C */	beq lbl_8004B134
/* 8004B11C 0004601C  38 80 00 00 */	li r4, 0
/* 8004B120 00046020  4B FB C8 5D */	bl __dt__Q44nw4r2ut6detail12LinkListImplFv
/* 8004B124 00046024  2C 1F 00 00 */	cmpwi r31, 0
/* 8004B128 00046028  40 81 00 0C */	ble lbl_8004B134
/* 8004B12C 0004602C  7F C3 F3 78 */	mr r3, r30
/* 8004B130 00046030  48 05 81 55 */	bl __dl__FPv
lbl_8004B134:
/* 8004B134 00046034  7F C3 F3 78 */	mr r3, r30
/* 8004B138 00046038  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8004B13C 0004603C  83 C1 00 08 */	lwz r30, 8(r1)
/* 8004B140 00046040  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004B144 00046044  7C 08 03 A6 */	mtlr r0
/* 8004B148 00046048  38 21 00 10 */	addi r1, r1, 0x10
/* 8004B14C 0004604C  4E 80 00 20 */	blr 

.global __ct__Q34nw4r2ut35LinkList$$0Q44nw4r3snd6detail4Task$$44$$1Fv
__ct__Q34nw4r2ut35LinkList$$0Q44nw4r3snd6detail4Task$$44$$1Fv:
/* 8004B150 00046050  38 00 00 00 */	li r0, 0
/* 8004B154 00046054  38 83 00 04 */	addi r4, r3, 4
/* 8004B158 00046058  90 03 00 04 */	stw r0, 4(r3)
/* 8004B15C 0004605C  90 03 00 08 */	stw r0, 8(r3)
/* 8004B160 00046060  90 03 00 00 */	stw r0, 0(r3)
/* 8004B164 00046064  90 83 00 04 */	stw r4, 4(r3)
/* 8004B168 00046068  90 83 00 08 */	stw r4, 8(r3)
/* 8004B16C 0004606C  4E 80 00 20 */	blr 

.global AppendTask__Q44nw4r3snd6detail11TaskManagerFPQ44nw4r3snd6detail4TaskQ54nw4r3snd6detail11TaskManager12TaskPriority
AppendTask__Q44nw4r3snd6detail11TaskManagerFPQ44nw4r3snd6detail4TaskQ54nw4r3snd6detail11TaskManager12TaskPriority:
/* 8004B170 00046070  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8004B174 00046074  7C 08 02 A6 */	mflr r0
/* 8004B178 00046078  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004B17C 0004607C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8004B180 00046080  7C BF 2B 78 */	mr r31, r5
/* 8004B184 00046084  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8004B188 00046088  7C 9E 23 78 */	mr r30, r4
/* 8004B18C 0004608C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8004B190 00046090  7C 7D 1B 78 */	mr r29, r3
/* 8004B194 00046094  48 0A 67 2D */	bl OSDisableInterrupts
/* 8004B198 00046098  1C 1F 00 0C */	mulli r0, r31, 0xc
/* 8004B19C 0004609C  38 80 00 01 */	li r4, 1
/* 8004B1A0 000460A0  98 9E 00 0C */	stb r4, 0xc(r30)
/* 8004B1A4 000460A4  7C 7F 1B 78 */	mr r31, r3
/* 8004B1A8 000460A8  38 81 00 08 */	addi r4, r1, 8
/* 8004B1AC 000460AC  7C 7D 02 14 */	add r3, r29, r0
/* 8004B1B0 000460B0  38 03 00 04 */	addi r0, r3, 4
/* 8004B1B4 000460B4  38 BE 00 04 */	addi r5, r30, 4
/* 8004B1B8 000460B8  90 01 00 08 */	stw r0, 8(r1)
/* 8004B1BC 000460BC  4B FB C8 D1 */	bl Insert__Q44nw4r2ut6detail12LinkListImplFQ54nw4r2ut6detail12LinkListImpl8IteratorPQ34nw4r2ut12LinkListNode
/* 8004B1C0 000460C0  38 7D 00 2C */	addi r3, r29, 0x2c
/* 8004B1C4 000460C4  48 0A A1 89 */	bl OSWakeupThread
/* 8004B1C8 000460C8  7F E3 FB 78 */	mr r3, r31
/* 8004B1CC 000460CC  48 0A 67 1D */	bl OSRestoreInterrupts
/* 8004B1D0 000460D0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004B1D4 000460D4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004B1D8 000460D8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8004B1DC 000460DC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004B1E0 000460E0  7C 08 03 A6 */	mtlr r0
/* 8004B1E4 000460E4  38 21 00 20 */	addi r1, r1, 0x20
/* 8004B1E8 000460E8  4E 80 00 20 */	blr 

.global PopTask__Q44nw4r3snd6detail11TaskManagerFv
PopTask__Q44nw4r3snd6detail11TaskManagerFv:
/* 8004B1EC 000460EC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8004B1F0 000460F0  7C 08 02 A6 */	mflr r0
/* 8004B1F4 000460F4  90 01 00 34 */	stw r0, 0x34(r1)
/* 8004B1F8 000460F8  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8004B1FC 000460FC  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8004B200 00046100  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8004B204 00046104  93 81 00 20 */	stw r28, 0x20(r1)
/* 8004B208 00046108  7C 7C 1B 78 */	mr r28, r3
/* 8004B20C 0004610C  48 0A 66 B5 */	bl OSDisableInterrupts
/* 8004B210 00046110  7C 7F 1B 78 */	mr r31, r3
/* 8004B214 00046114  48 0A 66 AD */	bl OSDisableInterrupts
/* 8004B218 00046118  80 1C 00 18 */	lwz r0, 0x18(r28)
/* 8004B21C 0004611C  7C 7E 1B 78 */	mr r30, r3
/* 8004B220 00046120  2C 00 00 00 */	cmpwi r0, 0
/* 8004B224 00046124  40 82 00 10 */	bne lbl_8004B234
/* 8004B228 00046128  48 0A 66 C1 */	bl OSRestoreInterrupts
/* 8004B22C 0004612C  3B C0 00 00 */	li r30, 0
/* 8004B230 00046130  48 00 00 24 */	b lbl_8004B254
lbl_8004B234:
/* 8004B234 00046134  83 BC 00 1C */	lwz r29, 0x1c(r28)
/* 8004B238 00046138  38 7C 00 18 */	addi r3, r28, 0x18
/* 8004B23C 0004613C  38 81 00 10 */	addi r4, r1, 0x10
/* 8004B240 00046140  93 A1 00 10 */	stw r29, 0x10(r1)
/* 8004B244 00046144  4B FB C7 BD */	bl Erase__Q44nw4r2ut6detail12LinkListImplFQ54nw4r2ut6detail12LinkListImpl8Iterator
/* 8004B248 00046148  7F C3 F3 78 */	mr r3, r30
/* 8004B24C 0004614C  48 0A 66 9D */	bl OSRestoreInterrupts
/* 8004B250 00046150  3B DD FF FC */	addi r30, r29, -4
lbl_8004B254:
/* 8004B254 00046154  2C 1E 00 00 */	cmpwi r30, 0
/* 8004B258 00046158  41 82 00 14 */	beq lbl_8004B26C
/* 8004B25C 0004615C  7F E3 FB 78 */	mr r3, r31
/* 8004B260 00046160  48 0A 66 89 */	bl OSRestoreInterrupts
/* 8004B264 00046164  7F C3 F3 78 */	mr r3, r30
/* 8004B268 00046168  48 00 00 C0 */	b lbl_8004B328
lbl_8004B26C:
/* 8004B26C 0004616C  48 0A 66 55 */	bl OSDisableInterrupts
/* 8004B270 00046170  80 1C 00 0C */	lwz r0, 0xc(r28)
/* 8004B274 00046174  7C 7E 1B 78 */	mr r30, r3
/* 8004B278 00046178  2C 00 00 00 */	cmpwi r0, 0
/* 8004B27C 0004617C  40 82 00 10 */	bne lbl_8004B28C
/* 8004B280 00046180  48 0A 66 69 */	bl OSRestoreInterrupts
/* 8004B284 00046184  3B C0 00 00 */	li r30, 0
/* 8004B288 00046188  48 00 00 24 */	b lbl_8004B2AC
lbl_8004B28C:
/* 8004B28C 0004618C  83 BC 00 10 */	lwz r29, 0x10(r28)
/* 8004B290 00046190  38 7C 00 0C */	addi r3, r28, 0xc
/* 8004B294 00046194  38 81 00 0C */	addi r4, r1, 0xc
/* 8004B298 00046198  93 A1 00 0C */	stw r29, 0xc(r1)
/* 8004B29C 0004619C  4B FB C7 65 */	bl Erase__Q44nw4r2ut6detail12LinkListImplFQ54nw4r2ut6detail12LinkListImpl8Iterator
/* 8004B2A0 000461A0  7F C3 F3 78 */	mr r3, r30
/* 8004B2A4 000461A4  48 0A 66 45 */	bl OSRestoreInterrupts
/* 8004B2A8 000461A8  3B DD FF FC */	addi r30, r29, -4
lbl_8004B2AC:
/* 8004B2AC 000461AC  2C 1E 00 00 */	cmpwi r30, 0
/* 8004B2B0 000461B0  41 82 00 14 */	beq lbl_8004B2C4
/* 8004B2B4 000461B4  7F E3 FB 78 */	mr r3, r31
/* 8004B2B8 000461B8  48 0A 66 31 */	bl OSRestoreInterrupts
/* 8004B2BC 000461BC  7F C3 F3 78 */	mr r3, r30
/* 8004B2C0 000461C0  48 00 00 68 */	b lbl_8004B328
lbl_8004B2C4:
/* 8004B2C4 000461C4  48 0A 65 FD */	bl OSDisableInterrupts
/* 8004B2C8 000461C8  80 1C 00 00 */	lwz r0, 0(r28)
/* 8004B2CC 000461CC  7C 7E 1B 78 */	mr r30, r3
/* 8004B2D0 000461D0  2C 00 00 00 */	cmpwi r0, 0
/* 8004B2D4 000461D4  40 82 00 10 */	bne lbl_8004B2E4
/* 8004B2D8 000461D8  48 0A 66 11 */	bl OSRestoreInterrupts
/* 8004B2DC 000461DC  3B C0 00 00 */	li r30, 0
/* 8004B2E0 000461E0  48 00 00 24 */	b lbl_8004B304
lbl_8004B2E4:
/* 8004B2E4 000461E4  83 BC 00 04 */	lwz r29, 4(r28)
/* 8004B2E8 000461E8  7F 83 E3 78 */	mr r3, r28
/* 8004B2EC 000461EC  38 81 00 08 */	addi r4, r1, 8
/* 8004B2F0 000461F0  93 A1 00 08 */	stw r29, 8(r1)
/* 8004B2F4 000461F4  4B FB C7 0D */	bl Erase__Q44nw4r2ut6detail12LinkListImplFQ54nw4r2ut6detail12LinkListImpl8Iterator
/* 8004B2F8 000461F8  7F C3 F3 78 */	mr r3, r30
/* 8004B2FC 000461FC  48 0A 65 ED */	bl OSRestoreInterrupts
/* 8004B300 00046200  3B DD FF FC */	addi r30, r29, -4
lbl_8004B304:
/* 8004B304 00046204  2C 1E 00 00 */	cmpwi r30, 0
/* 8004B308 00046208  41 82 00 14 */	beq lbl_8004B31C
/* 8004B30C 0004620C  7F E3 FB 78 */	mr r3, r31
/* 8004B310 00046210  48 0A 65 D9 */	bl OSRestoreInterrupts
/* 8004B314 00046214  7F C3 F3 78 */	mr r3, r30
/* 8004B318 00046218  48 00 00 10 */	b lbl_8004B328
lbl_8004B31C:
/* 8004B31C 0004621C  7F E3 FB 78 */	mr r3, r31
/* 8004B320 00046220  48 0A 65 C9 */	bl OSRestoreInterrupts
/* 8004B324 00046224  38 60 00 00 */	li r3, 0
lbl_8004B328:
/* 8004B328 00046228  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8004B32C 0004622C  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8004B330 00046230  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8004B334 00046234  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8004B338 00046238  83 81 00 20 */	lwz r28, 0x20(r1)
/* 8004B33C 0004623C  7C 08 03 A6 */	mtlr r0
/* 8004B340 00046240  38 21 00 30 */	addi r1, r1, 0x30
/* 8004B344 00046244  4E 80 00 20 */	blr 

.global GetNextTask__Q44nw4r3snd6detail11TaskManagerFv
GetNextTask__Q44nw4r3snd6detail11TaskManagerFv:
/* 8004B348 00046248  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8004B34C 0004624C  7C 08 02 A6 */	mflr r0
/* 8004B350 00046250  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004B354 00046254  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8004B358 00046258  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8004B35C 0004625C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8004B360 00046260  7C 7D 1B 78 */	mr r29, r3
/* 8004B364 00046264  48 0A 65 5D */	bl OSDisableInterrupts
/* 8004B368 00046268  7C 7F 1B 78 */	mr r31, r3
/* 8004B36C 0004626C  48 0A 65 55 */	bl OSDisableInterrupts
/* 8004B370 00046270  80 1D 00 18 */	lwz r0, 0x18(r29)
/* 8004B374 00046274  2C 00 00 00 */	cmpwi r0, 0
/* 8004B378 00046278  40 82 00 10 */	bne lbl_8004B388
/* 8004B37C 0004627C  48 0A 65 6D */	bl OSRestoreInterrupts
/* 8004B380 00046280  3B C0 00 00 */	li r30, 0
/* 8004B384 00046284  48 00 00 10 */	b lbl_8004B394
lbl_8004B388:
/* 8004B388 00046288  83 DD 00 1C */	lwz r30, 0x1c(r29)
/* 8004B38C 0004628C  48 0A 65 5D */	bl OSRestoreInterrupts
/* 8004B390 00046290  3B DE FF FC */	addi r30, r30, -4
lbl_8004B394:
/* 8004B394 00046294  2C 1E 00 00 */	cmpwi r30, 0
/* 8004B398 00046298  41 82 00 14 */	beq lbl_8004B3AC
/* 8004B39C 0004629C  7F E3 FB 78 */	mr r3, r31
/* 8004B3A0 000462A0  48 0A 65 49 */	bl OSRestoreInterrupts
/* 8004B3A4 000462A4  7F C3 F3 78 */	mr r3, r30
/* 8004B3A8 000462A8  48 00 00 90 */	b lbl_8004B438
lbl_8004B3AC:
/* 8004B3AC 000462AC  48 0A 65 15 */	bl OSDisableInterrupts
/* 8004B3B0 000462B0  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8004B3B4 000462B4  2C 00 00 00 */	cmpwi r0, 0
/* 8004B3B8 000462B8  40 82 00 10 */	bne lbl_8004B3C8
/* 8004B3BC 000462BC  48 0A 65 2D */	bl OSRestoreInterrupts
/* 8004B3C0 000462C0  3B C0 00 00 */	li r30, 0
/* 8004B3C4 000462C4  48 00 00 10 */	b lbl_8004B3D4
lbl_8004B3C8:
/* 8004B3C8 000462C8  83 DD 00 10 */	lwz r30, 0x10(r29)
/* 8004B3CC 000462CC  48 0A 65 1D */	bl OSRestoreInterrupts
/* 8004B3D0 000462D0  3B DE FF FC */	addi r30, r30, -4
lbl_8004B3D4:
/* 8004B3D4 000462D4  2C 1E 00 00 */	cmpwi r30, 0
/* 8004B3D8 000462D8  41 82 00 14 */	beq lbl_8004B3EC
/* 8004B3DC 000462DC  7F E3 FB 78 */	mr r3, r31
/* 8004B3E0 000462E0  48 0A 65 09 */	bl OSRestoreInterrupts
/* 8004B3E4 000462E4  7F C3 F3 78 */	mr r3, r30
/* 8004B3E8 000462E8  48 00 00 50 */	b lbl_8004B438
lbl_8004B3EC:
/* 8004B3EC 000462EC  48 0A 64 D5 */	bl OSDisableInterrupts
/* 8004B3F0 000462F0  80 1D 00 00 */	lwz r0, 0(r29)
/* 8004B3F4 000462F4  2C 00 00 00 */	cmpwi r0, 0
/* 8004B3F8 000462F8  40 82 00 10 */	bne lbl_8004B408
/* 8004B3FC 000462FC  48 0A 64 ED */	bl OSRestoreInterrupts
/* 8004B400 00046300  3B C0 00 00 */	li r30, 0
/* 8004B404 00046304  48 00 00 10 */	b lbl_8004B414
lbl_8004B408:
/* 8004B408 00046308  83 DD 00 04 */	lwz r30, 4(r29)
/* 8004B40C 0004630C  48 0A 64 DD */	bl OSRestoreInterrupts
/* 8004B410 00046310  3B DE FF FC */	addi r30, r30, -4
lbl_8004B414:
/* 8004B414 00046314  2C 1E 00 00 */	cmpwi r30, 0
/* 8004B418 00046318  41 82 00 14 */	beq lbl_8004B42C
/* 8004B41C 0004631C  7F E3 FB 78 */	mr r3, r31
/* 8004B420 00046320  48 0A 64 C9 */	bl OSRestoreInterrupts
/* 8004B424 00046324  7F C3 F3 78 */	mr r3, r30
/* 8004B428 00046328  48 00 00 10 */	b lbl_8004B438
lbl_8004B42C:
/* 8004B42C 0004632C  7F E3 FB 78 */	mr r3, r31
/* 8004B430 00046330  48 0A 64 B9 */	bl OSRestoreInterrupts
/* 8004B434 00046334  38 60 00 00 */	li r3, 0
lbl_8004B438:
/* 8004B438 00046338  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004B43C 0004633C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004B440 00046340  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8004B444 00046344  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004B448 00046348  7C 08 03 A6 */	mtlr r0
/* 8004B44C 0004634C  38 21 00 20 */	addi r1, r1, 0x20
/* 8004B450 00046350  4E 80 00 20 */	blr 

.global ExecuteTask__Q44nw4r3snd6detail11TaskManagerFv
ExecuteTask__Q44nw4r3snd6detail11TaskManagerFv:
/* 8004B454 00046354  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8004B458 00046358  7C 08 02 A6 */	mflr r0
/* 8004B45C 0004635C  90 01 00 24 */	stw r0, 0x24(r1)
/* 8004B460 00046360  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8004B464 00046364  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8004B468 00046368  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8004B46C 0004636C  7C 7D 1B 78 */	mr r29, r3
/* 8004B470 00046370  4B FF FD 7D */	bl PopTask__Q44nw4r3snd6detail11TaskManagerFv
/* 8004B474 00046374  2C 03 00 00 */	cmpwi r3, 0
/* 8004B478 00046378  7C 7E 1B 78 */	mr r30, r3
/* 8004B47C 0004637C  40 82 00 0C */	bne lbl_8004B488
/* 8004B480 00046380  38 60 00 00 */	li r3, 0
/* 8004B484 00046384  48 00 00 30 */	b lbl_8004B4B4
lbl_8004B488:
/* 8004B488 00046388  90 7D 00 24 */	stw r3, 0x24(r29)
/* 8004B48C 0004638C  3B E0 00 00 */	li r31, 0
/* 8004B490 00046390  9B E3 00 0C */	stb r31, 0xc(r3)
/* 8004B494 00046394  81 83 00 00 */	lwz r12, 0(r3)
/* 8004B498 00046398  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 8004B49C 0004639C  7D 89 03 A6 */	mtctr r12
/* 8004B4A0 000463A0  4E 80 04 21 */	bctrl 
/* 8004B4A4 000463A4  93 FD 00 24 */	stw r31, 0x24(r29)
/* 8004B4A8 000463A8  38 7D 00 34 */	addi r3, r29, 0x34
/* 8004B4AC 000463AC  48 0A 9E A1 */	bl OSWakeupThread
/* 8004B4B0 000463B0  7F C3 F3 78 */	mr r3, r30
lbl_8004B4B4:
/* 8004B4B4 000463B4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8004B4B8 000463B8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8004B4BC 000463BC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8004B4C0 000463C0  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8004B4C4 000463C4  7C 08 03 A6 */	mtlr r0
/* 8004B4C8 000463C8  38 21 00 20 */	addi r1, r1, 0x20
/* 8004B4CC 000463CC  4E 80 00 20 */	blr 

.global CancelTask__Q44nw4r3snd6detail11TaskManagerFPQ44nw4r3snd6detail4Task
CancelTask__Q44nw4r3snd6detail11TaskManagerFPQ44nw4r3snd6detail4Task:
/* 8004B4D0 000463D0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8004B4D4 000463D4  7C 08 02 A6 */	mflr r0
/* 8004B4D8 000463D8  90 01 00 34 */	stw r0, 0x34(r1)
/* 8004B4DC 000463DC  39 61 00 30 */	addi r11, r1, 0x30
/* 8004B4E0 000463E0  48 06 68 5D */	bl _savegpr_25
/* 8004B4E4 000463E4  7C 79 1B 78 */	mr r25, r3
/* 8004B4E8 000463E8  7C 9A 23 78 */	mr r26, r4
/* 8004B4EC 000463EC  48 0A 63 D5 */	bl OSDisableInterrupts
/* 8004B4F0 000463F0  80 19 00 24 */	lwz r0, 0x24(r25)
/* 8004B4F4 000463F4  7C 7E 1B 78 */	mr r30, r3
/* 8004B4F8 000463F8  7C 1A 00 40 */	cmplw r26, r0
/* 8004B4FC 000463FC  40 82 00 34 */	bne lbl_8004B530
/* 8004B500 00046400  81 9A 00 00 */	lwz r12, 0(r26)
/* 8004B504 00046404  7F 43 D3 78 */	mr r3, r26
/* 8004B508 00046408  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 8004B50C 0004640C  7D 89 03 A6 */	mtctr r12
/* 8004B510 00046410  4E 80 04 21 */	bctrl 
/* 8004B514 00046414  48 00 00 0C */	b lbl_8004B520
lbl_8004B518:
/* 8004B518 00046418  38 79 00 34 */	addi r3, r25, 0x34
/* 8004B51C 0004641C  48 0A 9D 45 */	bl OSSleepThread
lbl_8004B520:
/* 8004B520 00046420  80 19 00 24 */	lwz r0, 0x24(r25)
/* 8004B524 00046424  7C 1A 00 40 */	cmplw r26, r0
/* 8004B528 00046428  41 82 FF F0 */	beq lbl_8004B518
/* 8004B52C 0004642C  48 00 00 74 */	b lbl_8004B5A0
lbl_8004B530:
/* 8004B530 00046430  3B 60 00 00 */	li r27, 0
/* 8004B534 00046434  3B E0 00 00 */	li r31, 0
/* 8004B538 00046438  3B A0 00 00 */	li r29, 0
lbl_8004B53C:
/* 8004B53C 0004643C  7C 79 FA 14 */	add r3, r25, r31
/* 8004B540 00046440  80 83 00 04 */	lwz r4, 4(r3)
/* 8004B544 00046444  38 03 00 04 */	addi r0, r3, 4
/* 8004B548 00046448  48 00 00 40 */	b lbl_8004B588
lbl_8004B54C:
/* 8004B54C 0004644C  7C 9C 23 78 */	mr r28, r4
/* 8004B550 00046450  80 84 00 00 */	lwz r4, 0(r4)
/* 8004B554 00046454  38 BC FF FC */	addi r5, r28, -4
/* 8004B558 00046458  7C 05 D0 40 */	cmplw r5, r26
/* 8004B55C 0004645C  40 82 00 2C */	bne lbl_8004B588
/* 8004B560 00046460  93 81 00 08 */	stw r28, 8(r1)
/* 8004B564 00046464  38 81 00 08 */	addi r4, r1, 8
/* 8004B568 00046468  4B FB C4 99 */	bl Erase__Q44nw4r2ut6detail12LinkListImplFQ54nw4r2ut6detail12LinkListImpl8Iterator
/* 8004B56C 0004646C  9B BC 00 08 */	stb r29, 8(r28)
/* 8004B570 00046470  38 7C FF FC */	addi r3, r28, -4
/* 8004B574 00046474  81 9C FF FC */	lwz r12, -4(r28)
/* 8004B578 00046478  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 8004B57C 0004647C  7D 89 03 A6 */	mtctr r12
/* 8004B580 00046480  4E 80 04 21 */	bctrl 
/* 8004B584 00046484  48 00 00 0C */	b lbl_8004B590
lbl_8004B588:
/* 8004B588 00046488  7C 04 00 40 */	cmplw r4, r0
/* 8004B58C 0004648C  40 82 FF C0 */	bne lbl_8004B54C
lbl_8004B590:
/* 8004B590 00046490  3B 7B 00 01 */	addi r27, r27, 1
/* 8004B594 00046494  3B FF 00 0C */	addi r31, r31, 0xc
/* 8004B598 00046498  2C 1B 00 03 */	cmpwi r27, 3
/* 8004B59C 0004649C  41 80 FF A0 */	blt lbl_8004B53C
lbl_8004B5A0:
/* 8004B5A0 000464A0  7F C3 F3 78 */	mr r3, r30
/* 8004B5A4 000464A4  48 0A 63 45 */	bl OSRestoreInterrupts
/* 8004B5A8 000464A8  39 61 00 30 */	addi r11, r1, 0x30
/* 8004B5AC 000464AC  48 06 67 DD */	bl _restgpr_25
/* 8004B5B0 000464B0  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8004B5B4 000464B4  7C 08 03 A6 */	mtlr r0
/* 8004B5B8 000464B8  38 21 00 30 */	addi r1, r1, 0x30
/* 8004B5BC 000464BC  4E 80 00 20 */	blr 

.global CancelAllTask__Q44nw4r3snd6detail11TaskManagerFv
CancelAllTask__Q44nw4r3snd6detail11TaskManagerFv:
/* 8004B5C0 000464C0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8004B5C4 000464C4  7C 08 02 A6 */	mflr r0
/* 8004B5C8 000464C8  90 01 00 34 */	stw r0, 0x34(r1)
/* 8004B5CC 000464CC  39 61 00 30 */	addi r11, r1, 0x30
/* 8004B5D0 000464D0  48 06 67 6D */	bl _savegpr_25
/* 8004B5D4 000464D4  7C 79 1B 78 */	mr r25, r3
/* 8004B5D8 000464D8  48 0A 62 E9 */	bl OSDisableInterrupts
/* 8004B5DC 000464DC  7C 7E 1B 78 */	mr r30, r3
/* 8004B5E0 000464E0  3B 60 00 00 */	li r27, 0
/* 8004B5E4 000464E4  3B E0 00 00 */	li r31, 0
/* 8004B5E8 000464E8  3B A0 00 00 */	li r29, 0
lbl_8004B5EC:
/* 8004B5EC 000464EC  7C 19 F8 2E */	lwzx r0, r25, r31
/* 8004B5F0 000464F0  7F 59 FA 14 */	add r26, r25, r31
/* 8004B5F4 000464F4  2C 00 00 00 */	cmpwi r0, 0
/* 8004B5F8 000464F8  41 82 00 44 */	beq lbl_8004B63C
/* 8004B5FC 000464FC  48 00 00 34 */	b lbl_8004B630
lbl_8004B600:
/* 8004B600 00046500  80 BA 00 08 */	lwz r5, 8(r26)
/* 8004B604 00046504  7F 43 D3 78 */	mr r3, r26
/* 8004B608 00046508  38 81 00 08 */	addi r4, r1, 8
/* 8004B60C 0004650C  90 A1 00 08 */	stw r5, 8(r1)
/* 8004B610 00046510  3B 85 FF FC */	addi r28, r5, -4
/* 8004B614 00046514  4B FB C3 ED */	bl Erase__Q44nw4r2ut6detail12LinkListImplFQ54nw4r2ut6detail12LinkListImpl8Iterator
/* 8004B618 00046518  9B BC 00 0C */	stb r29, 0xc(r28)
/* 8004B61C 0004651C  7F 83 E3 78 */	mr r3, r28
/* 8004B620 00046520  81 9C 00 00 */	lwz r12, 0(r28)
/* 8004B624 00046524  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 8004B628 00046528  7D 89 03 A6 */	mtctr r12
/* 8004B62C 0004652C  4E 80 04 21 */	bctrl 
lbl_8004B630:
/* 8004B630 00046530  80 1A 00 00 */	lwz r0, 0(r26)
/* 8004B634 00046534  2C 00 00 00 */	cmpwi r0, 0
/* 8004B638 00046538  40 82 FF C8 */	bne lbl_8004B600
lbl_8004B63C:
/* 8004B63C 0004653C  3B 7B 00 01 */	addi r27, r27, 1
/* 8004B640 00046540  3B FF 00 0C */	addi r31, r31, 0xc
/* 8004B644 00046544  2C 1B 00 03 */	cmpwi r27, 3
/* 8004B648 00046548  41 80 FF A4 */	blt lbl_8004B5EC
/* 8004B64C 0004654C  80 19 00 24 */	lwz r0, 0x24(r25)
/* 8004B650 00046550  2C 00 00 00 */	cmpwi r0, 0
/* 8004B654 00046554  41 82 00 30 */	beq lbl_8004B684
/* 8004B658 00046558  80 79 00 24 */	lwz r3, 0x24(r25)
/* 8004B65C 0004655C  81 83 00 00 */	lwz r12, 0(r3)
/* 8004B660 00046560  81 8C 00 14 */	lwz r12, 0x14(r12)
/* 8004B664 00046564  7D 89 03 A6 */	mtctr r12
/* 8004B668 00046568  4E 80 04 21 */	bctrl 
/* 8004B66C 0004656C  48 00 00 0C */	b lbl_8004B678
lbl_8004B670:
/* 8004B670 00046570  38 79 00 34 */	addi r3, r25, 0x34
/* 8004B674 00046574  48 0A 9B ED */	bl OSSleepThread
lbl_8004B678:
/* 8004B678 00046578  80 19 00 24 */	lwz r0, 0x24(r25)
/* 8004B67C 0004657C  2C 00 00 00 */	cmpwi r0, 0
/* 8004B680 00046580  40 82 FF F0 */	bne lbl_8004B670
lbl_8004B684:
/* 8004B684 00046584  7F C3 F3 78 */	mr r3, r30
/* 8004B688 00046588  48 0A 62 61 */	bl OSRestoreInterrupts
/* 8004B68C 0004658C  39 61 00 30 */	addi r11, r1, 0x30
/* 8004B690 00046590  48 06 66 F9 */	bl _restgpr_25
/* 8004B694 00046594  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8004B698 00046598  7C 08 03 A6 */	mtlr r0
/* 8004B69C 0004659C  38 21 00 30 */	addi r1, r1, 0x30
/* 8004B6A0 000465A0  4E 80 00 20 */	blr 

.global WaitTask__Q44nw4r3snd6detail11TaskManagerFv
WaitTask__Q44nw4r3snd6detail11TaskManagerFv:
/* 8004B6A4 000465A4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004B6A8 000465A8  7C 08 02 A6 */	mflr r0
/* 8004B6AC 000465AC  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004B6B0 000465B0  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004B6B4 000465B4  93 C1 00 08 */	stw r30, 8(r1)
/* 8004B6B8 000465B8  7C 7E 1B 78 */	mr r30, r3
/* 8004B6BC 000465BC  48 0A 62 05 */	bl OSDisableInterrupts
/* 8004B6C0 000465C0  38 00 00 00 */	li r0, 0
/* 8004B6C4 000465C4  7C 7F 1B 78 */	mr r31, r3
/* 8004B6C8 000465C8  98 1E 00 28 */	stb r0, 0x28(r30)
/* 8004B6CC 000465CC  48 00 00 0C */	b lbl_8004B6D8
lbl_8004B6D0:
/* 8004B6D0 000465D0  38 7E 00 2C */	addi r3, r30, 0x2c
/* 8004B6D4 000465D4  48 0A 9B 8D */	bl OSSleepThread
lbl_8004B6D8:
/* 8004B6D8 000465D8  7F C3 F3 78 */	mr r3, r30
/* 8004B6DC 000465DC  4B FF FC 6D */	bl GetNextTask__Q44nw4r3snd6detail11TaskManagerFv
/* 8004B6E0 000465E0  2C 03 00 00 */	cmpwi r3, 0
/* 8004B6E4 000465E4  40 82 00 10 */	bne lbl_8004B6F4
/* 8004B6E8 000465E8  88 1E 00 28 */	lbz r0, 0x28(r30)
/* 8004B6EC 000465EC  2C 00 00 00 */	cmpwi r0, 0
/* 8004B6F0 000465F0  41 82 FF E0 */	beq lbl_8004B6D0
lbl_8004B6F4:
/* 8004B6F4 000465F4  7F E3 FB 78 */	mr r3, r31
/* 8004B6F8 000465F8  48 0A 61 F1 */	bl OSRestoreInterrupts
/* 8004B6FC 000465FC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004B700 00046600  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8004B704 00046604  83 C1 00 08 */	lwz r30, 8(r1)
/* 8004B708 00046608  7C 08 03 A6 */	mtlr r0
/* 8004B70C 0004660C  38 21 00 10 */	addi r1, r1, 0x10
/* 8004B710 00046610  4E 80 00 20 */	blr 

.global CancelWaitTask__Q44nw4r3snd6detail11TaskManagerFv
CancelWaitTask__Q44nw4r3snd6detail11TaskManagerFv:
/* 8004B714 00046614  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8004B718 00046618  7C 08 02 A6 */	mflr r0
/* 8004B71C 0004661C  90 01 00 14 */	stw r0, 0x14(r1)
/* 8004B720 00046620  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8004B724 00046624  93 C1 00 08 */	stw r30, 8(r1)
/* 8004B728 00046628  7C 7E 1B 78 */	mr r30, r3
/* 8004B72C 0004662C  48 0A 61 95 */	bl OSDisableInterrupts
/* 8004B730 00046630  38 00 00 01 */	li r0, 1
/* 8004B734 00046634  7C 7F 1B 78 */	mr r31, r3
/* 8004B738 00046638  98 1E 00 28 */	stb r0, 0x28(r30)
/* 8004B73C 0004663C  38 7E 00 2C */	addi r3, r30, 0x2c
/* 8004B740 00046640  48 0A 9C 0D */	bl OSWakeupThread
/* 8004B744 00046644  7F E3 FB 78 */	mr r3, r31
/* 8004B748 00046648  48 0A 61 A1 */	bl OSRestoreInterrupts
/* 8004B74C 0004664C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8004B750 00046650  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8004B754 00046654  83 C1 00 08 */	lwz r30, 8(r1)
/* 8004B758 00046658  7C 08 03 A6 */	mtlr r0
/* 8004B75C 0004665C  38 21 00 10 */	addi r1, r1, 0x10
/* 8004B760 00046660  4E 80 00 20 */	blr 
