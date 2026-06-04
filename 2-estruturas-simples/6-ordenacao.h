#include <stdio.h>
#include <stdbool.h>
#include "5-lista-encadeada.h"

#ifndef ORDENACAO_H
#define ORDENACAO_H

/**
 * @file 6-ordenacao.c
 * @brief MANUAL TÉCNICO: Métodos de Ordenação
 * @date 2026
 *
 * @details Conceitos : Algoritmos de ordenação
 * Algortimos de ordenação são conjuntos de instruções passo a passo criados para organizar
 * uma coleção de dados em uma sequência específica, seja ela crescente, decrescente, alfabética
 * ou cronológica.
 *
 * Ordenar dados é uma das tarefas mais fundamentais e estudadas, afinal, um computador passa
 * grande parte do seu tempo processando, buscando e exibindo informações.
 *
 * A ordenação é extremamente importante para se obter performance e busca.
 * Como vimos nas aulas anteriores, quando os dados estão organizados, o computador não precisa
 * olhar todos os elementos para saber se algo existe ou não. Em listas estáticas puras(vetores),
 * ter os dados ordenados permite o uso da poderosa Busca Binária, que reduz o tempo de procura
 * de O(N) para incríveis O(log N). Ordenar os dados é pagar um preço inicial de processamento
 * para ter buscas quase instantâneas depois.
 *
 * Como classificamos os métodos de ordenação?
 * Existem dezenas de algoritmos de ordenação, e a escolha do "melhor" depende do cenário. Nós os
 * avaliamos com base em três pilares principais:
 *
 * - Complexidade de Tempo (Velocidade):
 *   Quão rápido o algortimo roda conforme a quantidade de dados (N) cresce? Medimos isso usando a
 *   notação Big O, observando o pior caso, o caso médio e o melhor caso.
 *
 * - Complexidade de Espaço (Memória):
 *   O algoritmo consegue organizar os dados no próprio array (chamado de ordenação in-place) ou ele
 *   precisa criar cópias inteiras da lista na memória para conseguir trabalhar?
 *
 * - Estabilidade:
 *   Um algoritmo é "estável" se, ao ordenar uma lista com elementos repetidos, ele mantém a ordem
 *   original de chegada desses elementos iguais.
 *
 * O Cardápio dos Algoritmos Clássicos
 * Aqui estão os métodos mais utilizados pelos programadores, dividos pelo seu poder de fogo:
 *
 * - Bubble Sort | O(N²)
 *   Empurra os maiores valores para o final, trocando vizinhos de lugar.
 *   Apenas didático. É o mais ineficiente em cenários reais.
 *
 * - Selection Sort | O(N²)
 *   Procura o menor valor e o coloca na primeira posição disponível.
 *   Listas pequenas ou quando fazer trocas de memória é muito custoso.
 *
 * - Insertion Sort | O(N²)
 *   Insere um elemento de cada vez na sua posição correta (como organizar cartas na mão).
 *   Listas que já estão quase ordenadas e listas muito pequenas.
 *
 * - Merge Sort | O(N log N)
 *   Divide a lista ao meio até ter elementos únicos, depois os funde aos já ordenados.
 *   Grandes volumes de dados e listas encadeadas.
 *
 * - Quick Sort | O(N log N)
 *   Escolhe um "pivô" e joga os menores para a esquerda e maiores para a direita.
 *   Considerado o algoritmo de uso geral mais rápido na prática para arrays estáticos.
 *
 */

/**
 * @brief Declaração de constantes de controle
 * @details
 * MAX: Define a capacidade máxima de elementos simulando a "memória total".
 * INVALIDO: Atua como o nosso "NULL". Como índices de array vão de 0 a MAX-1,
 * o -1 é perfeito para indicar "fim da lista" ou "não aponta para lugar nenhum".
 */
#define MAX 50
#define INVALIDO -1

