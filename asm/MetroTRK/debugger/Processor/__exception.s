.include "macros.inc"

# Dynamically pad vector slots to 0x100 bytes
.macro padslot name
.fill 0x100 - (. - \name)
.endm

.section .init, "ax"

.global gTRKInterruptVectorTable
gTRKInterruptVectorTable:

# Slot 0x0000: Reserved (used for name string)
name_string:
.string "Metrowerks Target Resident Kernel for PowerPC"
.balign 4
padslot name_string

# Slot 0x0100: System Reset Exception
system_reset_exception_handler:
/* 80004288 00000388  48 00 1E 34 */	b __TRK_reset
padslot system_reset_exception_handler

# Slot 0x0200: Machine Check Exception
machine_check_vector:
/* 80004388 00000488  7C 51 43 A6 */	mtsprg1 r2
/* 8000438C 0000048C  7C 5A 02 A6 */	mfsrr0 r2
/* 80004390 00000490  7C 00 17 AC */	icbi 0, r2
/* 80004394 00000494  7C 53 02 A6 */	mfdar r2
/* 80004398 00000498  7C 00 13 AC */	dcbi 0, r2
/* 8000439C 0000049C  7C 51 42 A6 */	mfsprg1 r2
/* 800043A0 000004A0  7C 51 43 A6 */	mtsprg1 r2
/* 800043A4 000004A4  7C 72 43 A6 */	mtsprg2 r3
/* 800043A8 000004A8  7C 93 43 A6 */	mtsprg3 r4
/* 800043AC 000004AC  7C 5A 02 A6 */	mfsrr0 r2
/* 800043B0 000004B0  7C 9B 02 A6 */	mfsrr1 r4
/* 800043B4 000004B4  7C 60 00 A6 */	mfmsr r3
/* 800043B8 000004B8  60 63 00 30 */	ori r3, r3, 0x30
/* 800043BC 000004BC  7C 7B 03 A6 */	mtsrr1 r3
/* 800043C0 000004C0  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 800043C4 000004C4  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 800043C8 000004C8  7C 7A 03 A6 */	mtsrr0 r3
/* 800043CC 000004CC  38 60 02 00 */	li r3, 0x0200
/* 800043D0 000004D0  4C 00 00 64 */	rfi 
padslot machine_check_vector

# Slot 0x0300: DSI Exception
dsi_vector:
/* 80004488 00000588  7C 51 43 A6 */	mtsprg1 r2
/* 8000448C 0000058C  7C 72 43 A6 */	mtsprg2 r3
/* 80004490 00000590  7C 93 43 A6 */	mtsprg3 r4
/* 80004494 00000594  7C 5A 02 A6 */	mfsrr0 r2
/* 80004498 00000598  7C 9B 02 A6 */	mfsrr1 r4
/* 8000449C 0000059C  7C 60 00 A6 */	mfmsr r3
/* 800044A0 000005A0  60 63 00 30 */	ori r3, r3, 0x30
/* 800044A4 000005A4  7C 7B 03 A6 */	mtsrr1 r3
/* 800044A8 000005A8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 800044AC 000005AC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 800044B0 000005B0  7C 7A 03 A6 */	mtsrr0 r3
/* 800044B4 000005B4  38 60 03 00 */	li r3, 0x0300
/* 800044B8 000005B8  4C 00 00 64 */	rfi 
padslot dsi_vector

# Slot 0x0400: ISI Exception
isi_vector:
/* 80004588 00000688  7C 51 43 A6 */	mtsprg1 r2
/* 8000458C 0000068C  7C 72 43 A6 */	mtsprg2 r3
/* 80004590 00000690  7C 93 43 A6 */	mtsprg3 r4
/* 80004594 00000694  7C 5A 02 A6 */	mfsrr0 r2
/* 80004598 00000698  7C 9B 02 A6 */	mfsrr1 r4
/* 8000459C 0000069C  7C 60 00 A6 */	mfmsr r3
/* 800045A0 000006A0  60 63 00 30 */	ori r3, r3, 0x30
/* 800045A4 000006A4  7C 7B 03 A6 */	mtsrr1 r3
/* 800045A8 000006A8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 800045AC 000006AC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 800045B0 000006B0  7C 7A 03 A6 */	mtsrr0 r3
/* 800045B4 000006B4  38 60 04 00 */	li r3, 0x0400
/* 800045B8 000006B8  4C 00 00 64 */	rfi 
padslot isi_vector

