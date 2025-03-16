/*
* 公司：中软国际有限公司
* 作者：周建伟
* 项目：循环结构示例演示
* 题目：100以内的奇数和
*/
#include <stdio.h>

int main(void)
{
	int i, sum;
	
	for(i=1,sum=0; i<100; i += 2)
	{
//		printf("i = %d\n", i);
		sum += i;
	}
	printf("sum = %d.\n", sum);
	
	return 0;
}