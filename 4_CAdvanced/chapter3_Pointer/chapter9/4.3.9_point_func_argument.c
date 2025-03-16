#include <stdio.h>
struct A
{
	char a;
	int b;
};

void func_struct(struct A a)
{
	printf("&a: %p.\n", &a);
	printf("sizeof(a): %d.\n", sizeof(a));
	printf("a.a: %c.\n", a.a);
	printf("a.b: %d.\n", a.b);
}

void func_point(struct A *ap)
{
	printf("&ap: %p.\n", &ap);
	printf("ap: %p.\n", ap);
	printf("sizeof(ap): %d.\n", sizeof(ap));		//指针大小 4
	printf("sizeof(*ap): %d.\n", sizeof(*ap));		//结构体大小 8
	printf("ap->a: %c.\n", ap->a);					//结构体成员a大小
	printf("ap->b: %d.\n", ap->b);					//结构体成员b大小
}

void swap_value(int a, int b)
{
	int c = a;
	a = b;
	b = c;		//这里交换的a, b是实参赋值的内容，交换这里的ab并不能改变实参
	printf("a: %d, b: %d.\n", a, b);
}
void swap_point(int *p1, int *p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;		//交换实参指针指向变量的值，也就改变了实参变量的值了
	printf("*p1: %d, *p2: %d.\n", *p1, *p2);
}
int main(void)
{
	int v1 = 23;
	int v2 = 86;
	printf("=================before swap============\n");
	printf("v1: %d, v2: %d.\n", v1, v2);
	//swap_value(v1, v2);
	swap_point(&v1, &v2);
	printf("=================after swap============\n");
	printf("v1: %d, v2: %d.\n", v1, v2);
	/*
	struct A as = 
	{
		.a = 65,
		.b = 888
	};
	printf("&as: %p.\n", &as);
	printf("sizeof(as): %d.\n", sizeof(as));
	printf("as.a: %c.\n", as.a);
	printf("as.b: %d.\n", as.b);
	//func_struct(as);		//这里传的是结构体变量as
	func_point(&as);		//这里传的是结构体变量指针&as
	*/
	
	return 0;
}