#ifndef __TOUCH_H__
#define __TOUCH_H__
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/input.h>
#include <unistd.h>

void touch_init();				//触摸屏初始化	
int touch_dik(int flag);				//触摸屏点击

#endif
