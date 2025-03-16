#include <stdio.h>
int multip_5(int v)
{
	return v * 5;
}

int multip_5_output(int v, int *pRet)
{
	int tmp = v * 5;
	
	if(tmp > 500)
	{
		return -1;
	}
	else
	{
		*pRet = tmp;
		return 0;
	}
}
int main(void)
{
	char *p = "hello";
	int value = 110;
	int a;
	
	/* a = multip_5(value);
	printf("a = %d.\n", a); */
	
	int t = multip_5_output(value, &a);
	if(-1 == t)
	{
		printf("超出边界了。\n");
	}
	else
	{
		printf("a = %d.\n", a);
	}
	
	return 0;
}