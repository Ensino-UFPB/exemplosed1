/* ============================================================
   ListaDinEncadDupla.h
   Estrutura de Dados I - UFPB - Aula 08
   Lista dinamica duplamente encadeada

   Referencia: BACKES, A. R. Algoritmos e Estruturas de Dados em
   Linguagem C. Rio de Janeiro: LTC, 2023. Capitulo 5, secao 5.7.

   Este arquivo declara tudo o que e visivel para quem usa a
   biblioteca. A definicao de struct elemento fica oculta em
   ListaDinEncadDupla.c: Lista e um tipo opaco.

   A DIFERENCA PARA A LISTA DINAMICA ENCADEADA SIMPLES NAO ESTA
   AQUI. A interface e identica: os mesmos tipos visiveis e os
   mesmos prototipos. O que muda esta escondido no .c: cada
   elemento ganha um terceiro campo, ant, com o endereco do
   elemento anterior. O primeiro elemento aponta ant para NULL
   e o ultimo aponta prox para NULL.

   Consequencia pratica para quem for estender esta biblioteca:
   toda insercao e toda remocao precisam manter os DOIS sentidos
   consistentes, e a religacao vem sempre antes do free.
   ============================================================ */

#ifndef LISTA_DIN_ENCAD_DUPLA_H
#define LISTA_DIN_ENCAD_DUPLA_H

/* Tipo do dado armazenado na lista. */
struct aluno {
    int matricula;
    char nome[30];
    float n1, n2, n3;
};

/* Tipo opaco. Lista ja inclui um ponteiro (struct elemento*), de modo que
   Lista* e um ponteiro para ponteiro: o usuario declara Lista *li, e as
   funcoes podem alterar o inicio da lista alterando o conteudo de *li. */
typedef struct elemento* Lista;

/* --- criacao e destruicao ---------------------------------- */

/* Aloca o bloco do inicio e o inicializa com NULL (lista vazia).
   Devolve o ponteiro da lista, ou NULL se a alocacao falhar.
   Identica a da lista encadeada simples. */
Lista* cria_lista(void);

/* Libera todos os elementos e, por fim, o bloco do inicio.
   Percorre a lista apenas por prox; o campo ant e ignorado.
   Custo O(n). */
void libera_lista(Lista* li);

/* --- informacoes de estado --------------------------------- */

/* Devolve a quantidade de elementos; devolve 0 se li for NULL.
   Percorre apenas por prox. Custo O(n). */
int tamanho_lista(Lista* li);

/* Devolve sempre 0. Uma lista com alocacao dinamica so fica cheia
   quando falta memoria para o malloc, o que e detectado dentro das
   funcoes de insercao. */
int lista_cheia(Lista* li);

/* Devolve 1 se a lista estiver vazia ou se li for NULL (lista
   invalida), 0 caso contrario. */
int lista_vazia(Lista* li);

/* --- insercao ----------------------------------------------
   Todas devolvem 1 em caso de sucesso e 0 caso contrario
   (lista invalida ou falta de memoria).

   Alem do prox, cada insercao escreve o ant do novo elemento e,
   quando ele existe, o ant do elemento que passa a ser o seu
   sucessor. ------------------------------------------------ */

/* Insere antes do primeiro elemento. Nao percorre a lista.
   Custo O(1). */
int insere_lista_inicio(Lista* li, struct aluno al);

/* Percorre a lista ate o ultimo elemento e insere depois dele.
   O campo ant nao evita esse percurso. Custo O(n). */
int insere_lista_final(Lista* li, struct aluno al);

/* Insere mantendo a lista ordenada de forma crescente por
   matricula. O ponto de insercao pode ser no inicio, no meio ou
   no final. Custo O(n). */
int insere_lista_ordenada(Lista* li, struct aluno al);

/* --- remocao -----------------------------------------------
   Todas devolvem 1 em caso de sucesso e 0 caso contrario
   (lista invalida, lista vazia ou elemento inexistente).

   O antecessor do elemento removido e obtido pelo proprio no,
   em no->ant: nenhuma remocao precisa de um segundo ponteiro de
   percurso, ao contrario da lista encadeada simples. -------- */

/* Remove o primeiro elemento; o novo primeiro passa a apontar
   ant para NULL. Custo O(1). */
int remove_lista_inicio(Lista* li);

/* Percorre a lista ate o ultimo elemento e o remove; o penultimo
   e alcancado por no->ant. Custo O(n). */
int remove_lista_final(Lista* li);

/* Remove o elemento de matricula igual a passada, esteja ele no
   inicio, no meio ou no final. Custo O(n). */
int remove_lista(Lista* li, int mat);

/* --- busca -------------------------------------------------
   Copiam o elemento encontrado para *al e devolvem 1; devolvem 0
   quando a busca falha. Identicas as da lista encadeada simples:
   o percurso usa apenas prox. -------------------------------- */

/* Busca pela posicao na lista, contada a partir de 1 no inicio.
   Posicoes menores que 1 ou maiores que o numero de elementos
   devolvem 0. Custo O(n). */
int busca_lista_pos(Lista* li, int pos, struct aluno *al);

/* Busca pelo conteudo do campo matricula. Custo O(n). */
int busca_lista_mat(Lista* li, int mat, struct aluno *al);

#endif /* LISTA_DIN_ENCAD_DUPLA_H */