# Slot 0x0500: External Interrupt Exception
external_interrupt_vector:
/* 80004688 00000788  7C 51 43 A6 */	mtsprg1 r2
/* 8000468C 0000078C  7C 72 43 A6 */	mtsprg2 r3
/* 80004690 00000790  7C 93 43 A6 */	mtsprg3 r4
/* 80004694 00000794  7C 5A 02 A6 */	mfsrr0 r2
/* 80004698 00000798  7C 9B 02 A6 */	mfsrr1 r4
/* 8000469C 0000079C  7C 60 00 A6 */	mfmsr r3
/* 800046A0 000007A0  60 63 00 30 */	ori r3, r3, 0x30
/* 800046A4 000007A4  7C 7B 03 A6 */	mtsrr1 r3
/* 800046A8 000007A8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 800046AC 000007AC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 800046B0 000007B0  7C 7A 03 A6 */	mtsrr0 r3
/* 800046B4 000007B4  38 60 05 00 */	li r3, 0x0500
/* 800046B8 000007B8  4C 00 00 64 */	rfi 
padslot external_interrupt_vector

# Slot 0x0600: Alignment Exception
alignment_vector:
/* 80004788 00000888  7C 51 43 A6 */	mtsprg1 r2
/* 8000478C 0000088C  7C 72 43 A6 */	mtsprg2 r3
/* 80004790 00000890  7C 93 43 A6 */	mtsprg3 r4
/* 80004794 00000894  7C 5A 02 A6 */	mfsrr0 r2
/* 80004798 00000898  7C 9B 02 A6 */	mfsrr1 r4
/* 8000479C 0000089C  7C 60 00 A6 */	mfmsr r3
/* 800047A0 000008A0  60 63 00 30 */	ori r3, r3, 0x30
/* 800047A4 000008A4  7C 7B 03 A6 */	mtsrr1 r3
/* 800047A8 000008A8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 800047AC 000008AC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 800047B0 000008B0  7C 7A 03 A6 */	mtsrr0 r3
/* 800047B4 000008B4  38 60 06 00 */	li r3, 0x0600
/* 800047B8 000008B8  4C 00 00 64 */	rfi 
padslot alignment_vector

# Slot 0x0700: Program Exception
program_vector:
/* 80004888 00000988  7C 51 43 A6 */	mtsprg1 r2
/* 8000488C 0000098C  7C 72 43 A6 */	mtsprg2 r3
/* 80004890 00000990  7C 93 43 A6 */	mtsprg3 r4
/* 80004894 00000994  7C 5A 02 A6 */	mfsrr0 r2
/* 80004898 00000998  7C 9B 02 A6 */	mfsrr1 r4
/* 8000489C 0000099C  7C 60 00 A6 */	mfmsr r3
/* 800048A0 000009A0  60 63 00 30 */	ori r3, r3, 0x30
/* 800048A4 000009A4  7C 7B 03 A6 */	mtsrr1 r3
/* 800048A8 000009A8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 800048AC 000009AC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 800048B0 000009B0  7C 7A 03 A6 */	mtsrr0 r3
/* 800048B4 000009B4  38 60 07 00 */	li r3, 0x0700
/* 800048B8 000009B8  4C 00 00 64 */	rfi 
padslot program_vector

