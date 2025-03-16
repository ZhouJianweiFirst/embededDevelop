#include <stdio.h>

typedef struct s1
{
	int age;
	int score;
	int height;
}s1;

typedef struct s2
{
	char sex;
	int age;
	short height;
}s2;

typedef struct s3
{
	int age;
	double height;
}s3;
typedef struct s4
{
	int age;
	int score;
	s3 st3;
}s4;

int main(void)
{
	#if 0
	s1 st1 = {12, 50, 162};
	int *p = (int *)(&st1);
	int *p1 = (int *)((int)(&st1) + 4);
	int *p2 = (int *)((int)(&st1) + 8);
	
	printf("st1.age = %d, *p = %d.\n", st1.age, *p);
	printf("st1.score = %d, *p = %d.\n", st1.score, *p1);
	printf("st1.height = %d, *p = %d.\n", st1.height, *p2);
	
	#elif 0
	
	s2 st2 = {'M', 50, 162};
	char *p = (char *)(&st2);						//p: sex
	char *p3 = (char *)((int)(&st2) + 1);
	int *p1 = (int *)((int)(&st2) + 4);				//p1: age
	short *p2 = (short *)((int)(&st2) + 8);			//p2: height
	
	printf("st2.age = %d, *p1 = %d.\n", st2.age, *p1);
	printf("st2.sex = %c, *p = %c.\n", st2.sex, *p);
	printf("st2.height = %d, *p2 = %d.\n", st2.height, *p2);
	printf("sizeof(s2) = %d.\n", sizeof(s2));
	printf("*p3 = %d.\n", *p3);
	
	#elif 0
	
	s3 st3 = {23, 162.53};
	int *p = (int *)(&st3);
	double *p1 = (double *)((int)(&st3) + 4);
	printf("st3.height = %d, *p = %d.\n", st3.age, *p);
	printf("st3.age = %lf, *p1 = %lf.\n", st3.height, *p1);
	printf("sizeof(s3) = %d.\n", sizeof(s3));
	
	#elif 1
	s4 st4 = {4, 4, {23, 162.53}};
	double *p = (double *)((int)&st4 + 12);
	printf("st4.st3.height = %lf, *p = %lf.\n", st4.st3.height, *p);
	printf("sizeof(s4) = %d.\n", sizeof(s4));
	#endif
	return 0;
}