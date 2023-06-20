.include "macros.inc"

.section .rodata, "a"
.balign 0x8
.global __wctype_mapC
__wctype_mapC:
.incbin "baserom.dol", 0x377A48, 0x200
.global __wlower_mapC
__wlower_mapC:
.incbin "baserom.dol", 0x377C48, 0x200
.global __wupper_mapC
__wupper_mapC:
.incbin "baserom.dol", 0x377E48, 0x200
