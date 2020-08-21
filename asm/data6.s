.include "macros.inc"

# .data6 = .bss???

.section .data6, "wa"  # 0x80393A80 - 0x803CAF00
.global lbl_80393A80
lbl_80393A80:
	.incbin "baserom.dol", 0x38FB80, 0x14
.global lbl_80393A94
lbl_80393A94:
	.incbin "baserom.dol", 0x38FB94, 0x14
.global lbl_80393AA8
lbl_80393AA8:
	.incbin "baserom.dol", 0x38FBA8, 0x68
.global lbl_80393B10
lbl_80393B10:
	.incbin "baserom.dol", 0x38FC10, 0x68
.global lbl_80393B78
lbl_80393B78:
	.incbin "baserom.dol", 0x38FC78, 0x60
.global lbl_80393BD8
lbl_80393BD8:
	.incbin "baserom.dol", 0x38FCD8, 0x40
.global lbl_80393C18
lbl_80393C18:
	.incbin "baserom.dol", 0x38FD18, 0x58
.global lbl_80393C70
lbl_80393C70:
	.incbin "baserom.dol", 0x38FD70, 0x68
.global lbl_80393CD8
lbl_80393CD8:
	.incbin "baserom.dol", 0x38FDD8, 0x58
.global lbl_80393D30
lbl_80393D30:
	.incbin "baserom.dol", 0x38FE30, 0x58
.global lbl_80393D88
lbl_80393D88:
	.incbin "baserom.dol", 0x38FE88, 0x18
.global lbl_80393DA0
lbl_80393DA0:
	.incbin "baserom.dol", 0x38FEA0, 0x68
.global lbl_80393E08
lbl_80393E08:
	.incbin "baserom.dol", 0x38FF08, 0x28
.global lbl_80393E30
lbl_80393E30:
	.incbin "baserom.dol", 0x38FF30, 0xB8
.global lbl_80393EE8
lbl_80393EE8:
	.incbin "baserom.dol", 0x38FFE8, 0x20
.global lbl_80393F08
lbl_80393F08:
	.incbin "baserom.dol", 0x390008, 0x2C
.global lbl_80393F34
lbl_80393F34:
	.incbin "baserom.dol", 0x390034, 0xC
.global lbl_80393F40
lbl_80393F40:
	.incbin "baserom.dol", 0x390040, 0x10
.global lbl_80393F50
lbl_80393F50:
	.incbin "baserom.dol", 0x390050, 0x10
.global lbl_80393F60
lbl_80393F60:
	.incbin "baserom.dol", 0x390060, 0x10
.global lbl_80393F70
lbl_80393F70:
	.incbin "baserom.dol", 0x390070, 0x10
.global lbl_80393F80
lbl_80393F80:
	.incbin "baserom.dol", 0x390080, 0x10
.global lbl_80393F90
lbl_80393F90:
	.incbin "baserom.dol", 0x390090, 0x10
.global lbl_80393FA0
lbl_80393FA0:
	.incbin "baserom.dol", 0x3900A0, 0x10
.global lbl_80393FB0
lbl_80393FB0:
	.incbin "baserom.dol", 0x3900B0, 0x1C
.global lbl_80393FCC
lbl_80393FCC:
	.incbin "baserom.dol", 0x3900CC, 0xC
.global lbl_80393FD8
lbl_80393FD8:
	.incbin "baserom.dol", 0x3900D8, 0x18
.global lbl_80393FF0
lbl_80393FF0:
	.incbin "baserom.dol", 0x3900F0, 0x20
.global lbl_80394010
lbl_80394010:
	.incbin "baserom.dol", 0x390110, 0x1C
.global lbl_8039402C
lbl_8039402C:
	.incbin "baserom.dol", 0x39012C, 0x1C
.global lbl_80394048
lbl_80394048:
	.incbin "baserom.dol", 0x390148, 0x18
.global lbl_80394060
lbl_80394060:
	.incbin "baserom.dol", 0x390160, 0x18
.global lbl_80394078
lbl_80394078:
	.incbin "baserom.dol", 0x390178, 0x18
.global lbl_80394090
lbl_80394090:
	.incbin "baserom.dol", 0x390190, 0x64
.global lbl_803940F4
lbl_803940F4:
	.incbin "baserom.dol", 0x3901F4, 0x1C
.global lbl_80394110
lbl_80394110:
	.incbin "baserom.dol", 0x390210, 0x20
.global lbl_80394130
lbl_80394130:
	.incbin "baserom.dol", 0x390230, 0x64
.global lbl_80394194
lbl_80394194:
	.incbin "baserom.dol", 0x390294, 0x1C
.global lbl_803941B0
lbl_803941B0:
	.incbin "baserom.dol", 0x3902B0, 0x20
.global lbl_803941D0
lbl_803941D0:
	.incbin "baserom.dol", 0x3902D0, 0x108
.global lbl_803942D8
lbl_803942D8:
	.incbin "baserom.dol", 0x3903D8, 0x808
.global lbl_80394AE0
lbl_80394AE0:
	.incbin "baserom.dol", 0x390BE0, 0x1010
.global lbl_80395AF0
lbl_80395AF0:
	.incbin "baserom.dol", 0x391BF0, 0x108
.global lbl_80395BF8
lbl_80395BF8:
	.incbin "baserom.dol", 0x391CF8, 0x28
.global lbl_80395C20
lbl_80395C20:
	.incbin "baserom.dol", 0x391D20, 0x70
.global lbl_80395C90
lbl_80395C90:
	.incbin "baserom.dol", 0x391D90, 0x68
.global lbl_80395CF8
lbl_80395CF8:
	.incbin "baserom.dol", 0x391DF8, 0x20
.global lbl_80395D18
lbl_80395D18:
	.incbin "baserom.dol", 0x391E18, 0x20
.global lbl_80395D38
lbl_80395D38:
	.incbin "baserom.dol", 0x391E38, 0x20
.global lbl_80395D58
lbl_80395D58:
	.incbin "baserom.dol", 0x391E58, 0x20
.global lbl_80395D78
lbl_80395D78:
	.incbin "baserom.dol", 0x391E78, 0x20
.global lbl_80395D98
lbl_80395D98:
	.incbin "baserom.dol", 0x391E98, 0x60
.global lbl_80395DF8
lbl_80395DF8:
	.incbin "baserom.dol", 0x391EF8, 0x20
.global lbl_80395E18
lbl_80395E18:
	.incbin "baserom.dol", 0x391F18, 0x28
.global lbl_80395E40
lbl_80395E40:
	.incbin "baserom.dol", 0x391F40, 0x1F8
.global lbl_80396038
lbl_80396038:
	.incbin "baserom.dol", 0x392138, 0x10
.global lbl_80396048
lbl_80396048:
	.incbin "baserom.dol", 0x392148, 0x10
.global lbl_80396058
lbl_80396058:
	.incbin "baserom.dol", 0x392158, 0x18
.global lbl_80396070
lbl_80396070:
	.incbin "baserom.dol", 0x392170, 0x60
.global lbl_803960D0
lbl_803960D0:
	.incbin "baserom.dol", 0x3921D0, 0x38
.global lbl_80396108
lbl_80396108:
	.incbin "baserom.dol", 0x392208, 0x68
.global lbl_80396170
lbl_80396170:
	.incbin "baserom.dol", 0x392270, 0x70
.global lbl_803961E0
lbl_803961E0:
	.incbin "baserom.dol", 0x3922E0, 0x18
.global lbl_803961F8
lbl_803961F8:
	.incbin "baserom.dol", 0x3922F8, 0x10
.global lbl_80396208
lbl_80396208:
	.incbin "baserom.dol", 0x392308, 0x28
.global lbl_80396230
lbl_80396230:
	.incbin "baserom.dol", 0x392330, 0x28
.global lbl_80396258
lbl_80396258:
	.incbin "baserom.dol", 0x392358, 0x18
.global lbl_80396270
lbl_80396270:
	.incbin "baserom.dol", 0x392370, 0x20
.global lbl_80396290
lbl_80396290:
	.incbin "baserom.dol", 0x392390, 0x30
.global lbl_803962C0
lbl_803962C0:
	.incbin "baserom.dol", 0x3923C0, 0x10
.global lbl_803962D0
lbl_803962D0:
	.incbin "baserom.dol", 0x3923D0, 0x10
.global lbl_803962E0
lbl_803962E0:
	.incbin "baserom.dol", 0x3923E0, 0x10
.global lbl_803962F0
lbl_803962F0:
	.incbin "baserom.dol", 0x3923F0, 0x58
.global lbl_80396348
lbl_80396348:
	.incbin "baserom.dol", 0x392448, 0x48
.global lbl_80396390
lbl_80396390:
	.incbin "baserom.dol", 0x392490, 0x18
.global lbl_803963A8
lbl_803963A8:
	.incbin "baserom.dol", 0x3924A8, 0x18
.global lbl_803963C0
lbl_803963C0:
	.incbin "baserom.dol", 0x3924C0, 0x70
.global lbl_80396430
lbl_80396430:
	.incbin "baserom.dol", 0x392530, 0x24
.global lbl_80396454
lbl_80396454:
	.incbin "baserom.dol", 0x392554, 0x14
.global lbl_80396468
lbl_80396468:
	.incbin "baserom.dol", 0x392568, 0x10
.global lbl_80396478
lbl_80396478:
	.incbin "baserom.dol", 0x392578, 0x70
.global lbl_803964E8
lbl_803964E8:
	.incbin "baserom.dol", 0x3925E8, 0x78
.global lbl_80396560
lbl_80396560:
	.incbin "baserom.dol", 0x392660, 0x20
.global lbl_80396580
lbl_80396580:
	.incbin "baserom.dol", 0x392680, 0x20
.global lbl_803965A0
lbl_803965A0:
	.incbin "baserom.dol", 0x3926A0, 0x20
.global lbl_803965C0
lbl_803965C0:
	.incbin "baserom.dol", 0x3926C0, 0x20
.global lbl_803965E0
lbl_803965E0:
	.incbin "baserom.dol", 0x3926E0, 0x20
.global lbl_80396600
lbl_80396600:
	.incbin "baserom.dol", 0x392700, 0x20
.global lbl_80396620
lbl_80396620:
	.incbin "baserom.dol", 0x392720, 0x20
.global lbl_80396640
lbl_80396640:
	.incbin "baserom.dol", 0x392740, 0x20
.global lbl_80396660
lbl_80396660:
	.incbin "baserom.dol", 0x392760, 0x20
.global lbl_80396680
lbl_80396680:
	.incbin "baserom.dol", 0x392780, 0x40
.global lbl_803966C0
lbl_803966C0:
	.incbin "baserom.dol", 0x3927C0, 0x60
.global lbl_80396720
lbl_80396720:
	.incbin "baserom.dol", 0x392820, 0x20
.global lbl_80396740
lbl_80396740:
	.incbin "baserom.dol", 0x392840, 0x20
.global lbl_80396760
lbl_80396760:
	.incbin "baserom.dol", 0x392860, 0x20
.global lbl_80396780
lbl_80396780:
	.incbin "baserom.dol", 0x392880, 0x44
.global lbl_803967C4
lbl_803967C4:
	.incbin "baserom.dol", 0x3928C4, 0x44
.global lbl_80396808
lbl_80396808:
	.incbin "baserom.dol", 0x392908, 0x44
.global lbl_8039684C
lbl_8039684C:
	.incbin "baserom.dol", 0x39294C, 0x44
.global lbl_80396890
lbl_80396890:
	.incbin "baserom.dol", 0x392990, 0x48
.global lbl_803968D8
lbl_803968D8:
	.incbin "baserom.dol", 0x3929D8, 0x48
.global lbl_80396920
lbl_80396920:
	.incbin "baserom.dol", 0x392A20, 0x48
.global lbl_80396968
lbl_80396968:
	.incbin "baserom.dol", 0x392A68, 0x48
.global lbl_803969B0
lbl_803969B0:
	.incbin "baserom.dol", 0x392AB0, 0x48
.global lbl_803969F8
lbl_803969F8:
	.incbin "baserom.dol", 0x392AF8, 0x48
.global lbl_80396A40
lbl_80396A40:
	.incbin "baserom.dol", 0x392B40, 0x48
.global lbl_80396A88
lbl_80396A88:
	.incbin "baserom.dol", 0x392B88, 0x48
.global lbl_80396AD0
lbl_80396AD0:
	.incbin "baserom.dol", 0x392BD0, 0x48
.global lbl_80396B18
lbl_80396B18:
	.incbin "baserom.dol", 0x392C18, 0x48
.global lbl_80396B60
lbl_80396B60:
	.incbin "baserom.dol", 0x392C60, 0x48
.global lbl_80396BA8
lbl_80396BA8:
	.incbin "baserom.dol", 0x392CA8, 0x48
.global lbl_80396BF0
lbl_80396BF0:
	.incbin "baserom.dol", 0x392CF0, 0x58
.global lbl_80396C48
lbl_80396C48:
	.incbin "baserom.dol", 0x392D48, 0x58
.global lbl_80396CA0
lbl_80396CA0:
	.incbin "baserom.dol", 0x392DA0, 0x58
.global lbl_80396CF8
lbl_80396CF8:
	.incbin "baserom.dol", 0x392DF8, 0x58
.global lbl_80396D50
lbl_80396D50:
	.incbin "baserom.dol", 0x392E50, 0x50
.global lbl_80396DA0
lbl_80396DA0:
	.incbin "baserom.dol", 0x392EA0, 0x50
.global lbl_80396DF0
lbl_80396DF0:
	.incbin "baserom.dol", 0x392EF0, 0x50
.global lbl_80396E40
lbl_80396E40:
	.incbin "baserom.dol", 0x392F40, 0x50
.global lbl_80396E90
lbl_80396E90:
	.incbin "baserom.dol", 0x392F90, 0x20
.global lbl_80396EB0
lbl_80396EB0:
	.incbin "baserom.dol", 0x392FB0, 0x18
.global lbl_80396EC8
lbl_80396EC8:
	.incbin "baserom.dol", 0x392FC8, 0x10
.global lbl_80396ED8
lbl_80396ED8:
	.incbin "baserom.dol", 0x392FD8, 0x28
.global lbl_80396F00
lbl_80396F00:
	.incbin "baserom.dol", 0x393000, 0x28
.global lbl_80396F28
lbl_80396F28:
	.incbin "baserom.dol", 0x393028, 0x40
.global lbl_80396F68
lbl_80396F68:
	.incbin "baserom.dol", 0x393068, 0x38
.global lbl_80396FA0
lbl_80396FA0:
	.incbin "baserom.dol", 0x3930A0, 0x28
.global lbl_80396FC8
lbl_80396FC8:
	.incbin "baserom.dol", 0x3930C8, 0x40
.global lbl_80397008
lbl_80397008:
	.incbin "baserom.dol", 0x393108, 0x1C
.global lbl_80397024
lbl_80397024:
	.incbin "baserom.dol", 0x393124, 0xC
.global lbl_80397030
lbl_80397030:
	.incbin "baserom.dol", 0x393130, 0x48
.global lbl_80397078
lbl_80397078:
	.incbin "baserom.dol", 0x393178, 0x90
.global lbl_80397108
lbl_80397108:
	.incbin "baserom.dol", 0x393208, 0x80
.global lbl_80397188
lbl_80397188:
	.incbin "baserom.dol", 0x393288, 0x68
.global lbl_803971F0
lbl_803971F0:
	.incbin "baserom.dol", 0x3932F0, 0x10
.global lbl_80397200
lbl_80397200:
	.incbin "baserom.dol", 0x393300, 0x38
.global lbl_80397238
lbl_80397238:
	.incbin "baserom.dol", 0x393338, 0x68
.global lbl_803972A0
lbl_803972A0:
	.incbin "baserom.dol", 0x3933A0, 0x78
.global lbl_80397318
lbl_80397318:
	.incbin "baserom.dol", 0x393418, 0x3C
.global lbl_80397354
lbl_80397354:
	.incbin "baserom.dol", 0x393454, 0x7C
.global lbl_803973D0
lbl_803973D0:
	.incbin "baserom.dol", 0x3934D0, 0x68
.global lbl_80397438
lbl_80397438:
	.incbin "baserom.dol", 0x393538, 0x20
.global lbl_80397458
lbl_80397458:
	.incbin "baserom.dol", 0x393558, 0x20
.global lbl_80397478
lbl_80397478:
	.incbin "baserom.dol", 0x393578, 0x28
.global lbl_803974A0
lbl_803974A0:
	.incbin "baserom.dol", 0x3935A0, 0x10
.global lbl_803974B0
lbl_803974B0:
	.incbin "baserom.dol", 0x3935B0, 0x20
.global lbl_803974D0
lbl_803974D0:
	.incbin "baserom.dol", 0x3935D0, 0x18
.global lbl_803974E8
lbl_803974E8:
	.incbin "baserom.dol", 0x3935E8, 0x18
.global lbl_80397500
lbl_80397500:
	.incbin "baserom.dol", 0x393600, 0xC
.global lbl_8039750C
lbl_8039750C:
	.incbin "baserom.dol", 0x39360C, 0xC
.global lbl_80397518
lbl_80397518:
	.incbin "baserom.dol", 0x393618, 0x18
.global lbl_80397530
lbl_80397530:
	.incbin "baserom.dol", 0x393630, 0x18
.global lbl_80397548
lbl_80397548:
	.incbin "baserom.dol", 0x393648, 0x20
.global lbl_80397568
lbl_80397568:
	.incbin "baserom.dol", 0x393668, 0x10
.global lbl_80397578
lbl_80397578:
	.incbin "baserom.dol", 0x393678, 0x10
.global lbl_80397588
lbl_80397588:
	.incbin "baserom.dol", 0x393688, 0x38
.global lbl_803975C0
lbl_803975C0:
	.incbin "baserom.dol", 0x3936C0, 0x20
.global lbl_803975E0
lbl_803975E0:
	.incbin "baserom.dol", 0x3936E0, 0x40
.global lbl_80397620
lbl_80397620:
	.incbin "baserom.dol", 0x393720, 0x38
.global lbl_80397658
lbl_80397658:
	.incbin "baserom.dol", 0x393758, 0x48
.global lbl_803976A0
lbl_803976A0:
	.incbin "baserom.dol", 0x3937A0, 0x30
.global lbl_803976D0
lbl_803976D0:
	.incbin "baserom.dol", 0x3937D0, 0xC
.global lbl_803976DC
lbl_803976DC:
	.incbin "baserom.dol", 0x3937DC, 0x14
.global lbl_803976F0
lbl_803976F0:
	.incbin "baserom.dol", 0x3937F0, 0x5C
.global lbl_8039774C
lbl_8039774C:
	.incbin "baserom.dol", 0x39384C, 0x1C
.global lbl_80397768
lbl_80397768:
	.incbin "baserom.dol", 0x393868, 0x48
.global lbl_803977B0
lbl_803977B0:
	.incbin "baserom.dol", 0x3938B0, 0x30
.global lbl_803977E0
lbl_803977E0:
	.incbin "baserom.dol", 0x3938E0, 0x20
.global lbl_80397800
lbl_80397800:
	.incbin "baserom.dol", 0x393900, 0x18
.global lbl_80397818
lbl_80397818:
	.incbin "baserom.dol", 0x393918, 0x1C
.global lbl_80397834
lbl_80397834:
	.incbin "baserom.dol", 0x393934, 0x18
.global lbl_8039784C
lbl_8039784C:
	.incbin "baserom.dol", 0x39394C, 0x20
.global lbl_8039786C
lbl_8039786C:
	.incbin "baserom.dol", 0x39396C, 0x1C
.global lbl_80397888
lbl_80397888:
	.incbin "baserom.dol", 0x393988, 0x30
.global lbl_803978B8
lbl_803978B8:
	.incbin "baserom.dol", 0x3939B8, 0x30
.global lbl_803978E8
lbl_803978E8:
	.incbin "baserom.dol", 0x3939E8, 0x30
.global lbl_80397918
lbl_80397918:
	.incbin "baserom.dol", 0x393A18, 0x18
.global lbl_80397930
lbl_80397930:
	.incbin "baserom.dol", 0x393A30, 0x10
.global lbl_80397940
lbl_80397940:
	.incbin "baserom.dol", 0x393A40, 0x10
.global lbl_80397950
lbl_80397950:
	.incbin "baserom.dol", 0x393A50, 0x48
.global lbl_80397998
lbl_80397998:
	.incbin "baserom.dol", 0x393A98, 0x14
.global lbl_803979AC
lbl_803979AC:
	.incbin "baserom.dol", 0x393AAC, 0x14
.global lbl_803979C0
lbl_803979C0:
	.incbin "baserom.dol", 0x393AC0, 0xA4
.global lbl_80397A64
lbl_80397A64:
	.incbin "baserom.dol", 0x393B64, 0x14
.global lbl_80397A78
lbl_80397A78:
	.incbin "baserom.dol", 0x393B78, 0x64
.global lbl_80397ADC
lbl_80397ADC:
	.incbin "baserom.dol", 0x393BDC, 0x14
.global lbl_80397AF0
lbl_80397AF0:
	.incbin "baserom.dol", 0x393BF0, 0x18
.global lbl_80397B08
lbl_80397B08:
	.incbin "baserom.dol", 0x393C08, 0x20
.global lbl_80397B28
lbl_80397B28:
	.incbin "baserom.dol", 0x393C28, 0xC
.global lbl_80397B34
lbl_80397B34:
	.incbin "baserom.dol", 0x393C34, 0x28
.global lbl_80397B5C
lbl_80397B5C:
	.incbin "baserom.dol", 0x393C5C, 0x1C
.global lbl_80397B78
lbl_80397B78:
	.incbin "baserom.dol", 0x393C78, 0xC
.global lbl_80397B84
lbl_80397B84:
	.incbin "baserom.dol", 0x393C84, 0xC
.global lbl_80397B90
lbl_80397B90:
	.incbin "baserom.dol", 0x393C90, 0x70
.global lbl_80397C00
lbl_80397C00:
	.incbin "baserom.dol", 0x393D00, 0x1C
.global lbl_80397C1C
lbl_80397C1C:
	.incbin "baserom.dol", 0x393D1C, 0x14
.global lbl_80397C30
lbl_80397C30:
	.incbin "baserom.dol", 0x393D30, 0x48
.global lbl_80397C78
lbl_80397C78:
	.incbin "baserom.dol", 0x393D78, 0x28
.global lbl_80397CA0
lbl_80397CA0:
	.incbin "baserom.dol", 0x393DA0, 0x28
.global lbl_80397CC8
lbl_80397CC8:
	.incbin "baserom.dol", 0x393DC8, 0x10
.global lbl_80397CD8
lbl_80397CD8:
	.incbin "baserom.dol", 0x393DD8, 0x10
.global lbl_80397CE8
lbl_80397CE8:
	.incbin "baserom.dol", 0x393DE8, 0x28
.global lbl_80397D10
lbl_80397D10:
	.incbin "baserom.dol", 0x393E10, 0x28
.global lbl_80397D38
lbl_80397D38:
	.incbin "baserom.dol", 0x393E38, 0x28
.global lbl_80397D60
lbl_80397D60:
	.incbin "baserom.dol", 0x393E60, 0x28
.global lbl_80397D88
lbl_80397D88:
	.incbin "baserom.dol", 0x393E88, 0x28
.global lbl_80397DB0
lbl_80397DB0:
	.incbin "baserom.dol", 0x393EB0, 0x28
.global lbl_80397DD8
lbl_80397DD8:
	.incbin "baserom.dol", 0x393ED8, 0x30
.global lbl_80397E08
lbl_80397E08:
	.incbin "baserom.dol", 0x393F08, 0xC
.global lbl_80397E14
lbl_80397E14:
	.incbin "baserom.dol", 0x393F14, 0x14
.global lbl_80397E28
lbl_80397E28:
	.incbin "baserom.dol", 0x393F28, 0x14
.global lbl_80397E3C
lbl_80397E3C:
	.incbin "baserom.dol", 0x393F3C, 0x10
.global lbl_80397E4C
lbl_80397E4C:
	.incbin "baserom.dol", 0x393F4C, 0x10
.global lbl_80397E5C
lbl_80397E5C:
	.incbin "baserom.dol", 0x393F5C, 0x10
.global lbl_80397E6C
lbl_80397E6C:
	.incbin "baserom.dol", 0x393F6C, 0x14
.global lbl_80397E80
lbl_80397E80:
	.incbin "baserom.dol", 0x393F80, 0x20
.global lbl_80397EA0
lbl_80397EA0:
	.incbin "baserom.dol", 0x393FA0, 0x10
.global lbl_80397EB0
lbl_80397EB0:
	.incbin "baserom.dol", 0x393FB0, 0x1C
.global lbl_80397ECC
lbl_80397ECC:
	.incbin "baserom.dol", 0x393FCC, 0x30
.global lbl_80397EFC
lbl_80397EFC:
	.incbin "baserom.dol", 0x393FFC, 0x3C
.global lbl_80397F38
lbl_80397F38:
	.incbin "baserom.dol", 0x394038, 0x1C
.global lbl_80397F54
lbl_80397F54:
	.incbin "baserom.dol", 0x394054, 0x14
.global lbl_80397F68
lbl_80397F68:
	.incbin "baserom.dol", 0x394068, 0x18
.global lbl_80397F80
lbl_80397F80:
	.incbin "baserom.dol", 0x394080, 0x18
.global lbl_80397F98
lbl_80397F98:
	.incbin "baserom.dol", 0x394098, 0x18
.global lbl_80397FB0
lbl_80397FB0:
	.incbin "baserom.dol", 0x3940B0, 0x18
.global lbl_80397FC8
lbl_80397FC8:
	.incbin "baserom.dol", 0x3940C8, 0x1C
