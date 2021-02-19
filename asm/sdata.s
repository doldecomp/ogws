.include "macros.inc"

.section .sdata, "wa"  # 0x804BD380 - 0x804BE9E0

.balign 0x8

.global lbl_804BD418
lbl_804BD418:
	.long PlayPolicy_Onetime__Q24nw4r3g3dFfff
	.long PlayPolicy_Loop__Q24nw4r3g3dFfff
.balign 0x8

.global lbl_804BD420
lbl_804BD420:
	.single 0e1
.balign 0x8

.global lbl_804BD428
lbl_804BD428:
	.long -1

# pG3DStateIndMtxOp__Q44nw4r3g3d8G3DState23@unnamed@g3d_state_cpp@
.global pG3DStateIndMtxOp__Q44nw4r3g3d8G3DState23$$2unnamed$$2g3d_state_cpp$$2
pG3DStateIndMtxOp__Q44nw4r3g3d8G3DState23$$2unnamed$$2g3d_state_cpp$$2:
	.long 0x803f1620

.global $$28814
$$28814:
	.string "NodeMix"

.global lbl_804BD438
lbl_804BD438:
	.long -4

.global lbl_804BD43C
lbl_804BD43C:
	.long -4

.global lbl_804BD440
lbl_804BD440:
	.long 0x20

.global lbl_804BD444
lbl_804BD444:
	.long 0x20

.global lbl_804BD448
lbl_804BD448:
	.long -4

.global lbl_804BD44C
lbl_804BD44C:
	.long -4

.global lbl_804BD450
lbl_804BD450:
	.string "NodeMix"

.global lbl_804BD458
lbl_804BD458:
	.string "DrawOpa"

.global lbl_804BD460
lbl_804BD460:
	.string "DrawXlu"

# NW4R_G3D_Version___22@unnamed@g3d_init_cpp@
.global NW4R_G3D_Version___22$$2unnamed$$2g3d_init_cpp$$2
NW4R_G3D_Version___22$$2unnamed$$2g3d_init_cpp$$2:
	.long $$27641
.balign 0x8

# NW4R_LYT_Version___22@unnamed@lyt_pane_cpp@
.global NW4R_LYT_Version___22$$2unnamed$$2lyt_pane_cpp$$2
NW4R_LYT_Version___22$$2unnamed$$2lyt_pane_cpp$$2:
	.long lbl_80397140
.balign 0x8

.global lbl_804BD478
lbl_804BD478:
	.incbin "baserom.dol", 0x3C70F8, 0x4
.global lbl_804BD47C
lbl_804BD47C:
	.incbin "baserom.dol", 0x3C70FC, 0x4
.global lbl_804BD480
lbl_804BD480:
	.incbin "baserom.dol", 0x3C7100, 0x4
.global lbl_804BD484
lbl_804BD484:
	.incbin "baserom.dol", 0x3C7104, 0x4
.global lbl_804BD488
lbl_804BD488:
	.incbin "baserom.dol", 0x3C7108, 0x8
.global lbl_804BD490
lbl_804BD490:
	.incbin "baserom.dol", 0x3C7110, 0x8
.global lbl_804BD498
lbl_804BD498:
	.incbin "baserom.dol", 0x3C7118, 0x4
.global lbl_804BD49C
lbl_804BD49C:
	.incbin "baserom.dol", 0x3C711C, 0x4
.global lbl_804BD4A0
lbl_804BD4A0:
	.incbin "baserom.dol", 0x3C7120, 0x8
.global lbl_804BD4A8
lbl_804BD4A8:
	.incbin "baserom.dol", 0x3C7128, 0x8
.global lbl_804BD4B0
lbl_804BD4B0:
	.incbin "baserom.dol", 0x3C7130, 0x4
.global lbl_804BD4B4
lbl_804BD4B4:
	.incbin "baserom.dol", 0x3C7134, 0x4
.global lbl_804BD4B8
lbl_804BD4B8:
	.incbin "baserom.dol", 0x3C7138, 0x8
.global lbl_804BD4C0
lbl_804BD4C0:
	.incbin "baserom.dol", 0x3C7140, 0x8
.global lbl_804BD4C8
lbl_804BD4C8:
	.incbin "baserom.dol", 0x3C7148, 0x8
.global lbl_804BD4D0
lbl_804BD4D0:
	.incbin "baserom.dol", 0x3C7150, 0x8
.global lbl_804BD4D8
lbl_804BD4D8:
	.incbin "baserom.dol", 0x3C7158, 0x4
