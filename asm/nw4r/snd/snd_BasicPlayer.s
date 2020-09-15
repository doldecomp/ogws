.include "macros.inc"

.section .text, "ax"  # 0x800076E0 - 0x80355080 

.global __ct__Q44nw4r3snd6detail11BasicPlayerFv
__ct__Q44nw4r3snd6detail11BasicPlayerFv:
/* 80036120 00031020  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80036124 00031024  7C 08 02 A6 */	mflr r0
/* 80036128 00031028  3C 80 80 39 */	lis r4, lbl_80395BF8@ha
/* 8003612C 0003102C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80036130 00031030  38 00 FF FF */	li r0, -1
/* 80036134 00031034  38 84 5B F8 */	addi r4, r4, lbl_80395BF8@l
/* 80036138 00031038  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8003613C 0003103C  7C 7F 1B 78 */	mr r31, r3
/* 80036140 00031040  90 03 00 04 */	stw r0, 4(r3)
/* 80036144 00031044  90 83 00 00 */	stw r4, 0(r3)
/* 80036148 00031048  48 00 00 1D */	bl InitParam__Q44nw4r3snd6detail11BasicPlayerFv
/* 8003614C 0003104C  7F E3 FB 78 */	mr r3, r31
/* 80036150 00031050  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80036154 00031054  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80036158 00031058  7C 08 03 A6 */	mtlr r0
/* 8003615C 0003105C  38 21 00 10 */	addi r1, r1, 0x10
/* 80036160 00031060  4E 80 00 20 */	blr 

.global InitParam__Q44nw4r3snd6detail11BasicPlayerFv
InitParam__Q44nw4r3snd6detail11BasicPlayerFv:
/* 80036164 00031064  C0 02 85 54 */	lfs f0, lbl_804BFF74-_SDA2_BASE_(r2)
/* 80036168 00031068  38 80 00 00 */	li r4, 0
/* 8003616C 0003106C  C0 22 85 50 */	lfs f1, lbl_804BFF70-_SDA2_BASE_(r2)
/* 80036170 00031070  38 00 00 01 */	li r0, 1
/* 80036174 00031074  D0 03 00 10 */	stfs f0, 0x10(r3)
/* 80036178 00031078  D0 23 00 08 */	stfs f1, 8(r3)
/* 8003617C 0003107C  D0 23 00 0C */	stfs f1, 0xc(r3)
/* 80036180 00031080  D0 03 00 14 */	stfs f0, 0x14(r3)
/* 80036184 00031084  D0 03 00 18 */	stfs f0, 0x18(r3)
/* 80036188 00031088  98 83 00 68 */	stb r4, 0x68(r3)
/* 8003618C 0003108C  90 83 00 6C */	stw r4, 0x6c(r3)
/* 80036190 00031090  90 83 00 70 */	stw r4, 0x70(r3)
/* 80036194 00031094  90 03 00 20 */	stw r0, 0x20(r3)
/* 80036198 00031098  D0 03 00 28 */	stfs f0, 0x28(r3)
/* 8003619C 0003109C  D0 23 00 24 */	stfs f1, 0x24(r3)
/* 800361A0 000310A0  D0 03 00 2C */	stfs f0, 0x2c(r3)
/* 800361A4 000310A4  D0 03 00 30 */	stfs f0, 0x30(r3)
/* 800361A8 000310A8  D0 03 00 34 */	stfs f0, 0x34(r3)
/* 800361AC 000310AC  D0 23 00 38 */	stfs f1, 0x38(r3)
/* 800361B0 000310B0  D0 03 00 48 */	stfs f0, 0x48(r3)
/* 800361B4 000310B4  D0 03 00 58 */	stfs f0, 0x58(r3)
/* 800361B8 000310B8  D0 23 00 3C */	stfs f1, 0x3c(r3)
/* 800361BC 000310BC  D0 03 00 4C */	stfs f0, 0x4c(r3)
/* 800361C0 000310C0  D0 03 00 5C */	stfs f0, 0x5c(r3)
/* 800361C4 000310C4  D0 23 00 40 */	stfs f1, 0x40(r3)
/* 800361C8 000310C8  D0 03 00 50 */	stfs f0, 0x50(r3)
/* 800361CC 000310CC  D0 03 00 60 */	stfs f0, 0x60(r3)
/* 800361D0 000310D0  D0 23 00 44 */	stfs f1, 0x44(r3)
/* 800361D4 000310D4  D0 03 00 54 */	stfs f0, 0x54(r3)
/* 800361D8 000310D8  D0 03 00 64 */	stfs f0, 0x64(r3)
/* 800361DC 000310DC  4E 80 00 20 */	blr 

