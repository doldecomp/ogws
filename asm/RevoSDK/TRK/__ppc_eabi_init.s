.include "macros.inc"

.section .init, "ax"  # 0x80004000 - 0x800064E0

.global __init_hardware
__init_hardware:
/* 800063C8 000024C8  7C 00 00 A6 */	mfmsr r0
/* 800063CC 000024CC  60 00 20 00 */	ori r0, r0, 0x2000
/* 800063D0 000024D0  7C 00 01 24 */	mtmsr r0
/* 800063D4 000024D4  7F E8 02 A6 */	mflr r31
/* 800063D8 000024D8  48 0E 6C 05 */	bl func_800ECFDC
/* 800063DC 000024DC  48 0E 59 AD */	bl func_800EBD88
/* 800063E0 000024E0  48 0E 82 09 */	bl func_800EE5E8
/* 800063E4 000024E4  7F E8 03 A6 */	mtlr r31
/* 800063E8 000024E8  4E 80 00 20 */	blr 

.global __flush_cache
__flush_cache:
/* 800063EC 000024EC  3C A0 FF FF */	lis r5, 0xFFFFFFF1@h
/* 800063F0 000024F0  60 A5 FF F1 */	ori r5, r5, 0xFFFFFFF1@l
/* 800063F4 000024F4  7C A5 18 38 */	and r5, r5, r3
/* 800063F8 000024F8  7C 65 18 50 */	subf r3, r5, r3
/* 800063FC 000024FC  7C 84 1A 14 */	add r4, r4, r3
lbl_80006400:
/* 80006400 00002500  7C 00 28 6C */	dcbst 0, r5
/* 80006404 00002504  7C 00 04 AC */	sync 0
/* 80006408 00002508  7C 00 2F AC */	icbi 0, r5
/* 8000640C 0000250C  30 A5 00 08 */	addic r5, r5, 8
/* 80006410 00002510  34 84 FF F8 */	addic. r4, r4, -8
/* 80006414 00002514  40 80 FF EC */	bge lbl_80006400
/* 80006418 00002518  4C 00 01 2C */	isync 
/* 8000641C 0000251C  4E 80 00 20 */	blr 

.global rom_copy_info
rom_copy_info:
# init
/* 80006420 00002520  80 00 40 00 */	.4byte _f_init # Section ptr
/* 80006424 00002524  80 00 40 00 */	.4byte _f_init_rom # Section ptr (again?)
/* 80006428 00002528  00 00 24 D0 */	.4byte 0x000024D0 # Section size
# extab
/* 8000642C 0000252C  80 00 64 E0 */	.4byte _fextab_
/* 80006430 00002530  80 00 64 E0 */	.4byte _fextab__rom
/* 80006434 00002534  00 00 07 40 */	.4byte 0x00000740
# extabindex
/* 80006438 00002538  80 00 6C 20 */	.4byte _fextabindex_
/* 8000643C 0000253C  80 00 6C 20 */	.4byte _fextabindex__rom
/* 80006440 00002540  00 00 0A B8 */	.4byte 0x00000AB8
# text
/* 80006444 00002544  80 00 76 E0 */	.4byte _f_text
/* 80006448 00002548  80 00 76 E0 */	.4byte _f_text_rom
/* 8000644C 0000254C  00 34 D9 9C */	.4byte sz_text
# ctors
/* 80006450 00002550  80 35 50 80 */	.4byte _f_ctors
/* 80006454 00002554  80 35 50 80 */	.4byte _f_ctors_rom
/* 80006458 00002558  00 00 01 E0 */	.4byte 0x000001E0
# dtors
/* 8000645C 0000255C  80 35 52 60 */	.4byte _f_dtors
/* 80006460 00002560  80 35 52 60 */	.4byte _f_dtors_rom
/* 80006464 00002564  00 00 00 0C */	.4byte 0x0000000C
# rodata
/* 80006468 00002568  80 35 52 80 */	.4byte _f_file
/* 8000646C 0000256C  80 35 52 80 */	.4byte _f_file_rom
/* 80006470 00002570  00 02 05 00 */	.4byte 0x00020500
# data
/* 80006474 00002574  80 37 57 80 */	.4byte _f_rodata
/* 80006478 00002578  80 37 57 80 */	.4byte _f_rodata_rom
/* 8000647C 0000257C  00 01 E2 F0 */	.4byte 0x0001E2F0
# data6
/* 80006480 00002580  80 39 3A 80 */	.4byte _f_data
/* 80006484 00002584  80 39 3A 80 */	.4byte _f_data_rom
/* 80006488 00002588  00 03 74 80 */	.4byte 0x00037480
# sdata
/* 8000648C 0000258C  80 4B D3 80 */	.4byte _f_sdata
/* 80006490 00002590  80 4B D3 80 */	.4byte _f_sdata_rom
/* 80006494 00002594  00 00 16 50 */	.4byte 0x00001650
# sdata2
/* 80006498 00002598  80 4B FA 20 */	.4byte _f_sdata2
/* 8000649C 0000259C  80 4B FA 20 */	.4byte _f_sdata2_rom
/* 800064A0 000025A0  00 00 6F B0 */	.4byte 0x00006FB0
# Empty section
/* 800064A4 000025A4  00 00 00 00 */	.4byte 0x00000000
/* 800064A8 000025A8  00 00 00 00 */	.4byte 0x00000000
/* 800064AC 000025AC  00 00 00 00 */	.4byte 0x00000000

.global bss_init_info
bss_init_info:
# bss
/* 800064B0 800025B0  80 3C AF 00 */	.4byte 0x803CAF00 # Section ptr
/* 800064B4 000025B4  00 0F 24 6C */	.4byte 0x000F246C # Section size
# sbss
/* 800064B8 000025B8  80 4B E9 E0 */	.4byte 0x804BE9E0
/* 800064BC 000025BC  00 00 10 30 */	.4byte 0x00001030
# sbss2
/* 800064C0 000025C0  80 4C 69 E0 */	.4byte 0x804C69E0
/* 800064C4 000025C4  00 00 00 3C */	.4byte 0x0000003C
# Empty section
/* 800064C8 000025C8  00 00 00 00 */	.4byte 0x00000000
/* 800064CC 000025CC  00 00 00 00 */	.4byte 0x00000000
# Empty section
/* 800064D0 000025D0  00 00 00 00 */	.4byte 0x00000000
/* 800064D4 000025D4  00 00 00 00 */	.4byte 0x00000000
# Empty section
/* 800064D8 000025D8  00 00 00 00 */	.4byte 0x00000000
/* 800064DC 000025DC  00 00 00 00 */	.4byte 0x00000000
