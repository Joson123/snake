#include "touch.h"
int touch_fd = 0;
/*
	触摸屏解初始化
*/
void touch_init()
{
	touch_fd = open("/dev/input/event0",O_RDWR);
	if(touch_fd == -1)
	{
		perror("open touch error\n");
	}
}
/*
	触摸屏
*/
int touch_dik(int flag)
{
	struct input_event ev;
	int x,y;
	while(1)
	{
		int ret = read(touch_fd,&ev,sizeof(ev));
		if(ret != sizeof(ev))
		{
			continue;
		}
		if(ev.type == EV_ABS && ev.code == ABS_X)
		{
			x = ev.value;
		}
		if(ev.type == EV_ABS && ev.code == ABS_Y)
		{
			y = ev.value;
		}
		if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value != 0)	//按下去的状态
		{
			if(x >= 820 && x <= 910 && y >= 330 && y <= 390 && flag == 1)  		//向上方向键
			{
				return 1;
			}
			else if(x >= 820 && x <= 910 && y >= 500 && y <= 600 && flag == 1)	//向下方向键
			{
				return 2;
			}
			else if(x >= 730 && x <= 800 && y >= 410 && y <= 490 && flag == 1)	//向左方向键
			{
				return 3;
			}
			else if(x >= 920 && x <= 1000 && y >= 410 && y <= 490 && flag == 1)	//向右边方向键
			{
				return 4;
			}
			if(x && y && flag == 0)
			{
				return 6;
			}
			/*else if(x >= 820 && x <= 910 && y >= 410 && y <= 490)   //中间方向键
			{
				return 5;
			}*/
		}
		/*if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0) //弹起来的状态
		{
		}*/
	}
}