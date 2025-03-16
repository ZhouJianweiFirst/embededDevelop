/*
* 公司： 中软国际股份有限公司
* 作者： 周建伟
* 项目： 根据学生分数判定为优、良、及格和不及格
*/
#include <stdio.h>

int main(void)
{
	int scale;
	
	scale = 35;
	
	#if 1
	if(scale >= 90)
	{
		printf("excelent!\n");
	}
	else if(scale >= 80)
	{
		printf("good!\n");
	}
	else if(scale >= 80)
	{
		printf("entertainment!\n");
	}
	else
	{
		printf("not good.\n");
	}
	#elif 0
	
	#endif
	
	return 0;
}