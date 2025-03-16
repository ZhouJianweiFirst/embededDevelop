//通过宏定义调用函数，优点是使用简单。缺点是宏定义的内容编译时函数的参数无法参与静态类型校验
#define CopySDMMCtoMem(z,a,b,c,e)(((bool(*)(int, unsigned int, unsigned short, unsigned int*, bool))(*((unsigned int *)0xD0037F98)))(z,a,b,c,e))	//直接使用宏定义

//也可以通过函数指针的方式来调用函数
typedef unsigned int bool;
typedef bool(*pCopySDMMC2Mem)(int, unsigned int, unsigned short, unsigned int*, bool);

pCopySDMMC2Mem p1 = pCopySDMMC2Mem(0xD0037F98);
//以下两种方式都可以调用函数
(*p1)(x,x,x,x,x);
p1(x,x,x,x,x);