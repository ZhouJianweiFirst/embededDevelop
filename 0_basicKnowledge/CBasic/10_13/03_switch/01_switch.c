/*
* 公司：中软国际有限公司
* 作者：周建伟
* 项目：结构化设计--选择结构示例演示
* 题目：输入1打印a，输入2打印b，以此类推，知道输入7打印g
*/
#include <stdio.h>

int main(void)
{
	int num;
	
	num = 8;
	
	switch(num)
	{
		case 1:
			printf("a\n");
			break;
		case 2:
			printf("b\n");
			break;
		case 3:
			printf("c\n");
			break;
		case 4:
			printf("d\n");
			break;
		case 5:
			printf("e\n");
			break;
		case 6:
			printf("f\n");
			break;
		case 7:
			printf("g\n");
			break;
		default:
			printf("==========\n");
			break;
	}
}