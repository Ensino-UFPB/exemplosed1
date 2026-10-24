/* ============================================================
   FilaPrioridade.c
   Estrutura de Dados I - UFPB - Aula 10
   Implementacao da fila de prioridade sobre vetor ordenado,
   com capacidade definida na criacao.

   Tudo o que deve ficar oculto do usuario da biblioteca esta
   aqui: o tipo do elemento, a definicao de struct
   fila_prioridade e o corpo das funcoes.
   ============================================================ */

#include <stdlib.h>
#include <string.h>
#include "FilaPrioridade.h"

/* Elemento armazenado: paciente de um pronto-socorro. */
struct paciente {
    char nome[30];
    int  prio;
};

/* qtd:        quantos pacientes estao na fila.
   capacidade: tamanho do vetor dados, escolhido em cria_FilaPrio.
   dados:      vetor alocado com malloc em cria_FilaPrio.

   O vetor e mantido em ordem CRESCENTE de prioridade:
   - dados[qtd - 1] guarda o paciente de maior prioridade, que e o
     inicio da fila (o proximo a sair);
   - dados[0] guarda o de menor prioridade, que e o final da fila.
   Assim a remocao e a consulta acessam a ultima posicao ocupada e
   nao deslocam ninguem. */
struct fila_prioridade {
    int qtd;
    int capacidade;
    struct paciente *dados;
};

/* ------------------------------------------------------------
   Criacao e destruicao
   ------------------------------------------------------------ */

FilaPrio* cria_FilaPrio(int capacidade) {
    FilaPrio *fp;
    if (capacidade <= 0)
        return NULL;
    fp = (FilaPrio*) malloc(sizeof(struct fila_prioridade));      /* 1a alocacao */
    if (fp == NULL)
        return NULL;
    fp->dados = (struct paciente*) malloc(capacidade * sizeof(struct paciente));
    if (fp->dados == NULL) {                                       /* 2a alocacao falhou */
        free(fp);       /* sem este free, a struct ficaria perdida */
        return NULL;
    }
    fp->capacidade = capacidade;
    fp->qtd = 0;
    return fp;
}

void libera_FilaPrio(FilaPrio* fp) {
    if (fp == NULL)
        return;
    free(fp->dados);    /* primeiro o vetor: fp ainda e valido aqui */
    free(fp);           /* depois a estrutura que guardava o vetor */
}

/* ------------------------------------------------------------
   Informacoes de estado
   ------------------------------------------------------------ */

int tamanho_FilaPrio(FilaPrio* fp) {
    if (fp == NULL)
        return -1;
    return fp->qtd;
}

int estaCheia_FilaPrio(FilaPrio* fp) {
    if (fp == NULL)
        return -1;
    return (fp->qtd == fp->capacidade);   /* no livro: qtd == MAX */
}

int estaVazia_FilaPrio(FilaPrio* fp) {
    if (fp == NULL)
        return -1;
    return (fp->qtd == 0);
}

/* ------------------------------------------------------------
   Operacoes da fila
   ------------------------------------------------------------ */

/* Procura a posicao do novo paciente a partir do inicio da fila
   (dados[qtd - 1]) em direcao a dados[0]. Cada paciente com
   prioridade MAIOR OU IGUAL e copiado uma posicao a direita.
   O >= garante a regra de empate: quem ja esta na fila com a
   mesma prioridade permanece mais perto do inicio.
   A copia vai do fim para o comeco para que cada leitura ocorra
   antes de a posicao ser sobrescrita. */
int insere_FilaPrio(FilaPrio* fp, char *nome, int prioridade) {
    int i;
    if (fp == NULL)
        return 0;
    if (fp->qtd == fp->capacidade)        /* fila cheia */
        return 0;
    i = fp->qtd - 1;
    /* i >= 0 e testado primeiro: com i == -1 o && nao le dados[-1] */
    while (i >= 0 && fp->dados[i].prio >= prioridade) {
        fp->dados[i + 1] = fp->dados[i];
        i--;
    }
    strcpy(fp->dados[i + 1].nome, nome);
    fp->dados[i + 1].prio = prioridade;
    fp->qtd++;
    return 1;
}

/* O paciente de maior prioridade esta em dados[qtd - 1]: basta
   decrementar qtd. Os dados continuam no vetor, mas a posicao
   deixa de pertencer a fila. */
int remove_FilaPrio(FilaPrio* fp) {
    if (fp == NULL || fp->qtd == 0)
        return 0;
    fp->qtd--;
    return 1;
}

/* Sem o teste de fila vazia, com qtd == 0 a funcao leria dados[-1],
   fora do vetor. */
int consulta_FilaPrio(FilaPrio* fp, char *nome) {
    if (fp == NULL || fp->qtd == 0)
        return 0;
    strcpy(nome, fp->dados[fp->qtd - 1].nome);
    return 1;
}
