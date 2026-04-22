/**
 * @file 3-exBiblioteca.c
 * @brief Sistema de gestão de acervo usando alocação estática.
 * @date 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @brief Tamanho máximo do acervo. */
#define MAX_BOOKS 50
/** @brief Tamanho máximo para campos de texto. */
#define SIZE_STRING 100

/**
 * @struct Book
 * @brief Representa os dados técnicos de uma obra literária.
 */
typedef struct {
  char title[SIZE_STRING];
  char author[SIZE_STRING];
  int edition;
  char publisher[SIZE_STRING];
} Book;

/**
 * @brief Esvazia o buffer de entrada (stdin).
 * * Em C, ler um caractere e' o mesmo que remove-lo da "fila" (buffer) de entrada.
 * Este laço consome e descarta cada byte remanescente na esteira do sistema 
 * operacional ate' encontrar o caractere de nova linha ('\n') ou o fim do arquivo (EOF),
 * garantindo que a proxima leitura (como um fgets) comece do zero.
 */
 void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF); // Varre o buffer a procura de "\n" ou End of File;
 }


 /**
 * @brief Ponto de entrada do sistema.
 * @return int 0 para execução normal.
 */
int main(void) {
  Book library[MAX_BOOKS]; // Array estático de structs
  int totalBooks = 0;
  int option = -1;

  do {
      printf("\n--- BIBLIOTECA VIRTUAL ---\n");
      printf("Livros cadastrados: %d|%d\n", totalBooks, MAX_BOOKS);
      printf("1 | Cadastrar Livro\n");
      printf("2 | Listar Livros\n");
      printf("0 | Sair\n");
      printf("Escolha: ");
      
      if (scanf("%d", &option) != 1) {
        printf("Erro: Entrada inválida.\n");
        clearBuffer();
        continue;
      }
      clearBuffer(); // Remove o '\n' que sobraria para o proximo fgets

      switch (option) {
        
        case 1:
          if (totalBooks < MAX_BOOKS) {
            printf("\n--- Cadastro de Livro ---\n");

            printf("Titulo: ");
            fgets(library[totalBooks].title, SIZE_STRING, stdin);
            // Remove o \n (enter) do final
            library[totalBooks].title[strcspn(library[totalBooks].title, "\n")] = 0;

            printf("Autor: ");
            fgets(library[totalBooks].author, SIZE_STRING, stdin);
            library[totalBooks].author[strcspn(library[totalBooks].author, "\n")] = 0;

            printf("Edicao: ");
            scanf("%d", &library[totalBooks].edition);
            clearBuffer();

            printf("Editora: ");
            fgets(library[totalBooks].publisher, SIZE_STRING, stdin);
            library[totalBooks].publisher[strcspn(library[totalBooks].publisher, "\n")] = 0;

            totalBooks++;
            printf("\nSucesso: Livro registrado\n");
          } else {
            printf("Erro: Capacidade da biblioteca esgotada.\n");
          }
        break;

        case 2:
          printf("\n--- Listagem de Acervo ---\n");
          if (totalBooks == 0) printf("Nenhum livro cadastrado.\n");

          for(int i = 0; i < totalBooks; i++) {
            printf("%d. [%s] | Autor: %s | Edicao: %d | Editora: %s \n", i + 1, library[i].title, library[i].author, library[i].edition, library[i].publisher);
          }
        break;

        case 0:
          printf("Encerrando sistema...\n");
        break;

        default:
          printf("Opcao invalida.\n");

      }

  } while (option != 0);

  return 0;
}