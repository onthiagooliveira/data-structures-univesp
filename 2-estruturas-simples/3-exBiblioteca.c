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
  int availableForLoan;
} Book;

typedef struct {
  int BookIndex;
  char userName[SIZE_STRING];
} Loan;


/** @brief Variáveis globais */
Book* library[MAX_BOOKS];
int* totalBooks;
int option = -1;


/** Protótipo das funções
* Declarar a função aqui permite que a 'main' as invoque antes de suas definições; */

void clearBuffer();
void menuDisplay();
void addBook();
void bookList();
void bookLoan();
void listLoans();
void freeUpMemory();

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

 void menuDisplay() {
  do {
      printf("\n--------- BIBLIOTECA VIRTUAL ---------\n");
      printf("Livros cadastrados: %d|%d\n", ++(*totalBooks), MAX_BOOKS);
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
          addBook();
        break;

        case 2:
          bookList();
        break;

        case 0:
          printf("Encerrando sistema...\n");
        break;

        default:
          printf("Opcao invalida.\n");
      }
  } while (option != 0);  
};

/** @brief Função que regitra um livro na biblioteca */
void addBook() {
  if (*totalBooks < MAX_BOOKS){
    if(library != NULL) {
      while(option != 0) {
        for (int i = 0; i < MAX_BOOKS; i++) {
        /** @brief Aloca memória e zera os campos para inserção futura */
        library[i] = (Book*) calloc(1, sizeof(Book)); 
        
        printf("\n--- Adiconar Livro ---\n");
        printf("Titulo: ");
        fgets(library[i]->title, SIZE_STRING, stdin);
        // Remove o \n (enter) do final
        library[i]->title[strcspn(library[i]->title, "\n")] = 0;
        
        printf("Autor: ");
        fgets(library[i]->author, SIZE_STRING, stdin);
        library[i]->author[strcspn(library[i]->author, "\n")] = 0;

        printf("Edicao: ");
        scanf("%d", &library[i]->edition);
        clearBuffer();

        printf("Editora: ");
        fgets(library[i]->publisher, SIZE_STRING, stdin);
        library[i]->publisher[strcspn(library[i]->publisher, "\n")] = 0;

        printf("Disponibilidade: ");
        scanf("%d", &library[i]->edition);
        clearBuffer();
        
        *totalBooks++;
        printf("\nSucesso: Livro registrado\n");
        menuDisplay();
      }
      } 
    } else {
      printf("Erro: Capacidade da biblioteca esgotada.\n");
    }
  }
}

void bookList() {
  printf("\n--- Listagem de Acervo ---\n");
  if (totalBooks == 0) printf("Nenhum livro cadastrado.\n");
  for(int i = 0; i < *totalBooks; i++) {
    printf("%d. [%s] | Autor: %s | Edicao: %d | Editora: %s \n", i + 1, library[i]->title, library[i]->author, library[i]->edition, library[i]->publisher);
  }
}

 
/**
 * @brief Ponto de entrada do sistema.
 * @return int 0 para execução normal.
*/
int main() {
  totalBooks = (int*) calloc(1, sizeof(int));

  menuDisplay();
  return 0;
}