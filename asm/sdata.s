.include "macros.inc"

.section .sdata, "wa"  # 0x804BD380 - 0x804BE9E0

.balign 0x8

.global lbl_804BD960
lbl_804BD960:
	.incbin "baserom.dol", 0x3C75E0, 0x8
.global lbl_804BD968
lbl_804BD968:
	.incbin "baserom.dol", 0x3C75E8, 0x8
.global lbl_804BD970
lbl_804BD970:
	.incbin "baserom.dol", 0x3C75F0, 0x8
.global lbl_804BD978
lbl_804BD978:
	.incbin "baserom.dol", 0x3C75F8, 0x4
.global lbl_804BD97C
lbl_804BD97C:
	.incbin "baserom.dol", 0x3C75FC, 0x4
.global lbl_804BD980
lbl_804BD980:
	.incbin "baserom.dol", 0x3C7600, 0x4
.global lbl_804BD984
lbl_804BD984:
	.incbin "baserom.dol", 0x3C7604, 0x8
.global lbl_804BD98C
lbl_804BD98C:
	.incbin "baserom.dol", 0x3C760C, 0x4
.global lbl_804BD990
lbl_804BD990:
	.incbin "baserom.dol", 0x3C7610, 0x8
.global lbl_804BD998
lbl_804BD998:
	.incbin "baserom.dol", 0x3C7618, 0x8
.global lbl_804BD9A0
lbl_804BD9A0:
	.incbin "baserom.dol", 0x3C7620, 0x8
.global lbl_804BD9A8
lbl_804BD9A8:
	.incbin "baserom.dol", 0x3C7628, 0x8
.global lbl_804BD9B0
lbl_804BD9B0:
	.incbin "baserom.dol", 0x3C7630, 0x8
.global lbl_804BD9B8
lbl_804BD9B8:
	.incbin "baserom.dol", 0x3C7638, 0x8
.global lbl_804BD9C0
lbl_804BD9C0:
	.incbin "baserom.dol", 0x3C7640, 0x4
.global lbl_804BD9C4
lbl_804BD9C4:
	.incbin "baserom.dol", 0x3C7644, 0x4
.global lbl_804BD9C8
lbl_804BD9C8:
	.incbin "baserom.dol", 0x3C7648, 0x8
.global lbl_804BD9D0
lbl_804BD9D0:
	.incbin "baserom.dol", 0x3C7650, 0x4
.global lbl_804BD9D4
lbl_804BD9D4:
	.incbin "baserom.dol", 0x3C7654, 0x4
.global lbl_804BD9D8
lbl_804BD9D8:
	.incbin "baserom.dol", 0x3C7658, 0x8
.global lbl_804BD9E0
lbl_804BD9E0:
	.incbin "baserom.dol", 0x3C7660, 0x8
.global lbl_804BD9E8
lbl_804BD9E8:
	.incbin "baserom.dol", 0x3C7668, 0x8
.global lbl_804BD9F0
lbl_804BD9F0:
	.incbin "baserom.dol", 0x3C7670, 0x8
.global lbl_804BD9F8
lbl_804BD9F8:
	.incbin "baserom.dol", 0x3C7678, 0x48
.global lbl_804BDA40
lbl_804BDA40:
	.incbin "baserom.dol", 0x3C76C0, 0x8
.global lbl_804BDA48
lbl_804BDA48:
	.incbin "baserom.dol", 0x3C76C8, 0x8
.global lbl_804BDA50
lbl_804BDA50:
	.incbin "baserom.dol", 0x3C76D0, 0x4
.global lbl_804BDA54
lbl_804BDA54:
	.incbin "baserom.dol", 0x3C76D4, 0x4
.global lbl_804BDA58
lbl_804BDA58:
	.incbin "baserom.dol", 0x3C76D8, 0x4
.global lbl_804BDA5C
lbl_804BDA5C:
	.incbin "baserom.dol", 0x3C76DC, 0x8
.global lbl_804BDA64
lbl_804BDA64:
	.incbin "baserom.dol", 0x3C76E4, 0x4
.global lbl_804BDA68
lbl_804BDA68:
	.incbin "baserom.dol", 0x3C76E8, 0x8
.global lbl_804BDA70
lbl_804BDA70:
	.incbin "baserom.dol", 0x3C76F0, 0x8
.global lbl_804BDA78
lbl_804BDA78:
	.incbin "baserom.dol", 0x3C76F8, 0x4
.global lbl_804BDA7C
lbl_804BDA7C:
	.incbin "baserom.dol", 0x3C76FC, 0x8
.global lbl_804BDA84
lbl_804BDA84:
	.incbin "baserom.dol", 0x3C7704, 0x38
.global lbl_804BDABC
lbl_804BDABC:
	.incbin "baserom.dol", 0x3C773C, 0x4
.global lbl_804BDAC0
lbl_804BDAC0:
	.incbin "baserom.dol", 0x3C7740, 0x4
.global lbl_804BDAC4
lbl_804BDAC4:
	.incbin "baserom.dol", 0x3C7744, 0x4
.global lbl_804BDAC8
lbl_804BDAC8:
	.incbin "baserom.dol", 0x3C7748, 0x4
.global lbl_804BDACC
lbl_804BDACC:
	.incbin "baserom.dol", 0x3C774C, 0x4
.global lbl_804BDAD0
lbl_804BDAD0:
	.incbin "baserom.dol", 0x3C7750, 0x8
.global lbl_804BDAD8
lbl_804BDAD8:
	.incbin "baserom.dol", 0x3C7758, 0x8
.global lbl_804BDAE0
lbl_804BDAE0:
	.incbin "baserom.dol", 0x3C7760, 0x8
.global lbl_804BDAE8
lbl_804BDAE8:
	.incbin "baserom.dol", 0x3C7768, 0x8
.global lbl_804BDAF0
lbl_804BDAF0:
	.incbin "baserom.dol", 0x3C7770, 0x8
.global lbl_804BDAF8
lbl_804BDAF8:
	.incbin "baserom.dol", 0x3C7778, 0x4
.global lbl_804BDAFC
lbl_804BDAFC:
	.incbin "baserom.dol", 0x3C777C, 0x4
.global lbl_804BDB00
lbl_804BDB00:
	.incbin "baserom.dol", 0x3C7780, 0x4
.global lbl_804BDB04
lbl_804BDB04:
	.incbin "baserom.dol", 0x3C7784, 0x4
.global lbl_804BDB08
lbl_804BDB08:
	.incbin "baserom.dol", 0x3C7788, 0x4
.global lbl_804BDB0C
lbl_804BDB0C:
	.incbin "baserom.dol", 0x3C778C, 0x4
.global lbl_804BDB10
lbl_804BDB10:
	.incbin "baserom.dol", 0x3C7790, 0x4
.global lbl_804BDB14
lbl_804BDB14:
	.incbin "baserom.dol", 0x3C7794, 0x4
.global lbl_804BDB18
lbl_804BDB18:
	.incbin "baserom.dol", 0x3C7798, 0x8
.global lbl_804BDB20
lbl_804BDB20:
	.incbin "baserom.dol", 0x3C77A0, 0x4
.global lbl_804BDB24
lbl_804BDB24:
	.incbin "baserom.dol", 0x3C77A4, 0x4
.global lbl_804BDB28
lbl_804BDB28:
	.incbin "baserom.dol", 0x3C77A8, 0x4
.global lbl_804BDB2C
lbl_804BDB2C:
	.incbin "baserom.dol", 0x3C77AC, 0x4
.global lbl_804BDB30
lbl_804BDB30:
	.incbin "baserom.dol", 0x3C77B0, 0x4
.global lbl_804BDB34
lbl_804BDB34:
	.incbin "baserom.dol", 0x3C77B4, 0x4
.global lbl_804BDB38
lbl_804BDB38:
	.incbin "baserom.dol", 0x3C77B8, 0x4
.global lbl_804BDB3C
lbl_804BDB3C:
	.incbin "baserom.dol", 0x3C77BC, 0x4
.global lbl_804BDB40
lbl_804BDB40:
	.incbin "baserom.dol", 0x3C77C0, 0x4
.global lbl_804BDB44
lbl_804BDB44:
	.incbin "baserom.dol", 0x3C77C4, 0x1
.global lbl_804BDB45
lbl_804BDB45:
	.incbin "baserom.dol", 0x3C77C5, 0x3
.global lbl_804BDB48
lbl_804BDB48:
	.incbin "baserom.dol", 0x3C77C8, 0x8
.global lbl_804BDB50
lbl_804BDB50:
	.incbin "baserom.dol", 0x3C77D0, 0x8
.global lbl_804BDB58
lbl_804BDB58:
	.incbin "baserom.dol", 0x3C77D8, 0x4
.global lbl_804BDB5C
lbl_804BDB5C:
	.incbin "baserom.dol", 0x3C77DC, 0x4
.global lbl_804BDB60
lbl_804BDB60:
	.incbin "baserom.dol", 0x3C77E0, 0x8
.global lbl_804BDB68
lbl_804BDB68:
	.incbin "baserom.dol", 0x3C77E8, 0x8
.global lbl_804BDB70
lbl_804BDB70:
	.incbin "baserom.dol", 0x3C77F0, 0x4
.global lbl_804BDB74
lbl_804BDB74:
	.incbin "baserom.dol", 0x3C77F4, 0x4
.global lbl_804BDB78
lbl_804BDB78:
	.incbin "baserom.dol", 0x3C77F8, 0x8
.global lbl_804BDB80
lbl_804BDB80:
	.incbin "baserom.dol", 0x3C7800, 0x8
.global lbl_804BDB88
lbl_804BDB88:
	.incbin "baserom.dol", 0x3C7808, 0x8
.global lbl_804BDB90
lbl_804BDB90:
	.incbin "baserom.dol", 0x3C7810, 0x8
.global lbl_804BDB98
lbl_804BDB98:
	.incbin "baserom.dol", 0x3C7818, 0x8
.global lbl_804BDBA0
lbl_804BDBA0:
	.incbin "baserom.dol", 0x3C7820, 0x8
.global lbl_804BDBA8
lbl_804BDBA8:
	.incbin "baserom.dol", 0x3C7828, 0x4
.global lbl_804BDBAC
lbl_804BDBAC:
	.incbin "baserom.dol", 0x3C782C, 0x4
.global lbl_804BDBB0
lbl_804BDBB0:
	.incbin "baserom.dol", 0x3C7830, 0x8
.global lbl_804BDBB8
lbl_804BDBB8:
	.incbin "baserom.dol", 0x3C7838, 0x8
.global lbl_804BDBC0
lbl_804BDBC0:
	.incbin "baserom.dol", 0x3C7840, 0x8
.global lbl_804BDBC8
lbl_804BDBC8:
	.incbin "baserom.dol", 0x3C7848, 0x8
.global lbl_804BDBD0
lbl_804BDBD0:
	.incbin "baserom.dol", 0x3C7850, 0x8
.global lbl_804BDBD8
lbl_804BDBD8:
	.incbin "baserom.dol", 0x3C7858, 0x8
.global lbl_804BDBE0
lbl_804BDBE0:
	.incbin "baserom.dol", 0x3C7860, 0x8
.global lbl_804BDBE8
lbl_804BDBE8:
	.incbin "baserom.dol", 0x3C7868, 0x8
.global lbl_804BDBF0
lbl_804BDBF0:
	.incbin "baserom.dol", 0x3C7870, 0x8
.global lbl_804BDBF8
lbl_804BDBF8:
	.incbin "baserom.dol", 0x3C7878, 0x8
.global lbl_804BDC00
lbl_804BDC00:
	.incbin "baserom.dol", 0x3C7880, 0x8
.global lbl_804BDC08
lbl_804BDC08:
	.incbin "baserom.dol", 0x3C7888, 0x4
.global lbl_804BDC0C
lbl_804BDC0C:
	.incbin "baserom.dol", 0x3C788C, 0x4
.global lbl_804BDC10
lbl_804BDC10:
	.incbin "baserom.dol", 0x3C7890, 0x8
.global lbl_804BDC18
lbl_804BDC18:
	.incbin "baserom.dol", 0x3C7898, 0x8
.global lbl_804BDC20
lbl_804BDC20:
	.incbin "baserom.dol", 0x3C78A0, 0x8
.global lbl_804BDC28
lbl_804BDC28:
	.incbin "baserom.dol", 0x3C78A8, 0x4
.global lbl_804BDC2C
lbl_804BDC2C:
	.incbin "baserom.dol", 0x3C78AC, 0x4
.global lbl_804BDC30
lbl_804BDC30:
	.incbin "baserom.dol", 0x3C78B0, 0x4
.global lbl_804BDC34
lbl_804BDC34:
	.incbin "baserom.dol", 0x3C78B4, 0x4
.global lbl_804BDC38
lbl_804BDC38:
	.incbin "baserom.dol", 0x3C78B8, 0x8
.global lbl_804BDC40
lbl_804BDC40:
	.incbin "baserom.dol", 0x3C78C0, 0x8
.global lbl_804BDC48
lbl_804BDC48:
	.incbin "baserom.dol", 0x3C78C8, 0x4
