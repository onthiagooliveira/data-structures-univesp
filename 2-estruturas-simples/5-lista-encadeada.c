/**
 * @file 5-lista-encadeada.c
 * @brief MANUAL TÉCNICO: Lista Encadeada | Linked List (Implementação Estática)
 * @date 2026
 * 
 * @details CONCEITOS ORIGINAIS (O Paradigma):
 * Listas encadeadas são uma sequência de células ligadas ou encadeadas umas as outras. 
 * As células de uma lista encadeada são compostas de dois elementos cada. O primeiro elemento
 * é o dado efetivo a ser armazenado e o segundo elemento uma referência para o próximo elemento
 * da lista.
 *
 * Quando lidamos com arrays, devemos saber de antemão ou em tempo de compilação qual o tamanho
 * ou quantidade de bytes a ser alocados para o array. Existem situações em programação onde a 
 * quantidade exata de memória a ser alocada não é conhecida na criação do programa, devendo ser
 * definida durante sua execução. Para estes casos pode-se alocar a memória necessária via alocação
 * dinâmica de memória. No entanto existem outros casos em que mais memória deve ser alocada para 
 * armazenar os dados do programa a medida que o programa vai sendo utilizado. Estes é um dos casos
 * em que a utilização de listas ligadas é mais indicada do que a utilização de arrays estáticos ou 
 * dinâmicos. Outra vantagem das listas ligadas é que não existe nenhuma restrição indicando que
 * as células que as compõem devem estar alocadas sequencialmente na memória tal como ocorre em 
 * arrays ou memória alocada dinamicamente via malloc. Cada célula pode existir em diferentes regiões
 * da memória. 
 *
 * A lista encadeada é composta por células de informação. Cada célula contém um item de dado e um
 * ponteiro para a próxima célula da lista. O final da lista é marcado pela última célula da lista
 * apontando para o ponteiro nulo (NULL);
 *
 * Uma lista ligada vazia nada mais é que um ponteiro apontando para NULL.
 * 
 * --------------------------------------------------------------------------
 * @note COMPLEMENTO DE ESTUDO (A Prática do Código Abaixo):
 * Embora o texto acima descreva a "Lista Encadeada Dinâmica" (com ponteiros), 
 * a estrutura abaixo implementa uma "Lista Encadeada ESTÁTICA". 
 * 
 * O que isso significa?
 * 1. Usamos um ARRAY pré-alocado (A[MAX]) para simular a memória do computador.
 * 2. Em vez de ponteiros de memória (*prox), usamos "Índices de Vetor" (int prox) 
 *    para apontar para o próximo elemento.
 * 3. O "NULL" aqui é representado pelo valor -1 (INVALIDO).
 * 4. Controlamos nosso próprio gerenciamento de memória através da variável `dispo` 
 *    (lista de posições disponíveis).
 */

#include <stdio.h>

/** 
 * @brief Declaração de constantes de controle
 * @details 
 * MAX: Define a capacidade máxima de elementos simulando a "memória total".
 * INVALIDO: Atua como o nosso "NULL". Como índices de array vão de 0 a MAX-1, 
 * o -1 é perfeito para indicar "fim da lista" ou "não aponta para lugar nenhum".
 */
#define MAX 50
#define INVALIDO -1

/** @brief Tipo de dado da chave. */
typedef int TIPOCHAVE;

/** 
 * @brief Estrutura que guarda a carga útil (dados)
 * @details Aqui ficam os dados que realmente importam para o usuário da lista.
 */
typedef struct {
    TIPOCHAVE chave;
    // Demais campos... (ex: char nome[30], float preco, etc.)
} REGISTRO;

/** 
 * @brief A "Célula" ou "Nó" da nossa Lista Encadeada
 * @details Contém o dado e a "referência" (neste caso, o índice numérico) para o próximo.
 */
typedef struct {
    REGISTRO reg;
    int prox; // O "Ponteiro Falso": Guarda o índice do próximo elemento no array
} ELEMENTO;

