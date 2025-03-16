#include <stdio.h>

int main(void)
{
	int a[3] = {0x11223344, 0x55667788};
	int *pi = a;
	char *pc = (char *)a;
	int i = 0;
	/* printf("*pi = 0x%x.\n", *pi);
	for(i = 0; i < 8; i++)
	{
		printf("*(pc + %d)= 0x%x.\n", i, *(pc + i));
	} */
	printf("sizeof(a): %d.\n", sizeof(a));		//sizeof()这里的大小是以字节为单位的
	printf("sizeof(&a): %d.\n", sizeof(&a));
	printf("sizeof(a[0]): %d.\n", sizeof(a[0]));
	printf("sizeof(a[1]): %d.\n", sizeof(a[1]));
	printf("sizeof(char): %d.\n", sizeof(char));
	printf("sizeof(short): %d.\n", sizeof(short));
	printf("sizeof(int): %d.\n", sizeof(int));
	printf("sizeof(long): %d.\n", sizeof(long));
	printf("sizeof(long long): %d.\n", sizeof(long long));
	printf("sizeof(float): %d.\n", sizeof(float));
	printf("sizeof(double): %d.\n", sizeof(double));
	
	/*
	int a = 0x11223344;		//16进制的数11223344赋值给int型的变量，赋值了十进制的287,454,020
	int *p1 = &a;
	char *p2 = (char *)&a;
	
	printf("*p1 = %d.\n", *p1);		//以10进制方式打印
	printf("*p1 = 0x%x.\n", *p1);	//以16进制方式打印
	printf("*(p2 + 3) = 0x%x.\n", *(p2 + 3));
	*/
	
	/*
	int a = 66666;
	float b = 3.14;
	double c = 2.71828;
	double *pd = &b;
	long *pl = &a;
	
	//printf("a = %d.\n", a);
	
	printf("*pl = %d.\n", *pl);
	*/
	
	return 0;
}