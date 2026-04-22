#include <stdio.h>
#include <stdlib.h> // Padrão ANSI para malloc, free e exit

/**
 * @file 2-ponteiros-e-alocacao-de-memoria.c
 * @brief Estudo de alocação dinâmica e ponteiros.
 * * @note Notas de Aprendizado:
 * Em C há uma distinção bastante explícita entre um tipo (ou uma estrutura) e um endereço.
 * - int x: variável do tipo inteiro (valor direto).
 * - int* y: variável do tipo endereço para inteiro (ponteiro).
 * * O asterisco apos a palavra 'int' indica que estamos falando de um endereço 
 * para inteiro e nao mais de um valor inteiro propriamente dito.
 */

/**
 * @brief Função principal para demonstração de ponteiros e memória.
 * @return int 0 para execução bem-sucedida.
 */
int main(void) {
    
    /* * @var y
     * Alocação dinâmica: reservamos espaço na Heap para um inteiro.
     * O (int*) é um 'cast' que confirma que o endereço retornado será tratado como inteiro.
     */
    int* y = (int*) malloc(sizeof(int));

    /*
     * @note Operação de Desreferenciação:
     * O asterisco antes de 'y' significa que iremos ate a memória apontada 
     * pela referencia (y) para atribuir o valor.
     */
    if (y != NULL) { // Verificação básica de segurança para alocação
        *y = 30;
    }

    // Armazena o tamanho em bytes do tipo int na arquitetura atual
    int z = sizeof(int);

    printf("*Y = %i (valor no endereco)\n", *y);
    printf("Y  = %p (endereco de memoria)\n", (void*)y);
    printf("Z  = %i (tamanho do tipo int em bytes)\n", z);

    // Boa prática: sempre liberar a memória alocada manualmente
    free(y);

    return 0;
}