.global lbl_804BDC4C
lbl_804BDC4C:
	.incbin "baserom.dol", 0x3C78CC, 0x4
.global lbl_804BDC50
lbl_804BDC50:
	.incbin "baserom.dol", 0x3C78D0, 0x4
.global lbl_804BDC54
lbl_804BDC54:
	.incbin "baserom.dol", 0x3C78D4, 0x4
.global lbl_804BDC58
lbl_804BDC58:
	.incbin "baserom.dol", 0x3C78D8, 0x8
.global lbl_804BDC60
lbl_804BDC60:
	.incbin "baserom.dol", 0x3C78E0, 0x8
.global lbl_804BDC68
lbl_804BDC68:
	.incbin "baserom.dol", 0x3C78E8, 0x8
.global lbl_804BDC70
lbl_804BDC70:
	.incbin "baserom.dol", 0x3C78F0, 0x4
.global lbl_804BDC74
lbl_804BDC74:
	.incbin "baserom.dol", 0x3C78F4, 0x4
.global lbl_804BDC78
lbl_804BDC78:
	.incbin "baserom.dol", 0x3C78F8, 0x4
.global lbl_804BDC7C
lbl_804BDC7C:
	.incbin "baserom.dol", 0x3C78FC, 0x4
.global lbl_804BDC80
lbl_804BDC80:
	.incbin "baserom.dol", 0x3C7900, 0x4
.global lbl_804BDC84
lbl_804BDC84:
	.incbin "baserom.dol", 0x3C7904, 0x4
.global lbl_804BDC88
lbl_804BDC88:
	.incbin "baserom.dol", 0x3C7908, 0x4
.global lbl_804BDC8C
lbl_804BDC8C:
	.incbin "baserom.dol", 0x3C790C, 0x4
.global lbl_804BDC90
lbl_804BDC90:
	.incbin "baserom.dol", 0x3C7910, 0x8
.global lbl_804BDC98
lbl_804BDC98:
	.incbin "baserom.dol", 0x3C7918, 0x4
.global lbl_804BDC9C
lbl_804BDC9C:
	.incbin "baserom.dol", 0x3C791C, 0x4
.global lbl_804BDCA0
lbl_804BDCA0:
	.incbin "baserom.dol", 0x3C7920, 0x8
.global lbl_804BDCA8
lbl_804BDCA8:
	.incbin "baserom.dol", 0x3C7928, 0x8
.global lbl_804BDCB0
lbl_804BDCB0:
	.incbin "baserom.dol", 0x3C7930, 0x4
.global lbl_804BDCB4
lbl_804BDCB4:
	.incbin "baserom.dol", 0x3C7934, 0x4
.global lbl_804BDCB8
lbl_804BDCB8:
	.incbin "baserom.dol", 0x3C7938, 0x4
.global lbl_804BDCBC
lbl_804BDCBC:
	.incbin "baserom.dol", 0x3C793C, 0x4
.global lbl_804BDCC0
lbl_804BDCC0:
	.incbin "baserom.dol", 0x3C7940, 0x8
.global lbl_804BDCC8
lbl_804BDCC8:
	.incbin "baserom.dol", 0x3C7948, 0x8
.global lbl_804BDCD0
lbl_804BDCD0:
	.incbin "baserom.dol", 0x3C7950, 0x8
.global lbl_804BDCD8
lbl_804BDCD8:
	.incbin "baserom.dol", 0x3C7958, 0x8
.global lbl_804BDCE0
lbl_804BDCE0:
	.incbin "baserom.dol", 0x3C7960, 0x8
.global lbl_804BDCE8
lbl_804BDCE8:
	.incbin "baserom.dol", 0x3C7968, 0x8
.global lbl_804BDCF0
lbl_804BDCF0:
	.incbin "baserom.dol", 0x3C7970, 0x8
.global lbl_804BDCF8
lbl_804BDCF8:
	.incbin "baserom.dol", 0x3C7978, 0x8
.global lbl_804BDD00
lbl_804BDD00:
	.incbin "baserom.dol", 0x3C7980, 0x8
.global lbl_804BDD08
lbl_804BDD08:
	.incbin "baserom.dol", 0x3C7988, 0x4
.global lbl_804BDD0C
lbl_804BDD0C:
	.incbin "baserom.dol", 0x3C798C, 0x4
.global lbl_804BDD10
lbl_804BDD10:
	.incbin "baserom.dol", 0x3C7990, 0x8
.global lbl_804BDD18
lbl_804BDD18:
	.incbin "baserom.dol", 0x3C7998, 0x4
.global lbl_804BDD1C
lbl_804BDD1C:
	.incbin "baserom.dol", 0x3C799C, 0x4
.global lbl_804BDD20
lbl_804BDD20:
	.incbin "baserom.dol", 0x3C79A0, 0x4
.global lbl_804BDD24
lbl_804BDD24:
	.incbin "baserom.dol", 0x3C79A4, 0x4
.global lbl_804BDD28
lbl_804BDD28:
	.incbin "baserom.dol", 0x3C79A8, 0x4
.global lbl_804BDD2C
lbl_804BDD2C:
	.incbin "baserom.dol", 0x3C79AC, 0x4
.global lbl_804BDD30
lbl_804BDD30:
	.incbin "baserom.dol", 0x3C79B0, 0x4
.global lbl_804BDD34
lbl_804BDD34:
	.incbin "baserom.dol", 0x3C79B4, 0x4
.global lbl_804BDD38
lbl_804BDD38:
	.incbin "baserom.dol", 0x3C79B8, 0x8
.global lbl_804BDD40
lbl_804BDD40:
	.incbin "baserom.dol", 0x3C79C0, 0x8
.global lbl_804BDD48
lbl_804BDD48:
	.incbin "baserom.dol", 0x3C79C8, 0x4
.global lbl_804BDD4C
lbl_804BDD4C:
	.incbin "baserom.dol", 0x3C79CC, 0x4
.global lbl_804BDD50
lbl_804BDD50:
	.incbin "baserom.dol", 0x3C79D0, 0x8
.global lbl_804BDD58
lbl_804BDD58:
	.incbin "baserom.dol", 0x3C79D8, 0x4
.global lbl_804BDD5C
lbl_804BDD5C:
	.incbin "baserom.dol", 0x3C79DC, 0x4
.global lbl_804BDD60
lbl_804BDD60:
	.incbin "baserom.dol", 0x3C79E0, 0x40
.global lbl_804BDDA0
lbl_804BDDA0:
	.incbin "baserom.dol", 0x3C7A20, 0x8
.global lbl_804BDDA8
lbl_804BDDA8:
	.incbin "baserom.dol", 0x3C7A28, 0x8
.global lbl_804BDDB0
lbl_804BDDB0:
	.incbin "baserom.dol", 0x3C7A30, 0x8
.global lbl_804BDDB8
lbl_804BDDB8:
	.incbin "baserom.dol", 0x3C7A38, 0x8
.global lbl_804BDDC0
lbl_804BDDC0:
	.incbin "baserom.dol", 0x3C7A40, 0x8
.global lbl_804BDDC8
lbl_804BDDC8:
	.incbin "baserom.dol", 0x3C7A48, 0x8
.global lbl_804BDDD0
lbl_804BDDD0:
	.incbin "baserom.dol", 0x3C7A50, 0x8
.global lbl_804BDDD8
lbl_804BDDD8:
	.incbin "baserom.dol", 0x3C7A58, 0x4
.global lbl_804BDDDC
lbl_804BDDDC:
	.incbin "baserom.dol", 0x3C7A5C, 0x4
.global lbl_804BDDE0
lbl_804BDDE0:
	.incbin "baserom.dol", 0x3C7A60, 0x8
.global lbl_804BDDE8
lbl_804BDDE8:
	.incbin "baserom.dol", 0x3C7A68, 0x8
.global lbl_804BDDF0
lbl_804BDDF0:
	.incbin "baserom.dol", 0x3C7A70, 0x8
.global lbl_804BDDF8
lbl_804BDDF8:
	.incbin "baserom.dol", 0x3C7A78, 0x8
.global lbl_804BDE00
lbl_804BDE00:
	.incbin "baserom.dol", 0x3C7A80, 0x10
.global lbl_804BDE10
lbl_804BDE10:
	.incbin "baserom.dol", 0x3C7A90, 0x4
.global lbl_804BDE14
lbl_804BDE14:
	.incbin "baserom.dol", 0x3C7A94, 0x4
.global lbl_804BDE18
lbl_804BDE18:
	.incbin "baserom.dol", 0x3C7A98, 0x4
.global lbl_804BDE1C
lbl_804BDE1C:
	.incbin "baserom.dol", 0x3C7A9C, 0x4
.global lbl_804BDE20
lbl_804BDE20:
	.incbin "baserom.dol", 0x3C7AA0, 0x4
.global lbl_804BDE24
lbl_804BDE24:
	.incbin "baserom.dol", 0x3C7AA4, 0x4
.global lbl_804BDE28
lbl_804BDE28:
	.incbin "baserom.dol", 0x3C7AA8, 0x4
.global lbl_804BDE2C
lbl_804BDE2C:
	.incbin "baserom.dol", 0x3C7AAC, 0x4
.global lbl_804BDE30
lbl_804BDE30:
	.incbin "baserom.dol", 0x3C7AB0, 0x4
.global lbl_804BDE34
lbl_804BDE34:
	.incbin "baserom.dol", 0x3C7AB4, 0x4
.global lbl_804BDE38
lbl_804BDE38:
	.incbin "baserom.dol", 0x3C7AB8, 0x4
.global lbl_804BDE3C
lbl_804BDE3C:
	.incbin "baserom.dol", 0x3C7ABC, 0x4
.global lbl_804BDE40
lbl_804BDE40:
	.incbin "baserom.dol", 0x3C7AC0, 0x4
.global lbl_804BDE44
lbl_804BDE44:
	.incbin "baserom.dol", 0x3C7AC4, 0x4
.global lbl_804BDE48
lbl_804BDE48:
	.incbin "baserom.dol", 0x3C7AC8, 0x4
.global lbl_804BDE4C
lbl_804BDE4C:
	.incbin "baserom.dol", 0x3C7ACC, 0x4
.global lbl_804BDE50
lbl_804BDE50:
	.incbin "baserom.dol", 0x3C7AD0, 0x4
.global lbl_804BDE54
lbl_804BDE54:
	.incbin "baserom.dol", 0x3C7AD4, 0x4
.global lbl_804BDE58
lbl_804BDE58:
	.incbin "baserom.dol", 0x3C7AD8, 0x4
.global lbl_804BDE5C
lbl_804BDE5C:
	.incbin "baserom.dol", 0x3C7ADC, 0x4
.global lbl_804BDE60
lbl_804BDE60:
	.incbin "baserom.dol", 0x3C7AE0, 0x8
.global lbl_804BDE68
lbl_804BDE68:
	.incbin "baserom.dol", 0x3C7AE8, 0x4
.global lbl_804BDE6C
lbl_804BDE6C:
	.incbin "baserom.dol", 0x3C7AEC, 0x4
.global lbl_804BDE70
lbl_804BDE70:
	.incbin "baserom.dol", 0x3C7AF0, 0x1
.global lbl_804BDE71
lbl_804BDE71:
	.incbin "baserom.dol", 0x3C7AF1, 0x1
.global lbl_804BDE72
lbl_804BDE72:
	.incbin "baserom.dol", 0x3C7AF2, 0x1
.global lbl_804BDE73
lbl_804BDE73:
	.incbin "baserom.dol", 0x3C7AF3, 0x1
.global lbl_804BDE74
lbl_804BDE74:
	.incbin "baserom.dol", 0x3C7AF4, 0x4
.global lbl_804BDE78
lbl_804BDE78:
	.incbin "baserom.dol", 0x3C7AF8, 0x4
.global lbl_804BDE7C
lbl_804BDE7C:
	.incbin "baserom.dol", 0x3C7AFC, 0x4
.global lbl_804BDE80
lbl_804BDE80:
	.incbin "baserom.dol", 0x3C7B00, 0x4
.global lbl_804BDE84
lbl_804BDE84:
	.incbin "baserom.dol", 0x3C7B04, 0x4
.global lbl_804BDE88
lbl_804BDE88:
	.incbin "baserom.dol", 0x3C7B08, 0x4
.global lbl_804BDE8C
lbl_804BDE8C:
	.incbin "baserom.dol", 0x3C7B0C, 0x4
.global lbl_804BDE90
lbl_804BDE90:
	.incbin "baserom.dol", 0x3C7B10, 0x4
.global lbl_804BDE94
lbl_804BDE94:
	.incbin "baserom.dol", 0x3C7B14, 0x4
.global lbl_804BDE98
lbl_804BDE98:
	.incbin "baserom.dol", 0x3C7B18, 0x4
.global lbl_804BDE9C
lbl_804BDE9C:
	.incbin "baserom.dol", 0x3C7B1C, 0x4
.global lbl_804BDEA0
lbl_804BDEA0:
	.incbin "baserom.dol", 0x3C7B20, 0x4
.global lbl_804BDEA4
lbl_804BDEA4:
	.incbin "baserom.dol", 0x3C7B24, 0x4
