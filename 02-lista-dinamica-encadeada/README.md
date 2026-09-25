# Aula 05 · Lista sequencial estática

Implementação de uma lista com **alocação estática** e **acesso sequencial**: os elementos
ficam em um array de tamanho fixo `MAX`, e o campo `qtd` indica quantas posições estão
ocupadas. O elemento armazenado é uma `struct aluno` com matrícula, nome e três notas.

Referência: BACKES, A. R. *Algoritmos e estruturas de dados em linguagem C*, capítulo 5.

## Arquivos

| Arquivo | Conteúdo |
|---|---|
| `ListaSequencial.h` | Constante `MAX`, `struct aluno`, o tipo opaco `Lista` e os protótipos |
| `ListaSequencial.c` | `struct lista` (campos `qtd` e `dados`) e a implementação das funções |
| `main.c` | Demonstração das operações, com a saída esperada abaixo |
| `Makefile` | Compilação separada dos módulos |

## Representação em memória

```
Lista *li
   qtd  ┌───┐
        │ 3 │            qtd também indica a próxima posição livre
        └───┘                              │
                                           v
  dados ┌────┬────┬────┬────┬────┬ ... ┬────┐
        │ 33 │ 23 │ 16 │    │    │     │    │
        └────┴────┴────┴────┴────┴ ... ┴────┘
          [0]  [1]  [2]  [3]  [4]      [MAX-1]
```

As posições de `qtd` até `MAX - 1` existem na memória, mas não pertencem à lista.

## Operações e custos

| Função | O que faz | Custo |
|---|---|---|
| `cria_lista` | Aloca a estrutura e zera `qtd` | O(1) |
| `libera_lista` | Libera o bloco alocado | O(1) |
| `tamanho_lista`, `lista_cheia`, `lista_vazia` | Consultam apenas `qtd` | O(1) |
| `insere_lista_inicio` | Desloca todos os elementos e grava na posição 0 | O(n) |
| `insere_lista_final` | Grava em `dados[qtd]` | O(1) |
| `insere_lista_ordenada` | Procura a posição e desloca os elementos seguintes | O(n) |
| `remove_lista_inicio` | Desloca os elementos restantes uma posição para trás | O(n) |
| `remove_lista_final` | Apenas decrementa `qtd` | O(1) |
| `remove_lista` | Busca pela matrícula e desloca os elementos seguintes | O(n) |
| `remove_lista_otimizado` | Copia o último elemento para a posição liberada | O(n) pela busca |
| `busca_lista_pos` | Acesso direto a `dados[pos-1]` | O(1) |
| `busca_lista_mat` | Percorre a lista comparando matrículas | O(n) |

Duas observações que costumam gerar dúvida:

- **`remove_lista_otimizado` não é O(1).** A movimentação é de um único elemento, mas a
  busca pelo elemento a remover, que vem antes dela, continua percorrendo a lista. Além
  disso, a operação **altera a ordem** dos elementos, e por isso não serve para uma lista
  que precisa permanecer ordenada.
- **Remover não apaga o valor da memória.** O elemento deixa de pertencer à lista quando é
  sobrescrito ou quando sua posição passa a ser maior ou igual a `qtd`.

## Sentido do deslocamento

Na **inserção**, a cópia anda do fim para o início:

```c
for (i = li->qtd - 1; i >= 0; i--)
    li->dados[i + 1] = li->dados[i];
```

Na **remoção**, anda do início para o fim:

```c
for (k = 0; k < li->qtd - 1; k++)
    li->dados[k] = li->dados[k + 1];
```

Inverter esses sentidos faz cada iteração sobrescrever o valor que a iteração seguinte
precisaria copiar, replicando um elemento por toda a lista. O código compila sem aviso.

## Compilação e execução

```bash
make
./teste
```

Saída esperada:

```
vazia=1 cheia=0 tamanho=0
apos 3 insercoes       qtd=3: 33 23 16
insere_inicio(12)      qtd=4: 12 33 23 16
remove_inicio          qtd=3: 33 23 16
remove_final           qtd=2: 33 23
insercao ordenada      qtd=5: 12 16 19 23 33
busca_pos(3) -> matricula 19
busca_mat(23) -> Carla
busca_mat(99)=0
remove_lista(16)       qtd=4: 12 19 23 33
remove_otimizado(12)   qtd=3: 33 19 23
remove_lista(99)=0
```

Repare na penúltima linha: após a remoção otimizada de 12, o último elemento (33) ocupou a
posição liberada, e a lista deixou de estar ordenada.

## Exercícios sugeridos

1. Implementar `int lista_para_vetor(Lista* li, int v[], int n)`, que copia as matrículas
   da lista para um vetor do chamador, sem expor a `struct` interna.
2. Implementar `int remove_repetidos(Lista* li)`, mantendo apenas a primeira ocorrência de
   cada matrícula e preservando a ordem. A remoção otimizada pode ser usada aqui?
3. Alterar o critério de `insere_lista_ordenada` para ordem decrescente e verificar quais
   das demais funções precisam mudar.
