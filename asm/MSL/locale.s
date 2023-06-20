.include "macros.inc"

.section .data, "wa"
.balign 0x8
.global __lconv
__lconv:
	.incbin "baserom.dol", 0x394B40, 0x38
.global _loc_ctyp_C
_loc_ctyp_C:
	.incbin "baserom.dol", 0x394B78, 0x28
.global char_coll_tableC
char_coll_tableC:
	.incbin "baserom.dol", 0x394BA0, 0xC0
.global _loc_coll_C
_loc_coll_C:
	.incbin "baserom.dol", 0x394C60, 0x1C
.global _loc_mon_C
_loc_mon_C:
	.incbin "baserom.dol", 0x394C7C, 0x34
.global _loc_num_C
_loc_num_C:
	.incbin "baserom.dol", 0x394CB0, 0x14
.global _loc_tim_C
_loc_tim_C:
	.incbin "baserom.dol", 0x394CC4, 0x2C
.global _current_locale
_current_locale:
	.incbin "baserom.dol", 0x394CF0, 0x48
