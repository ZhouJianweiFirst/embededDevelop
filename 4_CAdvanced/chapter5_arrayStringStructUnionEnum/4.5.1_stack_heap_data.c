#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int func1(void)
{
	
	char *p = (char*)malloc(10 * sizeof(char));
	if(NULL == p)
	{
		printf("get memory from malloc failur.\n");
		return -1;
	}
	memset(p, 0, 10 * sizeof(char));
	strcpy(p, "hello");
	printf("heap: &p = %p.\n", p);
	printf("p = %s.\n", p);
	free(p);
	p = NULL;
	return 0;
}
int b = 0;
int c = 10;
int main(void)
{
	int a = 20;		//栈空间变量
	printf("stack:	 &a = %p.\n", &a);
	printf("data: 	 &b = %p.\n", &b);
	printf("bss:	 &c = %p.\n", &c);
	int t = func1();
	if(-1 == t)
	{
		return -1;
	}
	
	return 0;
}