# Slot 0x0800: Floating Point Unavailable Exception
fp_unavailable_vector:
/* 80004988 00000A88  7C 51 43 A6 */	mtsprg1 r2
/* 8000498C 00000A8C  7C 72 43 A6 */	mtsprg2 r3
/* 80004990 00000A90  7C 93 43 A6 */	mtsprg3 r4
/* 80004994 00000A94  7C 5A 02 A6 */	mfsrr0 r2
/* 80004998 00000A98  7C 9B 02 A6 */	mfsrr1 r4
/* 8000499C 00000A9C  7C 60 00 A6 */	mfmsr r3
/* 800049A0 00000AA0  60 63 00 30 */	ori r3, r3, 0x30
/* 800049A4 00000AA4  7C 7B 03 A6 */	mtsrr1 r3
/* 800049A8 00000AA8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 800049AC 00000AAC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 800049B0 00000AB0  7C 7A 03 A6 */	mtsrr0 r3
/* 800049B4 00000AB4  38 60 08 00 */	li r3, 0x0800
/* 800049B8 00000AB8  4C 00 00 64 */	rfi 
padslot fp_unavailable_vector

# Slot 0x0900: Decrementer Exception
decrementer_vector:
/* 80004A88 00000B88  7C 51 43 A6 */	mtsprg1 r2
/* 80004A8C 00000B8C  7C 72 43 A6 */	mtsprg2 r3
/* 80004A90 00000B90  7C 93 43 A6 */	mtsprg3 r4
/* 80004A94 00000B94  7C 5A 02 A6 */	mfsrr0 r2
/* 80004A98 00000B98  7C 9B 02 A6 */	mfsrr1 r4
/* 80004A9C 00000B9C  7C 60 00 A6 */	mfmsr r3
/* 80004AA0 00000BA0  60 63 00 30 */	ori r3, r3, 0x30
/* 80004AA4 00000BA4  7C 7B 03 A6 */	mtsrr1 r3
/* 80004AA8 00000BA8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 80004AAC 00000BAC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 80004AB0 00000BB0  7C 7A 03 A6 */	mtsrr0 r3
/* 80004AB4 00000BB4  38 60 09 00 */	li r3, 0x0900
/* 80004AB8 00000BB8  4C 00 00 64 */	rfi 
padslot decrementer_vector

# Slot 0x0A00: Reserved
slot_0A00:
padslot slot_0A00

# Slot 0x0B00: Reserved
slot_0B00:
padslot slot_0B00

# Slot 0x0C00: System Call Exception
syscall_vector:
/* 80004D88 00000E88  7C 51 43 A6 */	mtsprg1 r2
/* 80004D8C 00000E8C  7C 72 43 A6 */	mtsprg2 r3
/* 80004D90 00000E90  7C 93 43 A6 */	mtsprg3 r4
/* 80004D94 00000E94  7C 5A 02 A6 */	mfsrr0 r2
/* 80004D98 00000E98  7C 9B 02 A6 */	mfsrr1 r4
/* 80004D9C 00000E9C  7C 60 00 A6 */	mfmsr r3
/* 80004DA0 00000EA0  60 63 00 30 */	ori r3, r3, 0x30
/* 80004DA4 00000EA4  7C 7B 03 A6 */	mtsrr1 r3
/* 80004DA8 00000EA8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 80004DAC 00000EAC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 80004DB0 00000EB0  7C 7A 03 A6 */	mtsrr0 r3
/* 80004DB4 00000EB4  38 60 0C 00 */	li r3, 0x0C00
/* 80004DB8 00000EB8  4C 00 00 64 */	rfi 
padslot syscall_vector

# Slot 0x0D00: Trace Exception
trace_vector:
/* 80004E88 00000F88  7C 51 43 A6 */	mtsprg1 r2
/* 80004E8C 00000F8C  7C 72 43 A6 */	mtsprg2 r3
/* 80004E90 00000F90  7C 93 43 A6 */	mtsprg3 r4
/* 80004E94 00000F94  7C 5A 02 A6 */	mfsrr0 r2
/* 80004E98 00000F98  7C 9B 02 A6 */	mfsrr1 r4
/* 80004E9C 00000F9C  7C 60 00 A6 */	mfmsr r3
/* 80004EA0 00000FA0  60 63 00 30 */	ori r3, r3, 0x30
/* 80004EA4 00000FA4  7C 7B 03 A6 */	mtsrr1 r3
/* 80004EA8 00000FA8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 80004EAC 00000FAC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 80004EB0 00000FB0  7C 7A 03 A6 */	mtsrr0 r3
/* 80004EB4 00000FB4  38 60 0D 00 */	li r3, 0x0D00
/* 80004EB8 00000FB8  4C 00 00 64 */	rfi 
padslot trace_vector

