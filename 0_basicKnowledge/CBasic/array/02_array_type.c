/*
* 公司：中软国际有限公司
* 作者：周建伟
* 项目：数组类型
*/
#include <stdio.h>

int main(void)
{
	int i = 0;
	int a[5] = {};
	float b[5] = {};
	double c[5] = {};
	char d[5] = {};
	short e = 0;
	long long f = 0;
	int len = 0;
	
	/* for(i=0; i<5; i++)
	{
		printf("a[%d] = %d.\n", i, a[i]);
		printf("b[%d] = %f.\n", i, b[i]);
		printf("c[%d] = %f.\n", i, c[i]);
		printf("d[%d] = %d.\n", i, d[i]);
	} */
	
	len = sizeof(a) / sizeof(a[0]);			//计算数组中有多少个数组元素
	printf("sizeof(a) = %d.\n", sizeof(a));
	printf("length of a = %d.\n", len);
	
	return 0;
}