/*
* company: chinaSoft COMPANY
* author: zjw
* content: example of if_else
*/

#include <stdio.h>

int selectMax(int a, int b)		//返回两个数中的最大值
{
	return a > b ? a : b;
}

int main(int argc, char **argv)
{
	int a = 83;
	int b = 56;
	int c = 92;
	int max = 0;

	#if 0
	max = selectMax(a, b);
	max = selectMax(max, c);
	
	#elif 1
	if(a > b)
	{
		//a和b比，a较大
		if(a > c)
		{
			max = a;
		}
		else
		{
			max = c;
		}
	}
	else
	{
		//a和b比，b较大
		if(b > c)
		{
			max = b;
		}
		else
		{
			max = c;
		}
	}
	#endif
	printf("max = %d.\n", max);
	
	return 0;
	
}