.global lbl_80397FE4
lbl_80397FE4:
	.incbin "baserom.dol", 0x3940E4, 0x18
.global lbl_80397FFC
lbl_80397FFC:
	.incbin "baserom.dol", 0x3940FC, 0x14
.global lbl_80398010
lbl_80398010:
	.incbin "baserom.dol", 0x394110, 0x28
.global lbl_80398038
lbl_80398038:
	.incbin "baserom.dol", 0x394138, 0xC
.global lbl_80398044
lbl_80398044:
	.incbin "baserom.dol", 0x394144, 0x18
.global lbl_8039805C
lbl_8039805C:
	.incbin "baserom.dol", 0x39415C, 0x1C
.global lbl_80398078
lbl_80398078:
	.incbin "baserom.dol", 0x394178, 0x14
.global lbl_8039808C
lbl_8039808C:
	.incbin "baserom.dol", 0x39418C, 0x1C
.global lbl_803980A8
lbl_803980A8:
	.incbin "baserom.dol", 0x3941A8, 0x10
.global lbl_803980B8
lbl_803980B8:
	.incbin "baserom.dol", 0x3941B8, 0x30
.global lbl_803980E8
lbl_803980E8:
	.incbin "baserom.dol", 0x3941E8, 0x30
.global lbl_80398118
lbl_80398118:
	.incbin "baserom.dol", 0x394218, 0x30
.global lbl_80398148
lbl_80398148:
	.incbin "baserom.dol", 0x394248, 0x18
.global lbl_80398160
lbl_80398160:
	.incbin "baserom.dol", 0x394260, 0x18
.global lbl_80398178
lbl_80398178:
	.incbin "baserom.dol", 0x394278, 0x38
.global lbl_803981B0
lbl_803981B0:
	.incbin "baserom.dol", 0x3942B0, 0x18
.global lbl_803981C8
lbl_803981C8:
	.incbin "baserom.dol", 0x3942C8, 0x10
.global lbl_803981D8
lbl_803981D8:
	.incbin "baserom.dol", 0x3942D8, 0x28
.global lbl_80398200
lbl_80398200:
	.incbin "baserom.dol", 0x394300, 0x28
.global lbl_80398228
lbl_80398228:
	.incbin "baserom.dol", 0x394328, 0xC
.global lbl_80398234
lbl_80398234:
	.incbin "baserom.dol", 0x394334, 0xC
.global lbl_80398240
lbl_80398240:
	.incbin "baserom.dol", 0x394340, 0x20
.global lbl_80398260
lbl_80398260:
	.incbin "baserom.dol", 0x394360, 0x10
.global lbl_80398270
lbl_80398270:
	.incbin "baserom.dol", 0x394370, 0x1C
.global lbl_8039828C
lbl_8039828C:
	.incbin "baserom.dol", 0x39438C, 0x1C
.global lbl_803982A8
lbl_803982A8:
	.incbin "baserom.dol", 0x3943A8, 0x10
.global lbl_803982B8
lbl_803982B8:
	.incbin "baserom.dol", 0x3943B8, 0x20
.global lbl_803982D8
lbl_803982D8:
	.incbin "baserom.dol", 0x3943D8, 0x24
.global lbl_803982FC
lbl_803982FC:
	.incbin "baserom.dol", 0x3943FC, 0x3C
.global lbl_80398338
lbl_80398338:
	.incbin "baserom.dol", 0x394438, 0x18
.global lbl_80398350
lbl_80398350:
	.incbin "baserom.dol", 0x394450, 0x20
.global lbl_80398370
lbl_80398370:
	.incbin "baserom.dol", 0x394470, 0x28
.global lbl_80398398
lbl_80398398:
	.incbin "baserom.dol", 0x394498, 0x28
.global lbl_803983C0
lbl_803983C0:
	.incbin "baserom.dol", 0x3944C0, 0x68
.global lbl_80398428
lbl_80398428:
	.incbin "baserom.dol", 0x394528, 0x18
.global lbl_80398440
lbl_80398440:
	.incbin "baserom.dol", 0x394540, 0x18
.global lbl_80398458
lbl_80398458:
	.incbin "baserom.dol", 0x394558, 0x10
.global lbl_80398468
lbl_80398468:
	.incbin "baserom.dol", 0x394568, 0x18
.global lbl_80398480
lbl_80398480:
	.incbin "baserom.dol", 0x394580, 0x40
.global lbl_803984C0
lbl_803984C0:
	.incbin "baserom.dol", 0x3945C0, 0x20
.global lbl_803984E0
lbl_803984E0:
	.incbin "baserom.dol", 0x3945E0, 0x20
.global lbl_80398500
lbl_80398500:
	.incbin "baserom.dol", 0x394600, 0x10
.global lbl_80398510
lbl_80398510:
	.incbin "baserom.dol", 0x394610, 0x60
.global lbl_80398570
lbl_80398570:
	.incbin "baserom.dol", 0x394670, 0xB0
.global lbl_80398620
lbl_80398620:
	.incbin "baserom.dol", 0x394720, 0x10
.global lbl_80398630
lbl_80398630:
	.incbin "baserom.dol", 0x394730, 0x10
.global lbl_80398640
lbl_80398640:
	.incbin "baserom.dol", 0x394740, 0x38
.global lbl_80398678
lbl_80398678:
	.incbin "baserom.dol", 0x394778, 0x18
.global lbl_80398690
lbl_80398690:
	.incbin "baserom.dol", 0x394790, 0xA8
.global lbl_80398738
lbl_80398738:
	.incbin "baserom.dol", 0x394838, 0x10
.global lbl_80398748
lbl_80398748:
	.incbin "baserom.dol", 0x394848, 0x18
.global lbl_80398760
lbl_80398760:
	.incbin "baserom.dol", 0x394860, 0x38
.global lbl_80398798
lbl_80398798:
	.incbin "baserom.dol", 0x394898, 0x140
.global lbl_803988D8
lbl_803988D8:
	.incbin "baserom.dol", 0x3949D8, 0x128
.global lbl_80398A00
lbl_80398A00:
	.incbin "baserom.dol", 0x394B00, 0x40
.global lbl_80398A40
lbl_80398A40:
	.incbin "baserom.dol", 0x394B40, 0x1B0
.global lbl_80398BF0
lbl_80398BF0:
	.incbin "baserom.dol", 0x394CF0, 0x48
.global lbl_80398C38
lbl_80398C38:
	.incbin "baserom.dol", 0x394D38, 0x124
.global lbl_80398D5C
lbl_80398D5C:
	.incbin "baserom.dol", 0x394E5C, 0x84
.global lbl_80398DE0
lbl_80398DE0:
	.incbin "baserom.dol", 0x394EE0, 0xA8
.global lbl_80398E88
lbl_80398E88:
	.incbin "baserom.dol", 0x394F88, 0xE0
.global lbl_80398F68
lbl_80398F68:
	.incbin "baserom.dol", 0x395068, 0x20
.global lbl_80398F88
lbl_80398F88:
	.incbin "baserom.dol", 0x395088, 0xA8
.global lbl_80399030
lbl_80399030:
	.incbin "baserom.dol", 0x395130, 0x124
.global lbl_80399154
lbl_80399154:
	.incbin "baserom.dol", 0x395254, 0x84
.global lbl_803991D8
lbl_803991D8:
	.incbin "baserom.dol", 0x3952D8, 0xA8
.global lbl_80399280
lbl_80399280:
	.incbin "baserom.dol", 0x395380, 0x58
.global lbl_803992D8
lbl_803992D8:
	.incbin "baserom.dol", 0x3953D8, 0x70
.global lbl_80399348
lbl_80399348:
	.incbin "baserom.dol", 0x395448, 0x1C
.global lbl_80399364
lbl_80399364:
	.incbin "baserom.dol", 0x395464, 0x1C
.global lbl_80399380
lbl_80399380:
	.incbin "baserom.dol", 0x395480, 0xC
.global lbl_8039938C
lbl_8039938C:
	.incbin "baserom.dol", 0x39548C, 0x10
.global lbl_8039939C
lbl_8039939C:
	.incbin "baserom.dol", 0x39549C, 0x14
.global lbl_803993B0
lbl_803993B0:
	.incbin "baserom.dol", 0x3954B0, 0x40
.global lbl_803993F0
lbl_803993F0:
	.incbin "baserom.dol", 0x3954F0, 0x74
.global lbl_80399464
lbl_80399464:
	.incbin "baserom.dol", 0x395564, 0xC
.global lbl_80399470
lbl_80399470:
	.incbin "baserom.dol", 0x395570, 0x4C
.global lbl_803994BC
lbl_803994BC:
	.incbin "baserom.dol", 0x3955BC, 0x1C
.global lbl_803994D8
lbl_803994D8:
	.incbin "baserom.dol", 0x3955D8, 0x1C
.global lbl_803994F4
lbl_803994F4:
	.incbin "baserom.dol", 0x3955F4, 0x34
.global lbl_80399528
lbl_80399528:
	.incbin "baserom.dol", 0x395628, 0x10
.global lbl_80399538
lbl_80399538:
	.incbin "baserom.dol", 0x395638, 0x28
.global lbl_80399560
lbl_80399560:
	.incbin "baserom.dol", 0x395660, 0x18
.global lbl_80399578
lbl_80399578:
	.incbin "baserom.dol", 0x395678, 0xC
.global lbl_80399584
lbl_80399584:
	.incbin "baserom.dol", 0x395684, 0x38
.global lbl_803995BC
lbl_803995BC:
	.incbin "baserom.dol", 0x3956BC, 0xA4
.global lbl_80399660
lbl_80399660:
	.incbin "baserom.dol", 0x395760, 0x18
.global lbl_80399678
lbl_80399678:
	.incbin "baserom.dol", 0x395778, 0x2C
.global lbl_803996A4
lbl_803996A4:
	.incbin "baserom.dol", 0x3957A4, 0x1C
.global lbl_803996C0
lbl_803996C0:
	.incbin "baserom.dol", 0x3957C0, 0x1C
.global lbl_803996DC
lbl_803996DC:
	.incbin "baserom.dol", 0x3957DC, 0x1C
.global lbl_803996F8
lbl_803996F8:
	.incbin "baserom.dol", 0x3957F8, 0x1C
.global lbl_80399714
lbl_80399714:
	.incbin "baserom.dol", 0x395814, 0x1C
.global lbl_80399730
lbl_80399730:
	.incbin "baserom.dol", 0x395830, 0x28
.global lbl_80399758
lbl_80399758:
	.incbin "baserom.dol", 0x395858, 0x80
.global lbl_803997D8
lbl_803997D8:
	.incbin "baserom.dol", 0x3958D8, 0x290
.global lbl_80399A68
lbl_80399A68:
	.incbin "baserom.dol", 0x395B68, 0xC
.global lbl_80399A74
lbl_80399A74:
	.incbin "baserom.dol", 0x395B74, 0x144
.global lbl_80399BB8
lbl_80399BB8:
	.incbin "baserom.dol", 0x395CB8, 0x1370
.global lbl_8039AF28
lbl_8039AF28:
	.incbin "baserom.dol", 0x397028, 0x38
.global lbl_8039AF60
lbl_8039AF60:
	.incbin "baserom.dol", 0x397060, 0x170
.global lbl_8039B0D0
lbl_8039B0D0:
	.incbin "baserom.dol", 0x3971D0, 0xC0
.global lbl_8039B190
lbl_8039B190:
	.incbin "baserom.dol", 0x397290, 0x10
.global lbl_8039B1A0
lbl_8039B1A0:
	.incbin "baserom.dol", 0x3972A0, 0x18
.global lbl_8039B1B8
lbl_8039B1B8:
	.incbin "baserom.dol", 0x3972B8, 0x18
.global lbl_8039B1D0
lbl_8039B1D0:
	.incbin "baserom.dol", 0x3972D0, 0xD0
.global lbl_8039B2A0
lbl_8039B2A0:
	.incbin "baserom.dol", 0x3973A0, 0x68
.global lbl_8039B308
lbl_8039B308:
	.incbin "baserom.dol", 0x397408, 0x88
.global lbl_8039B390
lbl_8039B390:
	.incbin "baserom.dol", 0x397490, 0x44
.global lbl_8039B3D4
lbl_8039B3D4:
	.incbin "baserom.dol", 0x3974D4, 0x1C
.global lbl_8039B3F0
lbl_8039B3F0:
	.incbin "baserom.dol", 0x3974F0, 0x58
.global lbl_8039B448
lbl_8039B448:
	.incbin "baserom.dol", 0x397548, 0x3C
.global lbl_8039B484
lbl_8039B484:
	.incbin "baserom.dol", 0x397584, 0x3C
.global lbl_8039B4C0
lbl_8039B4C0:
	.incbin "baserom.dol", 0x3975C0, 0x3C
.global lbl_8039B4FC
lbl_8039B4FC:
	.incbin "baserom.dol", 0x3975FC, 0x3C
.global lbl_8039B538
lbl_8039B538:
	.incbin "baserom.dol", 0x397638, 0x20
.global lbl_8039B558
lbl_8039B558:
	.incbin "baserom.dol", 0x397658, 0xF4
.global lbl_8039B64C
lbl_8039B64C:
	.incbin "baserom.dol", 0x39774C, 0xF4
.global lbl_8039B740
lbl_8039B740:
	.incbin "baserom.dol", 0x397840, 0x40
.global lbl_8039B780
lbl_8039B780:
	.incbin "baserom.dol", 0x397880, 0x50
.global lbl_8039B7D0
lbl_8039B7D0:
	.incbin "baserom.dol", 0x3978D0, 0x28
.global lbl_8039B7F8
lbl_8039B7F8:
	.incbin "baserom.dol", 0x3978F8, 0x20
.global lbl_8039B818
lbl_8039B818:
	.incbin "baserom.dol", 0x397918, 0x5C
.global lbl_8039B874
lbl_8039B874:
	.incbin "baserom.dol", 0x397974, 0x94
.global lbl_8039B908
lbl_8039B908:
	.incbin "baserom.dol", 0x397A08, 0xC
.global lbl_8039B914
lbl_8039B914:
	.incbin "baserom.dol", 0x397A14, 0xC
.global lbl_8039B920
lbl_8039B920:
	.incbin "baserom.dol", 0x397A20, 0x60
.global lbl_8039B980
lbl_8039B980:
	.incbin "baserom.dol", 0x397A80, 0x50
.global lbl_8039B9D0
lbl_8039B9D0:
	.incbin "baserom.dol", 0x397AD0, 0xC
.global lbl_8039B9DC
lbl_8039B9DC:
	.incbin "baserom.dol", 0x397ADC, 0xC
.global lbl_8039B9E8
lbl_8039B9E8:
	.incbin "baserom.dol", 0x397AE8, 0xD8
.global lbl_8039BAC0
lbl_8039BAC0:
	.incbin "baserom.dol", 0x397BC0, 0x30
.global lbl_8039BAF0
lbl_8039BAF0:
	.incbin "baserom.dol", 0x397BF0, 0x1F0
.global lbl_8039BCE0
lbl_8039BCE0:
	.incbin "baserom.dol", 0x397DE0, 0x200
.global lbl_8039BEE0
lbl_8039BEE0:
	.incbin "baserom.dol", 0x397FE0, 0x10
.global lbl_8039BEF0
lbl_8039BEF0:
	.incbin "baserom.dol", 0x397FF0, 0x80
.global lbl_8039BF70
lbl_8039BF70:
	.incbin "baserom.dol", 0x398070, 0x238
.global lbl_8039C1A8
lbl_8039C1A8:
	.incbin "baserom.dol", 0x3982A8, 0x1B8
.global lbl_8039C360
lbl_8039C360:
	.incbin "baserom.dol", 0x398460, 0x28
.global lbl_8039C388
lbl_8039C388:
	.incbin "baserom.dol", 0x398488, 0x2DC
.global lbl_8039C664
lbl_8039C664:
	.incbin "baserom.dol", 0x398764, 0x44
.global lbl_8039C6A8
lbl_8039C6A8:
	.incbin "baserom.dol", 0x3987A8, 0x180
.global lbl_8039C828
lbl_8039C828:
	.incbin "baserom.dol", 0x398928, 0x990
.global lbl_8039D1B8
lbl_8039D1B8:
	.incbin "baserom.dol", 0x3992B8, 0x30
.global lbl_8039D1E8
lbl_8039D1E8:
	.incbin "baserom.dol", 0x3992E8, 0x10
.global lbl_8039D1F8
lbl_8039D1F8:
	.incbin "baserom.dol", 0x3992F8, 0xC
.global lbl_8039D204
lbl_8039D204:
	.incbin "baserom.dol", 0x399304, 0x30
.global lbl_8039D234
lbl_8039D234:
	.incbin "baserom.dol", 0x399334, 0x3C
.global lbl_8039D270
lbl_8039D270:
	.incbin "baserom.dol", 0x399370, 0x30
.global lbl_8039D2A0
lbl_8039D2A0:
	.incbin "baserom.dol", 0x3993A0, 0x30
.global lbl_8039D2D0
lbl_8039D2D0:
	.incbin "baserom.dol", 0x3993D0, 0xBA40
.global lbl_803A8D10
lbl_803A8D10:
	.incbin "baserom.dol", 0x3A4E10, 0x400
.global lbl_803A9110
lbl_803A9110:
	.incbin "baserom.dol", 0x3A5210, 0x14
.global lbl_803A9124
lbl_803A9124:
	.incbin "baserom.dol", 0x3A5224, 0x14
.global lbl_803A9138
lbl_803A9138:
	.incbin "baserom.dol", 0x3A5238, 0xC
.global lbl_803A9144
lbl_803A9144:
	.incbin "baserom.dol", 0x3A5244, 0x38
.global lbl_803A917C
lbl_803A917C:
	.incbin "baserom.dol", 0x3A527C, 0x38
.global lbl_803A91B4
lbl_803A91B4:
	.incbin "baserom.dol", 0x3A52B4, 0x24
.global lbl_803A91D8
lbl_803A91D8:
	.incbin "baserom.dol", 0x3A52D8, 0x2C
.global lbl_803A9204
lbl_803A9204:
	.incbin "baserom.dol", 0x3A5304, 0x1C
.global lbl_803A9220
lbl_803A9220:
	.incbin "baserom.dol", 0x3A5320, 0x28
.global lbl_803A9248
lbl_803A9248:
	.incbin "baserom.dol", 0x3A5348, 0x1F8
.global lbl_803A9440
lbl_803A9440:
	.incbin "baserom.dol", 0x3A5540, 0x118
.global lbl_803A9558
lbl_803A9558:
	.incbin "baserom.dol", 0x3A5658, 0x28
.global lbl_803A9580
lbl_803A9580:
	.incbin "baserom.dol", 0x3A5680, 0x48
.global lbl_803A95C8
lbl_803A95C8:
	.incbin "baserom.dol", 0x3A56C8, 0x620
.global lbl_803A9BE8
lbl_803A9BE8:
	.incbin "baserom.dol", 0x3A5CE8, 0x48
.global lbl_803A9C30
lbl_803A9C30:
	.incbin "baserom.dol", 0x3A5D30, 0x1A4
.global lbl_803A9DD4
lbl_803A9DD4:
	.incbin "baserom.dol", 0x3A5ED4, 0x34
.global lbl_803A9E08
lbl_803A9E08:
	.incbin "baserom.dol", 0x3A5F08, 0x10
.global lbl_803A9E18
lbl_803A9E18:
	.incbin "baserom.dol", 0x3A5F18, 0x20
.global lbl_803A9E38
lbl_803A9E38:
	.incbin "baserom.dol", 0x3A5F38, 0x7C
.global lbl_803A9EB4
lbl_803A9EB4:
	.incbin "baserom.dol", 0x3A5FB4, 0x174
.global lbl_803AA028
lbl_803AA028:
	.incbin "baserom.dol", 0x3A6128, 0x20
.global lbl_803AA048
lbl_803AA048:
	.incbin "baserom.dol", 0x3A6148, 0x20
.global lbl_803AA068
lbl_803AA068:
	.incbin "baserom.dol", 0x3A6168, 0x590
.global lbl_803AA5F8
lbl_803AA5F8:
	.incbin "baserom.dol", 0x3A66F8, 0xDC
.global lbl_803AA6D4
lbl_803AA6D4:
	.incbin "baserom.dol", 0x3A67D4, 0x10
.global lbl_803AA6E4
lbl_803AA6E4:
	.incbin "baserom.dol", 0x3A67E4, 0x10
.global lbl_803AA6F4
lbl_803AA6F4:
	.incbin "baserom.dol", 0x3A67F4, 0x24
.global lbl_803AA718
lbl_803AA718:
	.incbin "baserom.dol", 0x3A6818, 0x28
.global lbl_803AA740
lbl_803AA740:
	.incbin "baserom.dol", 0x3A6840, 0x28
.global lbl_803AA768
lbl_803AA768:
	.incbin "baserom.dol", 0x3A6868, 0x20
.global lbl_803AA788
lbl_803AA788:
	.incbin "baserom.dol", 0x3A6888, 0x10C
.global lbl_803AA894
lbl_803AA894:
	.incbin "baserom.dol", 0x3A6994, 0x100
.global lbl_803AA994
lbl_803AA994:
	.incbin "baserom.dol", 0x3A6A94, 0xC
.global lbl_803AA9A0
lbl_803AA9A0:
	.incbin "baserom.dol", 0x3A6AA0, 0x18
.global lbl_803AA9B8
lbl_803AA9B8:
	.incbin "baserom.dol", 0x3A6AB8, 0x14
.global lbl_803AA9CC
lbl_803AA9CC:
	.incbin "baserom.dol", 0x3A6ACC, 0x10
.global lbl_803AA9DC
lbl_803AA9DC:
	.incbin "baserom.dol", 0x3A6ADC, 0x1C
.global lbl_803AA9F8
lbl_803AA9F8:
	.incbin "baserom.dol", 0x3A6AF8, 0x34
.global lbl_803AAA2C
lbl_803AAA2C:
	.incbin "baserom.dol", 0x3A6B2C, 0x30
.global lbl_803AAA5C
lbl_803AAA5C:
	.incbin "baserom.dol", 0x3A6B5C, 0x18
.global lbl_803AAA74
lbl_803AAA74:
	.incbin "baserom.dol", 0x3A6B74, 0x1C
.global lbl_803AAA90
lbl_803AAA90:
	.incbin "baserom.dol", 0x3A6B90, 0x18
.global lbl_803AAAA8
lbl_803AAAA8:
	.incbin "baserom.dol", 0x3A6BA8, 0x1C
.global lbl_803AAAC4
lbl_803AAAC4:
	.incbin "baserom.dol", 0x3A6BC4, 0x1C
.global lbl_803AAAE0
lbl_803AAAE0:
	.incbin "baserom.dol", 0x3A6BE0, 0x1C
.global lbl_803AAAFC
lbl_803AAAFC:
	.incbin "baserom.dol", 0x3A6BFC, 0xBC
.global lbl_803AABB8
lbl_803AABB8:
	.incbin "baserom.dol", 0x3A6CB8, 0x5C
.global lbl_803AAC14
lbl_803AAC14:
	.incbin "baserom.dol", 0x3A6D14, 0x138
.global lbl_803AAD4C
lbl_803AAD4C:
	.incbin "baserom.dol", 0x3A6E4C, 0x18
.global lbl_803AAD64
lbl_803AAD64:
	.incbin "baserom.dol", 0x3A6E64, 0x27C
.global lbl_803AAFE0
lbl_803AAFE0:
	.incbin "baserom.dol", 0x3A70E0, 0x1A0
.global lbl_803AB180
lbl_803AB180:
	.incbin "baserom.dol", 0x3A7280, 0x1C
.global lbl_803AB19C
lbl_803AB19C:
	.incbin "baserom.dol", 0x3A729C, 0x2C4
.global lbl_803AB460
lbl_803AB460:
	.incbin "baserom.dol", 0x3A7560, 0x200
.global lbl_803AB660
lbl_803AB660:
	.incbin "baserom.dol", 0x3A7760, 0x40
.global lbl_803AB6A0
lbl_803AB6A0:
	.incbin "baserom.dol", 0x3A77A0, 0x18
.global lbl_803AB6B8
lbl_803AB6B8:
	.incbin "baserom.dol", 0x3A77B8, 0x14
.global lbl_803AB6CC
lbl_803AB6CC:
	.incbin "baserom.dol", 0x3A77CC, 0x5C
.global lbl_803AB728
lbl_803AB728:
	.incbin "baserom.dol", 0x3A7828, 0x24
.global lbl_803AB74C
lbl_803AB74C:
	.incbin "baserom.dol", 0x3A784C, 0x94
.global lbl_803AB7E0
lbl_803AB7E0:
	.incbin "baserom.dol", 0x3A78E0, 0x80
.global lbl_803AB860
lbl_803AB860:
	.incbin "baserom.dol", 0x3A7960, 0x20
.global lbl_803AB880
lbl_803AB880:
	.incbin "baserom.dol", 0x3A7980, 0xFC0
.global lbl_803AC840
lbl_803AC840:
	.incbin "baserom.dol", 0x3A8940, 0x2000
.global lbl_803AE840
lbl_803AE840:
	.incbin "baserom.dol", 0x3AA940, 0xC0
.global lbl_803AE900
lbl_803AE900:
	.incbin "baserom.dol", 0x3AAA00, 0xE0
.global lbl_803AE9E0
lbl_803AE9E0:
	.incbin "baserom.dol", 0x3AAAE0, 0xC0
.global lbl_803AEAA0
lbl_803AEAA0:
	.incbin "baserom.dol", 0x3AABA0, 0x100
.global lbl_803AEBA0
lbl_803AEBA0:
	.incbin "baserom.dol", 0x3AACA0, 0x200
