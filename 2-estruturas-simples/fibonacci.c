/**
 * @file fibonacci.c
 * @brief 1 SEQUÊNCIA DE FIBONACCI
 * 
 * Tarefa 1.1 Crie o projeto fibonacci.c.
 * Tarefa 1.2 Crie a classe Fibonacci, conforme mostrado no exemplo 1.
 *   Em C, a "classe" é representada como uma struct.
 * 
 * Tarefa 1.3 Crie o objeto fib e envie a mensagem fib.calcular(). 
 *   Qual o último número da sequência de Fibonacci mostrado?
 *   Resposta: 987 (considerando limite padrão 1000)
 * 
 * Tarefa 1.4 Acrescente a variável limite:int na classe Fibonacci.
 *   Representada pelo campo 'limite' na struct.
 * 
 * Tarefa 1.5 Acrescente o método mudarLimite(novo:int):void, 
 *   responsável por alterar o valor da variável limite.
 * 
 * Tarefa 1.6 Altere o método calcular() de modo que a condição de 
 *   parada seja o valor da variável limite.
 * 
 * Tarefa 1.7 Crie o objeto fib, envie a mensagem fib.mudarLimite(1000),
 *   seguida da mensagem fib.calcular(). 
 *   A sequência produzida é igual à anterior? Sim.
 * 
 * Tarefa 1.8 Qual o último número da sequência quando limite tem o 
 *   valor 5000?
 *   Resposta: 4181
 */
#include <stdio.h>
#include <stdlib.h>

/** Varáveis globais */
int f0;
int f1;
int f2;

void limparBuffer() {
  int c;
  while ( (c = getchar()) != '\n' && c != EOF);
}

int definirNumeroLimite() {
  int limite;
  printf("Defina o valor limite para calcular...");
  scanf("%d", &limite);
  limparBuffer();
  return limite;
}

void calcular(int limite) {
  f0 = 0;
  f1 = 1;
  f2 = f1 + f0;
  printf("%d", f0);
  if (f1 < limite) printf(", %d", f1);

  while(f2 < limite) {
    printf(", %d", f2);
    f0 = f1;
    f1 = f2;
    f2 = f1 + f0;
  }
  printf("\n");

}

int main () {
  
  printf("\n====== SEQUENCIA DE FIBONACCI ======\n");
  int limite = definirNumeroLimite();
  calcular(limite);

  return 0;
}