.global lbl_804BDEA8
lbl_804BDEA8:
	.incbin "baserom.dol", 0x3C7B28, 0x4
.global lbl_804BDEAC
lbl_804BDEAC:
	.incbin "baserom.dol", 0x3C7B2C, 0x4
.global lbl_804BDEB0
lbl_804BDEB0:
	.incbin "baserom.dol", 0x3C7B30, 0x4
.global lbl_804BDEB4
lbl_804BDEB4:
	.incbin "baserom.dol", 0x3C7B34, 0x4
.global lbl_804BDEB8
lbl_804BDEB8:
	.incbin "baserom.dol", 0x3C7B38, 0x4
.global lbl_804BDEBC
lbl_804BDEBC:
	.incbin "baserom.dol", 0x3C7B3C, 0x4
.global lbl_804BDEC0
lbl_804BDEC0:
	.incbin "baserom.dol", 0x3C7B40, 0x4
.global lbl_804BDEC4
lbl_804BDEC4:
	.incbin "baserom.dol", 0x3C7B44, 0x4
.global lbl_804BDEC8
lbl_804BDEC8:
	.incbin "baserom.dol", 0x3C7B48, 0x4
.global lbl_804BDECC
lbl_804BDECC:
	.incbin "baserom.dol", 0x3C7B4C, 0x4
.global lbl_804BDED0
lbl_804BDED0:
	.incbin "baserom.dol", 0x3C7B50, 0x4
.global lbl_804BDED4
lbl_804BDED4:
	.incbin "baserom.dol", 0x3C7B54, 0x4
.global lbl_804BDED8
lbl_804BDED8:
	.incbin "baserom.dol", 0x3C7B58, 0x4
.global lbl_804BDEDC
lbl_804BDEDC:
	.incbin "baserom.dol", 0x3C7B5C, 0x4
.global lbl_804BDEE0
lbl_804BDEE0:
	.incbin "baserom.dol", 0x3C7B60, 0x4
.global lbl_804BDEE4
lbl_804BDEE4:
	.incbin "baserom.dol", 0x3C7B64, 0x4
.global lbl_804BDEE8
lbl_804BDEE8:
	.incbin "baserom.dol", 0x3C7B68, 0x8
.global lbl_804BDEF0
lbl_804BDEF0:
	.incbin "baserom.dol", 0x3C7B70, 0x4
.global lbl_804BDEF4
lbl_804BDEF4:
	.incbin "baserom.dol", 0x3C7B74, 0x4
.global lbl_804BDEF8
lbl_804BDEF8:
	.incbin "baserom.dol", 0x3C7B78, 0x4
.global lbl_804BDEFC
lbl_804BDEFC:
	.incbin "baserom.dol", 0x3C7B7C, 0x4
.global lbl_804BDF00
lbl_804BDF00:
	.incbin "baserom.dol", 0x3C7B80, 0x4
.global lbl_804BDF04
lbl_804BDF04:
	.incbin "baserom.dol", 0x3C7B84, 0x4
.global lbl_804BDF08
lbl_804BDF08:
	.incbin "baserom.dol", 0x3C7B88, 0x8
.global lbl_804BDF10
lbl_804BDF10:
	.incbin "baserom.dol", 0x3C7B90, 0x4
.global lbl_804BDF14
lbl_804BDF14:
	.incbin "baserom.dol", 0x3C7B94, 0x4
.global lbl_804BDF18
lbl_804BDF18:
	.incbin "baserom.dol", 0x3C7B98, 0x8
.global lbl_804BDF20
lbl_804BDF20:
	.incbin "baserom.dol", 0x3C7BA0, 0x4
.global lbl_804BDF24
lbl_804BDF24:
	.incbin "baserom.dol", 0x3C7BA4, 0x4
.global lbl_804BDF28
lbl_804BDF28:
	.incbin "baserom.dol", 0x3C7BA8, 0x4
.global lbl_804BDF2C
lbl_804BDF2C:
	.incbin "baserom.dol", 0x3C7BAC, 0x4
.global lbl_804BDF30
lbl_804BDF30:
	.incbin "baserom.dol", 0x3C7BB0, 0x4
.global lbl_804BDF34
lbl_804BDF34:
	.incbin "baserom.dol", 0x3C7BB4, 0x4
.global lbl_804BDF38
lbl_804BDF38:
	.incbin "baserom.dol", 0x3C7BB8, 0x4
.global lbl_804BDF3C
lbl_804BDF3C:
	.incbin "baserom.dol", 0x3C7BBC, 0x4
.global lbl_804BDF40
lbl_804BDF40:
	.incbin "baserom.dol", 0x3C7BC0, 0x4
.global lbl_804BDF44
lbl_804BDF44:
	.incbin "baserom.dol", 0x3C7BC4, 0x4
.global lbl_804BDF48
lbl_804BDF48:
	.incbin "baserom.dol", 0x3C7BC8, 0x4
.global lbl_804BDF4C
lbl_804BDF4C:
	.incbin "baserom.dol", 0x3C7BCC, 0x4
.global lbl_804BDF50
lbl_804BDF50:
	.incbin "baserom.dol", 0x3C7BD0, 0x4
.global lbl_804BDF54
lbl_804BDF54:
	.incbin "baserom.dol", 0x3C7BD4, 0x4
.global lbl_804BDF58
lbl_804BDF58:
	.incbin "baserom.dol", 0x3C7BD8, 0x4
.global lbl_804BDF5C
lbl_804BDF5C:
	.incbin "baserom.dol", 0x3C7BDC, 0x4
.global lbl_804BDF60
lbl_804BDF60:
	.incbin "baserom.dol", 0x3C7BE0, 0x4
.global lbl_804BDF64
lbl_804BDF64:
	.incbin "baserom.dol", 0x3C7BE4, 0x4
.global lbl_804BDF68
lbl_804BDF68:
	.incbin "baserom.dol", 0x3C7BE8, 0x4
.global lbl_804BDF6C
lbl_804BDF6C:
	.incbin "baserom.dol", 0x3C7BEC, 0x4
.global lbl_804BDF70
lbl_804BDF70:
	.incbin "baserom.dol", 0x3C7BF0, 0x4
.global lbl_804BDF74
lbl_804BDF74:
	.incbin "baserom.dol", 0x3C7BF4, 0x4
.global lbl_804BDF78
lbl_804BDF78:
	.incbin "baserom.dol", 0x3C7BF8, 0x4
.global lbl_804BDF7C
lbl_804BDF7C:
	.incbin "baserom.dol", 0x3C7BFC, 0x4
.global lbl_804BDF80
lbl_804BDF80:
	.incbin "baserom.dol", 0x3C7C00, 0x4
.global lbl_804BDF84
lbl_804BDF84:
	.incbin "baserom.dol", 0x3C7C04, 0x4
.global lbl_804BDF88
lbl_804BDF88:
	.incbin "baserom.dol", 0x3C7C08, 0x4
.global lbl_804BDF8C
lbl_804BDF8C:
	.incbin "baserom.dol", 0x3C7C0C, 0x4
.global lbl_804BDF90
lbl_804BDF90:
	.incbin "baserom.dol", 0x3C7C10, 0x4
.global lbl_804BDF94
lbl_804BDF94:
	.incbin "baserom.dol", 0x3C7C14, 0x4
.global lbl_804BDF98
lbl_804BDF98:
	.incbin "baserom.dol", 0x3C7C18, 0x4
.global lbl_804BDF9C
lbl_804BDF9C:
	.incbin "baserom.dol", 0x3C7C1C, 0x4
.global lbl_804BDFA0
lbl_804BDFA0:
	.incbin "baserom.dol", 0x3C7C20, 0x4
.global lbl_804BDFA4
lbl_804BDFA4:
	.incbin "baserom.dol", 0x3C7C24, 0x4
.global lbl_804BDFA8
lbl_804BDFA8:
	.incbin "baserom.dol", 0x3C7C28, 0x4
.global lbl_804BDFAC
lbl_804BDFAC:
	.incbin "baserom.dol", 0x3C7C2C, 0x4
.global lbl_804BDFB0
lbl_804BDFB0:
	.incbin "baserom.dol", 0x3C7C30, 0x4
.global lbl_804BDFB4
lbl_804BDFB4:
	.incbin "baserom.dol", 0x3C7C34, 0x4
.global lbl_804BDFB8
lbl_804BDFB8:
	.incbin "baserom.dol", 0x3C7C38, 0x4
.global lbl_804BDFBC
lbl_804BDFBC:
	.incbin "baserom.dol", 0x3C7C3C, 0x4
.global lbl_804BDFC0
lbl_804BDFC0:
	.incbin "baserom.dol", 0x3C7C40, 0x4
.global lbl_804BDFC4
lbl_804BDFC4:
	.incbin "baserom.dol", 0x3C7C44, 0x4
.global lbl_804BDFC8
lbl_804BDFC8:
	.incbin "baserom.dol", 0x3C7C48, 0x4
.global lbl_804BDFCC
lbl_804BDFCC:
	.incbin "baserom.dol", 0x3C7C4C, 0x4
.global lbl_804BDFD0
lbl_804BDFD0:
	.incbin "baserom.dol", 0x3C7C50, 0x4
.global lbl_804BDFD4
lbl_804BDFD4:
	.incbin "baserom.dol", 0x3C7C54, 0x4
.global lbl_804BDFD8
lbl_804BDFD8:
	.incbin "baserom.dol", 0x3C7C58, 0x4
.global lbl_804BDFDC
lbl_804BDFDC:
	.incbin "baserom.dol", 0x3C7C5C, 0x4
.global lbl_804BDFE0
lbl_804BDFE0:
	.incbin "baserom.dol", 0x3C7C60, 0x4
.global lbl_804BDFE4
lbl_804BDFE4:
	.incbin "baserom.dol", 0x3C7C64, 0x4
.global lbl_804BDFE8
lbl_804BDFE8:
	.incbin "baserom.dol", 0x3C7C68, 0x4
.global lbl_804BDFEC
lbl_804BDFEC:
	.incbin "baserom.dol", 0x3C7C6C, 0x4
.global lbl_804BDFF0
lbl_804BDFF0:
	.incbin "baserom.dol", 0x3C7C70, 0x4
.global lbl_804BDFF4
lbl_804BDFF4:
	.incbin "baserom.dol", 0x3C7C74, 0x4
.global lbl_804BDFF8
lbl_804BDFF8:
	.incbin "baserom.dol", 0x3C7C78, 0x4
.global lbl_804BDFFC
lbl_804BDFFC:
	.incbin "baserom.dol", 0x3C7C7C, 0x4
.global lbl_804BE000
lbl_804BE000:
	.incbin "baserom.dol", 0x3C7C80, 0x4
.global lbl_804BE004
lbl_804BE004:
	.incbin "baserom.dol", 0x3C7C84, 0x4
.global lbl_804BE008
lbl_804BE008:
	.incbin "baserom.dol", 0x3C7C88, 0x4
.global lbl_804BE00C
lbl_804BE00C:
	.incbin "baserom.dol", 0x3C7C8C, 0x4
.global lbl_804BE010
lbl_804BE010:
	.incbin "baserom.dol", 0x3C7C90, 0x4
.global lbl_804BE014
lbl_804BE014:
	.incbin "baserom.dol", 0x3C7C94, 0x4
.global lbl_804BE018
lbl_804BE018:
	.incbin "baserom.dol", 0x3C7C98, 0x4
.global lbl_804BE01C
lbl_804BE01C:
	.incbin "baserom.dol", 0x3C7C9C, 0x4
.global lbl_804BE020
lbl_804BE020:
	.incbin "baserom.dol", 0x3C7CA0, 0x4
.global lbl_804BE024
lbl_804BE024:
	.incbin "baserom.dol", 0x3C7CA4, 0x4
.global lbl_804BE028
lbl_804BE028:
	.incbin "baserom.dol", 0x3C7CA8, 0x4
.global lbl_804BE02C
lbl_804BE02C:
	.incbin "baserom.dol", 0x3C7CAC, 0x4
.global lbl_804BE030
lbl_804BE030:
	.incbin "baserom.dol", 0x3C7CB0, 0x4
.global lbl_804BE034
lbl_804BE034:
	.incbin "baserom.dol", 0x3C7CB4, 0x4
.global lbl_804BE038
lbl_804BE038:
	.incbin "baserom.dol", 0x3C7CB8, 0x4
.global lbl_804BE03C
lbl_804BE03C:
	.incbin "baserom.dol", 0x3C7CBC, 0x4
.global lbl_804BE040
lbl_804BE040:
	.incbin "baserom.dol", 0x3C7CC0, 0x4
.global lbl_804BE044
lbl_804BE044:
	.incbin "baserom.dol", 0x3C7CC4, 0x4
.global lbl_804BE048
lbl_804BE048:
	.incbin "baserom.dol", 0x3C7CC8, 0x4
.global lbl_804BE04C
lbl_804BE04C:
	.incbin "baserom.dol", 0x3C7CCC, 0x4
.global lbl_804BE050
lbl_804BE050:
	.incbin "baserom.dol", 0x3C7CD0, 0x4
