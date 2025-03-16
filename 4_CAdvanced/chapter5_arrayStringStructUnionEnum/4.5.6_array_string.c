#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mystrlen(char *p)
{
	int cnt = 0;
	while('\0' != *p++)
	{
		cnt++;
	}
	
	return cnt++;
}
char a3[] = "linux";

int main(void)
{
	//字符存在栈上
	char a[] = "linux";
	char *p1 = a;
	
	//字符串存在堆上
	char *p2 = (char *)malloc(10 * sizeof(char));
	memset(p2, 0, 10 * sizeof(char));
	strcpy(p2, "linux");
	
	//字符串存在数据段上
	char *p3 = a3;
	
	printf("p1 = %s.\n", p1);
	printf("p2 = %s.\n", p2);
	printf("p3 = %s.\n", p3);
	printf("======================================================\n");
	printf("p1 = %p.\n", p1);
	printf("p2 = %p.\n", p2);
	printf("p3 = %p.\n", p3);
	
	/* char a[] = "linuxdatas";
	char *p = "linux";
	
	printf("strlen(p) = %d.\n", strlen(p));
	printf("p = %s.\n", p);
	
	printf("mystrlen(p) = %d.\n", mystrlen(p));
	printf("p = %s.\n", p); */
	
	
	/* int l = strlen(a);
	printf("sizeof(a) = %d.\n", sizeof(a));
	printf("strlen(a) = %d.\n", strlen(a));		//size_t strlen(const char *s);
	printf("a[l] = %d.\n", a[l]); */
	
	return 0;
}