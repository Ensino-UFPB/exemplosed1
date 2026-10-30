# Aula 11 · Pilha sequencial estática com capacidade definida na criação

Implementação de uma pilha (estrutura LIFO: o último a entrar é o primeiro a sair) com
**acesso sequencial** sobre um vetor. A inserção, a remoção e a consulta acontecem sempre
na mesma extremidade, o **topo**. O elemento armazenado é uma `struct aluno` com
matrícula, nome e três notas.

Referência: BACKES, A. R. *Algoritmos e estruturas de dados em linguagem C*, capítulo 8,
seção 8.4. A pilha dinâmica encadeada (seção 8.5) e a pilha construída sobre a lista
encadeada (seção 8.6) são discutidas ao final da aula; a segunda é a questão 5 da lista
de exercícios.

## O que muda em relação ao livro

Como nas filas das aulas 09 e 10, o vetor não tem tamanho `MAX` fixo. Quem cria a pilha
escolhe a capacidade:

```c
Pilha *pi = cria_Pilha(4);   /* pilha com 4 posicoes */
```

```c
struct pilha {
    int qtd;
    int capacidade;
    struct aluno *dados;   /* vetor alocado com malloc em cria_Pilha */
};
```

Depois de criada, a capacidade não muda e a pilha pode ficar cheia. Como nas filas, a
criação faz duas alocações (a estrutura e o vetor, liberando a estrutura se a segunda
falhar) e `libera_Pilha` faz dois `free`, o vetor antes da estrutura.

## Onde fica o topo

A pilha sequencial é implementada como a lista sequencial estática, permitindo apenas a
inserção e a remoção no **final** do vetor, que é a extremidade sem deslocamentos:

- a base é `dados[0]`;
- o topo é `dados[qtd - 1]`;
- a próxima inserção grava em `dados[qtd]`, a primeira posição livre.

Nenhum índice de topo é guardado: `qtd` faz o papel de tamanho, de primeira posição livre
e, menos um, de posição do topo. Por isso a pilha precisa de menos campos que a fila, que
mantém `inicio` e `final` e usa o vetor circular.

## Arquivos

| Arquivo | Conteúdo |
|---|---|
| `PilhaSequencial.h` | `struct aluno`, o tipo opaco `Pilha` e os protótipos |
| `PilhaSequencial.c` | `struct pilha` (campos `qtd`, `capacidade` e `dados`) e a implementação das funções |
| `main.c` | Demonstração das operações, com a saída esperada abaixo |
| `Makefile` | Compilação separada dos módulos |

## Representação em memória

Pilha com capacidade 4 após inserir 10, 20 e 30 e remover um elemento:

```
Pilha *pi
  qtd=2   capacidade=4
                    dados ──┐
                            v
             ┌────┬────┬────┬────┐
    (heap)   │ 10 │ 20 │ 30 │    │
             └────┴────┴────┴────┘
              [0]  [1]  [2]  [3]
              base  ^
                   topo (qtd - 1)
```

A posição 2 ainda guarda 30, mas não pertence mais à pilha: a remoção apenas decrementa
`qtd`. A próxima inserção grava em `dados[2]` e sobrescreve esse valor.

## Sequência da aula

O `main.c` reproduz o trace geral dos slides:

| Operação | Retorno | `qtd` | Vetor `[0..3]` | Topo |
|---|---|---|---|---|
| `cria_Pilha(4)` | `pi` | 0 | `__ __ __ __` | nenhum |
| `insere(10)` | 1 | 1 | `10 __ __ __` | 10 |
| `insere(20)` | 1 | 2 | `10 20 __ __` | 20 |
| `insere(30)` | 1 | 3 | `10 20 30 __` | 30 |
| `remove` | 1 | 2 | `10 20 (30) __` | 20 |
| `insere(40)` | 1 | 3 | `10 20 40 __` | 40 |
| `insere(50)` | 1 | 4 | `10 20 40 50` | 50 |
| `insere(60)` | 0 | 4 | `10 20 40 50` | 50 |
| quatro `remove` | 1 | 0 | `(10 20 40 50)` | nenhum |
| `remove` | 0 | 0 | `(10 20 40 50)` | nenhum |

Valores entre parênteses já não pertencem à pilha. A ordem de saída é 30, 50, 40, 20, 10:
cada remoção retira o elemento mais recente presente na pilha.

## Operações e custos

| Função | O que faz | Custo |
|---|---|---|
| `cria_Pilha` | Aloca a estrutura e o vetor de `capacidade` posições; zera `qtd` | O(1) |
| `libera_Pilha` | Libera o vetor e depois a estrutura | O(1) |
| `tamanho_Pilha`, `Pilha_cheia`, `Pilha_vazia` | Consultam apenas `qtd` (e `capacidade`) | O(1) |
| `insere_Pilha` | Grava em `dados[qtd]` e incrementa `qtd` | O(1) |
| `remove_Pilha` | Decrementa `qtd`; nada é apagado nem deslocado | O(1) |
| `consulta_topo_Pilha` | Copia `dados[qtd - 1]` | O(1) |

Nenhuma operação contém laço (Backes, seção 8.4.7). O custo de memória é fixo: o vetor
ocupa `capacidade * sizeof(struct aluno)` bytes desde a criação.

## Erros comuns

- **Consultar `dados[qtd]` em vez de `dados[qtd - 1]`**: devolve um elemento já removido ou,
  com a pilha cheia, lê fora do vetor (o `valgrind` acusa *Invalid read*).
- **Inserir sem testar a pilha cheia**: grava em `dados[capacidade]`, fora do bloco
  alocado (o `valgrind` acusa *Invalid write*).
- **Liberar apenas a estrutura**: o vetor fica sem nenhum ponteiro válido (vazamento).

## Compilação e execução

```bash
make
./teste
```

Saída esperada:

```
cria_Pilha(0) == NULL: 1
vazia=1 cheia=0 tamanho=0
apos empilhar 10 20 30   qtd=3  topo=30 (Carla)
apos 1 remocao           qtd=2  topo=20 (Bruno)
apos empilhar 40 50      qtd=4  topo=50 (Elisa)
vazia=0 cheia=1 tamanho=4
insere em pilha cheia = 0
desempilha 50
desempilha 40
desempilha 20
desempilha 10
remove em pilha vazia = 0
consulta em pilha vazia = 0
```

A função `mostra` do `main.c` usa apenas a interface da pilha: consulta o topo sem removê-lo.

Verificação de memória:

```bash
valgrind --leak-check=full ./teste
```

O código compila sem nenhum aviso com `-Wall -Wextra` e o `valgrind` não acusa vazamento
nem erro de acesso.

## Convenções

- `struct aluno` com matrícula, nome e três notas, como nos slides e no livro.
- Nomes das funções no padrão do livro (`cria_Pilha`, `insere_Pilha`, `remove_Pilha`,
  `consulta_topo_Pilha`, `Pilha_cheia`, `Pilha_vazia`, `tamanho_Pilha`, `libera_Pilha`);
  a única diferença de interface é o parâmetro `capacidade` de `cria_Pilha`.
- `cria_Pilha` devolve `NULL` para capacidade menor ou igual a zero.
- Inserção, remoção e consulta devolvem `1` em caso de sucesso e `0` caso contrário.
- `tamanho_Pilha`, `Pilha_cheia` e `Pilha_vazia` devolvem `-1` quando a pilha é inválida.
- Comentários sem acentuação nos arquivos `.c` e `.h`.