.global lbl_804BE054
lbl_804BE054:
	.incbin "baserom.dol", 0x3C7CD4, 0x4
.global lbl_804BE058
lbl_804BE058:
	.incbin "baserom.dol", 0x3C7CD8, 0x4
.global lbl_804BE05C
lbl_804BE05C:
	.incbin "baserom.dol", 0x3C7CDC, 0x4
.global lbl_804BE060
lbl_804BE060:
	.incbin "baserom.dol", 0x3C7CE0, 0x4
.global lbl_804BE064
lbl_804BE064:
	.incbin "baserom.dol", 0x3C7CE4, 0x4
.global lbl_804BE068
lbl_804BE068:
	.incbin "baserom.dol", 0x3C7CE8, 0x4
.global lbl_804BE06C
lbl_804BE06C:
	.incbin "baserom.dol", 0x3C7CEC, 0x4
.global lbl_804BE070
lbl_804BE070:
	.incbin "baserom.dol", 0x3C7CF0, 0x4
.global lbl_804BE074
lbl_804BE074:
	.incbin "baserom.dol", 0x3C7CF4, 0x4
.global lbl_804BE078
lbl_804BE078:
	.incbin "baserom.dol", 0x3C7CF8, 0x4
.global lbl_804BE07C
lbl_804BE07C:
	.incbin "baserom.dol", 0x3C7CFC, 0x4
.global lbl_804BE080
lbl_804BE080:
	.incbin "baserom.dol", 0x3C7D00, 0x4
.global lbl_804BE084
lbl_804BE084:
	.incbin "baserom.dol", 0x3C7D04, 0x4
.global lbl_804BE088
lbl_804BE088:
	.incbin "baserom.dol", 0x3C7D08, 0x4
.global lbl_804BE08C
lbl_804BE08C:
	.incbin "baserom.dol", 0x3C7D0C, 0x4
.global lbl_804BE090
lbl_804BE090:
	.incbin "baserom.dol", 0x3C7D10, 0x4
.global lbl_804BE094
lbl_804BE094:
	.incbin "baserom.dol", 0x3C7D14, 0x4
.global lbl_804BE098
lbl_804BE098:
	.incbin "baserom.dol", 0x3C7D18, 0x4
.global lbl_804BE09C
lbl_804BE09C:
	.incbin "baserom.dol", 0x3C7D1C, 0x4
.global lbl_804BE0A0
lbl_804BE0A0:
	.incbin "baserom.dol", 0x3C7D20, 0x4
.global lbl_804BE0A4
lbl_804BE0A4:
	.incbin "baserom.dol", 0x3C7D24, 0x4
.global lbl_804BE0A8
lbl_804BE0A8:
	.incbin "baserom.dol", 0x3C7D28, 0x4
.global lbl_804BE0AC
lbl_804BE0AC:
	.incbin "baserom.dol", 0x3C7D2C, 0x4
.global lbl_804BE0B0
lbl_804BE0B0:
	.incbin "baserom.dol", 0x3C7D30, 0x4
.global lbl_804BE0B4
lbl_804BE0B4:
	.incbin "baserom.dol", 0x3C7D34, 0x4
.global lbl_804BE0B8
lbl_804BE0B8:
	.incbin "baserom.dol", 0x3C7D38, 0x4
.global lbl_804BE0BC
lbl_804BE0BC:
	.incbin "baserom.dol", 0x3C7D3C, 0x4
.global lbl_804BE0C0
lbl_804BE0C0:
	.incbin "baserom.dol", 0x3C7D40, 0x4
.global lbl_804BE0C4
lbl_804BE0C4:
	.incbin "baserom.dol", 0x3C7D44, 0x4
.global lbl_804BE0C8
lbl_804BE0C8:
	.incbin "baserom.dol", 0x3C7D48, 0x4
.global lbl_804BE0CC
lbl_804BE0CC:
	.incbin "baserom.dol", 0x3C7D4C, 0x4
.global lbl_804BE0D0
lbl_804BE0D0:
	.incbin "baserom.dol", 0x3C7D50, 0x4
.global lbl_804BE0D4
lbl_804BE0D4:
	.incbin "baserom.dol", 0x3C7D54, 0x4
.global lbl_804BE0D8
lbl_804BE0D8:
	.incbin "baserom.dol", 0x3C7D58, 0x2
.global lbl_804BE0DA
lbl_804BE0DA:
	.incbin "baserom.dol", 0x3C7D5A, 0x2
.global lbl_804BE0DC
lbl_804BE0DC:
	.incbin "baserom.dol", 0x3C7D5C, 0x4
.global lbl_804BE0E0
lbl_804BE0E0:
	.incbin "baserom.dol", 0x3C7D60, 0x4
.global lbl_804BE0E4
lbl_804BE0E4:
	.incbin "baserom.dol", 0x3C7D64, 0x4
.global lbl_804BE0E8
lbl_804BE0E8:
	.incbin "baserom.dol", 0x3C7D68, 0x4
.global lbl_804BE0EC
lbl_804BE0EC:
	.incbin "baserom.dol", 0x3C7D6C, 0x4
.global lbl_804BE0F0
lbl_804BE0F0:
	.incbin "baserom.dol", 0x3C7D70, 0x4
.global lbl_804BE0F4
lbl_804BE0F4:
	.incbin "baserom.dol", 0x3C7D74, 0x4
.global lbl_804BE0F8
lbl_804BE0F8:
	.incbin "baserom.dol", 0x3C7D78, 0x8
.global lbl_804BE100
lbl_804BE100:
	.incbin "baserom.dol", 0x3C7D80, 0x8
.global lbl_804BE108
lbl_804BE108:
	.incbin "baserom.dol", 0x3C7D88, 0x8
.global lbl_804BE110
lbl_804BE110:
	.incbin "baserom.dol", 0x3C7D90, 0x4
.global lbl_804BE114
lbl_804BE114:
	.incbin "baserom.dol", 0x3C7D94, 0x4
.global lbl_804BE118
lbl_804BE118:
	.incbin "baserom.dol", 0x3C7D98, 0x4
.global lbl_804BE11C
lbl_804BE11C:
	.incbin "baserom.dol", 0x3C7D9C, 0x4
.global lbl_804BE120
lbl_804BE120:
	.incbin "baserom.dol", 0x3C7DA0, 0x4
.global lbl_804BE124
lbl_804BE124:
	.incbin "baserom.dol", 0x3C7DA4, 0x4
.global lbl_804BE128
lbl_804BE128:
	.incbin "baserom.dol", 0x3C7DA8, 0x4
.global lbl_804BE12C
lbl_804BE12C:
	.incbin "baserom.dol", 0x3C7DAC, 0x4
.global lbl_804BE130
lbl_804BE130:
	.incbin "baserom.dol", 0x3C7DB0, 0x4
.global lbl_804BE134
lbl_804BE134:
	.incbin "baserom.dol", 0x3C7DB4, 0x4
.global lbl_804BE138
lbl_804BE138:
	.incbin "baserom.dol", 0x3C7DB8, 0x4
.global lbl_804BE13C
lbl_804BE13C:
	.incbin "baserom.dol", 0x3C7DBC, 0x4
.global lbl_804BE140
lbl_804BE140:
	.incbin "baserom.dol", 0x3C7DC0, 0x4
.global lbl_804BE144
lbl_804BE144:
	.incbin "baserom.dol", 0x3C7DC4, 0x4
.global lbl_804BE148
lbl_804BE148:
	.incbin "baserom.dol", 0x3C7DC8, 0x4
.global lbl_804BE14C
lbl_804BE14C:
	.incbin "baserom.dol", 0x3C7DCC, 0x4
.global lbl_804BE150
lbl_804BE150:
	.incbin "baserom.dol", 0x3C7DD0, 0x4
.global lbl_804BE154
lbl_804BE154:
	.incbin "baserom.dol", 0x3C7DD4, 0x4
.global lbl_804BE158
lbl_804BE158:
	.incbin "baserom.dol", 0x3C7DD8, 0x4
.global lbl_804BE15C
lbl_804BE15C:
	.incbin "baserom.dol", 0x3C7DDC, 0x4
.global lbl_804BE160
lbl_804BE160:
	.incbin "baserom.dol", 0x3C7DE0, 0x4
.global lbl_804BE164
lbl_804BE164:
	.incbin "baserom.dol", 0x3C7DE4, 0x4
.global lbl_804BE168
lbl_804BE168:
	.incbin "baserom.dol", 0x3C7DE8, 0x4
.global lbl_804BE16C
lbl_804BE16C:
	.incbin "baserom.dol", 0x3C7DEC, 0x4
.global lbl_804BE170
lbl_804BE170:
	.incbin "baserom.dol", 0x3C7DF0, 0x4
.global lbl_804BE174
lbl_804BE174:
	.incbin "baserom.dol", 0x3C7DF4, 0x4
.global lbl_804BE178
lbl_804BE178:
	.incbin "baserom.dol", 0x3C7DF8, 0x4
.global lbl_804BE17C
lbl_804BE17C:
	.incbin "baserom.dol", 0x3C7DFC, 0x4
.global lbl_804BE180
lbl_804BE180:
	.incbin "baserom.dol", 0x3C7E00, 0x4
.global lbl_804BE184
lbl_804BE184:
	.incbin "baserom.dol", 0x3C7E04, 0x4
.global lbl_804BE188
lbl_804BE188:
	.incbin "baserom.dol", 0x3C7E08, 0x4
.global lbl_804BE18C
lbl_804BE18C:
	.incbin "baserom.dol", 0x3C7E0C, 0x4
.global lbl_804BE190
lbl_804BE190:
	.incbin "baserom.dol", 0x3C7E10, 0x4
.global lbl_804BE194
lbl_804BE194:
	.incbin "baserom.dol", 0x3C7E14, 0x4
.global lbl_804BE198
lbl_804BE198:
	.incbin "baserom.dol", 0x3C7E18, 0x4
.global lbl_804BE19C
lbl_804BE19C:
	.incbin "baserom.dol", 0x3C7E1C, 0x4
.global lbl_804BE1A0
lbl_804BE1A0:
	.incbin "baserom.dol", 0x3C7E20, 0x4
.global lbl_804BE1A4
lbl_804BE1A4:
	.incbin "baserom.dol", 0x3C7E24, 0x4
.global lbl_804BE1A8
lbl_804BE1A8:
	.incbin "baserom.dol", 0x3C7E28, 0x4
.global lbl_804BE1AC
lbl_804BE1AC:
	.incbin "baserom.dol", 0x3C7E2C, 0x4
.global lbl_804BE1B0
lbl_804BE1B0:
	.incbin "baserom.dol", 0x3C7E30, 0x4
.global lbl_804BE1B4
lbl_804BE1B4:
	.incbin "baserom.dol", 0x3C7E34, 0x4
.global lbl_804BE1B8
lbl_804BE1B8:
	.incbin "baserom.dol", 0x3C7E38, 0x4
.global lbl_804BE1BC
lbl_804BE1BC:
	.incbin "baserom.dol", 0x3C7E3C, 0x4
.global lbl_804BE1C0
lbl_804BE1C0:
	.incbin "baserom.dol", 0x3C7E40, 0x4
.global lbl_804BE1C4
lbl_804BE1C4:
	.incbin "baserom.dol", 0x3C7E44, 0x4
.global lbl_804BE1C8
lbl_804BE1C8:
	.incbin "baserom.dol", 0x3C7E48, 0x4
.global lbl_804BE1CC
lbl_804BE1CC:
	.incbin "baserom.dol", 0x3C7E4C, 0x4
.global lbl_804BE1D0
lbl_804BE1D0:
	.incbin "baserom.dol", 0x3C7E50, 0x4
.global lbl_804BE1D4
lbl_804BE1D4:
	.incbin "baserom.dol", 0x3C7E54, 0x4
.global lbl_804BE1D8
lbl_804BE1D8:
	.incbin "baserom.dol", 0x3C7E58, 0x4
.global lbl_804BE1DC
lbl_804BE1DC:
	.incbin "baserom.dol", 0x3C7E5C, 0x4
.global lbl_804BE1E0
lbl_804BE1E0:
	.incbin "baserom.dol", 0x3C7E60, 0x4
.global lbl_804BE1E4
lbl_804BE1E4:
	.incbin "baserom.dol", 0x3C7E64, 0x4
.global lbl_804BE1E8
lbl_804BE1E8:
	.incbin "baserom.dol", 0x3C7E68, 0x4
.global lbl_804BE1EC
lbl_804BE1EC:
	.incbin "baserom.dol", 0x3C7E6C, 0x4
.global lbl_804BE1F0
lbl_804BE1F0:
	.incbin "baserom.dol", 0x3C7E70, 0x4
.global lbl_804BE1F4
lbl_804BE1F4:
	.incbin "baserom.dol", 0x3C7E74, 0x4
.global lbl_804BE1F8
lbl_804BE1F8:
	.incbin "baserom.dol", 0x3C7E78, 0x4
.global lbl_804BE1FC
lbl_804BE1FC:
	.incbin "baserom.dol", 0x3C7E7C, 0x4
