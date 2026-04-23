/**
 * @file lista-linear-sequencial.c
 * @brief MANUAL TÉCNICO: Lista Linear Sequencial Estática
 * @date 2026
 * * CONCEITO CHAVE:
 * Uma lista sequencial armazena elementos em posições contíguas na memória (Array).
 * A ordem lógica (o que o usuário vê) é a mesma ordem física (como está na RAM).
 */

#include <stdio.h>
#include <stdbool.h> // Necessário para usar o tipo 'bool' em C

/** @brief Capacidade total do "balde" de memória reservado. */
#define MAX 50

typedef int KEYTYPE;

/** @brief Registro: A unidade de dados da lista. */
typedef struct {
    KEYTYPE key;
    /* Outros campos (payload) podem ser adicionados aqui, como 'nome', 'valor' etc. */
} RECORD;

/** @brief Estrutura da Lista: Gerencia o array e o contador. */
typedef struct {
    RECORD A[MAX];      // O arranjo físico de registros
    int elementNumber;  // Quantidade de elementos ATUAIS (Lógico)
} LIST;

/* =========================================================================
   FUNÇÕES DE GERENCIAMENTO
   ========================================================================= */

/** * @brief Inicialização da Lista
 * @param l Ponteiro para a lista que será "zerada".
 * @note No C, não limpamos o lixo de memória do array, apenas resetamos o 
 * ponteiro lógico 'elementNumber'. Para o sistema, a lista está vazia.
 */
void initializeList(LIST* l) {
    l->elementNumber = 0;
}

/** * @brief Reinicialização (Reset)
 * @param l Ponteiro para a lista.
 * @return Retorna 0 (sucesso).
 * @note Operação de complexidade O(1) - Velocidade constante.
 */
void resetList(LIST* l) {
    l->elementNumber = 0;
}

/** @brief Retorna o tamanho lógico da lista. */
int listSize(LIST* l) {
    return l->elementNumber;
}

/* =========================================================================
   FUNÇÕES DE OPERAÇÃO (CRUD)
   ========================================================================= */

/** * @brief Exibição da Lista
 * Percorre o array do índice 0 até elementNumber-1.
 */
void displayList(LIST* l) {
    printf("Lista [ ");
    for (int i = 0; i < l->elementNumber; i++) {
        printf("%i ", l->A[i].key);
    }
    printf("]\n");
}

/** * @brief Busca Sequencial Simples
 * @param l Ponteiro para a lista.
 * @param k Chave procurada.
 * @return Índice do elemento ou -1 se não encontrado.
 * @note Complexidade: O(n). Precisamos olhar um por um.
 */
int sequencialSearch(LIST* l, KEYTYPE k) {
    int i = 0;
    while (i < l->elementNumber) {
        if (k == l->A[i].key) return i;
        i++;
    }
    return -1;
}



/** * @brief Inserção com Deslocamento (Shift Right)
 * @param l Ponteiro para a lista.
 * @param reg O registro completo a ser inserido.
 * @param i Índice alvo da inserção.
 */
bool insertElemList(LIST* l, RECORD reg, int i) {
    // 1. Validação: Lista cheia? Índice faz sentido? Não deixa buracos?
    if ((l->elementNumber == MAX) || (i < 0) || (i > l->elementNumber)) {
        return false;
    }

    // 2. Abrir espaço: Move quem está na frente para a direita.
    // Começamos do fim para não sobrescrever dados.
    for (int j = l->elementNumber; j > i; j--) {
        l->A[j] = l->A[j - 1];
    }

    // 3. Inserir e Atualizar contador
    l->A[i] = reg;
    l->elementNumber++;
    return true;
}



/** * @brief Exclusão com Deslocamento (Shift Left)
 * @param k Chave do elemento a ser removido.
 * @param l Ponteiro para a lista.
 * @return true se removido, false se não encontrado.
 */
bool delElemList(LIST* l, KEYTYPE k) {
    int pos = sequencialSearch(l, k);
    if (pos == -1) return false; // Elemento não existe

    /* * SHIFT LEFT:
     * Para manter a lista sequencial sem "buracos", trazemos todos
     * os elementos após a posição removida uma casa para a esquerda.
     */
    for (int j = pos; j < l->elementNumber - 1; j++) {
        l->A[j] = l->A[j + 1];
    }

    l->elementNumber--;
    return true;
}



/* =========================================================================
   GUIA DE ESTUDO RÁPIDO (CHEATSHEET)
   =========================================================================
   1. Vantagem: Acesso direto via índice é instantâneo (O(1)).
   2. Desvantagem: Inserir/Remover no início é custoso (O(n)).
   3. Memória: Ocupa um bloco fixo (pode sobrar espaço ou faltar).
   4. Quando usar: Quando o número de elementos é conhecido e há poucas inserções/remoções.
   ========================================================================= */