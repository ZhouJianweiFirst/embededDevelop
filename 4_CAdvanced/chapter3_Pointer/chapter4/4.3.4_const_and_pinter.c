#include <stdio.h>

void strcpy(char a[], char b[])
{
	int i = 0;
	
	while((a[i] = b[i]) != '\0')
	{
		i += 1;
	}
	
}
int main(void)
{
	/* int a = 1, b = 2, c = 3, d = 4;
	
	const int *p1 = &a;			//指向const int型的指针，指针变量指向的int变量无法修改
	int const *p2 = &b;			//指向const int型的指针，指针变量指向int型的值，指向的值无法修改。
	int * const p3 = &c;			//指向int型的const指针，指针变量存储的地址无法修改
	const int * const p4 = &d;	//指向const int型的const指针，指针变量存储的地址以及地址存储的值均无法修改
	
	if(NULL != p4)
	{
		*p4 = 2;
	}
	p4 = p2; */
	
	char y[] = "tiger!";
	char x[10];
	strcpy(x, y);
	
	printf("y = %c\n", x[0]);
	
	
	return 0;
}