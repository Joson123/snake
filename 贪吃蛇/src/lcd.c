#include "lcd.h"
int *plcd = NULL;
int lcd_fd = 0;
/*
	lcd初始化函数
*/
void lcd_init()
{
	lcd_fd = open("/dev/fb0",O_RDWR);
	if(lcd_fd == -1)
	{
		perror("open lcd error\n");
	}
	plcd = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE,MAP_SHARED,lcd_fd,0);
}
/*
	画点函数
	@x:画点的x坐标
	@y:画点的y坐标
	@color:画点的颜色
*/
void draw_point(int x, int y, int color)
{
	*(plcd + 800 * y + x) = color;
}

/*
	lcd解初始化
*/
void unlcd_init()
{
	
	int a = munmap(plcd,800*480*4);
	if(a == -1)
	{
		perror("munmap lcd error\n");
	}
	a = close(lcd_fd);
	if(a == -1)
	{
		perror("close lcd error\n");
	}
}