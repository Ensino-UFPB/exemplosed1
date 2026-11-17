/* Programa de teste da biblioteca: reproduz os traces da Aula 12
   (grafo nao dirigido com 4 vertices e grau_max = 3) e mostra um
   pequeno digrafo ponderado. */
#include <stdio.h>
#include "Grafo.h"

int main(void) {
    Grafo *gr, *dg;

    printf("cria_Grafo(0, 3, 0) == NULL: %d\n", cria_Grafo(0, 3, 0) == NULL);

    /* grafo nao dirigido, 4 vertices, ate 3 vizinhos, sem pesos */
    gr = cria_Grafo(4, 3, 0);
    if (gr == NULL) {
        printf("falha na alocacao\n");
        return 1;
    }
    insereAresta(gr, 0, 2, 0, 0);
    insereAresta(gr, 1, 2, 0, 0);
    insereAresta(gr, 2, 3, 0, 0);
    printf("apos inserir {0,2} {1,2} {2,3}:\n");
    imprime_Grafo(gr);

    /* linha do vertice 2 cheia: a insercao falha sem alterar nada */
    printf("insere (2,1) com linha cheia = %d\n", insereAresta(gr, 2, 1, 1, 0));

    /* trace de insercao dos slides */
    printf("insere {0,1} = %d\n", insereAresta(gr, 0, 1, 0, 0));
    imprime_Grafo(gr);

    /* trace de remocao dos slides: o vizinho 3 ocupa o lugar do 1 */
    printf("remove {2,1} = %d\n", removeAresta(gr, 2, 1, 0));
    imprime_Grafo(gr);

    printf("remove {1,3} inexistente = %d\n", removeAresta(gr, 1, 3, 0));
    printf("insere {0,7} vertice invalido = %d\n", insereAresta(gr, 0, 7, 0, 0));
    libera_Grafo(gr);

    /* digrafo ponderado: cada aresta aparece apenas na linha de orig */
    dg = cria_Grafo(3, 2, 1);
    if (dg == NULL) {
        printf("falha na alocacao\n");
        return 1;
    }
    insereAresta(dg, 0, 1, 1, 2.5f);
    insereAresta(dg, 0, 2, 1, 4.0f);
    insereAresta(dg, 2, 1, 1, 1.5f);
    printf("digrafo ponderado:\n");
    imprime_Grafo(dg);
    libera_Grafo(dg);
    return 0;
}
