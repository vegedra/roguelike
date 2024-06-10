/******************************************************************************

                            Fantasy Lied - Arena
                             by Pedro Ivo, 2024

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Variaveis
char currentRoom[15] = "Caverna";
char player_move[10];

// Prototipos
void player_stats();
void movement();

int main(void) {
	setlocale(LC_ALL,"Portuguese");
	
	menu();
	while (1) { // loop infinito
		player_stats();
		printf("\nEscolha uma direção: ");
		scanf("%9s", player_move);  // O 9 é para limitar o quanto que o jogador pode digitar
        
        // Se usa strcmp para comparar valor de string
        if (strcmp(player_move, "Sair") == 0) {
            break;  // Sai do loop se o jogador digitar "Sair"
        } 
        
        // Verifica para onde o jogador quer ir
        movement();
	}
	// Se o loop encerrar
    printf("\nSaindo do jogo.");
    return 0;
}

int menu() {
	char input[50];
	char name[50]; // Variable to contain a name

	// MENU SCREEN
	
	printf("What is your name?\n");
	// fgets reads in a line from standard input and puts it in the variable
	fgets(input, sizeof(input), stdin);
	/* sscanf looks at our variable and transfer it over to the other variable because
	we'll want to use the variable Input again to get user input, so we can't leave 
	information in there or it will be overwriten */
	sscanf(input, "%s", &name);
	printf("It's a pleasure to meet you, %s.", name);
	/* Functions dont need to return a value, so a 'void' before a function means that
	the function doesnt return a datatype. */
	return 0;
}

// Mostra onde o jogador está
void player_stats() {
	printf("Você está em %s.\n", currentRoom);
}

// Movimentação do jogador
void movement() {
    if (strcmp(player_move, "norte") == 0) {
        strcpy(currentRoom, "floresta");
    } else if (strcmp(player_move, "sul") == 0) {
        strcpy(currentRoom, "deserto");
    } else {
        printf("Movimento inválido. Tente novamente.\n");
    }
}