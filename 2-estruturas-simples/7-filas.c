/**
 * @file fila_circular.c
 * @brief Estudo e implementação de uma estrutura de dados do tipo Fila Circular.
 * @details Este código demonstra o funcionamento de uma fila estática circular
 * utilizando o operador de resto de divisão (%) para reaproveitamento de memória.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

/**
 * @brief A struct PESSOA guarda os dados que caracterizam uma pessoa no sistema
 */
typedef struct
{
  char nome[30];
  int idade;
} PESSOA;

/**
 * @brief A struct FILA guarda os dados e controla o estado da fila com índices e
 * contador de elementos.
 */
typedef struct
{
  PESSOA itens[MAX]; /**< Vetor estático para armazenamento dos elementos. */
  int inicio;        /**< Índice do elemento que está na frente da fila (próximo a sair). */
  int fim;           /**< Índice da posição onde o próximo elemento será inserido. */
  int total;         /**< Contador total de elementos atualmente presentes na fila. */
} FILA;

/* --- Funções de Gerenciamento --- */

/**
 * @brief Inicializa os controles da fila, definindo-a como vazia.
 * @param f Ponteiro para a estrutura FILA que será inicializada.
 */
void inicializarFila(FILA *f)
{
  f->inicio = 0; // O primeiro elemento será removido da posição 0
  f->fim = 0;    // O primeiro elemento será inserido na posição 0
  f->total = 0;  // A fila começa com zero elementos
}

/**
 * @brief Verifica se a fila possui espaço livre para novas inserções.
 * @param f Ponteiro para a estrutura FILA.
 * @return 1 se houver espaço disponível, 0 caso contrário.
 */
int filaDisponivel(FILA *f)
{
  return f->total < MAX;
}

/**
 * @brief Verifica se a fila está completamente sem elementos.
 * @param f Ponteiro para a estrutura FILA.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int filaVazia(FILA *f)
{
  return f->total == 0;
}

/**
 * @brief Insere um novo elemento no final da fila (politica FIFO).
 * @details Caso a fila possua espaço, a pessoa é inserida no índice apontado por 'fim'.
 * Logo após, realiza-se o incremento circular do ponteiro 'fim' através da operação
 * matemática `(f->fim + 1) % MAX`, garantindo que o índice retorne a 0 ao atingir o limite.
 *
 * Lógica do incremento circular:
 * Se MAX = 4, os índices válidos são apenas 0, 1, 2 e 3.
 *
 * Passo a passo do cálculo (f->fim + 1) % 4:
 * - Se fim atual é 0: (0 + 1) % 4 = 1 % 4 = Resto 1 (avança para o índice 1)
 * - Se fim atual é 1: (1 + 1) % 4 = 2 % 4 = Resto 2 (avança para o índice 2)
 * - Se fim atual é 2: (2 + 1) % 4 = 3 % 4 = Resto 3 (avança para o índice 3)
 * - Se fim atual é 3: (3 + 1) % 4 = 4 % 4 = Resto 0 (VOLTA para o índice 0)
 */
void inserirNaFila(FILA *f, PESSOA p)
{
  if (f->total == MAX)
  {
    printf("[Erro] Não há mais espaço para armazenar na fila.");
    return;
  }
  f->itens[f->fim] = p;
  // Incremento circular: se f->fim + 1 for igual a MAX, o resto (%) resultará em 0
  f->fim = (f->fim + 1) % MAX; // fim atual é 0: (0 + 1) % 5 = 1 % 5 = Resto 1 (avança para o índice 1)
  f->total++;
}

/**
 * @brief Remove o elemento que está na frente da fila (First-In, First-Out).
 * @details Captura a pessoa localizada no índice 'inicio', copia seus dados para o
 * ponteiro de saída e avança o índice 'inicio' de forma circular utilizando o operador `%`.
 *
 * @param f Ponteiro para a estrutura FILA de onde o elemento será extraído.
 * @param p Ponteiro para a estrutura PESSOA que receberá os dados do elemento removido.
 */
void removerElementodaFila(FILA *f, PESSOA *p)
{
  if (filaVazia(f))
  {
    printf("Não há elementos para remover.\n");
    return;
  }

  *p = f->itens[f->inicio];

  // Avanço circular do índice de remoção para reaproveitamento de memória
  f->inicio = (f->inicio + 1) % MAX;
  f->total--;
}
/**
 * @brief Exibe na tela todos os elementos da fila em ordem cronológica de chegada.
 *
 * @details Este método utiliza uma lógica de varredura circular separada por etapas.
 * Em uma Fila Circular baseada em vetor, os dados se deslocam rotativamente. Por isso,
 * NÃO podemos usar um laço simples acessando `f->itens[i]` (onde i começa em 0), pois causaria:
 *
 * 1. LEITURA DE LIXO DE MEMÓRIA: Após remoções, o `f->inicio` avança (ex: para a posição 1).
 *    Um laço linear leria a posição 0 (dado antigo/inválido) e ignoraria o último elemento.
 *
 * 2. QUEBRA DA REGRA FIFO (First-In, First-Out): Se a fila "der a volta" no vetor
 *    (ex: início na posição 4 e fim na posição 0), o laço linear imprimiria a posição 0
 *    antes da 4, invertendo a ordem real de quem chegou primeiro.
 *
 * SOLUÇÃO ADOTADA (VERSÃO SEPARADA):
 * - `idx`: Variável externa inicializada no início real da fila (`f->inicio`) para rastrear a memória.
 * - `i`: O laço `for` agora atua estritamente como um contador de voltas baseado em `f->total`,
 *        garantindo que o código pare antes de ler células vazias.
 * - `idx = (idx + 1) % MAX`: Atualização manual feita no fim do bloco para avançar de forma circular.
 *
 * @param f Ponteiro para a estrutura da fila que será exibida.
 */
void exibirFila(FILA *f)
{
  printf("Fila: ");

  // 1. Inicializa o índice de leitura no início real da fila
  int idx = f->inicio;

  // 2. O laço cuida APENAS de contar o número correto de elementos existentes
  for (int i = 0; i < f->total; i++)
  {

    // 3. Imprime os dados da pessoa apontada pelo índice atual
    printf("[%s, %d] ", f->itens[idx].nome, f->itens[idx].idade);

    // 4. Avança o índice para a próxima posição (retornando a 0 se atingir o fim do vetor)
    idx = (idx + 1) % MAX;
  }
  printf("\n");
}

/**
 * @brief Ponto de entrada do programa para execução dos testes operacionais da fila.
 * @return Código de status de encerramento do programa (0 para sucesso).
 */
int main()
{
  FILA minhaFila;
  PESSOA p, p2;
  strcpy(p.nome, "Thiago Alves");
  p.idade = 30;
  strcpy(p2.nome, "Naty Alves");
  p2.idade = 27;

  inicializarFila(&minhaFila);
  filaDisponivel(&minhaFila);
  inserirNaFila(&minhaFila, p);
  inserirNaFila(&minhaFila, p2);
  removerElementodaFila(&minhaFila, &p);
  exibirFila(&minhaFila);
}