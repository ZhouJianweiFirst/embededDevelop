#ifndef __COMPUTER_H__
#define __COMPUTER_H__

typedef int (*pFunc)(int, int);

struct Comput
{
	int a;
	int b;
	char c;
	pFunc pf;
};

void computer(struct Comput *st);
#endif		//__COMPUTER_H__