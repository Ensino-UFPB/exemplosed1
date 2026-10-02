/* Programa de teste da biblioteca: reproduz os traces da Aula 06. */
#include <stdio.h>
#include <string.h>
#include "ListaDinEncad.h"

static struct tarefa mk(int codigo, const char *descricao, int prioridade) {
    struct tarefa t;
    t.codigo = codigo;
    strncpy(t.descricao, descricao, sizeof(t.descricao) - 1);
    t.descricao[sizeof(t.descricao) - 1] = '\0';
    t.prioridade = prioridade;
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

    insere_tarefa_final(li, mk(12, "Estudar", 3));
    insere_tarefa_final(li, mk(23, "Comprar leite", 1));
    insere_tarefa_final(li, mk(16, "Lavar roupa", 2));
    imprime("apos 3 insercoes", li);

    insere_tarefa_inicio(li, mk(30, "Revisar", 3));
    imprime("insere_inicio(30)", li);

    remove_tarefa_inicio(li);
    insere_tarefa_final(li, mk(40, "Dormir", 4));
    imprime("insere_final(40)", li);

    remove_tarefa_final(li);
    imprime("remove_final", li);

    remove_tarefa(li, 23);
    imprime("remove_tarefa(23)", li);
    printf("remove_tarefa(99)=%d\n", remove_tarefa(li, 99));

    libera_lista(li);

    li = cria_lista();
    insere_tarefa_ordenada(li, mk(23, "Comprar leite", 3));
    insere_tarefa_ordenada(li, mk(16, "Lavar roupa", 1));
    insere_tarefa_ordenada(li, mk(19, "Comprar", 2));
    insere_tarefa_ordenada(li, mk(12, "Estudar", 1));
    insere_tarefa_ordenada(li, mk(40, "Dormir", 4));
    imprime("ordenada por prioridade", li);

    if (busca_tarefa_pos(li, 3, &t))
        printf("busca_pos(3) -> codigo %d\n", t.codigo);
    if (busca_tarefa_cod(li, 19, &t))
        printf("busca_cod(19) -> %s\n", t.descricao);
    printf("busca_cod(99)=%d\n", busca_tarefa_cod(li, 99, &t));

    libera_lista(li);
    return 0;
}
