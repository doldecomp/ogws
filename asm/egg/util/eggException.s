.include "macros.inc"

.section .text, "ax"

# "Verified" symbol from BBA, call matched by WFU (RPSysSystem::initialize)
# OGWS: Exception::create(0x40,0x20,4,0);
# WFU:  Exception::create(0x40,0x20,4,0);
.global create__Q23EGG9ExceptionFUsUsUsPQ23EGG4Heap
create__Q23EGG9ExceptionFUsUsUsPQ23EGG4Heap:
/* 800B1744 000AC644  38 60 00 00 */	li r3, 0
/* 800B1748 000AC648  4E 80 00 20 */	blr 

# Given double pointer to floating_point_unavailable_exception_handler
# Non-stubbed version sets user exception callback
.global setPadInfo__Q23EGG9ExceptionFPCUs
setPadInfo__Q23EGG9ExceptionFPCUs:
/* 800B174C 000AC64C  4E 80 00 20 */	blr 
