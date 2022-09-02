#include "game.h"

int score = 0;
int changeflag = 0;
int key;
int key_pre;
pthread_mutex_t mutex;
void ev_init()
{
	int i,j;
	/*画墙*/
	for(i = 0 ; i < 800 ; i++)
	{
		for(j = 0 ; j < 480 ; j++)
		{
			if((i >= 550 && i <= 560) || (i >= 0 && i <= 10) || (j >= 0 && j <= 10 && i <=560) || (j >= 470 && j < 480 )&& i <= 560)
			{
				draw_point(i,j,0xFF000000);
			}
			else
			{
				draw_point(i,j,0xFFA0522D);
			}
		}
	}
	/*绘制方向盘*/
	show_bmp("./1.bmp",580,260);
	/*绘制环境按钮*/
	show_bmp("./3.bmp",580,40);
	/*随机数生成食物的坐标*/
	while(1)
	{
		srand(time(NULL));
		food.x = (rand() % (wallwide / 10)) * 10 ;
		food.y = (rand() % (wallheight /10)) * 10 ;
		if(food.x > 10 && food.y > 10 && food.x < 550 && food.y < 470)
		{
			break;
		}
	}
	printf("food x:%d\n",food.x);
	printf("food y:%d\n",food.y);
	/*随机生成食物*/
	for(i = 20 ; i < 540 ; i++)
	{
		for(j = 20 ; j < 460 ; j++)
		{
			if((i - food.x) * (i - food.x) + (j - food.y) * (j - food.y) <= 25)
			{
				draw_point(i,j,0xFFFF0000);
			}
		}
	}
	/*初始化蛇的属性*/
	snake.len = 3;		
	snake.speed = 200;
	snake.x[0] = wallheight / 2 ;
	snake.y[0] = wallwide / 2;
	for(int a = snake.x[0] - 5 ; a < snake.x[0] + 5 ; a++)
	{
		for(int b = snake.y[0] - 5; b < snake.y[0] + 5; b++)
		{
			draw_point(a,b, 0xFF00F5FF);
		}
	}
	/*初始化蛇的位置*/
	for(i = 1 ; i < snake.len ; i++)
	{
		snake.x[i] = snake.x[i - 1] + 10;
		snake.y[i] = snake.y[i - 1] + 10;
		for(int a = snake.x[i] - 5 ; a < snake.x[i] + 5 ; a++)
		{
			for(int b = snake.y[i] - 5; b < snake.y[i] + 5; b++)
			{
				draw_point(a,b, 0xFF00F5FF);
			}
		}
	}
}
/*
	创造食物
*/
void cread_food()
{
	if(snake.x[0] == food.x  && snake.y[0] == food.y )
	{
		//printf("aaa\n");
		while(1)
		{		
			int flag = 1;	
			srand(time(NULL));
			food.x = (rand() % (wallwide / 10)) * 10 ;
			food.y = (rand() % (wallheight /10)) * 10 ;
			for(int i = 0 ; i < snake.len ; i++)
			{
				if(snake.x[i] == food.x && snake.y[i] == food.y)
				{
					//printf("cccc\n");
					flag = 0;
					break;
				}
			}
			if(food.x <= 10 || food.y <= 10 || food.x >= 550 || food.y >= 470 )
			{
				flag = 0;
			}
			if(flag == 1)
			{
				printf("cread food\n");
				//printf("ssss\n");
				break;
			}
		}
		printf("food x:%d\n",food.x);
		printf("food y:%d\n",food.y);
		int i,j;
		for(i = 20 ; i < 540 ; i++)
		{
			for(j = 20 ; j < 460 ; j++)
			{
				if((i - food.x) * (i - food.x) + (j - food.y) * (j - food.y) <= 25)
				{
					draw_point(i,j,0xFFFF0000);
				}
			}
		}
		//score += 10;
		//snake.speed -= 5;
		changeflag = 1;
		snake.len ++;
	}
}

