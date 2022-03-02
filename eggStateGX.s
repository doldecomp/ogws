Analyzing: C:\Users\schif\AppData\Local\Temp\eggStateGX.o
Header idenfication: 0x7f, ELF, 32 bit MSB v1
    type:           1, machine:         20
    version: 00000001, entry:     00000000, phoff:  00000000
    shoff:   00001560, flags:     80000000, ehsize:       52, phentsize:  0
    phnum:          0, shentsize:       40, shnum:        14, shstrndx:  12


==> .shstrtab
    [  1]	.text
    [  7]	.rodata
    [ 15]	.bss
    [ 20]	.sdata
    [ 27]	.sbss
    [ 33]	.sdata2
    [ 41]	.mwcats.text
    [ 54]	.rela.text
    [ 65]	.rela.mwcats.text
    [ 83]	.symtab
    [ 91]	.strtab
    [ 99]	.shstrtab
    [ 109]	.comment

==> .text [1]: Section Header
    type:    00000001, flags:  00000006
    address: 00000000, offset: 00000034, size: 000005ec
    link:    00000000, info:   00000000, alignment: 4, entry size: 0


==> .rodata [2]: Section Header
    type:    00000001, flags:  00000002
    address: 00000000, offset: 00000620, size: 00000011
    link:    00000000, info:   00000000, alignment: 8, entry size: 0


==> .bss [3]: Section Header
    type:    00000008, flags:  00000003
    address: 00000000, offset: 00000640, size: 00000010
    link:    00000000, info:   00000000, alignment: 32, entry size: 0


==> .sdata [4]: Section Header
    type:    00000001, flags:  00000003
    address: 00000000, offset: 00000640, size: 00000008
    link:    00000000, info:   00000000, alignment: 8, entry size: 0


==> .sbss [5]: Section Header
    type:    00000008, flags:  00000003
    address: 00000000, offset: 00000648, size: 00000004
    link:    00000000, info:   00000000, alignment: 8, entry size: 0


==> .sdata2 [6]: Section Header
    type:    00000001, flags:  00000003
    address: 00000000, offset: 00000648, size: 00000004
    link:    00000000, info:   00000000, alignment: 8, entry size: 0


==> .mwcats.text [7]: Section Header
    type:    ca2a82c2, flags:  00000000
    address: 00000000, offset: 0000064c, size: 00000098
    link:    00000001, info:   00000000, alignment: 4, entry size: 1


==> .rela.text [8]: Section Header
    type:    00000004, flags:  00000000
    address: 00000000, offset: 000006e4, size: 000002dc
    link:    0000000a, info:   00000001, alignment: 4, entry size: 12


==> .rela.mwcats.text [9]: Section Header
    type:    00000004, flags:  00000000
    address: 00000000, offset: 000009c0, size: 000000e4
    link:    0000000a, info:   00000007, alignment: 4, entry size: 12


==> .symtab [10]: Section Header
    type:    00000002, flags:  00000000
    address: 00000000, offset: 00000aa4, size: 000003b0
    link:    0000000b, info:   00000016, alignment: 4, entry size: 16


==> .strtab [11]: Section Header
    type:    00000003, flags:  00000000
    address: 00000000, offset: 00000e54, size: 0000048d
    link:    00000000, info:   00000000, alignment: 1, entry size: 1


==> .shstrtab [12]: Section Header
    type:    00000003, flags:  00000000
    address: 00000000, offset: 000012e1, size: 00000076
    link:    00000000, info:   00000000, alignment: 1, entry size: 1


==> .comment [13]: Section Header
    type:    00000001, flags:  00000000
    address: 00000000, offset: 00001357, size: 00000204
    link:    00000000, info:   00000000, alignment: 1, entry size: 1


==> .strtab
    [  1]	eggStateGX.cpp
    [ 16]	OSInitFastCast
    [ 31]	OSSetGQR6
    [ 41]	OSSetGQR7
    [ 51]	__OSu16tof32
    [ 64]	OSu16tof32
    [ 75]	__OSf32tou16
    [ 88]	OSf32tou16
    [ 99]	__OSs16tof32
    [ 112]	OSs16tof32
    [ 123]	__OSf32tos16
    [ 136]	OSf32tos16
    [ 147]	GXEnd
    [ 153]	@stringBase0
    [ 166]	InitFastCast__Q24nw4r3g3dFv
    [ 194]	func_80083E18__Q23EGG7StateGXFv
    [ 226]	sStateFlags1__Q23EGG7StateGX
    [ 255]	GXInvalidateTexAll
    [ 274]	func_80083E5C__Q23EGG7StateGXFv
    [ 306]	func_80083EBC__Q23EGG7StateGXFv
    [ 338]	sTMemLayout__Q23EGG7StateGX
    [ 366]	SetTMemLayout__Q34nw4r3g3d4tmemFQ44nw4r3g3d4tmem10TMemLayout
    [ 427]	func_80084548__Q23EGG7StateGXFv
    [ 459]	func_80083EC0__Q23EGG7StateGXFv
    [ 491]	func_80083EF8__Q23EGG7StateGXFv
    [ 523]	func_80084110__Q23EGG7StateGXFv
    [ 555]	func_80084034__Q23EGG7StateGXFv
    [ 587]	func_80084188__Q23EGG7StateGXFv
    [ 619]	func_8008422C__Q23EGG7StateGXFv
    [ 651]	func_800842E0__Q23EGG7StateGXFv
    [ 683]	func_80084490__Q23EGG7StateGXFv
    [ 715]	GXSetVtxAttrFmt
    [ 731]	GXSetNumChans
    [ 745]	cAmbColorWhite__Q23EGG7StateGX
    [ 776]	GXSetChanAmbColor
    [ 794]	GXSetChanMatColor
    [ 812]	GXSetCullMode
    [ 826]	GXSetChanCtrl
    [ 840]	GXSetNumIndStages
    [ 858]	GXSetIndTexCoordScale
    [ 880]	sTexObjImage__Q23EGG7StateGX
    [ 909]	GXInitTexObj
    [ 922]	GXLoadTexObj
    [ 935]	sStateFlags2__Q23EGG7StateGX
    [ 964]	GXSetColorUpdate__Q23EGG7StateGXFb
    [ 999]	GXSetAlphaUpdate__Q23EGG7StateGXFb
    [ 1034]	GXSetDither__Q23EGG7StateGXFb
    [ 1064]	GXSetProjection__Q23EGG7StateGXFPA4_fi
    [ 1103]	func_800846A8
    [ 1120]	system_halt
    [ 1132]	sDefaultTexColor__Q23EGG7StateGX