# Slot 0x0E00: Performance Monitor Exception
perf_monitor_vector:
/* 80004F88 00001088  7C 51 43 A6 */	mtsprg1 r2
/* 80004F8C 0000108C  7C 72 43 A6 */	mtsprg2 r3
/* 80004F90 00001090  7C 93 43 A6 */	mtsprg3 r4
/* 80004F94 00001094  7C 5A 02 A6 */	mfsrr0 r2
/* 80004F98 00001098  7C 9B 02 A6 */	mfsrr1 r4
/* 80004F9C 0000109C  7C 60 00 A6 */	mfmsr r3
/* 80004FA0 000010A0  60 63 00 30 */	ori r3, r3, 0x30
/* 80004FA4 000010A4  7C 7B 03 A6 */	mtsrr1 r3
/* 80004FA8 000010A8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 80004FAC 000010AC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 80004FB0 000010B0  7C 7A 03 A6 */	mtsrr0 r3
/* 80004FB4 000010B4  38 60 0E 00 */	li r3, 0x0E00
/* 80004FB8 000010B8  4C 00 00 64 */	rfi 
padslot perf_monitor_vector

# Slot 0x0F00: Instruction Address Breakpoint Exception
iabr_vector:
/* 80005088 00001188  48 00 00 54 */	b iabr_vector_sub
.fill 32 - 4
/* 800050A8 000011A8  7C 51 43 A6 */	mtsprg1 r2
/* 800050AC 000011AC  7C 72 43 A6 */	mtsprg2 r3
/* 800050B0 000011B0  7C 93 43 A6 */	mtsprg3 r4
/* 800050B4 000011B4  7C 5A 02 A6 */	mfsrr0 r2
/* 800050B8 000011B8  7C 9B 02 A6 */	mfsrr1 r4
/* 800050BC 000011BC  7C 60 00 A6 */	mfmsr r3
/* 800050C0 000011C0  60 63 00 30 */	ori r3, r3, 0x30
/* 800050C4 000011C4  7C 7B 03 A6 */	mtsrr1 r3
/* 800050C8 000011C8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 800050CC 000011CC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 800050D0 000011D0  7C 7A 03 A6 */	mtsrr0 r3
/* 800050D4 000011D4  38 60 0F 20 */	li r3, 0x0F20
/* 800050D8 000011D8  4C 00 00 64 */	rfi 
iabr_vector_sub:
/* 800050DC 000011DC  7C 51 43 A6 */	mtsprg1 r2
/* 800050E0 000011E0  7C 72 43 A6 */	mtsprg2 r3
/* 800050E4 000011E4  7C 93 43 A6 */	mtsprg3 r4
/* 800050E8 000011E8  7C 5A 02 A6 */	mfsrr0 r2
/* 800050EC 000011EC  7C 9B 02 A6 */	mfsrr1 r4
/* 800050F0 000011F0  7C 60 00 A6 */	mfmsr r3
/* 800050F4 000011F4  60 63 00 30 */	ori r3, r3, 0x30
/* 800050F8 000011F8  7C 7B 03 A6 */	mtsrr1 r3
/* 800050FC 000011FC  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 80005100 00001200  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 80005104 00001204  7C 7A 03 A6 */	mtsrr0 r3
/* 80005108 00001208  38 60 0F 00 */	li r3, 0x0F00
/* 8000510C 0000120C  4C 00 00 64 */	rfi 
padslot iabr_vector

