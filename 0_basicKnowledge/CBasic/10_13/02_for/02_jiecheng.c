/*
* 公司：中软国际有限公司
* 作者：周建伟
* 项目：循环结构示例演示
* 题目：10以内的阶乘
*/
#include <stdio.h>

int main(void)
{
	int i, val;
	
	for(i=1,val=1; i<11; i++)
	{
//		printf("i = %d.\n", i);
		val *= i;
	}
	printf("val = %d.\n", val);
	
	return 0;
}