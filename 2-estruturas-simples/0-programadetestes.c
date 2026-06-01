/**
 * @section PROGRAMA PRINCIPAL (Ambiente de Testes Interativo)
 * @details Este bloco funciona como o painel de controle do laboratório.
 * Ele oferece uma interface amigável via console para que você possa manipular
 * a Lista Encadeada Estática e observar como as funções criadas reagem.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "5-lista-encadeada.h"
#include "6-ordenacao.h"

// Protótipos das funções para que o compilador as reconheça antes da main
void inicializarLista(LISTA *l);
int tamanho(LISTA *l);
void exibirLista(LISTA *l);
int buscaSequencialOrdenada(LISTA *l, TIPOCHAVE ch);
bool inserirElemListaOrdenada(LISTA *l, REGISTRO reg);
bool excluirElemLista(LISTA *l, TIPOCHAVE ch);
void reinicializarLista(LISTA *l);
void bubbleSort(LISTA *l);

// Funções de Seleção Modular
int posMenorEl(LISTA *l, int inicio);
void selectionSortModular(LISTA *l, int n);

int main()
{
  LISTA minhaLista;
  inicializarLista(&minhaLista);

  int opcao;
  REGISTRO reg;
  TIPOCHAVE chaveBusca;
  int indiceEncontrado;

  do
  {
    printf("\n=========================================\n");
    printf("   MENU: LISTA ENCADEADA ESTATICA\n");
    printf("=========================================\n");
    printf(" 1 - Inserir Elemento (Ordenado)\n");
    printf(" 2 - Excluir Elemento\n");
    printf(" 3 - Buscar Elemento\n");
    printf(" 4 - Exibir Lista (Ordem Logica)\n");
    printf(" 5 - Mostrar Tamanho Atual\n");
    printf(" 6 - Ordenar itens por Bolha (Logica)\n");
    printf(" 7 - Ordenar itens por Selecao (Fisica | Modular)\n");
    printf(" 8 - Reinicializar Lista (Wipe)\n");
    printf(" 0 - Sair do Programa\n");
    printf("=========================================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
      printf("\n->INSERIR ELEMENTO\n");
      printf("Digite o valor da chave inteira: ");
      scanf("%d", &chaveBusca);

      if (inserirElemListaOrdenada(&minhaLista, reg))
      {
        printf("[Sucesso] Elemento %d inserido com sucesso!\n", reg.chave);
      }
      else
      {
        printf("[Erro] Falha ao inserir. Lista cheia ou chave duplicada.\n");
      }
      break;

    case 2:
      printf("\n->EXCLUIR ELEMENTO\n");
      printf("Digite a chave do elemento a remover: ");
      scanf("%d", &chaveBusca);

      if (excluirElemLista(&minhaLista, chaveBusca))
      {
        printf("[SUCESSO] Elemento %d removido e seu nó foi reciclado!\n", chaveBusca);
      }
      else
      {
        printf("[ERRO] Elemento %d nao foi encontrado na lista.\n", chaveBusca);
      }
      break;

    case 3:
      printf("\n->BUSCAR ELEMENTO\n");
      printf("Digite a chave que deseja procurar: ");
      scanf("%d", &chaveBusca);

      indiceEncontrado = buscaSequencialOrdenada(&minhaLista, chaveBusca);
      if (indiceEncontrado != INVALIDO)
      {
        printf("[ACHOU] A chave %d existe! Guardada no indice fisico [%d].\n", chaveBusca, indiceEncontrado);
      }
      else
      {
        printf("[AVISO] Chave %d nao encontrada na estrutura.\n", chaveBusca);
      }
      break;

    case 4:
      printf("\n-> EXIBIÇÃO LOGICA\n");
      exibirLista(&minhaLista);
      break;

    case 5:
      printf("\n-> METRICAS DE TAMANHO\n");
      printf("A lista contem atualmente %d elmento(s) valido(s).\n", tamanho(&minhaLista));
      break;

    case 6:
      printf("\n-> ORDENACAO BUBBLE SORT\n");
      bubbleSort(&minhaLista);
      printf("[CONCLUIDO] Corrente logica reordenada via Bubble Sort!\n");
      exibirLista(&minhaLista);
      break;

    case 7:
      printf("\n-> ORDENACAO POR SELECAO\n");
      selectionSortModular(&minhaLista, tamanho(&minhaLista));
      printf("[CONCLUIDO] Ordenacao por Selecao Modular aplicada!\n");
      exibirLista(&minhaLista);
      break;

    case 8:
      printf("\n-> REINICIALIZANDO ESTRUTURA\n");
      reinicializarLista(&minhaLista);
      printf("[LIMPA] A lista foi resetada para o estado de fábrica!\n");

    case 0:
      printf("\nEncerrando os testes...");
      break;

    default:
      printf("\n[OPCAO INVALIDA] Escolha um numero do menu (0 a 8).\n");
    }
  } while (opcao != 0);
  return 0;
}