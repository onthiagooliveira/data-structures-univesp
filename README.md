# Estudos de Estrutura de Dados e Linguagem C (Univesp)

Repositório destinado ao acompanhamento da disciplina de Estrutura de Dados, com foco no aprendizado aprofundado da linguagem C, manipulação de memória (RAM) e implementação manual de algoritmos. Ao final deste estudo, este repositório servirá como uma **Apostila e Manual Técnico** de consulta rápida.

## Sobre a Matéria

A disciplina de **Estrutura de Dados** em C é o alicerce para qualquer desenvolvedor de software que deseja entender como o computador realmente opera. Ao contrário de linguagens de alto nível com *Garbage Collectors* (como Java ou C#), o C exige que o programador gerencie a memória manualmente, utilizando ponteiros e alocação dinâmica.

Os principais pilares deste estudo são:
* **Abstração de Dados:** Uso de `struct` e `typedef` para criar tipos de dados personalizados.
* **Gerenciamento de Memória:** Compreensão profunda da *Stack* (memória estática de escopo) vs *Heap* (memória dinâmica) e uso seguro de `malloc` e `free`.
* **Estruturas Lineares e Ramificadas:** Implementação de Listas Ligadas, Pilhas, Filas e Árvores.
* **Algoritmos de Busca e Ordenação:** Análise de eficácia, comportamento de ponteiros e complexidade algorítmica (Métrica Big O).

---

## Checklist de Progresso (Baseado na Playlist Univesp)
<a href="https://youtu.be/x2DwllnUZDg?si=KxwuFHjeaaaPDFU-" target="new-blank">Acessar PlayList Oficial</a>

### Módulo 1: Introdução e Fundamentos
- [x] Introdução à Disciplina
- [x] Tipos de Dados e Variáveis (`int`, `bool`, etc.)
- [x] Operadores e Expressões
- [x] Estruturas de Controle (Laços `for`, `while`, `do-while` e Condicionais)

### Módulo 2: Modularização e Memória
- [x] Funções, Escopo e Passagem por Referência
- [x] Introdução a Ponteiros (Acesso à memória física e lógica)
- [x] Vetores e Arrays (Uso em Estruturas Estáticas)
- [x] Alocação Dinâmica de Memória (`malloc`, `free` e prevenção de *Memory Leaks*)

### Módulo 3: Organização de Dados e Ordenação
- [x] Registros (`Structs`) e Tipos Abstratos de Dados (TAD)
- [x] Listas Lineares Sequenciais (Implementação Estática)
- [x] Algoritmos de Ordenação (Análise Big O e Testes de Mesa)
  - [x] *Bubble Sort* (Flutuação com laços lógicos)
  - [x] *Selection Sort* (Busca pelo menor e implementação modular)
  - [x] *Insertion Sort* (Deslocamento análogo a cartas de baralho)
- [x] Listas Ligadas Dinâmicas Simples
- [ ] Listas Ligadas Duplamente Encadeadas
- [ ] Pilhas (Stacks) e Filas (Queues)

### Módulo 4: Estruturas Avançadas
- [x] Recursividade (Conceitos da Pilha de Execução)
- [x] Árvores Binárias (Mecânica e Varreduras: Pré-fixa, In-fixa, Pós-fixa)
- [x] Árvores Binárias de Pesquisa / ABP (Inserção, Busca, Contagem e Remoção de Nós)
- [ ] Árvores Balanceadas (AVL / Red-Black)
- [ ] Tabelas Hash e Espalhamento

---

## Convenções de Código e Design Adotadas no Laboratório

* **Linguagem:** C (Padrão ANSI)
* **Nomenclatura:** Funções e variáveis em Português para máxima clareza didática e aderência ao material universitário (ex: `exibirArvore`, `inserirElemListaOrd`).
* **Documentação (Manual Técnico):** Padrão rigoroso baseado em **Doxygen**, contendo as seções:
  * `@brief`: Resumo da operação.
  * `@details`: Explicação teórica do comportamento "Por trás do capô" na memória RAM.
  * `@section COMPLEXIDADE`: Análise assintótica (Big O) de tempo e espaço.
* **Gerenciamento de Memória e Segurança:** * Todo ponteiro de retorno em buscas é validado preventivamente (`if (p != NULL)`).
  * Sempre utilizar `free()` após `malloc()` para destruição de nós excluídos.
  * *Wipe* seguro em reinicializações de estruturas dinâmicas, destruindo nó por nó.
