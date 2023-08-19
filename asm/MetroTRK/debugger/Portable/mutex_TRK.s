.include "macros.inc"

.section .text, "ax"
.global TRKReleaseMutex
TRKReleaseMutex:
/* 800C38F0 000BE7F0  38 60 00 00 */	li r3, 0
/* 800C38F4 000BE7F4  4E 80 00 20 */	blr 

.global TRKAcquireMutex
TRKAcquireMutex:
/* 800C38F8 000BE7F8  38 60 00 00 */	li r3, 0
/* 800C38FC 000BE7FC  4E 80 00 20 */	blr 

.global TRKInitializeMutex
TRKInitializeMutex:
/* 800C3900 000BE800  38 60 00 00 */	li r3, 0
/* 800C3904 000BE804  4E 80 00 20 */	blr 
