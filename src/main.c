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
int checkPosition(int newY, int newX, Player * user);
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
	printw("v0.0.3");
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
	int newY;
	int newX;
	
	switch (input) {
		// up
		case 'w':
		case 'W':
			newY = user->posY - 1;
			newX = user->posX;
			break;
			
		// down
		case 's':
		case 'S':
			newY = user->posY + 1;
			newX = user->posX;
			break;
			
		// left
		case 'a':
		case 'A':
			newY = user->posY;
			newX = user->posX-1;
			break;
			
		// right
		case 'd':
		case 'D':
			newY = user->posY;
			newX = user->posX+1;
			break;
			
		default:
			break;
	}
	checkPosition(newY, newX, user);
}

// Checks whats at next position
int checkPosition(int newY, int newX, Player * user) {
	int space;
	// Curses function that checks what is beneath the cursor
	switch (mvinch(newY, newX)) {
		// Wall
		case '.':
			playerMove(newY, newX, user);
			break;
		default:
			move(user->posY, user->posX);
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