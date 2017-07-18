#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define TS 15 /* total squares */

WINDOW *create_newwin(int h, int w, int sy, int sx);
void destroy_win(WINDOW *local_win);
void setup();
void logic();
void draw();

struct square
{
	WINDOW *win;
	int w;
	int h;
	int sy;
	int sx;
	int dx;
	int dy;
	int speed;
};

struct square squares[TS];

int main(int argc, char *argv[])
{
	/*
	 * program entry point
	 * args:
	 * 	arg count, arg character array
	 * returns 0 (program success)
	 */
	initscr();
	cbreak();
	noecho();
	curs_set(0); /* hide cursor */
	keypad(stdscr, TRUE);
	setup();
	refresh();
	while(1)
	{
		/* program loop */
		logic();
		draw();
		usleep(50000);
	}
	endwin();
	return 0;
}

void setup()
{
	/*
	 * setup function to initialise arrays, rand() seed etc
	 * args:
	 * 	none
	 * returns nothing
	 */
	/* color pairs */
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(2, COLOR_BLACK, COLOR_BLUE);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	/* seed random generator */
	srand(time(NULL));
	/* set values of each square */
	int x = 0;
	for (x; x < TS; x++)
	{
		squares[x].dx = rand() % 2; /* 0 = left. 1 = right */
		squares[x].dy = rand() % 2; /* 0 = down, 1 = up */
		squares[x].w = 4;
		squares[x].h = 2;
		squares[x].sy = rand() % LINES;
		squares[x].sx = rand() % COLS;
		squares[x].win = create_newwin(squares[x].h, squares[x].w, squares[x].sy, squares[x].sx);
		wbkgd(squares[x].win, COLOR_PAIR(rand() % 3 + 1));
		squares[x].speed = rand() % 2 + 1;
	}
}

void logic()
{
	/*
	 * logic for the squares
	 * args:
	 * 	none
	 * returns nothing
	 */
	int x = 0;
	for (x; x < TS; x++)
	{
		if (squares[x].dx == 1)
			squares[x].sx += squares[x].speed;
		if (squares[x].dx == 0)
			squares[x].sx -= squares[x].speed;
		if (squares[x].dy == 1)
			squares[x].sy -= squares[x].speed;
		if (squares[x].dy == 0)
			squares[x].sy += squares[x].speed;

		if (squares[x].sx + squares[x].w >= COLS)
			squares[x].dx = 0;
		if (squares[x].sx <= 0)
			squares[x].dx = 1;
		if (squares[x].sy + squares[x].h >= LINES)
			squares[x].dy = 1;
		if (squares[x].sy <= 0)
			squares[x].dy = 0;
	}
}

void draw()
{
	/* draws our screen
	 * args:
	 * 	none
	 * returns nothing
	 */
	int x = 0;
	wclear(stdscr);
	refresh();
	/* draw each square */
	for (x; x < TS; x++)
	{
		mvwin(squares[x].win, squares[x].sy, squares[x].sx);
		wrefresh(squares[x].win);
	}
}

WINDOW *create_newwin(int h, int w, int sy, int sx)
{
	/* 
	 * create a new window
	 * args:
	 * 	height, width, starting x, starting y
	 * returns pointer to the window
	 */
	WINDOW *local_win;
	local_win = newwin(h, w, sy, sx);
	//wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	//box(local_win, 0, 0);
	return local_win;
}

void destroy_win(WINDOW *local_win)
{
	/*
	 * destroys a given window
	 * args:
	 * 	pointer to the window to be destroyed
	 * returns nothing.
	 */
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}