# Slot 0x1000: System Management Interrupt Exception
smi_vector:
/* 80005188 00001288  7C 51 43 A6 */	mtsprg1 r2
/* 8000518C 0000128C  7C 40 00 26 */	mfcr r2
/* 80005190 00001290  7C 52 43 A6 */	mtsprg2 r2
/* 80005194 00001294  7C 40 00 A6 */	mfmsr r2
/* 80005198 00001298  74 42 00 02 */	andis. r2, r2, 2
/* 8000519C 0000129C  41 82 00 1C */	beq smi_ri_not_set
/* 800051A0 000012A0  7C 40 00 A6 */	mfmsr r2
/* 800051A4 000012A4  6C 42 00 02 */	xoris r2, r2, 2
/* 800051A8 000012A8  7C 00 04 AC */	sync 0
/* 800051AC 000012AC  7C 40 01 24 */	mtmsr r2
/* 800051B0 000012B0  7C 00 04 AC */	sync 0
/* 800051B4 000012B4  7C 51 43 A6 */	mtsprg1 r2
smi_ri_not_set:
/* 800051B8 000012B8  7C 52 42 A6 */	mfsprg2 r2
/* 800051BC 000012BC  7C 4F F1 20 */	mtcrf 0xFF, r2
/* 800051C0 000012C0  7C 51 42 A6 */	mfsprg1 r2
/* 800051C4 000012C4  7C 51 43 A6 */	mtsprg1 r2
/* 800051C8 000012C8  7C 72 43 A6 */	mtsprg2 r3
/* 800051CC 000012CC  7C 93 43 A6 */	mtsprg3 r4
/* 800051D0 000012D0  7C 5A 02 A6 */	mfsrr0 r2
/* 800051D4 000012D4  7C 9B 02 A6 */	mfsrr1 r4
/* 800051D8 000012D8  7C 60 00 A6 */	mfmsr r3
/* 800051DC 000012DC  60 63 00 30 */	ori r3, r3, 0x30
/* 800051E0 000012E0  7C 7B 03 A6 */	mtsrr1 r3
/* 800051E4 000012E4  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 800051E8 000012E8  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 800051EC 000012EC  7C 7A 03 A6 */	mtsrr0 r3
/* 800051F0 000012F0  38 60 10 00 */	li r3, 0x1000
/* 800051F4 000012F4  4C 00 00 64 */	rfi 
padslot smi_vector

# Slot 0x1100: Thermal-Management Interrupt Exception
thermal_int_vector:
/* 80005288 00001388  7C 51 43 A6 */	mtsprg1 r2
/* 8000528C 0000138C  7C 40 00 26 */	mfcr r2
/* 80005290 00001390  7C 52 43 A6 */	mtsprg2 r2
/* 80005294 00001394  7C 40 00 A6 */	mfmsr r2
/* 80005298 00001398  74 42 00 02 */	andis. r2, r2, 2
/* 8000529C 0000139C  41 82 00 1C */	beq thermal_int_ri_not_set
/* 800052A0 000013A0  7C 40 00 A6 */	mfmsr r2
/* 800052A4 000013A4  6C 42 00 02 */	xoris r2, r2, 2
/* 800052A8 000013A8  7C 00 04 AC */	sync 0
/* 800052AC 000013AC  7C 40 01 24 */	mtmsr r2
/* 800052B0 000013B0  7C 00 04 AC */	sync 0
/* 800052B4 000013B4  7C 51 43 A6 */	mtsprg1 r2
thermal_int_ri_not_set:
/* 800052B8 000013B8  7C 52 42 A6 */	mfsprg2 r2
/* 800052BC 000013BC  7C 4F F1 20 */	mtcrf 0xFF, r2
/* 800052C0 000013C0  7C 51 42 A6 */	mfsprg1 r2
/* 800052C4 000013C4  7C 51 43 A6 */	mtsprg1 r2
/* 800052C8 000013C8  7C 72 43 A6 */	mtsprg2 r3
/* 800052CC 000013CC  7C 93 43 A6 */	mtsprg3 r4
/* 800052D0 000013D0  7C 5A 02 A6 */	mfsrr0 r2
/* 800052D4 000013D4  7C 9B 02 A6 */	mfsrr1 r4
/* 800052D8 000013D8  7C 60 00 A6 */	mfmsr r3
/* 800052DC 000013DC  60 63 00 30 */	ori r3, r3, 0x30
/* 800052E0 000013E0  7C 7B 03 A6 */	mtsrr1 r3
/* 800052E4 000013E4  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 800052E8 000013E8  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 800052EC 000013EC  7C 7A 03 A6 */	mtsrr0 r3
/* 800052F0 000013F0  38 60 11 00 */	li r3, 0x1100
/* 800052F4 000013F4  4C 00 00 64 */	rfi 
padslot thermal_int_vector

