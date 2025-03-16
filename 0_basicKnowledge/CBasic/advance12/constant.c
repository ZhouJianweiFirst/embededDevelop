/*
* 公司：中软国际股份有限公司
* 作者：周建伟
* 项目：C语言中三种常量的演示
*/
#include <stdio.h>

#define N 25
/*
* 1. 宏定义的常量
* 2. const修饰的常量
*    const和指针结合（4种形式）： const int *p; int *const p;int const *p; const int *const p;
*	 const型指针有什么用：char *strcpy(char *dst, const char *src);将src指向的字符串常量(不能修改)复制给dst字符串
* 3. 枚举常量		枚举常量是宏定义的替代品，有时比宏定义好用
*/

enum ClassNum
{
	firstClass,
	secondClass,
	thirdClass,
	fourthClass,
	fifthClass,
};
int main(int argc, char **argv)
{
	int a[N];
	printf("sizeof array a: %d.\n", sizeof(a));
	const int arg = 80;
	printf("i am constant in const: %d.\n", arg);
	printf("i am constant in enum: %d.\n", fifthClass);
	return 0;
}