/** * @brief Ordenação por Bolha (Bubble Sort)
 * @details CONCEITO (Flutuação dos Maiores):
 * O algoritmo percorre a lista comparando elementos vizinhos. Se o elemento atual for maior
 * que o próximo, eles trocam de lugar. Esse processo se repete várias vezes, fazendo com que
 * os maiores valores "flutuem" para o final da lista como bolhas em um copo d'água.
 *
 * * DIFERENCIAL DESTA IMPLEMENTAÇÃO:
 * Em vez de usar um laço `for` preso aos índices físicos do array, usamos um  laço `while` que
 * segue as trilhas lógicas do campo `prox`. Isso garante  que a ordenação funcione perfeitamente
 * mesmo que os dados estejam fragmentados pela memória do vetor.
 *
 * * @param l Ponteiro para a lista que será ordenada.
 *
 * * @note ANÁLISE COMPARATIVA (Bubble vs. Selection):
 * - Enquanto o Selection Sort procura o menor valor da lista inteira antes de fazer UMA troca,
 *   o Bubble Sort faz VÁRIAS trocas curtas com os vizinhos durante a mesma varredura.
 *
 * - O Bubble Sort possui um mecanismo de "parada inteligente" (a variável `trocou`). Se ele percorrer
 *   a lista inteira e não precisar fazer nenhuma troca, ele  sabe que a lista já está perfeitamente
 *   ordenada e encerra a execução mais cedo.
 *
 * * @section COMPLEXIDADE (Métrica Big O)
 * - Pior Caso: O(N²) Se a lista estiver em ordem decrescente.
 * - Melhor Caso: O(N) Se a lista já estiver ordenada, graças à variável `trocou`.
 */
void bubbleSort(LISTA *l)
{
  // Se a lista estiver vazia ou tiver apenas 1 elemento, já está ordenada.
  if (l->inicio == INVALIDO || l->A[l->inicio].prox == INVALIDO)
  {
    return;
  }

  bool trocou; // Flag para monitorar se houve movimentação na varredura atual
  int atual;
  int proximo;
  REGISTRO aux;

  /**
   * @section LAÇO PRINCIPAL (Repetição de Varreduras)
   * Continua rodando varreduras na lista até que uma passagem inteira
   * aconteça sem nenhuma troca (o que significa que tudo está no lugar).
   */
  do
  {
    trocou = false;    // Reseta a flag no início de cada passagem
    atual = l->inicio; // O cursor volta para o começo da lista lógica

    /**
     * @section LAÇO DE COMPARAÇÃO (Varredura Lógica)
     * Caminha do início até o penúltimo elemento válido.
     */
    while (l->A[atual].prox != INVALIDO)
    {
      proximo = l->A[atual].prox; // Descobre quem é o vizinho da frente

      // Se o de trás for maior que o da frente, inverte as cargas úteis.
      if (l->A[atual].reg.chave > l->A[proximo].reg.chave)
      {

        // Troca físcia dos dados (Swap)
        aux = l->A[atual].reg;
        l->A[atual].reg = l->A[proximo].reg;
        l->A[proximo].reg = aux;

        trocou = true; // Sinaliza que a lista ainda não está 100% pronta.
      }
      // Avança o cursor para o próximo elo da corrente
      atual = l->A[atual].prox;
    }
  } while (trocou);
}

