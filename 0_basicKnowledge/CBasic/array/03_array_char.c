/*
* 公司：中软国际有限公司
* 作者：周建伟
* 项目：字符数组
*/
#include <stdio.h>

int main(void)
{
	char a[5] = {'0', 'a', 'A', 'B', 'C'};		//完全初始化
	char b[5] = {48, 97, 65, 66, 67};
	char c[] = {};
	char d[] = "hello";
	int i = 0;
	
	printf("number of array c = %d.\n", sizeof(c) / sizeof(c[0]));		//计算数组c的元素个数
	for(i = 0; i < 5; i++)
	{
//		printf("a[%d] = %d		%c.\n", i, a[i], a[i]);
//		printf("b[%d] = %d		%c.\n", i, b[i], b[i]);
		printf("c[%d] = %d		%c.\n", i, c[i], c[i]);
		//printf("d[%d] = %d		%c.\n", i, d[i], d[i]);
	}
}