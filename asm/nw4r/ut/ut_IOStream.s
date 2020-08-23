.include "macros.inc"

.section .text, "ax"  # 0x800076E0 - 0x80355080

# ReadAsync__Q34nw4r2ut8IOStreamFPvUlPFlPQ34nw4r2ut8IOStreamPv_vPv
.global func_8000833C
func_8000833C:
/* 8000833C 0000323C  38 60 00 00 */	li r3, 0
/* 80008340 00003240  4E 80 00 20 */	blr 

# Write__Q34nw4r2ut8IOStreamFPCvUl
.global func_80008344
func_80008344:
/* 80008344 00003244  4E 80 00 20 */	blr 

# WriteAsync__Q34nw4r2ut8IOStreamFPCvUlPFlPQ34nw4r2ut8IOStreamPv_vPv
.global func_80008348
func_80008348:
/* 80008348 00003248  38 60 00 00 */	li r3, 0
/* 8000834C 0000324C  4E 80 00 20 */	blr 

# IsBusy__Q34nw4r2ut8IOStreamCFv
.global func_80008350
func_80008350:
/* 80008350 00003250  38 60 00 00 */	li r3, 0
/* 80008354 00003254  4E 80 00 20 */	blr 

# GetBufferAlign__Q34nw4r2ut8IOStreamCFv
.global func_80008358
func_80008358:
/* 80008358 00003258  38 60 00 01 */	li r3, 1
/* 8000835C 0000325C  4E 80 00 20 */	blr 

# GetSizeAlign__Q34nw4r2ut8IOStreamCFv
.global func_80008360
func_80008360:
/* 80008360 00003260  38 60 00 01 */	li r3, 1
/* 80008364 00003264  4E 80 00 20 */	blr 

# GetOffsetAlign__Q34nw4r2ut8IOStreamCFv
.global func_80008368
func_80008368:
/* 80008368 00003268  38 60 00 01 */	li r3, 1
/* 8000836C 0000326C  4E 80 00 20 */	blr 

# __sinit_\ut_IOStream_cpp
.global func_80008370
func_80008370:
/* 80008370 00003270  38 00 00 00 */	li r0, 0
/* 80008374 00003274  90 0D 96 60 */	stw r0, lbl_804BE9E0-_SDA_BASE_(r13)
/* 80008378 00003278  4E 80 00 20 */	blr 
