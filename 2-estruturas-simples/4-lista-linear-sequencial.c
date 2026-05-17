/**
 * @file 4-lista-linear-sequencial.c
 * @brief MANUAL TÉCNICO: Lista Linear Sequencial Estática Otimizada
 * @date 2026
 * 
 * @details CONCEITOS INTEGRADOS:
 * - BUSCA COM SENTINELA: Otimização da busca exaustiva (O(N)) reduzindo testes de limite.
 * - INSERÇÃO ORDENADA: Técnica de Shifting para manter a integridade da ordem lógica.
 * - BUSCA BINÁRIA: Implementação do paradigma "Dividir para Conquistar", 
 *   reduzindo drasticamente a complexidade para O(log N).
 * 
 * @note A eficiência da Busca Binária depende estritamente da Inserção Ordenada.
*/

#include <stdio.h>
#include <stdbool.h> // Necessário para o tipo 'bool'

/** @brief Capacidade máxima de elementos reais na lista. */
#define MAX 50

/** @brief Tipo de dado da chave. Facilita a manutenção. */
typedef int TIPOCHAVE;

/** @brief Estrutura do registro. */
typedef struct {
    TIPOCHAVE chave;
} REGISTRO;

/** @brief Estrutura da Lista Linear Sequencial. */
typedef struct {
    /** 
     * IMPORTANTE: Alocamos MAX + 1. 
     * O índice [nroElem] será usado exclusivamente para o sentinela.
     */
    REGISTRO A[MAX + 1]; 
    int nroElem;
} LISTA;

/** 
 * @brief Inicializa a lista (Zera o número de elementos)
 */
void inicializarLista(LISTA* l) {
    l->nroElem = 0;
}

/** 
 * @brief Busca Sequencial Simples (Tradicional)
 * @details Realiza duas comparações lógicas a cada iteração (i < nroElem e chave != busca).
 */
int sequencialSearch(LISTA* l, TIPOCHAVE ch) {
    int i = 0;
    while (i < l->nroElem) { 
        if (ch == l->A[i].chave) return i; 
        else i++;
    }
    return -1; 
}

/** 
 * @brief Busca Sequencial Otimizada (Com Sentinela)
 * @details Planta-se a chave no fim da lista para eliminar um teste lógico no laço.
 */
int buscaSentinela(LISTA* l, TIPOCHAVE ch) {
    int i = 0;
    l->A[l->nroElem].chave = ch; // 1. Planta o sentinela
    
    while(l->A[i].chave != ch) { // 2. Laço ultra veloz (apenas 1 comparação)
        i++; 
    }
    
    if(i == l->nroElem) return -1; // 3. Se parou no sentinela, não existia na lista real
    return i; 
}

/**
* @brief Inserção Ordenada (Mantém a lista pronta para Busca Binária)
* @details 
* 1. Verifica se há espaço.
* 2. Localiza a posição correta (de trás para frente).
* 3. DESLOCAMENTO (Shifting): Move elementos maiores para a direita.
* 4. INSERÇÃO: Ocupa a vaga aberta.
*/
bool inserirElemListaOrd(LISTA* l, REGISTRO reg) {
    // 1. Verificação de transbordamento (Overflow)
    if(l->nroElem >= MAX) return false; 

    int pos = l->nroElem; // Começa no primeiro espaço vazio disponível

    /**
     * @section SHIFTING (O Coração da Inserção)
     * Enquanto o elemento anterior for maior que o novo registro, 
     * "empurramos" ele para a direita.
     */
    while(pos > 0 && l->A[pos-1].chave > reg.chave) {
        // O elemento em [pos-1] "anda" para [pos]
        l->A[pos] = l->A[pos-1]; 
        pos--; // Recuamos para testar o próximo vizinho à esquerda
    }

    l->A[pos] = reg; // Colocamos o novo registro na "vaga" que restou
    l->nroElem++;    // Atualizamos o contador de ocupação
    return true;
}


/** 
 * @brief Busca Binária
 * @details Requisito: A lista DEVE estar ordenada.
 * Divide o espaço de busca ao meio a cada iteração, atingindo complexidade O(log N).
 * 
 * @param l Ponteiro para a lista
 * @param ch Chave buscada
 * @return Posição do elemento ou -1 se não encontrado.
 */
int buscaBinaria(LISTA* l, TIPOCHAVE ch) {
    int esq, dir, meio;
    esq = 0;
    dir = l->nroElem - 1;

    while(esq <= dir) {
        // Calcula o meio para dividir a lista
        meio = (esq + dir) / 2; 

        if(l->A[meio].chave == ch) {
            return meio; // Sucesso: elemento encontrado no meio
        } 
        
        if (l->A[meio].chave < ch) {
            // Se a chave do meio é menor, o que buscamos está à DIREITA
            esq = meio + 1;
        } else {
            // Se a chave do meio é maior, o que buscamos está à ESQUERDA
            dir = meio - 1;
        }
    }
    return -1; // Fracasso: intervalo esgotado sem encontrar a chave
}