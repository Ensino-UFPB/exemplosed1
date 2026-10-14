# Lista dinâmica encadeada circular — Aula 07

Implementação completa da lista dinâmica encadeada circular, no mesmo estado em que
aparece nos slides da Aula 07. Referência: BACKES, A. R. *Algoritmos e estruturas de
dados em linguagem C*, capítulo 5, terceira parte.

## O que muda em relação à Aula 06

Nada nos tipos. Um elemento continua tendo um campo de dado e um campo `prox`, e a lista
continua sendo representada por um ponteiro para ponteiro `Lista *li`. A diferença está
inteiramente na implementação das funções:

> Em uma lista dinâmica encadeada, o `prox` do último elemento vale `NULL`. Em uma lista
> **circular**, ele guarda o endereço do primeiro.

Daí decorrem as três regras que governam todo o código desta pasta:

1. **Nenhum percurso compara `prox` com `NULL`.** A parada é sempre por comparação com o
   início da lista, `(*li)`. Um `while (no != NULL)` aqui é laço infinito.
2. **Contagens e impressões usam `do-while`.** Em um `while`, a condição `no != (*li)`
   já é falsa na primeira avaliação e o corpo nunca executa.
3. **Toda operação nas extremidades precisa localizar o último elemento**, porque é ele
   que fecha o ciclo. É esse percurso que torna `O(n)` operações que eram `O(1)` na lista
   não circular.

## Custo das operações

Para uma lista com `n` elementos, na representação que guarda o **início** em `(*li)`:

| Operação | Circular | Encadeada simples (Aula 06) | Por quê |
|---|---|---|---|
| `insere_lista_inicio` | `O(n)` | `O(1)` | é preciso achar o último para religá-lo ao novo primeiro |
| `insere_lista_final` | `O(n)` | `O(n)` | ambas percorrem até o último |
| `insere_lista_ordenada` | `O(n)` | `O(n)` | o ponto de inserção é procurado nos dois casos |
| `remove_lista_inicio` | `O(n)` | `O(1)` | é preciso achar o último para fechar o ciclo sem o removido |
| `remove_lista_final` | `O(n)` | `O(n)` | ambas percorrem até o penúltimo |
| `remove_lista` | `O(n)` | `O(n)` | envolve a busca pela chave |
| `busca_lista_pos` / `busca_lista_mat` | `O(n)` | `O(n)` | no pior caso visitam todos os nós |
| `tamanho_lista` | `O(n)` | `O(n)` | uma volta completa |
| `lista_vazia` / `lista_cheia` | `O(1)` | `O(1)` | consulta direta |

Nenhuma operação desta representação é `O(1)`. O fim da aula mostra que armazenar em
`(*li)` o endereço do **último** elemento, em vez do primeiro, reduz a `O(1)` a inserção
nas duas extremidades e a remoção do início, sem alterar nada no armazenamento dos dados.
Essa variante não está implementada aqui de propósito: ela é o desafio opcional da lista
de exercícios da aula.

## Compilação e execução

```bash
make        # gera o executável ./teste
./teste     # executa o programa de demonstração
make clean  # remove os .o e o executável
```

Sem o `make`:

```bash
gcc -Wall -Wextra -std=c11 -o teste ListaDinEncadCirc.c main.c
```

Verificação de memória, que passa a ser praxe a partir das listas encadeadas:

```bash
valgrind --leak-check=full ./teste
```

O código compila sem nenhum aviso com `-Wall -Wextra` e o `valgrind` não acusa vazamento
nem erro de acesso.

## Convenções

- `struct aluno` com matrícula, nome e três notas, como nos slides e no livro.
- Inserções e remoções devolvem `1` em caso de sucesso e `0` caso contrário.
- Buscas copiam o elemento encontrado para o ponteiro recebido e devolvem `1`; devolvem
  `0` quando a busca falha.
- `tamanho_lista` devolve `0` para lista inválida ou vazia, e `lista_vazia` devolve `1`
  para lista inválida, como no livro-texto e nos slides.
- Comentários sem acentuação nos arquivos `.c` e `.h`.
