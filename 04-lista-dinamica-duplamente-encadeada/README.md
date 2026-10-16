# Lista dinâmica duplamente encadeada · Aula 08

Implementação completa da lista dinâmica duplamente encadeada, no mesmo estado em que
aparece nos slides da Aula 08. Referência: BACKES, A. R. *Algoritmos e estruturas de
dados em linguagem C*, capítulo 5, seção 5.7.

## O que muda em relação à lista encadeada simples

Nada na interface. O arquivo `.h` declara os mesmos tipos visíveis e os mesmos
protótipos, e a lista continua sendo representada por um ponteiro para ponteiro
`Lista *li`. A diferença está na `struct elemento`, escondida no `.c`:

> Cada elemento passa a ter três campos: `ant`, `dados` e `prox`. O primeiro elemento
> aponta `ant` para `NULL` e o último aponta `prox` para `NULL`.

Daí decorrem as três regras que governam todo o código desta pasta:

1. **Toda inserção e toda remoção mantêm os dois sentidos.** Além do `prox` de algum
   elemento, cada operação escreve o `ant` do elemento que muda de vizinho. Esquecer
   essa atualização não gera aviso do compilador: o percurso por `prox` continua
   funcionando, e o erro só aparece quando alguma operação lê `ant`.
2. **A religação vem antes do `free`.** Na remoção, `no->ant->prox` e `no->prox->ant`
   são atualizados enquanto `no` ainda é válido; só então o nó é liberado.
3. **O antecessor está no próprio nó.** A remoção específica e a remoção do final usam
   um único ponteiro de percurso, `no`, e chegam ao anterior por `no->ant`. Na lista
   encadeada simples, o laço precisava carregar um segundo ponteiro.

## Custo das operações

Para uma lista com `n` elementos:

| Operação | Duplamente encadeada | Encadeada simples | Por quê |
|---|---|---|---|
| `insere_lista_inicio` | `O(1)` | `O(1)` | só manipula ponteiros do início |
| `insere_lista_final` | `O(n)` | `O(n)` | ambas percorrem até o último |
| `insere_lista_ordenada` | `O(n)` | `O(n)` | o ponto de inserção é procurado nos dois casos |
| `remove_lista_inicio` | `O(1)` | `O(1)` | só manipula ponteiros do início |
| `remove_lista_final` | `O(n)` | `O(n)` | é preciso encontrar o último; o `ant` dispensa apenas o ponteiro auxiliar |
| `remove_lista` | `O(n)` | `O(n)` | envolve a busca pela chave |
| `busca_lista_pos` / `busca_lista_mat` | `O(n)` | `O(n)` | no pior caso visitam todos os nós |
| `tamanho_lista` / `libera_lista` | `O(n)` | `O(n)` | visitam todos os nós |
| `lista_vazia` / `lista_cheia` | `O(1)` | `O(1)` | consulta direta |

As ordens de custo são as mesmas da lista encadeada simples. O campo `ant` custa 8 bytes
a mais por elemento (`sizeof(Elem)` passa de 56 para 64 bytes com a `struct aluno` da
disciplina) e uma atribuição a mais em cada inserção e remoção. O ganho aparece quando o
endereço do nó já é conhecido: removê-lo exige apenas religar `no->ant` e `no->prox`,
sem percorrer a lista para encontrar o antecessor.

## Compilação e execução

```bash
make        # gera o executável ./teste
./teste     # executa o programa de demonstração
make clean  # remove os .o e o executável
```

Sem o `make`:

```bash
gcc -Wall -Wextra -std=c11 -o teste ListaDinEncadDupla.c main.c
```

Verificação de memória:

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
- `tamanho_lista` devolve `0` para lista inválida, e `lista_vazia` devolve `1` para
  lista inválida, como no livro-texto e nos slides.
- Em `insere_lista_ordenada`, o ponteiro `ante` é inicializado com `NULL`. O livro o
  declara sem valor inicial; a inicialização não altera o comportamento e elimina o
  aviso *may be used uninitialized* do `gcc` com otimização.
- Comentários sem acentuação nos arquivos `.c` e `.h`.
