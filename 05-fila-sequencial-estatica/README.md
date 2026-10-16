# Aula 09 · Fila sequencial estática com capacidade definida na criação

Implementação de uma fila (estrutura FIFO: o primeiro a entrar é o primeiro a sair) com
**acesso sequencial** sobre um vetor tratado como **circular**. A inserção acontece sempre
no final e a remoção sempre no início. O elemento armazenado é uma `struct aluno` com
matrícula, nome e três notas.

Referência: BACKES, A. R. *Algoritmos e estruturas de dados em linguagem C*, capítulo 6,
seção 6.4.

## O que muda em relação ao livro

No livro, a `struct fila` contém um vetor `struct aluno dados[MAX]`, com `MAX` fixado em
tempo de compilação. Nesta disciplina, o tamanho é escolhido por quem cria a fila:

```c
Fila *fi = cria_Fila(5);   /* fila com 5 posicoes */
```

Para isso, a `struct fila` guarda um ponteiro e a capacidade:

```c
struct fila {
    int inicio, final, qtd;
    int capacidade;
    struct aluno *dados;   /* vetor alocado com malloc em cria_Fila */
};
```

Depois de criada, a capacidade não muda. A fila continua sendo estática no sentido de que
pode ficar cheia; o que passou a ser dinâmico foi apenas o momento em que o tamanho do
vetor é decidido. Essa mudança traz duas responsabilidades novas, ambas tratadas no código:

1. **Duas alocações na criação.** `cria_Fila` aloca a estrutura e depois o vetor. Se a
   segunda alocação falhar, a estrutura já alocada precisa ser liberada antes de devolver
   `NULL`; do contrário, ela fica inacessível na memória.
2. **Duas liberações na destruição, nesta ordem.** `libera_Fila` libera `fi->dados` e só
   depois `fi`. Liberar `fi` primeiro e então ler `fi->dados` é acesso a memória já
   liberada; liberar apenas `fi` deixa o vetor vazando.

## Arquivos

| Arquivo | Conteúdo |
|---|---|
| `FilaEstatica.h` | `struct aluno`, o tipo opaco `Fila` e os protótipos |
| `FilaEstatica.c` | `struct fila` (campos `inicio`, `final`, `qtd`, `capacidade` e `dados`) e a implementação das funções |
| `main.c` | Demonstração das operações, com a saída esperada abaixo |
| `Makefile` | Compilação separada dos módulos |

## Representação em memória

Fila com capacidade 5 após inserir 10, 20, 30 e 40 e remover dois elementos:

```
Fila *fi
  inicio=2   final=4   qtd=2   capacidade=5
                                       dados ──┐
                                               v
                  ┌────┬────┬────┬────┬────┐
       (heap)     │ 10 │ 20 │ 30 │ 40 │    │
                  └────┴────┴────┴────┴────┘
                   [0]  [1]  [2]  [3]  [4]
                              ^         ^
                           inicio     final
```

As posições 0 e 1 ainda guardam 10 e 20, mas não pertencem mais à fila: a remoção apenas
avança `inicio`. Elas serão reaproveitadas quando `final` der a volta.

## O vetor circular

A inserção e a remoção avançam um índice com o resto da divisão:

```c
fi->final  = (fi->final  + 1) % fi->capacidade;   /* insere_Fila */
fi->inicio = (fi->inicio + 1) % fi->capacidade;   /* remove_Fila */
```

Continuando o exemplo acima e inserindo 50, 60 e 70:

| Operação | Grava em | `inicio` | `final` | `qtd` | Vetor `[0..4]` |
|---|---|---|---|---|---|
| estado inicial | | 2 | 4 | 2 | `10 20 30 40 __` |
| `insere(50)` | `[4]` | 2 | 0 | 3 | `10 20 30 40 50` |
| `insere(60)` | `[0]` | 2 | 1 | 4 | `60 20 30 40 50` |
| `insere(70)` | `[1]` | 2 | 2 | 5 | `60 70 30 40 50` |

Na última linha a fila está cheia e `inicio == final`. Essa mesma igualdade acontece com a
fila vazia (logo após `cria_Fila`, por exemplo). Por isso `Fila_cheia` e `Fila_vazia`
consultam apenas `qtd`, e nunca a comparação entre `inicio` e `final`.

## Operações e custos

| Função | O que faz | Custo |
|---|---|---|
| `cria_Fila` | Aloca a estrutura e o vetor de `capacidade` posições; zera os índices | O(1) |
| `libera_Fila` | Libera o vetor e depois a estrutura | O(1) |
| `tamanho_Fila`, `Fila_cheia`, `Fila_vazia` | Consultam apenas `qtd` (e `capacidade`) | O(1) |
| `insere_Fila` | Grava em `dados[final]` e avança `final` | O(1) |
| `remove_Fila` | Avança `inicio`; nenhum elemento é deslocado | O(1) |
| `consulta_Fila` | Copia `dados[inicio]` | O(1) |

Compare com a lista sequencial estática: lá, `remove_lista_inicio` desloca todos os
elementos restantes e custa O(n). Na fila, os índices `inicio` e `final` e o vetor
circular eliminam esse deslocamento. O custo de memória é fixo: o vetor ocupa
`capacidade * sizeof(struct aluno)` bytes desde a criação, esteja a fila cheia ou vazia.

## Compilação e execução

```bash
make
./teste
```

Saída esperada:

```
cria_Fila(0) == NULL: 1
vazia=1 cheia=0 tamanho=0
apos 4 insercoes         qtd=4: 10 20 30 40
consulta -> 10 (Ana)
apos 2 remocoes          qtd=2: 30 40
volta circular           qtd=5: 30 40 50 60 70
vazia=0 cheia=1 tamanho=5
insere em fila cheia = 0
atende 30
atende 40
atende 50
atende 60
atende 70
remove em fila vazia = 0
consulta em fila vazia = 0
```

A função `imprime` do `main.c` usa apenas a interface da fila: para cada elemento, consulta,
remove e reinsere no final. Depois de `qtd` voltas, a fila retorna ao mesmo estado lógico.

Verificação de memória:

```bash
valgrind --leak-check=full ./teste
```

O código compila sem nenhum aviso com `-Wall -Wextra` e o `valgrind` não acusa vazamento
nem erro de acesso.

## Convenções

- `struct aluno` com matrícula, nome e três notas, como nos slides e no livro.
- Nomes das funções iguais aos do livro (`cria_Fila`, `insere_Fila`, `remove_Fila`,
  `consulta_Fila`, `Fila_cheia`, `Fila_vazia`, `tamanho_Fila`, `libera_Fila`); a única
  diferença de interface é o parâmetro `capacidade` de `cria_Fila`.
- `cria_Fila` devolve `NULL` para capacidade menor ou igual a zero.
- Inserção, remoção e consulta devolvem `1` em caso de sucesso e `0` caso contrário.
- `tamanho_Fila`, `Fila_cheia` e `Fila_vazia` devolvem `-1` quando a fila é inválida.
- Comentários sem acentuação nos arquivos `.c` e `.h`.
