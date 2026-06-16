/**
 * @file 2-arvores-binarias-de-pesquisa.c
 *
 * @details Conceito: Regra para poscionamento dos valores na árvore:
 * Uma árvore binária de pesquisa é uma árvore binária em que, a cada nó, todos os registros
 * com chaves MENORES que a deste nó estão na subárvore da ESQUERDA, enquanto que os registros
 * com chaves MAIORES estão na subárvore da DIREITA.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "1-conceitos-estruturais-binary-tree.h"

/**
 * @brief ABP - Inicialização da árvore
 * Para representarmos nossa árvore, precisaremos tão somente do endereço do nó raiz.
 * E para inicializarmos a árvore basta tormarmos esse endereço null, criando árvore vazia.
 */
PONT inicializarArvore()
{
  return (NULL);
}

/** @brief ABP - Inserção
 * Se a raiz for null, inserimos o valor.
 * Senão:
 *  Se a chave do elemento a ser inserido for menor que a da raiz:
 *    insere na subárvore da esquerda
 *  Senão:
 *    Insere na subárvore da direita
 * 
 * @note Neste algoritmos ignoramos chaves iguais.
 *
 */
PONT adicionar(PONT raiz, PONT no)
{
  if (raiz == NULL)
    return (no);
  if (no->chave < raiz->chave)
  {
    raiz->esq = adicionar(raiz->esq, no);
  }
  else
  {
    raiz->dir = adicionar(raiz->dir, no);
  }
  return(raiz);
}


/** @brief Função que aloca memória para um novo nó, inicializando os campos da estrutura  */
PONT criarNovoNo(TIPOCHAVE ch) {
  PONT novoNo = (PONT)malloc(sizeof(NO));
  novoNo->esq = NULL;
  novoNo->dir = NULL;
  novoNo->chave = ch;
  return(novoNo);
}


/**
 * @brief Busca Recursiva em Árvore Binária de Busca (ABP / BST)
 * @details 
 * - **O que faz:** Procura uma chave navegando de forma ramificada pela árvore.
 * - **Por trás do capô:** Aproveita a propriedade de ordenação da árvore para 
 * tomar decisões binárias (ir para a esquerda ou para a direita), evitando a 
 * necessidade de olhar todos os elementos da estrutura.
 * * * @param ch Chave inteira que estamos rastreando.
 *     @param raiz Ponteiro para o nó atual (no início, é a raiz principal).
 *     @return PONT Endereço do nó na Heap se localizado; ou `NULL` se não existir.
 * 
 */
PONT contem(TIPOCHAVE ch, PONT raiz) {
  // CASO BASE 1: A busca falhou. Chegamos em uma folha vazia (NULL).
  if (raiz == NULL) return(NULL);

  // CASO BASE 2: Sucesso! O nó atual carrega exatamente a chave buscada.
  if (raiz->chave == ch) return(raiz);

  // PASSO RECURSIVO 1: Se a chave do nó atual for maior do que o que eu busco,
  // significa que o meu alvo é menor. Portanto, deve estar na subárvore ESQUERDA.
  if (raiz->chave > ch) return(contem(ch, raiz->esq));

  // PASSO RECURSIVO 2: Se não caiu em nenhuma das regras anteriores, o alvo
  // obrigatoriamente é maior que o nó atual. Portanto, deve estar na DIREITA
  return(contem(ch, raiz->dir));
}


/**
 * @brief Contagem Total de Nós na Árvore (Abordagem Recursiva)
 * @details 
 * Existem n maneiras de se percorrer uma árvore binária, em geral envolvendo três
 * elementos:
 * 
 * - O nó raiz
 * - A subárvore da esqueda de cada nó
 * - A subárvore da direita de cada nó
 * 
 * Em relação a árvores binárias de pesquisa, uma ordem bastante útil é:
 * subárvore esquerda -> raiz -> subárvore direita
 * 
 * Essa ordem também é chamada de inorder tranversal, varredura infixa ou varredura
 * central. Nessa varredura, os nós são visitados na ordem crescente das chaves de busca.
 * 
 * - **O que faz:** Calcula dinamicamente a quantidade de nós alocados na árvore.
 * - **Por trás do capô:** O algoritmo realiza um percurso completo pela estrutura.
 * 
 * Ele desce recursivamente até as folhas de cada subárvore. Conforme as chamadas 
 * chegam ao fim da linha (`NULL`, que retorna 0), os valores vão "subindo" e sendo 
 * somados através da equação: `Esquerda + 1 (Nó Atual) + Direita`.
 * 
 * * @param raiz Ponteiro para o nó atual da árvore.
 *   @return int O número total de nós existentes na estrutura.
 */
