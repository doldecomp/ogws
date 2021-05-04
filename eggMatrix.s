Analyzing: C:\Users\schif\AppData\Local\Temp\eggMatrix.o
Header idenfication: 0x7f, ELF, 32 bit MSB v1
    type:           1, machine:         20
    version: 00000001, entry:     00000000, phoff:  00000000
    shoff:   00000680, flags:     80000000, ehsize:       52, phentsize:  0
    phnum:          0, shentsize:       40, shnum:        10, shstrndx:  8


==> .shstrtab
    [  1]	.text
    [  7]	.sdata2
    [ 15]	.mwcats.text
    [ 28]	.rela.text
    [ 39]	.rela.mwcats.text
    [ 57]	.symtab
    [ 65]	.strtab
    [ 73]	.shstrtab
    [ 83]	.comment

==> .text [1]: Section Header
    type:    00000001, flags:  00000006
    address: 00000000, offset: 00000034, size: 000001b0
    link:    00000000, info:   00000000, alignment: 4, entry size: 0


==> .sdata2 [2]: Section Header
    type:    00000001, flags:  00000003
    address: 00000000, offset: 000001e8, size: 0000000c
    link:    00000000, info:   00000000, alignment: 8, entry size: 0


==> .mwcats.text [3]: Section Header
    type:    ca2a82c2, flags:  00000000
    address: 00000000, offset: 000001f4, size: 00000038
    link:    00000001, info:   00000000, alignment: 4, entry size: 1


==> .rela.text [4]: Section Header
    type:    00000004, flags:  00000000
    address: 00000000, offset: 0000022c, size: 00000078
    link:    00000006, info:   00000001, alignment: 4, entry size: 12


==> .rela.mwcats.text [5]: Section Header
    type:    00000004, flags:  00000000
    address: 00000000, offset: 000002a4, size: 00000054
    link:    00000006, info:   00000003, alignment: 4, entry size: 12


==> .symtab [6]: Section Header
    type:    00000002, flags:  00000000
    address: 00000000, offset: 000002f8, size: 00000120
    link:    00000007, info:   00000009, alignment: 4, entry size: 16


==> .strtab [7]: Section Header
    type:    00000003, flags:  00000000
    address: 00000000, offset: 00000418, size: 0000014a
    link:    00000000, info:   00000000, alignment: 1, entry size: 1


==> .shstrtab [8]: Section Header
    type:    00000003, flags:  00000000
    address: 00000000, offset: 00000562, size: 0000005c
    link:    00000000, info:   00000000, alignment: 1, entry size: 1


==> .comment [9]: Section Header
    type:    00000001, flags:  00000000
    address: 00000000, offset: 000005be, size: 000000bc
    link:    00000000, info:   00000000, alignment: 1, entry size: 1


==> .strtab
    [  1]	eggMatrix.cpp
    [ 15]	GXEnd
    [ 21]	@29
    [ 25]	@30
    [ 29]	@47
    [ 33]	__dt__Q23EGG9Matrix34fFv
    [ 58]	__dl__FPv
    [ 68]	makeIdentity__Q23EGG9Matrix34fFv
    [ 101]	makeQ__Q23EGG9Matrix34fFRCQ23EGG4Quat
    [ 139]	makeS__Q23EGG9Matrix34fFRCQ23EGG8Vector3f
    [ 181]	setAxisRotation__Q23EGG9Matrix34fFRCQ23EGG8Vector3ff
    [ 234]	setAxisRotation__Q23EGG4QuatFRCQ23EGG8Vector3ff
    [ 282]	loadPosMtx__Q23EGG9Matrix34fFUl
    [ 314]	GXLoadPosMtxImm

==> .symtab
    entry  spndx   value      size   bind   type  other    shndx         name
    [   0]     0   00000000      0   LOC    NULL      0    UND           
    [   1]     1   00000000      0   LOC    FILE      0    ABS           eggMatrix.cpp
    [   2]     0   00000000      0   LOC    SECT      0    .text         .text
    [   3]     0   00000000      0   LOC    SECT      0    .sdata2       .sdata2
    [   4]     0   00000000      0   LOC    SECT      0    .mwcats.text  .mwcats.text
    [   5]    15   00000000      4   LOC    FUNC      0    .text         GXEnd
    [   6]    21   00000000      4   LOC    OBJ       0    .sdata2       @29
    [   7]    25   00000004      4   LOC    OBJ       0    .sdata2       @30
    [   8]    29   00000008      4   LOC    OBJ       0    .sdata2       @47
    [   9]    33   00000004     64   GLOB   FUNC      0    .text         __dt__Q23EGG9Matrix34fFv
    [  10]    58   00000000      0   GLOB   NULL      0    UND           __dl__FPv
    [  11]    68   00000044     60   GLOB   FUNC      0    .text         makeIdentity__Q23EGG9Matrix34fFv
    [  12]   101   00000080    172   GLOB   FUNC      0    .text         makeQ__Q23EGG9Matrix34fFRCQ23EGG4Quat
    [  13]   139   0000012c     68   GLOB   FUNC      0    .text         makeS__Q23EGG9Matrix34fFRCQ23EGG8Vector3f
    [  14]   181   00000170     60   GLOB   FUNC      0    .text         setAxisRotation__Q23EGG9Matrix34fFRCQ23EGG8Vector3ff
    [  15]   234   00000000      0   GLOB   NULL      0    UND           setAxisRotation__Q23EGG4QuatFRCQ23EGG8Vector3ff
    [  16]   282   000001ac      4   GLOB   FUNC      0    .text         loadPosMtx__Q23EGG9Matrix34fFUl
    [  17]   314   00000000      0   GLOB   NULL      0    UND           GXLoadPosMtxImm

