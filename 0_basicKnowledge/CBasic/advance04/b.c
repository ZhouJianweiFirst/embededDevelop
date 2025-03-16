/*
* 公司：中软国际股份有限公司
* 作者：周建伟
* 项目：跨文件操作
*/
#include <stdio.h>

static void func_static_arg(void);
static g_arg = 'b';

int g_a = 'A';
int g_b = '0';

void func_y(void)
{
	static int yy = 0;
	
	printf("i am fun_y in b.c.\n");
	yy++;
	printf("i am local static arguement yy in b.c: %d.\n", yy);
	func_static_arg();
	printf("i am static global arguement in b.c: %d.\n", g_arg);
}

static void func_static_arg(void)
{
	printf("i am static function in b.c.\n");
}