void *pthread_move(void * arg)
{
	while(1)
	{
		
		if(changeflag == 0)
		{
			for(int i = snake.x[snake.len - 1] - 5 ; i < snake.x[snake.len -1] + 5 ; i++)
			{
				for(int j = snake.y[snake.len - 1] - 5 ; j < snake.y[snake.len -1] + 5 ; j++)
				{
					draw_point(i,j,0xFFA0522D);
				}
			}
		}
		for(int i = snake.len ; i>0 ; i--)
		{
			snake.x[i] = snake.x[i - 1];
			snake.y[i] = snake.y[i - 1];
		}
		left_move();
		up_move();
		down_move();
		right_move();
		for(int i = snake.x[0] - 5; i < snake.x[0] + 5 ; i++)
		{
			for(int j = snake.y[0] - 5; j < snake.y[0] + 5 ; j++)
			{
				draw_point(i,j, 0xFF00F5FF);
			}
		}
		printf("x:%d\n",snake.x[0]);
		printf("y:%d\n",snake.y[0]);
		changeflag = 0;
		//cread_food();
		sleep(1);
		
	}
}
void left_move()
{
		/*if(changeflag == 0)
		{
			for(int i = snake.x[snake.len - 1] - 5 ; i < snake.x[snake.len -1] + 5 ; i++)
			{
				for(int j = snake.y[snake.len - 1] - 5 ; j < snake.y[snake.len -1] + 5 ; j++)
				{
					draw_point(i,j,0xFFA0522D);
				}
		}
			for(int i = snake.len ; i>0 ; i--)
			{
				snake.x[i] = snake.x[i - 1];
				snake.y[i] = snake.y[i - 1];
			}
		}*/
	if(key == 3)
	{
		snake.x[0] = snake.x[0] - 10;
	}
}
void up_move()
{
	if(key == 1)
	{
		snake.y[0] = snake.y[0] - 10;
	}
}
void down_move()
{
	if(key == 2)
	{
		snake.y[0] = snake.y[0] + 10;
	}
}
void right_move()
{
	if(key == 4)
	{
		snake.x[0] = snake.x[0] + 10;
	}
}
/*
	按键控制方向
*/
void key_down()
{
	pthread_t pthread_id;
	key_pre = key;

	/*	for(int i = snake.x[snake.len - 1] - 5 ; i < snake.x[snake.len -1] + 5 ; i++)
		{
			for(int j = snake.y[snake.len - 1] - 5 ; j < snake.y[snake.len -1] + 5 ; j++)
			{
				draw_point(i,j,0xFFA0522D);
			}
		}

	for(int i = snake.len ; i>0 ; i--)
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}*/
	pthread_create(&pthread_id,NULL,pthread_move,NULL);
	key = touch_dik(1);
	
	if(key_pre == 1 && key == 2)
	{
		key = 1;
	}
	if(key_pre == 2 && key == 1)
	{
		key = 2;
	}
	if(key_pre == 3 && key == 4)
	{
		key = 3;
	}
	if(key_pre == 4 && key == 3)
	{
		key = 4;
	}
	/*switch(key)
	{
		case 1:					              //向上
			snake.y[0] = snake.y[0] - 10;
			break;
		case 2:
			snake.y[0] = snake.y[0] + 10;		//向下
			break;
		case 3:
			snake.x[0] = snake.x[0] - 10;	//向左
			break;
		case 4:
			snake.x[0] = snake.x[0] + 10;	//向右 
			break;
	}*/
	/*printf("x:%d\n",snake.x[0]);
	printf("y:%d\n",snake.y[0]);*/
	/*for(int i = snake.x[0] - 5; i < snake.x[0] + 5 ; i++)
	{
		for(int j = snake.y[0] - 5; j < snake.y[0] + 5 ; j++)
		{
			draw_point(i,j, 0xFF00F5FF);
		}
	}*/
}

/*
	游戏结束判断
	函数返回值
				1 游戏正常
				0 游戏结束
*/
int game_over()
{
	if(snake.x[0] == 550 || snake.x[0] == 10)		//碰到左右墙
	{
		return 0;
	}
	if(snake.y[0] == 470 || snake.y[0] == 10)		//碰到上下墙
	{
		return 0;
	}
	for(int i = 1 ; i < snake.len ; i++)
	{
		if(snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i])	//碰到自身
		{
			return 0;
		}
	}
	return 1;
}
void start_game()
{
	while(1)
	{
		key_down();
		/*if(game_over() == 0)
		{
			break;
		}*/
		cread_food();
		//sleep(1);
	}
}

