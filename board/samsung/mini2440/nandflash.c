/*************************************************************************
 * File Name: sdram.c
 * Author: renwei
 * Mail: renweiaust@163.com 
 * Created Time: Mon 16 Nov 2015 09:42:58 PM CST
 ************************************************************************/

#define NFCONF		        (*(volatile unsigned long *)0x4e000000)	//nand falsh配置寄存器
#define NFCONT		        (*(volatile unsigned long *)0x4e000004)	//nand flash控制寄存器
#define NFCMD		        (*(volatile unsigned long *)0x4e000008)	//nand flash命令寄存器
#define NFADDR		        (*(volatile unsigned long *)0x4e00000C) //nand flash地址寄存器
#define NFDATA		        (*(volatile unsigned char *)0x4e000010)	//nand flash数据寄存器
#define NFSTAT		        (*(volatile unsigned long *)0x4e000020) //nand flash状态寄存器

void nand_flash_init();

#define enable_flash() \
{\
	NFCONT = 1; \
}

#define disable_flash() \
{\
	NFCONT = 0;\
}

int nand_readpage(unsigned long pagenum,char *dst_buf)
{
		int i;
		unsigned long j;
	
		nand_flash_init();
		enable_flash();

		for(j = 0; j < pagenum;j ++)
		{	

			NFCMD = 0x00;

			NFADDR = 0x00;
			NFADDR = 0x00;

			NFADDR = (j)&0xff;
			NFADDR = (j>>8)&0xff;
			NFADDR = (j>>16)&0x01;
		
			NFCMD = 0x30;

			while(!(NFSTAT&(1<<0)));

			for(i=0; i<2048; i++)
			{
				dst_buf[i + j * 2048] =NFDATA;
			}
		}
		disable_flash();
		return 0;

}

void nand_flash_init()
{
	NFCONF = (0 << 12) | (1 << 8);

	NFCONT = (1<<4);

	NFSTAT = 0;
}