.global lbl_803AEDA0
lbl_803AEDA0:
	.incbin "baserom.dol", 0x3AAEA0, 0x800
.global lbl_803AF5A0
lbl_803AF5A0:
	.incbin "baserom.dol", 0x3AB6A0, 0x38
.global lbl_803AF5D8
lbl_803AF5D8:
	.incbin "baserom.dol", 0x3AB6D8, 0x18
.global lbl_803AF5F0
lbl_803AF5F0:
	.incbin "baserom.dol", 0x3AB6F0, 0x98
.global lbl_803AF688
lbl_803AF688:
	.incbin "baserom.dol", 0x3AB788, 0x1C
.global lbl_803AF6A4
lbl_803AF6A4:
	.incbin "baserom.dol", 0x3AB7A4, 0x20
.global lbl_803AF6C4
lbl_803AF6C4:
	.incbin "baserom.dol", 0x3AB7C4, 0x44
.global lbl_803AF708
lbl_803AF708:
	.incbin "baserom.dol", 0x3AB808, 0x54
.global lbl_803AF75C
lbl_803AF75C:
	.incbin "baserom.dol", 0x3AB85C, 0x34
.global lbl_803AF790
lbl_803AF790:
	.incbin "baserom.dol", 0x3AB890, 0x5D0
.global lbl_803AFD60
lbl_803AFD60:
	.incbin "baserom.dol", 0x3ABE60, 0x60
.global lbl_803AFDC0
lbl_803AFDC0:
	.incbin "baserom.dol", 0x3ABEC0, 0x718
.global lbl_803B04D8
lbl_803B04D8:
	.incbin "baserom.dol", 0x3AC5D8, 0x14
.global lbl_803B04EC
lbl_803B04EC:
	.incbin "baserom.dol", 0x3AC5EC, 0x24
.global lbl_803B0510
lbl_803B0510:
	.incbin "baserom.dol", 0x3AC610, 0x20
.global lbl_803B0530
lbl_803B0530:
	.incbin "baserom.dol", 0x3AC630, 0x20
.global lbl_803B0550
lbl_803B0550:
	.incbin "baserom.dol", 0x3AC650, 0x40
.global lbl_803B0590
lbl_803B0590:
	.incbin "baserom.dol", 0x3AC690, 0x14
.global lbl_803B05A4
lbl_803B05A4:
	.incbin "baserom.dol", 0x3AC6A4, 0x30
.global lbl_803B05D4
lbl_803B05D4:
	.incbin "baserom.dol", 0x3AC6D4, 0x3C
.global lbl_803B0610
lbl_803B0610:
	.incbin "baserom.dol", 0x3AC710, 0x40
.global lbl_803B0650
lbl_803B0650:
	.incbin "baserom.dol", 0x3AC750, 0x2C
.global lbl_803B067C
lbl_803B067C:
	.incbin "baserom.dol", 0x3AC77C, 0x24
.global lbl_803B06A0
lbl_803B06A0:
	.incbin "baserom.dol", 0x3AC7A0, 0x58
.global lbl_803B06F8
lbl_803B06F8:
	.incbin "baserom.dol", 0x3AC7F8, 0x30
.global lbl_803B0728
lbl_803B0728:
	.incbin "baserom.dol", 0x3AC828, 0x50
.global lbl_803B0778
lbl_803B0778:
	.incbin "baserom.dol", 0x3AC878, 0x20
.global lbl_803B0798
lbl_803B0798:
	.incbin "baserom.dol", 0x3AC898, 0x4C
.global lbl_803B07E4
lbl_803B07E4:
	.incbin "baserom.dol", 0x3AC8E4, 0x114
.global lbl_803B08F8
lbl_803B08F8:
	.incbin "baserom.dol", 0x3AC9F8, 0x28
.global lbl_803B0920
lbl_803B0920:
	.incbin "baserom.dol", 0x3ACA20, 0x84
.global lbl_803B09A4
lbl_803B09A4:
	.incbin "baserom.dol", 0x3ACAA4, 0x28
.global lbl_803B09CC
lbl_803B09CC:
	.incbin "baserom.dol", 0x3ACACC, 0x2C
.global lbl_803B09F8
lbl_803B09F8:
	.incbin "baserom.dol", 0x3ACAF8, 0x10
.global lbl_803B0A08
lbl_803B0A08:
	.incbin "baserom.dol", 0x3ACB08, 0x1C
.global lbl_803B0A24
lbl_803B0A24:
	.incbin "baserom.dol", 0x3ACB24, 0x12C
.global lbl_803B0B50
lbl_803B0B50:
	.incbin "baserom.dol", 0x3ACC50, 0x24
.global lbl_803B0B74
lbl_803B0B74:
	.incbin "baserom.dol", 0x3ACC74, 0x24
.global lbl_803B0B98
lbl_803B0B98:
	.incbin "baserom.dol", 0x3ACC98, 0x30
.global lbl_803B0BC8
lbl_803B0BC8:
	.incbin "baserom.dol", 0x3ACCC8, 0xDC
.global lbl_803B0CA4
lbl_803B0CA4:
	.incbin "baserom.dol", 0x3ACDA4, 0x1C4
.global lbl_803B0E68
lbl_803B0E68:
	.incbin "baserom.dol", 0x3ACF68, 0x40
.global lbl_803B0EA8
lbl_803B0EA8:
	.incbin "baserom.dol", 0x3ACFA8, 0x84
.global lbl_803B0F2C
lbl_803B0F2C:
	.incbin "baserom.dol", 0x3AD02C, 0x23C
.global lbl_803B1168
lbl_803B1168:
	.incbin "baserom.dol", 0x3AD268, 0x40
.global lbl_803B11A8
lbl_803B11A8:
	.incbin "baserom.dol", 0x3AD2A8, 0x20
.global lbl_803B11C8
lbl_803B11C8:
	.incbin "baserom.dol", 0x3AD2C8, 0x180
.global lbl_803B1348
lbl_803B1348:
	.incbin "baserom.dol", 0x3AD448, 0x3C
.global lbl_803B1384
lbl_803B1384:
	.incbin "baserom.dol", 0x3AD484, 0x68
.global lbl_803B13EC
lbl_803B13EC:
	.incbin "baserom.dol", 0x3AD4EC, 0x28
.global lbl_803B1414
lbl_803B1414:
	.incbin "baserom.dol", 0x3AD514, 0x34
.global lbl_803B1448
lbl_803B1448:
	.incbin "baserom.dol", 0x3AD548, 0x3C
.global lbl_803B1484
lbl_803B1484:
	.incbin "baserom.dol", 0x3AD584, 0x30
.global lbl_803B14B4
lbl_803B14B4:
	.incbin "baserom.dol", 0x3AD5B4, 0xD4
.global lbl_803B1588
lbl_803B1588:
	.incbin "baserom.dol", 0x3AD688, 0x30
.global lbl_803B15B8
lbl_803B15B8:
	.incbin "baserom.dol", 0x3AD6B8, 0x6C
.global lbl_803B1624
lbl_803B1624:
	.incbin "baserom.dol", 0x3AD724, 0x40
.global lbl_803B1664
lbl_803B1664:
	.incbin "baserom.dol", 0x3AD764, 0x44
.global lbl_803B16A8
lbl_803B16A8:
	.incbin "baserom.dol", 0x3AD7A8, 0x40
.global lbl_803B16E8
lbl_803B16E8:
	.incbin "baserom.dol", 0x3AD7E8, 0x70
.global lbl_803B1758
lbl_803B1758:
	.incbin "baserom.dol", 0x3AD858, 0x2C
.global lbl_803B1784
lbl_803B1784:
	.incbin "baserom.dol", 0x3AD884, 0x2C
.global lbl_803B17B0
lbl_803B17B0:
	.incbin "baserom.dol", 0x3AD8B0, 0x38
.global lbl_803B17E8
lbl_803B17E8:
	.incbin "baserom.dol", 0x3AD8E8, 0x5C
.global lbl_803B1844
lbl_803B1844:
	.incbin "baserom.dol", 0x3AD944, 0x54
.global lbl_803B1898
lbl_803B1898:
	.incbin "baserom.dol", 0x3AD998, 0x1C
.global lbl_803B18B4
lbl_803B18B4:
	.incbin "baserom.dol", 0x3AD9B4, 0x38
.global lbl_803B18EC
lbl_803B18EC:
	.incbin "baserom.dol", 0x3AD9EC, 0x40
.global lbl_803B192C
lbl_803B192C:
	.incbin "baserom.dol", 0x3ADA2C, 0x20
.global lbl_803B194C
lbl_803B194C:
	.incbin "baserom.dol", 0x3ADA4C, 0x34
.global lbl_803B1980
lbl_803B1980:
	.incbin "baserom.dol", 0x3ADA80, 0x3C
.global lbl_803B19BC
lbl_803B19BC:
	.incbin "baserom.dol", 0x3ADABC, 0x3C
.global lbl_803B19F8
lbl_803B19F8:
	.incbin "baserom.dol", 0x3ADAF8, 0x40
.global lbl_803B1A38
lbl_803B1A38:
	.incbin "baserom.dol", 0x3ADB38, 0x12C
.global lbl_803B1B64
lbl_803B1B64:
	.incbin "baserom.dol", 0x3ADC64, 0x198
.global lbl_803B1CFC
lbl_803B1CFC:
	.incbin "baserom.dol", 0x3ADDFC, 0x3C
.global lbl_803B1D38
lbl_803B1D38:
	.incbin "baserom.dol", 0x3ADE38, 0x98
.global lbl_803B1DD0
lbl_803B1DD0:
	.incbin "baserom.dol", 0x3ADED0, 0x108
.global lbl_803B1ED8
lbl_803B1ED8:
	.incbin "baserom.dol", 0x3ADFD8, 0x60
.global lbl_803B1F38
lbl_803B1F38:
	.incbin "baserom.dol", 0x3AE038, 0xFC
.global lbl_803B2034
lbl_803B2034:
	.incbin "baserom.dol", 0x3AE134, 0x25C
.global lbl_803B2290
lbl_803B2290:
	.incbin "baserom.dol", 0x3AE390, 0x40
.global lbl_803B22D0
lbl_803B22D0:
	.incbin "baserom.dol", 0x3AE3D0, 0x3C
.global lbl_803B230C
lbl_803B230C:
	.incbin "baserom.dol", 0x3AE40C, 0x38
.global lbl_803B2344
lbl_803B2344:
	.incbin "baserom.dol", 0x3AE444, 0x34
.global lbl_803B2378
lbl_803B2378:
	.incbin "baserom.dol", 0x3AE478, 0x30
.global lbl_803B23A8
lbl_803B23A8:
	.incbin "baserom.dol", 0x3AE4A8, 0x34
.global lbl_803B23DC
lbl_803B23DC:
	.incbin "baserom.dol", 0x3AE4DC, 0x44
.global lbl_803B2420
lbl_803B2420:
	.incbin "baserom.dol", 0x3AE520, 0x44
.global lbl_803B2464
lbl_803B2464:
	.incbin "baserom.dol", 0x3AE564, 0x2C
.global lbl_803B2490
lbl_803B2490:
	.incbin "baserom.dol", 0x3AE590, 0x40
.global lbl_803B24D0
lbl_803B24D0:
	.incbin "baserom.dol", 0x3AE5D0, 0x25C
.global lbl_803B272C
lbl_803B272C:
	.incbin "baserom.dol", 0x3AE82C, 0x1C
.global lbl_803B2748
lbl_803B2748:
	.incbin "baserom.dol", 0x3AE848, 0x18
.global lbl_803B2760
lbl_803B2760:
	.incbin "baserom.dol", 0x3AE860, 0x28
.global lbl_803B2788
lbl_803B2788:
	.incbin "baserom.dol", 0x3AE888, 0x20
.global lbl_803B27A8
lbl_803B27A8:
	.incbin "baserom.dol", 0x3AE8A8, 0x30
.global lbl_803B27D8
lbl_803B27D8:
	.incbin "baserom.dol", 0x3AE8D8, 0x44
.global lbl_803B281C
lbl_803B281C:
	.incbin "baserom.dol", 0x3AE91C, 0x2C
.global lbl_803B2848
lbl_803B2848:
	.incbin "baserom.dol", 0x3AE948, 0x28
.global lbl_803B2870
lbl_803B2870:
	.incbin "baserom.dol", 0x3AE970, 0x38
.global lbl_803B28A8
lbl_803B28A8:
	.incbin "baserom.dol", 0x3AE9A8, 0xCC
.global lbl_803B2974
lbl_803B2974:
	.incbin "baserom.dol", 0x3AEA74, 0xAC
.global lbl_803B2A20
lbl_803B2A20:
	.incbin "baserom.dol", 0x3AEB20, 0x44
.global lbl_803B2A64
lbl_803B2A64:
	.incbin "baserom.dol", 0x3AEB64, 0x3C
.global lbl_803B2AA0
lbl_803B2AA0:
	.incbin "baserom.dol", 0x3AEBA0, 0x24
.global lbl_803B2AC4
lbl_803B2AC4:
	.incbin "baserom.dol", 0x3AEBC4, 0x24
.global lbl_803B2AE8
lbl_803B2AE8:
	.incbin "baserom.dol", 0x3AEBE8, 0x44
.global lbl_803B2B2C
lbl_803B2B2C:
	.incbin "baserom.dol", 0x3AEC2C, 0x24
.global lbl_803B2B50
lbl_803B2B50:
	.incbin "baserom.dol", 0x3AEC50, 0x24
.global lbl_803B2B74
lbl_803B2B74:
	.incbin "baserom.dol", 0x3AEC74, 0x24
.global lbl_803B2B98
lbl_803B2B98:
	.incbin "baserom.dol", 0x3AEC98, 0x18
.global lbl_803B2BB0
lbl_803B2BB0:
	.incbin "baserom.dol", 0x3AECB0, 0x18
.global lbl_803B2BC8
lbl_803B2BC8:
	.incbin "baserom.dol", 0x3AECC8, 0x20
.global lbl_803B2BE8
lbl_803B2BE8:
	.incbin "baserom.dol", 0x3AECE8, 0x118
.global lbl_803B2D00
lbl_803B2D00:
	.incbin "baserom.dol", 0x3AEE00, 0x20
.global lbl_803B2D20
lbl_803B2D20:
	.incbin "baserom.dol", 0x3AEE20, 0x24
.global lbl_803B2D44
lbl_803B2D44:
	.incbin "baserom.dol", 0x3AEE44, 0x120
.global lbl_803B2E64
lbl_803B2E64:
	.incbin "baserom.dol", 0x3AEF64, 0xB8
.global lbl_803B2F1C
lbl_803B2F1C:
	.incbin "baserom.dol", 0x3AF01C, 0x2C
.global lbl_803B2F48
lbl_803B2F48:
	.incbin "baserom.dol", 0x3AF048, 0x58
.global lbl_803B2FA0
lbl_803B2FA0:
	.incbin "baserom.dol", 0x3AF0A0, 0x2C
.global lbl_803B2FCC
lbl_803B2FCC:
	.incbin "baserom.dol", 0x3AF0CC, 0x24
.global lbl_803B2FF0
lbl_803B2FF0:
	.incbin "baserom.dol", 0x3AF0F0, 0x30
.global lbl_803B3020
lbl_803B3020:
	.incbin "baserom.dol", 0x3AF120, 0x28
.global lbl_803B3048
lbl_803B3048:
	.incbin "baserom.dol", 0x3AF148, 0x38
.global lbl_803B3080
lbl_803B3080:
	.incbin "baserom.dol", 0x3AF180, 0x38
.global lbl_803B30B8
lbl_803B30B8:
	.incbin "baserom.dol", 0x3AF1B8, 0x30
.global lbl_803B30E8
lbl_803B30E8:
	.incbin "baserom.dol", 0x3AF1E8, 0xA8
.global lbl_803B3190
lbl_803B3190:
	.incbin "baserom.dol", 0x3AF290, 0x34
.global lbl_803B31C4
lbl_803B31C4:
	.incbin "baserom.dol", 0x3AF2C4, 0x27C
.global lbl_803B3440
lbl_803B3440:
	.incbin "baserom.dol", 0x3AF540, 0x20
.global lbl_803B3460
lbl_803B3460:
	.incbin "baserom.dol", 0x3AF560, 0x2C
.global lbl_803B348C
lbl_803B348C:
	.incbin "baserom.dol", 0x3AF58C, 0x2C
.global lbl_803B34B8
lbl_803B34B8:
	.incbin "baserom.dol", 0x3AF5B8, 0x2C
.global lbl_803B34E4
lbl_803B34E4:
	.incbin "baserom.dol", 0x3AF5E4, 0x24
.global lbl_803B3508
lbl_803B3508:
	.incbin "baserom.dol", 0x3AF608, 0x2C
.global lbl_803B3534
lbl_803B3534:
	.incbin "baserom.dol", 0x3AF634, 0x24
.global lbl_803B3558
lbl_803B3558:
	.incbin "baserom.dol", 0x3AF658, 0x160
.global lbl_803B36B8
lbl_803B36B8:
	.incbin "baserom.dol", 0x3AF7B8, 0x1C0
.global lbl_803B3878
lbl_803B3878:
	.incbin "baserom.dol", 0x3AF978, 0x40
.global lbl_803B38B8
lbl_803B38B8:
	.incbin "baserom.dol", 0x3AF9B8, 0x80
.global lbl_803B3938
lbl_803B3938:
	.incbin "baserom.dol", 0x3AFA38, 0xA4
.global lbl_803B39DC
lbl_803B39DC:
	.incbin "baserom.dol", 0x3AFADC, 0x6C
.global lbl_803B3A48
lbl_803B3A48:
	.incbin "baserom.dol", 0x3AFB48, 0x28
.global lbl_803B3A70
lbl_803B3A70:
	.incbin "baserom.dol", 0x3AFB70, 0x30
.global lbl_803B3AA0
lbl_803B3AA0:
	.incbin "baserom.dol", 0x3AFBA0, 0x168
.global lbl_803B3C08
lbl_803B3C08:
	.incbin "baserom.dol", 0x3AFD08, 0x70
.global lbl_803B3C78
lbl_803B3C78:
	.incbin "baserom.dol", 0x3AFD78, 0x24
.global lbl_803B3C9C
lbl_803B3C9C:
	.incbin "baserom.dol", 0x3AFD9C, 0x194
.global lbl_803B3E30
lbl_803B3E30:
	.incbin "baserom.dol", 0x3AFF30, 0x8C
.global lbl_803B3EBC
lbl_803B3EBC:
	.incbin "baserom.dol", 0x3AFFBC, 0xC4
.global lbl_803B3F80
lbl_803B3F80:
	.incbin "baserom.dol", 0x3B0080, 0x70
.global lbl_803B3FF0
lbl_803B3FF0:
	.incbin "baserom.dol", 0x3B00F0, 0x28
.global lbl_803B4018
lbl_803B4018:
	.incbin "baserom.dol", 0x3B0118, 0x98
.global lbl_803B40B0
lbl_803B40B0:
	.incbin "baserom.dol", 0x3B01B0, 0x20
.global lbl_803B40D0
lbl_803B40D0:
	.incbin "baserom.dol", 0x3B01D0, 0x28
.global lbl_803B40F8
lbl_803B40F8:
	.incbin "baserom.dol", 0x3B01F8, 0x28
.global lbl_803B4120
lbl_803B4120:
	.incbin "baserom.dol", 0x3B0220, 0x34
.global lbl_803B4154
lbl_803B4154:
	.incbin "baserom.dol", 0x3B0254, 0x28
.global lbl_803B417C
lbl_803B417C:
	.incbin "baserom.dol", 0x3B027C, 0x12C
.global lbl_803B42A8
lbl_803B42A8:
	.incbin "baserom.dol", 0x3B03A8, 0x20
.global lbl_803B42C8
lbl_803B42C8:
	.incbin "baserom.dol", 0x3B03C8, 0x20
.global lbl_803B42E8
lbl_803B42E8:
	.incbin "baserom.dol", 0x3B03E8, 0x38
.global lbl_803B4320
lbl_803B4320:
	.incbin "baserom.dol", 0x3B0420, 0x2D4
.global lbl_803B45F4
lbl_803B45F4:
	.incbin "baserom.dol", 0x3B06F4, 0x14
.global lbl_803B4608
lbl_803B4608:
	.incbin "baserom.dol", 0x3B0708, 0x18
.global lbl_803B4620
lbl_803B4620:
	.incbin "baserom.dol", 0x3B0720, 0x1C
.global lbl_803B463C
lbl_803B463C:
	.incbin "baserom.dol", 0x3B073C, 0x20
.global lbl_803B465C
lbl_803B465C:
	.incbin "baserom.dol", 0x3B075C, 0x20
.global lbl_803B467C
lbl_803B467C:
	.incbin "baserom.dol", 0x3B077C, 0x64
.global lbl_803B46E0
lbl_803B46E0:
	.incbin "baserom.dol", 0x3B07E0, 0x28
.global lbl_803B4708
lbl_803B4708:
	.incbin "baserom.dol", 0x3B0808, 0x38
.global lbl_803B4740
lbl_803B4740:
	.incbin "baserom.dol", 0x3B0840, 0x38
.global lbl_803B4778
lbl_803B4778:
	.incbin "baserom.dol", 0x3B0878, 0x10
.global lbl_803B4788
lbl_803B4788:
	.incbin "baserom.dol", 0x3B0888, 0x20
.global lbl_803B47A8
lbl_803B47A8:
	.incbin "baserom.dol", 0x3B08A8, 0x20
.global lbl_803B47C8
lbl_803B47C8:
	.incbin "baserom.dol", 0x3B08C8, 0x2C
.global lbl_803B47F4
lbl_803B47F4:
	.incbin "baserom.dol", 0x3B08F4, 0x24
.global lbl_803B4818
lbl_803B4818:
	.incbin "baserom.dol", 0x3B0918, 0x30
.global lbl_803B4848
lbl_803B4848:
	.incbin "baserom.dol", 0x3B0948, 0x60
.global lbl_803B48A8
lbl_803B48A8:
	.incbin "baserom.dol", 0x3B09A8, 0x10
.global lbl_803B48B8
lbl_803B48B8:
	.incbin "baserom.dol", 0x3B09B8, 0x40
.global lbl_803B48F8
lbl_803B48F8:
	.incbin "baserom.dol", 0x3B09F8, 0x10
.global lbl_803B4908
lbl_803B4908:
	.incbin "baserom.dol", 0x3B0A08, 0x14
.global lbl_803B491C
lbl_803B491C:
	.incbin "baserom.dol", 0x3B0A1C, 0x14
.global lbl_803B4930
lbl_803B4930:
	.incbin "baserom.dol", 0x3B0A30, 0x10
.global lbl_803B4940
lbl_803B4940:
	.incbin "baserom.dol", 0x3B0A40, 0x18
.global lbl_803B4958
lbl_803B4958:
	.incbin "baserom.dol", 0x3B0A58, 0x24
.global lbl_803B497C
lbl_803B497C:
	.incbin "baserom.dol", 0x3B0A7C, 0x34
.global lbl_803B49B0
lbl_803B49B0:
	.incbin "baserom.dol", 0x3B0AB0, 0x2C
.global lbl_803B49DC
lbl_803B49DC:
	.incbin "baserom.dol", 0x3B0ADC, 0x2C
.global lbl_803B4A08
lbl_803B4A08:
	.incbin "baserom.dol", 0x3B0B08, 0x30
.global lbl_803B4A38
lbl_803B4A38:
	.incbin "baserom.dol", 0x3B0B38, 0x100
.global lbl_803B4B38
lbl_803B4B38:
	.incbin "baserom.dol", 0x3B0C38, 0x18
.global lbl_803B4B50
lbl_803B4B50:
	.incbin "baserom.dol", 0x3B0C50, 0x30
.global lbl_803B4B80
lbl_803B4B80:
	.incbin "baserom.dol", 0x3B0C80, 0x140
.global lbl_803B4CC0
lbl_803B4CC0:
	.incbin "baserom.dol", 0x3B0DC0, 0x70
.global lbl_803B4D30
lbl_803B4D30:
	.incbin "baserom.dol", 0x3B0E30, 0x28
.global lbl_803B4D58
lbl_803B4D58:
	.incbin "baserom.dol", 0x3B0E58, 0x80
.global lbl_803B4DD8
lbl_803B4DD8:
	.incbin "baserom.dol", 0x3B0ED8, 0x48
.global lbl_803B4E20
lbl_803B4E20:
	.incbin "baserom.dol", 0x3B0F20, 0x3C
.global lbl_803B4E5C
lbl_803B4E5C:
	.incbin "baserom.dol", 0x3B0F5C, 0x24
.global lbl_803B4E80
lbl_803B4E80:
	.incbin "baserom.dol", 0x3B0F80, 0x24
.global lbl_803B4EA4
lbl_803B4EA4:
	.incbin "baserom.dol", 0x3B0FA4, 0x30
.global lbl_803B4ED4
lbl_803B4ED4:
	.incbin "baserom.dol", 0x3B0FD4, 0x28
.global lbl_803B4EFC
lbl_803B4EFC:
	.incbin "baserom.dol", 0x3B0FFC, 0x3C
.global lbl_803B4F38
lbl_803B4F38:
	.incbin "baserom.dol", 0x3B1038, 0x24
.global lbl_803B4F5C
lbl_803B4F5C:
	.incbin "baserom.dol", 0x3B105C, 0x1C
.global lbl_803B4F78
lbl_803B4F78:
	.incbin "baserom.dol", 0x3B1078, 0x14
.global lbl_803B4F8C
lbl_803B4F8C:
	.incbin "baserom.dol", 0x3B108C, 0x20