/** 
 * @brief O Controlador da Lista Encadeada Estática
 * @details Possui o array físico e duas "cabeças" de lista (inicio e dispo).
 * Esta estrutura gerencia DUAS listas entrelaçadas dentro do mesmo array:
 * 1. A lista de dados válidos (começa em 'inicio').
 * 2. A lista de espaços vazios (começa em 'dispo').
 */
typedef struct {
    ELEMENTO A[MAX]; // O array físico que hospeda as células
    int inicio;      // Índice do PRIMEIRO elemento válido da nossa lista
    int dispo;       // Índice do PRIMEIRO espaço vazio (disponível) no array
} LISTA;


/** @brief Funções de gerenciamento
* @note Implementaremos funções para:
* 1 - Inicializar a estrutura
* 2 - Retornar o tamanho da lista (quantidade de elementos válidos)
* 3 - Exibir os elementos da estrutura
* 4 - Buscar por um elemento na estrutura
* 5 - Inserir elementos na estrutura
* 6 - Excluir elementos na estrutura
* 7 - Reinicializar a estrutura
*/

/** 
 * @brief Inicialização da Lista Encadeada Estática
 * @details CONCEITOS (A Construção da Corrente):
 * Essa função pega cada um dos elementos do nosso arranjo, da posição 0 até a 
 * penúltima posição do nosso arranjo, e informa que o próximo disponível dele 
 * é o seguinte (0 -> 1 -> 2 -> 3 -> ...).
 * 
 * Este passo é obrigatório porque, diferentemente do 'malloc' que gerencia a 
 * memória para nós, aqui nós somos os gerentes. Precisamos encadear todos os 
 * espaços vazios para criar a nossa "lista de disponibilidade" (dispo).
 * 
 * @param l Ponteiro para a lista que será inicializada.
 */
void inicializarLista(LISTA* l) {
    int i;
    
    /**
     * @section PASSO 1: Encadear espaços disponíveis
     * O laço vai de 0 até 48 (MAX - 2). 
     * O índice 0 aponta para o 1, o 1 para o 2, até o 48 apontar para o 49.
     */
    for (i = 0; i < MAX - 1; i++) {
        l->A[i].prox = i + 1;
    }
    
    /**
     * @section PASSO 2: Finalizar a corrente de disponíveis
     * O último elemento do array (índice 49, que é MAX - 1) não tem um 
     * próximo elemento físico no vetor. Portanto, seu 'prox' deve ser 
     * o nosso marcador de fim de lista.
     */
    l->A[MAX - 1].prox = INVALIDO; 
    
    /**
     * @section PASSO 3: Configurar os cabeçalhos (Ponteiros Iniciais)
     */
    // A lista de dados começa completamente vazia, logo, aponta para lugar nenhum.
    l->inicio = INVALIDO; 
    
    // O primeiro espaço vazio disponível para uso é o primeiríssimo do vetor.
    l->dispo = 0; 
}

/** 
 * @brief Retornar o tamanho da lista (Quantidade de elementos válidos)
 * @details CONCEITO (Caminhamento em Lista Encadeada):
 * Esta função percorre a lista de dados válidos do início ao fim, contando 
 * quantos nós estão encadeados a partir do ponto de partida `l->inicio`.
 * 
 * Diferente de um array tradicional onde bastaria ler o tamanho, aqui nós 
 * "saltamos" de elemento em elemento seguindo as pistas do campo `prox`.
 * 
 * @param l Ponteiro para a lista
 * @return Quantidade total de elementos reais/válidos inseridos.
 */
int tamanho(LISTA* l) {
    int i = l->inicio; // Começa o rastreamento pelo primeiro elemento válido
    int tam = 0;       // Inicializa o contador de tamanho

    /**
     * @section LAÇO DE CAMINHAMENTO
     * Enquanto o índice 'i' não esbarrar em INVALIDO (-1), significa que 
     * estamos posicionados em uma célula que contém um dado real do usuário.
     */
    while (i != INVALIDO) { 
        tam++;            // Incrementa o contador (achamos um elemento válido)
        i = l->A[i].prox; // O "salto": 'i' recebe o índice do próximo elemento da corrente
    }

    return tam; // Retorna o total de elementos contabilizados
}

