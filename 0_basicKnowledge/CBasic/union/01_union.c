/*
* 公司：中软国际有限公司
* 作者：周建伟
* 项目：C语言中共用体(联合体)初始化方式
* 目的：初步了解共用体的初始化
*/
#include <stdio.h>

//共用体类型只有一个数据，可以按照不同的类型去解析它，例如用char类型来查看int类型数据的高字节和低字节。
#if 0
union MyUnion
{
	int a;
	char b;
};

int main(void)
{
	union MyUnion u;
	
	
	return 0;
}
#elif 1
struct Male
{
	char name[20];
	int age;
	int basketbalScore;
};

struct Female
{
	char name[20];
	int age;
	int baleiScore;
};

union Human
{
	struct Male m;
	struct Female f;
};

int main(void)
{
	union Human h;
	h.f.baleiScore = 82;
	h.m.basketbalScore = 56;
	printf("name: %s, age: %d, basketbalScore: %d\n", h.m.name, h.m.age, h.m.basketbalScore);
	
	return 0;
}
#endif