/* ============================================================
   Grafo.c
   Estrutura de Dados I - UFPB - Aula 12
   Implementacao do grafo por lista de adjacencia em vetores.

   Tudo o que deve ficar oculto do usuario da biblioteca esta
   aqui: a definicao de struct grafo e o corpo das funcoes.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

/* eh_ponderado: 1 se as arestas tem peso.
   nro_vert:     numero de vertices (0 .. nro_vert - 1).
   grau_max:     numero maximo de vizinhos de cada vertice.
   arestas:      vetor de nro_vert ponteiros; arestas[v] aponta para
                 uma linha de grau_max inteiros com os vizinhos de v.
   pesos:        mesma organizacao de arestas; NULL se nao ponderado.
   grau:         grau[v] = quantidade de vizinhos ja inseridos em v. */
struct grafo {
    int eh_ponderado;
    int nro_vert;
    int grau_max;
    int **arestas;
    float **pesos;
    int *grau;
};

/* ------------------------------------------------------------
   Criacao e destruicao
   ------------------------------------------------------------ */

Grafo* cria_Grafo(int nro_vert, int grau_max, int eh_ponderado) {
    Grafo *gr;
    int v;
    if (nro_vert <= 0 || grau_max <= 0)
        return NULL;
    gr = (Grafo*) malloc(sizeof(struct grafo));
    if (gr == NULL)
        return NULL;
    gr->nro_vert = nro_vert;
    gr->grau_max = grau_max;
    gr->eh_ponderado = (eh_ponderado != 0) ? 1 : 0;
    gr->arestas = NULL;
    gr->pesos = NULL;

    /* calloc: todos os graus comecam em 0 */
    gr->grau = (int*) calloc(nro_vert, sizeof(int));
    if (gr->grau == NULL) {
        free(gr);
        return NULL;
    }

    /* calloc no vetor de ponteiros: linhas ainda nao alocadas valem
       NULL, o que permite liberar com seguranca em caso de falha */
    gr->arestas = (int**) calloc(nro_vert, sizeof(int*));
    if (gr->arestas == NULL) {
        libera_Grafo(gr);
        return NULL;
    }
    for (v = 0; v < nro_vert; v++) {
        gr->arestas[v] = (int*) malloc(grau_max * sizeof(int));
        if (gr->arestas[v] == NULL) {
            libera_Grafo(gr);   /* libera tudo o que ja foi alocado */
            return NULL;
        }
    }

    if (gr->eh_ponderado) {
        gr->pesos = (float**) calloc(nro_vert, sizeof(float*));
        if (gr->pesos == NULL) {
            libera_Grafo(gr);
            return NULL;
        }
        for (v = 0; v < nro_vert; v++) {
            gr->pesos[v] = (float*) malloc(grau_max * sizeof(float));
            if (gr->pesos[v] == NULL) {
                libera_Grafo(gr);
                return NULL;
            }
        }
    }
    return gr;
}

void libera_Grafo(Grafo* gr) {
    int v;
    if (gr == NULL)
        return;
    /* primeiro cada linha, enquanto os ponteiros ainda existem */
    if (gr->arestas != NULL) {
        for (v = 0; v < gr->nro_vert; v++)
            free(gr->arestas[v]);       /* free(NULL) nao faz nada */
        free(gr->arestas);
    }
    if (gr->pesos != NULL) {
        for (v = 0; v < gr->nro_vert; v++)
            free(gr->pesos[v]);
        free(gr->pesos);
    }
    free(gr->grau);
    free(gr);                           /* por ultimo, a estrutura */
}

/* ------------------------------------------------------------
   Operacoes sobre arestas
   ------------------------------------------------------------ */

int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso) {
    if (gr == NULL)
        return 0;
    if (orig < 0 || orig >= gr->nro_vert)
        return 0;
    if (dest < 0 || dest >= gr->nro_vert)
        return 0;
    if (gr->grau[orig] == gr->grau_max)     /* linha cheia */
        return 0;

    /* grava na primeira posicao livre da linha de orig */
    gr->arestas[orig][gr->grau[orig]] = dest;
    if (gr->eh_ponderado)
        gr->pesos[orig][gr->grau[orig]] = peso;
    gr->grau[orig]++;

    /* grafo nao dirigido: insere a direcao oposta. O argumento 1
       impede que a chamada recursiva chame a si mesma de novo. */
    if (eh_digrafo == 0)
        insereAresta(gr, dest, orig, 1, peso);
    return 1;
}

int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo) {
    int i = 0;
    if (gr == NULL)
        return 0;
    if (orig < 0 || orig >= gr->nro_vert)
        return 0;
    if (dest < 0 || dest >= gr->nro_vert)
        return 0;

    /* busca sequencial de dest na linha de orig */
    while (i < gr->grau[orig] && gr->arestas[orig][i] != dest)
        i++;
    if (i == gr->grau[orig])                /* aresta inexistente */
        return 0;

    /* o ultimo vizinho ocupa a posicao removida: sem deslocamento */
    gr->grau[orig]--;
    gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];
    if (gr->eh_ponderado)
        gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];

    if (eh_digrafo == 0)
        removeAresta(gr, dest, orig, 1);
    return 1;
}

/* ------------------------------------------------------------
   Consulta
   ------------------------------------------------------------ */

void imprime_Grafo(Grafo* gr) {
    int v, i;
    if (gr == NULL)
        return;
    for (v = 0; v < gr->nro_vert; v++) {
        printf("  %d (grau %d):", v, gr->grau[v]);
        for (i = 0; i < gr->grau[v]; i++) {
            if (gr->eh_ponderado)
                printf(" %d(%.1f)", gr->arestas[v][i], gr->pesos[v][i]);
            else
                printf(" %d", gr->arestas[v][i]);
        }
        printf("\n");
    }
}
