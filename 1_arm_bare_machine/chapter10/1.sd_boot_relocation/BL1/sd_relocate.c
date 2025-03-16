#define SD_START_ADDR	45				//开始扇区号
#define SD_BLOCK_CNT		32				//读取扇区个数
#define DDR_START_ADDR		0x23E00000		//读取BL2到DDR的地址	uboot代码是写到23E00000地址里了，于是这里也采用23E00000，其实SD卡分区的0x20000000~0x2fffffff都可以使用

typedef unsigned int bool;
typedef bool(*pCopySDMMC2Mem)(int, unsigned int, unsigned short, unsigned int*, bool);
typedef void (*pBL2_in_ddr)(void);


void copy_bl2_2_ddr_mem(void)
{
	//第一步，读取SD卡扇区的BL2到DDR
	pCopySDMMC2Mem pFunc = (pCopySDMMC2Mem)(*(unsigned int *)0xD0037F98);	//0xD0037F98存放的是ROM中存储的读取SD/MMCBL2到DDR的函数的函数地址所存放的位置，
	//通过0xD0037F98这个地址里的内容，可以指向读取SD/MMC代码的函数。
	//将SD卡的BL2代码拷贝到DDR的DDR_START_ADDR地址处
	pFunc(2, SD_START_ADDR, SD_BLOCK_CNT, (unsigned int *)DDR_START_ADDR, 0);
	
	//第二步，跳转到DDR
	pBL2_in_ddr BL2_DDR = (pBL2_in_ddr)DDR_START_ADDR;
	BL2_DDR();
}
