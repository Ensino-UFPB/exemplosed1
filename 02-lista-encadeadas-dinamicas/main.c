/* Programa de teste da biblioteca: reproduz os traces da Aula 06. */
#include <stdio.h>
#include <string.h>
#include "ListaDinEncad.h"

static struct tarefa mk(int codigo, const char *descricao) {
    struct tarefa t;
    t.codigo = codigo;
    strncpy(t.descricao, descricao, sizeof(t.descricao) - 1);
    t.descricao[sizeof(t.descricao) - 1] = '\0';
    t.prioridade = 0;
    return t;
}

static void imprime(const char *rotulo, ListaTarefas *li) {
    int i, n = tamanho_lista(li);
    struct tarefa t;
    printf("%-22s tam=%d: inicio ->", rotulo, n);
    for (i = 1; i <= n; i++) {
        busca_tarefa_pos(li, i, &t);
        printf(" (%d, %s, %d) ->", t.codigo, t.descricao, t.prioridade);
    }
    printf(" NULL\n");
}

int main(void) {
    ListaTarefas *li = cria_lista();
    struct tarefa t;

    printf("vazia=%d cheia=%d tamanho=%d\n", lista_vazia(li), lista_cheia(li), tamanho_lista(li));

    insere_tarefa_final(li, mk(12, "Estudar"));
    insere_tarefa_final(li, mk(23, "Comprar leite"));
    insere_tarefa_final(li, mk(16, "Lavar roupa"));
    imprime("apos 3 insercoes", li);

    insere_tarefa_inicio(li, mk(12, "Estudar"));
    imprime("insere_inicio(12)", li);

    remove_tarefa_inicio(li);
    insere_tarefa_final(li, mk(12, "Estudar"));
    imprime("insere_final(12)", li);

    remove_tarefa_final(li);
    imprime("remove_final", li);

    remove_tarefa(li, 23);
    imprime("remove_tarefa(23)", li);
    printf("remove_tarefa(99)=%d\n", remove_tarefa(li, 99));

    libera_lista(li);

    li = cria_lista();
    insere_tarefa_ordenada(li, mk(23, "Comprar leite"));
    insere_tarefa_ordenada(li, mk(16, "Lavar roupa"));
    imprime("ordenada", li);
    insere_tarefa_ordenada(li, mk(19, "Comprar"));
    imprime("insere_ordenada(19)", li);
    insere_tarefa_ordenada(li, mk(12, "Estudar"));
    insere_tarefa_ordenada(li, mk(40, "Dormir"));
    imprime("insere 12 e 40", li);

    if (busca_tarefa_pos(li, 3, &t))
        printf("busca_pos(3) -> codigo %d\n", t.codigo);
    if (busca_tarefa_cod(li, 19, &t))
        printf("busca_cod(19) -> %s\n", t.descricao);
    printf("busca_cod(99)=%d\n", busca_tarefa_cod(li, 99, &t));

    libera_lista(li);
    return 0;
}
