# Aula 10 · Fila de prioridade sobre vetor ordenado

Implementação de uma fila de prioridade: cada elemento tem um dado extra, a **prioridade**,
que determina a sua posição na fila e quem é o próximo a sair. A remoção e a consulta
acessam sempre o elemento de **maior** prioridade. Com prioridades iguais, sai primeiro
quem foi inserido primeiro. O elemento armazenado é uma `struct paciente`, com nome e
prioridade, como no exemplo do pronto-socorro usado no livro e em sala.

Quanto maior o número, maior a prioridade.

Referência: BACKES, A. R. *Algoritmos e estruturas de dados em linguagem C*, capítulo 7,
seções 7.1 a 7.7. A implementação com heap binária (seção 7.8) fica para a aula de heaps.

## O que muda em relação ao livro

Como na fila sequencial da Aula 09, o vetor não tem tamanho `MAX` fixo. Quem cria a fila
escolhe a capacidade:

```c
FilaPrio *fp = cria_FilaPrio(5);   /* fila com 5 posicoes */
```

```c
struct fila_prioridade {
    int qtd;
    int capacidade;
    struct paciente *dados;   /* vetor alocado com malloc em cria_FilaPrio */
};
```

A criação faz duas alocações, liberando a estrutura se a segunda falhar, e a destruição faz
dois `free`: primeiro o vetor, depois a estrutura.

## Arquivos

| Arquivo | Conteúdo |
|---|---|
| `FilaPrioridade.h` | Tipo opaco `FilaPrio` e os protótipos |
| `FilaPrioridade.c` | `struct paciente`, `struct fila_prioridade` (campos `qtd`, `capacidade` e `dados`) e a implementação das funções |
| `main.c` | Demonstração das operações, com a saída esperada abaixo |
| `Makefile` | Compilação separada dos módulos |

## Representação em memória

O vetor é mantido em ordem **crescente** de prioridade. O paciente de maior prioridade fica
em `dados[qtd - 1]`, que é o início da fila; o de menor prioridade fica em `dados[0]`, que
é o final da fila.

Fila Davi (8), Bia (5), Ana (3), Caio (1) com capacidade 6:

```
FilaPrio *fp
  qtd=4   capacidade=6
                   dados ──┐
                           v
                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
       (heap)     │ Caio │ Ana  │ Bia  │ Davi │      │      │
                  │  1   │  3   │  5   │  8   │      │      │
                  └──────┴──────┴──────┴──────┴──────┴──────┘
                    [0]    [1]    [2]    [3]    [4]    [5]
                     ^                    ^
               final da fila        inicio da fila
```

Com essa ordem, a remoção e a consulta usam a última posição ocupada e não deslocam
ninguém. Se o vetor fosse decrescente, o início ficaria em `dados[0]` e cada remoção
deslocaria todos os demais pacientes, como em `remove_lista_inicio`.

## A inserção

A procura pela posição começa no início da fila (`dados[qtd - 1]`) e anda em direção a
`dados[0]`. Cada paciente com prioridade **maior ou igual** à do novo é copiado uma posição
à direita; o laço para no primeiro de prioridade menor, ou ao passar de `dados[0]`.

```c
i = fp->qtd - 1;
while (i >= 0 && fp->dados[i].prio >= prioridade) {
    fp->dados[i + 1] = fp->dados[i];
    i--;
}
/* o novo paciente ocupa dados[i + 1] */
```

Inserindo Eva (5) na fila acima:

| Passo | `i` | Teste | Efeito | Cópias |
|---|---|---|---|---|
| início | 3 | | | 0 |
| 1 | 3 | `8 >= 5`: sim | Davi copiado para `[4]` | 1 |
| 2 | 2 | `5 >= 5`: sim | Bia copiada para `[3]` | 2 |
| 3 | 1 | `3 >= 5`: não | laço termina | 2 |
| fim | | | Eva gravada em `[2]`, `qtd` = 5 | 2 |

