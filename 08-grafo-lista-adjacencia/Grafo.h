/* ============================================================
   Grafo.h
   Estrutura de Dados I - UFPB - Aula 12
   Grafo representado por lista de adjacencia em vetores

   Referencia: BACKES, A. R. Algoritmos e Estruturas de Dados em
   Linguagem C. Rio de Janeiro: LTC, 2023. Capitulo 10, secao 10.3.

   Cada vertice v tem uma linha arestas[v] com grau_max posicoes,
   alocada na criacao. grau[v] conta os vizinhos ja inseridos: os
   vizinhos de v estao em arestas[v][0 .. grau[v] - 1]. E a mesma
   organizacao da lista sequencial estatica, com grau[v] no papel
   de qtd.

   Os vertices sao numerados de 0 a nro_vert - 1. Um grafo nao
   dirigido e armazenado como um digrafo com as duas direcoes de
   cada aresta: o parametro eh_digrafo de cada operacao escolhe
   o comportamento.

   Diferenca em relacao ao livro: insereAresta testa se a linha
   de orig esta cheia (grau[orig] == grau_max) antes de gravar,
   em vez de escrever fora do vetor.

   Este arquivo declara tudo o que e visivel para quem usa a
   biblioteca. Os campos de struct grafo ficam ocultos em
   Grafo.c: Grafo e um tipo opaco.
   ============================================================ */

#ifndef GRAFO_H
#define GRAFO_H

/* Tipo opaco: o usuario da biblioteca so pode declarar Grafo *gr. */
typedef struct grafo Grafo;

/* --- criacao e destruicao ---------------------------------- */

/* Cria um grafo com nro_vert vertices, cada um com espaco para ate
   grau_max vizinhos. Se eh_ponderado for 1, aloca tambem a matriz
   de pesos. Devolve NULL se nro_vert <= 0, grau_max <= 0 ou se
   alguma alocacao falhar. Custo O(nro_vert). */
Grafo* cria_Grafo(int nro_vert, int grau_max, int eh_ponderado);

/* Libera as linhas de arestas (e de pesos), os vetores de
   ponteiros, o vetor grau e, por ultimo, a estrutura.
   Custo O(nro_vert). */
void libera_Grafo(Grafo* gr);

/* --- operacoes sobre arestas --------------------------------
   Devolvem 1 em caso de sucesso e 0 caso contrario. ---------- */

/* Insere a aresta (orig, dest) no fim da linha de orig. Se
   eh_digrafo for 0, insere tambem (dest, orig). Falha se gr for
   NULL, se algum vertice for invalido ou se a linha estiver cheia.
   O peso so e gravado se o grafo for ponderado. Custo O(1). */
int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso);

/* Remove a aresta (orig, dest): procura dest na linha de orig e
   copia o ultimo vizinho para a posicao removida. Se eh_digrafo
   for 0, remove tambem (dest, orig). Falha se a aresta nao existir.
   Custo O(grau_max). */
int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo);

/* --- consulta ----------------------------------------------- */

/* Mostra a lista de adjacencia, uma linha por vertice, com o grau
   e os vizinhos (e os pesos, se o grafo for ponderado). */
void imprime_Grafo(Grafo* gr);

#endif /* GRAFO_H */
