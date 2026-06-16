/**
 * @file 3-arvores-binarias-de-pesquisa.c
 * @brief MANUAL TÉCNICO: ABP - Remoção e Busca Iterativa
 */
#include <stdio.h>
#include <stdlib.h>
#include "1-conceitos-estruturais-binary-tree.h"

// ============================================================================
// @section FUNÇÕES AUXILIARES
// ============================================================================

/**
 * @brief Busca Iterativa com Rastreio de Pai (Não-Recursiva)
 * @details 
 * - **O que faz:** Procura um nó específico e, simultaneamente, anota quem é o nó 
 * pai dele. Isso é OBRIGATÓRIO para a remoção, pois precisamos costurar o nó pai 
 * ao novo substituto.
 * - **Por trás do capô (Memória):** Diferente da busca recursiva que gasta memória 
 * Stack empilhando funções, esta abordagem usa um simples laço `while`. É mais 
 * leve e rápida. O ponteiro `pai` é atualizado a cada passo, agindo como uma 
 * "sombra" um passo atrás do ponteiro `atual`.
 * * @param raiz Ponteiro raiz da árvore.
 * @param ch Chave a ser buscada.
 * @param pai [Referência] Variável que receberá o endereço do nó pai.
 * @return PONT O endereço do nó encontrado, ou NULL.
 */
PONT buscaNO(PONT raiz, TIPOCHAVE ch, PONT *pai) {
    PONT atual = raiz;
    *pai = NULL;
    
    while(atual) {
        if(atual->chave == ch) return(atual);
        *pai = atual; // A sombra guarda o nó atual antes dele descer
        
        if(ch < atual->chave) atual = atual->esq;
        else atual = atual->dir;
    }
    return(NULL);
}

// ============================================================================
// @section OPERAÇÕES DE EXCLUSÃO
// ============================================================================

/**
 * @brief Remoção de Nó na Árvore Binária de Pesquisa (Hibbard Deletion)
 * @details Manipula fisicamente a memória para excluir um nó mantendo a propriedade
 * de ordenação. Lida com os três casos estruturais: Folha, Um Filho e Dois Filhos.
 * * @param raiz Ponteiro para a raiz da árvore.
 * @param ch Chave do elemento que queremos aniquilar.
 * @return PONT A nova raiz da árvore (que pode ter mudado se a própria raiz for removida).
 * * @section COMPLEXIDADE (Métrica Big O)
 * - $O(\log N)$ no caso médio (árvore balanceada).
 * - $O(N)$ no pior caso (árvore degradada em lista).
 */
PONT removeNo(PONT raiz, TIPOCHAVE ch) {
    PONT pai, no, p, q;
    
    // 1. Localiza o Alvo e seu respectivo Pai
    no = buscaNO(raiz, ch, &pai);
    if(no == NULL) return(raiz); // Chave não existe, aborta.

    // ---------------------------------------------------------
    // CENÁRIO 1 e 2: O nó possui ZERO ou apenas UM filho
    // ---------------------------------------------------------
    if(!no->esq || !no->dir) {
        // Se a esquerda é vazia, o 'herdeiro' (q) é a direita (mesmo que seja NULL).
        if(!no->esq) q = no->dir; 
        else q = no->esq;
    }
    // ---------------------------------------------------------
    // CENÁRIO 3: O nó possui DOIS filhos
    // ---------------------------------------------------------
    else {
        p = no;
        q = no->esq; // Vai uma vez para a esquerda
        
        // Desce tudo para a direita para achar o PREDECESSOR (o maior dos menores)
        while(q->dir) {
            p = q;
            q = q->dir;
        }
        
        // Faz a costura: o predecessor (q) assume os filhos do nó que vai morrer
        if(p != no) {
            p->dir = q->esq;
            q->esq = no->esq;
        }
        q->dir = no->dir;
    }

    // ---------------------------------------------------------
    // RECONEXÃO COM O PAI E ANQUILAÇÃO FISÍCA (free)
    // ---------------------------------------------------------
    
    // CASO ESPECIAL: O nó removido era a Raiz Principal da árvore
    if(!pai) {
        free(no);
        return(q); // O 'herdeiro' se torna a nova Raiz Principal
    }
    
    // O nó removido era um nó interno. Precisamos conectar o Pai ao 'herdeiro' (q)
    if(ch < pai->chave) pai->esq = q;
    else pai->dir = q;
    
    free(no); // Libera o espaço na memória Heap (Evita Memory Leak)
    return(raiz);
}