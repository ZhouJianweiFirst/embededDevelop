/*
* 公司：中软国际有限公司
* 作者：周建伟
* 项目：C语言函数演示
* 题目：计算器
*/

#include <stdio.h>

//函数声明
int add(int a, int b);
int sub(int a, int b);
int multi(int a, int b);
int devide(int a, int b);

//函数定义，也叫函数实现
int add(int a, int b)
{
	return a + b;
}

//函数定义，也叫函数实现
int sub(int a, int b)
{
	return a - b;
}

//函数定义，也叫函数实现
int multi(int a, int b)
{
	return a * b;
}

//函数定义，也叫函数实现
int devide(int a, int b)
{
	return a / b;
}

int main(void)
{
	int a, b;
	int c, d, e, f;
	
	a = 15;
	b = 3;
	
	c = add(a, b);
	d = sub(a, b);
	e = multi(a, b);
	f = devide(a, b);
	
	
	printf("a add b = %d.\n", c);
	printf("a sub b = %d.\n", d);
	printf("a multiply b = %d.\n", e);
	printf("a devide b = %d.\n", f);
	
	return 0;
}