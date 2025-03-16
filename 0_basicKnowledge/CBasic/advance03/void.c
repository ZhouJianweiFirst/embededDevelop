/*
* 公司：中软国际有限公司
* 作者：周建伟
* 项目：C语言空类型演示
* 目的：初步了解void及void *
*/
#include <stdio.h>

int main(void)
{
	int a = 25;
	void *pVoid;
	
	pVoid = &a;
	//printf("*pVoid = %d.\n", *(int *)pVoid);
	printf("*pVoid = %f.\n", *(float *)pVoid);		//void *可以指向任意数据类型，但读数和取数时的类型必须一致，否则编译器是不会报错的，只能由程序员自己负责。
	
	return 0;
}