.global lbl_803B4FAC
lbl_803B4FAC:
	.incbin "baserom.dol", 0x3B10AC, 0x24
.global lbl_803B4FD0
lbl_803B4FD0:
	.incbin "baserom.dol", 0x3B10D0, 0x3C
.global lbl_803B500C
lbl_803B500C:
	.incbin "baserom.dol", 0x3B110C, 0x2C
.global lbl_803B5038
lbl_803B5038:
	.incbin "baserom.dol", 0x3B1138, 0x98
.global lbl_803B50D0
lbl_803B50D0:
	.incbin "baserom.dol", 0x3B11D0, 0xA0
.global lbl_803B5170
lbl_803B5170:
	.incbin "baserom.dol", 0x3B1270, 0x40
.global lbl_803B51B0
lbl_803B51B0:
	.incbin "baserom.dol", 0x3B12B0, 0x24
.global lbl_803B51D4
lbl_803B51D4:
	.incbin "baserom.dol", 0x3B12D4, 0x3C
.global lbl_803B5210
lbl_803B5210:
	.incbin "baserom.dol", 0x3B1310, 0x2C
.global lbl_803B523C
lbl_803B523C:
	.incbin "baserom.dol", 0x3B133C, 0x3C
.global lbl_803B5278
lbl_803B5278:
	.incbin "baserom.dol", 0x3B1378, 0x28
.global lbl_803B52A0
lbl_803B52A0:
	.incbin "baserom.dol", 0x3B13A0, 0xD8
.global lbl_803B5378
lbl_803B5378:
	.incbin "baserom.dol", 0x3B1478, 0x10
.global lbl_803B5388
lbl_803B5388:
	.incbin "baserom.dol", 0x3B1488, 0x20
.global lbl_803B53A8
lbl_803B53A8:
	.incbin "baserom.dol", 0x3B14A8, 0x24
.global lbl_803B53CC
lbl_803B53CC:
	.incbin "baserom.dol", 0x3B14CC, 0x24
.global lbl_803B53F0
lbl_803B53F0:
	.incbin "baserom.dol", 0x3B14F0, 0x18
.global lbl_803B5408
lbl_803B5408:
	.incbin "baserom.dol", 0x3B1508, 0x50
.global lbl_803B5458
lbl_803B5458:
	.incbin "baserom.dol", 0x3B1558, 0x3C
.global lbl_803B5494
lbl_803B5494:
	.incbin "baserom.dol", 0x3B1594, 0x5C
.global lbl_803B54F0
lbl_803B54F0:
	.incbin "baserom.dol", 0x3B15F0, 0x28
.global lbl_803B5518
lbl_803B5518:
	.incbin "baserom.dol", 0x3B1618, 0x28
.global lbl_803B5540
lbl_803B5540:
	.incbin "baserom.dol", 0x3B1640, 0xE8
.global lbl_803B5628
lbl_803B5628:
	.incbin "baserom.dol", 0x3B1728, 0x28
.global lbl_803B5650
lbl_803B5650:
	.incbin "baserom.dol", 0x3B1750, 0x78
.global lbl_803B56C8
lbl_803B56C8:
	.incbin "baserom.dol", 0x3B17C8, 0xC0
.global lbl_803B5788
lbl_803B5788:
	.incbin "baserom.dol", 0x3B1888, 0x2C
.global lbl_803B57B4
lbl_803B57B4:
	.incbin "baserom.dol", 0x3B18B4, 0x58
.global lbl_803B580C
lbl_803B580C:
	.incbin "baserom.dol", 0x3B190C, 0x1C
.global lbl_803B5828
lbl_803B5828:
	.incbin "baserom.dol", 0x3B1928, 0x2C
.global lbl_803B5854
lbl_803B5854:
	.incbin "baserom.dol", 0x3B1954, 0x24
.global lbl_803B5878
lbl_803B5878:
	.incbin "baserom.dol", 0x3B1978, 0x38
.global lbl_803B58B0
lbl_803B58B0:
	.incbin "baserom.dol", 0x3B19B0, 0x78
.global lbl_803B5928
lbl_803B5928:
	.incbin "baserom.dol", 0x3B1A28, 0x30
.global lbl_803B5958
lbl_803B5958:
	.incbin "baserom.dol", 0x3B1A58, 0x28
.global lbl_803B5980
lbl_803B5980:
	.incbin "baserom.dol", 0x3B1A80, 0x30
.global lbl_803B59B0
lbl_803B59B0:
	.incbin "baserom.dol", 0x3B1AB0, 0x24
.global lbl_803B59D4
lbl_803B59D4:
	.incbin "baserom.dol", 0x3B1AD4, 0x1C
.global lbl_803B59F0
lbl_803B59F0:
	.incbin "baserom.dol", 0x3B1AF0, 0x44
.global lbl_803B5A34
lbl_803B5A34:
	.incbin "baserom.dol", 0x3B1B34, 0x38
.global lbl_803B5A6C
lbl_803B5A6C:
	.incbin "baserom.dol", 0x3B1B6C, 0x3C
.global lbl_803B5AA8
lbl_803B5AA8:
	.incbin "baserom.dol", 0x3B1BA8, 0x20
.global lbl_803B5AC8
lbl_803B5AC8:
	.incbin "baserom.dol", 0x3B1BC8, 0x20
.global lbl_803B5AE8
lbl_803B5AE8:
	.incbin "baserom.dol", 0x3B1BE8, 0x18
.global lbl_803B5B00
lbl_803B5B00:
	.incbin "baserom.dol", 0x3B1C00, 0x80
.global lbl_803B5B80
lbl_803B5B80:
	.incbin "baserom.dol", 0x3B1C80, 0x208
.global lbl_803B5D88
lbl_803B5D88:
	.incbin "baserom.dol", 0x3B1E88, 0x38
.global lbl_803B5DC0
lbl_803B5DC0:
	.incbin "baserom.dol", 0x3B1EC0, 0x34
.global lbl_803B5DF4
lbl_803B5DF4:
	.incbin "baserom.dol", 0x3B1EF4, 0x7C
.global lbl_803B5E70
lbl_803B5E70:
	.incbin "baserom.dol", 0x3B1F70, 0x34
.global lbl_803B5EA4
lbl_803B5EA4:
	.incbin "baserom.dol", 0x3B1FA4, 0x9C
.global lbl_803B5F40
lbl_803B5F40:
	.incbin "baserom.dol", 0x3B2040, 0xA8
.global lbl_803B5FE8
lbl_803B5FE8:
	.incbin "baserom.dol", 0x3B20E8, 0x98
.global lbl_803B6080
lbl_803B6080:
	.incbin "baserom.dol", 0x3B2180, 0x38
.global lbl_803B60B8
lbl_803B60B8:
	.incbin "baserom.dol", 0x3B21B8, 0x1C
.global lbl_803B60D4
lbl_803B60D4:
	.incbin "baserom.dol", 0x3B21D4, 0x4C4
.global lbl_803B6598
lbl_803B6598:
	.incbin "baserom.dol", 0x3B2698, 0xC40
.global lbl_803B71D8
lbl_803B71D8:
	.incbin "baserom.dol", 0x3B32D8, 0x18
.global lbl_803B71F0
lbl_803B71F0:
	.incbin "baserom.dol", 0x3B32F0, 0x10
.global lbl_803B7200
lbl_803B7200:
	.incbin "baserom.dol", 0x3B3300, 0x98
.global lbl_803B7298
lbl_803B7298:
	.incbin "baserom.dol", 0x3B3398, 0x30
.global lbl_803B72C8
lbl_803B72C8:
	.incbin "baserom.dol", 0x3B33C8, 0x38
.global lbl_803B7300
lbl_803B7300:
	.incbin "baserom.dol", 0x3B3400, 0x340
.global lbl_803B7640
lbl_803B7640:
	.incbin "baserom.dol", 0x3B3740, 0x7C
.global lbl_803B76BC
lbl_803B76BC:
	.incbin "baserom.dol", 0x3B37BC, 0x10
.global lbl_803B76CC
lbl_803B76CC:
	.incbin "baserom.dol", 0x3B37CC, 0x58
.global lbl_803B7724
lbl_803B7724:
	.incbin "baserom.dol", 0x3B3824, 0xC4
.global lbl_803B77E8
lbl_803B77E8:
	.incbin "baserom.dol", 0x3B38E8, 0x10
.global lbl_803B77F8
lbl_803B77F8:
	.incbin "baserom.dol", 0x3B38F8, 0x10
.global lbl_803B7808
lbl_803B7808:
	.incbin "baserom.dol", 0x3B3908, 0x10
.global lbl_803B7818
lbl_803B7818:
	.incbin "baserom.dol", 0x3B3918, 0x50
.global lbl_803B7868
lbl_803B7868:
	.incbin "baserom.dol", 0x3B3968, 0x14
.global lbl_803B787C
lbl_803B787C:
	.incbin "baserom.dol", 0x3B397C, 0x12C
.global lbl_803B79A8
lbl_803B79A8:
	.incbin "baserom.dol", 0x3B3AA8, 0x28
.global lbl_803B79D0
lbl_803B79D0:
	.incbin "baserom.dol", 0x3B3AD0, 0x28
.global lbl_803B79F8
lbl_803B79F8:
	.incbin "baserom.dol", 0x3B3AF8, 0xD8
.global lbl_803B7AD0
lbl_803B7AD0:
	.incbin "baserom.dol", 0x3B3BD0, 0x40
.global lbl_803B7B10
lbl_803B7B10:
	.incbin "baserom.dol", 0x3B3C10, 0x58
.global lbl_803B7B68
lbl_803B7B68:
	.incbin "baserom.dol", 0x3B3C68, 0x10
.global lbl_803B7B78
lbl_803B7B78:
	.incbin "baserom.dol", 0x3B3C78, 0x10
.global lbl_803B7B88
lbl_803B7B88:
	.incbin "baserom.dol", 0x3B3C88, 0x110
.global lbl_803B7C98
lbl_803B7C98:
	.incbin "baserom.dol", 0x3B3D98, 0x18
.global lbl_803B7CB0
lbl_803B7CB0:
	.incbin "baserom.dol", 0x3B3DB0, 0x30
.global lbl_803B7CE0
lbl_803B7CE0:
	.incbin "baserom.dol", 0x3B3DE0, 0x28
.global lbl_803B7D08
lbl_803B7D08:
	.incbin "baserom.dol", 0x3B3E08, 0x10
.global lbl_803B7D18
lbl_803B7D18:
	.incbin "baserom.dol", 0x3B3E18, 0x10
.global lbl_803B7D28
lbl_803B7D28:
	.incbin "baserom.dol", 0x3B3E28, 0xC
.global lbl_803B7D34
lbl_803B7D34:
	.incbin "baserom.dol", 0x3B3E34, 0xE4
.global lbl_803B7E18
lbl_803B7E18:
	.incbin "baserom.dol", 0x3B3F18, 0x14
.global lbl_803B7E2C
lbl_803B7E2C:
	.incbin "baserom.dol", 0x3B3F2C, 0x1C
.global lbl_803B7E48
lbl_803B7E48:
	.incbin "baserom.dol", 0x3B3F48, 0x58
.global lbl_803B7EA0
lbl_803B7EA0:
	.incbin "baserom.dol", 0x3B3FA0, 0x18
.global lbl_803B7EB8
lbl_803B7EB8:
	.incbin "baserom.dol", 0x3B3FB8, 0x14
.global lbl_803B7ECC
lbl_803B7ECC:
	.incbin "baserom.dol", 0x3B3FCC, 0x34
.global lbl_803B7F00
lbl_803B7F00:
	.incbin "baserom.dol", 0x3B4000, 0x18
.global lbl_803B7F18
lbl_803B7F18:
	.incbin "baserom.dol", 0x3B4018, 0x14
.global lbl_803B7F2C
lbl_803B7F2C:
	.incbin "baserom.dol", 0x3B402C, 0x1C
.global lbl_803B7F48
lbl_803B7F48:
	.incbin "baserom.dol", 0x3B4048, 0x10
.global lbl_803B7F58
lbl_803B7F58:
	.incbin "baserom.dol", 0x3B4058, 0xA0
.global lbl_803B7FF8
lbl_803B7FF8:
	.incbin "baserom.dol", 0x3B40F8, 0xE8
.global lbl_803B80E0
lbl_803B80E0:
	.incbin "baserom.dol", 0x3B41E0, 0x10
.global lbl_803B80F0
lbl_803B80F0:
	.incbin "baserom.dol", 0x3B41F0, 0x10
.global lbl_803B8100
lbl_803B8100:
	.incbin "baserom.dol", 0x3B4200, 0x360
.global lbl_803B8460
lbl_803B8460:
	.incbin "baserom.dol", 0x3B4560, 0x14
.global lbl_803B8474
lbl_803B8474:
	.incbin "baserom.dol", 0x3B4574, 0x14
.global lbl_803B8488
lbl_803B8488:
	.incbin "baserom.dol", 0x3B4588, 0xD8
.global lbl_803B8560
lbl_803B8560:
	.incbin "baserom.dol", 0x3B4660, 0x18
.global lbl_803B8578
lbl_803B8578:
	.incbin "baserom.dol", 0x3B4678, 0x1B0
.global lbl_803B8728
lbl_803B8728:
	.incbin "baserom.dol", 0x3B4828, 0x18
.global lbl_803B8740
lbl_803B8740:
	.incbin "baserom.dol", 0x3B4840, 0x48
.global lbl_803B8788
lbl_803B8788:
	.incbin "baserom.dol", 0x3B4888, 0x4
.global lbl_803B878C
lbl_803B878C:
	.incbin "baserom.dol", 0x3B488C, 0xAC
.global lbl_803B8838
lbl_803B8838:
	.incbin "baserom.dol", 0x3B4938, 0x908
.global lbl_803B9140
lbl_803B9140:
	.incbin "baserom.dol", 0x3B5240, 0x4C
.global lbl_803B918C
lbl_803B918C:
	.incbin "baserom.dol", 0x3B528C, 0x10C
.global lbl_803B9298
lbl_803B9298:
	.incbin "baserom.dol", 0x3B5398, 0x60
.global lbl_803B92F8
lbl_803B92F8:
	.incbin "baserom.dol", 0x3B53F8, 0x50
.global lbl_803B9348
lbl_803B9348:
	.incbin "baserom.dol", 0x3B5448, 0x28
.global lbl_803B9370
lbl_803B9370:
	.incbin "baserom.dol", 0x3B5470, 0x28
.global lbl_803B9398
lbl_803B9398:
	.incbin "baserom.dol", 0x3B5498, 0x28
.global lbl_803B93C0
lbl_803B93C0:
	.incbin "baserom.dol", 0x3B54C0, 0x40
.global lbl_803B9400
lbl_803B9400:
	.incbin "baserom.dol", 0x3B5500, 0x10
.global lbl_803B9410
lbl_803B9410:
	.incbin "baserom.dol", 0x3B5510, 0x68
.global lbl_803B9478
lbl_803B9478:
	.incbin "baserom.dol", 0x3B5578, 0x54
.global lbl_803B94CC
lbl_803B94CC:
	.incbin "baserom.dol", 0x3B55CC, 0x3C
.global lbl_803B9508
lbl_803B9508:
	.incbin "baserom.dol", 0x3B5608, 0x60
.global lbl_803B9568
lbl_803B9568:
	.incbin "baserom.dol", 0x3B5668, 0x10
.global lbl_803B9578
lbl_803B9578:
	.incbin "baserom.dol", 0x3B5678, 0xC
.global lbl_803B9584
lbl_803B9584:
	.incbin "baserom.dol", 0x3B5684, 0x34
.global lbl_803B95B8
lbl_803B95B8:
	.incbin "baserom.dol", 0x3B56B8, 0x30
.global lbl_803B95E8
lbl_803B95E8:
	.incbin "baserom.dol", 0x3B56E8, 0x18
.global lbl_803B9600
lbl_803B9600:
	.incbin "baserom.dol", 0x3B5700, 0x190
.global lbl_803B9790
lbl_803B9790:
	.incbin "baserom.dol", 0x3B5890, 0x20
.global lbl_803B97B0
lbl_803B97B0:
	.incbin "baserom.dol", 0x3B58B0, 0x28
.global lbl_803B97D8
lbl_803B97D8:
	.incbin "baserom.dol", 0x3B58D8, 0x20
.global lbl_803B97F8
lbl_803B97F8:
	.incbin "baserom.dol", 0x3B58F8, 0x10
.global lbl_803B9808
lbl_803B9808:
	.incbin "baserom.dol", 0x3B5908, 0xC
.global lbl_803B9814
lbl_803B9814:
	.incbin "baserom.dol", 0x3B5914, 0x14
.global lbl_803B9828
lbl_803B9828:
	.incbin "baserom.dol", 0x3B5928, 0x14
.global lbl_803B983C
lbl_803B983C:
	.incbin "baserom.dol", 0x3B593C, 0x14
.global lbl_803B9850
lbl_803B9850:
	.incbin "baserom.dol", 0x3B5950, 0x10
.global lbl_803B9860
lbl_803B9860:
	.incbin "baserom.dol", 0x3B5960, 0x10
.global lbl_803B9870
lbl_803B9870:
	.incbin "baserom.dol", 0x3B5970, 0x10
.global lbl_803B9880
lbl_803B9880:
	.incbin "baserom.dol", 0x3B5980, 0x14
.global lbl_803B9894
lbl_803B9894:
	.incbin "baserom.dol", 0x3B5994, 0x14
.global lbl_803B98A8
lbl_803B98A8:
	.incbin "baserom.dol", 0x3B59A8, 0x60
.global lbl_803B9908
lbl_803B9908:
	.incbin "baserom.dol", 0x3B5A08, 0x20
.global lbl_803B9928
lbl_803B9928:
	.incbin "baserom.dol", 0x3B5A28, 0x10
.global lbl_803B9938
lbl_803B9938:
	.incbin "baserom.dol", 0x3B5A38, 0x18
.global lbl_803B9950
lbl_803B9950:
	.incbin "baserom.dol", 0x3B5A50, 0x1C
.global lbl_803B996C
lbl_803B996C:
	.incbin "baserom.dol", 0x3B5A6C, 0xC
.global lbl_803B9978
lbl_803B9978:
	.incbin "baserom.dol", 0x3B5A78, 0x10
.global lbl_803B9988
lbl_803B9988:
	.incbin "baserom.dol", 0x3B5A88, 0x10
.global lbl_803B9998
lbl_803B9998:
	.incbin "baserom.dol", 0x3B5A98, 0x18
.global lbl_803B99B0
lbl_803B99B0:
	.incbin "baserom.dol", 0x3B5AB0, 0x10
.global lbl_803B99C0
lbl_803B99C0:
	.incbin "baserom.dol", 0x3B5AC0, 0x10
.global lbl_803B99D0
lbl_803B99D0:
	.incbin "baserom.dol", 0x3B5AD0, 0x10
.global lbl_803B99E0
lbl_803B99E0:
	.incbin "baserom.dol", 0x3B5AE0, 0x18
.global lbl_803B99F8
lbl_803B99F8:
	.incbin "baserom.dol", 0x3B5AF8, 0x18
.global lbl_803B9A10
lbl_803B9A10:
	.incbin "baserom.dol", 0x3B5B10, 0x10
.global lbl_803B9A20
lbl_803B9A20:
	.incbin "baserom.dol", 0x3B5B20, 0x18
.global lbl_803B9A38
lbl_803B9A38:
	.incbin "baserom.dol", 0x3B5B38, 0x68
.global lbl_803B9AA0
lbl_803B9AA0:
	.incbin "baserom.dol", 0x3B5BA0, 0xC
.global lbl_803B9AAC
lbl_803B9AAC:
	.incbin "baserom.dol", 0x3B5BAC, 0xC
.global lbl_803B9AB8
lbl_803B9AB8:
	.incbin "baserom.dol", 0x3B5BB8, 0xC
.global lbl_803B9AC4
lbl_803B9AC4:
	.incbin "baserom.dol", 0x3B5BC4, 0xC
.global lbl_803B9AD0
lbl_803B9AD0:
	.incbin "baserom.dol", 0x3B5BD0, 0x68
.global lbl_803B9B38
lbl_803B9B38:
	.incbin "baserom.dol", 0x3B5C38, 0x98
.global lbl_803B9BD0
lbl_803B9BD0:
	.incbin "baserom.dol", 0x3B5CD0, 0x10
.global lbl_803B9BE0
lbl_803B9BE0:
	.incbin "baserom.dol", 0x3B5CE0, 0x18
.global lbl_803B9BF8
lbl_803B9BF8:
	.incbin "baserom.dol", 0x3B5CF8, 0x10
.global lbl_803B9C08
lbl_803B9C08:
	.incbin "baserom.dol", 0x3B5D08, 0x18
.global lbl_803B9C20
lbl_803B9C20:
	.incbin "baserom.dol", 0x3B5D20, 0x10
.global lbl_803B9C30
lbl_803B9C30:
	.incbin "baserom.dol", 0x3B5D30, 0x18
.global lbl_803B9C48
lbl_803B9C48:
	.incbin "baserom.dol", 0x3B5D48, 0x38
.global lbl_803B9C80
lbl_803B9C80:
	.incbin "baserom.dol", 0x3B5D80, 0x18
.global lbl_803B9C98
lbl_803B9C98:
	.incbin "baserom.dol", 0x3B5D98, 0x10
.global lbl_803B9CA8
lbl_803B9CA8:
	.incbin "baserom.dol", 0x3B5DA8, 0x10
.global lbl_803B9CB8
lbl_803B9CB8:
	.incbin "baserom.dol", 0x3B5DB8, 0x10
.global lbl_803B9CC8
lbl_803B9CC8:
	.incbin "baserom.dol", 0x3B5DC8, 0x10
.global lbl_803B9CD8
lbl_803B9CD8:
	.incbin "baserom.dol", 0x3B5DD8, 0x2C
.global lbl_803B9D04
lbl_803B9D04:
	.incbin "baserom.dol", 0x3B5E04, 0xC
.global lbl_803B9D10
lbl_803B9D10:
	.incbin "baserom.dol", 0x3B5E10, 0x34
.global lbl_803B9D44
lbl_803B9D44:
	.incbin "baserom.dol", 0x3B5E44, 0xC
.global lbl_803B9D50
lbl_803B9D50:
	.incbin "baserom.dol", 0x3B5E50, 0x18
.global lbl_803B9D68
lbl_803B9D68:
	.incbin "baserom.dol", 0x3B5E68, 0x18
.global lbl_803B9D80
lbl_803B9D80:
	.incbin "baserom.dol", 0x3B5E80, 0x30
.global lbl_803B9DB0
lbl_803B9DB0:
	.incbin "baserom.dol", 0x3B5EB0, 0x10
.global lbl_803B9DC0
lbl_803B9DC0:
	.incbin "baserom.dol", 0x3B5EC0, 0x40
.global lbl_803B9E00
lbl_803B9E00:
	.incbin "baserom.dol", 0x3B5F00, 0xC
.global lbl_803B9E0C
lbl_803B9E0C:
	.incbin "baserom.dol", 0x3B5F0C, 0xC
.global lbl_803B9E18
lbl_803B9E18:
	.incbin "baserom.dol", 0x3B5F18, 0x20
.global lbl_803B9E38
lbl_803B9E38:
	.incbin "baserom.dol", 0x3B5F38, 0x10
.global lbl_803B9E48
lbl_803B9E48:
	.incbin "baserom.dol", 0x3B5F48, 0x10
.global lbl_803B9E58
lbl_803B9E58:
	.incbin "baserom.dol", 0x3B5F58, 0x10
.global lbl_803B9E68
lbl_803B9E68:
	.incbin "baserom.dol", 0x3B5F68, 0x10
.global lbl_803B9E78
lbl_803B9E78:
	.incbin "baserom.dol", 0x3B5F78, 0xC
.global lbl_803B9E84
lbl_803B9E84:
	.incbin "baserom.dol", 0x3B5F84, 0xC
.global lbl_803B9E90
lbl_803B9E90:
	.incbin "baserom.dol", 0x3B5F90, 0x10
.global lbl_803B9EA0
lbl_803B9EA0:
	.incbin "baserom.dol", 0x3B5FA0, 0x10
.global lbl_803B9EB0
lbl_803B9EB0:
	.incbin "baserom.dol", 0x3B5FB0, 0x9C
.global lbl_803B9F4C
lbl_803B9F4C:
	.incbin "baserom.dol", 0x3B604C, 0xC
.global lbl_803B9F58
lbl_803B9F58:
	.incbin "baserom.dol", 0x3B6058, 0x38
.global lbl_803B9F90
lbl_803B9F90:
	.incbin "baserom.dol", 0x3B6090, 0x38
.global lbl_803B9FC8
lbl_803B9FC8:
	.incbin "baserom.dol", 0x3B60C8, 0x10
.global lbl_803B9FD8
lbl_803B9FD8:
	.incbin "baserom.dol", 0x3B60D8, 0x18
.global lbl_803B9FF0
lbl_803B9FF0:
	.incbin "baserom.dol", 0x3B60F0, 0x18
.global lbl_803BA008
lbl_803BA008:
	.incbin "baserom.dol", 0x3B6108, 0x18
.global lbl_803BA020
lbl_803BA020:
	.incbin "baserom.dol", 0x3B6120, 0x18
.global lbl_803BA038
lbl_803BA038:
	.incbin "baserom.dol", 0x3B6138, 0x18
.global lbl_803BA050
lbl_803BA050:
	.incbin "baserom.dol", 0x3B6150, 0x10
.global lbl_803BA060
lbl_803BA060:
	.incbin "baserom.dol", 0x3B6160, 0xA0
