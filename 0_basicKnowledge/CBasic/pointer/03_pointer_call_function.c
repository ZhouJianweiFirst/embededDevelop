/*
* 公司：中软国际有限公司
* 作者：周建伟
* 项目：C语言中指针与函数传参的结合
* 目的：理解指针进行传参的实质
*/
#include <stdio.h>


/* void SwapValue(int x, int y)
{
	int tmp = x;
	
	x = y;
	y = tmp;
	printf("SwapValue: x = %d, y = %d.\n", x, y);	
} */

void SwapValue(int *px, int *py)
{
	int tmp = 0;
	
	tmp = *px;
	*px = *py;
	*py = tmp;
	printf("SwapValue: *px = %d, *py = %d.\n", *px, *py);	
}
int main(void)
{
	int x = 5, y = 9;
	
	printf("before swap: x = %d, y = %d.\n", x, y);
	SwapValue(&x, &y);
	printf("after swap: x = %d, y = %d.\n", x, y);
	
	
	return 0;
}