# Slot 0x1200: Unknown
slot_1200:
/* 80005388 00001488  7C 51 43 A6 */	mtsprg1 r2
/* 8000538C 0000148C  7C 40 00 26 */	mfcr r2
/* 80005390 00001490  7C 52 43 A6 */	mtsprg2 r2
/* 80005394 00001494  7C 40 00 A6 */	mfmsr r2
/* 80005398 00001498  74 42 00 02 */	andis. r2, r2, 2
/* 8000539C 0000149C  41 82 00 1C */	beq slot_1200_ri_not_set
/* 800053A0 000014A0  7C 40 00 A6 */	mfmsr r2
/* 800053A4 000014A4  6C 42 00 02 */	xoris r2, r2, 2
/* 800053A8 000014A8  7C 00 04 AC */	sync 0
/* 800053AC 000014AC  7C 40 01 24 */	mtmsr r2
/* 800053B0 000014B0  7C 00 04 AC */	sync 0
/* 800053B4 000014B4  7C 51 43 A6 */	mtsprg1 r2
slot_1200_ri_not_set:
/* 800053B8 000014B8  7C 52 42 A6 */	mfsprg2 r2
/* 800053BC 000014BC  7C 4F F1 20 */	mtcrf 0xFF, r2
/* 800053C0 000014C0  7C 51 42 A6 */	mfsprg1 r2
/* 800053C4 000014C4  7C 51 43 A6 */	mtsprg1 r2
/* 800053C8 000014C8  7C 72 43 A6 */	mtsprg2 r3
/* 800053CC 000014CC  7C 93 43 A6 */	mtsprg3 r4
/* 800053D0 000014D0  7C 5A 02 A6 */	mfsrr0 r2
/* 800053D4 000014D4  7C 9B 02 A6 */	mfsrr1 r4
/* 800053D8 000014D8  7C 60 00 A6 */	mfmsr r3
/* 800053DC 000014DC  60 63 00 30 */	ori r3, r3, 0x30
/* 800053E0 000014E0  7C 7B 03 A6 */	mtsrr1 r3
/* 800053E4 000014E4  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 800053E8 000014E8  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 800053EC 000014EC  7C 7A 03 A6 */	mtsrr0 r3
/* 800053F0 000014F0  38 60 12 00 */	li r3, 0x1200
/* 800053F4 000014F4  4C 00 00 64 */	rfi 
padslot slot_1200

# Slot 0x1300: Unknown
slot_1300:
/* 80005488 00001588  7C 51 43 A6 */	mtsprg1 r2
/* 8000548C 0000158C  7C 72 43 A6 */	mtsprg2 r3
/* 80005490 00001590  7C 93 43 A6 */	mtsprg3 r4
/* 80005494 00001594  7C 5A 02 A6 */	mfsrr0 r2
/* 80005498 00001598  7C 9B 02 A6 */	mfsrr1 r4
/* 8000549C 0000159C  7C 60 00 A6 */	mfmsr r3
/* 800054A0 000015A0  60 63 00 30 */	ori r3, r3, 0x30
/* 800054A4 000015A4  7C 7B 03 A6 */	mtsrr1 r3
/* 800054A8 000015A8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 800054AC 000015AC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 800054B0 000015B0  7C 7A 03 A6 */	mtsrr0 r3
/* 800054B4 000015B4  38 60 13 00 */	li r3, 0x1300
/* 800054B8 000015B8  4C 00 00 64 */	rfi 
padslot slot_1300