==> .symtab
    entry  spndx   value      size   bind   type  other    shndx         name
    [   0]     0   00000000      0   LOC    NULL      0    UND           
    [   1]     1   00000000      0   LOC    FILE      0    ABS           eggStateGX.cpp
    [   2]     0   00000000      0   LOC    SECT      0    .text         .text
    [   3]     0   00000000      0   LOC    SECT      0    .rodata       .rodata
    [   4]     0   00000000      0   LOC    SECT      0    .bss          .bss
    [   5]     0   00000000      0   LOC    SECT      0    .sdata        .sdata
    [   6]     0   00000000      0   LOC    SECT      0    .sbss         .sbss
    [   7]     0   00000000      0   LOC    SECT      0    .sdata2       .sdata2
    [   8]     0   00000000      0   LOC    SECT      0    .mwcats.text  .mwcats.text
    [   9]    16   00000000     52   LOC    FUNC      0    .text         OSInitFastCast
    [  10]    31   00000034     24   LOC    FUNC      0    .text         OSSetGQR6
    [  11]    41   0000004c     24   LOC    FUNC      0    .text         OSSetGQR7
    [  12]    51   00000064      8   LOC    FUNC      0    .text         __OSu16tof32
    [  13]    64   0000006c     12   LOC    FUNC      0    .text         OSu16tof32
    [  14]    75   00000078     20   LOC    FUNC      0    .text         __OSf32tou16
    [  15]    88   0000008c     28   LOC    FUNC      0    .text         OSf32tou16
    [  16]    99   000000a8      8   LOC    FUNC      0    .text         __OSs16tof32
    [  17]   112   000000b0     12   LOC    FUNC      0    .text         OSs16tof32
    [  18]   123   000000bc     20   LOC    FUNC      0    .text         __OSf32tos16
    [  19]   136   000000d0     28   LOC    FUNC      0    .text         OSf32tos16
    [  20]   147   00000138      4   LOC    FUNC      0    .text         GXEnd
    [  21]   153   00000000     17   LOC    OBJ       0    .rodata       @stringBase0
    [  22]   166   000000ec     76   GLOB   FUNC      0    .text         InitFastCast__Q24nw4r3g3dFv
    [  23]   194   0000013c     68   GLOB   FUNC      0    .text         func_80083E18__Q23EGG7StateGXFv
    [  24]   226   00000000      2   GLOB   OBJ       0    .sdata        sStateFlags1__Q23EGG7StateGX
    [  25]   255   00000000      0   GLOB   NULL      0    UND           GXInvalidateTexAll
    [  26]   274   00000180      4   GLOB   FUNC      0    .text         func_80083E5C__Q23EGG7StateGXFv
    [  27]   306   00000184      4   GLOB   FUNC      0    .text         func_80083EBC__Q23EGG7StateGXFv
    [  28]   338   00000004      4   GLOB   OBJ       0    .sdata        sTMemLayout__Q23EGG7StateGX
    [  29]   366   00000000      0   GLOB   NULL      0    UND           SetTMemLayout__Q34nw4r3g3d4tmemFQ44nw4r3g3d4tmem10TMemLayout
    [  30]   427   000004d4     60   GLOB   FUNC      0    .text         func_80084548__Q23EGG7StateGXFv
    [  31]   459   00000188     56   GLOB   FUNC      0    .text         func_80083EC0__Q23EGG7StateGXFv
    [  32]   491   000001c0    316   GLOB   FUNC      0    .text         func_80083EF8__Q23EGG7StateGXFv
    [  33]   523   000003d8     76   GLOB   FUNC      0    .text         func_80084110__Q23EGG7StateGXFv
    [  34]   555   000002fc    220   GLOB   FUNC      0    .text         func_80084034__Q23EGG7StateGXFv
    [  35]   587   00000424    164   GLOB   FUNC      0    .text         func_80084188__Q23EGG7StateGXFv
    [  36]   619   000004c8      4   GLOB   FUNC      0    .text         func_8008422C__Q23EGG7StateGXFv
    [  37]   651   000004cc      4   GLOB   FUNC      0    .text         func_800842E0__Q23EGG7StateGXFv
    [  38]   683   000004d0      4   GLOB   FUNC      0    .text         func_80084490__Q23EGG7StateGXFv
    [  39]   715   00000000      0   GLOB   NULL      0    UND           GXSetVtxAttrFmt
    [  40]   731   00000000      0   GLOB   NULL      0    UND           GXSetNumChans
    [  41]   745   00000000      4   GLOB   OBJ       0    .sdata2       cAmbColorWhite__Q23EGG7StateGX
    [  42]   776   00000000      0   GLOB   NULL      0    UND           GXSetChanAmbColor
    [  43]   794   00000000      0   GLOB   NULL      0    UND           GXSetChanMatColor
    [  44]   812   00000000      0   GLOB   NULL      0    UND           GXSetCullMode
    [  45]   826   00000000      0   GLOB   NULL      0    UND           GXSetChanCtrl
    [  46]   840   00000000      0   GLOB   NULL      0    UND           GXSetNumIndStages
    [  47]   858   00000000      0   GLOB   NULL      0    UND           GXSetIndTexCoordScale
    [  48]   880   00000000     16   GLOB   OBJ       0    .bss          sTexObjImage__Q23EGG7StateGX
    [  49]   909   00000000      0   GLOB   NULL      0    UND           GXInitTexObj
    [  50]   922   00000000      0   GLOB   NULL      0    UND           GXLoadTexObj
    [  51]   935   00000000      0   GLOB   NULL      0    UND           sStateFlags2__Q23EGG7StateGX
    [  52]   964   00000000      0   GLOB   NULL      0    UND           GXSetColorUpdate__Q23EGG7StateGXFb
    [  53]   999   00000000      0   GLOB   NULL      0    UND           GXSetAlphaUpdate__Q23EGG7StateGXFb
    [  54]   1034   00000000      0   GLOB   NULL      0    UND           GXSetDither__Q23EGG7StateGXFb
    [  55]   1064   00000510    220   GLOB   FUNC      0    .text         GXSetProjection__Q23EGG7StateGXFPA4_fi
    [  56]   1103   00000000      0   GLOB   NULL      0    UND           func_800846A8
    [  57]   1120   00000000      0   GLOB   NULL      0    UND           system_halt
    [  58]   1132   00000000      4   GLOB   OBJ       0    .sbss         sDefaultTexColor__Q23EGG7StateGX

