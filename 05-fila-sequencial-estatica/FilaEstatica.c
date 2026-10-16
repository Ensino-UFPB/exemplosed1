/* ============================================================
   FilaEstatica.c
   Estrutura de Dados I - UFPB - Aula 09
   Implementacao da fila sequencial estatica com capacidade
   definida na criacao.

   Tudo o que deve ficar oculto do usuario da biblioteca esta
   aqui: a definicao de struct fila e o corpo das funcoes.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include "FilaEstatica.h"

/* inicio:     posicao do vetor que guarda o primeiro da fila.
   final:      posicao livre onde entra o proximo elemento.
   qtd:        quantos elementos estao na fila.
   capacidade: tamanho do vetor dados, escolhido em cria_Fila.
   dados:      vetor alocado com malloc em cria_Fila.

   O vetor e tratado como circular: ao passar da ultima posicao
   (capacidade - 1), inicio e final voltam para a posicao 0. Por
   isso inicio == final ocorre tanto na fila vazia quanto na fila
   cheia, e quem distingue os dois casos e o campo qtd. */
struct fila {
    int inicio, final, qtd;
    int capacidade;
    struct aluno *dados;
};

/* ------------------------------------------------------------
   Criacao e destruicao
   ------------------------------------------------------------ */

Fila* cria_Fila(int capacidade) {
    Fila *fi;
    if (capacidade <= 0)
        return NULL;
    fi = (Fila*) malloc(sizeof(struct fila));            /* 1a alocacao */
    if (fi == NULL)
        return NULL;
    fi->dados = (struct aluno*) malloc(capacidade * sizeof(struct aluno));
    if (fi->dados == NULL) {                             /* 2a alocacao falhou */
        free(fi);       /* sem este free, a struct ficaria perdida */
        return NULL;
    }
    fi->capacidade = capacidade;
    fi->inicio = 0;
    fi->final = 0;
    fi->qtd = 0;
    return fi;
}

void libera_Fila(Fila* fi) {
    if (fi == NULL)
        return;
    free(fi->dados);    /* primeiro o vetor: fi ainda e valido aqui */
    free(fi);           /* depois a estrutura que guardava o vetor */
}

/* ------------------------------------------------------------
   Informacoes de estado
   ------------------------------------------------------------ */

int tamanho_Fila(Fila* fi) {
    if (fi == NULL)
        return -1;
    return fi->qtd;
}

int Fila_cheia(Fila* fi) {
    if (fi == NULL)
        return -1;
    return (fi->qtd == fi->capacidade);  /* no livro: qtd == MAX */
}

int Fila_vazia(Fila* fi) {
    if (fi == NULL)
        return -1;
    return (fi->qtd == 0);
}

/* ------------------------------------------------------------
   Operacoes da fila
   ------------------------------------------------------------ */

int insere_Fila(Fila* fi, struct aluno al) {
    if (fi == NULL)
        return 0;
    if (Fila_cheia(fi))                   /* teste de estouro */
        return 0;
    fi->dados[fi->final] = al;            /* final e a posicao livre */
    fi->final = (fi->final + 1) % fi->capacidade;   /* volta para 0 no fim */
    fi->qtd++;
    return 1;
}

int remove_Fila(Fila* fi) {
    if (fi == NULL || Fila_vazia(fi))
        return 0;
    /* nenhum elemento e deslocado: o inicio apenas avanca */
    fi->inicio = (fi->inicio + 1) % fi->capacidade;
    fi->qtd--;
    return 1;
}

int consulta_Fila(Fila* fi, struct aluno *al) {
    if (fi == NULL || al == NULL || Fila_vazia(fi))
        return 0;
    *al = fi->dados[fi->inicio];
    return 1;
}
