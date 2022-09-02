#include "bmp.h"


void show_bmp(char * pathname, int x, int y)
{
	/*打开图片*/
	int picture_fd = open(pathname,O_RDWR);
	if(picture_fd == -1)
	{
		perror("picture open error\n");
	}
	/*测量图片的高度以及宽度*/
	int wide = 0;
	lseek(picture_fd,0x12,SEEK_SET);
	int b = read(picture_fd,&wide,4);
	if(b != 4)
	{
		perror("read wide error\n");
	}
	int height = 0;
	lseek(picture_fd,0x16,SEEK_SET);
	b = read(picture_fd,&height,4);
	if(b != 4)
	{
		perror("read height error\n");
	}
	/*计算宽度的实际字节大小*/
	int realbyte;
	int kd = 0;
	int depth = 24;				//色深一般为24位
	if(wide * depth / 8 % 4)
	{
		realbyte = 4 - wide * depth / 8 % 4 + wide * depth / 8;
		kd = 4 - wide * depth / 8 % 4;
	}
	else
	{
		realbyte = wide * depth / 8;
	}
	/*读取图片内容*/
	unsigned char buf[800*480*3] = {0};
	lseek(picture_fd,54,SEEK_SET);
	b = read(picture_fd,buf,realbyte*height);
	if(b != realbyte*height)
	{
		perror("read picture error\n");
	}
	/*图片转化并将其写入LCD屏幕中*/
	unsigned char a = 0;
	int color = 0;
	int num = 0;
	int i,j;
	for(i = 0 ; i < height ; i++)
	{
		for(j = 0 ; j < wide ; j++)
		{
			color = a << 24 | buf[num + 2] << 16 | buf[num +  1] << 8 | buf[num + 0];
			num = num + 3;
			draw_point(x + j, y + height - 1 - i,color);
		}
		num = num + kd;
	}
	close(picture_fd);
}