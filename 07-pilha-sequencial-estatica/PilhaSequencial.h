/* ============================================================
   PilhaSequencial.h
   Estrutura de Dados I - UFPB - Aula 11
   Pilha sequencial estatica com capacidade definida na criacao

   Referencia: BACKES, A. R. Algoritmos e Estruturas de Dados em
   Linguagem C. Rio de Janeiro: LTC, 2023. Capitulo 8, secao 8.4.

   Diferenca em relacao ao livro: no livro o vetor de dados tem
   tamanho fixo MAX, definido em tempo de compilacao. Aqui o
   tamanho (capacidade) e informado pelo usuario em cria_Pilha,
   e o vetor e alocado com malloc nesse momento. Depois de
   criada, a pilha continua com capacidade fixa: o vetor nao
   cresce nem diminui.

   Este arquivo declara tudo o que e visivel para quem usa a
   biblioteca. Os campos de struct pilha ficam ocultos em
   PilhaSequencial.c: Pilha e um tipo opaco.
   ============================================================ */

#ifndef PILHA_SEQUENCIAL_H
#define PILHA_SEQUENCIAL_H

/* Tipo do elemento armazenado na pilha. */
struct aluno {
    int   matricula;
    char  nome[30];
    float n1, n2, n3;
};

/* Tipo opaco: o usuario da biblioteca so pode declarar Pilha *pi. */
typedef struct pilha Pilha;

/* --- criacao e destruicao ---------------------------------- */

/* Aloca a estrutura da pilha e um vetor com 'capacidade' posicoes.
   Devolve o ponteiro da pilha, ou NULL se capacidade <= 0 ou se
   qualquer uma das duas alocacoes falhar. */
Pilha* cria_Pilha(int capacidade);

/* Libera o vetor de dados e, em seguida, a estrutura da pilha. */
void libera_Pilha(Pilha* pi);

/* --- informacoes de estado --------------------------------- */

/* Devolve a quantidade de elementos, ou -1 se pi for NULL. */
int tamanho_Pilha(Pilha* pi);

/* Devolve 1 se a pilha esta cheia, 0 caso contrario, -1 se pi for NULL. */
int Pilha_cheia(Pilha* pi);

/* Devolve 1 se a pilha esta vazia, 0 caso contrario, -1 se pi for NULL. */
int Pilha_vazia(Pilha* pi);

/* --- operacoes da pilha -------------------------------------
   Todas acontecem no topo, isto e, na posicao qtd - 1 do vetor.
   Devolvem 1 em caso de sucesso e 0 caso contrario. ---------- */

/* Insere no topo da pilha (empilha). Falha se a pilha for invalida
   ou estiver cheia. Custo O(1). */
int insere_Pilha(Pilha* pi, struct aluno al);

/* Remove o elemento do topo da pilha (desempilha). Falha se a pilha
   for invalida ou estiver vazia. Custo O(1). */
int remove_Pilha(Pilha* pi);

/* Copia para *al o elemento do topo, sem remove-lo. Falha se a
   pilha for invalida ou estiver vazia. Custo O(1). */
int consulta_topo_Pilha(Pilha* pi, struct aluno *al);

#endif /* PILHA_SEQUENCIAL_H */
