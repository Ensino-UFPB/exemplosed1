/* Programa de teste da biblioteca: reproduz o trace geral da Aula 11
   (pilha com capacidade 4, incluindo pilha cheia e pilha vazia). */
#include <stdio.h>
#include <string.h>
#include "PilhaSequencial.h"

static struct aluno mk(int matricula, const char *nome) {
    struct aluno al;
    al.matricula = matricula;
    strncpy(al.nome, nome, sizeof(al.nome) - 1);
    al.nome[sizeof(al.nome) - 1] = '\0';
    al.n1 = al.n2 = al.n3 = 0.0f;
    return al;
}

/* Mostra o topo e o tamanho usando apenas a interface da pilha. */
static void mostra(const char *rotulo, Pilha *pi) {
    struct aluno al;
    printf("%-24s qtd=%d", rotulo, tamanho_Pilha(pi));
    if (consulta_topo_Pilha(pi, &al))
        printf("  topo=%d (%s)", al.matricula, al.nome);
    printf("\n");
}

int main(void) {
    Pilha *pi;
    struct aluno al;

    printf("cria_Pilha(0) == NULL: %d\n", cria_Pilha(0) == NULL);

    pi = cria_Pilha(4);
    if (pi == NULL) {
        printf("falha na alocacao\n");
        return 1;
    }
    printf("vazia=%d cheia=%d tamanho=%d\n", Pilha_vazia(pi), Pilha_cheia(pi), tamanho_Pilha(pi));

    insere_Pilha(pi, mk(10, "Ana"));
    insere_Pilha(pi, mk(20, "Bruno"));
    insere_Pilha(pi, mk(30, "Carla"));
    mostra("apos empilhar 10 20 30", pi);

    remove_Pilha(pi);                      /* sai o 30: ultimo a entrar */
    mostra("apos 1 remocao", pi);

    insere_Pilha(pi, mk(40, "Diego"));
    insere_Pilha(pi, mk(50, "Elisa"));     /* pilha cheia */
    mostra("apos empilhar 40 50", pi);
    printf("vazia=%d cheia=%d tamanho=%d\n", Pilha_vazia(pi), Pilha_cheia(pi), tamanho_Pilha(pi));
    printf("insere em pilha cheia = %d\n", insere_Pilha(pi, mk(60, "Fabio")));

    while (!Pilha_vazia(pi)) {             /* ordem inversa da insercao */
        consulta_topo_Pilha(pi, &al);
        printf("desempilha %d\n", al.matricula);
        remove_Pilha(pi);
    }
    printf("remove em pilha vazia = %d\n", remove_Pilha(pi));
    printf("consulta em pilha vazia = %d\n", consulta_topo_Pilha(pi, &al));

    libera_Pilha(pi);
    return 0;
}
