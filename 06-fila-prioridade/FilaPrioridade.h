/* ============================================================
   FilaPrioridade.h
   Estrutura de Dados I - UFPB - Aula 10
   Fila de prioridade sobre vetor ordenado, com capacidade
   definida na criacao

   Referencia: BACKES, A. R. Algoritmos e Estruturas de Dados em
   Linguagem C. Rio de Janeiro: LTC, 2023. Capitulo 7, secoes
   7.1 a 7.7 (implementacao com array ordenado).

   Diferenca em relacao ao livro: no livro o vetor de dados tem
   tamanho fixo MAX, definido em tempo de compilacao. Aqui o
   tamanho (capacidade) e informado pelo usuario em
   cria_FilaPrio, e o vetor e alocado com malloc nesse momento,
   como na fila sequencial da Aula 09.

   Quanto maior o numero da prioridade, maior a prioridade. Com
   prioridades iguais, sai primeiro quem foi inserido primeiro.

   Este arquivo declara tudo o que e visivel para quem usa a
   biblioteca. Os campos de struct fila_prioridade e o tipo do
   elemento (struct paciente) ficam ocultos em FilaPrioridade.c:
   FilaPrio e um tipo opaco.
   ============================================================ */

#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

/* Tipo opaco: o usuario da biblioteca so pode declarar FilaPrio *fp. */
typedef struct fila_prioridade FilaPrio;

/* --- criacao e destruicao ---------------------------------- */

/* Aloca a estrutura da fila e um vetor com 'capacidade' pacientes.
   Devolve o ponteiro da fila, ou NULL se capacidade <= 0 ou se
   qualquer uma das duas alocacoes falhar. */
FilaPrio* cria_FilaPrio(int capacidade);

/* Libera o vetor de dados e, em seguida, a estrutura da fila. */
void libera_FilaPrio(FilaPrio* fp);

/* --- informacoes de estado --------------------------------- */

/* Devolve a quantidade de pacientes, ou -1 se fp for NULL. */
int tamanho_FilaPrio(FilaPrio* fp);

/* Devolve 1 se a fila esta cheia, 0 caso contrario, -1 se fp for NULL. */
int estaCheia_FilaPrio(FilaPrio* fp);

/* Devolve 1 se a fila esta vazia, 0 caso contrario, -1 se fp for NULL. */
int estaVazia_FilaPrio(FilaPrio* fp);

/* --- operacoes da fila --------------------------------------
   Devolvem 1 em caso de sucesso e 0 caso contrario. ---------- */

/* Insere um paciente com a prioridade informada, mantendo o vetor
   em ordem crescente de prioridade. Falha se a fila for invalida
   ou estiver cheia. O nome deve ter no maximo 29 caracteres.
   Custo O(N) no pior caso e O(1) no melhor. */
int insere_FilaPrio(FilaPrio* fp, char *nome, int prioridade);

/* Remove o paciente de maior prioridade (inicio da fila). Falha se
   a fila for invalida ou estiver vazia. Custo O(1). */
int remove_FilaPrio(FilaPrio* fp);

/* Copia para 'nome' o nome do paciente de maior prioridade, sem
   remove-lo. 'nome' deve ter espaco para 30 caracteres. Falha se a
   fila for invalida ou estiver vazia. Custo O(1). */
int consulta_FilaPrio(FilaPrio* fp, char *nome);

#endif /* FILA_PRIORIDADE_H */