# Slot 0x1400: Unknown
slot_1400:
/* 80005588 00001688  7C 51 43 A6 */	mtsprg1 r2
/* 8000558C 0000168C  7C 72 43 A6 */	mtsprg2 r3
/* 80005590 00001690  7C 93 43 A6 */	mtsprg3 r4
/* 80005594 00001694  7C 5A 02 A6 */	mfsrr0 r2
/* 80005598 00001698  7C 9B 02 A6 */	mfsrr1 r4
/* 8000559C 0000169C  7C 60 00 A6 */	mfmsr r3
/* 800055A0 000016A0  60 63 00 30 */	ori r3, r3, 0x30
/* 800055A4 000016A4  7C 7B 03 A6 */	mtsrr1 r3
/* 800055A8 000016A8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 800055AC 000016AC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 800055B0 000016B0  7C 7A 03 A6 */	mtsrr0 r3
/* 800055B4 000016B4  38 60 14 00 */	li r3, 0x1400
/* 800055B8 000016B8  4C 00 00 64 */	rfi 
padslot slot_1400

# Slot 0x1500: Reserved
slot_1500:
padslot slot_1500

# Slot 0x1600: Unknown
slot_1600:
/* 80005788 00001888  7C 51 43 A6 */	mtsprg1 r2
/* 8000578C 0000188C  7C 72 43 A6 */	mtsprg2 r3
/* 80005790 00001890  7C 93 43 A6 */	mtsprg3 r4
/* 80005794 00001894  7C 5A 02 A6 */	mfsrr0 r2
/* 80005798 00001898  7C 9B 02 A6 */	mfsrr1 r4
/* 8000579C 0000189C  7C 60 00 A6 */	mfmsr r3
/* 800057A0 000018A0  60 63 00 30 */	ori r3, r3, 0x30
/* 800057A4 000018A4  7C 7B 03 A6 */	mtsrr1 r3
/* 800057A8 000018A8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 800057AC 000018AC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 800057B0 000018B0  7C 7A 03 A6 */	mtsrr0 r3
/* 800057B4 000018B4  38 60 16 00 */	li r3, 0x1600
/* 800057B8 000018B8  4C 00 00 64 */	rfi 
padslot slot_1600

# Slot 0x1700: Unknown
slot_1700:
/* 80005888 00001988  7C 51 43 A6 */	mtsprg1 r2
/* 8000588C 0000198C  7C 72 43 A6 */	mtsprg2 r3
/* 80005890 00001990  7C 93 43 A6 */	mtsprg3 r4
/* 80005894 00001994  7C 5A 02 A6 */	mfsrr0 r2
/* 80005898 00001998  7C 9B 02 A6 */	mfsrr1 r4
/* 8000589C 0000199C  7C 60 00 A6 */	mfmsr r3
/* 800058A0 000019A0  60 63 00 30 */	ori r3, r3, 0x30
/* 800058A4 000019A4  7C 7B 03 A6 */	mtsrr1 r3
/* 800058A8 000019A8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 800058AC 000019AC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 800058B0 000019B0  7C 7A 03 A6 */	mtsrr0 r3
/* 800058B4 000019B4  38 60 17 00 */	li r3, 0x1700
/* 800058B8 000019B8  4C 00 00 64 */	rfi 
padslot slot_1700

# Slot 0x1800: Reserved
slot_1800:
padslot slot_1800

# Slot 0x1900: Reserved
slot_1900:
padslot slot_1900

# Slot 0x1A00: Reserved
slot_1A00:
padslot slot_1A00

# Slot 0x1B00: Reserved
slot_1B00:
padslot slot_1B00

# Slot 0x1C00: Unknown
slot_1C00:
/* 80005D88 00001E88  7C 51 43 A6 */	mtsprg1 r2
/* 80005D8C 00001E8C  7C 72 43 A6 */	mtsprg2 r3
/* 80005D90 00001E90  7C 93 43 A6 */	mtsprg3 r4
/* 80005D94 00001E94  7C 5A 02 A6 */	mfsrr0 r2
/* 80005D98 00001E98  7C 9B 02 A6 */	mfsrr1 r4
/* 80005D9C 00001E9C  7C 60 00 A6 */	mfmsr r3
/* 80005DA0 00001EA0  60 63 00 30 */	ori r3, r3, 0x30
/* 80005DA4 00001EA4  7C 7B 03 A6 */	mtsrr1 r3
/* 80005DA8 00001EA8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 80005DAC 00001EAC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 80005DB0 00001EB0  7C 7A 03 A6 */	mtsrr0 r3
/* 80005DB4 00001EB4  38 60 1C 00 */	li r3, 0x1C00
/* 80005DB8 00001EB8  4C 00 00 64 */	rfi 
padslot slot_1C00