/** * @brief Ordenação por Seleção (Selection Sort)
 * @details CONCEITO (Busca pelo Menor):
 * O algoritmo funciona dividindo a lista imaginariamente em duas partes:
 * Uma sublista ordenada (que começa vazia, à esquerda) e uma sublista desordenada
 * (à direita). A cada iteração, ele varre a porção desordenada procurando o MENOR
 * elemento disponível e o troca de lugar fisicamente com o primeiro elemento dessa
 * porção desordenada. Esse ciclo se repete até que toda a lista esteja na porção
 * ordenada.
 *
 * *DIFERENCIAL DESTE ALGORITMO (A Economia de Movimentos):
 * Ele é amplamente reconhecido pela sua eficiência em "escritas na memória".
 * Como ele varre toda a sublista antes de tomar qualquer decisão, ele realiza
 * no máximo UMA única troca de posição por ciclo. Se o custo de reescrever um
 * dado na memória for muito alto (como em bancos de dados antigos ou hardwares
 * limitados), ele brilha muito mais que métodos baseados em trocas constantes.
 *
 * * @param l Ponteiro para a lista que será ordenada.
 * * @param n Tamanho total de elementos válidos no array.
 *
 * * @note ANÁLISE COMPARATIVA (Selection vs. Bubble):
 * - Enquanto o Bubble Sort é "ansioso" e sai trocando vizinhos de lugar inúmeras
 *   vezes na mesma varredura, o Selection Sort é "paciente": ele olha todo mundo,
 *   elege o menor e faz UMA única troca cirúrgica.
 *
 * - A grande desvantagem do Selection Sort é que ele é "cego" para a ordem pré-existente
 *   dos dados. Diferente do bubble Sort com sua variável 'trocou', o selection Sort NÃO
 *   possui mecanismo de "parada precoce". Ele sempre vai executar os dois laços aninhados
 *   até o fim, comparando tudo, mesmo que a lista já esteja 100% ordenada desde o ínicio.
 *
 *  *@section COMPLEXIDADE (Métrica Big O)
 * - Pior caso:     O(N²) vai realizar todas as comparações possíveis.
 * - Melhor caso:   O(N²) Diferente do Bubble Sort, não há atalhos. Mesmo se a lista já vier
 *   ordenada, o tempo de execução será exatamente o mesmo.

 * * @note ATENÇÃO À ESTRUTURA (Fragmentação):
 * Este código realiza uma ordenação FÍSICA dos índices de 0 até n-1.
 * Em uma Lista Encadeada Estática, isso só funcionará com segurança se a  lista for recém-
 * criada (sem fragmentação por exclusões), pois as exclusões deixam "buracos" no meio do
 * array (espaços devolvidos ao 'dispo').
*/

/**
 * @brief FUNÇÃO AUXILIAR: Encontra a posição física do menor elemento
 * @details Varre o array a partir de um índice inicial ('inicio') até o fim ('n')
 * procurando qual é a gaveta que guarda a menor chave.
 * * @param l Ponteiro para a lista
 * @param inicio Índice de onde a busca deve começar
 * @param n Quantidade total de elementos válidos
 * @return O índice físico (int) do menor elemento encontrado, ou -1 se erro.
 */
int posMenorEl(LISTA *l, int inicio)
{

  int posMenor = -1;  // Começa assumindo um valor inválido por segurança
  int n = tamanho(l); // Função que retorna o tamanho da lista

  // Validação de segurança
  if (l != NULL && inicio >= 0 && inicio < n)
  {
    posMenor = inicio; // Assume que o primeiro da fila é o menor

    // Laço de varredura
    for (int i = inicio + 1; i < n; i++)
    {
      if (l->A[i].reg.chave < l->A[posMenor].reg.chave)
      {
        posMenor = i; // Atualiza o índice com o menor valor
      }
    }
  }
  return posMenor;
}

/**
 * @brief Ordenação por Seleção (Abordagem Modular)
 * @details Delega a busca pelo menor elemento para a função posMenorEl().
 * * @param l Ponteiro para a lista
 * * @param n Quantidade total de elementos válidos
 */
