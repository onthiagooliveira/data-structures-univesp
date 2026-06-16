/**
 * @file 5-lista-encadeadaDinamica.c
 * @brief MANUAL TÉCNICO: Lista Encadeada | Linked List (Implementação Dinâmica)
 * @details Alocaremos e desalocaremos a memória para os elementos sob demanda (Heap).
 */
#include <stdio.h>
#include <stdlib.h> // Para malloc e free
#include <stdbool.h> // Biblioteca nativa para booleanos em C

// --- MODELAGEM DOS DADOS (A Arquitetura da Estrutura) ---

/** * @brief 1. Tipo da Chave (O Identificador)
 * Usamos 'typedef' para criar um apelido lógico. Se amanhã decidirmos que a 
 * chave de busca do nosso sistema não será mais um 'int', mas sim um 'float', 
 * mudamos apenas esta linha e o código inteiro se adapta magicamente.
 */
typedef int TIPOCHAVE;

/** * @brief 2. O Registro (A Carga Útil)
 * É aqui que ficam as informações reais que queremos guardar no sistema.
 * Separar o REGISTRO da mecânica da lista é uma excelente prática de design.
 * Pense no Elemento como o "caminhão" e no Registro como a "carga".
 */
typedef struct {
    TIPOCHAVE chave;
    // Aqui poderiam entrar: char nome[50]; int idade; float salario; etc.
} REGISTRO;

/** * @brief 3. O Elemento / Nó (O Vagão do Trem)
 * Esta é a engrenagem central da Lista Dinâmica. Ela possui dois compartimentos:
 * 1º: A carga útil (nosso REGISTRO armazenando os dados).
 * 2º: A corrente (um ponteiro chamado 'prox' que guarda o ENDEREÇO do próximo vagão).
 * * * NOTA SOBRE O 'struct aux': Precisamos dar esse nome temporário ('aux') porque 
 * dentro da própria estrutura nós declaramos um ponteiro para ela mesma. O C 
 * precisa desse nome para entender a referência antes de fechar o 'typedef'.
 */
typedef struct aux {
    REGISTRO reg;
    struct aux *prox; 
} ELEMENTO;

/** * @brief 4. Ponteiro para Elemento (O Apelido Facilitador)
 * Em vez de escrevermos "ELEMENTO *" (com asterisco) por todo o código, 
 * criamos o apelido "PONT". Isso mascara a complexidade visual do ponteiro 
 * e deixa a leitura das funções muito mais limpa e fluida.
 */
typedef ELEMENTO *PONT;

/** * @brief 5. A Estrutura Gerenciadora (A Locomotiva)
 * Por que criar uma struct só para guardar o ponteiro de 'inicio'?
 * Pelo conceito de escalabilidade! Se no futuro você quiser otimizar a lista
 * adicionando um campo `int tamanhoTotal` ou um ponteiro `PONT fim` para achar
 * o último elemento rápido, você adiciona aqui dentro. Isso evita que você 
 * tenha que reescrever todas as funções do seu sistema.
 */
typedef struct {
    PONT inicio;
} LISTA;

// --- FUNÇÕES GERENCIADORAS ---
/**
 * @brief Inicialização da Estrutura
 * @details 
 * - **O que faz:** Define o ponto de partida da lista.
 * - **Por trás do capô:** thu. Sem essa inicialização, o ponteiro conteria um
 * "endereço lixo" da memória, fazendo o programa tentar acessar regiões proibidas
 * (causando *Segmentation Fault*).
 * - **Complexidade:** O(1) — Tempo constante, uma única atribuição na memória.
 * * @param l Ponteiro para a estrutura de controle da lista.
 */
void inicializarLista(LISTA *l) {
    l->inicio = NULL;
}


/**
 * @brief Contador de Elementos (Caminhada Linear)
 * @details 
 * - **O que faz:** Varre a lista inteira do primeiro ao último nó para contar o tamanho.
 * - **Por trás do capô:** Como optamos por não gastar memória guardando uma variável 
 * `tamanho` na struct, precisamos criar um cursor dinâmico (`end`). Esse cursor pula
 * de gaveta em gaveta na memória Heap seguindo a trilha do ponteiro `->prox`. O laço
 * só para quando encontra o valor `NULL`, que sinaliza o fim da linha.
 * - **Complexidade:** O(N) — Tempo linear. Quanto maior a lista, mais nós precisamos visitar.
 * * @param l Ponteiro para a lista.
 *   @return int Quantidade de elementos válidos atualmente alocados.
 */