.global SetFxSend__Q44nw4r3snd6detail11BasicPlayerFQ34nw4r3snd6AuxBusf
SetFxSend__Q44nw4r3snd6detail11BasicPlayerFQ34nw4r3snd6AuxBusf:
/* 800361E0 000310E0  54 80 10 3A */	slwi r0, r4, 2
/* 800361E4 000310E4  7C 63 02 14 */	add r3, r3, r0
/* 800361E8 000310E8  D0 23 00 2C */	stfs f1, 0x2c(r3)
/* 800361EC 000310EC  4E 80 00 20 */	blr 

.global GetFxSend__Q44nw4r3snd6detail11BasicPlayerCFQ34nw4r3snd6AuxBus
GetFxSend__Q44nw4r3snd6detail11BasicPlayerCFQ34nw4r3snd6AuxBus:
/* 800361F0 000310F0  54 80 10 3A */	slwi r0, r4, 2
/* 800361F4 000310F4  7C 63 02 14 */	add r3, r3, r0
/* 800361F8 000310F8  C0 23 00 2C */	lfs f1, 0x2c(r3)
/* 800361FC 000310FC  4E 80 00 20 */	blr 

.global SetRemoteOutVolume__Q44nw4r3snd6detail11BasicPlayerFif
SetRemoteOutVolume__Q44nw4r3snd6detail11BasicPlayerFif:
/* 80036200 00031100  54 80 10 3A */	slwi r0, r4, 2
/* 80036204 00031104  7C 63 02 14 */	add r3, r3, r0
/* 80036208 00031108  D0 23 00 38 */	stfs f1, 0x38(r3)
/* 8003620C 0003110C  4E 80 00 20 */	blr 

.global GetRemoteOutVolume__Q44nw4r3snd6detail11BasicPlayerCFi
GetRemoteOutVolume__Q44nw4r3snd6detail11BasicPlayerCFi:
/* 80036210 00031110  54 80 10 3A */	slwi r0, r4, 2
/* 80036214 00031114  7C 63 02 14 */	add r3, r3, r0
/* 80036218 00031118  C0 23 00 38 */	lfs f1, 0x38(r3)
/* 8003621C 0003111C  4E 80 00 20 */	blr 

.global GetRemoteSend__Q44nw4r3snd6detail11BasicPlayerCFi
GetRemoteSend__Q44nw4r3snd6detail11BasicPlayerCFi:
/* 80036220 00031120  54 80 10 3A */	slwi r0, r4, 2
/* 80036224 00031124  7C 63 02 14 */	add r3, r3, r0
/* 80036228 00031128  C0 23 00 48 */	lfs f1, 0x48(r3)
/* 8003622C 0003112C  4E 80 00 20 */	blr 

.global GetRemoteFxSend__Q44nw4r3snd6detail11BasicPlayerCFi
GetRemoteFxSend__Q44nw4r3snd6detail11BasicPlayerCFi:
/* 80036230 00031130  54 80 10 3A */	slwi r0, r4, 2
/* 80036234 00031134  7C 63 02 14 */	add r3, r3, r0
/* 80036238 00031138  C0 23 00 58 */	lfs f1, 0x58(r3)
/* 8003623C 0003113C  4E 80 00 20 */	blr 

.global __dt__Q44nw4r3snd6detail11BasicPlayerFv
__dt__Q44nw4r3snd6detail11BasicPlayerFv:
/* 80036240 00031140  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80036244 00031144  7C 08 02 A6 */	mflr r0
/* 80036248 00031148  2C 03 00 00 */	cmpwi r3, 0
/* 8003624C 0003114C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80036250 00031150  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80036254 00031154  7C 7F 1B 78 */	mr r31, r3
/* 80036258 00031158  41 82 00 10 */	beq lbl_80036268
/* 8003625C 0003115C  2C 04 00 00 */	cmpwi r4, 0
/* 80036260 00031160  40 81 00 08 */	ble lbl_80036268
/* 80036264 00031164  48 06 D0 21 */	bl __dl__FPv
lbl_80036268:
/* 80036268 00031168  7F E3 FB 78 */	mr r3, r31
/* 8003626C 0003116C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80036270 00031170  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80036274 00031174  7C 08 03 A6 */	mtlr r0
/* 80036278 00031178  38 21 00 10 */	addi r1, r1, 0x10
/* 8003627C 0003117C  4E 80 00 20 */	blr 
