#include <stdio.h>
#include <stdlib.h>
int main() {

  /**
  * @brief Lista linear estática: 
  * Um vetor estático é útil quando sabemos previamente a quantidade de dados que alocaremos.
  * Possui tamanho fixo, pré-determinado, evita gargalos de memória.
  */
  int numeros[5] = {10, 20, 30, 40, 50};


  /** @brief Lista Linear dinâmica
  * Estrutura de dados que armazena elementos de forma sequencial, mas com capacidade de ajustar
  * seu tamanho durante a execução do programa, alocando e desalocando memória conforme necessário.
  * - Malloc - Aloca dinamicamente um bloco de memória de tamanho especificado, retorna um * para seu início.
  * - Realloc - Redimensiona um bloco de memória já alocado, preserveando seu conteúdo até o menor dos tamanhos, podendo ser antigo e novo.
  * - Free Libera um bloco de memória já alocado, tornando-o disponível para uso futuro.
  */ 
  int* num = (int*) malloc(3* sizeof(int));
  int tamanho = 5;

  num[0] = 10;
  num[1] = 20;
  num[2] = 30;

  /** @brief Expandi a lista para 5 posições */
  num = (int*) realloc(num, 5* sizeof(int));
  num[3] = 40;
  num[4] = 50;

  for (int i = 0; i < tamanho; i++) {
    printf ("%d, ", num[i]);
  }
  free(num);
  
}