.global lbl_804BE200
lbl_804BE200:
	.incbin "baserom.dol", 0x3C7E80, 0x4
.global lbl_804BE204
lbl_804BE204:
	.incbin "baserom.dol", 0x3C7E84, 0x4
.global lbl_804BE208
lbl_804BE208:
	.incbin "baserom.dol", 0x3C7E88, 0x8
.global lbl_804BE210
lbl_804BE210:
	.incbin "baserom.dol", 0x3C7E90, 0x4
.global lbl_804BE214
lbl_804BE214:
	.incbin "baserom.dol", 0x3C7E94, 0x4
.global lbl_804BE218
lbl_804BE218:
	.incbin "baserom.dol", 0x3C7E98, 0x4
.global lbl_804BE21C
lbl_804BE21C:
	.incbin "baserom.dol", 0x3C7E9C, 0x4
.global lbl_804BE220
lbl_804BE220:
	.incbin "baserom.dol", 0x3C7EA0, 0x4
.global lbl_804BE224
lbl_804BE224:
	.incbin "baserom.dol", 0x3C7EA4, 0x4
.global lbl_804BE228
lbl_804BE228:
	.incbin "baserom.dol", 0x3C7EA8, 0x4
.global lbl_804BE22C
lbl_804BE22C:
	.incbin "baserom.dol", 0x3C7EAC, 0x4
.global lbl_804BE230
lbl_804BE230:
	.incbin "baserom.dol", 0x3C7EB0, 0x4
.global lbl_804BE234
lbl_804BE234:
	.incbin "baserom.dol", 0x3C7EB4, 0x4
.global lbl_804BE238
lbl_804BE238:
	.incbin "baserom.dol", 0x3C7EB8, 0x8
.global lbl_804BE240
lbl_804BE240:
	.incbin "baserom.dol", 0x3C7EC0, 0x4
.global lbl_804BE244
lbl_804BE244:
	.incbin "baserom.dol", 0x3C7EC4, 0x4
.global lbl_804BE248
lbl_804BE248:
	.incbin "baserom.dol", 0x3C7EC8, 0x4
.global lbl_804BE24C
lbl_804BE24C:
	.incbin "baserom.dol", 0x3C7ECC, 0x4
.global lbl_804BE250
lbl_804BE250:
	.incbin "baserom.dol", 0x3C7ED0, 0x4
.global lbl_804BE254
lbl_804BE254:
	.incbin "baserom.dol", 0x3C7ED4, 0x4
.global lbl_804BE258
lbl_804BE258:
	.incbin "baserom.dol", 0x3C7ED8, 0x4
.global lbl_804BE25C
lbl_804BE25C:
	.incbin "baserom.dol", 0x3C7EDC, 0x4
.global lbl_804BE260
lbl_804BE260:
	.incbin "baserom.dol", 0x3C7EE0, 0x4
.global lbl_804BE264
lbl_804BE264:
	.incbin "baserom.dol", 0x3C7EE4, 0x4
.global lbl_804BE268
lbl_804BE268:
	.incbin "baserom.dol", 0x3C7EE8, 0x4
.global lbl_804BE26C
lbl_804BE26C:
	.incbin "baserom.dol", 0x3C7EEC, 0x4
.global lbl_804BE270
lbl_804BE270:
	.incbin "baserom.dol", 0x3C7EF0, 0x4
.global lbl_804BE274
lbl_804BE274:
	.incbin "baserom.dol", 0x3C7EF4, 0x4
.global lbl_804BE278
lbl_804BE278:
	.incbin "baserom.dol", 0x3C7EF8, 0x4
.global lbl_804BE27C
lbl_804BE27C:
	.incbin "baserom.dol", 0x3C7EFC, 0x4
.global lbl_804BE280
lbl_804BE280:
	.incbin "baserom.dol", 0x3C7F00, 0x4
.global lbl_804BE284
lbl_804BE284:
	.incbin "baserom.dol", 0x3C7F04, 0x4
.global lbl_804BE288
lbl_804BE288:
	.incbin "baserom.dol", 0x3C7F08, 0x4
.global lbl_804BE28C
lbl_804BE28C:
	.incbin "baserom.dol", 0x3C7F0C, 0x4
.global lbl_804BE290
lbl_804BE290:
	.incbin "baserom.dol", 0x3C7F10, 0x4
.global lbl_804BE294
lbl_804BE294:
	.incbin "baserom.dol", 0x3C7F14, 0x4
.global lbl_804BE298
lbl_804BE298:
	.incbin "baserom.dol", 0x3C7F18, 0x4
.global lbl_804BE29C
lbl_804BE29C:
	.incbin "baserom.dol", 0x3C7F1C, 0x4
.global lbl_804BE2A0
lbl_804BE2A0:
	.incbin "baserom.dol", 0x3C7F20, 0x4
.global lbl_804BE2A4
lbl_804BE2A4:
	.incbin "baserom.dol", 0x3C7F24, 0x4
.global lbl_804BE2A8
lbl_804BE2A8:
	.incbin "baserom.dol", 0x3C7F28, 0x4
.global lbl_804BE2AC
lbl_804BE2AC:
	.incbin "baserom.dol", 0x3C7F2C, 0x4
.global lbl_804BE2B0
lbl_804BE2B0:
	.incbin "baserom.dol", 0x3C7F30, 0x4
.global lbl_804BE2B4
lbl_804BE2B4:
	.incbin "baserom.dol", 0x3C7F34, 0x4
.global lbl_804BE2B8
lbl_804BE2B8:
	.incbin "baserom.dol", 0x3C7F38, 0x4
.global lbl_804BE2BC
lbl_804BE2BC:
	.incbin "baserom.dol", 0x3C7F3C, 0x4
.global lbl_804BE2C0
lbl_804BE2C0:
	.incbin "baserom.dol", 0x3C7F40, 0x4
.global lbl_804BE2C4
lbl_804BE2C4:
	.incbin "baserom.dol", 0x3C7F44, 0x4
.global lbl_804BE2C8
lbl_804BE2C8:
	.incbin "baserom.dol", 0x3C7F48, 0x4
.global lbl_804BE2CC
lbl_804BE2CC:
	.incbin "baserom.dol", 0x3C7F4C, 0x4
.global lbl_804BE2D0
lbl_804BE2D0:
	.incbin "baserom.dol", 0x3C7F50, 0x4
.global lbl_804BE2D4
lbl_804BE2D4:
	.incbin "baserom.dol", 0x3C7F54, 0x4
.global lbl_804BE2D8
lbl_804BE2D8:
	.incbin "baserom.dol", 0x3C7F58, 0x4
.global lbl_804BE2DC
lbl_804BE2DC:
	.incbin "baserom.dol", 0x3C7F5C, 0x4
.global lbl_804BE2E0
lbl_804BE2E0:
	.incbin "baserom.dol", 0x3C7F60, 0x4
.global lbl_804BE2E4
lbl_804BE2E4:
	.incbin "baserom.dol", 0x3C7F64, 0x4
.global lbl_804BE2E8
lbl_804BE2E8:
	.incbin "baserom.dol", 0x3C7F68, 0x4
.global lbl_804BE2EC
lbl_804BE2EC:
	.incbin "baserom.dol", 0x3C7F6C, 0x4
.global lbl_804BE2F0
lbl_804BE2F0:
	.incbin "baserom.dol", 0x3C7F70, 0x4
.global lbl_804BE2F4
lbl_804BE2F4:
	.incbin "baserom.dol", 0x3C7F74, 0x4
.global lbl_804BE2F8
lbl_804BE2F8:
	.incbin "baserom.dol", 0x3C7F78, 0x4
.global lbl_804BE2FC
lbl_804BE2FC:
	.incbin "baserom.dol", 0x3C7F7C, 0x4
.global lbl_804BE300
lbl_804BE300:
	.incbin "baserom.dol", 0x3C7F80, 0x4
.global lbl_804BE304
lbl_804BE304:
	.incbin "baserom.dol", 0x3C7F84, 0x4
.global lbl_804BE308
lbl_804BE308:
	.incbin "baserom.dol", 0x3C7F88, 0x4
.global lbl_804BE30C
lbl_804BE30C:
	.incbin "baserom.dol", 0x3C7F8C, 0x4
.global lbl_804BE310
lbl_804BE310:
	.incbin "baserom.dol", 0x3C7F90, 0x4
.global lbl_804BE314
lbl_804BE314:
	.incbin "baserom.dol", 0x3C7F94, 0x4
.global lbl_804BE318
lbl_804BE318:
	.incbin "baserom.dol", 0x3C7F98, 0x4
.global lbl_804BE31C
lbl_804BE31C:
	.incbin "baserom.dol", 0x3C7F9C, 0x4
.global lbl_804BE320
lbl_804BE320:
	.incbin "baserom.dol", 0x3C7FA0, 0x4
.global lbl_804BE324
lbl_804BE324:
	.incbin "baserom.dol", 0x3C7FA4, 0x4
.global lbl_804BE328
lbl_804BE328:
	.incbin "baserom.dol", 0x3C7FA8, 0x4
.global lbl_804BE32C
lbl_804BE32C:
	.incbin "baserom.dol", 0x3C7FAC, 0x4
.global lbl_804BE330
lbl_804BE330:
	.incbin "baserom.dol", 0x3C7FB0, 0x4
.global lbl_804BE334
lbl_804BE334:
	.incbin "baserom.dol", 0x3C7FB4, 0x4
.global lbl_804BE338
lbl_804BE338:
	.incbin "baserom.dol", 0x3C7FB8, 0x4
.global lbl_804BE33C
lbl_804BE33C:
	.incbin "baserom.dol", 0x3C7FBC, 0x4
.global lbl_804BE340
lbl_804BE340:
	.incbin "baserom.dol", 0x3C7FC0, 0x4
.global lbl_804BE344
lbl_804BE344:
	.incbin "baserom.dol", 0x3C7FC4, 0x4
.global lbl_804BE348
lbl_804BE348:
	.incbin "baserom.dol", 0x3C7FC8, 0x4
.global lbl_804BE34C
lbl_804BE34C:
	.incbin "baserom.dol", 0x3C7FCC, 0x4
.global lbl_804BE350
lbl_804BE350:
	.incbin "baserom.dol", 0x3C7FD0, 0x4
.global lbl_804BE354
lbl_804BE354:
	.incbin "baserom.dol", 0x3C7FD4, 0x4
.global lbl_804BE358
lbl_804BE358:
	.incbin "baserom.dol", 0x3C7FD8, 0x4
.global lbl_804BE35C
lbl_804BE35C:
	.incbin "baserom.dol", 0x3C7FDC, 0x4
.global lbl_804BE360
lbl_804BE360:
	.incbin "baserom.dol", 0x3C7FE0, 0x4
.global lbl_804BE364
lbl_804BE364:
	.incbin "baserom.dol", 0x3C7FE4, 0x4
.global lbl_804BE368
lbl_804BE368:
	.incbin "baserom.dol", 0x3C7FE8, 0x4
.global lbl_804BE36C
lbl_804BE36C:
	.incbin "baserom.dol", 0x3C7FEC, 0x4
.global lbl_804BE370
lbl_804BE370:
	.incbin "baserom.dol", 0x3C7FF0, 0x4
.global lbl_804BE374
lbl_804BE374:
	.incbin "baserom.dol", 0x3C7FF4, 0x4
.global lbl_804BE378
lbl_804BE378:
	.incbin "baserom.dol", 0x3C7FF8, 0x4
.global lbl_804BE37C
lbl_804BE37C:
	.incbin "baserom.dol", 0x3C7FFC, 0x4
.global lbl_804BE380
lbl_804BE380:
	.incbin "baserom.dol", 0x3C8000, 0x4
.global lbl_804BE384
lbl_804BE384:
	.incbin "baserom.dol", 0x3C8004, 0x4
.global lbl_804BE388
lbl_804BE388:
	.incbin "baserom.dol", 0x3C8008, 0x8
.global lbl_804BE390
lbl_804BE390:
	.incbin "baserom.dol", 0x3C8010, 0x8
.global lbl_804BE398
lbl_804BE398:
	.incbin "baserom.dol", 0x3C8018, 0x4
.global lbl_804BE39C
lbl_804BE39C:
	.incbin "baserom.dol", 0x3C801C, 0x4
.global lbl_804BE3A0
lbl_804BE3A0:
	.incbin "baserom.dol", 0x3C8020, 0x4
.global lbl_804BE3A4
lbl_804BE3A4:
	.incbin "baserom.dol", 0x3C8024, 0x4
.global lbl_804BE3A8
lbl_804BE3A8:
	.incbin "baserom.dol", 0x3C8028, 0x8
.global lbl_804BE3B0
lbl_804BE3B0:
	.incbin "baserom.dol", 0x3C8030, 0x4
.global lbl_804BE3B4
lbl_804BE3B4:
	.incbin "baserom.dol", 0x3C8034, 0x4
.global lbl_804BE3B8
lbl_804BE3B8:
	.incbin "baserom.dol", 0x3C8038, 0x4
.global lbl_804BE3BC
lbl_804BE3BC:
	.incbin "baserom.dol", 0x3C803C, 0x4
