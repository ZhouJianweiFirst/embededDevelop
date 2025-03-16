/*
* 公司：中软国际有限公司
* 作者：周建伟
* 项目：C语言中结构体类型
* 目的：初步了解结构体的定义
*/
#include <stdio.h>

//结构体是一种集合了多个元素的一种新的类型，其中的元素数据类型可以相同，也可以不相同
struct Student
{
	char name[20];
	unsigned int num;
	char sex[10];
	int age;
	float score;
};

int main(void)
{
	struct Student stu;
	
	stu.name[0] = 't';
	stu.name[1] = 'o';
	stu.name[2] = 'm';
	stu.name[3] = '\0';
	stu.num = 101;
	stu.sex[0] = 'm';
	stu.sex[1] = 'a';
	stu.sex[2] = 'l';
	stu.sex[3] = 'e';
	stu.sex[4] = '\0';
	stu.age = 28;
	stu.score = 89.5;
	
	printf("name: %s\nnum: %d\nsex: %s\nage: %d\nscore: %.2f\n", stu.name, stu.num, stu.sex, stu.age, stu.score);
	
	return 0;
}