==> .rela.text
    entry  offset   addend   type name(symbol id)
    [   0] 00000148 00000000  109 sStateFlags1__Q23EGG7StateGX(24)
    [   1] 00000150 00000000  109 sStateFlags1__Q23EGG7StateGX(24)
    [   2] 00000154 00000000   10 GXInvalidateTexAll(25)
    [   3] 00000158 00000000   10 func_80083E5C__Q23EGG7StateGXFv(26)
    [   4] 0000015c 00000000   10 func_80083EBC__Q23EGG7StateGXFv(27)
    [   5] 00000168 00000000  109 sTMemLayout__Q23EGG7StateGX(28)
    [   6] 0000016c 00000000   10 SetTMemLayout__Q34nw4r3g3d4tmemFQ44nw4r3g3d4tmem10TMemLayout(29)
    [   7] 00000184 00000000   10 func_80084548__Q23EGG7StateGXFv(30)
    [   8] 00000194 00000000   10 func_80083EF8__Q23EGG7StateGXFv(32)
    [   9] 00000198 00000000   10 func_80084110__Q23EGG7StateGXFv(33)
    [  10] 0000019c 00000000   10 func_80084034__Q23EGG7StateGXFv(34)
    [  11] 000001a0 00000000   10 func_80084188__Q23EGG7StateGXFv(35)
    [  12] 000001a4 00000000   10 func_8008422C__Q23EGG7StateGXFv(36)
    [  13] 000001a8 00000000   10 func_800842E0__Q23EGG7StateGXFv(37)
    [  14] 000001ac 00000000   10 func_80084490__Q23EGG7StateGXFv(38)
    [  15] 000001e0 00000000   10 GXSetVtxAttrFmt(39)
    [  16] 000001f8 00000000   10 GXSetVtxAttrFmt(39)
    [  17] 00000210 00000000   10 GXSetVtxAttrFmt(39)
    [  18] 00000228 00000000   10 GXSetVtxAttrFmt(39)
    [  19] 00000240 00000000   10 GXSetVtxAttrFmt(39)
    [  20] 00000258 00000000   10 GXSetVtxAttrFmt(39)
    [  21] 00000270 00000000   10 GXSetVtxAttrFmt(39)
    [  22] 00000288 00000000   10 GXSetVtxAttrFmt(39)
    [  23] 000002a0 00000000   10 GXSetVtxAttrFmt(39)
    [  24] 000002b8 00000000   10 GXSetVtxAttrFmt(39)
    [  25] 000002d0 00000000   10 GXSetVtxAttrFmt(39)
    [  26] 000002e8 00000000   10 GXSetVtxAttrFmt(39)
    [  27] 0000030c 00000000   10 GXSetNumChans(40)
    [  28] 00000310 00000000  109 cAmbColorWhite__Q23EGG7StateGX(41)
    [  29] 00000318 00000001  109 cAmbColorWhite__Q23EGG7StateGX(41)
    [  30] 00000320 00000002  109 cAmbColorWhite__Q23EGG7StateGX(41)
    [  31] 00000324 00000003  109 cAmbColorWhite__Q23EGG7StateGX(41)
    [  32] 00000340 00000000   10 GXSetChanAmbColor(42)
    [  33] 00000354 00000000   10 GXSetChanAmbColor(42)
    [  34] 00000368 00000000   10 GXSetChanMatColor(43)
    [  35] 0000037c 00000000   10 GXSetChanMatColor(43)
    [  36] 00000384 00000000   10 GXSetCullMode(44)
    [  37] 000003a4 00000000   10 GXSetChanCtrl(45)
    [  38] 000003c4 00000000   10 GXSetChanCtrl(45)
    [  39] 000003ec 00000000   10 GXSetNumIndStages(46)
    [  40] 00000400 00000000   10 GXSetIndTexCoordScale(47)
    [  41] 0000042e 00000000    6 sTexObjImage__Q23EGG7StateGX(48)
    [  42] 0000043e 00000000    4 sTexObjImage__Q23EGG7StateGX(48)
    [  43] 00000454 00000000   10 GXInitTexObj(49)
    [  44] 00000460 00000000   10 GXLoadTexObj(50)
    [  45] 0000046c 00000000   10 GXLoadTexObj(50)
    [  46] 00000478 00000000   10 GXLoadTexObj(50)
    [  47] 00000484 00000000   10 GXLoadTexObj(50)
    [  48] 00000490 00000000   10 GXLoadTexObj(50)
    [  49] 0000049c 00000000   10 GXLoadTexObj(50)
    [  50] 000004a8 00000000   10 GXLoadTexObj(50)
    [  51] 000004b4 00000000   10 GXLoadTexObj(50)
    [  52] 000004e8 00000000  109 sStateFlags2__Q23EGG7StateGX(51)
    [  53] 000004ec 00000000   10 GXSetColorUpdate__Q23EGG7StateGXFb(52)
    [  54] 000004f4 00000000   10 GXSetAlphaUpdate__Q23EGG7StateGXFb(53)
    [  55] 000004fc 00000000   10 GXSetDither__Q23EGG7StateGXFb(54)
    [  56] 000005b8 00000000   10 func_800846A8(56)
    [  57] 000005c0 00000000   10 func_800846A8(56)
    [  58] 000005c6 00000000    6 @stringBase0(21)
    [  59] 000005ce 00000000    4 @stringBase0(21)
    [  60] 000005d8 00000000   10 system_halt(57)

