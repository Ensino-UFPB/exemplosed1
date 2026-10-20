/* Programa de teste da biblioteca: reproduz os traces da Aula 06. */
#include <stdio.h>
#include <string.h>
#include "ListaDinEncad.h"

static struct aluno mk(int matricula, const char *nome) {
    struct aluno al;
    al.matricula = matricula;
    strncpy(al.nome, nome, sizeof(al.nome) - 1);
    al.nome[sizeof(al.nome) - 1] = '\0';
    al.n1 = al.n2 = al.n3 = 0.0f;
    return al;
}

static void imprime(const char *rotulo, Lista *li) {
    int i, n = tamanho_lista(li);
    struct aluno al;
    printf("%-22s tam=%d: inicio ->", rotulo, n);
    for (i = 1; i <= n; i++) {
        busca_lista_pos(li, i, &al);
        printf(" %d ->", al.matricula);
    }
    printf(" NULL\n");
}

int main(void) {
    Lista *li = cria_lista();
    struct aluno al;

    printf("vazia=%d cheia=%d tamanho=%d\n", lista_vazia(li), lista_cheia(li), tamanho_lista(li));

    insere_lista_final(li, mk(33, "Ana"));
    insere_lista_final(li, mk(23, "Bruno"));
    insere_lista_final(li, mk(16, "Carla"));
    imprime("apos 3 insercoes", li);

    insere_lista_inicio(li, mk(12, "Diego"));        /* trace B */
    imprime("insere_inicio(12)", li);

    remove_lista_inicio(li);
    insere_lista_final(li, mk(12, "Diego"));         /* trace C */
    imprime("insere_final(12)", li);

    remove_lista_final(li);
    imprime("remove_final", li);

    remove_lista(li, 23);                            /* trace E */
    imprime("remove_lista(23)", li);
    printf("remove_lista(99)=%d\n", remove_lista(li, 99));

    libera_lista(li);                                /* trace A */

    li = cria_lista();
    insere_lista_ordenada(li, mk(23, "Ana"));
    insere_lista_ordenada(li, mk(16, "Bruno"));
    imprime("ordenada", li);
    insere_lista_ordenada(li, mk(19, "Carla"));      /* trace D */
    imprime("insere_ordenada(19)", li);
    insere_lista_ordenada(li, mk(12, "Diego"));
    insere_lista_ordenada(li, mk(40, "Elisa"));
    imprime("insere 12 e 40", li);

    if (busca_lista_pos(li, 3, &al))
        printf("busca_pos(3) -> matricula %d\n", al.matricula);
    if (busca_lista_mat(li, 19, &al))
        printf("busca_mat(19) -> %s\n", al.nome);
    printf("busca_mat(99)=%d\n", busca_lista_mat(li, 99, &al));

    libera_lista(li);
    return 0;
}
