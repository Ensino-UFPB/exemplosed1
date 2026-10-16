/* ============================================================
   FilaEstatica.h
   Estrutura de Dados I - UFPB - Aula 09
   Fila sequencial estatica com capacidade definida na criacao

   Referencia: BACKES, A. R. Algoritmos e Estruturas de Dados em
   Linguagem C. Rio de Janeiro: LTC, 2023. Capitulo 6, secao 6.4.

   Diferenca em relacao ao livro: no livro o vetor de dados tem
   tamanho fixo MAX, definido em tempo de compilacao. Aqui o
   tamanho (capacidade) e informado pelo usuario em cria_Fila,
   e o vetor e alocado com malloc nesse momento. Depois de
   criada, a fila continua com capacidade fixa: o vetor nao
   cresce nem diminui.

   Este arquivo declara tudo o que e visivel para quem usa a
   biblioteca. Os campos de struct fila ficam ocultos em
   FilaEstatica.c: Fila e um tipo opaco.
   ============================================================ */

#ifndef FILA_ESTATICA_H
#define FILA_ESTATICA_H

/* Tipo do elemento armazenado na fila. */
struct aluno {
    int   matricula;
    char  nome[30];
    float n1, n2, n3;
};

/* Tipo opaco: o usuario da biblioteca so pode declarar Fila *fi. */
typedef struct fila Fila;

/* --- criacao e destruicao ---------------------------------- */

/* Aloca a estrutura da fila e um vetor com 'capacidade' posicoes.
   Devolve o ponteiro da fila, ou NULL se capacidade <= 0 ou se
   qualquer uma das duas alocacoes falhar. */
Fila* cria_Fila(int capacidade);

/* Libera o vetor de dados e, em seguida, a estrutura da fila. */
void libera_Fila(Fila* fi);

/* --- informacoes de estado --------------------------------- */

/* Devolve a quantidade de elementos, ou -1 se fi for NULL. */
int tamanho_Fila(Fila* fi);

/* Devolve 1 se a fila esta cheia, 0 caso contrario, -1 se fi for NULL. */
int Fila_cheia(Fila* fi);

/* Devolve 1 se a fila esta vazia, 0 caso contrario, -1 se fi for NULL. */
int Fila_vazia(Fila* fi);

/* --- operacoes da fila --------------------------------------
   Devolvem 1 em caso de sucesso e 0 caso contrario. ---------- */

/* Insere no final da fila. Falha se a fila for invalida ou estiver
   cheia. Custo O(1). */
int insere_Fila(Fila* fi, struct aluno al);

/* Remove o elemento do inicio da fila. Falha se a fila for invalida
   ou estiver vazia. Custo O(1). */
int remove_Fila(Fila* fi);

/* Copia para *al o elemento do inicio da fila, sem remove-lo. Falha
   se a fila for invalida ou estiver vazia. Custo O(1). */
int consulta_Fila(Fila* fi, struct aluno *al);

#endif /* FILA_ESTATICA_H */
