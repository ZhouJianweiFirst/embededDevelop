#define SD_START_ADDR	45				//��ʼ������
#define SD_BLOCK_CNT		32				//��ȡ��������
#define DDR_START_ADDR		0x23E00000		//��ȡBL2��DDR�ĵ�ַ	uboot������д��23E00000��ַ���ˣ���������Ҳ����23E00000����ʵSD��������0x20000000~0x2fffffff������ʹ��

typedef unsigned int bool;
typedef bool(*pCopySDMMC2Mem)(int, unsigned int, unsigned short, unsigned int*, bool);
typedef void (*pBL2_in_ddr)(void);


void copy_bl2_2_ddr_mem(void)
{
	//��һ������ȡSD��������BL2��DDR
	pCopySDMMC2Mem pFunc = (pCopySDMMC2Mem)(*(unsigned int *)0xD0037F98);	//0xD0037F98��ŵ���ROM�д洢�Ķ�ȡSD/MMCBL2��DDR�ĺ����ĺ�����ַ����ŵ�λ�ã�
	//ͨ��0xD0037F98�����ַ������ݣ�����ָ���ȡSD/MMC����ĺ�����
	//��SD����BL2���뿽����DDR��DDR_START_ADDR��ַ��
	pFunc(2, SD_START_ADDR, SD_BLOCK_CNT, (unsigned int *)DDR_START_ADDR, 0);
	
	//�ڶ�������ת��DDR
	pBL2_in_ddr BL2_DDR = (pBL2_in_ddr)DDR_START_ADDR;
	BL2_DDR();
}
