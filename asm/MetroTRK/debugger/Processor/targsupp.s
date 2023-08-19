# I believe this file was written in pure assembly,
# from the link map and the padding at the end of targimpl.o
# 
# 000000 803198f0 00315ad0    TRKAccessFile (entry of .text)   	RevoSDKD.a debugger\embedded\MetroTRK\Processor\ppc\Export\targsupp.o
# 000000 803198f8 00315ad8    TRKOpenFile (entry of .text) 	    RevoSDKD.a debugger\embedded\MetroTRK\Processor\ppc\Export\targsupp.o
# 000000 80319900 00315ae0    TRKCloseFile (entry of .text) 	    RevoSDKD.a debugger\embedded\MetroTRK\Processor\ppc\Export\targsupp.o
# 000000 80319908 00315ae8    TRKPositionFile (entry of .text) 	RevoSDKD.a debugger\embedded\MetroTRK\Processor\ppc\Export\targsupp.o

.include "macros.inc"

.section .text, "ax"
.global TRKAccessFile
TRKAccessFile:
/* 800C54D0 000C03D0  0F E0 00 00 */	twui r0, 0
/* 800C54D4 000C03D4  4E 80 00 20 */	blr 

.global TRKOpenFile
TRKOpenFile:
/* 800C54D8 000C03D8  0F E0 00 00 */	twui r0, 0
/* 800C54DC 000C03DC  4E 80 00 20 */	blr 

.global TRKCloseFile
TRKCloseFile:
/* 800C54E0 000C03E0  0F E0 00 00 */	twui r0, 0
/* 800C54E4 000C03E4  4E 80 00 20 */	blr 

.global TRKPositionFile
TRKPositionFile:
/* 800C54E8 000C03E8  0F E0 00 00 */	twui r0, 0
/* 800C54EC 000C03EC  4E 80 00 20 */	blr 
