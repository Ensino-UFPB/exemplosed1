# Aula 12 · Grafo por lista de adjacência em vetores

Implementação do TAD grafo do livro-texto: cada vértice guarda os seus vizinhos em uma
linha de tamanho fixo, alocada na criação. O mesmo TAD representa grafos e dígrafos,
com ou sem pesos.

Referência: BACKES, A. R. *Algoritmos e estruturas de dados em linguagem C*, capítulo 10,
seção 10.3. As buscas em profundidade e em largura e o algoritmo de Dijkstra, assuntos das
aulas seguintes, serão publicados em pastas próprias.

## O que muda em relação ao livro

`insereAresta` testa se a linha do vértice de origem está cheia antes de gravar:

```c
if (gr->grau[orig] == gr->grau_max)   /* linha cheia */
    return 0;
```

Sem esse teste, inserir em um vértice com `grau_max` vizinhos grava em
`arestas[orig][grau_max]`, fora da linha alocada. Além disso, `cria_Grafo` libera tudo o
que já alocou quando uma das alocações falha.

## Arquivos

| Arquivo | Conteúdo |
|---|---|
| `Grafo.h` | O tipo opaco `Grafo` e os protótipos |
| `Grafo.c` | `struct grafo` e a implementação das funções |
| `main.c` | Demonstração com os traces dos slides e um dígrafo ponderado |
| `Makefile` | Compilação separada dos módulos |

## Representação em memória

```c
struct grafo {
    int eh_ponderado;   /* 1: arestas com peso */
    int nro_vert;       /* numero de vertices */
    int grau_max;       /* vizinhos por vertice */
    int **arestas;      /* arestas[v][i]: i-esimo vizinho de v */
    float **pesos;      /* pesos[v][i], se ponderado */
    int *grau;          /* grau[v]: vizinhos ja inseridos */
};
```

Grafo não dirigido com 4 vértices, `grau_max = 3` e as arestas {0, 2}, {1, 2} e {2, 3}:

```
grau      [0]  [1]  [2]  [3]
         │ 1  │ 1  │ 3  │ 1  │

arestas        [0]  [1]  [2]
  [0] ──>     │ 2  │    │    │
  [1] ──>     │ 2  │    │    │
  [2] ──>     │ 0  │ 1  │ 3  │
  [3] ──>     │ 2  │    │    │
```

Os vizinhos de `v` estão em `arestas[v][0 .. grau[v] - 1]`. É a lista sequencial estática
repetida para cada vértice, com `grau[v]` no papel de `qtd`. Uma aresta não dirigida
aparece nas duas linhas.

## Sequência da aula

O `main.c` reproduz os dois traces dos slides:

| Operação | Retorno | Linhas após a operação |
|---|---|---|
| inserir {0, 2}, {1, 2}, {2, 3} | 1 | 0: 2 · 1: 2 · 2: 0 1 3 · 3: 2 |
| `insereAresta(gr, 2, 1, 1, 0)` | 0 | linha de 2 cheia, nada muda |
| `insereAresta(gr, 0, 1, 0, 0)` | 1 | 0: 2 1 · 1: 2 0 · 2: 0 1 3 · 3: 2 |
| `removeAresta(gr, 2, 1, 0)` | 1 | 0: 2 1 · 1: 0 · 2: 0 3 · 3: 2 |
| `removeAresta(gr, 1, 3, 0)` | 0 | aresta inexistente |

Na remoção de {2, 1}, o vizinho 1 estava em `arestas[2][1]`; o último vizinho da linha,
3, foi copiado para essa posição e `grau[2]` passou de 3 para 2. Nenhum elemento foi
deslocado.

## Operações e custos

| Função | O que faz | Custo |
|---|---|---|
| `cria_Grafo` | Aloca a estrutura, `grau` (zerado), o vetor de ponteiros e uma linha por vértice | O(n) |
| `libera_Grafo` | Libera as linhas, os vetores de ponteiros, `grau` e a estrutura | O(n) |
| `insereAresta` | Grava no fim da linha de `orig`; repete para `dest` se não for dígrafo | O(1) |
| `removeAresta` | Procura `dest` na linha de `orig` e copia o último vizinho para a posição | O(grau_max) |
| `imprime_Grafo` | Percorre todas as linhas | O(n + m) |

`n` é o número de vértices e `m`, o de arestas. O espaço ocupado é `O(n · grau_max)`,
independente de quantas arestas foram inseridas.

## Erros comuns

- **Inserir sem testar a linha cheia**: escrita fora do bloco de `arestas[orig]` (o
  `valgrind` acusa *Invalid write*).
- **Liberar `gr->arestas` antes das linhas**: os endereços das linhas se perdem e cada uma
  vira um vazamento.
- **Esquecer a direção oposta em grafo não dirigido**: a aresta passa a existir só em uma
  das linhas e o grafo deixa de ser simétrico.

## Compilação e execução

```bash
make
./teste
```

Saída esperada:

```
cria_Grafo(0, 3, 0) == NULL: 1
apos inserir {0,2} {1,2} {2,3}:
  0 (grau 1): 2
  1 (grau 1): 2
  2 (grau 3): 0 1 3
  3 (grau 1): 2
insere (2,1) com linha cheia = 0
insere {0,1} = 1
  0 (grau 2): 2 1
  1 (grau 2): 2 0
  2 (grau 3): 0 1 3
  3 (grau 1): 2
remove {2,1} = 1
  0 (grau 2): 2 1
  1 (grau 1): 0
  2 (grau 2): 0 3
  3 (grau 1): 2
remove {1,3} inexistente = 0
insere {0,7} vertice invalido = 0
digrafo ponderado:
  0 (grau 2): 1(2.5) 2(4.0)
  1 (grau 0):
  2 (grau 1): 1(1.5)
```

Verificação de memória:

```bash
valgrind --leak-check=full ./teste
```

O código compila sem nenhum aviso com `-Wall -Wextra` e o `valgrind` não acusa vazamento
nem erro de acesso.

## Convenções

- Nomes das funções no padrão do livro (`cria_Grafo`, `libera_Grafo`, `insereAresta`,
  `removeAresta`), iguais aos dos slides.
- `eh_digrafo` é parâmetro de cada operação, e não campo da estrutura.
- `cria_Grafo` devolve `NULL` para `nro_vert` ou `grau_max` menores ou iguais a zero.
- Inserção e remoção devolvem `1` em caso de sucesso e `0` caso contrário.
- Comentários sem acentuação nos arquivos `.c` e `.h`.
