#include "computer.h"
#include <stdio.h>

void computer(struct Comput *st)
{
	int t = st->pf(st->a, st->b);
	printf("%d %c %d = %d\n", st->a, st->c, st->b, t);
}