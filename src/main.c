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
int handleInput(int input, Player * user);
int playerMove(int y, int x, Player * user);
Player * playerSetup();

int main() {
	Player * user;
	int ch;
	screenSetup();
	
	mapSetup();
	
	user = playerSetup();
	
	// Main game loop
	while ((ch = getch()) != 'q') {
		handleInput(ch, user);
	}
	endwin();
	return 0;
}

int screenSetup() {
	initscr();
	noecho();

	printw("Fantasy Lied by Pedro Ivo, 2024\n");
	printw("v0.0.1");
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
	
	playerMove(14, 14, newPlayer);
	
	return newPlayer;
}

int handleInput(int input, Player * user) {
	switch (input) {
		// up
		case 'w':
		case 'W':
			playerMove(user->posY-1, user->posX, user);
			break;
			
		// down
		case 's':
		case 'S':
			playerMove(user->posY+1, user->posX, user);
			break;
			
		// left
		case 'a':
		case 'A':
			playerMove(user->posY, user->posX-1, user);
			break;
			
		// right
		case 'd':
		case 'D':
			playerMove(user->posY, user->posX+1, user);
			break;
			
		default:
			break;
	}
}

int playerMove(int y, int x, Player * user) {
	mvprintw(user->posY, user->posX, "."); 
	user->posY = y;
	user->posX = x;
	mvprintw(user->posY, user->posX, "@"); 
	move(user->posY, user->posX);
}