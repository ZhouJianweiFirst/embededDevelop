/*
* 公司：中软国际有限公司
* 作者：周建伟
* 项目：结构化设计--do while循环结构示例演示
* 题目：100以内的奇数相加
*/
#include <stdio.h>

int main(void)
{
	int i, sum;
	
	i = 1;
	sum = 0;
	do
	{
		//printf("i = %d.\n", i);
		sum += i;
		i += 2;
	}while(i < 100);
	
	printf("sum = %d.\n", sum);
	
	return 0;
}