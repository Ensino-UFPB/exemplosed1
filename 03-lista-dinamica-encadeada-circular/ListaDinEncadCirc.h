/* ============================================================
   ListaDinEncadCirc.h
   Estrutura de Dados I - UFPB - Aula 07
   Lista dinamica encadeada circular

   Referencia: BACKES, A. R. Algoritmos e Estruturas de Dados em
   Linguagem C. Rio de Janeiro: LTC, 2023. Capitulo 5.

   Este arquivo declara tudo o que e visivel para quem usa a
   biblioteca. A definicao de struct elemento fica oculta em
   ListaDinEncadCirc.c: Lista e um tipo opaco.

   A DIFERENCA PARA A LISTA DINAMICA ENCADEADA DA AULA 06 NAO
   ESTA AQUI. Os tipos sao identicos: um elemento continua tendo
   um campo de dado e um campo prox. O que muda e a implementacao
   das funcoes, porque o campo prox do ultimo elemento guarda o
   endereco do primeiro, e nao a constante NULL.

   Consequencia pratica para quem for estender esta biblioteca:
   nenhum percurso pode terminar comparando prox com NULL. Todo
   percurso para ao voltar ao inicio da lista, (*li).
   ============================================================ */

#ifndef LISTA_DIN_ENCAD_CIRC_H
#define LISTA_DIN_ENCAD_CIRC_H

/* Tipo do dado armazenado na lista. */
struct aluno {
    int matricula;
    char nome[30];
    float n1, n2, n3;
};

/* Tipo opaco. Lista ja inclui um ponteiro (struct elemento*), de modo que
   Lista* e um ponteiro para ponteiro: o usuario declara Lista *li, e as
   funcoes podem alterar o inicio da lista alterando o conteudo de *li. */
typedef struct elemento* Lista;

/* --- criacao e destruicao ---------------------------------- */

/* Aloca o bloco do inicio e o inicializa com NULL (lista vazia).
   Devolve o ponteiro da lista, ou NULL se a alocacao falhar.
   Identica a da lista nao circular: a circularidade so aparece
   a partir da primeira insercao. */
Lista* cria_lista(void);

/* Libera todos os elementos e, por fim, o bloco do inicio.
   O percurso para quando o elemento seguinte ao atual e o inicio
   da lista, e nao quando encontra NULL. Custo O(n). */
void libera_lista(Lista* li);

/* --- informacoes de estado --------------------------------- */

/* Devolve a quantidade de elementos; devolve 0 se li for NULL ou
   se a lista estiver vazia. Usa do-while: em um while a condicao
   de parada ja seria falsa na primeira avaliacao. Custo O(n). */
int tamanho_lista(Lista* li);

/* Devolve sempre 0. Uma lista com alocacao dinamica so fica cheia
   quando falta memoria para o malloc, o que e detectado dentro das
   funcoes de insercao. */
int lista_cheia(Lista* li);

/* Devolve 1 se a lista estiver vazia ou se li for NULL (lista
   invalida), 0 caso contrario. */
int lista_vazia(Lista* li);

/* --- insercao ----------------------------------------------
   Todas devolvem 1 em caso de sucesso e 0 caso contrario
   (lista invalida ou falta de memoria).

   Em uma lista circular, inserir no inicio e inserir no final
   colocam o novo elemento na MESMA posicao fisica: entre o
   ultimo e o primeiro. A unica diferenca entre as duas funcoes
   e a atribuicao final *li = no, presente apenas na insercao
   no inicio. ------------------------------------------------ */

/* Percorre a lista para achar o ultimo elemento, insere entre ele
   e o primeiro, e passa a ser o novo inicio. Custo O(n).
   Na lista nao circular da Aula 06 esta operacao era O(1): o
   percurso e o preco da circularidade nesta representacao. */
int insere_lista_inicio(Lista* li, struct aluno al);

/* Percorre a lista para achar o ultimo elemento e insere depois
   dele, sem alterar o inicio. Custo O(n). */
int insere_lista_final(Lista* li, struct aluno al);

/* Insere mantendo a lista ordenada de forma crescente por
   matricula. O ponto de insercao pode ser no inicio, no meio ou
   no final. Custo O(n). */
int insere_lista_ordenada(Lista* li, struct aluno al);

/* --- remocao -----------------------------------------------
   Todas devolvem 1 em caso de sucesso e 0 caso contrario
   (lista invalida, lista vazia ou elemento inexistente).

   As tres tratam antes de tudo o caso do elemento unico, que e
   reconhecido pelo teste (*li) == (*li)->prox: o no aponta para
   si mesmo e a lista fica vazia apos a remocao. -------------- */

/* Percorre a lista para achar o ultimo elemento, que aponta para
   o que sera removido, e religa o ciclo. Custo O(n).
   Tambem era O(1) na lista nao circular da Aula 06. */
int remove_lista_inicio(Lista* li);

/* Percorre a lista mantendo o antecessor, remove o ultimo e
   religa o antecessor ao inicio. Custo O(n). */
int remove_lista_final(Lista* li);

/* Remove o elemento de matricula igual a passada, esteja ele no
   inicio, no meio ou no final. Custo O(n). */
int remove_lista(Lista* li, int mat);

/* --- busca -------------------------------------------------
   Copiam o elemento encontrado para *al e devolvem 1; devolvem 0
   quando a busca falha.

   As duas tem duas condicoes de parada: encontrar o que se
   procura e completar uma volta na lista. Omitir a segunda
   transforma a busca de uma chave ausente em laco infinito. -- */

/* Busca pela posicao na lista, contada a partir de 1 no inicio.
   Posicoes maiores que o numero de elementos devolvem 0.
   Custo O(n). */
int busca_lista_pos(Lista* li, int pos, struct aluno *al);

/* Busca pelo conteudo do campo matricula. Custo O(n). */
int busca_lista_mat(Lista* li, int mat, struct aluno *al);

#endif /* LISTA_DIN_ENCAD_CIRC_H */
