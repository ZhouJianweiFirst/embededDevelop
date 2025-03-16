/*
* 公司：中软国际有限公司
* 作者：周建伟
* 项目：C语言静态局部变量与普通变量的区别
* 目的：初步了解静态局部变量
*/

#include <stdio.h>

//static静态局部变量与global都只定义并初始化一次，变量在程序运行期间有效。区别在于作用域不一样，static静态局部变量只在定义该变量的函数体中有效，在文本其他位置无效；而全局变量在文本所有位置均有效

int g_a = 1;

void func_global(void)
{
	g_a += 3;
	printf("g_a = %d.\n", g_a);
}
void func(void)
{
	int i = 1;
	
	i++;
	printf("i = %d.\n", i);
}

void func_static(void)
{
	static int a = 1;		//static定义的变量初始化内容只进行一次，且static修饰的变量在程序运行期间一直存在
	
	a++;
	printf("a = %d.\n", a);
}

void func_static2(void)
{
	static int b = 1;
	
	b += 5;
	printf("b = %d.\n", b);
}

int main(void)
{
	func();
	func();
	func();
	
	func_static();
	func_static();
	func_static();
	
	func_static2();
	func_static2();
	func_static2();
	
	func_global();
	func_global();
	func_global();
	
	return 0;
}