/* ============================================================
   ListaDinEncad.c
   Estrutura de Dados I - UFPB - Aula 06
   Implementacao da lista dinamica encadeada.

   Tudo o que deve ficar oculto do usuario da biblioteca esta
   aqui: a definicao de struct elemento e o corpo das funcoes.

   Diferencas em relacao ao codigo do livro:
   - o ponteiro ant e inicializado com NULL, o que evita o aviso
     -Wmaybe-uninitialized quando se compila com otimizacao;
   - as consultas devolvem -1 para lista invalida, conforme a
     convencao do repositorio.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncad.h"

/* Cada elemento guarda os dados e o endereco do proximo elemento.
   O ultimo elemento aponta para NULL. */
struct elemento {
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

/* ------------------------------------------------------------
   Criacao e destruicao
   ------------------------------------------------------------ */

Lista* cria_lista(void) {
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;               /* lista vazia: o inicio aponta para NULL */
    return li;
}

void libera_lista(Lista* li) {
    if (li != NULL) {
        Elem* no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;    /* avanca ANTES de liberar */
            free(no);
        }
        free(li);                 /* libera o bloco do inicio */
    }
}

/* ------------------------------------------------------------
   Informacoes de estado
   ------------------------------------------------------------ */

int tamanho_lista(Lista* li) {
    if (li == NULL)
        return -1;
    int cont = 0;
    Elem* no = *li;
    while (no != NULL) {          /* nao ha campo qtd: e preciso percorrer */
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li) {
    if (li == NULL)
        return -1;
    return 0;                     /* so falta memoria quando o malloc falha */
}

int lista_vazia(Lista* li) {
    if (li == NULL)
        return -1;
    if (*li == NULL)
        return 1;
    return 0;
}

/* ------------------------------------------------------------
   Insercao
   ------------------------------------------------------------ */

int insere_lista_inicio(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;     /* falta de memoria: lista cheia */
    no->dados = al;
    no->prox = (*li);             /* 1o: liga o novo no ao antigo primeiro */
    *li = no;                     /* 2o: so entao altera o inicio */
    return 1;
}

int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    no->prox = NULL;              /* o novo no sera o ultimo */
    if ((*li) == NULL) {          /* lista vazia: insere no inicio */
        *li = no;
    } else {
        Elem* aux = *li;
        while (aux->prox != NULL) /* para NO ultimo, e nao depois dele */
            aux = aux->prox;
        aux->prox = no;
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    if ((*li) == NULL) {          /* lista vazia: insere no inicio */
        no->prox = NULL;
        *li = no;
        return 1;
    } else {
        Elem *ant = NULL, *atual = *li;
        /* procura o primeiro elemento com matricula maior ou igual */
        while (atual != NULL &&
               atual->dados.matricula < al.matricula) {
            ant = atual;
            atual = atual->prox;
        }
        if (atual == *li) {       /* insere no inicio */
            no->prox = (*li);
            *li = no;
        } else {                  /* insere entre ant e atual */
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

/* ------------------------------------------------------------
   Remocao
   ------------------------------------------------------------ */

int remove_lista_inicio(Lista* li) {
    if (li == NULL) return 0;
    if ((*li) == NULL)            /* lista vazia */
        return 0;
    Elem *no = *li;
    *li = no->prox;               /* religa antes do free */
    free(no);
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL) return 0;
    if ((*li) == NULL)            /* lista vazia */
        return 0;
    Elem *ant = NULL, *no = *li;
    while (no->prox != NULL) {
        ant = no;
        no = no->prox;
    }
    if (no == (*li))              /* unico elemento: a lista fica vazia */
        *li = no->prox;
    else
        ant->prox = no->prox;     /* o penultimo passa a apontar para NULL */
    free(no);
    return 1;
}

int remove_lista(Lista* li, int mat) {
    if (li == NULL) return 0;
    if ((*li) == NULL)            /* lista vazia */
        return 0;
    Elem *ant = NULL, *no = *li;
    while (no != NULL && no->dados.matricula != mat) {
        ant = no;
        no = no->prox;
    }
    if (no == NULL)               /* elemento nao encontrado */
        return 0;
    if (no == *li)                /* remove o primeiro */
        *li = no->prox;
    else
        ant->prox = no->prox;     /* contorna o no removido */
    free(no);
    return 1;
}

/* ------------------------------------------------------------
   Busca
   ------------------------------------------------------------ */

int busca_lista_pos(Lista* li, int pos, struct aluno *al) {
    if (li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while (no != NULL && i < pos) { /* nao ha indice: percorre ate a posicao */
        no = no->prox;
        i++;
    }
    if (no == NULL)               /* posicao maior que o tamanho */
        return 0;
    else {
        *al = no->dados;
        return 1;
    }
}

int busca_lista_mat(Lista* li, int mat, struct aluno *al) {
    if (li == NULL)
        return 0;
    Elem *no = *li;
    while (no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if (no == NULL)               /* elemento nao encontrado */
        return 0;
    else {
        *al = no->dados;
        return 1;
    }
}
