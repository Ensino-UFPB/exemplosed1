/* ============================================================
   ListaDinEncad.h
   Estrutura de Dados I - UFPB - Aula 06
   Lista dinamica encadeada (alocacao dinamica, acesso encadeado)

   Referencia: BACKES, A. R. Algoritmos e Estruturas de Dados em
   Linguagem C. Rio de Janeiro: LTC, 2023. Capitulo 5.

   Este arquivo declara tudo o que e visivel para quem usa a
   biblioteca. A definicao de struct elemento fica oculta em
   ListaDinEncad.c: Lista e um tipo opaco.
   ============================================================ */

#ifndef LISTA_DIN_ENCAD_H
#define LISTA_DIN_ENCAD_H

/* Tipo do elemento armazenado na lista. */
struct aluno {
    int   matricula;
    char  nome[30];
    float n1, n2, n3;
};

/* Tipo opaco. Lista ja inclui um ponteiro (struct elemento*), de modo
   que Lista* e um ponteiro para ponteiro: o usuario declara Lista *li,
   exatamente como na lista sequencial estatica. */
typedef struct elemento* Lista;

/* --- criacao e destruicao ---------------------------------- */

/* Aloca o bloco do inicio e o inicializa com NULL (lista vazia).
   Devolve o ponteiro da lista, ou NULL se a alocacao falhar. */
Lista* cria_lista(void);

/* Libera todos os elementos e, por fim, o bloco do inicio. Custo O(n). */
void libera_lista(Lista* li);

/* --- informacoes de estado --------------------------------- */

/* Devolve a quantidade de elementos, ou -1 se li for NULL.
   Percorre a lista inteira: custo O(n). */
int tamanho_lista(Lista* li);

/* Devolve 0 (a lista so fica cheia quando falta memoria para o malloc),
   ou -1 se li for NULL. */
int lista_cheia(Lista* li);

/* Devolve 1 se a lista esta vazia, 0 caso contrario, -1 se li for NULL. */
int lista_vazia(Lista* li);

/* --- insercao ----------------------------------------------
   Todas devolvem 1 em caso de sucesso e 0 caso contrario
   (lista invalida ou falta de memoria). -------------------- */

/* Insere antes do primeiro elemento. Custo O(1). */
int insere_lista_inicio(Lista* li, struct aluno al);

/* Percorre a lista ate o ultimo elemento e insere depois dele. Custo O(n). */
int insere_lista_final(Lista* li, struct aluno al);

/* Insere mantendo a lista ordenada de forma crescente por matricula.
   Custo O(n). */
int insere_lista_ordenada(Lista* li, struct aluno al);

/* --- remocao -----------------------------------------------
   Todas devolvem 1 em caso de sucesso e 0 caso contrario
   (lista invalida, lista vazia ou elemento inexistente). --- */

/* Remove o primeiro elemento. Custo O(1). */
int remove_lista_inicio(Lista* li);

/* Percorre a lista ate o ultimo elemento e o remove. Custo O(n). */
int remove_lista_final(Lista* li);

/* Remove o elemento de matricula mat. Custo O(n). */
int remove_lista(Lista* li, int mat);

/* --- busca -------------------------------------------------
   Copiam o elemento encontrado para *al e devolvem 1; devolvem 0
   quando a busca falha. ------------------------------------ */

/* Busca pela posicao na lista, contada a partir de 1. Custo O(n). */
int busca_lista_pos(Lista* li, int pos, struct aluno *al);

/* Busca pelo conteudo do campo matricula. Custo O(n). */
int busca_lista_mat(Lista* li, int mat, struct aluno *al);

#endif /* LISTA_DIN_ENCAD_H */
