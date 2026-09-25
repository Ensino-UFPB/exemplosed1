/* ============================================================
   ListaSequencial.c
   Estrutura de Dados I - UFPB - Aula 05
   Implementacao da lista sequencial estatica.

   Tudo o que deve ficar oculto do usuario da biblioteca esta
   aqui: a definicao de struct lista e o corpo das funcoes.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include "ListaSequencial.h"

/* qtd guarda quantas posicoes de dados estao ocupadas e, ao mesmo
   tempo, indica a proxima posicao livre no final da lista.
   As posicoes de qtd ate MAX-1 existem na memoria, mas nao
   pertencem a lista. */
struct lista {
    int qtd;
    struct aluno dados[MAX];
};

/* ------------------------------------------------------------
   Criacao e destruicao
   ------------------------------------------------------------ */

Lista* cria_lista(void) {
    Lista *li;
    li = (Lista*) malloc(sizeof(struct lista));
    if (li != NULL)
        li->qtd = 0;
    return li;
}

void libera_lista(Lista* li) {
    free(li);
}

/* ------------------------------------------------------------
   Informacoes de estado
   ------------------------------------------------------------ */

int tamanho_lista(Lista* li) {
    if (li == NULL)
        return -1;
    return li->qtd;
}

int lista_cheia(Lista* li) {
    if (li == NULL)
        return -1;
    return (li->qtd == MAX);
}

int lista_vazia(Lista* li) {
    if (li == NULL)
        return -1;
    return (li->qtd == 0);
}

/* ------------------------------------------------------------
   Insercao
   ------------------------------------------------------------ */

int insere_lista_inicio(Lista* li, struct aluno al) {
    int i;
    if (li == NULL)
        return 0;
    if (li->qtd == MAX)           /* teste de estouro */
        return 0;
    /* copia do fim para o inicio, para nao sobrescrever um valor
       antes de ele ser copiado */
    for (i = li->qtd - 1; i >= 0; i--)
        li->dados[i + 1] = li->dados[i];
    li->dados[0] = al;
    li->qtd++;
    return 1;
}

int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;
    if (li->qtd == MAX)           /* teste de estouro */
        return 0;
    li->dados[li->qtd] = al;      /* qtd e a primeira posicao livre */
    li->qtd++;
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al) {
    int k, i = 0;
    if (li == NULL)
        return 0;
    if (li->qtd == MAX)           /* teste de estouro */
        return 0;
    /* procura a primeira posicao com matricula maior ou igual */
    while (i < li->qtd && li->dados[i].matricula < al.matricula)
        i++;
    /* abre espaco na posicao i */
    for (k = li->qtd - 1; k >= i; k--)
        li->dados[k + 1] = li->dados[k];
    li->dados[i] = al;
    li->qtd++;
    return 1;
}

/* ------------------------------------------------------------
   Remocao
   ------------------------------------------------------------ */

int remove_lista_inicio(Lista* li) {
    int k;
    if (li == NULL)
        return 0;
    if (li->qtd == 0)             /* teste de lista vazia */
        return 0;
    /* na remocao a copia anda do inicio para o fim */
    for (k = 0; k < li->qtd - 1; k++)
        li->dados[k] = li->dados[k + 1];
    li->qtd--;
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL)
        return 0;
    if (li->qtd == 0)             /* teste de lista vazia */
        return 0;
    li->qtd--;                    /* nenhum elemento e deslocado */
    return 1;
}

int remove_lista(Lista* li, int mat) {
    int k, i = 0;
    if (li == NULL)
        return 0;
    if (li->qtd == 0)             /* teste de lista vazia */
        return 0;
    while (i < li->qtd && li->dados[i].matricula != mat)
        i++;
    if (i == li->qtd)             /* elemento nao encontrado */
        return 0;
    for (k = i; k < li->qtd - 1; k++)
        li->dados[k] = li->dados[k + 1];
    li->qtd--;
    return 1;
}

int remove_lista_otimizado(Lista* li, int mat) {
    int i = 0;
    if (li == NULL)
        return 0;
    if (li->qtd == 0)             /* teste de lista vazia */
        return 0;
    while (i < li->qtd && li->dados[i].matricula != mat)
        i++;
    if (i == li->qtd)             /* elemento nao encontrado */
        return 0;
    li->qtd--;                    /* qtd passa a indicar o ultimo elemento */
    li->dados[i] = li->dados[li->qtd];
    return 1;                     /* a ordem da lista foi alterada */
}

/* ------------------------------------------------------------
   Busca
   ------------------------------------------------------------ */

int busca_lista_pos(Lista* li, int pos, struct aluno *al) {
    if (li == NULL || al == NULL || pos <= 0 || pos > li->qtd)
        return 0;
    *al = li->dados[pos - 1];     /* posicao 1 da lista = indice 0 */
    return 1;
}

int busca_lista_mat(Lista* li, int mat, struct aluno *al) {
    int i = 0;
    if (li == NULL || al == NULL)
        return 0;
    while (i < li->qtd && li->dados[i].matricula != mat)
        i++;
    if (i == li->qtd)             /* elemento nao encontrado */
        return 0;
    *al = li->dados[i];
    return 1;
}