==> .text

Hunk:	Kind=HUNK_LOCAL_CODE     Name="OSInitFastCast"  Size=52
00000000: 38600004  li       r3,4
00000004: 64630004  oris     r3,r3,0x0004
00000008: 7C72E3A6  mtspr    spr914,r3
0000000C: 38600005  li       r3,5
00000010: 64630005  oris     r3,r3,0x0005
00000014: 7C73E3A6  mtspr    spr915,r3
00000018: 38600006  li       r3,6
0000001C: 64630006  oris     r3,r3,0x0006
00000020: 7C74E3A6  mtspr    spr916,r3
00000024: 38600007  li       r3,7
00000028: 64630007  oris     r3,r3,0x0007
0000002C: 7C75E3A6  mtspr    spr917,r3
00000030: 4E800020  blr

Hunk:	Kind=HUNK_LOCAL_CODE     Name="OSSetGQR6"  Size=24
00000034: 5480402E  slwi     r0,r4,8                 ; rlwinm     r0,r4,8,0,23
00000038: 7C031B78  or       r3,r0,r3
0000003C: 5460801E  slwi     r0,r3,16                ; rlwinm     r0,r3,16,0,15
00000040: 7C600378  or       r0,r3,r0
00000044: 7C16E3A6  mtspr    spr918,r0
00000048: 4E800020  blr

Hunk:	Kind=HUNK_LOCAL_CODE     Name="OSSetGQR7"  Size=24
0000004C: 5480402E  slwi     r0,r4,8                 ; rlwinm     r0,r4,8,0,23
00000050: 7C031B78  or       r3,r0,r3
00000054: 5460801E  slwi     r0,r3,16                ; rlwinm     r0,r3,16,0,15
00000058: 7C600378  or       r0,r3,r0
0000005C: 7C17E3A6  mtspr    spr919,r0
00000060: 4E800020  blr

Hunk:	Kind=HUNK_LOCAL_CODE     Name="__OSu16tof32"  Size=8
00000064: E023B000  psq_l    fp1,0(r3),1,gqr3
00000068: 4E800020  blr

Hunk:	Kind=HUNK_LOCAL_CODE     Name="OSu16tof32"  Size=12
0000006C: E003B000  psq_l    fp0,0(r3),1,gqr3
00000070: D0040000  stfs     fp0,0(r4)
00000074: 4E800020  blr

Hunk:	Kind=HUNK_LOCAL_CODE     Name="__OSf32tou16"  Size=20
00000078: 9421FFF0  stwu     rsp,-16(rsp)
0000007C: F021B008  psq_st   fp1,8(rsp),1,gqr3
00000080: A0610008  lhz      r3,8(rsp)
00000084: 38210010  addi     rsp,rsp,16
00000088: 4E800020  blr

Hunk:	Kind=HUNK_LOCAL_CODE     Name="OSf32tou16"  Size=28
0000008C: 9421FFF0  stwu     rsp,-16(rsp)
00000090: C0030000  lfs      fp0,0(r3)
00000094: F001B008  psq_st   fp0,8(rsp),1,gqr3
00000098: A0010008  lhz      r0,8(rsp)
0000009C: B0040000  sth      r0,0(r4)
000000A0: 38210010  addi     rsp,rsp,16
000000A4: 4E800020  blr

Hunk:	Kind=HUNK_LOCAL_CODE     Name="__OSs16tof32"  Size=8
000000A8: E023B000  psq_l    fp1,0(r3),1,gqr3
000000AC: 4E800020  blr

Hunk:	Kind=HUNK_LOCAL_CODE     Name="OSs16tof32"  Size=12
000000B0: E003B000  psq_l    fp0,0(r3),1,gqr3
000000B4: D0040000  stfs     fp0,0(r4)
000000B8: 4E800020  blr

Hunk:	Kind=HUNK_LOCAL_CODE     Name="__OSf32tos16"  Size=20
000000BC: 9421FFF0  stwu     rsp,-16(rsp)
000000C0: F021D008  psq_st   fp1,8(rsp),1,gqr5
000000C4: A8610008  lha      r3,8(rsp)
000000C8: 38210010  addi     rsp,rsp,16
000000CC: 4E800020  blr