==> .rela.text
    entry  offset   addend   type name(symbol id)
    [   0] 00000028 00000000   10 __dl__FPv(10)
    [   1] 00000044 00000000  109 @29(6)
    [   2] 00000048 00000000  109 @30(7)
    [   3] 00000080 00000000  109 @47(8)
    [   4] 00000088 00000000  109 @29(6)
    [   5] 000000a8 00000000  109 @30(7)
    [   6] 0000012c 00000000  109 @29(6)
    [   7] 00000188 00000000   10 setAxisRotation__Q23EGG4QuatFRCQ23EGG8Vector3ff(15)
    [   8] 00000194 00000000   10 makeQ__Q23EGG9Matrix34fFRCQ23EGG4Quat(12)
    [   9] 000001ac 00000000   10 GXLoadPosMtxImm(17)

==> .text

Hunk:	Kind=HUNK_LOCAL_CODE     Name="GXEnd"  Size=4
00000000: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="__dt__Q23EGG9Matrix34fFv"  Size=64
00000004: 9421FFF0  stwu     rsp,-16(rsp)
00000008: 7C0802A6  mflr     r0
0000000C: 2C030000  cmpwi    r3,0x0000
00000010: 90010014  stw      r0,20(rsp)
00000014: 93E1000C  stw      r31,12(rsp)
00000018: 7C7F1B78  mr       r31,r3
0000001C: 41820010  beq      *+16                    ; 0x0000002C
00000020: 2C040000  cmpwi    r4,0x0000
00000024: 40810008  ble      *+8                     ; 0x0000002C
00000028: 48000001  bl       __dl__FPv
0000002C: 7FE3FB78  mr       r3,r31
00000030: 83E1000C  lwz      r31,12(rsp)
00000034: 80010014  lwz      r0,20(rsp)
00000038: 7C0803A6  mtlr     r0
0000003C: 38210010  addi     rsp,rsp,16
00000040: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="makeIdentity__Q23EGG9Matrix34fFv"  Size=60
00000044: C0200000  lfs      fp1,@29@sda21
00000048: C0000000  lfs      fp0,@30@sda21
0000004C: D0230004  stfs     fp1,4(r3)
00000050: D0230008  stfs     fp1,8(r3)
00000054: D023000C  stfs     fp1,12(r3)
00000058: D0230010  stfs     fp1,16(r3)
0000005C: D0230018  stfs     fp1,24(r3)
00000060: D023001C  stfs     fp1,28(r3)
00000064: D0230020  stfs     fp1,32(r3)
00000068: D0230024  stfs     fp1,36(r3)
0000006C: D023002C  stfs     fp1,44(r3)
00000070: D0030028  stfs     fp0,40(r3)
00000074: D0030014  stfs     fp0,20(r3)
00000078: D0030000  stfs     fp0,0(r3)
0000007C: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="makeQ__Q23EGG9Matrix34fFRCQ23EGG4Quat"  Size=172
00000080: C0600000  lfs      fp3,@47@sda21
00000084: C1440004  lfs      fp10,4(r4)
00000088: C0400000  lfs      fp2,@29@sda21
0000008C: ED2302B2  fmuls    fp9,fp3,fp10
00000090: C1040000  lfs      fp8,0(r4)
00000094: C0C40008  lfs      fp6,8(r4)
00000098: C004000C  lfs      fp0,12(r4)
0000009C: ECE30232  fmuls    fp7,fp3,fp8
000000A0: EC2301B2  fmuls    fp1,fp3,fp6
000000A4: ECA30032  fmuls    fp5,fp3,fp0
000000A8: C0000000  lfs      fp0,@30@sda21
000000AC: ED6902B2  fmuls    fp11,fp9,fp10
000000B0: D043000C  stfs     fp2,12(r3)
000000B4: ED8101B2  fmuls    fp12,fp1,fp6
000000B8: EC670232  fmuls    fp3,fp7,fp8
000000BC: EC205828  fsubs    fp1,fp0,fp11
000000C0: D043001C  stfs     fp2,28(r3)
000000C4: EDA702B2  fmuls    fp13,fp7,fp10
000000C8: D043002C  stfs     fp2,44(r3)
000000CC: EC4501B2  fmuls    fp2,fp5,fp6
000000D0: EC001828  fsubs    fp0,fp0,fp3
000000D4: EC816028  fsubs    fp4,fp1,fp12
000000D8: EC6D1028  fsubs    fp3,fp13,fp2
000000DC: EC206028  fsubs    fp1,fp0,fp12
000000E0: EC4D102A  fadds    fp2,fp13,fp2
000000E4: D0830000  stfs     fp4,0(r3)
000000E8: EC005828  fsubs    fp0,fp0,fp11
000000EC: EC8701B2  fmuls    fp4,fp7,fp6
000000F0: D0630004  stfs     fp3,4(r3)
000000F4: EC6502B2  fmuls    fp3,fp5,fp10
000000F8: D0430010  stfs     fp2,16(r3)
000000FC: ECC901B2  fmuls    fp6,fp9,fp6
00000100: ECA50232  fmuls    fp5,fp5,fp8
00000104: EC441828  fsubs    fp2,fp4,fp3
00000108: D0230014  stfs     fp1,20(r3)
0000010C: EC262828  fsubs    fp1,fp6,fp5
00000110: D0030028  stfs     fp0,40(r3)
00000114: EC06282A  fadds    fp0,fp6,fp5
00000118: D0430008  stfs     fp2,8(r3)
0000011C: D0230018  stfs     fp1,24(r3)
00000120: D0430020  stfs     fp2,32(r3)
00000124: D0030024  stfs     fp0,36(r3)
00000128: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="makeS__Q23EGG9Matrix34fFRCQ23EGG8Vector3f"  Size=68
0000012C: C0400000  lfs      fp2,@29@sda21
00000130: C0640000  lfs      fp3,0(r4)
00000134: C0240004  lfs      fp1,4(r4)
00000138: C0040008  lfs      fp0,8(r4)
0000013C: D0630000  stfs     fp3,0(r3)
00000140: D0430004  stfs     fp2,4(r3)
00000144: D0430008  stfs     fp2,8(r3)
00000148: D043000C  stfs     fp2,12(r3)
0000014C: D0230010  stfs     fp1,16(r3)
00000150: D0430014  stfs     fp2,20(r3)
00000154: D0430018  stfs     fp2,24(r3)
00000158: D043001C  stfs     fp2,28(r3)
0000015C: D0030020  stfs     fp0,32(r3)
00000160: D0430024  stfs     fp2,36(r3)
00000164: D0430028  stfs     fp2,40(r3)
00000168: D043002C  stfs     fp2,44(r3)
0000016C: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="setAxisRotation__Q23EGG9Matrix34fFRCQ23EGG8Vector3ff"  Size=60
00000170: 9421FFE0  stwu     rsp,-32(rsp)
00000174: 7C0802A6  mflr     r0
00000178: 90010024  stw      r0,36(rsp)
0000017C: 93E1001C  stw      r31,28(rsp)
00000180: 7C7F1B78  mr       r31,r3
00000184: 38610008  addi     r3,rsp,8
00000188: 48000001  bl       setAxisRotation__Q23EGG4QuatFRCQ23EGG8Vector3ff
0000018C: 7FE3FB78  mr       r3,r31
00000190: 38810008  addi     r4,rsp,8
00000194: 48000001  bl       makeQ__Q23EGG9Matrix34fFRCQ23EGG4Quat
00000198: 80010024  lwz      r0,36(rsp)
0000019C: 83E1001C  lwz      r31,28(rsp)
000001A0: 7C0803A6  mtlr     r0
000001A4: 38210020  addi     rsp,rsp,32
000001A8: 4E800020  blr