Resultado: `Caio 1 | Ana 3 | Eva 5 | Bia 5 | Davi 8`. Bia e Eva empatam, e Bia, que chegou
antes, continua mais perto do início. É o `>=` que garante essa regra; com `>`, Eva seria
gravada à frente de Bia.

Dois cuidados do código:

1. **Copiar do fim para o começo.** Cada cópia lê uma posição que ainda não foi
   sobrescrita. Percorrer da esquerda para a direita espalha a mesma cópia e perde
   elementos.
2. **Testar `i >= 0` primeiro.** Com `i == -1`, o `&&` encerra a avaliação e
   `dados[-1]`, fora do vetor, nunca é lido.

## Operações e custos

| Função | O que faz | Custo |
|---|---|---|
| `cria_FilaPrio` | Aloca a estrutura e o vetor de `capacidade` posições; zera `qtd` | O(1) |
| `libera_FilaPrio` | Libera o vetor e depois a estrutura | O(1) |
| `tamanho_FilaPrio`, `estaCheia_FilaPrio`, `estaVazia_FilaPrio` | Consultam apenas `qtd` (e `capacidade`) | O(1) |
| `insere_FilaPrio` | Procura a posição e desloca os pacientes de prioridade maior ou igual | O(N) no pior caso, O(1) no melhor |
| `remove_FilaPrio` | Decrementa `qtd` | O(1) |
| `consulta_FilaPrio` | Copia o nome de `dados[qtd - 1]` | O(1) |

O melhor caso da inserção ocorre quando o novo paciente tem prioridade maior que todos (vai
direto para `dados[qtd]`); o pior, quando tem a menor prioridade (todos são copiados).

Comparação entre as implementações citadas no livro (Quadro 7.1):

| Implementação | Inserção | Remoção |
|---|---|---|
| lista dinâmica encadeada | O(N) | O(1) |
| vetor desordenado | O(1) | O(N) |
| vetor ordenado (esta pasta) | O(N) | O(1) |
| heap binária | O(log N) | O(log N) |

## Compilação e execução

```bash
make
./teste
```

Saída esperada:

```
cria_FilaPrio(0) == NULL: 1
vazia=1 cheia=0 tamanho=0
insere Ana (3)             qtd=1  inicio: Ana
insere Bia (5)             qtd=2  inicio: Bia
insere Caio (1)            qtd=3  inicio: Bia
insere Davi (5), empate    qtd=4  inicio: Bia
consulta -> Bia
remove                     qtd=3  inicio: Davi
insere Eva (4)             qtd=4  inicio: Davi
insere Fabio (9)           qtd=5  inicio: Fabio
vazia=0 cheia=1 tamanho=5
insere em fila cheia = 0
atende Fabio
atende Davi
atende Eva
atende Ana
atende Caio
remove em fila vazia = 0
consulta em fila vazia = 0
```

Verificação de memória:

```bash
valgrind --leak-check=full ./teste
```

O código compila sem nenhum aviso com `-Wall -Wextra` e o `valgrind` não acusa vazamento
nem erro de acesso.

## Convenções

- `struct paciente` com nome e prioridade, como no livro; o tipo fica oculto em
  `FilaPrioridade.c` e o usuário informa apenas o nome e a prioridade.
- Nomes das funções iguais aos do livro (`cria_FilaPrio`, `insere_FilaPrio`,
  `remove_FilaPrio`, `consulta_FilaPrio`, `estaCheia_FilaPrio`, `estaVazia_FilaPrio`,
  `tamanho_FilaPrio`, `libera_FilaPrio`); a única diferença de interface é o parâmetro
  `capacidade` de `cria_FilaPrio`.
- O nome do paciente tem no máximo 29 caracteres; a string passada a `consulta_FilaPrio`
  deve ter espaço para 30.
- `cria_FilaPrio` devolve `NULL` para capacidade menor ou igual a zero.
- Inserção, remoção e consulta devolvem `1` em caso de sucesso e `0` caso contrário.
- `tamanho_FilaPrio`, `estaCheia_FilaPrio` e `estaVazia_FilaPrio` devolvem `-1` quando a
  fila é inválida.
- Comentários sem acentuação nos arquivos `.c` e `.h`.