Hunk:	Kind=HUNK_LOCAL_CODE     Name="OSf32tos16"  Size=28
000000D0: 9421FFF0  stwu     rsp,-16(rsp)
000000D4: C0030000  lfs      fp0,0(r3)
000000D8: F001D008  psq_st   fp0,8(rsp),1,gqr5
000000DC: A8010008  lha      r0,8(rsp)
000000E0: B0040000  sth      r0,0(r4)
000000E4: 38210010  addi     rsp,rsp,16
000000E8: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="InitFastCast__Q24nw4r3g3dFv"  Size=76
000000EC: 38600004  li       r3,4
000000F0: 64630004  oris     r3,r3,0x0004
000000F4: 7C72E3A6  mtspr    spr914,r3
000000F8: 38600005  li       r3,5
000000FC: 64630005  oris     r3,r3,0x0005
00000100: 7C73E3A6  mtspr    spr915,r3
00000104: 38600006  li       r3,6
00000108: 64630006  oris     r3,r3,0x0006
0000010C: 7C74E3A6  mtspr    spr916,r3
00000110: 38600007  li       r3,7
00000114: 64630007  oris     r3,r3,0x0007
00000118: 7C75E3A6  mtspr    spr917,r3
0000011C: 3C800507  lis      r4,1287
00000120: 38040507  addi     r0,r4,1287
00000124: 7C16E3A6  mtspr    spr918,r0
00000128: 3C800807  lis      r4,2055
0000012C: 38040807  addi     r0,r4,2055
00000130: 7C17E3A6  mtspr    spr919,r0
00000134: 4E800020  blr

Hunk:	Kind=HUNK_LOCAL_CODE     Name="GXEnd"  Size=4
00000138: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="func_80083E18__Q23EGG7StateGXFv"  Size=68
0000013C: 9421FFF0  stwu     rsp,-16(rsp)
00000140: 7C0802A6  mflr     r0
00000144: 90010014  stw      r0,20(rsp)
00000148: A0000000  lhz      r0,sStateFlags1__Q23EGG7StateGX@sda21
0000014C: 540006F2  rlwinm   r0,r0,0,27,25
00000150: B0000000  sth      r0,sStateFlags1__Q23EGG7StateGX@sda21
00000154: 48000001  bl       GXInvalidateTexAll
00000158: 48000001  bl       func_80083E5C__Q23EGG7StateGXFv
0000015C: 48000001  bl       func_80083EBC__Q23EGG7StateGXFv
00000160: 38000001  li       r0,1
00000164: 38600001  li       r3,1
00000168: 90000000  stw      r0,sTMemLayout__Q23EGG7StateGX@sda21
0000016C: 48000001  bl       SetTMemLayout__Q34nw4r3g3d4tmemFQ44nw4r3g3d4tmem10TMemLayout
00000170: 80010014  lwz      r0,20(rsp)
00000174: 7C0803A6  mtlr     r0
00000178: 38210010  addi     rsp,rsp,16
0000017C: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="func_80083E5C__Q23EGG7StateGXFv"  Size=4
00000180: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="func_80083EBC__Q23EGG7StateGXFv"  Size=4
00000184: 48000000  b        func_80084548__Q23EGG7StateGXFv

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="func_80083EC0__Q23EGG7StateGXFv"  Size=56
00000188: 9421FFF0  stwu     rsp,-16(rsp)
0000018C: 7C0802A6  mflr     r0
00000190: 90010014  stw      r0,20(rsp)
00000194: 48000001  bl       func_80083EF8__Q23EGG7StateGXFv
00000198: 48000001  bl       func_80084110__Q23EGG7StateGXFv
0000019C: 48000001  bl       func_80084034__Q23EGG7StateGXFv
000001A0: 48000001  bl       func_80084188__Q23EGG7StateGXFv
000001A4: 48000001  bl       func_8008422C__Q23EGG7StateGXFv
000001A8: 48000001  bl       func_800842E0__Q23EGG7StateGXFv
000001AC: 48000001  bl       func_80084490__Q23EGG7StateGXFv
000001B0: 80010014  lwz      r0,20(rsp)
000001B4: 7C0803A6  mtlr     r0
000001B8: 38210010  addi     rsp,rsp,16
000001BC: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="func_80083EF8__Q23EGG7StateGXFv"  Size=316
000001C0: 9421FFF0  stwu     rsp,-16(rsp)
000001C4: 7C0802A6  mflr     r0
000001C8: 38600000  li       r3,0
000001CC: 38800009  li       r4,9
000001D0: 90010014  stw      r0,20(rsp)
000001D4: 38A00001  li       r5,1
000001D8: 38C00004  li       r6,4
000001DC: 38E00000  li       r7,0
000001E0: 48000001  bl       GXSetVtxAttrFmt
000001E4: 38600000  li       r3,0
000001E8: 3880000A  li       r4,10
000001EC: 38A00000  li       r5,0
000001F0: 38C00004  li       r6,4
000001F4: 38E00000  li       r7,0
000001F8: 48000001  bl       GXSetVtxAttrFmt
000001FC: 38600000  li       r3,0
00000200: 3880000B  li       r4,11
00000204: 38A00001  li       r5,1
00000208: 38C00005  li       r6,5
0000020C: 38E00000  li       r7,0
00000210: 48000001  bl       GXSetVtxAttrFmt
00000214: 38600000  li       r3,0
00000218: 3880000C  li       r4,12
0000021C: 38A00001  li       r5,1
00000220: 38C00005  li       r6,5
00000224: 38E00000  li       r7,0
00000228: 48000001  bl       GXSetVtxAttrFmt
0000022C: 38600000  li       r3,0
00000230: 3880000D  li       r4,13
00000234: 38A00001  li       r5,1
00000238: 38C00003  li       r6,3
0000023C: 38E00007  li       r7,7
00000240: 48000001  bl       GXSetVtxAttrFmt
00000244: 38600000  li       r3,0
00000248: 3880000E  li       r4,14
0000024C: 38A00001  li       r5,1
00000250: 38C00003  li       r6,3
00000254: 38E00007  li       r7,7
00000258: 48000001  bl       GXSetVtxAttrFmt
0000025C: 38600000  li       r3,0
00000260: 3880000F  li       r4,15
00000264: 38A00001  li       r5,1
00000268: 38C00003  li       r6,3
0000026C: 38E00007  li       r7,7
00000270: 48000001  bl       GXSetVtxAttrFmt
00000274: 38600000  li       r3,0
00000278: 38800010  li       r4,16
0000027C: 38A00001  li       r5,1
00000280: 38C00003  li       r6,3
00000284: 38E00007  li       r7,7
00000288: 48000001  bl       GXSetVtxAttrFmt
0000028C: 38600000  li       r3,0
00000290: 38800011  li       r4,17
00000294: 38A00001  li       r5,1
00000298: 38C00003  li       r6,3
0000029C: 38E00007  li       r7,7
000002A0: 48000001  bl       GXSetVtxAttrFmt
000002A4: 38600000  li       r3,0
000002A8: 38800012  li       r4,18
000002AC: 38A00001  li       r5,1
000002B0: 38C00003  li       r6,3
000002B4: 38E00007  li       r7,7
000002B8: 48000001  bl       GXSetVtxAttrFmt
000002BC: 38600000  li       r3,0
000002C0: 38800013  li       r4,19
000002C4: 38A00001  li       r5,1
000002C8: 38C00003  li       r6,3
000002CC: 38E00007  li       r7,7
000002D0: 48000001  bl       GXSetVtxAttrFmt
000002D4: 38600000  li       r3,0
000002D8: 38800014  li       r4,20
000002DC: 38A00001  li       r5,1
000002E0: 38C00003  li       r6,3
000002E4: 38E00007  li       r7,7
000002E8: 48000001  bl       GXSetVtxAttrFmt
000002EC: 80010014  lwz      r0,20(rsp)
000002F0: 7C0803A6  mtlr     r0
000002F4: 38210010  addi     rsp,rsp,16
000002F8: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="func_80084034__Q23EGG7StateGXFv"  Size=220
000002FC: 9421FFE0  stwu     rsp,-32(rsp)
00000300: 7C0802A6  mflr     r0
00000304: 38600001  li       r3,1
00000308: 90010024  stw      r0,36(rsp)
0000030C: 48000001  bl       GXSetNumChans
00000310: 88E00000  lbz      r7,cAmbColorWhite__Q23EGG7StateGX@sda21
00000314: 38810018  addi     r4,rsp,24
00000318: 88C00000  lbz      r6,cAmbColorWhite__Q23EGG7StateGX+1@sda21
0000031C: 38600004  li       r3,4
00000320: 88A00000  lbz      r5,cAmbColorWhite__Q23EGG7StateGX+2@sda21
00000324: 88000000  lbz      r0,cAmbColorWhite__Q23EGG7StateGX+3@sda21
00000328: 98E10008  stb      r7,8(rsp)
0000032C: 98C10009  stb      r6,9(rsp)
00000330: 98A1000A  stb      r5,10(rsp)
00000334: 9801000B  stb      r0,11(rsp)
00000338: 80010008  lwz      r0,8(rsp)
0000033C: 90010018  stw      r0,24(rsp)
00000340: 48000001  bl       GXSetChanAmbColor
00000344: 80010008  lwz      r0,8(rsp)
00000348: 38810014  addi     r4,rsp,20
0000034C: 38600005  li       r3,5
00000350: 90010014  stw      r0,20(rsp)
00000354: 48000001  bl       GXSetChanAmbColor
00000358: 80010008  lwz      r0,8(rsp)
0000035C: 38810010  addi     r4,rsp,16
00000360: 38600004  li       r3,4
00000364: 90010010  stw      r0,16(rsp)
00000368: 48000001  bl       GXSetChanMatColor
0000036C: 80010008  lwz      r0,8(rsp)
00000370: 3881000C  addi     r4,rsp,12
00000374: 38600005  li       r3,5
00000378: 9001000C  stw      r0,12(rsp)
0000037C: 48000001  bl       GXSetChanMatColor
00000380: 38600002  li       r3,2
00000384: 48000001  bl       GXSetCullMode
00000388: 38600004  li       r3,4
0000038C: 38800000  li       r4,0
00000390: 38A00000  li       r5,0
00000394: 38C00000  li       r6,0
00000398: 38E00000  li       r7,0
0000039C: 39000002  li       r8,2
000003A0: 39200002  li       r9,2
000003A4: 48000001  bl       GXSetChanCtrl
000003A8: 38600005  li       r3,5
000003AC: 38800000  li       r4,0
000003B0: 38A00000  li       r5,0
000003B4: 38C00000  li       r6,0
000003B8: 38E00000  li       r7,0
000003BC: 39000002  li       r8,2
000003C0: 39200002  li       r9,2
000003C4: 48000001  bl       GXSetChanCtrl
000003C8: 80010024  lwz      r0,36(rsp)
000003CC: 7C0803A6  mtlr     r0
000003D0: 38210020  addi     rsp,rsp,32
000003D4: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="func_80084110__Q23EGG7StateGXFv"  Size=76
000003D8: 9421FFF0  stwu     rsp,-16(rsp)
000003DC: 7C0802A6  mflr     r0
000003E0: 38600000  li       r3,0
000003E4: 90010014  stw      r0,20(rsp)
000003E8: 93E1000C  stw      r31,12(rsp)
000003EC: 48000001  bl       GXSetNumIndStages
000003F0: 3BE00000  li       r31,0
000003F4: 38600000  li       r3,0
000003F8: 38800000  li       r4,0
000003FC: 38A00000  li       r5,0
00000400: 48000001  bl       GXSetIndTexCoordScale
00000404: 3BFF0001  addi     r31,r31,1
00000408: 2C1F0003  cmpwi    r31,0x0003
0000040C: 4180FFE8  blt      *-24                    ; 0x000003F4
00000410: 80010014  lwz      r0,20(rsp)
00000414: 83E1000C  lwz      r31,12(rsp)
00000418: 7C0803A6  mtlr     r0
0000041C: 38210010  addi     rsp,rsp,16
00000420: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="func_80084188__Q23EGG7StateGXFv"  Size=164
00000424: 9421FFD0  stwu     rsp,-48(rsp)
00000428: 7C0802A6  mflr     r0
0000042C: 3C800000  lis      r4,sTexObjImage__Q23EGG7StateGX@ha
00000430: 38A00004  li       r5,4
00000434: 90010034  stw      r0,52(rsp)
00000438: 38610008  addi     r3,rsp,8
0000043C: 38840000  addi     r4,r4,sTexObjImage__Q23EGG7StateGX@l
00000440: 38C00004  li       r6,4
00000444: 38E00003  li       r7,3
00000448: 39000000  li       r8,0
0000044C: 39200000  li       r9,0
00000450: 39400000  li       r10,0
00000454: 48000001  bl       GXInitTexObj
00000458: 38610008  addi     r3,rsp,8
0000045C: 38800000  li       r4,0
00000460: 48000001  bl       GXLoadTexObj
00000464: 38610008  addi     r3,rsp,8
00000468: 38800001  li       r4,1
0000046C: 48000001  bl       GXLoadTexObj
00000470: 38610008  addi     r3,rsp,8
00000474: 38800002  li       r4,2
00000478: 48000001  bl       GXLoadTexObj
0000047C: 38610008  addi     r3,rsp,8
00000480: 38800003  li       r4,3
00000484: 48000001  bl       GXLoadTexObj
00000488: 38610008  addi     r3,rsp,8
0000048C: 38800004  li       r4,4
00000490: 48000001  bl       GXLoadTexObj
00000494: 38610008  addi     r3,rsp,8
00000498: 38800005  li       r4,5
0000049C: 48000001  bl       GXLoadTexObj
000004A0: 38610008  addi     r3,rsp,8
000004A4: 38800006  li       r4,6
000004A8: 48000001  bl       GXLoadTexObj
000004AC: 38610008  addi     r3,rsp,8
000004B0: 38800007  li       r4,7
000004B4: 48000001  bl       GXLoadTexObj
000004B8: 80010034  lwz      r0,52(rsp)
000004BC: 7C0803A6  mtlr     r0
000004C0: 38210030  addi     rsp,rsp,48
000004C4: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="func_8008422C__Q23EGG7StateGXFv"  Size=4
000004C8: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="func_800842E0__Q23EGG7StateGXFv"  Size=4
000004CC: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="func_80084490__Q23EGG7StateGXFv"  Size=4
000004D0: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="func_80084548__Q23EGG7StateGXFv"  Size=60
000004D4: 9421FFF0  stwu     rsp,-16(rsp)
000004D8: 7C0802A6  mflr     r0
000004DC: 38600001  li       r3,1
000004E0: 90010014  stw      r0,20(rsp)
000004E4: 38000000  li       r0,0
000004E8: 90000000  stw      r0,sStateFlags2__Q23EGG7StateGX@sda21
000004EC: 48000001  bl       GXSetColorUpdate__Q23EGG7StateGXFb
000004F0: 38600001  li       r3,1
000004F4: 48000001  bl       GXSetAlphaUpdate__Q23EGG7StateGXFb
000004F8: 38600001  li       r3,1
000004FC: 48000001  bl       GXSetDither__Q23EGG7StateGXFb
00000500: 80010014  lwz      r0,20(rsp)
00000504: 7C0803A6  mtlr     r0
00000508: 38210010  addi     rsp,rsp,16
0000050C: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="GXSetProjection__Q23EGG7StateGXFPA4_fi"  Size=220
00000510: 9421FFB0  stwu     rsp,-80(rsp)
00000514: 7C0802A6  mflr     r0
00000518: 2C040001  cmpwi    r4,0x0001
0000051C: 90010054  stw      r0,84(rsp)
00000520: 41820014  beq      *+20                    ; 0x00000534
00000524: 408000A0  bge      *+160                   ; 0x000005C4
00000528: 2C040000  cmpwi    r4,0x0000
0000052C: 40800090  bge      *+144                   ; 0x000005BC
00000530: 48000094  b        *+148                   ; 0x000005C4
00000534: 80830000  lwz      r4,0(r3)
00000538: 80030004  lwz      r0,4(r3)
0000053C: 90810008  stw      r4,8(rsp)
00000540: 9001000C  stw      r0,12(rsp)
00000544: 80830008  lwz      r4,8(r3)
00000548: 8003000C  lwz      r0,12(r3)
0000054C: 90810010  stw      r4,16(rsp)
00000550: 90010014  stw      r0,20(rsp)
00000554: 80830010  lwz      r4,16(r3)
00000558: 80030014  lwz      r0,20(r3)
0000055C: 90810018  stw      r4,24(rsp)
00000560: 9001001C  stw      r0,28(rsp)
00000564: 80830018  lwz      r4,24(r3)
00000568: 8003001C  lwz      r0,28(r3)
0000056C: 90810020  stw      r4,32(rsp)
00000570: 90010024  stw      r0,36(rsp)
00000574: 80830020  lwz      r4,32(r3)
00000578: 80030024  lwz      r0,36(r3)
0000057C: 90810028  stw      r4,40(rsp)
00000580: 9001002C  stw      r0,44(rsp)
00000584: 80830028  lwz      r4,40(r3)
00000588: 8003002C  lwz      r0,44(r3)
0000058C: 90810030  stw      r4,48(rsp)
00000590: 90010034  stw      r0,52(rsp)
00000594: 80830030  lwz      r4,48(r3)
00000598: 80030034  lwz      r0,52(r3)
0000059C: 90810038  stw      r4,56(rsp)
000005A0: 9001003C  stw      r0,60(rsp)
000005A4: 80830038  lwz      r4,56(r3)
000005A8: 8003003C  lwz      r0,60(r3)
000005AC: 38610008  addi     r3,rsp,8
000005B0: 90810040  stw      r4,64(rsp)
000005B4: 90010044  stw      r0,68(rsp)
000005B8: 48000001  bl       func_800846A8
000005BC: 38610008  addi     r3,rsp,8
000005C0: 48000001  bl       func_800846A8
000005C4: 3C600000  lis      r3,@stringBase0@ha
000005C8: 3880008C  li       r4,140
000005CC: 38630000  addi     r3,r3,@stringBase0@l
000005D0: 38A3000F  addi     r5,r3,15
000005D4: 4CC63182  crxor    6,6,6
000005D8: 48000001  bl       system_halt
000005DC: 80010054  lwz      r0,84(rsp)
000005E0: 7C0803A6  mtlr     r0
000005E4: 38210050  addi     rsp,rsp,80
000005E8: 4E800020  blr

==> .rodata
@stringBase0:
00000000: 65676753  74617465  47582E63  70700030 'eggStateGX.cpp.0'
00000010: 00                                     '.               '

==> .bss
sTexObjImage__Q23EGG7StateGX:
00000000: 00000000  00000000  00000000  00000000 

==> .sdata
sStateFlags1__Q23EGG7StateGX:
00000000: 00200000                               '. ..            '
sTMemLayout__Q23EGG7StateGX:
00000004:           00000001                     '    ....        '

==> .sbss
sDefaultTexColor__Q23EGG7StateGX:
00000000: 00000000                               

==> .sdata2
cAmbColorWhite__Q23EGG7StateGX:
00000000: FFFFFFFF                               '....            '

==> .rela.mwcats.text
    entry  offset   addend   type name(symbol id)
    [   0] 00000004 00000000    1 OSu16tof32(13)
    [   1] 0000000c 00000000    1 OSf32tou16(15)
    [   2] 00000014 00000000    1 OSs16tof32(17)
    [   3] 0000001c 00000000    1 OSf32tos16(19)
    [   4] 00000024 00000000    1 InitFastCast__Q24nw4r3g3dFv(22)
    [   5] 0000002c 00000000    1 GXEnd(20)
    [   6] 00000034 00000000    1 func_80083E18__Q23EGG7StateGXFv(23)
    [   7] 0000003c 00000000    1 func_80083E5C__Q23EGG7StateGXFv(26)
    [   8] 00000044 00000000    1 func_80083EBC__Q23EGG7StateGXFv(27)
    [   9] 0000004c 00000000    1 func_80083EC0__Q23EGG7StateGXFv(31)
    [  10] 00000054 00000000    1 func_80083EF8__Q23EGG7StateGXFv(32)
    [  11] 0000005c 00000000    1 func_80084034__Q23EGG7StateGXFv(34)
    [  12] 00000064 00000000    1 func_80084110__Q23EGG7StateGXFv(33)
    [  13] 0000006c 00000000    1 func_80084188__Q23EGG7StateGXFv(35)
    [  14] 00000074 00000000    1 func_8008422C__Q23EGG7StateGXFv(36)
    [  15] 0000007c 00000000    1 func_800842E0__Q23EGG7StateGXFv(37)
    [  16] 00000084 00000000    1 func_80084490__Q23EGG7StateGXFv(38)
    [  17] 0000008c 00000000    1 func_80084548__Q23EGG7StateGXFv(30)
    [  18] 00000094 00000000    1 GXSetProjection__Q23EGG7StateGXFPA4_fi(55)

