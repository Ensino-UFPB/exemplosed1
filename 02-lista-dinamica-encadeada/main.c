/* Programa de teste da biblioteca: reproduz os traces da Aula 05. */
#include <stdio.h>
#include <string.h>
#include "ListaSequencial.h"

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
    printf("%-22s qtd=%d:", rotulo, n);
    for (i = 1; i <= n; i++) {
        busca_lista_pos(li, i, &al);
        printf(" %d", al.matricula);
    }
    printf("\n");
}

int main(void) {
    Lista *li = cria_lista();
    struct aluno al;

    printf("vazia=%d cheia=%d tamanho=%d\n", lista_vazia(li), lista_cheia(li), tamanho_lista(li));

    insere_lista_final(li, mk(33, "Ana"));
    insere_lista_final(li, mk(23, "Bruno"));
    insere_lista_final(li, mk(16, "Carla"));
    imprime("apos 3 insercoes", li);

    insere_lista_inicio(li, mk(12, "Diego"));
    imprime("insere_inicio(12)", li);

    remove_lista_inicio(li);
    imprime("remove_inicio", li);

    remove_lista_final(li);
    imprime("remove_final", li);

    libera_lista(li);

    li = cria_lista();
    insere_lista_ordenada(li, mk(12, "Ana"));
    insere_lista_ordenada(li, mk(16, "Bruno"));
    insere_lista_ordenada(li, mk(23, "Carla"));
    insere_lista_ordenada(li, mk(33, "Diego"));
    insere_lista_ordenada(li, mk(19, "Elisa"));
    imprime("insercao ordenada", li);

    if (busca_lista_pos(li, 3, &al))
        printf("busca_pos(3) -> matricula %d\n", al.matricula);
    if (busca_lista_mat(li, 23, &al))
        printf("busca_mat(23) -> %s\n", al.nome);
    printf("busca_mat(99)=%d\n", busca_lista_mat(li, 99, &al));

    remove_lista(li, 16);
    imprime("remove_lista(16)", li);

    remove_lista_otimizado(li, 12);
    imprime("remove_otimizado(12)", li);

    printf("remove_lista(99)=%d\n", remove_lista(li, 99));
    libera_lista(li);
    return 0;
}
