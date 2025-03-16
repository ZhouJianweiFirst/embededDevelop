#include <stdio.h>
#include <string.h>

void func(int *b, int num)
{
	printf("sizeof(b): %d.\n", sizeof(b));		//这时b是指针类型，大小为4字节
	int i = 0;
	for(i=0; i<num; i++)
	{
		printf("b+%d: %p, *(b+%d): %d.\n", i, (b+i), i, *(b+i));
	}
	
}
int main(void)
{
	char str[] = "hello";
	
	printf("sizeof(str): %d.\n", sizeof(str));			//6
	printf("sizeof(str[1]): %d.\n", sizeof(str[1]));	//1
	printf("strlen(str): %d.\n", strlen(str));			//5
	
	char *p = str;
	printf("sizeof(p): %d.\n", sizeof(p));
	printf("sizeof(*p): %d.\n", sizeof(*p));
	printf("strlen(p): %d.\n", strlen(p));
	
	int n = 100;
	int b[5] = {0, 1, 2, 3, 4};
	
	int *p2 = b;		//b表示首元素的首地址
	printf("sizeof(n): %d.\n", sizeof(n));
	printf("sizeof(b): %d.\n", sizeof(b));		//sizeof(数组名)表示整个数组的大小 100*4 = 400byte
	printf("sizeof(p2): %d.\n", sizeof(p2));
	func(b, (sizeof(b)/sizeof(b[0])));	//这里的sizeof(b)/sizeof(b[0])表示数组的元素个数。整个数组所占字节大小/第0个元素所占字节大小
	
	
	
	return 0;
}