==> .mwcats.text
    entry   offset    type size     addr     procexits
    [   0]  00000000     2 000c     00000000         0
    [   1]  00000008     2 001c     00000000         0
    [   2]  00000010     2 000c     00000000         0
    [   3]  00000018     2 001c     00000000         0
    [   4]  00000020     2 004c     00000000         0
    [   5]  00000028     2 0004     00000000         0
    [   6]  00000030     2 0044     00000000         0
    [   7]  00000038     2 0004     00000000         0
    [   8]  00000040     2 0004     00000000         0
    [   9]  00000048     2 0038     00000000         0
    [  10]  00000050     2 013c     00000000         0
    [  11]  00000058     2 00dc     00000000         0
    [  12]  00000060     2 004c     00000000         0
    [  13]  00000068     2 00a4     00000000         0
    [  14]  00000070     2 0004     00000000         0
    [  15]  00000078     2 0004     00000000         0
    [  16]  00000080     2 0004     00000000         0
    [  17]  00000088     2 003c     00000000         0
    [  18]  00000090     2 00dc     00000000         0

==> .comment
MagicWord: CodeWarrior
Comment section version: 15
Compiler version: 4.0.0
CW Compiler generated
Pooled data: true
PPC EABI compliant
FP Support: Hardware
Processor: Gecko
Char Signedness: signed