# Slot 0x1D00: Unknown
slot_1D00:
/* 80005E88 00001F88  7C 51 43 A6 */	mtsprg1 r2
/* 80005E8C 00001F8C  7C 72 43 A6 */	mtsprg2 r3
/* 80005E90 00001F90  7C 93 43 A6 */	mtsprg3 r4
/* 80005E94 00001F94  7C 5A 02 A6 */	mfsrr0 r2
/* 80005E98 00001F98  7C 9B 02 A6 */	mfsrr1 r4
/* 80005E9C 00001F9C  7C 60 00 A6 */	mfmsr r3
/* 80005EA0 00001FA0  60 63 00 30 */	ori r3, r3, 0x30
/* 80005EA4 00001FA4  7C 7B 03 A6 */	mtsrr1 r3
/* 80005EA8 00001FA8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 80005EAC 00001FAC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 80005EB0 00001FB0  7C 7A 03 A6 */	mtsrr0 r3
/* 80005EB4 00001FB4  38 60 1D 00 */	li r3, 0x1D00
/* 80005EB8 00001FB8  4C 00 00 64 */	rfi 
padslot slot_1D00

# Slot 0x1E00: Unknown
slot_1E00:
/* 80005F88 00002088  7C 51 43 A6 */	mtsprg1 r2
/* 80005F8C 0000208C  7C 72 43 A6 */	mtsprg2 r3
/* 80005F90 00002090  7C 93 43 A6 */	mtsprg3 r4
/* 80005F94 00002094  7C 5A 02 A6 */	mfsrr0 r2
/* 80005F98 00002098  7C 9B 02 A6 */	mfsrr1 r4
/* 80005F9C 0000209C  7C 60 00 A6 */	mfmsr r3
/* 80005FA0 000020A0  60 63 00 30 */	ori r3, r3, 0x30
/* 80005FA4 000020A4  7C 7B 03 A6 */	mtsrr1 r3
/* 80005FA8 000020A8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 80005FAC 000020AC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 80005FB0 000020B0  7C 7A 03 A6 */	mtsrr0 r3
/* 80005FB4 000020B4  38 60 1E 00 */	li r3, 0x1E00
/* 80005FB8 000020B8  4C 00 00 64 */	rfi 
padslot slot_1E00

# Slot 0x1F00: Unknown
slot_1F00:
/* 80006088 00002188  7C 51 43 A6 */	mtsprg1 r2
/* 8000608C 0000218C  7C 72 43 A6 */	mtsprg2 r3
/* 80006090 00002190  7C 93 43 A6 */	mtsprg3 r4
/* 80006094 00002194  7C 5A 02 A6 */	mfsrr0 r2
/* 80006098 00002198  7C 9B 02 A6 */	mfsrr1 r4
/* 8000609C 0000219C  7C 60 00 A6 */	mfmsr r3
/* 800060A0 000021A0  60 63 00 30 */	ori r3, r3, 0x30
/* 800060A4 000021A4  7C 7B 03 A6 */	mtsrr1 r3
/* 800060A8 000021A8  3C 60 80 0C */	lis r3, TRKInterruptHandler@h
/* 800060AC 000021AC  60 63 3A F8 */	ori r3, r3, TRKInterruptHandler@l
/* 800060B0 000021B0  7C 7A 03 A6 */	mtsrr0 r3
/* 800060B4 000021B4  38 60 1F 00 */	li r3, 0x1F00
/* 800060B8 000021B8  4C 00 00 64 */	rfi 

.global gTRKInterruptVectorTableEnd
gTRKInterruptVectorTableEnd:
