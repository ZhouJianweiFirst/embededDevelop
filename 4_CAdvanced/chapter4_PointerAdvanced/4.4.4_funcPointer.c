#include <stdio.h>

typedef int (*pFunc)(int, int);

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

int main(void)
{
	int a = 0, b = 0;
	char c;
	printf("please enter two number: \n");
	scanf("%d%d", &a, &b);
	printf("please choose + | - | * | /\n");
	
	do
	{
		scanf("%c", &c);
	}while(c == '\n');
	
	printf("a = %d, b = %d, c = :%d\n", a, b, c);
	
	pFunc pf = NULL;
	switch(c)
	{
		case '+':
		pf = addF;
		break;
		case '-':
		pf = subF;
		break;
		case '*':
		pf = multiF;
		break;
		case '/':
		pf = dividF;
		break;
		default:
		pf = NULL;
		break;
	}
	
	
	int result = pf(a, b);
	printf("%d %c %d = %d\n", a, c, b, result);
	
	return 0;
}