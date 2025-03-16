#include <stdio.h>

int main(void)
{
	int a[5] = {1, 2, 3, 4, 5};
	int *p = a;		//数组名a做右值时表示首元素的首地址，等价于&a[0]；&a表示整个数组的首地址指针，数值和a一样，意义不一样。
	char *pc = (char *)a;
	
	printf("*(p+1) = %d\n", *(p+1));			//p是int型的指针，它的位移是以指针类型的大小为单位移动的，如int *指针变量p + 1就相当于指针移动了sizeof(int)=4个字节。
	printf("*(pc + 4) = %d\n", *(pc + 4));		//pc是char型指针，它的唯一是以sizeof(char)个字节为单位进行移动的。
	printf("*(pc + 5) = %d\n", *(pc + 5));
	printf("*(pc + 6) = %d\n", *(pc + 6));
	printf("*(pc + 7) = %d\n", *(pc + 7));
	
	return 0;
}