/** 
 * @brief Exibir/Imprimir os elementos válidos da lista
 * @details CONCEITO (Varredura Gráfica):
 * Assim como na função de tamanho, esta função começa no `l->inicio` e 
 * segue as pistas (`prox`) de elemento em elemento. A cada parada, ela 
 * imprime o valor da chave na tela.
 * 
 * É ideal para visualizar a "ordem lógica" da lista, que frequentemente 
 * será diferente da "ordem física" (os índices reais do array).
 * 
 * @param l Ponteiro para a lista
*/
void exibirLista(LISTA* l){
  int i = l->inicio; // Ponteiro lógico começa no primeiro elemento válido
  
  printf("Lista: [ ");

  /**
     * @section LAÇO DE IMPRESSÃO
     * Caminha pela estrutura enquanto o índice for válido, exibindo os dados.
     */
  while(i != INVALIDO) {
    // Imprime a chave do registro atual seguido de um espaço
    printf("%d ", l->A[i].reg.chave);

    // Avança para o próximo elemento lógico através do link de encadeamento
    i = l->A[i].prox;
  }
  printf("]\n");
}

/** 
 * @brief Busca Sequencial em Lista Encadeada Estática Ordenada
 * @details CONCEITO (Parada Precoce - Early Termination):
 * Varre a lista a partir do `l->inicio`. Como a lista está organizada em ordem 
 * crescente, o laço avança apenas enquanto a chave atual for MENOR que a 
 * chave buscada (`l->A[i].reg.chave < ch`). Se encontrar um valor maior ou igual, 
 * o laço é interrompido imediatamente, pois o elemento certamente não estará adiante.
 * 
 * @param l Ponteiro para a lista ordenada
 * @param ch Chave do elemento que estamos buscando
 * @return O índice físico do elemento no array se encontrado, ou -1 (INVALIDO) se não existir.
 * 
 * @note ANÁLISE COMPARATIVA DE PERFORMANCE (Cenário de Elemento Inexistente):
 * Considere a lista ordenada `[10 -> 20 -> 30 -> 40 -> 50]` e a busca pela chave `25`.
 * 
 * - BUSCA SEQUENCIAL TRADICIONAL:
 *   Testará individualmente: 10, 20, 30, 40, 50 e INVALIDO.
 *   Resultado: Varre a estrutura inteira realizando **5 comparações** no laço.
 * 
 * - BUSCA SEQUENCIAL ORDENADA (ESTE CÓDIGO):
 *   1. Testará o 10 (10 < 25): Verdadeiro. Avança.
 *   2. Testará o 20 (20 < 25): Verdadeiro. Avança.
 *   3. Testará o 30 (30 < 25): FALSO! O laço quebra imediatamente aqui.
 *   4. O bloco condicional testa se 30 é igual a 25. Não é. Retorna INVALIDO.
 *   Resultado: Interrompido no meio do caminho realizando apenas **3 comparações**.
 * 
 * @section COMPLEXIDADE (Métrica Big O)
 * - Pior Caso: $O(N)$ (Se a chave buscada for maior que o último elemento ou se estiver no fim).
 * - Caso Médio: $O(N/2)$ (A parada precoce corta o número de iterações pela metade em dados aleatórios).
 */
int buscaSequencialOrdenada(LISTA* l, TIPOCHAVE ch) {
    int i = l->inicio; // Ponteiro lógico começa no primeiro elemento válido

    /**
     * @section LAÇO DE BUSCA OTIMIZADO
     * O laço roda enquanto não for o fim da lista E a chave atual for menor que a buscada.
     */
    while(i != INVALIDO && l->A[i].reg.chave < ch) {
        i = l->A[i].prox; // Avança para o próximo elemento lógico
    }

    /**
     * @section PÓS-PROCESSAMENTO
     * Ao sair do laço, precisamos checar duas condições para confirmar o sucesso:
     * 1. 'i' não pode ser INVALIDO (não podemos ter chegado ao fim da lista).
     * 2. A chave em 'i' deve ser EXATAMENTE igual à chave buscada ('ch').
     */
    if (i != INVALIDO && l->A[i].reg.chave == ch) {
        return i; // Sucesso: Retorna o índice físico onde o elemento está guardado
    } else {
        return INVALIDO; // Fracasso: O elemento não existe na lista
    }
}


