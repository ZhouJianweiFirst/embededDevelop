#include <stdio.h>
#include <string.h>

int main(void)
{
	char *p = "linux";		//p是一个指针变量，没有存放字符串的空间，因此编译器在代码段开辟空间存放字符串，将存放字符串空间的首地址给了字符指针p，C语言没有原生的字符串，通过字符串首地址和结束标志‘\0’来表示字符串的，首地址和结束标志中间的内存空间是连续的。
	char a[] = "linux";		//编译器首先在栈空间给一个空间，用以存放linux这个字符串的内容，也就是a[0]=l, a[1]=i, a[2]=n, a[3]=u, a[4]=x, a[5]='\0'.给字符数组赋值之后，字符串“linux”就不见了。
	
	printf("p+1 = %s.\n", p+1);
	printf("a = %s.\n", a);
	printf("sizeof(p) = %d.\n", sizeof(p));
	printf("sizeof(a) = %d.\n", sizeof(a));		//结束符'\0'也属于数组元素，所以sizeof（a） = 6.
	printf("strlen(a) = %d.\n", strlen(a));		//结束符'\0'不属于字符串的内容，所以strlen（a）=5.
	
	return 0;
}