int numeroNos(PONT raiz) {
  // CASO BASE: Se o ponteiro for nulo, chegamos ao fim de um ramo. 
  // Uma árvore vazia possui zero nós.
  if (!raiz) return 0;

  // PASSO RECURSIVO: O total de nós sob o ponto de vista do nó atual é:
  // a quantidade de nós do seu lado esquerdo, mais 1 (ele mesmo), mais o seu lado direito.
  return(numeroNos(raiz->esq) + 1 + numeroNos(raiz->dir));
}


/**
 * @brief Exibição Textual Estruturada da Árvore (Varredura Pré-Fixa / Pre-order)
 * @details 
 * - **O que faz:** Imprime a árvore no console em uma única linha, utilizando 
 * colchetes para delimitar escopos e hierarquias de forma visual.
 * 
 * - **Por trás do capô:** Segue a ordem estrita de Visitação Pré-Fixa (Raiz, 
 * Subárvore Esquerda, Subárvore Direita). A inclusão dos caracteres '[' e ']' 
 * cria um aninhamento perfeito que reflete a profundidade de cada nó na Heap.
 * 
 * * @param raiz Ponteiro para o nó atual (no início, a raiz principal).
 */
void exibirArvore(PONT raiz) {
  // CASO BASE IMPLÍCITO: Se o nó for NULL, a função simplesmente termina sem fazer nada.
  if (raiz != NULL) {

    // 1. VISITA A RAIZ: Imprime o valor do nó atual imediatamente
    printf("%i", raiz->chave);
    // 2. ABRE ESCOPO: Sinaliza que estamos prestes a descer um nível na hierarquia
    printf("[");
    // 3. EXPLORA A ESQUERDA: Desce recursivamente para processar os menores
    exibirArvore(raiz->esq);
    // 4. EXPLORA A DIREITA: Desce recursivamente para processar os maiores
    exibirArvore(raiz->dir);
    // 5. FECHA ESCOPO: Sinaliza que este nó e todos os seus descendentes foram processados
    printf("]");
  }
}


int main()
{

  // 1. Inicializa o controle da árvore na Stack (Aponta para NULL)
  PONT r = inicializarArvore();

  /**
   * @section ALOCAÇÃO DINÂMICA
   * Criamos 3 nós independentes na memória Heap. 
   * Cada chamada do 'criarNovoNo' faz um 'malloc' isolado.
   */
  PONT no = criarNovoNo(23);
  PONT no1 = criarNovoNo(12);
  PONT no2 = criarNovoNo(24);

  /**
   * @section CONSTRUÇÃO DA ÁRVORE (Costura de Ponteiros)
   * O ponteiro 'r' (raiz) recebe o resultado de cada inserção para o caso
   * de a raiz principal precisar ser atualizada ou remanejada.
   */
  r = adicionar(r, no);     // 23 vira a Raiz Principal
  r = adicionar(r, no1);    // 12 cai à esquerda do 23
  r = adicionar(r, no2);    // 24 cai à direita do 23

  /**
   * @section TESTE DE BUSCA DEFENSIVA
   * Buscamos a chave 12. Como ela foi adicionada acima, o ponteiro 'p'
   * receberá o endereço real do nó 'no1' na Heap.
   */
  PONT p = contem(12, r);
  if(p != NULL) {
    printf("\n[Sucesso] A chave foi encontrada.\n");
    printf("Dados do registro: %d\n", p->chave);
  } else {
    printf("[Erro] Chave nao encontrada.\n");
  }

  /**
   * @section MÉTRICAS E EXIBIÇÃO
   * - numeroNos(r) deve exibir o valor 3 no console.
   * - exibirArvore(r) fará a varredura (In-order, provavelmente) mostrando: 12 23 24.
   */
  printf("\nQuantidade atual de nos na arvore: %d\n", numeroNos(r));

  printf("\nEstrutura logica da arvore:\n");
  exibirArvore(r);

  return 0;
}
