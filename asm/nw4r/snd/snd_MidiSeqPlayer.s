.include "macros.inc"

.section .text, "ax"  # 0x800076E0 - 0x80355080 

.global OnShutdownSoundThread__Q44nw4r3snd6detail9SeqPlayerFv
OnShutdownSoundThread__Q44nw4r3snd6detail9SeqPlayerFv:
/* 8003B868 00036768  81 83 00 00 */	lwz r12, 0(r3)
/* 8003B86C 0003676C  81 8C 00 10 */	lwz r12, 0x10(r12)
/* 8003B870 00036770  7D 89 03 A6 */	mtctr r12
/* 8003B874 00036774  4E 80 04 20 */	bctr 

.global InvalidateWaveData__Q44nw4r3snd6detail9SeqPlayerFPCvPCv
InvalidateWaveData__Q44nw4r3snd6detail9SeqPlayerFPCvPCv:
/* 8003B878 00036778  4E 80 00 20 */	blr 
/* 8003B87C 0003677C  4E 80 00 20 */	blr 

.global IsPause__Q44nw4r3snd6detail9SeqPlayerCFv
IsPause__Q44nw4r3snd6detail9SeqPlayerCFv:
/* 8003B880 00036780  88 63 00 8E */	lbz r3, 0x8e(r3)
/* 8003B884 00036784  4E 80 00 20 */	blr 

.global IsStarted__Q44nw4r3snd6detail9SeqPlayerCFv
IsStarted__Q44nw4r3snd6detail9SeqPlayerCFv:
/* 8003B888 00036788  88 63 00 8D */	lbz r3, 0x8d(r3)
/* 8003B88C 0003678C  4E 80 00 20 */	blr 

.global IsActive__Q44nw4r3snd6detail9SeqPlayerCFv
IsActive__Q44nw4r3snd6detail9SeqPlayerCFv:
/* 8003B890 00036790  88 63 00 8C */	lbz r3, 0x8c(r3)
/* 8003B894 00036794  4E 80 00 20 */	blr 

.global $$2116$$2InvalidateWaveData__Q44nw4r3snd6detail9SeqPlayerFPCvPCv
$$2116$$InvalidateWaveData__Q44nw4r3snd6detail9SeqPlayerFPCvPCv:
/* 8003B898 00036798  38 63 FF 8C */	addi r3, r3, -116
/* 8003B89C 0003679C  4B FF FF DC */	b InvalidateWaveData__Q44nw4r3snd6detail9SeqPlayerFPCvPCv

.global InvalidateData__Q44nw4r3snd6detail9SeqPlayerFPCvPCv
InvalidateData__Q44nw4r3snd6detail9SeqPlayerFPCvPCv:
/* 8003B8A0 000367A0  38 63 FF 8C */	addi r3, r3, -116
/* 8003B8A4 000367A4  48 00 31 B4 */	b func_8003EA58

.global $$2128$$2OnShutdownSoundThread__Q44nw4r3snd6detail9SeqPlayerFv
$$2128$$2OnShutdownSoundThread__Q44nw4r3snd6detail9SeqPlayerFv:
/* 8003B8A8 000367A8  38 63 FF 80 */	addi r3, r3, -128
/* 8003B8AC 000367AC  4B FF FF BC */	b OnShutdownSoundThread__Q44nw4r3snd6detail9SeqPlayerFv

.global OnUpdateFrameSoundThread__Q44nw4r3snd6detail9SeqPlayerFv
OnUpdateFrameSoundThread__Q44nw4r3snd6detail9SeqPlayerFv:
/* 8003B8B0 000367B0  38 63 FF 80 */	addi r3, r3, -128
/* 8003B8B4 000367B4  4B FF FF B0 */	b func_8003B864
