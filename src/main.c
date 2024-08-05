//		Fantasy Lied - Soul Thief
//	       by Pedro Ivo, 2024

#include <curses.h>
#include <stdlib.h>

typedef struct Player {
	int posX;
	int posY;
	int hp;
} Player;

int screenSetup();
int mapSetup();
Player * playerSetup();

int main() {
	Player * user;
	int ch;
	screenSetup();
	
	mapSetup();
	
	user = playerSetup();
	
	while ((ch = getch()) != 'q') {
		
	}
	endwin();
	return 0;
}

int screenSetup() {
	initscr();
	noecho();

	printw("Hello world");
	refresh();
	
	return 0;
}

int mapSetup() {
	mvprintw(13, 13, "--------");
	mvprintw(14, 13, "|......|");
	mvprintw(15, 13, "|......|");
	mvprintw(16, 13, "|......|");
	mvprintw(17, 13, "|......|");
	mvprintw(18, 13, "--------");
	
	mvprintw(2, 40, "----------");
	mvprintw(3, 40, "|........|");
	mvprintw(4, 40, "|........|");
	mvprintw(5, 40, "|........|");
	mvprintw(6, 40, "|........|");
	mvprintw(7, 40, "----------");
}

Player * playerSetup() {
	Player * newPlayer;
	newPlayer = malloc(sizeof(Player));
	newPlayer->posX = 14;
	newPlayer->posY = 14;
	newPlayer->hp = 20;
	
	mvprintw(newPlayer->posY, newPlayer->posX, "@"); // acaba colocando o cursor a frente
	move(14, 14); // volta o cursor para posição do player
	
	return newPlayer;
}