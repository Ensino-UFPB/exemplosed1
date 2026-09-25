/* ============================================================
   ListaSequencial.h
   Estrutura de Dados I - UFPB - Aula 05
   Lista sequencial estatica (alocacao estatica, acesso sequencial)

   Referencia: BACKES, A. R. Algoritmos e Estruturas de Dados em
   Linguagem C. Rio de Janeiro: LTC, 2023. Capitulo 5.

   Este arquivo declara tudo o que e visivel para quem usa a
   biblioteca. Os campos de struct lista ficam ocultos em
   ListaSequencial.c: Lista e um tipo opaco.
   ============================================================ */

#ifndef LISTA_SEQUENCIAL_H
#define LISTA_SEQUENCIAL_H

/* Numero maximo de elementos da lista, fixado em tempo de compilacao. */
#define MAX 100

/* Tipo do elemento armazenado na lista. */
struct aluno {
    int   matricula;
    char  nome[30];
    float n1, n2, n3;
};

/* Tipo opaco: o usuario da biblioteca so pode declarar Lista *li. */
typedef struct lista Lista;

/* --- criacao e destruicao ---------------------------------- */

/* Aloca e inicializa uma lista vazia.
   Devolve o ponteiro da lista, ou NULL se a alocacao falhar. */
Lista* cria_lista(void);

/* Libera a memoria da lista. */
void libera_lista(Lista* li);

/* --- informacoes de estado --------------------------------- */

/* Devolve a quantidade de elementos, ou -1 se li for NULL. */
int tamanho_lista(Lista* li);

/* Devolve 1 se a lista esta cheia, 0 caso contrario, -1 se li for NULL. */
int lista_cheia(Lista* li);

/* Devolve 1 se a lista esta vazia, 0 caso contrario, -1 se li for NULL. */
int lista_vazia(Lista* li);

/* --- insercao ----------------------------------------------
   Todas devolvem 1 em caso de sucesso e 0 caso contrario
   (lista invalida ou lista cheia). ------------------------- */

/* Insere na posicao 0, deslocando os demais elementos. Custo O(n). */
int insere_lista_inicio(Lista* li, struct aluno al);

/* Insere na primeira posicao livre do final. Custo O(1). */
int insere_lista_final(Lista* li, struct aluno al);

/* Insere mantendo a lista ordenada de forma crescente por matricula.
   Custo O(n). */
int insere_lista_ordenada(Lista* li, struct aluno al);

/* --- remocao -----------------------------------------------
   Todas devolvem 1 em caso de sucesso e 0 caso contrario
   (lista invalida, lista vazia ou elemento inexistente). --- */

/* Remove o elemento da posicao 0, deslocando os demais. Custo O(n). */
int remove_lista_inicio(Lista* li);

/* Remove o ultimo elemento. Custo O(1). */
int remove_lista_final(Lista* li);

/* Remove o elemento de matricula mat preservando a ordem. Custo O(n). */
int remove_lista(Lista* li, int mat);

/* Remove o elemento de matricula mat copiando o ultimo elemento para a
   posicao liberada. Movimenta um unico elemento, mas ALTERA A ORDEM da
   lista. A busca continua sendo O(n). */
int remove_lista_otimizado(Lista* li, int mat);

/* --- busca -------------------------------------------------
   Copiam o elemento encontrado para *al e devolvem 1; devolvem 0
   quando a busca falha. ------------------------------------ */

/* Busca pela posicao na lista, contada a partir de 1. Custo O(1). */
int busca_lista_pos(Lista* li, int pos, struct aluno *al);

/* Busca pelo conteudo do campo matricula. Custo O(n). */
int busca_lista_mat(Lista* li, int mat, struct aluno *al);

#endif /* LISTA_SEQUENCIAL_H */