.global lbl_804BD4DC
lbl_804BD4DC:
	.incbin "baserom.dol", 0x3C715C, 0x4
.global lbl_804BD4E0
lbl_804BD4E0:
	.incbin "baserom.dol", 0x3C7160, 0x8
.global lbl_804BD4E8
lbl_804BD4E8:
	.incbin "baserom.dol", 0x3C7168, 0x4
.global lbl_804BD4EC
lbl_804BD4EC:
	.incbin "baserom.dol", 0x3C716C, 0x4
.global lbl_804BD4F0
lbl_804BD4F0:
	.incbin "baserom.dol", 0x3C7170, 0x8
.global lbl_804BD4F8
lbl_804BD4F8:
	.incbin "baserom.dol", 0x3C7178, 0x8
.global lbl_804BD500
lbl_804BD500:
	.incbin "baserom.dol", 0x3C7180, 0x8
.global lbl_804BD508
lbl_804BD508:
	.incbin "baserom.dol", 0x3C7188, 0x8
.global lbl_804BD510
lbl_804BD510:
	.incbin "baserom.dol", 0x3C7190, 0x8
.global lbl_804BD518
lbl_804BD518:
	.incbin "baserom.dol", 0x3C7198, 0x8
.global lbl_804BD520
lbl_804BD520:
	.incbin "baserom.dol", 0x3C71A0, 0x8
.global lbl_804BD528
lbl_804BD528:
	.incbin "baserom.dol", 0x3C71A8, 0x8
.global lbl_804BD530
lbl_804BD530:
	.incbin "baserom.dol", 0x3C71B0, 0x8
.global lbl_804BD538
lbl_804BD538:
	.incbin "baserom.dol", 0x3C71B8, 0x8
.global lbl_804BD540
lbl_804BD540:
	.incbin "baserom.dol", 0x3C71C0, 0x8
.global lbl_804BD548
lbl_804BD548:
	.incbin "baserom.dol", 0x3C71C8, 0x4
.global lbl_804BD54C
lbl_804BD54C:
	.incbin "baserom.dol", 0x3C71CC, 0x4
.global lbl_804BD550
lbl_804BD550:
	.incbin "baserom.dol", 0x3C71D0, 0x8
.global lbl_804BD558
lbl_804BD558:
	.incbin "baserom.dol", 0x3C71D8, 0x8
.global lbl_804BD560
lbl_804BD560:
	.incbin "baserom.dol", 0x3C71E0, 0x4
.global lbl_804BD564
lbl_804BD564:
	.incbin "baserom.dol", 0x3C71E4, 0x4
.global lbl_804BD568
lbl_804BD568:
	.incbin "baserom.dol", 0x3C71E8, 0x4
.global lbl_804BD56C
lbl_804BD56C:
	.incbin "baserom.dol", 0x3C71EC, 0x4
.global lbl_804BD570
lbl_804BD570:
	.incbin "baserom.dol", 0x3C71F0, 0x4
.global lbl_804BD574
lbl_804BD574:
	.incbin "baserom.dol", 0x3C71F4, 0x4
.global lbl_804BD578
lbl_804BD578:
	.incbin "baserom.dol", 0x3C71F8, 0x4
.global lbl_804BD57C
lbl_804BD57C:
	.incbin "baserom.dol", 0x3C71FC, 0x4
.global lbl_804BD580
lbl_804BD580:
	.incbin "baserom.dol", 0x3C7200, 0x4
.global lbl_804BD584
lbl_804BD584:
	.incbin "baserom.dol", 0x3C7204, 0x4
.global lbl_804BD588
lbl_804BD588:
	.incbin "baserom.dol", 0x3C7208, 0x4
.global lbl_804BD58C
lbl_804BD58C:
	.incbin "baserom.dol", 0x3C720C, 0x4
.global lbl_804BD590
lbl_804BD590:
	.incbin "baserom.dol", 0x3C7210, 0x4
.global lbl_804BD594
lbl_804BD594:
	.incbin "baserom.dol", 0x3C7214, 0x4
.global lbl_804BD598
lbl_804BD598:
	.incbin "baserom.dol", 0x3C7218, 0x4
.global lbl_804BD59C
lbl_804BD59C:
	.incbin "baserom.dol", 0x3C721C, 0x4
.global lbl_804BD5A0
lbl_804BD5A0:
	.incbin "baserom.dol", 0x3C7220, 0x4
.global lbl_804BD5A4
lbl_804BD5A4:
	.incbin "baserom.dol", 0x3C7224, 0x4