void selectionSortModular(LISTA *l, int n)
{
  // Se a lista não existir ou tiver 1 elemento ou menos, saia.
  if (l != NULL || n <= 1)
    return;

  // Laço principal que avança a fronteira da parte ordenada
  for (int i = 0; i < n - 1; i++)
  {

    // Delega o trabalho pesado de buscar o índice para a função auxiliar
    int posMenor = posMenorEl(l, i);

    /**
     * @section PROCESSO DE TROCA (Com Trava de Segurança)
     * O if abaixo garante que só faremos esforço de memória (a troca física)
     * se a chave encontrada for ESTRITAMENTE MENOR que a chave atual.
     * Isso evita trocar um  número por ele mesmo.
     */
    if (posMenor != INVALIDO && l->A[posMenor].reg.chave < l->A[i].reg.chave)
    {

      // Swap (Troca física dos registros)
      REGISTRO aux = l->A[i].reg;
      l->A[i].reg = l->A[posMenor].reg;
      l->A[posMenor].reg = aux;
    }
  }
}

/** *@brief Ordenação por Inserção (Insertion Sort)
 * @details CONCEITO (Organizando Cartas)
 * O algoritmo finge que o primeiro elemento já está ordenado. Depois, ele pega o segundo
 * elemento e o "insere" na posição correta em relação ao primeiro.
 * Em seguida, pega o terceiro e o insere na posição correta em relação aos dois primeiros,
 * e assim por diante. Ele faz isso EMPURRANDO OS ELEMENTOS MAIORES PARA A DIREITA para
 * abrir espaço para o elemento atual.
 *
 * *DIFERENCAL DESTE ALGORITMO (Deslocamento vs Troca):
 * Note que dentro do laço 'while', nós NÃO fazemos o clássico "swap" (troca com variável
 * auxiliar) que usávamos no Bubble e Selection. Nós simplesmente COPIAMOS o elemento anterior
 * para a casa da frente ('v[j] = v[j-1]'). A inserção real (escrita do dado) só acontece uma
 * vez por rodada, fora do 'while'.
 *
 * * @param l Ponteiro para a lista ordenada.
 * * @param n tamanho total de elementos válidos no array.
 *
 * * @note ANÁLISE COMPARATIVA (Insetion vs. Selection):
 * - O Selection Sort é cego e roda O(N²)sempre. O Insertion Sort é inteligente:
 *   Se ele olha para trás e o vizinho  já for menor,  laço 'while' nem executa.
 * - Isso torna o Insertion Sort o "Rei das Listas Quase Ordenadas". Se você adicionar
 *   um item novo no final de uma lista já ordenada, o Insertion Sort arruma a lista em
 *   tempo quase instantâneo.
 *
 * * @section COMPLEXIDADE (Métrica Big O)
 * - Pior caso: O(N²)   (Se a lista estiver em ordem decrescente, ele terá que empurrar tudo).
 * - Melhor caso: O(N)  (Se a lista já estiver ordenada, o 'while' nunca roda).
 */
void insertionSort(LISTA *l, int n)
{
  // Se a lista estiver vazia ou tiver apenas 1 elemento, já está ordenada.
  if (l != NULL || n <= 1)
    return;

  // 'i' representa o elemento que estamos segurando na mão para inserir
  for (int i = 1; i < n; i++)
  {

    // aux guarda a "carta" que retiramos da lista
    REGISTRO aux = l->A[i].reg;

    // 'j' será o nosso cursor para olhar as cartas que estão para trás
    int j = i;

    /**
     * @section LAÇO DE DESLOCAMENTO (Abrindo Espaço)
     * Enquanto j não bater o limite esquerdo (j > 0(indice)) e a carta que estamos segurando (aux) for
     * menor que a carta anterior (j-1)...
     */
    while ((j > 0) && (aux.chave < l->A[j - 1].reg.chave))
    {

      // Empurramos a carta maior uma casa para a direita
      l->A[j].reg.chave = l->A[j - 1].reg.chave;

      // Andamos com o cursor para trás para continuar comparando
      j--;
    }

    /**
     * @section INSERÇÃO FINAL
     * O espaço foi aberto. 'j' parou exatamente na gaveta onde a nossa carta 'aux' deve ser
     * colocada.
    */
    l->A[j].reg = aux;
        
  }
}

#endif
