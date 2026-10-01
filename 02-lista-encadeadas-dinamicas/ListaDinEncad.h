/* ============================================================
   ListaDinEncad.h
   Estrutura de Dados I - UFPB - Aula 06
   Lista dinamica encadeada (alocacao dinamica, acesso encadeado)

   Referencia: BACKES, A. R. Algoritmos e Estruturas de Dados em
   Linguagem C. Rio de Janeiro: LTC, 2023. Capitulo 5.

   Este arquivo declara tudo o que e visivel para quem usa a
   biblioteca. A definicao de struct elemento fica oculta em
   ListaDinEncad.c: Lista e um tipo opaco.
   ============================================================ */

#ifndef LISTA_DIN_ENCAD_H
#define LISTA_DIN_ENCAD_H

/* Tipo do elemento armazenado na lista. */
struct tarefa {
    int codigo;
    char descricao[40];
    int prioridade;
};

/* Tipo opaco. ListaTarefas ja inclui um ponteiro (struct elemento*), de modo
   que ListaTarefas* e um ponteiro para ponteiro: o usuario declara ListaTarefas *li,
   exatamente como na lista sequencial estatica. */
typedef struct elemento* ListaTarefas;

/* --- criacao e destruicao ---------------------------------- */

/* Aloca o bloco do inicio e o inicializa com NULL (lista vazia).
   Devolve o ponteiro da lista, ou NULL se a alocacao falhar. */
ListaTarefas* cria_lista(void);

/* Libera todos os elementos e, por fim, o bloco do inicio. Custo O(n). */
void libera_lista(ListaTarefas* li);

/* --- informacoes de estado --------------------------------- */

/* Devolve a quantidade de elementos, ou -1 se li for NULL.
   Percorre a lista inteira: custo O(n). */
int tamanho_lista(ListaTarefas* li);

/* Devolve 0 (a lista so fica cheia quando falta memoria para o malloc),
   ou -1 se li for NULL. */
int lista_cheia(ListaTarefas* li);

/* Devolve 1 se a lista esta vazia, 0 caso contrario, -1 se li for NULL. */
int lista_vazia(ListaTarefas* li);

/* --- insercao ----------------------------------------------
   Todas devolvem 1 em caso de sucesso e 0 caso contrario
   (lista invalida ou falta de memoria). -------------------- */

/* Insere antes do primeiro elemento. Custo O(1). */
int insere_tarefa_inicio(ListaTarefas* li, struct tarefa t);

/* Percorre a lista ate o ultimo elemento e insere depois dele. Custo O(n). */
int insere_tarefa_final(ListaTarefas* li, struct tarefa t);

/* Insere mantendo a lista ordenada de forma crescente por prioridade.
   Custo O(n). */
int insere_tarefa_ordenada(ListaTarefas* li, struct tarefa t);

/* --- remocao -----------------------------------------------
   Todas devolvem 1 em caso de sucesso e 0 caso contrario
   (lista invalida, lista vazia ou elemento inexistente). --- */

/* Remove o primeiro elemento. Custo O(1). */
int remove_tarefa_inicio(ListaTarefas* li);

/* Percorre a lista ate o ultimo elemento e o remove. Custo O(n). */
int remove_tarefa_final(ListaTarefas* li);

/* Remove o elemento de codigo igual ao passado. Custo O(n). */
int remove_tarefa(ListaTarefas* li, int codigo);

/* --- busca -------------------------------------------------
   Copiam o elemento encontrado para *t e devolvem 1; devolvem 0
   quando a busca falha. ------------------------------------ */

/* Busca pela posicao na lista, contada a partir de 1. Custo O(n). */
int busca_tarefa_pos(ListaTarefas* li, int pos, struct tarefa *t);

/* Busca pelo conteudo do campo codigo. Custo O(n). */
int busca_tarefa_cod(ListaTarefas* li, int codigo, struct tarefa *t);

#endif /* LISTA_DIN_ENCAD_H */
