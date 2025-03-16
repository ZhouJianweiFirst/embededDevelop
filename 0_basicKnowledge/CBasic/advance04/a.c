/*
* 公司：中软国际股份有限公司
* 作者：周建伟
* 项目：跨文件操作
*/
#include <stdio.h>

void func_x(void);
void func_y(void);
static void func_static_arg(void);		//静态全局变量的作用就是防止多文件中有重名函数/全局变量，告诉编译器static修饰的函数/全局变量只在定义的文件中使用
static g_arg = 'B';

extern int g_a;
extern int g_b;

int main(void)
{
	func_x();
	func_y();
	
	printf("g_a = %d.\n", g_a);
	printf("g_b = %d.\n", g_b);
	
	func_static_arg();
	
	printf("i am static global arguement in a.c: %d.\n", g_arg);
	
	return 0;
}

void func_x(void)
{
	printf("i am fun_x in a.c.\n");
}


static void func_static_arg(void)
{
	printf("i am static function in a.c.\n");
}
