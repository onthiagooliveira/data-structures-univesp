/**
 * @file 2-desafio-aventureiro.C
 * @brief Sistema de Construção dos territórios | Jogo War
 * @date 2026
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> // Para utilizarmos Memory Allocation | Clean Allocation
#include "library.h" // Inclui library.h, nossa biblioteca com funções personalizadas.


int main (void) {
  // Invoca função que aloca memória e zera os bytes do campo, iniciando em 0.
  numTerritories = allocateMemoryTypeInt();

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