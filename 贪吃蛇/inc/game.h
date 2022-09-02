#ifndef __GAME_H__
#define __GAME_H__
#include "bmp.h"
#include <stdlib.h>
#include <time.h>
#include "touch.h"
#include <stdio.h>
#include <pthread.h>

#define wallheight 460
#define wallwide 540
#define snakesize 100
struct snake 
{
	int speed;				//蛇的移动速度
	int len;				//蛇身长
	int	x[snakesize];		//蛇的x的坐标
	int y[snakesize];		//蛇的y的坐标
}snake;
 struct food
{
	int x;
	int y;
}food;

void ev_init();					//环境初始化
void cread_food();				//创造食物
void key_down();				//按键控制方向		
int game_over();				//游戏结束判断
void start_game();				//开始游戏
void *pthread_move(void *arg);			//蛇移动线程
void left_move();				
void up_move();		
void down_move();					
void right_move();


#endif
