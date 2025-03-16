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
	
flash:
	//第2步，LED灯3亮，4、5灭
	ldr r0, =((0 << 3) | (1 << 4) | (1 << 5))
	ldr r1, =GPJ0DAT
	str r0, [r1]
	//延迟
	bl delay
	
	//第3步，LED灯4亮，3、5灭
	ldr r0, =((1 << 3) | (0 << 4) | (1 << 5))
	ldr r1, =GPJ0DAT
	str r0, [r1]
	//延迟
	bl delay
	
	//第4步，LED灯5亮，3、4灭
	ldr r0, =((1 << 3) | (1 << 4) | (0 << 5))
	ldr r1, =GPJ0DAT
	str r0, [r1]
	//延迟
	bl delay
	b flash
	
delay:
	ldr r2, =0x900000
	ldr r3, =0x0
delay_loop:
	cmp r2, r3
	sub r2, r2, #1
	bne delay_loop
	mov pc, lr
