/* Programa de teste da biblioteca: reproduz os traces da Aula 10
   (pronto-socorro com capacidade 5, empates de prioridade, fila
   cheia e fila vazia). Quanto maior o numero, maior a prioridade. */
#include <stdio.h>
#include "FilaPrioridade.h"

/* Mostra o paciente do inicio da fila e a quantidade atual. */
static void estado(const char *rotulo, FilaPrio *fp) {
    char nome[30];
    printf("%-26s qtd=%d", rotulo, tamanho_FilaPrio(fp));
    if (consulta_FilaPrio(fp, nome))
        printf("  inicio: %s\n", nome);
    else
        printf("  (fila vazia)\n");
}

int main(void) {
    FilaPrio *fp;
    char nome[30];

    printf("cria_FilaPrio(0) == NULL: %d\n", cria_FilaPrio(0) == NULL);

    fp = cria_FilaPrio(5);
    if (fp == NULL) {
        printf("falha na alocacao\n");
        return 1;
    }
    printf("vazia=%d cheia=%d tamanho=%d\n",
           estaVazia_FilaPrio(fp), estaCheia_FilaPrio(fp), tamanho_FilaPrio(fp));

    /* Trace geral da aula */
    insere_FilaPrio(fp, "Ana", 3);   estado("insere Ana (3)", fp);
    insere_FilaPrio(fp, "Bia", 5);   estado("insere Bia (5)", fp);
    insere_FilaPrio(fp, "Caio", 1);  estado("insere Caio (1)", fp);
    insere_FilaPrio(fp, "Davi", 5);  estado("insere Davi (5), empate", fp);

    consulta_FilaPrio(fp, nome);
    printf("consulta -> %s\n", nome);

    remove_FilaPrio(fp);             estado("remove", fp);
    insere_FilaPrio(fp, "Eva", 4);   estado("insere Eva (4)", fp);

    /* Fila cheia */
    insere_FilaPrio(fp, "Fabio", 9); estado("insere Fabio (9)", fp);
    printf("vazia=%d cheia=%d tamanho=%d\n",
           estaVazia_FilaPrio(fp), estaCheia_FilaPrio(fp), tamanho_FilaPrio(fp));
    printf("insere em fila cheia = %d\n", insere_FilaPrio(fp, "Gil", 2));

    /* Atende todos, do inicio para o final */
    while (consulta_FilaPrio(fp, nome)) {
        printf("atende %s\n", nome);
        remove_FilaPrio(fp);
    }
    printf("remove em fila vazia = %d\n", remove_FilaPrio(fp));
    printf("consulta em fila vazia = %d\n", consulta_FilaPrio(fp, nome));

    libera_FilaPrio(fp);
    return 0;
}