.global lbl_804BE3C0
lbl_804BE3C0:
	.incbin "baserom.dol", 0x3C8040, 0x4
.global lbl_804BE3C4
lbl_804BE3C4:
	.incbin "baserom.dol", 0x3C8044, 0x4
.global lbl_804BE3C8
lbl_804BE3C8:
	.incbin "baserom.dol", 0x3C8048, 0x4
.global lbl_804BE3CC
lbl_804BE3CC:
	.incbin "baserom.dol", 0x3C804C, 0x4
.global lbl_804BE3D0
lbl_804BE3D0:
	.incbin "baserom.dol", 0x3C8050, 0x4
.global lbl_804BE3D4
lbl_804BE3D4:
	.incbin "baserom.dol", 0x3C8054, 0x4
.global lbl_804BE3D8
lbl_804BE3D8:
	.incbin "baserom.dol", 0x3C8058, 0x4
.global lbl_804BE3DC
lbl_804BE3DC:
	.incbin "baserom.dol", 0x3C805C, 0x4
.global lbl_804BE3E0
lbl_804BE3E0:
	.incbin "baserom.dol", 0x3C8060, 0x4
.global lbl_804BE3E4
lbl_804BE3E4:
	.incbin "baserom.dol", 0x3C8064, 0x4
.global lbl_804BE3E8
lbl_804BE3E8:
	.incbin "baserom.dol", 0x3C8068, 0x4
.global lbl_804BE3EC
lbl_804BE3EC:
	.incbin "baserom.dol", 0x3C806C, 0x4
.global lbl_804BE3F0
lbl_804BE3F0:
	.incbin "baserom.dol", 0x3C8070, 0x4
.global lbl_804BE3F4
lbl_804BE3F4:
	.incbin "baserom.dol", 0x3C8074, 0x4
.global lbl_804BE3F8
lbl_804BE3F8:
	.incbin "baserom.dol", 0x3C8078, 0x4
.global lbl_804BE3FC
lbl_804BE3FC:
	.incbin "baserom.dol", 0x3C807C, 0x4
.global lbl_804BE400
lbl_804BE400:
	.incbin "baserom.dol", 0x3C8080, 0x4
.global lbl_804BE404
lbl_804BE404:
	.incbin "baserom.dol", 0x3C8084, 0x4
.global lbl_804BE408
lbl_804BE408:
	.incbin "baserom.dol", 0x3C8088, 0x4
.global lbl_804BE40C
lbl_804BE40C:
	.incbin "baserom.dol", 0x3C808C, 0x4
.global lbl_804BE410
lbl_804BE410:
	.incbin "baserom.dol", 0x3C8090, 0x4
.global lbl_804BE414
lbl_804BE414:
	.incbin "baserom.dol", 0x3C8094, 0x4
.global lbl_804BE418
lbl_804BE418:
	.incbin "baserom.dol", 0x3C8098, 0x4
.global lbl_804BE41C
lbl_804BE41C:
	.incbin "baserom.dol", 0x3C809C, 0x4
.global lbl_804BE420
lbl_804BE420:
	.incbin "baserom.dol", 0x3C80A0, 0x4
.global lbl_804BE424
lbl_804BE424:
	.incbin "baserom.dol", 0x3C80A4, 0x4
.global lbl_804BE428
lbl_804BE428:
	.incbin "baserom.dol", 0x3C80A8, 0x4
.global lbl_804BE42C
lbl_804BE42C:
	.incbin "baserom.dol", 0x3C80AC, 0x4
.global lbl_804BE430
lbl_804BE430:
	.incbin "baserom.dol", 0x3C80B0, 0x4
.global lbl_804BE434
lbl_804BE434:
	.incbin "baserom.dol", 0x3C80B4, 0x4
.global lbl_804BE438
lbl_804BE438:
	.incbin "baserom.dol", 0x3C80B8, 0x4
.global lbl_804BE43C
lbl_804BE43C:
	.incbin "baserom.dol", 0x3C80BC, 0x4
.global lbl_804BE440
lbl_804BE440:
	.incbin "baserom.dol", 0x3C80C0, 0x4
.global lbl_804BE444
lbl_804BE444:
	.incbin "baserom.dol", 0x3C80C4, 0x4
.global lbl_804BE448
lbl_804BE448:
	.incbin "baserom.dol", 0x3C80C8, 0x4
.global lbl_804BE44C
lbl_804BE44C:
	.incbin "baserom.dol", 0x3C80CC, 0x4
.global lbl_804BE450
lbl_804BE450:
	.incbin "baserom.dol", 0x3C80D0, 0x4
.global lbl_804BE454
lbl_804BE454:
	.incbin "baserom.dol", 0x3C80D4, 0x4
.global lbl_804BE458
lbl_804BE458:
	.incbin "baserom.dol", 0x3C80D8, 0x4
.global lbl_804BE45C
lbl_804BE45C:
	.incbin "baserom.dol", 0x3C80DC, 0x4
.global lbl_804BE460
lbl_804BE460:
	.incbin "baserom.dol", 0x3C80E0, 0x4
.global lbl_804BE464
lbl_804BE464:
	.incbin "baserom.dol", 0x3C80E4, 0x4
.global lbl_804BE468
lbl_804BE468:
	.incbin "baserom.dol", 0x3C80E8, 0x4
.global lbl_804BE46C
lbl_804BE46C:
	.incbin "baserom.dol", 0x3C80EC, 0x4
.global lbl_804BE470
lbl_804BE470:
	.incbin "baserom.dol", 0x3C80F0, 0x4
.global lbl_804BE474
lbl_804BE474:
	.incbin "baserom.dol", 0x3C80F4, 0x4
.global lbl_804BE478
lbl_804BE478:
	.incbin "baserom.dol", 0x3C80F8, 0x4
.global lbl_804BE47C
lbl_804BE47C:
	.incbin "baserom.dol", 0x3C80FC, 0x4
.global lbl_804BE480
lbl_804BE480:
	.incbin "baserom.dol", 0x3C8100, 0x4
.global lbl_804BE484
lbl_804BE484:
	.incbin "baserom.dol", 0x3C8104, 0x4
.global lbl_804BE488
lbl_804BE488:
	.incbin "baserom.dol", 0x3C8108, 0x4
.global lbl_804BE48C
lbl_804BE48C:
	.incbin "baserom.dol", 0x3C810C, 0x4
.global lbl_804BE490
lbl_804BE490:
	.incbin "baserom.dol", 0x3C8110, 0x4
.global lbl_804BE494
lbl_804BE494:
	.incbin "baserom.dol", 0x3C8114, 0x4
.global lbl_804BE498
lbl_804BE498:
	.incbin "baserom.dol", 0x3C8118, 0x4
.global lbl_804BE49C
lbl_804BE49C:
	.incbin "baserom.dol", 0x3C811C, 0x4
.global lbl_804BE4A0
lbl_804BE4A0:
	.incbin "baserom.dol", 0x3C8120, 0x4
.global lbl_804BE4A4
lbl_804BE4A4:
	.incbin "baserom.dol", 0x3C8124, 0x4
.global lbl_804BE4A8
lbl_804BE4A8:
	.incbin "baserom.dol", 0x3C8128, 0x4
.global lbl_804BE4AC
lbl_804BE4AC:
	.incbin "baserom.dol", 0x3C812C, 0x4
.global lbl_804BE4B0
lbl_804BE4B0:
	.incbin "baserom.dol", 0x3C8130, 0x4
.global lbl_804BE4B4
lbl_804BE4B4:
	.incbin "baserom.dol", 0x3C8134, 0x4
.global lbl_804BE4B8
lbl_804BE4B8:
	.incbin "baserom.dol", 0x3C8138, 0x4
.global lbl_804BE4BC
lbl_804BE4BC:
	.incbin "baserom.dol", 0x3C813C, 0x4
.global lbl_804BE4C0
lbl_804BE4C0:
	.incbin "baserom.dol", 0x3C8140, 0x4
.global lbl_804BE4C4
lbl_804BE4C4:
	.incbin "baserom.dol", 0x3C8144, 0x4
.global lbl_804BE4C8
lbl_804BE4C8:
	.incbin "baserom.dol", 0x3C8148, 0x4
.global lbl_804BE4CC
lbl_804BE4CC:
	.incbin "baserom.dol", 0x3C814C, 0x4
.global lbl_804BE4D0
lbl_804BE4D0:
	.incbin "baserom.dol", 0x3C8150, 0x4
.global lbl_804BE4D4
lbl_804BE4D4:
	.incbin "baserom.dol", 0x3C8154, 0x4
.global lbl_804BE4D8
lbl_804BE4D8:
	.incbin "baserom.dol", 0x3C8158, 0x4
.global lbl_804BE4DC
lbl_804BE4DC:
	.incbin "baserom.dol", 0x3C815C, 0x4
.global lbl_804BE4E0
lbl_804BE4E0:
	.incbin "baserom.dol", 0x3C8160, 0x4
.global lbl_804BE4E4
lbl_804BE4E4:
	.incbin "baserom.dol", 0x3C8164, 0x4
.global lbl_804BE4E8
lbl_804BE4E8:
	.incbin "baserom.dol", 0x3C8168, 0x4
.global lbl_804BE4EC
lbl_804BE4EC:
	.incbin "baserom.dol", 0x3C816C, 0x4
.global lbl_804BE4F0
lbl_804BE4F0:
	.incbin "baserom.dol", 0x3C8170, 0x4
.global lbl_804BE4F4
lbl_804BE4F4:
	.incbin "baserom.dol", 0x3C8174, 0x4
.global lbl_804BE4F8
lbl_804BE4F8:
	.incbin "baserom.dol", 0x3C8178, 0x4
.global lbl_804BE4FC
lbl_804BE4FC:
	.incbin "baserom.dol", 0x3C817C, 0x4
.global lbl_804BE500
lbl_804BE500:
	.incbin "baserom.dol", 0x3C8180, 0x4
.global lbl_804BE504
lbl_804BE504:
	.incbin "baserom.dol", 0x3C8184, 0x4
.global lbl_804BE508
lbl_804BE508:
	.incbin "baserom.dol", 0x3C8188, 0x4
.global lbl_804BE50C
lbl_804BE50C:
	.incbin "baserom.dol", 0x3C818C, 0x4
.global lbl_804BE510
lbl_804BE510:
	.incbin "baserom.dol", 0x3C8190, 0x8
.global lbl_804BE518
lbl_804BE518:
	.incbin "baserom.dol", 0x3C8198, 0x4
.global lbl_804BE51C
lbl_804BE51C:
	.incbin "baserom.dol", 0x3C819C, 0x4
.global lbl_804BE520
lbl_804BE520:
	.incbin "baserom.dol", 0x3C81A0, 0x4
.global lbl_804BE524
lbl_804BE524:
	.incbin "baserom.dol", 0x3C81A4, 0x4
.global lbl_804BE528
lbl_804BE528:
	.incbin "baserom.dol", 0x3C81A8, 0x4
.global lbl_804BE52C
lbl_804BE52C:
	.incbin "baserom.dol", 0x3C81AC, 0x4
.global lbl_804BE530
lbl_804BE530:
	.incbin "baserom.dol", 0x3C81B0, 0x4
.global lbl_804BE534
lbl_804BE534:
	.incbin "baserom.dol", 0x3C81B4, 0x4
.global lbl_804BE538
lbl_804BE538:
	.incbin "baserom.dol", 0x3C81B8, 0x8
.global lbl_804BE540
lbl_804BE540:
	.incbin "baserom.dol", 0x3C81C0, 0x4
.global lbl_804BE544
lbl_804BE544:
	.incbin "baserom.dol", 0x3C81C4, 0x4
.global lbl_804BE548
lbl_804BE548:
	.incbin "baserom.dol", 0x3C81C8, 0x4
.global lbl_804BE54C
lbl_804BE54C:
	.incbin "baserom.dol", 0x3C81CC, 0x4
.global lbl_804BE550
lbl_804BE550:
	.incbin "baserom.dol", 0x3C81D0, 0x4
.global lbl_804BE554
lbl_804BE554:
	.incbin "baserom.dol", 0x3C81D4, 0x4
.global lbl_804BE558
lbl_804BE558:
	.incbin "baserom.dol", 0x3C81D8, 0x8
.global lbl_804BE560
lbl_804BE560:
	.incbin "baserom.dol", 0x3C81E0, 0x4
.global lbl_804BE564
lbl_804BE564:
	.incbin "baserom.dol", 0x3C81E4, 0x4
.global lbl_804BE568
lbl_804BE568:
	.incbin "baserom.dol", 0x3C81E8, 0x8
.global lbl_804BE570
lbl_804BE570:
	.incbin "baserom.dol", 0x3C81F0, 0x4
.global lbl_804BE574
lbl_804BE574:
	.incbin "baserom.dol", 0x3C81F4, 0x4
.global lbl_804BE578
lbl_804BE578:
	.incbin "baserom.dol", 0x3C81F8, 0x4
.global lbl_804BE57C
lbl_804BE57C:
	.incbin "baserom.dol", 0x3C81FC, 0x4