/** 
 * @brief Gerenciador de Memória Caseiro (Malloc Estático)
 * @details CONCEITO (Alocação de Nós):
 * Esta função simula a função `malloc()`. Ela vai até a lista de espaços 
 * disponíveis (`l->dispo`), retira o primeiro índice livre encontrado e 
 * atualiza o topo da lista de disponíveis para o próximo da fila.
 * 
 * @param l Ponteiro para a lista
 * @return O índice físico da "gaveta" que acaba de ser liberada para uso, 
 *         ou o valor da variável de controle original se estiver esgotada.
 * @section COMPLEXIDADE: O(1) - Tempo constante, pois o nó livre está sempre no topo.
*/
int obterNo(LISTA* l) {
    int resultado = l->dispo; // Armazena o índice da primeira gaveta vazia disponível
    
    if(l->dispo != INVALIDO) { 
        // O próximo espaço disponível passa a ser o que estava encadeado ao atual
        l->dispo = l->A[l->dispo].prox; 
    }
    return resultado;
}

/** 
 * @brief Inserção Ordenada por Chave
 * @details CONCEITO (Encaixe por Reencadeamento):
 * Insere um novo registro na lista mantendo a ordem crescente das chaves.
 * O algoritmo usa a estratégia de dois cursores que caminham juntos (`anterior` e `i`) 
 * para encontrar o ponto exato onde a nova chave deve ser "amarrada".
 * 
 * @param l Ponteiro para a lista
 * @param reg Registro contendo os dados a serem inseridos
 * @return true se a inserção foi bem-sucedida, false se a lista estiver cheia ou a chave for duplicada.
 * 
 * @note O SEGREDO DO SUCESSO: ENTENDENDO OS DOIS CASOS DE INSERÇÃO
 * Para entender como a corrente se reorganiza sem mover nenhum elemento física ou mecanicamente,
 * analise os dois cenários possíveis abaixo:
 * 
 * -----------------------------------------------------------------------------------------
 * CASO A: Inserção no Início (A nova chave é a menor de todas) -> `anterior == INVALIDO`
 * Exemplo: Você tem a lista [20 -> 30] e quer inserir o número 10.
 *   1. O laço 'while' nem inicia, pois a primeira chave (20) já é maior que a nova (10).
 *   2. A variável 'anterior' permanece valendo INVALIDO (-1).
 *   3. O novo nó (10) precisa apontar para quem era o antigo primeiro colocado (20).
 *      Linha de código: l->A[i].prox = l->inicio;
 *   4. O ponteiro mestre da lista avisa que o novo ponto de partida agora é o 10.
 *      Linha de código: l->inicio = i;
 *   Resultado Lógico: [10 -> 20 -> 30]
 * 
 * -----------------------------------------------------------------------------------------
 * CASO B: Inserção no Meio ou Fim (A nova chave tem um antecessor) -> `anterior != INVALIDO`
 * Exemplo: Você tem a lista [10 -> 30] e quer inserir o número 20.
 *   1. O laço 'while' roda uma vez: 'anterior' assume o índice do 10 e 'i' avança para o 30.
 *   2. O laço quebra porque 30 é maior que 20. Paramos exatamente onde precisamos operar!
 *   3. O novo nó (20) precisa "pescar" o elemento da frente (30). Ele rouba o 'prox' do 10.
 *      Linha de código: l->A[i].prox = l->A[anterior].prox; // (20 agora aponta para 30)
 *   4. O nó anterior (10) quebra o elo antigo e passa a apontar orgulhosamente para o novo nó (20).
 *      Linha de código: l->A[anterior].prox = i; // (10 agora aponta para 20)
 *   Resultado Lógico: [10 -> 20 -> 30]
 * -----------------------------------------------------------------------------------------
 */
