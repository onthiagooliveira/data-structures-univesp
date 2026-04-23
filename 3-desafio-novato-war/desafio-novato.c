/**
 * @file desafio-novato.C
 * @brief Sistema de Construção dos territórios | Jogo War
 * @date 2026
*/

#include <stdio.h>
#include <string.h>

/** @brief Tamanho máximo do número de territórios. */
#define MAX_TERRITORIES 5
/** @brief Tamanho máximo para os campos de texto. */
#define SIZE_STRING 30
/** @brief Tamanho máximo para o cmapo cor. */
#define SIZE_COLOR 10

/**
 * @brief struct território
 * @brief Representa os dados doterritório
*/
typedef struct {
  char name[SIZE_STRING];
  char color[SIZE_COLOR];
  int number_of_troops;
} Territory;

// Variáveis Globais (Acessíveis por todas as funções)
Territory territories[MAX_TERRITORIES];
int totalTerritories = 0;

/**
 * @brief Esvazia o buffer de entrada (stdin).
 * * Em C, ler um caractere e' o mesmo que remove-lo da "fila" (buffer) de entrada.
 * Este laço consome e descarta cada byte remanescente na esteira do sistema
 * operacional ate' encontrar o caractere de nova linha ('\n') ou o fim do arquivo (EOF),
 * garantindo que a proxima leitura (como um fgets) comece do zero.
*/
void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

/** @brief Realiza o cadastro de um novo território no array global. */
void registerTerritories() {
  if (totalTerritories < MAX_TERRITORIES) {

    for(int i = 0; i < MAX_TERRITORIES; i++) {
          printf("\n--- Adicionar Territorio ---\n");
          printf("Territorios %d/%d\n", totalTerritories, MAX_TERRITORIES);

          printf("Nome do Territorio: \n");
          fgets(territories[totalTerritories].name, SIZE_STRING, stdin);
          territories[totalTerritories].name[strcspn(territories[totalTerritories].name, "\n")] = 0;

          printf("Cor do Execito:  \n");
          fgets(territories[totalTerritories].color, SIZE_COLOR, stdin);
          territories[totalTerritories].color[strcspn(territories[totalTerritories].color, "\n")] = 0;

          printf("Numero de tropas: \n");
          scanf("%d", &territories[totalTerritories].number_of_troops);
          clearBuffer();

          totalTerritories++;
          printf("\nSucesso: Territorio registrado\n");
        }
  } else {
    printf("Erro: Capacidade de territorios esgotados.");
  }
}

/* @brief Exibe o mapa com os territorios cadastrados*/
void displayTerritories() {
  if(totalTerritories == 0) {
    printf("\nNao foram adicionados territorios.\n");
  } else {
    printf("\n******** MAPA ESTRATEGICO (WAR) ********\n");
    for(int i = 0; i < totalTerritories; i++) {
      printf("%d  | %s   | Exercito:   %s   | Tropas:   %d\n ", i + 1, territories[i].name, territories[i].color, territories[i].number_of_troops);
    }
  }
}

/** @brief Ponto de entrada principal. */
int main(void) {
    int option = -1;

    do {
      printf("\nWAR | O jogo da estrategia\n");
      printf("========== Menu ==========\n");
      printf("1 | Definir Territorios\n");
      printf("2 | Mapa de Territorios\n");
      printf("0 | Sair\n");
      printf("Escolha: ");
      
      if (scanf("%d", &option) != 1) {
        clearBuffer();
        continue;
      }

      clearBuffer();
      
      
    switch (option) {
      case 1:
        registerTerritories();
        break;

      case 2:
        displayTerritories();
        break;

      case 0:
        printf("Saindo...\n");
        break;

      default:
        printf("Opcao invalida.\n");
      }

    } while (option != 0);
    return 0;
  }
  
  
