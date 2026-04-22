/**
 * @file 1-estrutura.c
 * @brief Programa de exemplo para manipulação de estruturas com alocação dinâmica.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Biblioteca padrão para malloc e free

/**
 * @struct PersonMetrics
 * @brief Armazena métricas físicas básicas de um indivíduo.
 * * @var PersonMetrics::weight
 * Membro 'weight' armazena o peso em quilogramas.
 * @var PersonMetrics::height
 * Membro 'height' armazena a altura em centímetros.
 */
typedef struct {
    int weight; 
    int height; 
} PersonMetrics;

/** @brief Limite máximo de altura permitido (em cm). */
#define MAX_HEIGHT 225

/** @brief Limite mínimo de altura permitido (em cm). */
#define MIN_HEIGHT 30

/**
 * @brief Ponto de entrada do programa.
 * * Demonstra a alocação dinâmica de uma struct, atribuição via ponteiro
 * e liberação de memória.
 * * @return int Retorna 0 em caso de execução bem-sucedida.
 */
int main(void) {
    
    // Alocação dinâmica: reservamos espaço na Heap com o tamanho em bytes da estrutura
    PersonMetrics* person1 = (PersonMetrics*) malloc(sizeof(PersonMetrics));

    // Verificação de segurança (Boa prática: checar se o malloc falhou)
    if (person1 == NULL) {
        return 1;
    }
    
    // Atribuição usando o operador de seta (->) para ponteiros
    person1->weight = 63;
    person1->height = 179;

    // Saída de dados
    printf("Peso:   %i kg\n", person1->weight);
    printf("Altura: %i cm\n", person1->height);
    
    // Lógica de verificação de limites
    if (person1->height > MAX_HEIGHT || person1->height < MIN_HEIGHT) {
        printf("Aviso: Altura fora dos padrões normativos.\n");
    } else {
        printf("Status: Altura dentro dos limites permitidos.\n");
    }

    // REGRA DE OURO: usou malloc, DEVE usar free.
    free(person1);
    person1 = NULL; // Evita ponteiros "soltos" (dangling pointers)

    return 0;
}