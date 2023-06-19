.include "macros.inc"

.section .text, "ax"
.global udp_cc_post_stop
udp_cc_post_stop:
/* 800C6248 000C1148  38 60 FF FF */	li r3, -1
/* 800C624C 000C114C  4E 80 00 20 */	blr 

.global udp_cc_pre_continue
udp_cc_pre_continue:
/* 800C6250 000C1150  38 60 FF FF */	li r3, -1
/* 800C6254 000C1154  4E 80 00 20 */	blr 

.global udp_cc_peek
udp_cc_peek:
/* 800C6258 000C1158  38 60 00 00 */	li r3, 0
/* 800C625C 000C115C  4E 80 00 20 */	blr 

.global udp_cc_write
udp_cc_write:
/* 800C6260 000C1160  38 60 00 00 */	li r3, 0
/* 800C6264 000C1164  4E 80 00 20 */	blr 

.global udp_cc_read
udp_cc_read:
/* 800C6268 000C1168  38 60 00 00 */	li r3, 0
/* 800C626C 000C116C  4E 80 00 20 */	blr 

.global udp_cc_close
udp_cc_close:
/* 800C6270 000C1170  38 60 FF FF */	li r3, -1
/* 800C6274 000C1174  4E 80 00 20 */	blr 

.global udp_cc_open
udp_cc_open:
/* 800C6278 000C1178  38 60 FF FF */	li r3, -1
/* 800C627C 000C117C  4E 80 00 20 */	blr 

.global udp_cc_shutdown
udp_cc_shutdown:
/* 800C6280 000C1180  38 60 FF FF */	li r3, -1
/* 800C6284 000C1184  4E 80 00 20 */	blr 

.global udp_cc_initialize
udp_cc_initialize:
/* 800C6288 000C1188  38 60 FF FF */	li r3, -1
/* 800C628C 000C118C  4E 80 00 20 */	blr 
