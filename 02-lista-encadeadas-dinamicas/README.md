# Aula 06 · Lista dinâmica encadeada

Implementação de uma lista com **alocação dinâmica** e **acesso encadeado**: cada elemento
é alocado com `malloc` no momento da inserção, liberado com `free` no momento da remoção e
guarda o endereço do próximo elemento no campo `prox`. O último elemento aponta para `NULL`.
O elemento armazenado é uma `struct aluno` com matrícula, nome e três notas.

Referência: BACKES, A. R. *Algoritmos e estruturas de dados em linguagem C*, capítulo 5.

## Arquivos

| Arquivo | Conteúdo |
|---|---|
| `ListaDinEncad.h` | `struct aluno`, o tipo opaco `Lista` e os protótipos |
| `ListaDinEncad.c` | `struct elemento` (campos `dados` e `prox`) e a implementação das funções |
| `main.c` | Demonstração das operações, com a saída esperada abaixo |
| `Makefile` | Compilação separada dos módulos |

## Representação em memória

```
Lista *li            (variável do usuário; nunca muda)
    │
    v
 ┌────────┐
 │ início │          (bloco de 8 bytes no heap; muda a cada inserção
 └────────┘           ou remoção no início)
    │
    v
 ┌────┬───┐    ┌────┬───┐    ┌────┬───┐
 │ 33 │ ●─┼──> │ 23 │ ●─┼──> │ 16 │ ●─┼──> NULL
 └────┴───┘    └────┴───┘    └────┴───┘
  dados prox
```

Os nós não ocupam posições contíguas: a ordem da lista é dada pelos ponteiros, e não pelos
endereços.

## Por que `Lista*` é um ponteiro para ponteiro

No arquivo `.h`, `Lista` é definido como `struct elemento*`. Assim, `Lista*` equivale a
`struct elemento**`. Inserir ou remover no início muda **o endereço em que a lista começa**;
para que uma função altere esse endereço no chamador, ela precisa receber o endereço do
ponteiro que o guarda. O bloco `início` cumpre esse papel: `li` aponta para ele durante toda
a vida da lista, e `*li` guarda o primeiro nó. O usuário continua declarando apenas
`Lista *li`, exatamente como na lista sequencial estática.

## Operações e custos

| Função | O que faz | Custo |
|---|---|---|
| `cria_lista` | Aloca o bloco do início e o inicializa com `NULL` | O(1) |
| `libera_lista` | Percorre a lista liberando cada nó e, por fim, o início | O(n) |
| `tamanho_lista` | Percorre a lista contando os nós | O(n) |
| `lista_cheia`, `lista_vazia` | Consultam apenas o início | O(1) |
| `insere_lista_inicio` | Liga o novo nó ao antigo primeiro e altera o início | O(1) |
| `insere_lista_final` | Percorre até o último nó e liga o novo nó depois dele | O(n) |
| `insere_lista_ordenada` | Procura a posição com `ant` e `atual` e religa dois ponteiros | O(n) |
| `remove_lista_inicio` | Altera o início para o segundo nó e libera o primeiro | O(1) |
| `remove_lista_final` | Percorre até o último nó, religa o penúltimo e libera | O(n) |
| `remove_lista` | Busca pela matrícula, contorna o nó e o libera | O(n) |
| `busca_lista_pos` | Percorre a lista até a posição pedida | O(n) |
| `busca_lista_mat` | Percorre a lista comparando matrículas | O(n) |

Nenhuma operação desloca elementos. O custo linear vem sempre do **percurso**, e não da
movimentação de dados. Em relação à lista sequencial estática, os custos se invertem: o
início passa a ser barato, e o final e o acesso por posição passam a ser caros.

## Dois erros que compilam sem aviso

**Ordem das atribuições na inserção no início.** Alterar o início antes de ligar o novo nó
faz o nó apontar para si mesmo, e toda a lista antiga fica inacessível (vazamento):

```c
*li = no;            /* errado: o inicio muda primeiro */
no->prox = (*li);    /* *li ja e o proprio no */
```

A ordem correta é `no->prox = (*li);` e só depois `*li = no;`.

**Liberar antes de avançar.** Em `libera_lista`, liberar o nó e depois ler `(*li)->prox`
acessa memória que já foi devolvida ao sistema:

```c
free(*li);
*li = (*li)->prox;   /* errado: le um bloco liberado */
```

A versão correta guarda o nó em `no`, avança o início e só então chama `free(no)`. Nos dois
casos o `valgrind` ajuda a localizar o problema.

## Compilação e execução

```bash
make
./teste
```

Saída esperada:

```
vazia=1 cheia=0 tamanho=0
apos 3 insercoes       tam=3: inicio -> 33 -> 23 -> 16 -> NULL
insere_inicio(12)      tam=4: inicio -> 12 -> 33 -> 23 -> 16 -> NULL
insere_final(12)       tam=4: inicio -> 33 -> 23 -> 16 -> 12 -> NULL
remove_final           tam=3: inicio -> 33 -> 23 -> 16 -> NULL
remove_lista(23)       tam=2: inicio -> 33 -> 16 -> NULL
remove_lista(99)=0
ordenada               tam=2: inicio -> 16 -> 23 -> NULL
insere_ordenada(19)    tam=3: inicio -> 16 -> 19 -> 23 -> NULL
insere 12 e 40         tam=5: inicio -> 12 -> 16 -> 19 -> 23 -> 40 -> NULL
busca_pos(3) -> matricula 19
busca_mat(19) -> Carla
busca_mat(99)=0
```

Para verificar vazamentos e acessos inválidos:

```bash
valgrind --leak-check=full ./teste
```

## Exercícios sugeridos

1. A partir de uma lista vazia, executar `insere_lista_ordenada` com 30, 10 e 20,
   `insere_lista_inicio` com 40, `remove_lista_final` e `insere_lista_ordenada` com 15.
   Desenhar a lista após cada chamada e explicar por que o 15 é inserido no início.
2. Implementar `remove_lista_final` **sem** o ponteiro `ant`, localizando o penúltimo
   elemento pelo teste `no->prox->prox != NULL`. Tratar à parte a lista com um único
   elemento.
3. Implementar `int conta_maiores(Lista* li, int mat)`, que devolve quantos alunos têm
   matrícula maior que `mat`, e determinar o seu custo.
