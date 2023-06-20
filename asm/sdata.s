.include "macros.inc"

.section .sdata, "wa"  # 0x804BD380 - 0x804BE9E0

.balign 0x8

.global lbl_804BD840
lbl_804BD840:
	.incbin "baserom.dol", 0x3C74C0, 0x4
.global lbl_804BD844
lbl_804BD844:
	.incbin "baserom.dol", 0x3C74C4, 0x4
.global lbl_804BD848
lbl_804BD848:
	.incbin "baserom.dol", 0x3C74C8, 0x4
.global lbl_804BD84C
lbl_804BD84C:
	.incbin "baserom.dol", 0x3C74CC, 0x4
.global lbl_804BD850
lbl_804BD850:
	.incbin "baserom.dol", 0x3C74D0, 0x4
.global lbl_804BD854
lbl_804BD854:
	.incbin "baserom.dol", 0x3C74D4, 0x4
.global lbl_804BD858
lbl_804BD858:
	.incbin "baserom.dol", 0x3C74D8, 0x8
.global lbl_804BD860
lbl_804BD860:
	.incbin "baserom.dol", 0x3C74E0, 0x8
.global lbl_804BD868
lbl_804BD868:
	.incbin "baserom.dol", 0x3C74E8, 0x1
.global lbl_804BD869
lbl_804BD869:
	.incbin "baserom.dol", 0x3C74E9, 0x1
.global lbl_804BD86A
lbl_804BD86A:
	.incbin "baserom.dol", 0x3C74EA, 0x1
.global lbl_804BD86B
lbl_804BD86B:
	.incbin "baserom.dol", 0x3C74EB, 0x1
.global lbl_804BD86C
lbl_804BD86C:
	.incbin "baserom.dol", 0x3C74EC, 0x1
.global lbl_804BD86D
lbl_804BD86D:
	.incbin "baserom.dol", 0x3C74ED, 0x1
.global lbl_804BD86E
lbl_804BD86E:
	.incbin "baserom.dol", 0x3C74EE, 0x1
.global lbl_804BD86F
lbl_804BD86F:
	.incbin "baserom.dol", 0x3C74EF, 0x1
.global lbl_804BD870
lbl_804BD870:
	.incbin "baserom.dol", 0x3C74F0, 0x1
.global lbl_804BD871
lbl_804BD871:
	.incbin "baserom.dol", 0x3C74F1, 0x1
.global lbl_804BD872
lbl_804BD872:
	.incbin "baserom.dol", 0x3C74F2, 0x2
.global lbl_804BD874
lbl_804BD874:
	.incbin "baserom.dol", 0x3C74F4, 0x4
.global lbl_804BD878
lbl_804BD878:
	.incbin "baserom.dol", 0x3C74F8, 0x8
.global lbl_804BD880
lbl_804BD880:
	.incbin "baserom.dol", 0x3C7500, 0x8
.global lbl_804BD888
lbl_804BD888:
	.incbin "baserom.dol", 0x3C7508, 0x8
