/*
* 公司：中软国际有限公司
* 作者：周建伟
* 项目：指针使用示例
*/
#include <stdio.h>

int main(void)
{
	int a = 20;
	int *p;
	
	p = &a;
	
	printf("a = %d, *p = %d\n&a = %p, p = %p.\n", a, *p, &a, p);
	
	*p = 62;
	printf("a = %d, *p = %d.\n", a, *p);
	
	return 0;
}