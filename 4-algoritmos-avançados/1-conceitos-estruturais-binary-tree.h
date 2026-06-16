/** @file 1-conceitos-estruturais-binary-tree.h
 * @brief Definição:
 * Diversas aplicações necessitam que se represente um cojunto de objetos e as suas relações
 * hierárquicas.
 * 
 * Uma árvore é uma abstração matemática usada para representar estruturas hierárquicas não
 * lineares dos objetos modelados; em outras palavras, uma árvore é um conjunto de nós consistindo
 * de um nó chamado raiz, abaixo do qual estão as subárvores que compõe essa árvore.
 * 
 * @details Definição
 * - É um tipo especial de grafo (é uma estrutura matemática ou computacional que modela relações
 *   entre objetos). 
 * - Uma árvore é definida usando um conjunto de nós (ou vértices) e arestas.
 * - Qualquer par de vértices está conectado a apenas uma aresta.
 * 
 * - Vértice
 *   Cada uma das entidades representadas na árvore (depende da natureza do problema);
 *   
 * Basicamente, qualquer problema em que exista algum tipo de hierárquia pode ser represetnado
 * por uma árvore.
 * 
 * @brief Conceitos relativos as árvores
 * 
 * - Raiz
 *   Nó mais alto na árvore, o único que não possui pai.
 * 
 * - Grau
 *   É o número de subárvores de cada nó possui.
 * 
 *   - Nó folha ou terminal | Nós de grau zero
 *   Qualquer nó que não possui filhos.
 * 
 * - Nó interno ou não terminal
 *   Nó que possui ao menos UM filho.
 * 
 * - Pai ou ancestral
 *   Nó antecessor imediato de outro nó.
 * 
 * - Filho
 *   Nó sucessor imediato de outro nó.
 * 
 * - Caminho 
 *   Sequência de nós de modo que existe sempre uma aresta ligado o nó anterior ao seguinte.
 * 
 * @brief Observação
 * Dado um determinado nó da árvore, cada filho seu é considerado a raiz de uma nova sub-árvore.
 * Qualquer nó é a raiz de uma sub-ávore consistindo dele e dos nós abaixo dele.
 * Conceito recursivo.
 * 
 * - Nível
 *   É dado pelo número de nós que existem no caminho entre esse nó e a raiz (nível 0).
 *   Nós são classificados em diferentes níveis.
 * 
 * - Altura
 *   É o número total de níveis de uma árvore.
 *   Comprimento do CAMINHO MAIS LONGO da raiz até uma das suas folhas. 
 * 
 * - Profundidade
 *   É a distância percorrida da raiz determinado nó.
 * 
 * @brief Tipos de árvores
 * Na computação, assim como na natureza, existem vários tipos diferentes de árvores.
 * Cada uma delas foi desenvolvida pensando diferentes tipos de aplicações.
 *  
 *  - árvore binária de busca
 *  - árvore AVL
 *  - árvore Rubro-Negra
 *  - árvore B, B+ e B*
 *  - árvore 2-3
 *  - árvore 2-3-4
 *  - quadtree
 *  - octree
 * 
 * @brief Árvore Binária
 * É um tipo especial de árvore
 * 
 * - Cada nó pode possuir nenhuma, uma ou no máximo duas subárvores.
 *   Sub-árvore da esquerda e a Sub-árvore da direita.
 * 
 * - Usadas em situações onde, a cada passo, é preciso tomar uma decisão entre duas direções.
 * 
 *  @brief Como representar computacionalmente uma árvore binária?
 *  Unindo nós. 
 *  
 * E como representamos os nós?
 * Com 2 ponteiros: Um para a subárvore da esquerda e um para a subárvore da direita, além de
 * um campo para a chave e dados;
 *                         |__  CHAVE  __|
 *                         | null | null |
 */
#include <stdio.h>
#include <stdlib.h>

#ifndef ESTRUTURA_H
#define ESTRTURA_H

#define true 1
#define false 0

typedef int boolean;
typedef int TIPOCHAVE; // Definimos como inteiro mas pode ser de qualquer tipo que desejarmos

// Estrutura que representa o nó
typedef struct aux {
  TIPOCHAVE chave;
  /* Dados armazenados vão aqui */
  struct aux *esq, *dir;
} NO;

typedef NO* PONT;

#endif
