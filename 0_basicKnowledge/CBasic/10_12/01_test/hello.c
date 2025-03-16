/*
* company: zhongruan
* name:    zjw
* content: print hello 
*/

#include <stdio.h>

int main(int argc, char **argv)
{
	printf("\n    *		\
		\n   ***		\
		\n  *****		\
		\n   ***        	\
		\n    *			\
		\n");

	int a = 1, sum;
	for(a=0,sum=0; a<10; a++)
	{
		sum += a;
	}
	printf("sum = %d\n", sum);
	return 0;
}
