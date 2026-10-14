/* ============================================================
   main.c
   Estrutura de Dados I - UFPB - Aula 07

   Programa de demonstracao: reproduz, na ordem, os oito traces
   apresentados nos slides da Aula 07, imprimindo o estado da
   lista antes e depois de cada operacao.

   Note que este arquivo usa apenas o que esta declarado em
   ListaDinEncadCirc.h. Em nenhum ponto ele acessa os campos
   dados ou prox: o tipo struct elemento nao e visivel aqui.
   E por isso que as funcoes das listas de exercicios devem ser
   escritas dentro de ListaDinEncadCirc.c, e nao neste arquivo.
   ============================================================ */

#include <stdio.h>
#include <string.h>
#include "ListaDinEncadCirc.h"

/* Constroi um aluno a partir da matricula; as notas nao importam
   na maior parte das demonstracoes. */
static struct aluno mk(int matricula, float n1, float n2, float n3) {
    struct aluno a;
    a.matricula = matricula;
    snprintf(a.nome, sizeof(a.nome), "Aluno %d", matricula);
    a.n1 = n1; a.n2 = n2; a.n3 = n3;
    return a;
}

/* Imprime uma volta completa da lista usando apenas a interface
   publica. A seta final volta ao primeiro elemento, para deixar
   a circularidade visivel na saida. */
static void imprime(const char *rotulo, Lista *li) {
    int i, n = tamanho_lista(li);
    struct aluno a;
    printf("  %-26s tam=%d: ", rotulo, n);
    if (n == 0) {
        printf("(vazia)\n");
        return;
    }
    printf("inicio ->");
    for (i = 1; i <= n; i++) {
        busca_lista_pos(li, i, &a);
        printf(" [%d] ->", a.matricula);
    }
    printf(" volta ao inicio\n");
}

/* Monta uma lista com as matriculas dadas, inserindo no final. */
static Lista* monta(const int *mats, int n) {
    Lista *li = cria_lista();
    for (int i = 0; i < n; i++)
        insere_lista_final(li, mk(mats[i], 0, 0, 0));
    return li;
}

static void titulo(const char *t) {
    printf("\n%s\n", t);
}

int main(void) {
    struct aluno a;
    Lista *li;

    /* ---------- estado inicial, slide de criacao ---------- */
    titulo("Criacao da lista");
    li = cria_lista();
    printf("  vazia=%d  cheia=%d  tamanho=%d\n",
           lista_vazia(li), lista_cheia(li), tamanho_lista(li));

    /* ---------- insercao em lista vazia ---------- */
    titulo("Insercao em lista vazia: o no aponta para si mesmo");
    insere_lista_final(li, mk(12, 8, 8, 8));
    imprime("apos inserir 12", li);
    libera_lista(li);

    /* ---------- Trace 2: tamanho_lista ---------- */
    titulo("Trace 2 - tamanho_lista sobre [33, 23]");
    {
        int m[] = {33, 23};
        li = monta(m, 2);
        imprime("lista montada", li);
        printf("  tamanho_lista devolve %d (uma volta completa)\n", tamanho_lista(li));
        /* ---------- Trace 1: libera_lista ---------- */
        titulo("Trace 1 - libera_lista sobre a mesma lista");
        libera_lista(li);
        printf("  memoria dos dois nos e do bloco de inicio liberada\n");
    }

    /* ---------- Trace 3: insercao no inicio ---------- */
    titulo("Trace 3 - insere_lista_inicio(12) em [33, 23, 16]");
    {
        int m[] = {33, 23, 16};
        li = monta(m, 3);
        imprime("antes", li);
        insere_lista_inicio(li, mk(12, 0, 0, 0));
        imprime("depois", li);
        libera_lista(li);
    }

    /* ---------- Trace 4: insercao no final ---------- */
    titulo("Trace 4 - insere_lista_final(12) na mesma lista inicial");
    {
        int m[] = {33, 23, 16};
        li = monta(m, 3);
        imprime("antes", li);
        insere_lista_final(li, mk(12, 0, 0, 0));
        imprime("depois", li);
        printf("  mesma sequencia de ligacoes do trace 3: so o inicio difere\n");
        libera_lista(li);
    }

    /* ---------- Trace 5: insercao ordenada ---------- */
    titulo("Trace 5 - insere_lista_ordenada(30) em [16, 23, 40]");
    {
        int m[] = {16, 23, 40};
        li = monta(m, 3);
        imprime("antes", li);
        insere_lista_ordenada(li, mk(30, 0, 0, 0));
        imprime("depois (meio)", li);
        insere_lista_ordenada(li, mk(10, 0, 0, 0));
        imprime("depois (inicio)", li);
        insere_lista_ordenada(li, mk(50, 0, 0, 0));
        imprime("depois (final)", li);
        libera_lista(li);
    }

    /* ---------- Traces 6 e 7: remocao nas extremidades ---------- */
    titulo("Trace 6 - remove_lista_inicio em [16, 12, 23]");
    {
        int m[] = {16, 12, 23};
        li = monta(m, 3);
        imprime("antes", li);
        remove_lista_inicio(li);
        imprime("depois", li);
        libera_lista(li);
    }

    titulo("Trace 7 - remove_lista_final na mesma lista inicial");
    {
        int m[] = {16, 12, 23};
        li = monta(m, 3);
        imprime("antes", li);
        remove_lista_final(li);
        imprime("depois", li);
        libera_lista(li);
    }

    /* ---------- Trace 8: remocao de elemento especifico ---------- */
    titulo("Trace 8 - remove_lista(16) em [12, 16, 23]");
    {
        int m[] = {12, 16, 23};
        li = monta(m, 3);
        imprime("antes", li);
        remove_lista(li, 16);
        imprime("remove do meio", li);
        remove_lista(li, 12);
        imprime("remove do inicio", li);
        printf("  remove_lista(99) devolve %d (chave ausente)\n", remove_lista(li, 99));
        remove_lista(li, 23);
        imprime("remove o unico", li);
        printf("  vazia=%d\n", lista_vazia(li));
        libera_lista(li);
    }

    /* ---------- buscas ---------- */
    titulo("Busca por posicao e por conteudo em [33, 23, 16]");
    {
        int m[] = {33, 23, 16};
        li = monta(m, 3);
        if (busca_lista_pos(li, 3, &a))
            printf("  busca_lista_pos(3)  -> matricula %d\n", a.matricula);
        printf("  busca_lista_pos(9)  -> %d (posicao inexistente)\n",
               busca_lista_pos(li, 9, &a));
        if (busca_lista_mat(li, 33, &a))
            printf("  busca_lista_mat(33) -> %s\n", a.nome);
        printf("  busca_lista_mat(99) -> %d (chave ausente)\n",
               busca_lista_mat(li, 99, &a));
        libera_lista(li);
    }

    /* ---------- a propriedade que define a estrutura ---------- */
    titulo("Duas voltas seguidas na mesma lista");
    {
        int m[] = {33, 23, 16};
        int i, n;
        li = monta(m, 3);
        n = tamanho_lista(li);
        printf("  ");
        for (i = 0; i < 2 * n; i++) {          /* duas voltas, sem reiniciar */
            busca_lista_pos(li, (i % n) + 1, &a);
            printf("%d ", a.matricula);
        }
        printf("\n  nenhum campo prox vale NULL: o percurso nao tem fim natural\n");
        libera_lista(li);
    }

    printf("\n");
    return 0;
}