.global lbl_803BA100
lbl_803BA100:
	.incbin "baserom.dol", 0x3B6200, 0x88
.global lbl_803BA188
lbl_803BA188:
	.incbin "baserom.dol", 0x3B6288, 0x20
.global lbl_803BA1A8
lbl_803BA1A8:
	.incbin "baserom.dol", 0x3B62A8, 0x20
.global lbl_803BA1C8
lbl_803BA1C8:
	.incbin "baserom.dol", 0x3B62C8, 0x20
.global lbl_803BA1E8
lbl_803BA1E8:
	.incbin "baserom.dol", 0x3B62E8, 0x88
.global lbl_803BA270
lbl_803BA270:
	.incbin "baserom.dol", 0x3B6370, 0x20
.global lbl_803BA290
lbl_803BA290:
	.incbin "baserom.dol", 0x3B6390, 0x20
.global lbl_803BA2B0
lbl_803BA2B0:
	.incbin "baserom.dol", 0x3B63B0, 0x20
.global lbl_803BA2D0
lbl_803BA2D0:
	.incbin "baserom.dol", 0x3B63D0, 0x20
.global lbl_803BA2F0
lbl_803BA2F0:
	.incbin "baserom.dol", 0x3B63F0, 0xF8
.global lbl_803BA3E8
lbl_803BA3E8:
	.incbin "baserom.dol", 0x3B64E8, 0x10
.global lbl_803BA3F8
lbl_803BA3F8:
	.incbin "baserom.dol", 0x3B64F8, 0x20
.global lbl_803BA418
lbl_803BA418:
	.incbin "baserom.dol", 0x3B6518, 0x28
.global lbl_803BA440
lbl_803BA440:
	.incbin "baserom.dol", 0x3B6540, 0x30
.global lbl_803BA470
lbl_803BA470:
	.incbin "baserom.dol", 0x3B6570, 0x28
.global lbl_803BA498
lbl_803BA498:
	.incbin "baserom.dol", 0x3B6598, 0x28
.global lbl_803BA4C0
lbl_803BA4C0:
	.incbin "baserom.dol", 0x3B65C0, 0x10
.global lbl_803BA4D0
lbl_803BA4D0:
	.incbin "baserom.dol", 0x3B65D0, 0x14
.global lbl_803BA4E4
lbl_803BA4E4:
	.incbin "baserom.dol", 0x3B65E4, 0xC
.global lbl_803BA4F0
lbl_803BA4F0:
	.incbin "baserom.dol", 0x3B65F0, 0x10
.global lbl_803BA500
lbl_803BA500:
	.incbin "baserom.dol", 0x3B6600, 0x10
.global lbl_803BA510
lbl_803BA510:
	.incbin "baserom.dol", 0x3B6610, 0x10
.global lbl_803BA520
lbl_803BA520:
	.incbin "baserom.dol", 0x3B6620, 0x10
.global lbl_803BA530
lbl_803BA530:
	.incbin "baserom.dol", 0x3B6630, 0x10
.global lbl_803BA540
lbl_803BA540:
	.incbin "baserom.dol", 0x3B6640, 0x10
.global lbl_803BA550
lbl_803BA550:
	.incbin "baserom.dol", 0x3B6650, 0x10
.global lbl_803BA560
lbl_803BA560:
	.incbin "baserom.dol", 0x3B6660, 0x10
.global lbl_803BA570
lbl_803BA570:
	.incbin "baserom.dol", 0x3B6670, 0x10
.global lbl_803BA580
lbl_803BA580:
	.incbin "baserom.dol", 0x3B6680, 0x10
.global lbl_803BA590
lbl_803BA590:
	.incbin "baserom.dol", 0x3B6690, 0x20
.global lbl_803BA5B0
lbl_803BA5B0:
	.incbin "baserom.dol", 0x3B66B0, 0x10
.global lbl_803BA5C0
lbl_803BA5C0:
	.incbin "baserom.dol", 0x3B66C0, 0x2C
.global lbl_803BA5EC
lbl_803BA5EC:
	.incbin "baserom.dol", 0x3B66EC, 0xC
.global lbl_803BA5F8
lbl_803BA5F8:
	.incbin "baserom.dol", 0x3B66F8, 0x10
.global lbl_803BA608
lbl_803BA608:
	.incbin "baserom.dol", 0x3B6708, 0x30
.global lbl_803BA638
lbl_803BA638:
	.incbin "baserom.dol", 0x3B6738, 0x30
.global lbl_803BA668
lbl_803BA668:
	.incbin "baserom.dol", 0x3B6768, 0x10
.global lbl_803BA678
lbl_803BA678:
	.incbin "baserom.dol", 0x3B6778, 0x20
.global lbl_803BA698
lbl_803BA698:
	.incbin "baserom.dol", 0x3B6798, 0x28
.global lbl_803BA6C0
lbl_803BA6C0:
	.incbin "baserom.dol", 0x3B67C0, 0x18
.global lbl_803BA6D8
lbl_803BA6D8:
	.incbin "baserom.dol", 0x3B67D8, 0x10
.global lbl_803BA6E8
lbl_803BA6E8:
	.incbin "baserom.dol", 0x3B67E8, 0x20
.global lbl_803BA708
lbl_803BA708:
	.incbin "baserom.dol", 0x3B6808, 0x10
.global lbl_803BA718
lbl_803BA718:
	.incbin "baserom.dol", 0x3B6818, 0x18
.global lbl_803BA730
lbl_803BA730:
	.incbin "baserom.dol", 0x3B6830, 0x10
.global lbl_803BA740
lbl_803BA740:
	.incbin "baserom.dol", 0x3B6840, 0x10
.global lbl_803BA750
lbl_803BA750:
	.incbin "baserom.dol", 0x3B6850, 0x18
.global lbl_803BA768
lbl_803BA768:
	.incbin "baserom.dol", 0x3B6868, 0x18
.global lbl_803BA780
lbl_803BA780:
	.incbin "baserom.dol", 0x3B6880, 0x10
.global lbl_803BA790
lbl_803BA790:
	.incbin "baserom.dol", 0x3B6890, 0x10
.global lbl_803BA7A0
lbl_803BA7A0:
	.incbin "baserom.dol", 0x3B68A0, 0x10
.global lbl_803BA7B0
lbl_803BA7B0:
	.incbin "baserom.dol", 0x3B68B0, 0xD0
.global lbl_803BA880
lbl_803BA880:
	.incbin "baserom.dol", 0x3B6980, 0xC0
.global lbl_803BA940
lbl_803BA940:
	.incbin "baserom.dol", 0x3B6A40, 0x14
.global lbl_803BA954
lbl_803BA954:
	.incbin "baserom.dol", 0x3B6A54, 0x10
.global lbl_803BA964
lbl_803BA964:
	.incbin "baserom.dol", 0x3B6A64, 0x1C
.global lbl_803BA980
lbl_803BA980:
	.incbin "baserom.dol", 0x3B6A80, 0x10
.global lbl_803BA990
lbl_803BA990:
	.incbin "baserom.dol", 0x3B6A90, 0x18
.global lbl_803BA9A8
lbl_803BA9A8:
	.incbin "baserom.dol", 0x3B6AA8, 0x1C
.global lbl_803BA9C4
lbl_803BA9C4:
	.incbin "baserom.dol", 0x3B6AC4, 0x18
.global lbl_803BA9DC
lbl_803BA9DC:
	.incbin "baserom.dol", 0x3B6ADC, 0x14
.global lbl_803BA9F0
lbl_803BA9F0:
	.incbin "baserom.dol", 0x3B6AF0, 0x18
.global lbl_803BAA08
lbl_803BAA08:
	.incbin "baserom.dol", 0x3B6B08, 0x18
.global lbl_803BAA20
lbl_803BAA20:
	.incbin "baserom.dol", 0x3B6B20, 0x10
.global lbl_803BAA30
lbl_803BAA30:
	.incbin "baserom.dol", 0x3B6B30, 0x10
.global lbl_803BAA40
lbl_803BAA40:
	.incbin "baserom.dol", 0x3B6B40, 0x10
.global lbl_803BAA50
lbl_803BAA50:
	.incbin "baserom.dol", 0x3B6B50, 0x10
.global lbl_803BAA60
lbl_803BAA60:
	.incbin "baserom.dol", 0x3B6B60, 0x10
.global lbl_803BAA70
lbl_803BAA70:
	.incbin "baserom.dol", 0x3B6B70, 0x18
.global lbl_803BAA88
lbl_803BAA88:
	.incbin "baserom.dol", 0x3B6B88, 0x10
.global lbl_803BAA98
lbl_803BAA98:
	.incbin "baserom.dol", 0x3B6B98, 0x88
.global lbl_803BAB20
lbl_803BAB20:
	.incbin "baserom.dol", 0x3B6C20, 0x54E4
.global lbl_803C0004
lbl_803C0004:
	.incbin "baserom.dol", 0x3BC104, 0x16BC
.global lbl_803C16C0
lbl_803C16C0:
	.incbin "baserom.dol", 0x3BD7C0, 0x60
.global lbl_803C1720
lbl_803C1720:
	.incbin "baserom.dol", 0x3BD820, 0x28
.global lbl_803C1748
lbl_803C1748:
	.incbin "baserom.dol", 0x3BD848, 0x18
.global lbl_803C1760
lbl_803C1760:
	.incbin "baserom.dol", 0x3BD860, 0x34
.global lbl_803C1794
lbl_803C1794:
	.incbin "baserom.dol", 0x3BD894, 0x34
.global lbl_803C17C8
lbl_803C17C8:
	.incbin "baserom.dol", 0x3BD8C8, 0x10
.global lbl_803C17D8
lbl_803C17D8:
	.incbin "baserom.dol", 0x3BD8D8, 0x10
.global lbl_803C17E8
lbl_803C17E8:
	.incbin "baserom.dol", 0x3BD8E8, 0x10
.global lbl_803C17F8
lbl_803C17F8:
	.incbin "baserom.dol", 0x3BD8F8, 0x28
.global lbl_803C1820
lbl_803C1820:
	.incbin "baserom.dol", 0x3BD920, 0x28
.global lbl_803C1848
lbl_803C1848:
	.incbin "baserom.dol", 0x3BD948, 0x18
.global lbl_803C1860
lbl_803C1860:
	.incbin "baserom.dol", 0x3BD960, 0x10
.global lbl_803C1870
lbl_803C1870:
	.incbin "baserom.dol", 0x3BD970, 0x10
.global lbl_803C1880
lbl_803C1880:
	.incbin "baserom.dol", 0x3BD980, 0x20
.global lbl_803C18A0
lbl_803C18A0:
	.incbin "baserom.dol", 0x3BD9A0, 0x28
.global lbl_803C18C8
lbl_803C18C8:
	.incbin "baserom.dol", 0x3BD9C8, 0x38
.global lbl_803C1900
lbl_803C1900:
	.incbin "baserom.dol", 0x3BDA00, 0x10
.global lbl_803C1910
lbl_803C1910:
	.incbin "baserom.dol", 0x3BDA10, 0x78
.global lbl_803C1988
lbl_803C1988:
	.incbin "baserom.dol", 0x3BDA88, 0x20
.global lbl_803C19A8
lbl_803C19A8:
	.incbin "baserom.dol", 0x3BDAA8, 0x2C
.global lbl_803C19D4
lbl_803C19D4:
	.incbin "baserom.dol", 0x3BDAD4, 0xC
.global lbl_803C19E0
lbl_803C19E0:
	.incbin "baserom.dol", 0x3BDAE0, 0x18
.global lbl_803C19F8
lbl_803C19F8:
	.incbin "baserom.dol", 0x3BDAF8, 0x28
.global lbl_803C1A20
lbl_803C1A20:
	.incbin "baserom.dol", 0x3BDB20, 0x18
.global lbl_803C1A38
lbl_803C1A38:
	.incbin "baserom.dol", 0x3BDB38, 0x14
.global lbl_803C1A4C
lbl_803C1A4C:
	.incbin "baserom.dol", 0x3BDB4C, 0x14
.global lbl_803C1A60
lbl_803C1A60:
	.incbin "baserom.dol", 0x3BDB60, 0x78
.global lbl_803C1AD8
lbl_803C1AD8:
	.incbin "baserom.dol", 0x3BDBD8, 0x10
.global lbl_803C1AE8
lbl_803C1AE8:
	.incbin "baserom.dol", 0x3BDBE8, 0x18
.global lbl_803C1B00
lbl_803C1B00:
	.incbin "baserom.dol", 0x3BDC00, 0x18
.global lbl_803C1B18
lbl_803C1B18:
	.incbin "baserom.dol", 0x3BDC18, 0x30
.global lbl_803C1B48
lbl_803C1B48:
	.incbin "baserom.dol", 0x3BDC48, 0x20
.global lbl_803C1B68
lbl_803C1B68:
	.incbin "baserom.dol", 0x3BDC68, 0x20
.global lbl_803C1B88
lbl_803C1B88:
	.incbin "baserom.dol", 0x3BDC88, 0x20
.global lbl_803C1BA8
lbl_803C1BA8:
	.incbin "baserom.dol", 0x3BDCA8, 0x48
.global lbl_803C1BF0
lbl_803C1BF0:
	.incbin "baserom.dol", 0x3BDCF0, 0x30
.global lbl_803C1C20
lbl_803C1C20:
	.incbin "baserom.dol", 0x3BDD20, 0x30
.global lbl_803C1C50
lbl_803C1C50:
	.incbin "baserom.dol", 0x3BDD50, 0x10
.global lbl_803C1C60
lbl_803C1C60:
	.incbin "baserom.dol", 0x3BDD60, 0x10
.global lbl_803C1C70
lbl_803C1C70:
	.incbin "baserom.dol", 0x3BDD70, 0x30
.global lbl_803C1CA0
lbl_803C1CA0:
	.incbin "baserom.dol", 0x3BDDA0, 0x10
.global lbl_803C1CB0
lbl_803C1CB0:
	.incbin "baserom.dol", 0x3BDDB0, 0x20
.global lbl_803C1CD0
lbl_803C1CD0:
	.incbin "baserom.dol", 0x3BDDD0, 0x48
.global lbl_803C1D18
lbl_803C1D18:
	.incbin "baserom.dol", 0x3BDE18, 0x10
.global lbl_803C1D28
lbl_803C1D28:
	.incbin "baserom.dol", 0x3BDE28, 0x20
.global lbl_803C1D48
lbl_803C1D48:
	.incbin "baserom.dol", 0x3BDE48, 0x20
.global lbl_803C1D68
lbl_803C1D68:
	.incbin "baserom.dol", 0x3BDE68, 0x10
.global lbl_803C1D78
lbl_803C1D78:
	.incbin "baserom.dol", 0x3BDE78, 0x180
.global lbl_803C1EF8
lbl_803C1EF8:
	.incbin "baserom.dol", 0x3BDFF8, 0x50
.global lbl_803C1F48
lbl_803C1F48:
	.incbin "baserom.dol", 0x3BE048, 0x30
.global lbl_803C1F78
lbl_803C1F78:
	.incbin "baserom.dol", 0x3BE078, 0x60
.global lbl_803C1FD8
lbl_803C1FD8:
	.incbin "baserom.dol", 0x3BE0D8, 0x60
.global lbl_803C2038
lbl_803C2038:
	.incbin "baserom.dol", 0x3BE138, 0xC
.global lbl_803C2044
lbl_803C2044:
	.incbin "baserom.dol", 0x3BE144, 0x24
.global lbl_803C2068
lbl_803C2068:
	.incbin "baserom.dol", 0x3BE168, 0x18
.global lbl_803C2080
lbl_803C2080:
	.incbin "baserom.dol", 0x3BE180, 0x20
.global lbl_803C20A0
lbl_803C20A0:
	.incbin "baserom.dol", 0x3BE1A0, 0x28
.global lbl_803C20C8
lbl_803C20C8:
	.incbin "baserom.dol", 0x3BE1C8, 0x1C
.global lbl_803C20E4
lbl_803C20E4:
	.incbin "baserom.dol", 0x3BE1E4, 0x2C
.global lbl_803C2110
lbl_803C2110:
	.incbin "baserom.dol", 0x3BE210, 0x20
.global lbl_803C2130
lbl_803C2130:
	.incbin "baserom.dol", 0x3BE230, 0x20
.global lbl_803C2150
lbl_803C2150:
	.incbin "baserom.dol", 0x3BE250, 0xD0
.global lbl_803C2220
lbl_803C2220:
	.incbin "baserom.dol", 0x3BE320, 0x28
.global lbl_803C2248
lbl_803C2248:
	.incbin "baserom.dol", 0x3BE348, 0x30
.global lbl_803C2278
lbl_803C2278:
	.incbin "baserom.dol", 0x3BE378, 0x30
.global lbl_803C22A8
lbl_803C22A8:
	.incbin "baserom.dol", 0x3BE3A8, 0x30
.global lbl_803C22D8
lbl_803C22D8:
	.incbin "baserom.dol", 0x3BE3D8, 0x30
.global lbl_803C2308
lbl_803C2308:
	.incbin "baserom.dol", 0x3BE408, 0x30
.global lbl_803C2338
lbl_803C2338:
	.incbin "baserom.dol", 0x3BE438, 0xE0
.global lbl_803C2418
lbl_803C2418:
	.incbin "baserom.dol", 0x3BE518, 0x78
.global lbl_803C2490
lbl_803C2490:
	.incbin "baserom.dol", 0x3BE590, 0xB8
.global lbl_803C2548
lbl_803C2548:
	.incbin "baserom.dol", 0x3BE648, 0x20
.global lbl_803C2568
lbl_803C2568:
	.incbin "baserom.dol", 0x3BE668, 0x30
.global lbl_803C2598
lbl_803C2598:
	.incbin "baserom.dol", 0x3BE698, 0x30
.global lbl_803C25C8
lbl_803C25C8:
	.incbin "baserom.dol", 0x3BE6C8, 0x20
.global lbl_803C25E8
lbl_803C25E8:
	.incbin "baserom.dol", 0x3BE6E8, 0x10
.global lbl_803C25F8
lbl_803C25F8:
	.incbin "baserom.dol", 0x3BE6F8, 0x20
.global lbl_803C2618
lbl_803C2618:
	.incbin "baserom.dol", 0x3BE718, 0x20
.global lbl_803C2638
lbl_803C2638:
	.incbin "baserom.dol", 0x3BE738, 0x18
.global lbl_803C2650
lbl_803C2650:
	.incbin "baserom.dol", 0x3BE750, 0x10
.global lbl_803C2660
lbl_803C2660:
	.incbin "baserom.dol", 0x3BE760, 0x20
.global lbl_803C2680
lbl_803C2680:
	.incbin "baserom.dol", 0x3BE780, 0xE8
.global lbl_803C2768
lbl_803C2768:
	.incbin "baserom.dol", 0x3BE868, 0x28
.global lbl_803C2790
lbl_803C2790:
	.incbin "baserom.dol", 0x3BE890, 0x60
.global lbl_803C27F0
lbl_803C27F0:
	.incbin "baserom.dol", 0x3BE8F0, 0x60
.global lbl_803C2850
lbl_803C2850:
	.incbin "baserom.dol", 0x3BE950, 0x60
.global lbl_803C28B0
lbl_803C28B0:
	.incbin "baserom.dol", 0x3BE9B0, 0x60
.global lbl_803C2910
lbl_803C2910:
	.incbin "baserom.dol", 0x3BEA10, 0x80
.global lbl_803C2990
lbl_803C2990:
	.incbin "baserom.dol", 0x3BEA90, 0x10
.global lbl_803C29A0
lbl_803C29A0:
	.incbin "baserom.dol", 0x3BEAA0, 0x10
.global lbl_803C29B0
lbl_803C29B0:
	.incbin "baserom.dol", 0x3BEAB0, 0x24
.global lbl_803C29D4
lbl_803C29D4:
	.incbin "baserom.dol", 0x3BEAD4, 0xC
.global lbl_803C29E0
lbl_803C29E0:
	.incbin "baserom.dol", 0x3BEAE0, 0x18
.global lbl_803C29F8
lbl_803C29F8:
	.incbin "baserom.dol", 0x3BEAF8, 0x48
.global lbl_803C2A40
lbl_803C2A40:
	.incbin "baserom.dol", 0x3BEB40, 0x80
.global lbl_803C2AC0
lbl_803C2AC0:
	.incbin "baserom.dol", 0x3BEBC0, 0x60
.global lbl_803C2B20
lbl_803C2B20:
	.incbin "baserom.dol", 0x3BEC20, 0x30
.global lbl_803C2B50
lbl_803C2B50:
	.incbin "baserom.dol", 0x3BEC50, 0x58
.global lbl_803C2BA8
lbl_803C2BA8:
	.incbin "baserom.dol", 0x3BECA8, 0x24
.global lbl_803C2BCC
lbl_803C2BCC:
	.incbin "baserom.dol", 0x3BECCC, 0x24
.global lbl_803C2BF0
lbl_803C2BF0:
	.incbin "baserom.dol", 0x3BECF0, 0x48
.global lbl_803C2C38
lbl_803C2C38:
	.incbin "baserom.dol", 0x3BED38, 0x30
.global lbl_803C2C68
lbl_803C2C68:
	.incbin "baserom.dol", 0x3BED68, 0x2C
.global lbl_803C2C94
lbl_803C2C94:
	.incbin "baserom.dol", 0x3BED94, 0x5C
.global lbl_803C2CF0
lbl_803C2CF0:
	.incbin "baserom.dol", 0x3BEDF0, 0x18
.global lbl_803C2D08
lbl_803C2D08:
	.incbin "baserom.dol", 0x3BEE08, 0xC0
.global lbl_803C2DC8
lbl_803C2DC8:
	.incbin "baserom.dol", 0x3BEEC8, 0x60
.global lbl_803C2E28
lbl_803C2E28:
	.incbin "baserom.dol", 0x3BEF28, 0x18
.global lbl_803C2E40
lbl_803C2E40:
	.incbin "baserom.dol", 0x3BEF40, 0x18
.global lbl_803C2E58
lbl_803C2E58:
	.incbin "baserom.dol", 0x3BEF58, 0x10
.global lbl_803C2E68
lbl_803C2E68:
	.incbin "baserom.dol", 0x3BEF68, 0x88
.global lbl_803C2EF0
lbl_803C2EF0:
	.incbin "baserom.dol", 0x3BEFF0, 0x10
.global lbl_803C2F00
lbl_803C2F00:
	.incbin "baserom.dol", 0x3BF000, 0x20
.global lbl_803C2F20
lbl_803C2F20:
	.incbin "baserom.dol", 0x3BF020, 0x30
.global lbl_803C2F50
lbl_803C2F50:
	.incbin "baserom.dol", 0x3BF050, 0x30
.global lbl_803C2F80
lbl_803C2F80:
	.incbin "baserom.dol", 0x3BF080, 0x50
.global lbl_803C2FD0
lbl_803C2FD0:
	.incbin "baserom.dol", 0x3BF0D0, 0x48
.global lbl_803C3018
lbl_803C3018:
	.incbin "baserom.dol", 0x3BF118, 0x10
.global lbl_803C3028
lbl_803C3028:
	.incbin "baserom.dol", 0x3BF128, 0x18
.global lbl_803C3040
lbl_803C3040:
	.incbin "baserom.dol", 0x3BF140, 0x10
.global lbl_803C3050
lbl_803C3050:
	.incbin "baserom.dol", 0x3BF150, 0x20
.global lbl_803C3070
lbl_803C3070:
	.incbin "baserom.dol", 0x3BF170, 0xB4
.global lbl_803C3124
lbl_803C3124:
	.incbin "baserom.dol", 0x3BF224, 0x14
.global lbl_803C3138
lbl_803C3138:
	.incbin "baserom.dol", 0x3BF238, 0x14
.global lbl_803C314C
lbl_803C314C:
	.incbin "baserom.dol", 0x3BF24C, 0xC
.global lbl_803C3158
lbl_803C3158:
	.incbin "baserom.dol", 0x3BF258, 0x10
.global lbl_803C3168
lbl_803C3168:
	.incbin "baserom.dol", 0x3BF268, 0x20
.global lbl_803C3188
lbl_803C3188:
	.incbin "baserom.dol", 0x3BF288, 0x10
.global lbl_803C3198
lbl_803C3198:
	.incbin "baserom.dol", 0x3BF298, 0x20
.global lbl_803C31B8
lbl_803C31B8:
	.incbin "baserom.dol", 0x3BF2B8, 0x2C
.global lbl_803C31E4
lbl_803C31E4:
	.incbin "baserom.dol", 0x3BF2E4, 0x160
.global lbl_803C3344
lbl_803C3344:
	.incbin "baserom.dol", 0x3BF444, 0x6C
.global lbl_803C33B0
lbl_803C33B0:
	.incbin "baserom.dol", 0x3BF4B0, 0x58
.global lbl_803C3408
lbl_803C3408:
	.incbin "baserom.dol", 0x3BF508, 0x30
.global lbl_803C3438
lbl_803C3438:
	.incbin "baserom.dol", 0x3BF538, 0x2C
.global lbl_803C3464
lbl_803C3464:
	.incbin "baserom.dol", 0x3BF564, 0xC
.global lbl_803C3470
lbl_803C3470:
	.incbin "baserom.dol", 0x3BF570, 0x20
.global lbl_803C3490
lbl_803C3490:
	.incbin "baserom.dol", 0x3BF590, 0x18
.global lbl_803C34A8
lbl_803C34A8:
	.incbin "baserom.dol", 0x3BF5A8, 0x10
.global lbl_803C34B8
lbl_803C34B8:
	.incbin "baserom.dol", 0x3BF5B8, 0x20
.global lbl_803C34D8
lbl_803C34D8:
	.incbin "baserom.dol", 0x3BF5D8, 0x10
