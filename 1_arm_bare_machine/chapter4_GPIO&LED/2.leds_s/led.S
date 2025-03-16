/*
*作者：周建伟
*描述：逐步点亮LED灯写的第一个裸机程序
*/
#define GPJ0CON 0xE0200240
#define GPJ0DAT 0xE0200244
.global _start
_start:
//第一步，0x11111111写入到0xE0200240位置
	ldr r0, =0x11111111
	ldr r1, =GPJ0CON
	str r0, [r1]
	
	//第2步，0x0写入到0xE0200244位置
	ldr r0, =((0 << 5) | (1 << 4) | (0 << 3))
	ldr r1, =GPJ0DAT
	str r0, [r1]
	
	b .
