# Exemplos de Estrutura de Dados I

Códigos de exemplo em C usados nas aulas de **Estrutura de Dados I** do Departamento de
Informática da UFPB (Ciência da Computação, Ciência de Dados e Engenharia da Computação).

Cada pasta corresponde a uma aula e traz a implementação completa da estrutura estudada,
no mesmo estado em que ela aparece nos slides: nomes de funções, ordem dos parâmetros e
convenções de retorno são os mesmos apresentados em sala.

Prof. Daniel Faustino Lacerda de Souza · danielfaustino@ci.ufpb.br

## Conteúdo

| Pasta | Aula | Estrutura | Situação |
|---|---|---|---|
| [`05-lista-sequencial-estatica`](05-lista-sequencial-estatica) | 05 | Lista sequencial estática (array e campo `qtd`) | disponível |
| `06-lista-dinamica-encadeada` | 06 | Lista dinâmica encadeada | em preparação |

As demais estruturas do semestre (pilhas, filas, árvores de busca, árvores balanceadas,
heaps, filas de prioridade e grafos) serão publicadas conforme as aulas forem ministradas.

## Como compilar e executar

Cada pasta é independente e traz o seu próprio `Makefile`:

```bash
cd 05-lista-sequencial-estatica
make        # gera o executável ./teste
./teste     # executa o programa de demonstração
make clean  # remove os .o e o executável
```

Sem o `make`, a compilação manual é direta:

```bash
gcc -Wall -Wextra -std=c11 -o teste ListaSequencial.c main.c
```

O único requisito é um compilador C com suporte a C11 (`gcc` ou `clang`). No Windows,
funcionam o WSL2, o MinGW-w64 e o compilador do MSYS2.

## Organização de cada pasta

```
NN-nome-da-estrutura/
├── Estrutura.h      interface: tipo opaco, constantes e protótipos
├── Estrutura.c      implementação: struct interna e corpo das funções
├── main.c           programa de demonstração com as operações da aula
├── Makefile         compilação separada dos módulos
└── README.md        resumo da estrutura, das operações e dos custos
```

## Convenções adotadas

1. **Tipo opaco.** A `struct` interna é definida apenas no arquivo `.c`. Quem usa a
   biblioteca declara um ponteiro e chama as funções do `.h`, sem acessar os campos
   diretamente.
2. **Compilação limpa.** Todo o código compila com `gcc -Wall -Wextra -std=c11` sem
   nenhum aviso.
3. **Retorno das operações.** Inserção e remoção devolvem `1` em caso de sucesso e `0`
   caso contrário. Funções de consulta devolvem `-1` quando o ponteiro da estrutura é
   `NULL`.
4. **Comentários sem acentuação** nos arquivos `.c` e `.h`, para evitar problemas de
   codificação em editores configurados com outra página de código. Os arquivos
   `README.md` usam acentuação normal.
5. **Nomes em português**, iguais aos dos slides e das listas de exercícios, seguindo a
   bibliografia da disciplina.

## Bibliografia de referência

- BACKES, A. R. *Algoritmos e estruturas de dados em linguagem C*. Rio de Janeiro: LTC, 2023.
- TENENBAUM, A. M.; LANGSAM, Y.; AUGENSTEIN, M. J. *Estruturas de dados usando C*. São Paulo: Makron Books, 1995.
- CORMEN, T. H. et al. *Algoritmos: teoria e prática*. 3. ed. Rio de Janeiro: Elsevier, 2012.

## Uso

Material didático de uso livre para estudo. Ao reutilizar em outra disciplina, a citação
da origem é bem-vinda.
