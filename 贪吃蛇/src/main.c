#include "bmp.h"
#include "game.h"
int main(int argc,char *argv[])
{
	lcd_init();
	touch_init();
	show_bmp("./2.bmp",0,0);
	touch_dik(0);
	ev_init();
	start_game();
	return 0;
}