.global lbl_803C34E8
lbl_803C34E8:
	.incbin "baserom.dol", 0x3BF5E8, 0x10
.global lbl_803C34F8
lbl_803C34F8:
	.incbin "baserom.dol", 0x3BF5F8, 0x10
.global lbl_803C3508
lbl_803C3508:
	.incbin "baserom.dol", 0x3BF608, 0x10
.global lbl_803C3518
lbl_803C3518:
	.incbin "baserom.dol", 0x3BF618, 0x10
.global lbl_803C3528
lbl_803C3528:
	.incbin "baserom.dol", 0x3BF628, 0xB0
.global lbl_803C35D8
lbl_803C35D8:
	.incbin "baserom.dol", 0x3BF6D8, 0x10
.global lbl_803C35E8
lbl_803C35E8:
	.incbin "baserom.dol", 0x3BF6E8, 0x10
.global lbl_803C35F8
lbl_803C35F8:
	.incbin "baserom.dol", 0x3BF6F8, 0xD0
.global lbl_803C36C8
lbl_803C36C8:
	.incbin "baserom.dol", 0x3BF7C8, 0x50
.global lbl_803C3718
lbl_803C3718:
	.incbin "baserom.dol", 0x3BF818, 0x18
.global lbl_803C3730
lbl_803C3730:
	.incbin "baserom.dol", 0x3BF830, 0x80
.global lbl_803C37B0
lbl_803C37B0:
	.incbin "baserom.dol", 0x3BF8B0, 0x68
.global lbl_803C3818
lbl_803C3818:
	.incbin "baserom.dol", 0x3BF918, 0x10
.global lbl_803C3828
lbl_803C3828:
	.incbin "baserom.dol", 0x3BF928, 0x28
.global lbl_803C3850
lbl_803C3850:
	.incbin "baserom.dol", 0x3BF950, 0x10
.global lbl_803C3860
lbl_803C3860:
	.incbin "baserom.dol", 0x3BF960, 0x10
.global lbl_803C3870
lbl_803C3870:
	.incbin "baserom.dol", 0x3BF970, 0xC
.global lbl_803C387C
lbl_803C387C:
	.incbin "baserom.dol", 0x3BF97C, 0x14
.global lbl_803C3890
lbl_803C3890:
	.incbin "baserom.dol", 0x3BF990, 0x10
.global lbl_803C38A0
lbl_803C38A0:
	.incbin "baserom.dol", 0x3BF9A0, 0x18
.global lbl_803C38B8
lbl_803C38B8:
	.incbin "baserom.dol", 0x3BF9B8, 0x10
.global lbl_803C38C8
lbl_803C38C8:
	.incbin "baserom.dol", 0x3BF9C8, 0x10
.global lbl_803C38D8
lbl_803C38D8:
	.incbin "baserom.dol", 0x3BF9D8, 0x20
.global lbl_803C38F8
lbl_803C38F8:
	.incbin "baserom.dol", 0x3BF9F8, 0x58
.global lbl_803C3950
lbl_803C3950:
	.incbin "baserom.dol", 0x3BFA50, 0x48
.global lbl_803C3998
lbl_803C3998:
	.incbin "baserom.dol", 0x3BFA98, 0x30
.global lbl_803C39C8
lbl_803C39C8:
	.incbin "baserom.dol", 0x3BFAC8, 0x10
.global lbl_803C39D8
lbl_803C39D8:
	.incbin "baserom.dol", 0x3BFAD8, 0x18
.global lbl_803C39F0
lbl_803C39F0:
	.incbin "baserom.dol", 0x3BFAF0, 0x288
.global lbl_803C3C78
lbl_803C3C78:
	.incbin "baserom.dol", 0x3BFD78, 0x30
.global lbl_803C3CA8
lbl_803C3CA8:
	.incbin "baserom.dol", 0x3BFDA8, 0x30
.global lbl_803C3CD8
lbl_803C3CD8:
	.incbin "baserom.dol", 0x3BFDD8, 0x30
.global lbl_803C3D08
lbl_803C3D08:
	.incbin "baserom.dol", 0x3BFE08, 0x30
.global lbl_803C3D38
lbl_803C3D38:
	.incbin "baserom.dol", 0x3BFE38, 0xDC
.global lbl_803C3E14
lbl_803C3E14:
	.incbin "baserom.dol", 0x3BFF14, 0xDC
.global lbl_803C3EF0
lbl_803C3EF0:
	.incbin "baserom.dol", 0x3BFFF0, 0xD0
.global lbl_803C3FC0
lbl_803C3FC0:
	.incbin "baserom.dol", 0x3C00C0, 0x38
.global lbl_803C3FF8
lbl_803C3FF8:
	.incbin "baserom.dol", 0x3C00F8, 0x10
.global lbl_803C4008
lbl_803C4008:
	.incbin "baserom.dol", 0x3C0108, 0x10
.global lbl_803C4018
lbl_803C4018:
	.incbin "baserom.dol", 0x3C0118, 0x20
.global lbl_803C4038
lbl_803C4038:
	.incbin "baserom.dol", 0x3C0138, 0x14
.global lbl_803C404C
lbl_803C404C:
	.incbin "baserom.dol", 0x3C014C, 0x10
.global lbl_803C405C
lbl_803C405C:
	.incbin "baserom.dol", 0x3C015C, 0x14
.global lbl_803C4070
lbl_803C4070:
	.incbin "baserom.dol", 0x3C0170, 0x38
.global lbl_803C40A8
lbl_803C40A8:
	.incbin "baserom.dol", 0x3C01A8, 0x10
.global lbl_803C40B8
lbl_803C40B8:
	.incbin "baserom.dol", 0x3C01B8, 0x10
.global lbl_803C40C8
lbl_803C40C8:
	.incbin "baserom.dol", 0x3C01C8, 0x10
.global lbl_803C40D8
lbl_803C40D8:
	.incbin "baserom.dol", 0x3C01D8, 0x18
.global lbl_803C40F0
lbl_803C40F0:
	.incbin "baserom.dol", 0x3C01F0, 0x18
.global lbl_803C4108
lbl_803C4108:
	.incbin "baserom.dol", 0x3C0208, 0x48
.global lbl_803C4150
lbl_803C4150:
	.incbin "baserom.dol", 0x3C0250, 0x58
.global lbl_803C41A8
lbl_803C41A8:
	.incbin "baserom.dol", 0x3C02A8, 0x20
.global lbl_803C41C8
lbl_803C41C8:
	.incbin "baserom.dol", 0x3C02C8, 0x48
.global lbl_803C4210
lbl_803C4210:
	.incbin "baserom.dol", 0x3C0310, 0x20
.global lbl_803C4230
lbl_803C4230:
	.incbin "baserom.dol", 0x3C0330, 0x30
.global lbl_803C4260
lbl_803C4260:
	.incbin "baserom.dol", 0x3C0360, 0x28
.global lbl_803C4288
lbl_803C4288:
	.incbin "baserom.dol", 0x3C0388, 0x20
.global lbl_803C42A8
lbl_803C42A8:
	.incbin "baserom.dol", 0x3C03A8, 0x28
.global lbl_803C42D0
lbl_803C42D0:
	.incbin "baserom.dol", 0x3C03D0, 0x10
.global lbl_803C42E0
lbl_803C42E0:
	.incbin "baserom.dol", 0x3C03E0, 0x28
.global lbl_803C4308
lbl_803C4308:
	.incbin "baserom.dol", 0x3C0408, 0xC
.global lbl_803C4314
lbl_803C4314:
	.incbin "baserom.dol", 0x3C0414, 0x44
.global lbl_803C4358
lbl_803C4358:
	.incbin "baserom.dol", 0x3C0458, 0x10
.global lbl_803C4368
lbl_803C4368:
	.incbin "baserom.dol", 0x3C0468, 0x28
.global lbl_803C4390
lbl_803C4390:
	.incbin "baserom.dol", 0x3C0490, 0x48
.global lbl_803C43D8
lbl_803C43D8:
	.incbin "baserom.dol", 0x3C04D8, 0xC
.global lbl_803C43E4
lbl_803C43E4:
	.incbin "baserom.dol", 0x3C04E4, 0xC
.global lbl_803C43F0
lbl_803C43F0:
	.incbin "baserom.dol", 0x3C04F0, 0x28
.global lbl_803C4418
lbl_803C4418:
	.incbin "baserom.dol", 0x3C0518, 0x20
.global lbl_803C4438
lbl_803C4438:
	.incbin "baserom.dol", 0x3C0538, 0x30
.global lbl_803C4468
lbl_803C4468:
	.incbin "baserom.dol", 0x3C0568, 0x10
.global lbl_803C4478
lbl_803C4478:
	.incbin "baserom.dol", 0x3C0578, 0x58
.global lbl_803C44D0
lbl_803C44D0:
	.incbin "baserom.dol", 0x3C05D0, 0x58
.global lbl_803C4528
lbl_803C4528:
	.incbin "baserom.dol", 0x3C0628, 0x3C
.global lbl_803C4564
lbl_803C4564:
	.incbin "baserom.dol", 0x3C0664, 0xC
.global lbl_803C4570
lbl_803C4570:
	.incbin "baserom.dol", 0x3C0670, 0x48
.global lbl_803C45B8
lbl_803C45B8:
	.incbin "baserom.dol", 0x3C06B8, 0x28
.global lbl_803C45E0
lbl_803C45E0:
	.incbin "baserom.dol", 0x3C06E0, 0x20
.global lbl_803C4600
lbl_803C4600:
	.incbin "baserom.dol", 0x3C0700, 0x38
.global lbl_803C4638
lbl_803C4638:
	.incbin "baserom.dol", 0x3C0738, 0x20
.global lbl_803C4658
lbl_803C4658:
	.incbin "baserom.dol", 0x3C0758, 0x10
.global lbl_803C4668
lbl_803C4668:
	.incbin "baserom.dol", 0x3C0768, 0x48
.global lbl_803C46B0
lbl_803C46B0:
	.incbin "baserom.dol", 0x3C07B0, 0x10
.global lbl_803C46C0
lbl_803C46C0:
	.incbin "baserom.dol", 0x3C07C0, 0x10
.global lbl_803C46D0
lbl_803C46D0:
	.incbin "baserom.dol", 0x3C07D0, 0x10
.global lbl_803C46E0
lbl_803C46E0:
	.incbin "baserom.dol", 0x3C07E0, 0x10
.global lbl_803C46F0
lbl_803C46F0:
	.incbin "baserom.dol", 0x3C07F0, 0x10
.global lbl_803C4700
lbl_803C4700:
	.incbin "baserom.dol", 0x3C0800, 0x10
.global lbl_803C4710
lbl_803C4710:
	.incbin "baserom.dol", 0x3C0810, 0x10
.global lbl_803C4720
lbl_803C4720:
	.incbin "baserom.dol", 0x3C0820, 0xC
.global lbl_803C472C
lbl_803C472C:
	.incbin "baserom.dol", 0x3C082C, 0xC
.global lbl_803C4738
lbl_803C4738:
	.incbin "baserom.dol", 0x3C0838, 0xC
.global lbl_803C4744
lbl_803C4744:
	.incbin "baserom.dol", 0x3C0844, 0xC
.global lbl_803C4750
lbl_803C4750:
	.incbin "baserom.dol", 0x3C0850, 0xC
.global lbl_803C475C
lbl_803C475C:
	.incbin "baserom.dol", 0x3C085C, 0xC
.global lbl_803C4768
lbl_803C4768:
	.incbin "baserom.dol", 0x3C0868, 0x10
.global lbl_803C4778
lbl_803C4778:
	.incbin "baserom.dol", 0x3C0878, 0x10
.global lbl_803C4788
lbl_803C4788:
	.incbin "baserom.dol", 0x3C0888, 0x10
.global lbl_803C4798
lbl_803C4798:
	.incbin "baserom.dol", 0x3C0898, 0x10
.global lbl_803C47A8
lbl_803C47A8:
	.incbin "baserom.dol", 0x3C08A8, 0x10
.global lbl_803C47B8
lbl_803C47B8:
	.incbin "baserom.dol", 0x3C08B8, 0x10
.global lbl_803C47C8
lbl_803C47C8:
	.incbin "baserom.dol", 0x3C08C8, 0x10
.global lbl_803C47D8
lbl_803C47D8:
	.incbin "baserom.dol", 0x3C08D8, 0x10
.global lbl_803C47E8
lbl_803C47E8:
	.incbin "baserom.dol", 0x3C08E8, 0x10
.global lbl_803C47F8
lbl_803C47F8:
	.incbin "baserom.dol", 0x3C08F8, 0x10
.global lbl_803C4808
lbl_803C4808:
	.incbin "baserom.dol", 0x3C0908, 0x10
.global lbl_803C4818
lbl_803C4818:
	.incbin "baserom.dol", 0x3C0918, 0x10
.global lbl_803C4828
lbl_803C4828:
	.incbin "baserom.dol", 0x3C0928, 0x10
.global lbl_803C4838
lbl_803C4838:
	.incbin "baserom.dol", 0x3C0938, 0x10
.global lbl_803C4848
lbl_803C4848:
	.incbin "baserom.dol", 0x3C0948, 0x10
.global lbl_803C4858
lbl_803C4858:
	.incbin "baserom.dol", 0x3C0958, 0x10
.global lbl_803C4868
lbl_803C4868:
	.incbin "baserom.dol", 0x3C0968, 0x10
.global lbl_803C4878
lbl_803C4878:
	.incbin "baserom.dol", 0x3C0978, 0x10
.global lbl_803C4888
lbl_803C4888:
	.incbin "baserom.dol", 0x3C0988, 0x10
.global lbl_803C4898
lbl_803C4898:
	.incbin "baserom.dol", 0x3C0998, 0x38
.global lbl_803C48D0
lbl_803C48D0:
	.incbin "baserom.dol", 0x3C09D0, 0x20
.global lbl_803C48F0
lbl_803C48F0:
	.incbin "baserom.dol", 0x3C09F0, 0x10
.global lbl_803C4900
lbl_803C4900:
	.incbin "baserom.dol", 0x3C0A00, 0x10
.global lbl_803C4910
lbl_803C4910:
	.incbin "baserom.dol", 0x3C0A10, 0x10
.global lbl_803C4920
lbl_803C4920:
	.incbin "baserom.dol", 0x3C0A20, 0x10
.global lbl_803C4930
lbl_803C4930:
	.incbin "baserom.dol", 0x3C0A30, 0x10
.global lbl_803C4940
lbl_803C4940:
	.incbin "baserom.dol", 0x3C0A40, 0xC
.global lbl_803C494C
lbl_803C494C:
	.incbin "baserom.dol", 0x3C0A4C, 0x44
.global lbl_803C4990
lbl_803C4990:
	.incbin "baserom.dol", 0x3C0A90, 0x10
.global lbl_803C49A0
lbl_803C49A0:
	.incbin "baserom.dol", 0x3C0AA0, 0x58
.global lbl_803C49F8
lbl_803C49F8:
	.incbin "baserom.dol", 0x3C0AF8, 0x48
.global lbl_803C4A40
lbl_803C4A40:
	.incbin "baserom.dol", 0x3C0B40, 0xC
.global lbl_803C4A4C
lbl_803C4A4C:
	.incbin "baserom.dol", 0x3C0B4C, 0x44
.global lbl_803C4A90
lbl_803C4A90:
	.incbin "baserom.dol", 0x3C0B90, 0x30
.global lbl_803C4AC0
lbl_803C4AC0:
	.incbin "baserom.dol", 0x3C0BC0, 0x28
.global lbl_803C4AE8
lbl_803C4AE8:
	.incbin "baserom.dol", 0x3C0BE8, 0x48
.global lbl_803C4B30
lbl_803C4B30:
	.incbin "baserom.dol", 0x3C0C30, 0x10
.global lbl_803C4B40
lbl_803C4B40:
	.incbin "baserom.dol", 0x3C0C40, 0x28
.global lbl_803C4B68
lbl_803C4B68:
	.incbin "baserom.dol", 0x3C0C68, 0x10
.global lbl_803C4B78
lbl_803C4B78:
	.incbin "baserom.dol", 0x3C0C78, 0x24
.global lbl_803C4B9C
lbl_803C4B9C:
	.incbin "baserom.dol", 0x3C0C9C, 0xC
.global lbl_803C4BA8
lbl_803C4BA8:
	.incbin "baserom.dol", 0x3C0CA8, 0x14
.global lbl_803C4BBC
lbl_803C4BBC:
	.incbin "baserom.dol", 0x3C0CBC, 0x10
.global lbl_803C4BCC
lbl_803C4BCC:
	.incbin "baserom.dol", 0x3C0CCC, 0x14
.global lbl_803C4BE0
lbl_803C4BE0:
	.incbin "baserom.dol", 0x3C0CE0, 0xC
.global lbl_803C4BEC
lbl_803C4BEC:
	.incbin "baserom.dol", 0x3C0CEC, 0x24
.global lbl_803C4C10
lbl_803C4C10:
	.incbin "baserom.dol", 0x3C0D10, 0x28
.global lbl_803C4C38
lbl_803C4C38:
	.incbin "baserom.dol", 0x3C0D38, 0xC
.global lbl_803C4C44
lbl_803C4C44:
	.incbin "baserom.dol", 0x3C0D44, 0x24
.global lbl_803C4C68
lbl_803C4C68:
	.incbin "baserom.dol", 0x3C0D68, 0x28
.global lbl_803C4C90
lbl_803C4C90:
	.incbin "baserom.dol", 0x3C0D90, 0x24
.global lbl_803C4CB4
lbl_803C4CB4:
	.incbin "baserom.dol", 0x3C0DB4, 0x24
.global lbl_803C4CD8
lbl_803C4CD8:
	.incbin "baserom.dol", 0x3C0DD8, 0x28
.global lbl_803C4D00
lbl_803C4D00:
	.incbin "baserom.dol", 0x3C0E00, 0x28
.global lbl_803C4D28
lbl_803C4D28:
	.incbin "baserom.dol", 0x3C0E28, 0x24
.global lbl_803C4D4C
lbl_803C4D4C:
	.incbin "baserom.dol", 0x3C0E4C, 0x24
.global lbl_803C4D70
lbl_803C4D70:
	.incbin "baserom.dol", 0x3C0E70, 0x28
.global lbl_803C4D98
lbl_803C4D98:
	.incbin "baserom.dol", 0x3C0E98, 0x28
.global lbl_803C4DC0
lbl_803C4DC0:
	.incbin "baserom.dol", 0x3C0EC0, 0x28
.global lbl_803C4DE8
lbl_803C4DE8:
	.incbin "baserom.dol", 0x3C0EE8, 0x28
.global lbl_803C4E10
lbl_803C4E10:
	.incbin "baserom.dol", 0x3C0F10, 0x28
.global lbl_803C4E38
lbl_803C4E38:
	.incbin "baserom.dol", 0x3C0F38, 0x10
.global lbl_803C4E48
lbl_803C4E48:
	.incbin "baserom.dol", 0x3C0F48, 0x10
.global lbl_803C4E58
lbl_803C4E58:
	.incbin "baserom.dol", 0x3C0F58, 0x24
.global lbl_803C4E7C
lbl_803C4E7C:
	.incbin "baserom.dol", 0x3C0F7C, 0x24
.global lbl_803C4EA0
lbl_803C4EA0:
	.incbin "baserom.dol", 0x3C0FA0, 0x28
.global lbl_803C4EC8
lbl_803C4EC8:
	.incbin "baserom.dol", 0x3C0FC8, 0x48
.global lbl_803C4F10
lbl_803C4F10:
	.incbin "baserom.dol", 0x3C1010, 0x10
.global lbl_803C4F20
lbl_803C4F20:
	.incbin "baserom.dol", 0x3C1020, 0x28
.global lbl_803C4F48
lbl_803C4F48:
	.incbin "baserom.dol", 0x3C1048, 0x10
.global lbl_803C4F58
lbl_803C4F58:
	.incbin "baserom.dol", 0x3C1058, 0x28
.global lbl_803C4F80
lbl_803C4F80:
	.incbin "baserom.dol", 0x3C1080, 0x48
.global lbl_803C4FC8
lbl_803C4FC8:
	.incbin "baserom.dol", 0x3C10C8, 0x10
.global lbl_803C4FD8
lbl_803C4FD8:
	.incbin "baserom.dol", 0x3C10D8, 0x80
.global lbl_803C5058
lbl_803C5058:
	.incbin "baserom.dol", 0x3C1158, 0x7C
.global lbl_803C50D4
lbl_803C50D4:
	.incbin "baserom.dol", 0x3C11D4, 0xC8
.global lbl_803C519C
lbl_803C519C:
	.incbin "baserom.dol", 0x3C129C, 0xC4
.global lbl_803C5260
lbl_803C5260:
	.incbin "baserom.dol", 0x3C1360, 0x28
.global lbl_803C5288
lbl_803C5288:
	.incbin "baserom.dol", 0x3C1388, 0x28
.global lbl_803C52B0
lbl_803C52B0:
	.incbin "baserom.dol", 0x3C13B0, 0x68
.global lbl_803C5318
lbl_803C5318:
	.incbin "baserom.dol", 0x3C1418, 0xE0
.global lbl_803C53F8
lbl_803C53F8:
	.incbin "baserom.dol", 0x3C14F8, 0x20
.global lbl_803C5418
lbl_803C5418:
	.incbin "baserom.dol", 0x3C1518, 0x10
.global lbl_803C5428
lbl_803C5428:
	.incbin "baserom.dol", 0x3C1528, 0x18
.global lbl_803C5440
lbl_803C5440:
	.incbin "baserom.dol", 0x3C1540, 0x20
.global lbl_803C5460
lbl_803C5460:
	.incbin "baserom.dol", 0x3C1560, 0x20
.global lbl_803C5480
lbl_803C5480:
	.incbin "baserom.dol", 0x3C1580, 0x38
.global lbl_803C54B8
lbl_803C54B8:
	.incbin "baserom.dol", 0x3C15B8, 0x20
.global lbl_803C54D8
lbl_803C54D8:
	.incbin "baserom.dol", 0x3C15D8, 0x60
.global lbl_803C5538
lbl_803C5538:
	.incbin "baserom.dol", 0x3C1638, 0x10
.global lbl_803C5548
lbl_803C5548:
	.incbin "baserom.dol", 0x3C1648, 0x3D4
.global lbl_803C591C
lbl_803C591C:
	.incbin "baserom.dol", 0x3C1A1C, 0xA4
.global lbl_803C59C0
lbl_803C59C0:
	.incbin "baserom.dol", 0x3C1AC0, 0xC
.global lbl_803C59CC
lbl_803C59CC:
	.incbin "baserom.dol", 0x3C1ACC, 0xC
.global lbl_803C59D8
lbl_803C59D8:
	.incbin "baserom.dol", 0x3C1AD8, 0x18
.global lbl_803C59F0
lbl_803C59F0:
	.incbin "baserom.dol", 0x3C1AF0, 0xC0
.global lbl_803C5AB0
lbl_803C5AB0:
	.incbin "baserom.dol", 0x3C1BB0, 0x10
.global lbl_803C5AC0
lbl_803C5AC0:
	.incbin "baserom.dol", 0x3C1BC0, 0x18
.global lbl_803C5AD8
lbl_803C5AD8:
	.incbin "baserom.dol", 0x3C1BD8, 0xA4
.global lbl_803C5B7C
lbl_803C5B7C:
	.incbin "baserom.dol", 0x3C1C7C, 0x6C
.global lbl_803C5BE8
lbl_803C5BE8:
	.incbin "baserom.dol", 0x3C1CE8, 0x28
.global lbl_803C5C10
lbl_803C5C10:
	.incbin "baserom.dol", 0x3C1D10, 0x20
.global lbl_803C5C30
lbl_803C5C30:
	.incbin "baserom.dol", 0x3C1D30, 0x18
.global lbl_803C5C48
lbl_803C5C48:
	.incbin "baserom.dol", 0x3C1D48, 0x90
.global lbl_803C5CD8
lbl_803C5CD8:
	.incbin "baserom.dol", 0x3C1DD8, 0x10
.global lbl_803C5CE8
lbl_803C5CE8:
	.incbin "baserom.dol", 0x3C1DE8, 0x48
.global lbl_803C5D30
lbl_803C5D30:
	.incbin "baserom.dol", 0x3C1E30, 0x28
.global lbl_803C5D58
lbl_803C5D58:
	.incbin "baserom.dol", 0x3C1E58, 0x54
.global lbl_803C5DAC
lbl_803C5DAC:
	.incbin "baserom.dol", 0x3C1EAC, 0x84
.global lbl_803C5E30
lbl_803C5E30:
	.incbin "baserom.dol", 0x3C1F30, 0x28
.global lbl_803C5E58
lbl_803C5E58:
	.incbin "baserom.dol", 0x3C1F58, 0x100
.global lbl_803C5F58
lbl_803C5F58:
	.incbin "baserom.dol", 0x3C2058, 0x60
.global lbl_803C5FB8
lbl_803C5FB8:
	.incbin "baserom.dol", 0x3C20B8, 0xC8
.global lbl_803C6080
lbl_803C6080:
	.incbin "baserom.dol", 0x3C2180, 0x10
.global lbl_803C6090
lbl_803C6090:
	.incbin "baserom.dol", 0x3C2190, 0x18
.global lbl_803C60A8
lbl_803C60A8:
	.incbin "baserom.dol", 0x3C21A8, 0x10
.global lbl_803C60B8
lbl_803C60B8:
	.incbin "baserom.dol", 0x3C21B8, 0x90
.global lbl_803C6148
lbl_803C6148:
	.incbin "baserom.dol", 0x3C2248, 0xC4