bool inserirElemListaOrdenada(LISTA* l, REGISTRO reg) {
    // 1. Verificação de transbordamento (Memória cheia)
    if(l->dispo == INVALIDO) return false; 

    int anterior = INVALIDO; // Guardará o nó que virá ANTES do novo elemento
    int i = l->inicio;       // Cursor para percorrer a lista de elementos válidos
    TIPOCHAVE ch = reg.chave;

    /**
     * @section LAÇO DE BUSCA DA POSIÇÃO
     * Avança os ponteiros enquanto não for o fim da lista E a chave atual for menor que a nova.
    */
    while((i != INVALIDO) && (l->A[i].reg.chave < ch)) {
        anterior = i;     // O 'anterior' segue as pegadas de 'i'
        i = l->A[i].prox; // 'i' avança para o próximo nó
    }

    // 2. Verificação de Elemento Duplicado (Regra de Negócio)
    if (i != INVALIDO && l->A[i].reg.chave == ch){
        return false; // Chaves idênticas não são permitidas nesta estrutura
    } 
    
    /**
     * @section PROCESSO DE INSERÇÃO (Mudar os Elos da Corrente)
     */
    i = obterNo(l);     // Solicita um índice de gaveta vazia ao nosso alocador
    l->A[i].reg = reg;  // Copia os dados do usuário para dentro dessa gaveta

    if (anterior == INVALIDO) { 
        // CASO A: O elemento é o menor de todos (A nova cabeça da lista)
        l->A[i].prox = l->inicio; 
        l->inicio = i;            
    } else {
        // CASO B: O elemento será encaixado no meio ou no fim da lista
        l->A[i].prox = l->A[anterior].prox; 
        l->A[anterior].prox = i;            
    }

    return true; // Sucesso na operação
}


/** 
 * @brief Reciclador de Memória Caseiro (Free Estático)
 * @details CONCEITO (Devolução de Nós):
 * Esta função simula o comando `free()`. Ela recebe um índice físico que 
 * não está mais sendo usado pela lista principal e o insere de volta no 
 * topo da lista de disponíveis (`l->dispo`), deixando-o pronto para futuras inserções.
 * 
 * @param l Ponteiro para a lista
 * @param i Índice físico do nó que será reciclado
 * @section COMPLEXIDADE: O(1) - Tempo constante.
 */
void devolverNo(LISTA* l, int i) {
    l->A[i].prox = l->dispo; // O nó reciclado passa a apontar para o antigo topo dos disponíveis
    l->dispo = i;            // O topo dos disponíveis passa a ser o nó que acabamos de liberar
}

/** 
 * @brief Exclusão de um Elemento por Chave
 * @details CONCEITO (Desencaixe e Reciclagem):
 * Remove um registro da lista mantendo a integridade do encadeamento restante.
 * Utiliza a mesma estratégia de dois cursores (`anterior` e `i`) para localizar
 * o alvo e saber quem vinha logo antes dele.
 * 
 * @param l Ponteiro para a lista
 * @param ch Chave do elemento que deseja remover
 * @return true se a remoção foi bem-sucedida, false se o elemento não foi encontrado.
 * 
 * @note O SEGREDO DO SUCESSO: ENTENDENDO OS DOIS CASOS DE EXCLUSÃO E RECICLAGEM
 * Assim como na inserção, a remoção precisa tratar o ponto de partida de forma especial.
 * Imagine a lista lógica [10 -> 20 -> 30] para os cenários abaixo:
 * 
 * -----------------------------------------------------------------------------------------
 * CASO A: Remoção no Início (O elemento a ser apagado é o primeiro) -> `anterior == INVALIDO`
 * Exemplo: Você quer apagar o número 10.
 *   1. O laço localiza o 10 logo de cara. A variável 'anterior' continua valendo INVALIDO.
 *   2. O ponteiro mestre da lista ('inicio') simplesmente ignora o 10 e passa a apontar 
 *      direto para o próximo elemento da fila (o 20).
 *      Linha de código: l->inicio = l->A[i].prox;
 *   3. O nó do 10 é enviado para a função devolverNo() para ser limpo e reciclado.
 *   Resultado Lógico: [20 -> 30]
 * 
 * -----------------------------------------------------------------------------------------
 * CASO B: Remoção no Meio ou Fim (O elemento tem um antecessor) -> `anterior != INVALIDO`
 * Exemplo: Você quer apagar o número 20.
 *   1. O laço caminha. 'anterior' para no 10, e 'i' para no 20.
 *   2. O nó anterior (10) precisa dar um "pulo" sobre o 20 e apontar diretamente para 
 *      quem o 20 estava apontando (o 30).
 *      Linha de código: l->A[anterior].prox = l->A[i].prox;
 *   3. Com a ponte refeita entre o 10 e o 30, o nó do 20 ficou isolado e é enviado para a reciclagem.
 *   Resultado Lógico: [10 -> 30]
 * -----------------------------------------------------------------------------------------
 */