.global lbl_804BD5A8
lbl_804BD5A8:
	.incbin "baserom.dol", 0x3C7228, 0x4
.global lbl_804BD5AC
lbl_804BD5AC:
	.incbin "baserom.dol", 0x3C722C, 0x4
.global lbl_804BD5B0
lbl_804BD5B0:
	.incbin "baserom.dol", 0x3C7230, 0x4
.global lbl_804BD5B4
lbl_804BD5B4:
	.incbin "baserom.dol", 0x3C7234, 0x4
.global lbl_804BD5B8
lbl_804BD5B8:
	.incbin "baserom.dol", 0x3C7238, 0x4
.global lbl_804BD5BC
lbl_804BD5BC:
	.incbin "baserom.dol", 0x3C723C, 0x4
.global lbl_804BD5C0
lbl_804BD5C0:
	.incbin "baserom.dol", 0x3C7240, 0x4
.global lbl_804BD5C4
lbl_804BD5C4:
	.incbin "baserom.dol", 0x3C7244, 0x4
.global lbl_804BD5C8
lbl_804BD5C8:
	.incbin "baserom.dol", 0x3C7248, 0x8
.global lbl_804BD5D0
lbl_804BD5D0:
	.incbin "baserom.dol", 0x3C7250, 0x4
.global lbl_804BD5D4
lbl_804BD5D4:
	.incbin "baserom.dol", 0x3C7254, 0x2
.global lbl_804BD5D6
lbl_804BD5D6:
	.incbin "baserom.dol", 0x3C7256, 0x2
.global lbl_804BD5D8
lbl_804BD5D8:
	.incbin "baserom.dol", 0x3C7258, 0x2
.global lbl_804BD5DA
lbl_804BD5DA:
	.incbin "baserom.dol", 0x3C725A, 0x2
.global lbl_804BD5DC
lbl_804BD5DC:
	.incbin "baserom.dol", 0x3C725C, 0x4
.global lbl_804BD5E0
lbl_804BD5E0:
	.incbin "baserom.dol", 0x3C7260, 0x8
.global lbl_804BD5E8
lbl_804BD5E8:
	.incbin "baserom.dol", 0x3C7268, 0x4
.global lbl_804BD5EC
lbl_804BD5EC:
	.incbin "baserom.dol", 0x3C726C, 0x4
.global lbl_804BD5F0
lbl_804BD5F0:
	.incbin "baserom.dol", 0x3C7270, 0x8
.global lbl_804BD5F8
lbl_804BD5F8:
	.incbin "baserom.dol", 0x3C7278, 0x8
.global lbl_804BD600
lbl_804BD600:
	.incbin "baserom.dol", 0x3C7280, 0x4
.global lbl_804BD604
lbl_804BD604:
	.incbin "baserom.dol", 0x3C7284, 0x4
.global lbl_804BD608
lbl_804BD608:
	.incbin "baserom.dol", 0x3C7288, 0x8
.global lbl_804BD610
lbl_804BD610:
	.incbin "baserom.dol", 0x3C7290, 0x8
.global lbl_804BD618
lbl_804BD618:
	.incbin "baserom.dol", 0x3C7298, 0x8
.global lbl_804BD620
lbl_804BD620:
	.incbin "baserom.dol", 0x3C72A0, 0x8
.global lbl_804BD628
lbl_804BD628:
	.incbin "baserom.dol", 0x3C72A8, 0x8
.global lbl_804BD630
lbl_804BD630:
	.incbin "baserom.dol", 0x3C72B0, 0x8
.global lbl_804BD638
lbl_804BD638:
	.incbin "baserom.dol", 0x3C72B8, 0x8
.global lbl_804BD640
lbl_804BD640:
	.incbin "baserom.dol", 0x3C72C0, 0x8
.global lbl_804BD648
lbl_804BD648:
	.incbin "baserom.dol", 0x3C72C8, 0x8
.global lbl_804BD650
lbl_804BD650:
	.incbin "baserom.dol", 0x3C72D0, 0x8
.global lbl_804BD658
lbl_804BD658:
	.incbin "baserom.dol", 0x3C72D8, 0x4
.global lbl_804BD65C
lbl_804BD65C:
	.incbin "baserom.dol", 0x3C72DC, 0x4
.global lbl_804BD660
lbl_804BD660:
	.incbin "baserom.dol", 0x3C72E0, 0x8
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
.global lbl_804BD6E0
lbl_804BD6E0:
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
