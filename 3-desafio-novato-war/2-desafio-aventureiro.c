/**
 * @file 2-desafio-aventureiro.C
 * @brief Sistema de Construção dos territórios | Jogo War
 * @date 2026
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> // Para utilizarmos Memory Allocation | Clean Allocation

/** @brief Constantes globais */
#define MAX_TERRITORIES 5 // Tamanho máximo do número de territorios.
#define SIZE_STRING 30  // Tamanho máximo para os campos de texto.
#define SIZE_COLOR 10 // Tamanho máximo para o campo cor.

/**
 * @brief struct território
 * @brief Representa os dados doterritório
*/
typedef struct {
  char name[SIZE_STRING];
  char color[SIZE_COLOR];
  int number_of_troops;
} Territory;


/** @brief Variáveis globais (Acessíveis por todas as funções) */
// Vetor que armazena ponteiros para as estruturas de território, limitado ao máximo definido.
Territory* territories[MAX_TERRITORIES];
int* numTerritories; // Ponteiro para inteiro que armazena o número de territorios de um jogador
int option = -1;


/** @brief Esvazia o buffer de entrada (stdin) */
void bufferClearing() {
  int c;
  while( (c = getchar()) != '\n' && c != EOF );
}

/** @brief Realiza o cadastro de um novo território no array global.*/
void addTerritories() {
  if (*numTerritories < MAX_TERRITORIES) {
    if (territories != NULL) {
      for(int i = 0; i < MAX_TERRITORIES; i++) {

        // Aloca memória e zera todos os bytes automaticamente do primeiro item do vetor| + seguro.
        territories[i] = (Territory*) calloc(1, sizeof(Territory)); // Garante que todos os campos da struct sejam inciados com zero ou vazios

        printf("\n======= Adicionar Territorio =======\n");
        printf("Territorios Adicionados %d/%d\n", ++(*numTerritories), MAX_TERRITORIES);
        
        printf("\nNome do Territorio: \n");
        fgets(territories[i]->name, SIZE_STRING, stdin);
        territories[i]->name[strcspn(territories[i]->name, "\n")] = 0;

        printf("Cor do Exercito: \n");
        fgets(territories[i]->color, SIZE_COLOR, stdin);
        territories[i]->color[strcspn(territories[i]->color, "\n")] = 0;

        printf("Numero de tropas: \n");
        scanf("%d", &territories[i]->number_of_troops);
        bufferClearing();
        

        printf("\nSucesso: Territorio adiconado.\n");
      }
    }
  } else {
    printf("Erro | Capacidade de territorios esgotada.");
  }
}

/** @brief Exibe menu */
void viewMenu() {
  do {
    printf("\n  WAR: CENTRAL DE ESTRATEGIA\n");
    printf("===========================\n");
    printf("1 | Recrutar e Definir Territorios\n");
    printf("2 | Visualizar Mapa Tatico\n");
    printf("0 | Encerrar Operaçao\n");
    printf("---------------------------\n");
    printf("Ordem do Comandante: ");

    if(scanf("%d", &option) != 1) {
      bufferClearing();
      continue;
    }
    switch (option) {
      case 1:
        addTerritories();
        break;

      case 2:
        //displayTerritories();
        break;

      case 0:
        printf("Saindo...\n");
        break;

      default:
        printf("Opcao invalida.\n");
      }
  } while (option != 0);
}


int main (void) {
  // Aloca memória e zera os bytes do campo, iniciando em 0.
  numTerritories = (int*) calloc(1, sizeof(int));

  // Exibe menu para o usuário
  viewMenu();

  
  // Extrai o endereço da variável
  printf("Endereco vetor: %p\n", (void*)&territories);
  printf("Endereco numTerritories: %p\n", (void*)&numTerritories);
  //printf("Valor: %s\n", &territories);

  /** @brief Libera a memória utilizada */
  free(numTerritories); 

  // Limpa a lista linear a partir do primeiro índice.
  for(int i = 0; i < MAX_TERRITORIES; i++) {
    if (territories != NULL) {
      free(territories[i]);
    }
  }
  return 0;
}