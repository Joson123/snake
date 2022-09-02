#ifndef __LCD_H__
#define __LCD_H__
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
void lcd_init();								//lcd初始化
void draw_point(int x,int y,int color);			//画点函数
void unlcd_init();								//lcd解初始化





#endif