.global lbl_804BE580
lbl_804BE580:
	.incbin "baserom.dol", 0x3C8200, 0x4
.global lbl_804BE584
lbl_804BE584:
	.incbin "baserom.dol", 0x3C8204, 0x4
.global lbl_804BE588
lbl_804BE588:
	.incbin "baserom.dol", 0x3C8208, 0x4
.global lbl_804BE58C
lbl_804BE58C:
	.incbin "baserom.dol", 0x3C820C, 0x4
.global lbl_804BE590
lbl_804BE590:
	.incbin "baserom.dol", 0x3C8210, 0x4
.global lbl_804BE594
lbl_804BE594:
	.incbin "baserom.dol", 0x3C8214, 0x4
.global lbl_804BE598
lbl_804BE598:
	.incbin "baserom.dol", 0x3C8218, 0x4
.global lbl_804BE59C
lbl_804BE59C:
	.incbin "baserom.dol", 0x3C821C, 0x4
.global lbl_804BE5A0
lbl_804BE5A0:
	.incbin "baserom.dol", 0x3C8220, 0x4
.global lbl_804BE5A4
lbl_804BE5A4:
	.incbin "baserom.dol", 0x3C8224, 0x4
.global lbl_804BE5A8
lbl_804BE5A8:
	.incbin "baserom.dol", 0x3C8228, 0x4
.global lbl_804BE5AC
lbl_804BE5AC:
	.incbin "baserom.dol", 0x3C822C, 0x4
.global lbl_804BE5B0
lbl_804BE5B0:
	.incbin "baserom.dol", 0x3C8230, 0x4
.global lbl_804BE5B4
lbl_804BE5B4:
	.incbin "baserom.dol", 0x3C8234, 0x4
.global lbl_804BE5B8
lbl_804BE5B8:
	.incbin "baserom.dol", 0x3C8238, 0x4
.global lbl_804BE5BC
lbl_804BE5BC:
	.incbin "baserom.dol", 0x3C823C, 0x4
.global lbl_804BE5C0
lbl_804BE5C0:
	.incbin "baserom.dol", 0x3C8240, 0x4
.global lbl_804BE5C4
lbl_804BE5C4:
	.incbin "baserom.dol", 0x3C8244, 0x4
.global lbl_804BE5C8
lbl_804BE5C8:
	.incbin "baserom.dol", 0x3C8248, 0x4
.global lbl_804BE5CC
lbl_804BE5CC:
	.incbin "baserom.dol", 0x3C824C, 0x4
.global lbl_804BE5D0
lbl_804BE5D0:
	.incbin "baserom.dol", 0x3C8250, 0x4
.global lbl_804BE5D4
lbl_804BE5D4:
	.incbin "baserom.dol", 0x3C8254, 0x4
.global lbl_804BE5D8
lbl_804BE5D8:
	.incbin "baserom.dol", 0x3C8258, 0x4
.global lbl_804BE5DC
lbl_804BE5DC:
	.incbin "baserom.dol", 0x3C825C, 0x4
.global lbl_804BE5E0
lbl_804BE5E0:
	.incbin "baserom.dol", 0x3C8260, 0x4
.global lbl_804BE5E4
lbl_804BE5E4:
	.incbin "baserom.dol", 0x3C8264, 0x4
.global lbl_804BE5E8
lbl_804BE5E8:
	.incbin "baserom.dol", 0x3C8268, 0x4
.global lbl_804BE5EC
lbl_804BE5EC:
	.incbin "baserom.dol", 0x3C826C, 0x4
.global lbl_804BE5F0
lbl_804BE5F0:
	.incbin "baserom.dol", 0x3C8270, 0x4
.global lbl_804BE5F4
lbl_804BE5F4:
	.incbin "baserom.dol", 0x3C8274, 0x4
.global lbl_804BE5F8
lbl_804BE5F8:
	.incbin "baserom.dol", 0x3C8278, 0x4
.global lbl_804BE5FC
lbl_804BE5FC:
	.incbin "baserom.dol", 0x3C827C, 0x4
.global lbl_804BE600
lbl_804BE600:
	.incbin "baserom.dol", 0x3C8280, 0x4
.global lbl_804BE604
lbl_804BE604:
	.incbin "baserom.dol", 0x3C8284, 0x4
.global lbl_804BE608
lbl_804BE608:
	.incbin "baserom.dol", 0x3C8288, 0x4
.global lbl_804BE60C
lbl_804BE60C:
	.incbin "baserom.dol", 0x3C828C, 0x4
.global lbl_804BE610
lbl_804BE610:
	.incbin "baserom.dol", 0x3C8290, 0x4
.global lbl_804BE614
lbl_804BE614:
	.incbin "baserom.dol", 0x3C8294, 0x4
.global lbl_804BE618
lbl_804BE618:
	.incbin "baserom.dol", 0x3C8298, 0x4
.global lbl_804BE61C
lbl_804BE61C:
	.incbin "baserom.dol", 0x3C829C, 0x4
.global lbl_804BE620
lbl_804BE620:
	.incbin "baserom.dol", 0x3C82A0, 0x4
.global lbl_804BE624
lbl_804BE624:
	.incbin "baserom.dol", 0x3C82A4, 0x4
.global lbl_804BE628
lbl_804BE628:
	.incbin "baserom.dol", 0x3C82A8, 0x4
.global lbl_804BE62C
lbl_804BE62C:
	.incbin "baserom.dol", 0x3C82AC, 0x4
.global lbl_804BE630
lbl_804BE630:
	.incbin "baserom.dol", 0x3C82B0, 0x4
.global lbl_804BE634
lbl_804BE634:
	.incbin "baserom.dol", 0x3C82B4, 0x4
.global lbl_804BE638
lbl_804BE638:
	.incbin "baserom.dol", 0x3C82B8, 0x4
.global lbl_804BE63C
lbl_804BE63C:
	.incbin "baserom.dol", 0x3C82BC, 0x4
.global lbl_804BE640
lbl_804BE640:
	.incbin "baserom.dol", 0x3C82C0, 0x4
.global lbl_804BE644
lbl_804BE644:
	.incbin "baserom.dol", 0x3C82C4, 0x4
.global lbl_804BE648
lbl_804BE648:
	.incbin "baserom.dol", 0x3C82C8, 0x4
.global lbl_804BE64C
lbl_804BE64C:
	.incbin "baserom.dol", 0x3C82CC, 0x4
.global lbl_804BE650
lbl_804BE650:
	.incbin "baserom.dol", 0x3C82D0, 0x4
.global lbl_804BE654
lbl_804BE654:
	.incbin "baserom.dol", 0x3C82D4, 0x4
.global lbl_804BE658
lbl_804BE658:
	.incbin "baserom.dol", 0x3C82D8, 0x4
.global lbl_804BE65C
lbl_804BE65C:
	.incbin "baserom.dol", 0x3C82DC, 0x4
.global lbl_804BE660
lbl_804BE660:
	.incbin "baserom.dol", 0x3C82E0, 0x4
.global lbl_804BE664
lbl_804BE664:
	.incbin "baserom.dol", 0x3C82E4, 0x4
.global lbl_804BE668
lbl_804BE668:
	.incbin "baserom.dol", 0x3C82E8, 0x8
.global lbl_804BE670
lbl_804BE670:
	.incbin "baserom.dol", 0x3C82F0, 0x8
.global lbl_804BE678
lbl_804BE678:
	.incbin "baserom.dol", 0x3C82F8, 0x8
.global lbl_804BE680
lbl_804BE680:
	.incbin "baserom.dol", 0x3C8300, 0x4
.global lbl_804BE684
lbl_804BE684:
	.incbin "baserom.dol", 0x3C8304, 0x4
.global lbl_804BE688
lbl_804BE688:
	.incbin "baserom.dol", 0x3C8308, 0x4
.global lbl_804BE68C
lbl_804BE68C:
	.incbin "baserom.dol", 0x3C830C, 0x4
.global lbl_804BE690
lbl_804BE690:
	.incbin "baserom.dol", 0x3C8310, 0x4
.global lbl_804BE694
lbl_804BE694:
	.incbin "baserom.dol", 0x3C8314, 0x4
.global lbl_804BE698
lbl_804BE698:
	.incbin "baserom.dol", 0x3C8318, 0x4
.global lbl_804BE69C
lbl_804BE69C:
	.incbin "baserom.dol", 0x3C831C, 0x4
.global lbl_804BE6A0
lbl_804BE6A0:
	.incbin "baserom.dol", 0x3C8320, 0x4
.global lbl_804BE6A4
lbl_804BE6A4:
	.incbin "baserom.dol", 0x3C8324, 0x4
.global lbl_804BE6A8
lbl_804BE6A8:
	.incbin "baserom.dol", 0x3C8328, 0x4
.global lbl_804BE6AC
lbl_804BE6AC:
	.incbin "baserom.dol", 0x3C832C, 0x4
.global lbl_804BE6B0
lbl_804BE6B0:
	.incbin "baserom.dol", 0x3C8330, 0x4
.global lbl_804BE6B4
lbl_804BE6B4:
	.incbin "baserom.dol", 0x3C8334, 0x4
.global lbl_804BE6B8
lbl_804BE6B8:
	.incbin "baserom.dol", 0x3C8338, 0x4
.global lbl_804BE6BC
lbl_804BE6BC:
	.incbin "baserom.dol", 0x3C833C, 0x4
.global lbl_804BE6C0
lbl_804BE6C0:
	.incbin "baserom.dol", 0x3C8340, 0x4
.global lbl_804BE6C4
lbl_804BE6C4:
	.incbin "baserom.dol", 0x3C8344, 0x4
.global lbl_804BE6C8
lbl_804BE6C8:
	.incbin "baserom.dol", 0x3C8348, 0x4
.global lbl_804BE6CC
lbl_804BE6CC:
	.incbin "baserom.dol", 0x3C834C, 0x4
.global lbl_804BE6D0
lbl_804BE6D0:
	.incbin "baserom.dol", 0x3C8350, 0x4
.global lbl_804BE6D4
lbl_804BE6D4:
	.incbin "baserom.dol", 0x3C8354, 0x4
.global lbl_804BE6D8
lbl_804BE6D8:
	.incbin "baserom.dol", 0x3C8358, 0x4
.global lbl_804BE6DC
lbl_804BE6DC:
	.incbin "baserom.dol", 0x3C835C, 0x4
.global lbl_804BE6E0
lbl_804BE6E0:
	.incbin "baserom.dol", 0x3C8360, 0x4
.global lbl_804BE6E4
lbl_804BE6E4:
	.incbin "baserom.dol", 0x3C8364, 0x4
.global lbl_804BE6E8
lbl_804BE6E8:
	.incbin "baserom.dol", 0x3C8368, 0x4
.global lbl_804BE6EC
lbl_804BE6EC:
	.incbin "baserom.dol", 0x3C836C, 0x4
.global lbl_804BE6F0
lbl_804BE6F0:
	.incbin "baserom.dol", 0x3C8370, 0x4
.global lbl_804BE6F4
lbl_804BE6F4:
	.incbin "baserom.dol", 0x3C8374, 0x4
.global lbl_804BE6F8
lbl_804BE6F8:
	.incbin "baserom.dol", 0x3C8378, 0x4
.global lbl_804BE6FC
lbl_804BE6FC:
	.incbin "baserom.dol", 0x3C837C, 0x4
.global lbl_804BE700
lbl_804BE700:
	.incbin "baserom.dol", 0x3C8380, 0x4
.global lbl_804BE704
lbl_804BE704:
	.incbin "baserom.dol", 0x3C8384, 0x4
.global lbl_804BE708
lbl_804BE708:
	.incbin "baserom.dol", 0x3C8388, 0x4
.global lbl_804BE70C
lbl_804BE70C:
	.incbin "baserom.dol", 0x3C838C, 0x4
.global lbl_804BE710
lbl_804BE710:
	.incbin "baserom.dol", 0x3C8390, 0x4
.global lbl_804BE714
lbl_804BE714:
	.incbin "baserom.dol", 0x3C8394, 0x4
.global lbl_804BE718
lbl_804BE718:
	.incbin "baserom.dol", 0x3C8398, 0x4
.global lbl_804BE71C
lbl_804BE71C:
	.incbin "baserom.dol", 0x3C839C, 0x4
.global lbl_804BE720
lbl_804BE720:
	.incbin "baserom.dol", 0x3C83A0, 0x4
.global lbl_804BE724
lbl_804BE724:
	.incbin "baserom.dol", 0x3C83A4, 0x4
.global lbl_804BE728
lbl_804BE728:
	.incbin "baserom.dol", 0x3C83A8, 0x4
.global lbl_804BE72C
lbl_804BE72C:
	.incbin "baserom.dol", 0x3C83AC, 0x4
.global lbl_804BE730
lbl_804BE730:
	.incbin "baserom.dol", 0x3C83B0, 0x4
.global lbl_804BE734
lbl_804BE734:
	.incbin "baserom.dol", 0x3C83B4, 0x4
.global lbl_804BE738
lbl_804BE738:
	.incbin "baserom.dol", 0x3C83B8, 0x4
