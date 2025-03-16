#include <stdio.h>

int main(void)
{
	int a = 21, b = 0, c = 0;
	
	int *p1, *p2;
	p1 = &a;
	p2 = (int *)&p1;		//p2存放了指针变量p1的地址，p2解引用后是一个int型变量，但这个变量实际是p1的地址，所以，强制转换成（int *）指针变量后，可以通过解引用获取指针变量p1解引用后的int型变量值
	
	printf("*p1 = %d, *(int *)(*p2) = %d\n", *p1, *(int *)(*p2));		//*(int * (*p3))
	printf("&p1: %p, p2: %p\n", &p1, p2);
	
	return 0;
}