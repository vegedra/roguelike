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
int menu();

int main(void) {
	setlocale(LC_ALL,"Portuguese");
	
	menu();
	while (1) { // loop infinito
		player_stats();
		printf("\nEscolha uma direção: ");
		scanf("%9s", player_move);  // O 9 é para limitar o quanto que o jogador pode digitar
		
        // Se usa strcasecmp para comparar strings ignorando maiúsculas/minúsculas - strcmp não
        if (strcasecmp(player_move, "sair") == 0) {
            break;  // Sai do loop se o jogador digitar "sair"
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
	
	printf("Qual seu nome?\n");
	// fgets reads in a line from standard input and puts it in the variable
	fgets(input, sizeof(input), stdin);
	/* sscanf looks at our variable and transfer it over to the other variable because
	we'll want to use the variable Input again to get user input, so we can't leave 
	information in there or it will be overwriten */
	sscanf(input, "%s", name);
	printf("Obrigado por atender meu pedido, %s.", name);
	/* Functions dont need to return a value, so a 'void' before a function means that
	the function doesnt return a datatype. */
	printf("\nEu me chamo Theia, meu objetivo é me encontrar com o antigo rei dos demonios.");
	printf("\nEle se encontra no ponto mais baixo desse subsolo.");
	printf("\nConto com você para me guiar até ele.");
	return 0;
}

// Mostra onde o jogador está
void player_stats() {
	printf("\nVocê está em %s.\n", currentRoom);
}

// Movimentação do jogador
void movement() {
	printf("\a");
    if (strcasecmp(player_move, "norte") == 0) {
        strcpy(currentRoom, "floresta");
    } else if (strcasecmp(player_move, "sul") == 0) {
        strcpy(currentRoom, "deserto");
    } else {
        printf("Movimento inválido. Tente novamente.\n");
    }
}