bool excluirElemLista(LISTA* l, TIPOCHAVE ch) {
    int anterior = INVALIDO;
    int i = l->inicio;

    /**
     * @section LAÇO DE BUSCA PELO ALVO
     * Como a nossa lista está ordenada, podemos usar a técnica de parada precoce:
     * Avançamos enquanto não for o fim da lista E a chave atual for menor que a chave alvo.
     */
    while (i != INVALIDO && l->A[i].reg.chave < ch) {
        anterior = i;
        i = l->A[i].prox;
    }

    // Se chegamos ao fim da lista ou passamos pelo ponto onde o elemento deveria estar
    if (i == INVALIDO || l->A[i].reg.chave != ch) {
        return false; // Elemento não existe na lista, nada a excluir
    }

    /**
     * @section PROCESSO DE DESENCAIXE
     */
    if (anterior == INVALIDO) {
        // CASO A: Removendo o primeiro elemento da lista
        l->inicio = l->A[i].prox;
    } else {
        // CASO B: Removendo elemento do meio ou do fim
        l->A[anterior].prox = l->A[i].prox;
    }

    /**
     * @section PASSO FINAL: RECICLAGEM
     * Devolvemos o índice 'i' para a lista de disponíveis para que ele possa ser usado de novo.
     */
    devolverNo(l, i);

    return true; // Sucesso na remoção
}

/** 
 * @brief Reinicialização da Lista (Wipe/Reset)
 * @details CONCEITO (Reseta Rápido - Instant Reset):
 * Apaga todos os elementos da lista de uma vez só, devolvendo a estrutura ao 
 * seu estado original de fábrica. 
 * 
 * Em uma lista encadeada dinâmica, esta operação exigiria uma varredura 
 * trabalhosa para liberar a memória de cada nó. Aqui, na abordagem estática, 
 * basta chamar a função 'inicializarLista()'. Ela reconstrói os elos da lista 
 * de disponíveis (`dispo = 0`) e desengata o início (`inicio = INVALIDO`).
 * 
 * @param l Ponteiro para a lista que será resetada
 * 
 * @note O SEGREDO DO SUCESSO: REAPROVEITAMENTO SEM APAGAR BYTES
 * Uma dúvida comum de quem está aprendendo é: "Mas essa função limpa os dados antigos 
 * que estavam dentro do vetor .reg.chave?" 
 * A resposta é: **Não, e nem precisa!**
 * 
 * Para o computador, um dado só existe se houver um ponteiro/índice apontando para ele. 
 * Ao mudar `l->inicio` para `INVALIDO` e reconstruir o `dispo`, nós dizemos ao sistema 
 * que todas as gavetas do array estão vazias e prontas para uso, mesmo que elas ainda 
 * guardem os números antigos dentro delas. Eles serão esmagados (sobrescritos) naturalmente 
 * conforme novas inserções forem chamadas.
 * 
 * @section COMPLEXIDADE (Métrica Big O)
 * - Complexidade: $O(MAX)$ devido ao laço 'for' interno da inicialização que reconstrói 
 *   a corrente de disponíveis. 
 * - Vantagem: O tempo de execução é FIXO. Não importa se a lista tinha 1 ou 50 elementos 
 *   válidos, o esforço para resetá-la é exatamente o mesmo.
 */
void reinicializarLista(LISTA* l) {
    inicializarLista(l); // Delega o trabalho para a função de inicialização padrão
}