int tamanho(LISTA *l) {
    PONT end = l->inicio;
    int tam = 0;
    while (end != NULL) {
        tam++;
        end = end->prox; // O cursor assume o endereço do próximo nó da Heap
    }
    return tam;
}


/**
 * @brief Exibição e Impressão de Dados
 * @details 
 * - **O que faz:** Imprime na tela a chave de todos os registros em ordem lógica.
 * - **Por trás do capô:** Semelhante à função `tamanho`, ela realiza uma varredura
 * linear pela Heap. A diferença é que, a cada parada do cursor `end`, ela acessa a
 * carga útil do nó (`end->reg.chave`) e renderiza o valor no console.
 * - **Complexidade:** O(N) — Tempo linear devido à necessidade de visitar todos os nós.
 * * @param l Ponteiro para a lista.
 */
void imprimirLista(LISTA *l) {
    PONT end = l->inicio;
    printf("Lista: \" ");
    while (end != NULL) {
        printf("%i ", end->reg.chave);
        end = end->prox;
    }
    printf("\"\n");
}


/**
 * @brief Busca Sequencial Padrão (Lista Desordenada)
 * @details 
 * - **O que faz:** Procura por uma chave varrendo a lista do início ao fim.
 * - **Por trás do capô:** Avalia nó por nó. Se encontrar a chave, interrompe o laço
 * imediatamente e devolve o endereço exato da memória Heap onde aquele nó está.
 * Se chegar ao final da lista (`NULL`) sem encontrar nada, retorna `NULL`.
 * - **Complexidade:** * 
 * - Melhor Caso: O(1) (Se o elemento for o primeiro da lista).
 * - Pior Caso: O(N)   (Se o elemento for o último ou não existir).
 * * @param l Ponteiro para a lista.
 *   @param ch Chave inteira que estamos procurando.
 *   @return PONT Endereço do nó encontrado ou `NULL` caso não exista.
 */
PONT buscaSequencial(LISTA *l, TIPOCHAVE ch) {
    PONT pos = l->inicio;
    while (pos != NULL) {
        if (pos->reg.chave == ch) {
            return pos; // Interrompe a busca e retorna o endereço físico da Heap
        }
        pos = pos->prox;
    }
    return NULL;
}


/**
 * @brief Busca Sequencial com Ponteiro Predecessor (A Chave de Ouro da Estrutura)
 * @details 
 * - **O que faz:** Encontra a posição correta de uma chave e, **crucialmente**, 
 * guarda o endereço do nó que vem logo ATRAZ dela.
 * - **Por trás do capô:** Em uma lista dinamicamente ligada simples, os nós só sabem
 * quem vem *depois* deles; eles são cegos para quem está *atrás*. Para podermos
 * inserir ou remover um nó no meio da lista, precisamos atualizar o ponteiro do nó 
 * anterior. Esta função resolve isso usando um ponteiro de ponteiro (`PONT* ant`) que 
 * funciona como uma "sombra", caminhando sempre um nó atrás do ponteiro `atual`.
 * - **Vantagem da Ordenação:** Como a lista é ordenada, o laço `while` tem uma parada
 * inteligente (`atual->reg.chave < ch`). Se ele encontrar um número maior do que a
 * chave buscada, ele para ali mesmo, pois sabe que dali para frente ninguém mais será igual.
 * - **Complexidade:** $O(N)$ no pior caso.
 * * @param l Ponteiro para a lista.
 * @param ch Chave alvo da busca ou inserção.
 * @param ant [Retorno por Referência] Ponteiro que receberá o endereço do nó anterior.
 * @return PONT Endereço do nó atual se ele já existir (duplicado), ou `NULL` se estiver livre.
 */
PONT buscaSequencialExc(LISTA* l, TIPOCHAVE ch, PONT* ant) {
    *ant = NULL; // Presume inicialmente que não há predecessor (caso seja o início)
    PONT atual = l->inicio;
    
    // Avança enquanto houver nós e a chave atual for menor que a chave desejada
    while ((atual != NULL) && (atual->reg.chave < ch)) {
        *ant = atual;       // A "sombra" salva o nó atual antes dele avançar
        atual = atual->prox; // O atual avança para o próximo elo
    }
    
    // Se saiu do laço e encontrou a chave exata, encontramos um elemento existente
    if ((atual != NULL) && (atual->reg.chave == ch)) return atual;
    
    return NULL; // A chave não existe na lista (posição de inserção encontrada)
}