.global lbl_804BE73C
lbl_804BE73C:
	.incbin "baserom.dol", 0x3C83BC, 0x4
.global lbl_804BE740
lbl_804BE740:
	.incbin "baserom.dol", 0x3C83C0, 0x4
.global lbl_804BE744
lbl_804BE744:
	.incbin "baserom.dol", 0x3C83C4, 0x4
.global lbl_804BE748
lbl_804BE748:
	.incbin "baserom.dol", 0x3C83C8, 0x4
.global lbl_804BE74C
lbl_804BE74C:
	.incbin "baserom.dol", 0x3C83CC, 0x4
.global lbl_804BE750
lbl_804BE750:
	.incbin "baserom.dol", 0x3C83D0, 0x4
.global lbl_804BE754
lbl_804BE754:
	.incbin "baserom.dol", 0x3C83D4, 0x4
.global lbl_804BE758
lbl_804BE758:
	.incbin "baserom.dol", 0x3C83D8, 0x4
.global lbl_804BE75C
lbl_804BE75C:
	.incbin "baserom.dol", 0x3C83DC, 0x4
.global lbl_804BE760
lbl_804BE760:
	.incbin "baserom.dol", 0x3C83E0, 0x4
.global lbl_804BE764
lbl_804BE764:
	.incbin "baserom.dol", 0x3C83E4, 0x4
.global lbl_804BE768
lbl_804BE768:
	.incbin "baserom.dol", 0x3C83E8, 0x4
.global lbl_804BE76C
lbl_804BE76C:
	.incbin "baserom.dol", 0x3C83EC, 0x4
.global lbl_804BE770
lbl_804BE770:
	.incbin "baserom.dol", 0x3C83F0, 0x4
.global lbl_804BE774
lbl_804BE774:
	.incbin "baserom.dol", 0x3C83F4, 0x4
.global lbl_804BE778
lbl_804BE778:
	.incbin "baserom.dol", 0x3C83F8, 0x4
.global lbl_804BE77C
lbl_804BE77C:
	.incbin "baserom.dol", 0x3C83FC, 0x4
.global lbl_804BE780
lbl_804BE780:
	.incbin "baserom.dol", 0x3C8400, 0x4
.global lbl_804BE784
lbl_804BE784:
	.incbin "baserom.dol", 0x3C8404, 0x4
.global lbl_804BE788
lbl_804BE788:
	.incbin "baserom.dol", 0x3C8408, 0x4
.global lbl_804BE78C
lbl_804BE78C:
	.incbin "baserom.dol", 0x3C840C, 0x4
.global lbl_804BE790
lbl_804BE790:
	.incbin "baserom.dol", 0x3C8410, 0x4
.global lbl_804BE794
lbl_804BE794:
	.incbin "baserom.dol", 0x3C8414, 0x4
.global lbl_804BE798
lbl_804BE798:
	.incbin "baserom.dol", 0x3C8418, 0x8
.global lbl_804BE7A0
lbl_804BE7A0:
	.incbin "baserom.dol", 0x3C8420, 0x4
.global lbl_804BE7A4
lbl_804BE7A4:
	.incbin "baserom.dol", 0x3C8424, 0x4
.global lbl_804BE7A8
lbl_804BE7A8:
	.incbin "baserom.dol", 0x3C8428, 0x4
.global lbl_804BE7AC
lbl_804BE7AC:
	.incbin "baserom.dol", 0x3C842C, 0x4
.global lbl_804BE7B0
lbl_804BE7B0:
	.incbin "baserom.dol", 0x3C8430, 0x4
.global lbl_804BE7B4
lbl_804BE7B4:
	.incbin "baserom.dol", 0x3C8434, 0x4
.global lbl_804BE7B8
lbl_804BE7B8:
	.incbin "baserom.dol", 0x3C8438, 0x8
.global lbl_804BE7C0
lbl_804BE7C0:
	.incbin "baserom.dol", 0x3C8440, 0x4
.global lbl_804BE7C4
lbl_804BE7C4:
	.incbin "baserom.dol", 0x3C8444, 0x4
.global lbl_804BE7C8
lbl_804BE7C8:
	.incbin "baserom.dol", 0x3C8448, 0x4
.global lbl_804BE7CC
lbl_804BE7CC:
	.incbin "baserom.dol", 0x3C844C, 0x4
.global lbl_804BE7D0
lbl_804BE7D0:
	.incbin "baserom.dol", 0x3C8450, 0x4
.global lbl_804BE7D4
lbl_804BE7D4:
	.incbin "baserom.dol", 0x3C8454, 0x4
.global lbl_804BE7D8
lbl_804BE7D8:
	.incbin "baserom.dol", 0x3C8458, 0x4
.global lbl_804BE7DC
lbl_804BE7DC:
	.incbin "baserom.dol", 0x3C845C, 0x4
.global lbl_804BE7E0
lbl_804BE7E0:
	.incbin "baserom.dol", 0x3C8460, 0x4
.global lbl_804BE7E4
lbl_804BE7E4:
	.incbin "baserom.dol", 0x3C8464, 0x4
.global lbl_804BE7E8
lbl_804BE7E8:
	.incbin "baserom.dol", 0x3C8468, 0x4
.global lbl_804BE7EC
lbl_804BE7EC:
	.incbin "baserom.dol", 0x3C846C, 0x4
.global lbl_804BE7F0
lbl_804BE7F0:
	.incbin "baserom.dol", 0x3C8470, 0x4
.global lbl_804BE7F4
lbl_804BE7F4:
	.incbin "baserom.dol", 0x3C8474, 0x4
.global lbl_804BE7F8
lbl_804BE7F8:
	.incbin "baserom.dol", 0x3C8478, 0x8
.global lbl_804BE800
lbl_804BE800:
	.incbin "baserom.dol", 0x3C8480, 0x8
.global lbl_804BE808
lbl_804BE808:
	.incbin "baserom.dol", 0x3C8488, 0x4
.global lbl_804BE80C
lbl_804BE80C:
	.incbin "baserom.dol", 0x3C848C, 0x4
.global lbl_804BE810
lbl_804BE810:
	.incbin "baserom.dol", 0x3C8490, 0x8
.global lbl_804BE818
lbl_804BE818:
	.incbin "baserom.dol", 0x3C8498, 0x4
.global lbl_804BE81C
lbl_804BE81C:
	.incbin "baserom.dol", 0x3C849C, 0x4
.global lbl_804BE820
lbl_804BE820:
	.incbin "baserom.dol", 0x3C84A0, 0x4
.global lbl_804BE824
lbl_804BE824:
	.incbin "baserom.dol", 0x3C84A4, 0x4
.global lbl_804BE828
lbl_804BE828:
	.incbin "baserom.dol", 0x3C84A8, 0x8
.global lbl_804BE830
lbl_804BE830:
	.incbin "baserom.dol", 0x3C84B0, 0x4
.global lbl_804BE834
lbl_804BE834:
	.incbin "baserom.dol", 0x3C84B4, 0x4
.global lbl_804BE838
lbl_804BE838:
	.incbin "baserom.dol", 0x3C84B8, 0x4
.global lbl_804BE83C
lbl_804BE83C:
	.incbin "baserom.dol", 0x3C84BC, 0x4
.global lbl_804BE840
lbl_804BE840:
	.incbin "baserom.dol", 0x3C84C0, 0x8
.global lbl_804BE848
lbl_804BE848:
	.incbin "baserom.dol", 0x3C84C8, 0x4
.global lbl_804BE84C
lbl_804BE84C:
	.incbin "baserom.dol", 0x3C84CC, 0x4
.global lbl_804BE850
lbl_804BE850:
	.incbin "baserom.dol", 0x3C84D0, 0x8
.global lbl_804BE858
lbl_804BE858:
	.incbin "baserom.dol", 0x3C84D8, 0x4
.global lbl_804BE85C
lbl_804BE85C:
	.incbin "baserom.dol", 0x3C84DC, 0x4
.global lbl_804BE860
lbl_804BE860:
	.incbin "baserom.dol", 0x3C84E0, 0x4
.global lbl_804BE864
lbl_804BE864:
	.incbin "baserom.dol", 0x3C84E4, 0x4
.global lbl_804BE868
lbl_804BE868:
	.incbin "baserom.dol", 0x3C84E8, 0x8
.global lbl_804BE870
lbl_804BE870:
	.incbin "baserom.dol", 0x3C84F0, 0x8
.global lbl_804BE878
lbl_804BE878:
	.incbin "baserom.dol", 0x3C84F8, 0x8
.global lbl_804BE880
lbl_804BE880:
	.incbin "baserom.dol", 0x3C8500, 0x8
.global lbl_804BE888
lbl_804BE888:
	.incbin "baserom.dol", 0x3C8508, 0x4
.global lbl_804BE88C
lbl_804BE88C:
	.incbin "baserom.dol", 0x3C850C, 0x4
.global lbl_804BE890
lbl_804BE890:
	.incbin "baserom.dol", 0x3C8510, 0x4
.global lbl_804BE894
lbl_804BE894:
	.incbin "baserom.dol", 0x3C8514, 0x4
.global lbl_804BE898
lbl_804BE898:
	.incbin "baserom.dol", 0x3C8518, 0x8
.global lbl_804BE8A0
lbl_804BE8A0:
	.incbin "baserom.dol", 0x3C8520, 0x8
.global lbl_804BE8A8
lbl_804BE8A8:
	.incbin "baserom.dol", 0x3C8528, 0x4
.global lbl_804BE8AC
lbl_804BE8AC:
	.incbin "baserom.dol", 0x3C852C, 0x4
.global lbl_804BE8B0
lbl_804BE8B0:
	.incbin "baserom.dol", 0x3C8530, 0x8
.global lbl_804BE8B8
lbl_804BE8B8:
	.incbin "baserom.dol", 0x3C8538, 0x4
.global lbl_804BE8BC
lbl_804BE8BC:
	.incbin "baserom.dol", 0x3C853C, 0x4
.global lbl_804BE8C0
lbl_804BE8C0:
	.incbin "baserom.dol", 0x3C8540, 0x8
.global lbl_804BE8C8
lbl_804BE8C8:
	.incbin "baserom.dol", 0x3C8548, 0x4
.global lbl_804BE8CC
lbl_804BE8CC:
	.incbin "baserom.dol", 0x3C854C, 0x4
.global lbl_804BE8D0
lbl_804BE8D0:
	.incbin "baserom.dol", 0x3C8550, 0x8
.global lbl_804BE8D8
lbl_804BE8D8:
	.incbin "baserom.dol", 0x3C8558, 0x8
.global lbl_804BE8E0
lbl_804BE8E0:
	.incbin "baserom.dol", 0x3C8560, 0x8
.global lbl_804BE8E8
lbl_804BE8E8:
	.incbin "baserom.dol", 0x3C8568, 0x8
.global lbl_804BE8F0
lbl_804BE8F0:
	.incbin "baserom.dol", 0x3C8570, 0x8
.global lbl_804BE8F8
lbl_804BE8F8:
	.incbin "baserom.dol", 0x3C8578, 0x8
.global lbl_804BE900
lbl_804BE900:
	.incbin "baserom.dol", 0x3C8580, 0x8
.global lbl_804BE908
lbl_804BE908:
	.incbin "baserom.dol", 0x3C8588, 0x8
.global lbl_804BE910
lbl_804BE910:
	.incbin "baserom.dol", 0x3C8590, 0x8
.global lbl_804BE918
lbl_804BE918:
	.incbin "baserom.dol", 0x3C8598, 0x8
.global lbl_804BE920
lbl_804BE920:
	.incbin "baserom.dol", 0x3C85A0, 0x8
.global lbl_804BE928
lbl_804BE928:
	.incbin "baserom.dol", 0x3C85A8, 0x8
.global lbl_804BE930
lbl_804BE930:
	.incbin "baserom.dol", 0x3C85B0, 0x2
.global lbl_804BE932
lbl_804BE932:
	.incbin "baserom.dol", 0x3C85B2, 0x2
.global lbl_804BE934
lbl_804BE934:
	.incbin "baserom.dol", 0x3C85B4, 0x4
.global lbl_804BE938
lbl_804BE938:
	.incbin "baserom.dol", 0x3C85B8, 0x8
.global lbl_804BE940
lbl_804BE940:
	.incbin "baserom.dol", 0x3C85C0, 0x8
.global lbl_804BE948
lbl_804BE948:
	.incbin "baserom.dol", 0x3C85C8, 0x8
.global lbl_804BE950
lbl_804BE950:
	.incbin "baserom.dol", 0x3C85D0, 0x8
.global lbl_804BE958
lbl_804BE958:
	.incbin "baserom.dol", 0x3C85D8, 0x8
.global lbl_804BE960
lbl_804BE960:
	.incbin "baserom.dol", 0x3C85E0, 0x8
.global lbl_804BE968
lbl_804BE968:
	.incbin "baserom.dol", 0x3C85E8, 0x8
.global lbl_804BE970
lbl_804BE970:
	.incbin "baserom.dol", 0x3C85F0, 0x4
.global lbl_804BE974
lbl_804BE974:
	.incbin "baserom.dol", 0x3C85F4, 0x6C
