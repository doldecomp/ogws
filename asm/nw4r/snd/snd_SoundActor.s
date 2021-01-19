.include "macros.inc"

.section .text, "ax"

.global detail_SetupSound__Q44nw4r3snd6detail10SoundActorFPQ34nw4r3snd11SoundHandleUlPQ54nw4r3snd6detail10BasicSound14AmbientArgInfoPQ44nw4r3snd6detail19ExternalSoundPlayerbPCQ44nw4r3snd14SoundStartable9StartInfo
detail_SetupSound__Q44nw4r3snd6detail10SoundActorFPQ34nw4r3snd11SoundHandleUlPQ54nw4r3snd6detail10BasicSound14AmbientArgInfoPQ44nw4r3snd6detail19ExternalSoundPlayerbPCQ44nw4r3snd14SoundStartable9StartInfo:
/* 80041CF0 0003CBF0  7C 66 1B 78 */	mr r6, r3
/* 80041CF4 0003CBF4  80 63 00 04 */	lwz r3, 4(r3)
/* 80041CF8 0003CBF8  38 E6 00 08 */	addi r7, r6, 8
/* 80041CFC 0003CBFC  81 83 00 00 */	lwz r12, 0(r3)
/* 80041D00 0003CC00  38 C0 00 00 */	li r6, 0
/* 80041D04 0003CC04  81 8C 00 0C */	lwz r12, 0xc(r12)
/* 80041D08 0003CC08  7D 89 03 A6 */	mtctr r12
/* 80041D0C 0003CC0C  4E 80 04 20 */	bctr 
