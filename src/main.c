#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>  // Habilitar caracteres especiais
#include <curses.h> // Biblioteca PDCurses (curses pra windows)

// Constantes para definir o número de salas/rooms e o tamanho do nome e descrição
#define NUM_ROOMS 4
#define NAME_SIZE 15
#define DESC_SIZE 256

// Estrutura de uma sala/local - room
typedef struct {
    char name[NAME_SIZE];
    char description[DESC_SIZE];
    int north;
    int south;
    int east;
    int west;
} Room;

// Variavéis
Room rooms[NUM_ROOMS];          // Array das Rooms
int currentRoomIndex = 0;       // Index da room atual
char player_move[10];           // Input do movimento do jogador
int player_hp = 10;             // Pontos de vida do jogador, se chegar a 0 ele morre

// Protótipos de função
void displayPlayerStats();
void handleMovement();
void generateCharacter();
void initializeRooms();

int main(void) {
    // Seta o locale para o portugues e que mostre os caracteres especiais
    setlocale(LC_ALL, "Portuguese_Brazil.1252"); 

    // Inicializa PDCurses
    initscr();          // Inicia a tela
    cbreak();           // Disable line buffering
    keypad(stdscr, TRUE); // Enable special keys
    curs_set(0);        // Hide the cursor
    //noecho();           // Desativa a exibição de teclas pressionadas

    // Inicializa as salas
    initializeRooms();
	
	int input;
    do {
		resize_term(40, 80);  // Muda o tamanho da janela, tem que estar acompanhado de um refresh()
        clear();
        mvprintw(0, 0, "********************************************************************************");
        mvprintw(1, 30, "Fantasy Lied - Arena");
        mvprintw(2, 31, "by Pedro Ivo, 2024");
        mvprintw(15, 36, "1) Jogar");
        mvprintw(16, 36, "2) Sair");
        mvprintw(39, 0, "********************************************************************************");
		refresh();  // Atualiza a tela

        // Recebe o input do jogador
        input = getch();

        if (input == '1') {
			curs_set(1);
            generateCharacter();
            do {
                clear();
                displayPlayerStats();
                mvprintw(4, 0, "Escolha uma direção cardinal. Digite 'sair' para fechar o jogo.");
				mvprintw(5, 0, "> ");
                refresh();
                scanw("%9s", player_move); // Limita o input a 9 caracteres

                // Movimentação do jogador
                handleMovement();
            } while (strcasecmp(player_move, "sair") != 0);
        }
    } while (input != '2');

    mvprintw(14, 0, "\nSaindo do jogo.");
    refresh();
    endwin();
    return 0;
}

// Inicia as rooms com seus nomes, descrições e conexões predefinidas
void initializeRooms() {
    //strcpy(destino, fonte);  syntaxe

	// Sala Caverna
    strcpy(rooms[0].name, "Caverna");
    strcpy(rooms[0].description, "Uma caverna escura.");
    rooms[0].north = 1; // North leads to room 1 (Forest)
    rooms[0].south = 2; // South leads to room 2 (Desert)
    rooms[0].east = 3;  // East leads to room 3 (Castle)
    rooms[0].west = -1; // No room to the west (-1 means no exit)

	// Sala Floresta
    strcpy(rooms[1].name, "Floresta");
    strcpy(rooms[1].description, "Uma floresta densa e misteriosa.");
    rooms[1].north = -1; // No room to the north
    rooms[1].south = 0;  // South leads back to room 0 (Cave)
    rooms[1].east = -1;  // No room to the east
    rooms[1].west = -1;  // No room to the west

	// Sala deserto
    strcpy(rooms[2].name, "Deserto");
    strcpy(rooms[2].description, "Quente e árido...");
    rooms[2].north = 0; // North leads back to room 0 (Cave)
    rooms[2].south = -1; // No room to the south
    rooms[2].east = -1;  // No room to the east
    rooms[2].west = -1;  // No room to the west

	// Sala castelo
    strcpy(rooms[3].name, "Castelo");
    strcpy(rooms[3].description, "Em ruínas...");
    rooms[3].north = -1; // No room to the north
    rooms[3].south = -1; // No room to the south
    rooms[3].east = -1;  // No room to the east
    rooms[3].west = 0;   // West leads back to room 0 (Cave)
}

// Exibe a localização e a descrição atuais do jogador
void displayPlayerStats() {
    mvprintw(0, 0, "Você está em: %s  |  HP: %d\n", rooms[currentRoomIndex].name, player_hp);
    mvprintw(1, 0, "%s\n", rooms[currentRoomIndex].description);
}

// Cuida do movimento do jogador com base no input do mesmo
void handleMovement() {
    int newRoomIndex = -1;

    if (strcasecmp(player_move, "norte") == 0) {
        newRoomIndex = rooms[currentRoomIndex].north;
    } else if (strcasecmp(player_move, "sul") == 0) {
        newRoomIndex = rooms[currentRoomIndex].south;
    } else if (strcasecmp(player_move, "leste") == 0) {
        newRoomIndex = rooms[currentRoomIndex].east;
    } else if (strcasecmp(player_move, "oeste") == 0) {
        newRoomIndex = rooms[currentRoomIndex].west;
    } 

    // Atualiza sala atual se o input for válido
    if (newRoomIndex >= 0) {
        currentRoomIndex = newRoomIndex;
    } else {
        mvprintw(7, 0, "Movimento inválido ou sem saída nessa direção. Tente novamente.\n");
		refresh();
    }
}

// Geração de personagem
void generateCharacter() {
    char name[9];

    clear();
    mvprintw(0, 0, "Diga-me, qual o seu nome?");
	mvprintw(1, 0, "> ");
    refresh();
    scanw("%9s", name); 

    mvprintw(3, 0, "É um prazer em te conhecer, %s.", name);
    mvprintw(4, 0, "Eu sou Theia, eu te invoquei aqui para que me ajude em minha missão.");
	mvprintw(5, 0, "Preciso encontrar o antigo Rei do Subsolo, o rei demônio.");
    mvprintw(6, 0, "Ele está no ponto mais baixo deste lugar.\n");
	refresh();
    mvprintw(7, 0, "Qualquer humano que cai aqui enlouquece, logo, deixarei que tome controle do\n");
	mvprintw(8, 0, "meu corpo, já que és um espírito já sem corpo. Vamos em frente.\n");
	refresh();
	//napms(2000);  // sleep do curses.h
	mvprintw(10, 0, "Pressione Enter para continuar");
    refresh();
    getch();
}
