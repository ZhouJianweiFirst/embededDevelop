#include <stdio.h>

int main(void)
{
	int *p = NULL;		//定义指针时赋初值为NULL，表明这个指针目前还是野指针，需要绑定可用的地址。
	
	int a = 34;
	p = &a;			//解引用指针前，一定要绑定绝对可用的地址。
	
	if(NULL != p)		//指针不是野指针时，再对其进行解引用。
	{
		*p = 12;
	}
	printf("a =v%d\n");
	
	p = NULL;		//使用完后，指针赋值NULL，把它变成野指针。防止该指针在其他位置被使用，导致莫名其妙的错误，最终程序崩溃
	
	return 0;
}