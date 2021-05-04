###############################################################
# I think this is eggException.s, but I don't have any proof. #
# These two functions get called in what seems to be the      #
# Pack Project engine init function (first call in main),     #
# but their contents seem to be stubbed out.                  #
###############################################################

.include "macros.inc"

.section .text, "ax"

# FUN_800b1744(0x40,0x20,4,0);
.global func_800B1744
func_800B1744:
/* 800B1744 000AC644  38 60 00 00 */	li r3, 0
/* 800B1748 000AC648  4E 80 00 20 */	blr 

# FUN_800b174c(&PTR_DAT_803820b8);
# Given double pointer to floating_point_unavailable_exception_handler
.global func_800B174C
func_800B174C:
/* 800B174C 000AC64C  4E 80 00 20 */	blr 
