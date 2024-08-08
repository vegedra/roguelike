//		Fantasy Lied - Soul Thief
//	       by Pedro Ivo, 2024

#include <curses.h>
#include <stdlib.h>

// Structs
typedef struct Room {
	int posX;
	int posY;
	int height;
	int width;
	//Monster ** monsters;
	//Item ** items;
} Room;

typedef struct Player {
	int posX;
	int posY;
	int hp;
} Player;

// Prototype functions

int screenSetup();
int handleInput(int input, Player * user);
int playerMove(int y, int x, Player * user);
int checkPosition(int newY, int newX, Player * user);
int drawRoom(Room *room);
Room ** mapSetup();
Player * playerSetup();

// Room functions
Room * createRoom(int x, int y, int height, int width);

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
	printw("v0.0.4");
	refresh();
	
	return 0;
}

Room ** mapSetup() {
	Room ** rooms;
	rooms = malloc(sizeof(Room)*6);
	
	// x, y, height, width
	rooms[0] = createRoom(13, 13, 6, 8);
	drawRoom(rooms[0]);
	
	rooms[1] = createRoom(40, 10, 6, 11);
	drawRoom(rooms[1]);
	
	rooms[2] = createRoom(60, 3, 9, 8);
	drawRoom(rooms[2]);
}

Room * createRoom(int x, int y, int height, int width) {
	Room * newRoom;
	newRoom = malloc(sizeof(Room));
	
	newRoom->posX = x;
	newRoom->posY = y;
	newRoom->height = height;
	newRoom->width = width;
	
	return newRoom;
}

int drawRoom(Room *room) {
	int x;
	int y;
	
	// Draws top and bottom
	for (x = room->posX; x < room->posX + room->width; x++) {
		mvprintw(room->posY, x, "-"); // Top
		mvprintw(room->posY + room->height - 1, x, "-"); // Bottom
	}
	// Draws side-walls
	for (y = room->posY + 1; y < room->posY + room->height - 1; y++) {
		mvprintw(y, room->posX, "|"); 
		mvprintw(y, room->posX + room->width - 1, "|");
		
		// Draws the floors
		for (x = room->posX + 1; x < room->posX + room->width - 1; x++) {
			mvprintw(y, x, "."); 
		}
	}
	
	return 0;
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