Hunk:	Kind=HUNK_GLOBAL_CODE     Name="loadPosMtx__Q23EGG9Matrix34fFUl"  Size=4
000001AC: 48000000  b        GXLoadPosMtxImm

==> .sdata2
@29:
00000000: 00000000                               '....            '
@30:
00000004:           3F800000                     '    ?...        '
@47:
00000008:                     40000000           '        @...    '

==> .rela.mwcats.text
    entry  offset   addend   type name(symbol id)
    [   0] 00000004 00000000    1 GXEnd(5)
    [   1] 0000000c 00000000    1 __dt__Q23EGG9Matrix34fFv(9)
    [   2] 00000014 00000000    1 makeIdentity__Q23EGG9Matrix34fFv(11)
    [   3] 0000001c 00000000    1 makeQ__Q23EGG9Matrix34fFRCQ23EGG4Quat(12)
    [   4] 00000024 00000000    1 makeS__Q23EGG9Matrix34fFRCQ23EGG8Vector3f(13)
    [   5] 0000002c 00000000    1 setAxisRotation__Q23EGG9Matrix34fFRCQ23EGG8Vector3ff(14)
    [   6] 00000034 00000000    1 loadPosMtx__Q23EGG9Matrix34fFUl(16)

==> .mwcats.text
    entry   offset    type size     addr     procexits
    [   0]  00000000     2 0004     00000000         0
    [   1]  00000008     2 0040     00000000         0
    [   2]  00000010     2 003c     00000000         0
    [   3]  00000018     2 00ac     00000000         0
    [   4]  00000020     2 0044     00000000         0
    [   5]  00000028     2 003c     00000000         0
    [   6]  00000030     2 0004     00000000         0

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
