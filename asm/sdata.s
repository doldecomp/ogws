.include "macros.inc"

.section .sdata, "wa"  # 0x804BD380 - 0x804BE9E0

.balign 0x8

.global lbl_804BD668
lbl_804BD668:
	.incbin "baserom.dol", 0x3C72E8, 0x4
.global lbl_804BD66C
lbl_804BD66C:
	.incbin "baserom.dol", 0x3C72EC, 0x4
.global lbl_804BD670
lbl_804BD670:
	.incbin "baserom.dol", 0x3C72F0, 0x8
.global lbl_804BD678
lbl_804BD678:
	.incbin "baserom.dol", 0x3C72F8, 0x4
.global lbl_804BD67C
lbl_804BD67C:
	.incbin "baserom.dol", 0x3C72FC, 0x4
.global lbl_804BD680
lbl_804BD680:
	.incbin "baserom.dol", 0x3C7300, 0x4
.global lbl_804BD684
lbl_804BD684:
	.incbin "baserom.dol", 0x3C7304, 0x4
.global lbl_804BD688
lbl_804BD688:
	.incbin "baserom.dol", 0x3C7308, 0x4
.global lbl_804BD68C
lbl_804BD68C:
	.incbin "baserom.dol", 0x3C730C, 0x4
.global lbl_804BD690
lbl_804BD690:
	.incbin "baserom.dol", 0x3C7310, 0x8
.global lbl_804BD698
lbl_804BD698:
	.incbin "baserom.dol", 0x3C7318, 0x8
.global lbl_804BD6A0
lbl_804BD6A0:
	.incbin "baserom.dol", 0x3C7320, 0x4
.global lbl_804BD6A4
lbl_804BD6A4:
	.incbin "baserom.dol", 0x3C7324, 0x14
.global lbl_804BD6B8
lbl_804BD6B8:
	.incbin "baserom.dol", 0x3C7338, 0x4
.global lbl_804BD6BC
lbl_804BD6BC:
	.incbin "baserom.dol", 0x3C733C, 0x8
.global lbl_804BD6C4
lbl_804BD6C4:
	.incbin "baserom.dol", 0x3C7344, 0x4
.global lbl_804BD6C8
lbl_804BD6C8:
	.incbin "baserom.dol", 0x3C7348, 0x10
.global lbl_804BD6D8
lbl_804BD6D8:
	.incbin "baserom.dol", 0x3C7358, 0x8
.global __OSCurrHeap
__OSCurrHeap:
	.incbin "baserom.dol", 0x3C7360, 0x8
.global lbl_804BD6E8
lbl_804BD6E8:
	.incbin "baserom.dol", 0x3C7368, 0x4
.global lbl_804BD6EC
lbl_804BD6EC:
	.incbin "baserom.dol", 0x3C736C, 0x4
.global lbl_804BD6F0
lbl_804BD6F0:
	.incbin "baserom.dol", 0x3C7370, 0x4
.global lbl_804BD6F4
lbl_804BD6F4:
	.incbin "baserom.dol", 0x3C7374, 0x4
.global lbl_804BD6F8
lbl_804BD6F8:
	.incbin "baserom.dol", 0x3C7378, 0x8
.global lbl_804BD700
lbl_804BD700:
	.incbin "baserom.dol", 0x3C7380, 0x8
.global lbl_804BD708
lbl_804BD708:
	.incbin "baserom.dol", 0x3C7388, 0x8
.global lbl_804BD710
lbl_804BD710:
	.incbin "baserom.dol", 0x3C7390, 0x8
.global lbl_804BD718
lbl_804BD718:
	.incbin "baserom.dol", 0x3C7398, 0x8
.global lbl_804BD720
lbl_804BD720:
	.incbin "baserom.dol", 0x3C73A0, 0x8
.global lbl_804BD728
lbl_804BD728:
	.incbin "baserom.dol", 0x3C73A8, 0xF0
.global lbl_804BD818
lbl_804BD818:
	.incbin "baserom.dol", 0x3C7498, 0x8
.global lbl_804BD820
lbl_804BD820:
	.incbin "baserom.dol", 0x3C74A0, 0x8
.global lbl_804BD828
lbl_804BD828:
	.incbin "baserom.dol", 0x3C74A8, 0x8
.global lbl_804BD830
lbl_804BD830:
	.incbin "baserom.dol", 0x3C74B0, 0x4
.global lbl_804BD834
lbl_804BD834:
	.incbin "baserom.dol", 0x3C74B4, 0xC
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
