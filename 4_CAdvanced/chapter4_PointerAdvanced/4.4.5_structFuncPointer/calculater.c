#include "computer.h"
#include <stdio.h>

int addF(int a, int b);
int subF(int a, int b);
int multiF(int a, int b);
int dividF(int a, int b);

int main(void)
{
	int a = 0, b = 0;
	struct Comput comput;
	char c;
	printf("please enter two number: \n");
	scanf("%d%d", &comput.a, &comput.b);
	printf("please choose + | - | * | /\n");
	
	do
	{
		scanf("%c", &comput.c);
	}while(comput.c == '\n');
	
	printf("comput.a = %d, comput.b = %d, comput.c = :%d\n", comput.a, comput.b, comput.c);
	
	
	switch(comput.c)
	{
		case '+':
		comput.pf = addF;
		break;
		case '-':
		comput.pf = subF;
		break;
		case '*':
		comput.pf = multiF;
		break;
		case '/':
		comput.pf = dividF;
		break;
		default:
		comput.pf = NULL;
		break;
	}
	
	computer(&comput);
	
}

int addF(int a, int b)
{
	return a + b;
}

int subF(int a, int b)
{
	return a - b;
}

int multiF(int a, int b)
{
	return a * b;
}

int dividF(int a, int b)
{
	return a / b;
}