/**
 * @brief Inserção Dinâmica Ordenada (Sem Duplicações)
 * @details 
 * - **O que faz:** Aloca dinamicamente um novo nó e o costura na posição correta
 * para manter a lista 100% ordenada por chave.
 * - **Por trás do capô:** * 1. Invoca a `buscaSequencialExc`. Se ela retornar um endereço válido, a inserção é
 * abortada porque a chave já existe (regrados das listas sem duplicatas).
 * 2. Se estiver livre, o `malloc` entra em ação, reservando um espaço novinho na Heap.
 * 3. **Cenário A (Início):** Se `ant == NULL`, o novo elemento deve se tornar o primeiro.
 * Ele aponta para o antigo início (`i->prox = l->inicio`) e o controle da lista assume 
 * o novo nó (`l->inicio = i`).
 * 4. **Cenário B (Meio/Fim):** Se `ant` existir, o novo nó assume o próximo do anterior
 * (`i->prox = ant->prox`) e o anterior é costurado para apontar para o novo (`ant->prox = i`).
 * - **Complexidade:** $O(N)$ — O custo do `malloc` é $O(1)$, mas fomos obrigados a fazer a 
 * busca linear antes.
 */
bool inserirElemListaOrd(LISTA* l, REGISTRO reg) {
    TIPOCHAVE ch = reg.chave;
    PONT ant, i;
    
    i = buscaSequencialExc(l, ch, &ant);
    if(i != NULL) return false; // Erro: Elemento com chave idêntica já existe.
    
    // Alocação sob demanda na memória Heap
    i = (PONT) malloc(sizeof(ELEMENTO));
    i->reg = reg;
    
    if(ant == NULL) { 
        // O nó deve ser inserido na cabeceira (posição zero)
        i->prox = l->inicio;
        l->inicio = i;
    } else {
        // O nó deve ser inserido entre 'ant' e o próximo da sequência
        i->prox = ant->prox;
        ant->prox = i; 
    }
    return true;
}


/**
 * @brief Exclusão de Elemento e Reciclagem de Memória
 * @details 
 * - **O que faz:** Remove um nó da lista através de sua chave e libera a memória física.
 * - **Por trás do capô:** Localiza o alvo e seu predecessor usando a função de busca.
 * Para remover o nó sem quebrar a lista ao meio, fazemos uma ponte: o nó `anterior`
 * passa a apontar diretamente para o nó que vinha *depois* do elemento excluído (`ant->prox = i->prox`).
 * Com o elemento isolado e fora da corrente lógica, chamamos a função `free(i)`. Isso devolve
 * os bytes daquela gaveta imediatamente para o Sistema Operacional. Esquecer de usar `free`
 * causaria um *Memory Leak*.
 * - **Complexidade:** $O(N)$ devido à busca prévia.
 */
bool excluirElemLista(LISTA* l, TIPOCHAVE ch) {
    PONT ant, i;  
    i = buscaSequencialExc(l, ch, &ant);
    
    if(i == NULL) return false; // Erro: Elemento não foi localizado.
    
    if(ant == NULL) {
        // Removendo o primeiro elemento da lista (o atual início)
        l->inicio = i->prox; 
    } else {
        // Ignora/pula o nó 'i' conectando o anterior direto ao sucessor de 'i'
        ant->prox = i->prox; 
    }
    
    free(i); // Liberação física da memória RAM
    return true;
}


/**
 * @brief Reinicialização Segura (Wipe Total)
 * @details 
 * - **O que faz:** Desaloca absolutamente todos os nós da lista, limpando a memória Heap.
 * - **Por trás do capô:** Um erro comum seria simplesmente fazer `l->inicio = NULL`. 
 * Se fizéssemos isso, perderíamos a referência dos nós e toda a memória alocada ficaria 
 * "órfã" e inacessível na RAM. O algoritmo correto usa um ponteiro temporário `apagar`
 * para segurar o nó atual, avança o cursor principal para o próximo elo (`end = end->prox`)
 * e só então destrói o nó segurado (`free(apagar)`). Ao final, com todos os nós mortos,
 * definimos o `l->inicio = NULL`.
 * - **Complexidade:** $O(N)$ — Precisamos aplicar o `free` individualmente em cada nó.
 */
void reinicializarLista(LISTA* l) {
    PONT end = l->inicio; 
    
    while(end != NULL) {
        PONT apagar = end;   // Segura o nó atual
        end = end->prox;     // Avança o cursor para o próximo de forma segura
        free(apagar)         // Destrói o nó que ficou para trás
    }
    l->inicio = NULL; // Zera a estrutura, deixando-a pronta para ser reabastecida
}