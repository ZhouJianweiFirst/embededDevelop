/*
* 公司：中软国际有限公司
* 作者：周建伟
* 项目：C语言中结构体初始化方式
* 目的：初步了解结构体的初始化
*/
#include <stdio.h>

struct Student
{
	char name;
	int num;
	int age;
	float heigh;
	double score;
};

int main(void)
{
	//struct Student stu = {'K', 100, 32, 173.5, 96.75};		//完全初始化
	struct Student stu = {.name = 't', .num = 101, .age = 19, .score = 96.15};		//不完全初始化
	//struct Student stu = {stu.name = 't', stu.age = 19, stu.heigh = 173.5, stu.score = 96.25};		//不完全初始化
	
	printf("name: %c\nnum: %d\nage: %d\nheigh: %.1f\nscore: %.2f\n", stu.name, stu.num, stu.age, stu.heigh, stu.score);
	
	return 0;
}