.global lbl_803C620C
lbl_803C620C:
	.incbin "baserom.dol", 0x3C230C, 0x2C
.global lbl_803C6238
lbl_803C6238:
	.incbin "baserom.dol", 0x3C2338, 0x1C
.global lbl_803C6254
lbl_803C6254:
	.incbin "baserom.dol", 0x3C2354, 0x210
.global lbl_803C6464
lbl_803C6464:
	.incbin "baserom.dol", 0x3C2564, 0x94
.global lbl_803C64F8
lbl_803C64F8:
	.incbin "baserom.dol", 0x3C25F8, 0x28
.global lbl_803C6520
lbl_803C6520:
	.incbin "baserom.dol", 0x3C2620, 0x28
.global lbl_803C6548
lbl_803C6548:
	.incbin "baserom.dol", 0x3C2648, 0x28
.global lbl_803C6570
lbl_803C6570:
	.incbin "baserom.dol", 0x3C2670, 0x50
.global lbl_803C65C0
lbl_803C65C0:
	.incbin "baserom.dol", 0x3C26C0, 0x30
.global lbl_803C65F0
lbl_803C65F0:
	.incbin "baserom.dol", 0x3C26F0, 0x40
.global lbl_803C6630
lbl_803C6630:
	.incbin "baserom.dol", 0x3C2730, 0x28
.global lbl_803C6658
lbl_803C6658:
	.incbin "baserom.dol", 0x3C2758, 0x28
.global lbl_803C6680
lbl_803C6680:
	.incbin "baserom.dol", 0x3C2780, 0x28
.global lbl_803C66A8
lbl_803C66A8:
	.incbin "baserom.dol", 0x3C27A8, 0x28
.global lbl_803C66D0
lbl_803C66D0:
	.incbin "baserom.dol", 0x3C27D0, 0x28
.global lbl_803C66F8
lbl_803C66F8:
	.incbin "baserom.dol", 0x3C27F8, 0x28
.global lbl_803C6720
lbl_803C6720:
	.incbin "baserom.dol", 0x3C2820, 0x1C
.global lbl_803C673C
lbl_803C673C:
	.incbin "baserom.dol", 0x3C283C, 0x1AC
.global lbl_803C68E8
lbl_803C68E8:
	.incbin "baserom.dol", 0x3C29E8, 0xC8
.global lbl_803C69B0
lbl_803C69B0:
	.incbin "baserom.dol", 0x3C2AB0, 0x70
.global lbl_803C6A20
lbl_803C6A20:
	.incbin "baserom.dol", 0x3C2B20, 0x28
.global lbl_803C6A48
lbl_803C6A48:
	.incbin "baserom.dol", 0x3C2B48, 0x58
.global lbl_803C6AA0
lbl_803C6AA0:
	.incbin "baserom.dol", 0x3C2BA0, 0x6C
.global lbl_803C6B0C
lbl_803C6B0C:
	.incbin "baserom.dol", 0x3C2C0C, 0x2C
.global lbl_803C6B38
lbl_803C6B38:
	.incbin "baserom.dol", 0x3C2C38, 0x20
.global lbl_803C6B58
lbl_803C6B58:
	.incbin "baserom.dol", 0x3C2C58, 0x30
.global lbl_803C6B88
lbl_803C6B88:
	.incbin "baserom.dol", 0x3C2C88, 0x30
.global lbl_803C6BB8
lbl_803C6BB8:
	.incbin "baserom.dol", 0x3C2CB8, 0x30
.global lbl_803C6BE8
lbl_803C6BE8:
	.incbin "baserom.dol", 0x3C2CE8, 0x28
.global lbl_803C6C10
lbl_803C6C10:
	.incbin "baserom.dol", 0x3C2D10, 0x138
.global lbl_803C6D48
lbl_803C6D48:
	.incbin "baserom.dol", 0x3C2E48, 0x88
.global lbl_803C6DD0
lbl_803C6DD0:
	.incbin "baserom.dol", 0x3C2ED0, 0x28
.global lbl_803C6DF8
lbl_803C6DF8:
	.incbin "baserom.dol", 0x3C2EF8, 0x28
.global lbl_803C6E20
lbl_803C6E20:
	.incbin "baserom.dol", 0x3C2F20, 0x60
.global lbl_803C6E80
lbl_803C6E80:
	.incbin "baserom.dol", 0x3C2F80, 0xB4
.global lbl_803C6F34
lbl_803C6F34:
	.incbin "baserom.dol", 0x3C3034, 0x2C
.global lbl_803C6F60
lbl_803C6F60:
	.incbin "baserom.dol", 0x3C3060, 0x90
.global lbl_803C6FF0
lbl_803C6FF0:
	.incbin "baserom.dol", 0x3C30F0, 0xC4
.global lbl_803C70B4
lbl_803C70B4:
	.incbin "baserom.dol", 0x3C31B4, 0x14
.global lbl_803C70C8
lbl_803C70C8:
	.incbin "baserom.dol", 0x3C31C8, 0x38
.global lbl_803C7100
lbl_803C7100:
	.incbin "baserom.dol", 0x3C3200, 0x30
.global lbl_803C7130
lbl_803C7130:
	.incbin "baserom.dol", 0x3C3230, 0x28
.global lbl_803C7158
lbl_803C7158:
	.incbin "baserom.dol", 0x3C3258, 0x48
.global lbl_803C71A0
lbl_803C71A0:
	.incbin "baserom.dol", 0x3C32A0, 0x70
.global lbl_803C7210
lbl_803C7210:
	.incbin "baserom.dol", 0x3C3310, 0xD0
.global lbl_803C72E0
lbl_803C72E0:
	.incbin "baserom.dol", 0x3C33E0, 0x198
.global lbl_803C7478
lbl_803C7478:
	.incbin "baserom.dol", 0x3C3578, 0xA8
.global lbl_803C7520
lbl_803C7520:
	.incbin "baserom.dol", 0x3C3620, 0x28
.global lbl_803C7548
lbl_803C7548:
	.incbin "baserom.dol", 0x3C3648, 0x18
.global lbl_803C7560
lbl_803C7560:
	.incbin "baserom.dol", 0x3C3660, 0x18
.global lbl_803C7578
lbl_803C7578:
	.incbin "baserom.dol", 0x3C3678, 0x30
.global lbl_803C75A8
lbl_803C75A8:
	.incbin "baserom.dol", 0x3C36A8, 0x28
.global lbl_803C75D0
lbl_803C75D0:
	.incbin "baserom.dol", 0x3C36D0, 0x28
.global lbl_803C75F8
lbl_803C75F8:
	.incbin "baserom.dol", 0x3C36F8, 0x30
.global lbl_803C7628
lbl_803C7628:
	.incbin "baserom.dol", 0x3C3728, 0x30
.global lbl_803C7658
lbl_803C7658:
	.incbin "baserom.dol", 0x3C3758, 0x50
.global lbl_803C76A8
lbl_803C76A8:
	.incbin "baserom.dol", 0x3C37A8, 0x20
.global lbl_803C76C8
lbl_803C76C8:
	.incbin "baserom.dol", 0x3C37C8, 0x28
.global lbl_803C76F0
lbl_803C76F0:
	.incbin "baserom.dol", 0x3C37F0, 0x28
.global lbl_803C7718
lbl_803C7718:
	.incbin "baserom.dol", 0x3C3818, 0x80
.global lbl_803C7798
lbl_803C7798:
	.incbin "baserom.dol", 0x3C3898, 0x10
.global lbl_803C77A8
lbl_803C77A8:
	.incbin "baserom.dol", 0x3C38A8, 0xC
.global lbl_803C77B4
lbl_803C77B4:
	.incbin "baserom.dol", 0x3C38B4, 0xC
.global lbl_803C77C0
lbl_803C77C0:
	.incbin "baserom.dol", 0x3C38C0, 0x10
.global lbl_803C77D0
lbl_803C77D0:
	.incbin "baserom.dol", 0x3C38D0, 0xC
.global lbl_803C77DC
lbl_803C77DC:
	.incbin "baserom.dol", 0x3C38DC, 0xC
.global lbl_803C77E8
lbl_803C77E8:
	.incbin "baserom.dol", 0x3C38E8, 0x10
.global lbl_803C77F8
lbl_803C77F8:
	.incbin "baserom.dol", 0x3C38F8, 0xB4
.global lbl_803C78AC
lbl_803C78AC:
	.incbin "baserom.dol", 0x3C39AC, 0xC
.global lbl_803C78B8
lbl_803C78B8:
	.incbin "baserom.dol", 0x3C39B8, 0xC
.global lbl_803C78C4
lbl_803C78C4:
	.incbin "baserom.dol", 0x3C39C4, 0xC
.global lbl_803C78D0
lbl_803C78D0:
	.incbin "baserom.dol", 0x3C39D0, 0xC
.global lbl_803C78DC
lbl_803C78DC:
	.incbin "baserom.dol", 0x3C39DC, 0xC
.global lbl_803C78E8
lbl_803C78E8:
	.incbin "baserom.dol", 0x3C39E8, 0x10
.global lbl_803C78F8
lbl_803C78F8:
	.incbin "baserom.dol", 0x3C39F8, 0x10
.global lbl_803C7908
lbl_803C7908:
	.incbin "baserom.dol", 0x3C3A08, 0x10
.global lbl_803C7918
lbl_803C7918:
	.incbin "baserom.dol", 0x3C3A18, 0x44
.global lbl_803C795C
lbl_803C795C:
	.incbin "baserom.dol", 0x3C3A5C, 0xC
.global lbl_803C7968
lbl_803C7968:
	.incbin "baserom.dol", 0x3C3A68, 0xDC
.global lbl_803C7A44
lbl_803C7A44:
	.incbin "baserom.dol", 0x3C3B44, 0xC
.global lbl_803C7A50
lbl_803C7A50:
	.incbin "baserom.dol", 0x3C3B50, 0x10
.global lbl_803C7A60
lbl_803C7A60:
	.incbin "baserom.dol", 0x3C3B60, 0x20
.global lbl_803C7A80
lbl_803C7A80:
	.incbin "baserom.dol", 0x3C3B80, 0x20
.global lbl_803C7AA0
lbl_803C7AA0:
	.incbin "baserom.dol", 0x3C3BA0, 0x21C
.global lbl_803C7CBC
lbl_803C7CBC:
	.incbin "baserom.dol", 0x3C3DBC, 0xC
.global lbl_803C7CC8
lbl_803C7CC8:
	.incbin "baserom.dol", 0x3C3DC8, 0x40
.global lbl_803C7D08
lbl_803C7D08:
	.incbin "baserom.dol", 0x3C3E08, 0x20
.global lbl_803C7D28
lbl_803C7D28:
	.incbin "baserom.dol", 0x3C3E28, 0x68
.global lbl_803C7D90
lbl_803C7D90:
	.incbin "baserom.dol", 0x3C3E90, 0x10
.global lbl_803C7DA0
lbl_803C7DA0:
	.incbin "baserom.dol", 0x3C3EA0, 0xC
.global lbl_803C7DAC
lbl_803C7DAC:
	.incbin "baserom.dol", 0x3C3EAC, 0x14
.global lbl_803C7DC0
lbl_803C7DC0:
	.incbin "baserom.dol", 0x3C3EC0, 0x10
.global lbl_803C7DD0
lbl_803C7DD0:
	.incbin "baserom.dol", 0x3C3ED0, 0x20
.global lbl_803C7DF0
lbl_803C7DF0:
	.incbin "baserom.dol", 0x3C3EF0, 0x20
.global lbl_803C7E10
lbl_803C7E10:
	.incbin "baserom.dol", 0x3C3F10, 0x40
.global lbl_803C7E50
lbl_803C7E50:
	.incbin "baserom.dol", 0x3C3F50, 0x10
.global lbl_803C7E60
lbl_803C7E60:
	.incbin "baserom.dol", 0x3C3F60, 0x10
.global lbl_803C7E70
lbl_803C7E70:
	.incbin "baserom.dol", 0x3C3F70, 0xC
.global lbl_803C7E7C
lbl_803C7E7C:
	.incbin "baserom.dol", 0x3C3F7C, 0xC
.global lbl_803C7E88
lbl_803C7E88:
	.incbin "baserom.dol", 0x3C3F88, 0x10
.global lbl_803C7E98
lbl_803C7E98:
	.incbin "baserom.dol", 0x3C3F98, 0x10
.global lbl_803C7EA8
lbl_803C7EA8:
	.incbin "baserom.dol", 0x3C3FA8, 0x10
.global lbl_803C7EB8
lbl_803C7EB8:
	.incbin "baserom.dol", 0x3C3FB8, 0x10
.global lbl_803C7EC8
lbl_803C7EC8:
	.incbin "baserom.dol", 0x3C3FC8, 0x10
.global lbl_803C7ED8
lbl_803C7ED8:
	.incbin "baserom.dol", 0x3C3FD8, 0x10
.global lbl_803C7EE8
lbl_803C7EE8:
	.incbin "baserom.dol", 0x3C3FE8, 0x10
.global lbl_803C7EF8
lbl_803C7EF8:
	.incbin "baserom.dol", 0x3C3FF8, 0x10
.global lbl_803C7F08
lbl_803C7F08:
	.incbin "baserom.dol", 0x3C4008, 0xC
.global lbl_803C7F14
lbl_803C7F14:
	.incbin "baserom.dol", 0x3C4014, 0xC
.global lbl_803C7F20
lbl_803C7F20:
	.incbin "baserom.dol", 0x3C4020, 0xC
.global lbl_803C7F2C
lbl_803C7F2C:
	.incbin "baserom.dol", 0x3C402C, 0xC
.global lbl_803C7F38
lbl_803C7F38:
	.incbin "baserom.dol", 0x3C4038, 0xC
.global lbl_803C7F44
lbl_803C7F44:
	.incbin "baserom.dol", 0x3C4044, 0xC
.global lbl_803C7F50
lbl_803C7F50:
	.incbin "baserom.dol", 0x3C4050, 0xC
.global lbl_803C7F5C
lbl_803C7F5C:
	.incbin "baserom.dol", 0x3C405C, 0x2C
.global lbl_803C7F88
lbl_803C7F88:
	.incbin "baserom.dol", 0x3C4088, 0x60
.global lbl_803C7FE8
lbl_803C7FE8:
	.incbin "baserom.dol", 0x3C40E8, 0x40
.global lbl_803C8028
lbl_803C8028:
	.incbin "baserom.dol", 0x3C4128, 0x40
.global lbl_803C8068
lbl_803C8068:
	.incbin "baserom.dol", 0x3C4168, 0x30
.global lbl_803C8098
lbl_803C8098:
	.incbin "baserom.dol", 0x3C4198, 0x30
.global lbl_803C80C8
lbl_803C80C8:
	.incbin "baserom.dol", 0x3C41C8, 0x40
.global lbl_803C8108
lbl_803C8108:
	.incbin "baserom.dol", 0x3C4208, 0x10
.global lbl_803C8118
lbl_803C8118:
	.incbin "baserom.dol", 0x3C4218, 0x20
.global lbl_803C8138
lbl_803C8138:
	.incbin "baserom.dol", 0x3C4238, 0x40
.global lbl_803C8178
lbl_803C8178:
	.incbin "baserom.dol", 0x3C4278, 0x40
.global lbl_803C81B8
lbl_803C81B8:
	.incbin "baserom.dol", 0x3C42B8, 0x20
.global lbl_803C81D8
lbl_803C81D8:
	.incbin "baserom.dol", 0x3C42D8, 0x10
.global lbl_803C81E8
lbl_803C81E8:
	.incbin "baserom.dol", 0x3C42E8, 0x10
.global lbl_803C81F8
lbl_803C81F8:
	.incbin "baserom.dol", 0x3C42F8, 0x44
.global lbl_803C823C
lbl_803C823C:
	.incbin "baserom.dol", 0x3C433C, 0x44
.global lbl_803C8280
lbl_803C8280:
	.incbin "baserom.dol", 0x3C4380, 0x48
.global lbl_803C82C8
lbl_803C82C8:
	.incbin "baserom.dol", 0x3C43C8, 0x98
.global lbl_803C8360
lbl_803C8360:
	.incbin "baserom.dol", 0x3C4460, 0x20
.global lbl_803C8380
lbl_803C8380:
	.incbin "baserom.dol", 0x3C4480, 0x20
.global lbl_803C83A0
lbl_803C83A0:
	.incbin "baserom.dol", 0x3C44A0, 0x10
.global lbl_803C83B0
lbl_803C83B0:
	.incbin "baserom.dol", 0x3C44B0, 0x10
.global lbl_803C83C0
lbl_803C83C0:
	.incbin "baserom.dol", 0x3C44C0, 0x10
.global lbl_803C83D0
lbl_803C83D0:
	.incbin "baserom.dol", 0x3C44D0, 0x10
.global lbl_803C83E0
lbl_803C83E0:
	.incbin "baserom.dol", 0x3C44E0, 0x10
.global lbl_803C83F0
lbl_803C83F0:
	.incbin "baserom.dol", 0x3C44F0, 0x10
.global lbl_803C8400
lbl_803C8400:
	.incbin "baserom.dol", 0x3C4500, 0x10
.global lbl_803C8410
lbl_803C8410:
	.incbin "baserom.dol", 0x3C4510, 0x10
.global lbl_803C8420
lbl_803C8420:
	.incbin "baserom.dol", 0x3C4520, 0x10
.global lbl_803C8430
lbl_803C8430:
	.incbin "baserom.dol", 0x3C4530, 0x30
.global lbl_803C8460
lbl_803C8460:
	.incbin "baserom.dol", 0x3C4560, 0x10
.global lbl_803C8470
lbl_803C8470:
	.incbin "baserom.dol", 0x3C4570, 0x10
.global lbl_803C8480
lbl_803C8480:
	.incbin "baserom.dol", 0x3C4580, 0x10
.global lbl_803C8490
lbl_803C8490:
	.incbin "baserom.dol", 0x3C4590, 0x10
.global lbl_803C84A0
lbl_803C84A0:
	.incbin "baserom.dol", 0x3C45A0, 0x10
.global lbl_803C84B0
lbl_803C84B0:
	.incbin "baserom.dol", 0x3C45B0, 0x10
.global lbl_803C84C0
lbl_803C84C0:
	.incbin "baserom.dol", 0x3C45C0, 0x10
.global lbl_803C84D0
lbl_803C84D0:
	.incbin "baserom.dol", 0x3C45D0, 0x10
.global lbl_803C84E0
lbl_803C84E0:
	.incbin "baserom.dol", 0x3C45E0, 0x10
.global lbl_803C84F0
lbl_803C84F0:
	.incbin "baserom.dol", 0x3C45F0, 0x10
.global lbl_803C8500
lbl_803C8500:
	.incbin "baserom.dol", 0x3C4600, 0x10
.global lbl_803C8510
lbl_803C8510:
	.incbin "baserom.dol", 0x3C4610, 0x10
.global lbl_803C8520
lbl_803C8520:
	.incbin "baserom.dol", 0x3C4620, 0x10
.global lbl_803C8530
lbl_803C8530:
	.incbin "baserom.dol", 0x3C4630, 0x10
.global lbl_803C8540
lbl_803C8540:
	.incbin "baserom.dol", 0x3C4640, 0x10
.global lbl_803C8550
lbl_803C8550:
	.incbin "baserom.dol", 0x3C4650, 0x10
.global lbl_803C8560
lbl_803C8560:
	.incbin "baserom.dol", 0x3C4660, 0x10
.global lbl_803C8570
lbl_803C8570:
	.incbin "baserom.dol", 0x3C4670, 0x10
.global lbl_803C8580
lbl_803C8580:
	.incbin "baserom.dol", 0x3C4680, 0x10
.global lbl_803C8590
lbl_803C8590:
	.incbin "baserom.dol", 0x3C4690, 0x10
.global lbl_803C85A0
lbl_803C85A0:
	.incbin "baserom.dol", 0x3C46A0, 0x30
.global lbl_803C85D0
lbl_803C85D0:
	.incbin "baserom.dol", 0x3C46D0, 0x30
.global lbl_803C8600
lbl_803C8600:
	.incbin "baserom.dol", 0x3C4700, 0x30
.global lbl_803C8630
lbl_803C8630:
	.incbin "baserom.dol", 0x3C4730, 0x30
.global lbl_803C8660
lbl_803C8660:
	.incbin "baserom.dol", 0x3C4760, 0x30
.global lbl_803C8690
lbl_803C8690:
	.incbin "baserom.dol", 0x3C4790, 0x30
.global lbl_803C86C0
lbl_803C86C0:
	.incbin "baserom.dol", 0x3C47C0, 0x30
.global lbl_803C86F0
lbl_803C86F0:
	.incbin "baserom.dol", 0x3C47F0, 0x30
.global lbl_803C8720
lbl_803C8720:
	.incbin "baserom.dol", 0x3C4820, 0x30
.global lbl_803C8750
lbl_803C8750:
	.incbin "baserom.dol", 0x3C4850, 0x30
.global lbl_803C8780
lbl_803C8780:
	.incbin "baserom.dol", 0x3C4880, 0x28
.global lbl_803C87A8
lbl_803C87A8:
	.incbin "baserom.dol", 0x3C48A8, 0x1C
.global lbl_803C87C4
lbl_803C87C4:
	.incbin "baserom.dol", 0x3C48C4, 0x44
.global lbl_803C8808
lbl_803C8808:
	.incbin "baserom.dol", 0x3C4908, 0x10
.global lbl_803C8818
lbl_803C8818:
	.incbin "baserom.dol", 0x3C4918, 0x10
.global lbl_803C8828
lbl_803C8828:
	.incbin "baserom.dol", 0x3C4928, 0x10
.global lbl_803C8838
lbl_803C8838:
	.incbin "baserom.dol", 0x3C4938, 0x10
.global lbl_803C8848
lbl_803C8848:
	.incbin "baserom.dol", 0x3C4948, 0x10
.global lbl_803C8858
lbl_803C8858:
	.incbin "baserom.dol", 0x3C4958, 0x10
.global lbl_803C8868
lbl_803C8868:
	.incbin "baserom.dol", 0x3C4968, 0x10
.global lbl_803C8878
lbl_803C8878:
	.incbin "baserom.dol", 0x3C4978, 0x10
.global lbl_803C8888
lbl_803C8888:
	.incbin "baserom.dol", 0x3C4988, 0x10
.global lbl_803C8898
lbl_803C8898:
	.incbin "baserom.dol", 0x3C4998, 0x10
.global lbl_803C88A8
lbl_803C88A8:
	.incbin "baserom.dol", 0x3C49A8, 0x10
.global lbl_803C88B8
lbl_803C88B8:
	.incbin "baserom.dol", 0x3C49B8, 0x20
.global lbl_803C88D8
lbl_803C88D8:
	.incbin "baserom.dol", 0x3C49D8, 0x20
.global lbl_803C88F8
lbl_803C88F8:
	.incbin "baserom.dol", 0x3C49F8, 0x30
.global lbl_803C8928
lbl_803C8928:
	.incbin "baserom.dol", 0x3C4A28, 0x10
.global lbl_803C8938
lbl_803C8938:
	.incbin "baserom.dol", 0x3C4A38, 0x20
.global lbl_803C8958
lbl_803C8958:
	.incbin "baserom.dol", 0x3C4A58, 0x18
.global lbl_803C8970
lbl_803C8970:
	.incbin "baserom.dol", 0x3C4A70, 0x18
.global lbl_803C8988
lbl_803C8988:
	.incbin "baserom.dol", 0x3C4A88, 0xC
.global lbl_803C8994
lbl_803C8994:
	.incbin "baserom.dol", 0x3C4A94, 0xC
.global lbl_803C89A0
lbl_803C89A0:
	.incbin "baserom.dol", 0x3C4AA0, 0x28
.global lbl_803C89C8
lbl_803C89C8:
	.incbin "baserom.dol", 0x3C4AC8, 0x38
.global lbl_803C8A00
lbl_803C8A00:
	.incbin "baserom.dol", 0x3C4B00, 0x80
.global lbl_803C8A80
lbl_803C8A80:
	.incbin "baserom.dol", 0x3C4B80, 0x28
.global lbl_803C8AA8
lbl_803C8AA8:
	.incbin "baserom.dol", 0x3C4BA8, 0x24
.global lbl_803C8ACC
lbl_803C8ACC:
	.incbin "baserom.dol", 0x3C4BCC, 0x28
.global lbl_803C8AF4
lbl_803C8AF4:
	.incbin "baserom.dol", 0x3C4BF4, 0x2C
.global lbl_803C8B20
lbl_803C8B20:
	.incbin "baserom.dol", 0x3C4C20, 0x38
.global lbl_803C8B58
lbl_803C8B58:
	.incbin "baserom.dol", 0x3C4C58, 0x38
.global lbl_803C8B90
lbl_803C8B90:
	.incbin "baserom.dol", 0x3C4C90, 0x20
.global lbl_803C8BB0
lbl_803C8BB0:
	.incbin "baserom.dol", 0x3C4CB0, 0x2C
.global lbl_803C8BDC
lbl_803C8BDC:
	.incbin "baserom.dol", 0x3C4CDC, 0x2C
.global lbl_803C8C08
lbl_803C8C08:
	.incbin "baserom.dol", 0x3C4D08, 0x3C
.global lbl_803C8C44
lbl_803C8C44:
	.incbin "baserom.dol", 0x3C4D44, 0x28
.global lbl_803C8C6C
lbl_803C8C6C:
	.incbin "baserom.dol", 0x3C4D6C, 0xA0
.global lbl_803C8D0C
lbl_803C8D0C:
	.incbin "baserom.dol", 0x3C4E0C, 0x20
