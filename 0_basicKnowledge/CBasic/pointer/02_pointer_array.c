/*
* 公司：中软国际有限公司
* 作者：周建伟
* 项目：C语言中指针与数组的结合
* 目的：如何使用指针指向数组
*/
#include <stdio.h>

int main(void)
{
	int a[5] = {8, 2, 4, 1, 6};
	float b[5] = {5.26, 2.00, 3.26, 6.21, 1.02};
	double c[5] = {6.3526, 2.3652, 1.0325, 2.0365, 1.3652};
	char d[] = "china";
	
	int i = 0;
	int *pInt;
	float *pFloat;
	double *pDouble;
	char *pChar;
	
	//pInt = &a;
	// = a;
	pInt = a;
	pFloat = b;
	pDouble = c;
	pChar = d;
	
	printf("=================================================================================\n");
	for(i=0; i < 5; i++)
	{
		printf("(pInt + %d) = %p		*(pInt + %d) = %d.\n", i, (pInt++), i, *(pInt)); 
	}
	printf("\n=================================================================================\n");
	for(i=0; i < 5; i++)
	{
		printf("(pFloat + %d) = %p		*(pFloat + %d) = %f.\n", i, (pFloat + i), i, *(pFloat + i)); 
	}
	printf("\n=================================================================================\n");
	for(i=0; i < 5; i++)
	{
		printf("(pDouble + %d) = %p		*(pDouble + %d) = %lf.\n", i, (pDouble + i), i, *(pDouble + i)); 
	}
	printf("\n=================================================================================\n");
	for(i=0; i < 5; i++)
	{
		printf("(pChar + %d) = %p		*(pChar + %d) = %c.\n", i, (pChar + i), i, *(pChar + i)); 
	}
	
	return 0;
}