/*
* 公司：中软国际有限公司
* 作者：周建伟
* 项目：循环结构示例演示
* 题目：打印ascii码
*/
#include <stdio.h>

int main(void)
{
	int i;
	
	printf("========ASCII========\n");
	for(i=0; i<128; i++)
	{
		printf("%d               %c.\n", i, i);
	}
	printf("========ASCII========\n");
	
	return 0;
}