/* Programa de teste da biblioteca: reproduz os traces da Aula 09
   (fila com capacidade 5, incluindo a volta circular de final). */
#include <stdio.h>
#include <string.h>
#include "FilaEncadeada.h"

static struct aluno mk(int matricula, const char *nome) {
    struct aluno al;
    al.matricula = matricula;
    strncpy(al.nome, nome, sizeof(al.nome) - 1);
    al.nome[sizeof(al.nome) - 1] = '\0';
    al.n1 = al.n2 = al.n3 = 0.0f;
    return al;
}

/* Imprime a fila do inicio para o final usando apenas a interface:
   consulta, remove e reinsere cada elemento (qtd voltas completas).
   A fila termina no mesmo estado logico em que comecou. */
static void imprime(const char *rotulo, Fila *fi) {
    int i, n = tamanho_Fila(fi);
    struct aluno al;
    printf("%-24s qtd=%d:", rotulo, n);
    for (i = 0; i < n; i++) {
        consulta_Fila(fi, &al);
        remove_Fila(fi);
        insere_Fila(fi, al);
        printf(" %d", al.matricula);
    }
    printf("\n");
}

int main(void) {
    Fila *fi;
    struct aluno al;

    printf("cria_Fila() == NULL: %d\n", cria_Fila() == NULL);

    fi = cria_Fila();
    if (fi == NULL) {
        printf("falha na alocacao\n");
        return 1;
    }
    printf("vazia=%d cheia=%d tamanho=%d\n", Fila_vazia(fi), Fila_cheia(fi), tamanho_Fila(fi));

    insere_Fila(fi, mk(10, "Ana"));
    insere_Fila(fi, mk(20, "Bruno"));
    insere_Fila(fi, mk(30, "Carla"));
    insere_Fila(fi, mk(40, "Diego"));
    imprime("apos 4 insercoes", fi);

    consulta_Fila(fi, &al);
    printf("consulta -> %d (%s)\n", al.matricula, al.nome);

    remove_Fila(fi);
    remove_Fila(fi);
    imprime("apos 2 remocoes", fi);

    insere_Fila(fi, mk(50, "Elisa"));
    insere_Fila(fi, mk(60, "Fabio"));    
    insere_Fila(fi, mk(70, "Gabriela"));
    printf("vazia=%d cheia=%d tamanho=%d\n", Fila_vazia(fi), Fila_cheia(fi), tamanho_Fila(fi));

    while (!Fila_vazia(fi)) {
        consulta_Fila(fi, &al);
        printf("atende %d\n", al.matricula);
        remove_Fila(fi);
    }
    printf("remove em fila vazia = %d\n", remove_Fila(fi));
    printf("consulta em fila vazia = %d\n", consulta_Fila(fi, &al));

    libera_Fila(fi); 
    return 0;
}