.global lbl_803C8D2C
lbl_803C8D2C:
	.incbin "baserom.dol", 0x3C4E2C, 0x3C
.global lbl_803C8D68
lbl_803C8D68:
	.incbin "baserom.dol", 0x3C4E68, 0x3C
.global lbl_803C8DA4
lbl_803C8DA4:
	.incbin "baserom.dol", 0x3C4EA4, 0x2C
.global lbl_803C8DD0
lbl_803C8DD0:
	.incbin "baserom.dol", 0x3C4ED0, 0x44
.global lbl_803C8E14
lbl_803C8E14:
	.incbin "baserom.dol", 0x3C4F14, 0xC
.global lbl_803C8E20
lbl_803C8E20:
	.incbin "baserom.dol", 0x3C4F20, 0xC
.global lbl_803C8E2C
lbl_803C8E2C:
	.incbin "baserom.dol", 0x3C4F2C, 0xC
.global lbl_803C8E38
lbl_803C8E38:
	.incbin "baserom.dol", 0x3C4F38, 0x58
.global lbl_803C8E90
lbl_803C8E90:
	.incbin "baserom.dol", 0x3C4F90, 0x20
.global lbl_803C8EB0
lbl_803C8EB0:
	.incbin "baserom.dol", 0x3C4FB0, 0xC
.global lbl_803C8EBC
lbl_803C8EBC:
	.incbin "baserom.dol", 0x3C4FBC, 0xC
.global lbl_803C8EC8
lbl_803C8EC8:
	.incbin "baserom.dol", 0x3C4FC8, 0xC
.global lbl_803C8ED4
lbl_803C8ED4:
	.incbin "baserom.dol", 0x3C4FD4, 0xC
.global lbl_803C8EE0
lbl_803C8EE0:
	.incbin "baserom.dol", 0x3C4FE0, 0x50
.global lbl_803C8F30
lbl_803C8F30:
	.incbin "baserom.dol", 0x3C5030, 0x20
.global lbl_803C8F50
lbl_803C8F50:
	.incbin "baserom.dol", 0x3C5050, 0x20
.global lbl_803C8F70
lbl_803C8F70:
	.incbin "baserom.dol", 0x3C5070, 0x10
.global lbl_803C8F80
lbl_803C8F80:
	.incbin "baserom.dol", 0x3C5080, 0x50
.global lbl_803C8FD0
lbl_803C8FD0:
	.incbin "baserom.dol", 0x3C50D0, 0x20
.global lbl_803C8FF0
lbl_803C8FF0:
	.incbin "baserom.dol", 0x3C50F0, 0x50
.global lbl_803C9040
lbl_803C9040:
	.incbin "baserom.dol", 0x3C5140, 0xC
.global lbl_803C904C
lbl_803C904C:
	.incbin "baserom.dol", 0x3C514C, 0xC
.global lbl_803C9058
lbl_803C9058:
	.incbin "baserom.dol", 0x3C5158, 0xC
.global lbl_803C9064
lbl_803C9064:
	.incbin "baserom.dol", 0x3C5164, 0xC
.global lbl_803C9070
lbl_803C9070:
	.incbin "baserom.dol", 0x3C5170, 0x10
.global lbl_803C9080
lbl_803C9080:
	.incbin "baserom.dol", 0x3C5180, 0x20
.global lbl_803C90A0
lbl_803C90A0:
	.incbin "baserom.dol", 0x3C51A0, 0xC
.global lbl_803C90AC
lbl_803C90AC:
	.incbin "baserom.dol", 0x3C51AC, 0xC
.global lbl_803C90B8
lbl_803C90B8:
	.incbin "baserom.dol", 0x3C51B8, 0x20
.global lbl_803C90D8
lbl_803C90D8:
	.incbin "baserom.dol", 0x3C51D8, 0x10
.global lbl_803C90E8
lbl_803C90E8:
	.incbin "baserom.dol", 0x3C51E8, 0x18
.global lbl_803C9100
lbl_803C9100:
	.incbin "baserom.dol", 0x3C5200, 0x28
.global lbl_803C9128
lbl_803C9128:
	.incbin "baserom.dol", 0x3C5228, 0x20
.global lbl_803C9148
lbl_803C9148:
	.incbin "baserom.dol", 0x3C5248, 0x20
.global lbl_803C9168
lbl_803C9168:
	.incbin "baserom.dol", 0x3C5268, 0x20
.global lbl_803C9188
lbl_803C9188:
	.incbin "baserom.dol", 0x3C5288, 0x64
.global lbl_803C91EC
lbl_803C91EC:
	.incbin "baserom.dol", 0x3C52EC, 0x20
.global lbl_803C920C
lbl_803C920C:
	.incbin "baserom.dol", 0x3C530C, 0x38
.global lbl_803C9244
lbl_803C9244:
	.incbin "baserom.dol", 0x3C5344, 0x1C
.global lbl_803C9260
lbl_803C9260:
	.incbin "baserom.dol", 0x3C5360, 0x28
.global lbl_803C9288
lbl_803C9288:
	.incbin "baserom.dol", 0x3C5388, 0x90
.global lbl_803C9318
lbl_803C9318:
	.incbin "baserom.dol", 0x3C5418, 0xC
.global lbl_803C9324
lbl_803C9324:
	.incbin "baserom.dol", 0x3C5424, 0xC
.global lbl_803C9330
lbl_803C9330:
	.incbin "baserom.dol", 0x3C5430, 0x10
.global lbl_803C9340
lbl_803C9340:
	.incbin "baserom.dol", 0x3C5440, 0x20
.global lbl_803C9360
lbl_803C9360:
	.incbin "baserom.dol", 0x3C5460, 0x18
.global lbl_803C9378
lbl_803C9378:
	.incbin "baserom.dol", 0x3C5478, 0x18
.global lbl_803C9390
lbl_803C9390:
	.incbin "baserom.dol", 0x3C5490, 0x10
.global lbl_803C93A0
lbl_803C93A0:
	.incbin "baserom.dol", 0x3C54A0, 0x38
.global lbl_803C93D8
lbl_803C93D8:
	.incbin "baserom.dol", 0x3C54D8, 0x10
.global lbl_803C93E8
lbl_803C93E8:
	.incbin "baserom.dol", 0x3C54E8, 0x10
.global lbl_803C93F8
lbl_803C93F8:
	.incbin "baserom.dol", 0x3C54F8, 0x68
.global lbl_803C9460
lbl_803C9460:
	.incbin "baserom.dol", 0x3C5560, 0x10
.global lbl_803C9470
lbl_803C9470:
	.incbin "baserom.dol", 0x3C5570, 0xDC
.global lbl_803C954C
lbl_803C954C:
	.incbin "baserom.dol", 0x3C564C, 0xDC
.global lbl_803C9628
lbl_803C9628:
	.incbin "baserom.dol", 0x3C5728, 0x38
.global lbl_803C9660
lbl_803C9660:
	.incbin "baserom.dol", 0x3C5760, 0x10
.global lbl_803C9670
lbl_803C9670:
	.incbin "baserom.dol", 0x3C5770, 0xC
.global lbl_803C967C
lbl_803C967C:
	.incbin "baserom.dol", 0x3C577C, 0x14
.global lbl_803C9690
lbl_803C9690:
	.incbin "baserom.dol", 0x3C5790, 0x10
.global lbl_803C96A0
lbl_803C96A0:
	.incbin "baserom.dol", 0x3C57A0, 0x14
.global lbl_803C96B4
lbl_803C96B4:
	.incbin "baserom.dol", 0x3C57B4, 0x10
.global lbl_803C96C4
lbl_803C96C4:
	.incbin "baserom.dol", 0x3C57C4, 0x14
.global lbl_803C96D8
lbl_803C96D8:
	.incbin "baserom.dol", 0x3C57D8, 0x10
.global lbl_803C96E8
lbl_803C96E8:
	.incbin "baserom.dol", 0x3C57E8, 0x30
.global lbl_803C9718
lbl_803C9718:
	.incbin "baserom.dol", 0x3C5818, 0x28
.global lbl_803C9740
lbl_803C9740:
	.incbin "baserom.dol", 0x3C5840, 0x24
.global lbl_803C9764
lbl_803C9764:
	.incbin "baserom.dol", 0x3C5864, 0xC
.global lbl_803C9770
lbl_803C9770:
	.incbin "baserom.dol", 0x3C5870, 0x24
.global lbl_803C9794
lbl_803C9794:
	.incbin "baserom.dol", 0x3C5894, 0x24
.global lbl_803C97B8
lbl_803C97B8:
	.incbin "baserom.dol", 0x3C58B8, 0x24
.global lbl_803C97DC
lbl_803C97DC:
	.incbin "baserom.dol", 0x3C58DC, 0x24
.global lbl_803C9800
lbl_803C9800:
	.incbin "baserom.dol", 0x3C5900, 0x10
.global lbl_803C9810
lbl_803C9810:
	.incbin "baserom.dol", 0x3C5910, 0x18
.global lbl_803C9828
lbl_803C9828:
	.incbin "baserom.dol", 0x3C5928, 0x28
.global lbl_803C9850
lbl_803C9850:
	.incbin "baserom.dol", 0x3C5950, 0x10
.global lbl_803C9860
lbl_803C9860:
	.incbin "baserom.dol", 0x3C5960, 0x18
.global lbl_803C9878
lbl_803C9878:
	.incbin "baserom.dol", 0x3C5978, 0x18
.global lbl_803C9890
lbl_803C9890:
	.incbin "baserom.dol", 0x3C5990, 0x10
.global lbl_803C98A0
lbl_803C98A0:
	.incbin "baserom.dol", 0x3C59A0, 0x30
.global lbl_803C98D0
lbl_803C98D0:
	.incbin "baserom.dol", 0x3C59D0, 0x50
.global lbl_803C9920
lbl_803C9920:
	.incbin "baserom.dol", 0x3C5A20, 0x38
.global lbl_803C9958
lbl_803C9958:
	.incbin "baserom.dol", 0x3C5A58, 0x20
.global lbl_803C9978
lbl_803C9978:
	.incbin "baserom.dol", 0x3C5A78, 0xC
.global lbl_803C9984
lbl_803C9984:
	.incbin "baserom.dol", 0x3C5A84, 0xC
.global lbl_803C9990
lbl_803C9990:
	.incbin "baserom.dol", 0x3C5A90, 0x10
.global lbl_803C99A0
lbl_803C99A0:
	.incbin "baserom.dol", 0x3C5AA0, 0x18
.global lbl_803C99B8
lbl_803C99B8:
	.incbin "baserom.dol", 0x3C5AB8, 0x18
.global lbl_803C99D0
lbl_803C99D0:
	.incbin "baserom.dol", 0x3C5AD0, 0x18
.global lbl_803C99E8
lbl_803C99E8:
	.incbin "baserom.dol", 0x3C5AE8, 0x50
.global lbl_803C9A38
lbl_803C9A38:
	.incbin "baserom.dol", 0x3C5B38, 0x20
.global lbl_803C9A58
lbl_803C9A58:
	.incbin "baserom.dol", 0x3C5B58, 0xC
.global lbl_803C9A64
lbl_803C9A64:
	.incbin "baserom.dol", 0x3C5B64, 0xC
.global lbl_803C9A70
lbl_803C9A70:
	.incbin "baserom.dol", 0x3C5B70, 0x10
.global lbl_803C9A80
lbl_803C9A80:
	.incbin "baserom.dol", 0x3C5B80, 0x2C
.global lbl_803C9AAC
lbl_803C9AAC:
	.incbin "baserom.dol", 0x3C5BAC, 0xC
.global lbl_803C9AB8
lbl_803C9AB8:
	.incbin "baserom.dol", 0x3C5BB8, 0x10
.global lbl_803C9AC8
lbl_803C9AC8:
	.incbin "baserom.dol", 0x3C5BC8, 0x1C
.global lbl_803C9AE4
lbl_803C9AE4:
	.incbin "baserom.dol", 0x3C5BE4, 0xC
.global lbl_803C9AF0
lbl_803C9AF0:
	.incbin "baserom.dol", 0x3C5BF0, 0xC
.global lbl_803C9AFC
lbl_803C9AFC:
	.incbin "baserom.dol", 0x3C5BFC, 0xC
.global lbl_803C9B08
lbl_803C9B08:
	.incbin "baserom.dol", 0x3C5C08, 0x18
.global lbl_803C9B20
lbl_803C9B20:
	.incbin "baserom.dol", 0x3C5C20, 0x18
.global lbl_803C9B38
lbl_803C9B38:
	.incbin "baserom.dol", 0x3C5C38, 0x18
.global lbl_803C9B50
lbl_803C9B50:
	.incbin "baserom.dol", 0x3C5C50, 0x50
.global lbl_803C9BA0
lbl_803C9BA0:
	.incbin "baserom.dol", 0x3C5CA0, 0x20
.global lbl_803C9BC0
lbl_803C9BC0:
	.incbin "baserom.dol", 0x3C5CC0, 0x10
.global lbl_803C9BD0
lbl_803C9BD0:
	.incbin "baserom.dol", 0x3C5CD0, 0xC
.global lbl_803C9BDC
lbl_803C9BDC:
	.incbin "baserom.dol", 0x3C5CDC, 0xC
.global lbl_803C9BE8
lbl_803C9BE8:
	.incbin "baserom.dol", 0x3C5CE8, 0x10
.global lbl_803C9BF8
lbl_803C9BF8:
	.incbin "baserom.dol", 0x3C5CF8, 0x10
.global lbl_803C9C08
lbl_803C9C08:
	.incbin "baserom.dol", 0x3C5D08, 0x50
.global lbl_803C9C58
lbl_803C9C58:
	.incbin "baserom.dol", 0x3C5D58, 0x38
.global lbl_803C9C90
lbl_803C9C90:
	.incbin "baserom.dol", 0x3C5D90, 0x28
.global lbl_803C9CB8
lbl_803C9CB8:
	.incbin "baserom.dol", 0x3C5DB8, 0x20
.global lbl_803C9CD8
lbl_803C9CD8:
	.incbin "baserom.dol", 0x3C5DD8, 0x10
.global lbl_803C9CE8
lbl_803C9CE8:
	.incbin "baserom.dol", 0x3C5DE8, 0x10
.global lbl_803C9CF8
lbl_803C9CF8:
	.incbin "baserom.dol", 0x3C5DF8, 0x24
.global lbl_803C9D1C
lbl_803C9D1C:
	.incbin "baserom.dol", 0x3C5E1C, 0xC
.global lbl_803C9D28
lbl_803C9D28:
	.incbin "baserom.dol", 0x3C5E28, 0x10
.global lbl_803C9D38
lbl_803C9D38:
	.incbin "baserom.dol", 0x3C5E38, 0x10
.global lbl_803C9D48
lbl_803C9D48:
	.incbin "baserom.dol", 0x3C5E48, 0x14
.global lbl_803C9D5C
lbl_803C9D5C:
	.incbin "baserom.dol", 0x3C5E5C, 0x60
.global lbl_803C9DBC
lbl_803C9DBC:
	.incbin "baserom.dol", 0x3C5EBC, 0x20
.global lbl_803C9DDC
lbl_803C9DDC:
	.incbin "baserom.dol", 0x3C5EDC, 0x2C
.global lbl_803C9E08
lbl_803C9E08:
	.incbin "baserom.dol", 0x3C5F08, 0x38
.global lbl_803C9E40
lbl_803C9E40:
	.incbin "baserom.dol", 0x3C5F40, 0x88
.global lbl_803C9EC8
lbl_803C9EC8:
	.incbin "baserom.dol", 0x3C5FC8, 0x28
.global lbl_803C9EF0
lbl_803C9EF0:
	.incbin "baserom.dol", 0x3C5FF0, 0x88
.global lbl_803C9F78
lbl_803C9F78:
	.incbin "baserom.dol", 0x3C6078, 0x28
.global lbl_803C9FA0
lbl_803C9FA0:
	.incbin "baserom.dol", 0x3C60A0, 0x28
.global lbl_803C9FC8
lbl_803C9FC8:
	.incbin "baserom.dol", 0x3C60C8, 0x38
.global lbl_803CA000
lbl_803CA000:
	.incbin "baserom.dol", 0x3C6100, 0x28
.global lbl_803CA028
lbl_803CA028:
	.incbin "baserom.dol", 0x3C6128, 0x28
.global lbl_803CA050
lbl_803CA050:
	.incbin "baserom.dol", 0x3C6150, 0x20
.global lbl_803CA070
lbl_803CA070:
	.incbin "baserom.dol", 0x3C6170, 0x20
.global lbl_803CA090
lbl_803CA090:
	.incbin "baserom.dol", 0x3C6190, 0x30
.global lbl_803CA0C0
lbl_803CA0C0:
	.incbin "baserom.dol", 0x3C61C0, 0x30
.global lbl_803CA0F0
lbl_803CA0F0:
	.incbin "baserom.dol", 0x3C61F0, 0x30
.global lbl_803CA120
lbl_803CA120:
	.incbin "baserom.dol", 0x3C6220, 0x28
.global lbl_803CA148
lbl_803CA148:
	.incbin "baserom.dol", 0x3C6248, 0xC
.global lbl_803CA154
lbl_803CA154:
	.incbin "baserom.dol", 0x3C6254, 0xC
.global lbl_803CA160
lbl_803CA160:
	.incbin "baserom.dol", 0x3C6260, 0x10
.global lbl_803CA170
lbl_803CA170:
	.incbin "baserom.dol", 0x3C6270, 0x10
.global lbl_803CA180
lbl_803CA180:
	.incbin "baserom.dol", 0x3C6280, 0x38
.global lbl_803CA1B8
lbl_803CA1B8:
	.incbin "baserom.dol", 0x3C62B8, 0x10
.global lbl_803CA1C8
lbl_803CA1C8:
	.incbin "baserom.dol", 0x3C62C8, 0x18
.global lbl_803CA1E0
lbl_803CA1E0:
	.incbin "baserom.dol", 0x3C62E0, 0x20
.global lbl_803CA200
lbl_803CA200:
	.incbin "baserom.dol", 0x3C6300, 0x1C
.global lbl_803CA21C
lbl_803CA21C:
	.incbin "baserom.dol", 0x3C631C, 0x14
.global lbl_803CA230
lbl_803CA230:
	.incbin "baserom.dol", 0x3C6330, 0x18
.global lbl_803CA248
lbl_803CA248:
	.incbin "baserom.dol", 0x3C6348, 0x18
.global lbl_803CA260
lbl_803CA260:
	.incbin "baserom.dol", 0x3C6360, 0x14
.global lbl_803CA274
lbl_803CA274:
	.incbin "baserom.dol", 0x3C6374, 0x34
.global lbl_803CA2A8
lbl_803CA2A8:
	.incbin "baserom.dol", 0x3C63A8, 0x18
.global lbl_803CA2C0
lbl_803CA2C0:
	.incbin "baserom.dol", 0x3C63C0, 0x10
.global lbl_803CA2D0
lbl_803CA2D0:
	.incbin "baserom.dol", 0x3C63D0, 0x14
.global lbl_803CA2E4
lbl_803CA2E4:
	.incbin "baserom.dol", 0x3C63E4, 0x94
.global lbl_803CA378
lbl_803CA378:
	.incbin "baserom.dol", 0x3C6478, 0x20
.global lbl_803CA398
lbl_803CA398:
	.incbin "baserom.dol", 0x3C6498, 0x18
.global lbl_803CA3B0
lbl_803CA3B0:
	.incbin "baserom.dol", 0x3C64B0, 0x14
.global lbl_803CA3C4
lbl_803CA3C4:
	.incbin "baserom.dol", 0x3C64C4, 0x24
.global lbl_803CA3E8
lbl_803CA3E8:
	.incbin "baserom.dol", 0x3C64E8, 0x48
.global lbl_803CA430
lbl_803CA430:
	.incbin "baserom.dol", 0x3C6530, 0x28
.global lbl_803CA458
lbl_803CA458:
	.incbin "baserom.dol", 0x3C6558, 0xE0
.global lbl_803CA538
lbl_803CA538:
	.incbin "baserom.dol", 0x3C6638, 0x38
.global lbl_803CA570
lbl_803CA570:
	.incbin "baserom.dol", 0x3C6670, 0x18
.global lbl_803CA588
lbl_803CA588:
	.incbin "baserom.dol", 0x3C6688, 0x68
.global lbl_803CA5F0
lbl_803CA5F0:
	.incbin "baserom.dol", 0x3C66F0, 0x50
.global lbl_803CA640
lbl_803CA640:
	.incbin "baserom.dol", 0x3C6740, 0x10
.global lbl_803CA650
lbl_803CA650:
	.incbin "baserom.dol", 0x3C6750, 0x38
.global lbl_803CA688
lbl_803CA688:
	.incbin "baserom.dol", 0x3C6788, 0x28
.global lbl_803CA6B0
lbl_803CA6B0:
	.incbin "baserom.dol", 0x3C67B0, 0x18
.global lbl_803CA6C8
lbl_803CA6C8:
	.incbin "baserom.dol", 0x3C67C8, 0x20
.global lbl_803CA6E8
lbl_803CA6E8:
	.incbin "baserom.dol", 0x3C67E8, 0x18
.global lbl_803CA700
lbl_803CA700:
	.incbin "baserom.dol", 0x3C6800, 0x38
.global lbl_803CA738
lbl_803CA738:
	.incbin "baserom.dol", 0x3C6838, 0x20
.global lbl_803CA758
lbl_803CA758:
	.incbin "baserom.dol", 0x3C6858, 0x18
.global lbl_803CA770
lbl_803CA770:
	.incbin "baserom.dol", 0x3C6870, 0x50
.global lbl_803CA7C0
lbl_803CA7C0:
	.incbin "baserom.dol", 0x3C68C0, 0x48
.global lbl_803CA808
lbl_803CA808:
	.incbin "baserom.dol", 0x3C6908, 0x50
.global lbl_803CA858
lbl_803CA858:
	.incbin "baserom.dol", 0x3C6958, 0x28
.global lbl_803CA880
lbl_803CA880:
	.incbin "baserom.dol", 0x3C6980, 0x18
.global lbl_803CA898
lbl_803CA898:
	.incbin "baserom.dol", 0x3C6998, 0x18
.global lbl_803CA8B0
lbl_803CA8B0:
	.incbin "baserom.dol", 0x3C69B0, 0x38
.global lbl_803CA8E8
lbl_803CA8E8:
	.incbin "baserom.dol", 0x3C69E8, 0x28
.global lbl_803CA910
lbl_803CA910:
	.incbin "baserom.dol", 0x3C6A10, 0x30
.global lbl_803CA940
lbl_803CA940:
	.incbin "baserom.dol", 0x3C6A40, 0x28
.global lbl_803CA968
lbl_803CA968:
	.incbin "baserom.dol", 0x3C6A68, 0x38
.global lbl_803CA9A0
lbl_803CA9A0:
	.incbin "baserom.dol", 0x3C6AA0, 0x38
.global lbl_803CA9D8
lbl_803CA9D8:
	.incbin "baserom.dol", 0x3C6AD8, 0x48
.global lbl_803CAA20
lbl_803CAA20:
	.incbin "baserom.dol", 0x3C6B20, 0x10
.global lbl_803CAA30
lbl_803CAA30:
	.incbin "baserom.dol", 0x3C6B30, 0x100
.global lbl_803CAB30
lbl_803CAB30:
	.incbin "baserom.dol", 0x3C6C30, 0x10
.global lbl_803CAB40
lbl_803CAB40:
	.incbin "baserom.dol", 0x3C6C40, 0x48
.global lbl_803CAB88
lbl_803CAB88:
	.incbin "baserom.dol", 0x3C6C88, 0x20
.global lbl_803CABA8
lbl_803CABA8:
	.incbin "baserom.dol", 0x3C6CA8, 0x48
.global lbl_803CABF0
lbl_803CABF0:
	.incbin "baserom.dol", 0x3C6CF0, 0x20
.global lbl_803CAC10
lbl_803CAC10:
	.incbin "baserom.dol", 0x3C6D10, 0x48
.global lbl_803CAC58
lbl_803CAC58:
	.incbin "baserom.dol", 0x3C6D58, 0x30
.global lbl_803CAC88
lbl_803CAC88:
	.incbin "baserom.dol", 0x3C6D88, 0x30
.global lbl_803CACB8
lbl_803CACB8:
	.incbin "baserom.dol", 0x3C6DB8, 0x30
.global lbl_803CACE8
lbl_803CACE8:
	.incbin "baserom.dol", 0x3C6DE8, 0x30
.global lbl_803CAD18
lbl_803CAD18:
	.incbin "baserom.dol", 0x3C6E18, 0x30
.global lbl_803CAD48
lbl_803CAD48:
	.incbin "baserom.dol", 0x3C6E48, 0x30
.global lbl_803CAD78
lbl_803CAD78:
	.incbin "baserom.dol", 0x3C6E78, 0x30
.global lbl_803CADA8
lbl_803CADA8:
	.incbin "baserom.dol", 0x3C6EA8, 0x20
.global lbl_803CADC8
lbl_803CADC8:
	.incbin "baserom.dol", 0x3C6EC8, 0x48
.global lbl_803CAE10
lbl_803CAE10:
	.incbin "baserom.dol", 0x3C6F10, 0x30
.global lbl_803CAE40
lbl_803CAE40:
	.incbin "baserom.dol", 0x3C6F40, 0x20
.global lbl_803CAE60
lbl_803CAE60:
	.incbin "baserom.dol", 0x3C6F60, 0x48
.global lbl_803CAEA8
lbl_803CAEA8:
	.incbin "baserom.dol", 0x3C6FA8, 0x28
.global lbl_803CAED0
lbl_803CAED0:
	.incbin "baserom.dol", 0x3C6FD0, 0x30