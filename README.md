
# Laboratório Interativo de Árvores

**Disciplina:** Laboratório de Estruturas de Dados — Regime Especial  
**Aluno:** MATHEUS NOVAIS ROCHA  
**RA:** 202110039  
**Linguagem:** C (padrão C11)  
**Repositório:** https://github.com/Matheusnrocha/laboratorio-arvores-estruturas-dados  
**Vídeo de apresentação:** https://youtu.be/ybJ8TbhL_mc — demonstração de 5 a 8 minutos

## 1. Sobre o projeto

Este projeto apresenta um laboratório interativo de estruturas de dados desenvolvido em linguagem C e executado pelo terminal. A proposta é permitir a construção, a manipulação e a visualização de quatro estruturas independentes: **árvore binária**, **árvore binária de busca (BST)**, **árvore AVL** e **max-heap**.

O programa oferece um menu principal, submenus para cada estrutura e um experimento de comparação entre BST e AVL. Na implementação das árvores são utilizados `structs`, ponteiros, funções recursivas e alocação dinâmica de memória. O heap é armazenado em um vetor.

## 2. Funcionalidades

| Módulo | Operações implementadas |
|---|---|
| Árvore binária | Inserção por pai e lado, carregamento do exemplo do enunciado, percursos em pré-ordem, em ordem e pós-ordem, contagem de nós e folhas, altura, exibição das ligações e limpeza. |
| BST | Inserção ordenada, busca com contagem de nós visitados, remoção de nós com zero, um ou dois filhos, percursos, altura, exibição das ligações, validação da propriedade de ordenação e limpeza. |
| AVL | Inserção balanceada, busca com contagem de visitas, rotações LL, RR, LR e RL, percurso em ordem, altura, fatores de balanceamento, validação e limpeza. |
| Max-heap | Inserção com *sift-up*, consulta ao máximo, extração com *sift-down*, registro de trocas, exibição do vetor e índices, validação e limpeza. |
| Comparação BST × AVL | Inserção dos números de 1 a 15 nas duas estruturas, medição de altura e contagem de nós visitados nas buscas por 1, 8, 15 e 99. |

### Convenções adotadas

- As chaves são números inteiros e não são permitidas duplicatas.
- A altura de uma árvore é medida pelo **número de arestas** do maior caminho da raiz até uma folha: árvore vazia = `-1`, folha = `0`.
- Na BST, a remoção de um nó com dois filhos utiliza o **sucessor em ordem** (menor valor da subárvore direita).
- Na AVL, o fator de balanceamento é `altura(esquerda) - altura(direita)` e deve permanecer entre `-1` e `1` em todos os nós.
- O max-heap é representado por vetor com **capacidade fixa de 128 posições**, indexadas a partir de zero.

## 3. Organização dos arquivos

```text
laboratorio-arvores/
├── src/
│   ├── main.c                 # Menus, entrada do usuário e comparação BST × AVL
│   ├── arvore_binaria.c/.h    # Árvore binária sem ordenação
│   ├── bst.c/.h               # Árvore binária de busca
│   ├── avl.c/.h               # Árvore AVL
│   └── heap.c/.h              # Max-heap
├── testes/
│   ├── teste_estruturas.c     # Testes automatizados
│   └── entrada_demo.txt       # Entradas reproduzíveis para o menu
├── docs/
│   ├── testes.md              # Relatório de testes
│   ├── comparacao.md          # Experimento e análise BST × AVL
│   ├── roteiro_video.md       # Material de apoio à apresentação
│   ├── publicacao_git.md      # Orientações sobre publicação
│   └── evidencias/            # Saídas registradas do terminal
├── scripts/
│   └── verificar.sh           # Verificações em shell compatível
├── README.md
├── USO_IA.md
└── .gitignore
```

## 4. Requisitos e compilação

É necessário ter o **GCC** instalado. O projeto utiliza somente a biblioteca padrão da linguagem C, sem bibliotecas prontas de árvores ou heap.

### Windows — PowerShell no VS Code

O projeto foi compilado e executado no **Windows com GCC 16.2.0 (MSYS2 UCRT64)**.

Abra o terminal PowerShell na pasta raiz do repositório. Se o GCC estiver instalado em `C:\msys64\ucrt64\bin`, mas não for reconhecido no terminal atual, execute:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
gcc --version
```

Essa configuração do `PATH` vale apenas para o terminal atual.

Para compilar e executar:

```powershell
gcc -std=c11 -Wall -Wextra -pedantic (Get-ChildItem .\src\*.c).FullName -o laboratorio.exe
.\laboratorio.exe
```

### Linux, macOS ou Git Bash com GCC

```bash
gcc -std=c11 -Wall -Wextra -pedantic src/*.c -o laboratorio
./laboratorio
```

## 5. Como utilizar o programa

Ao iniciar, o terminal apresenta o menu principal:

```text
=== LABORATORIO INTERATIVO DE ARVORES ===

1 Arvore binaria | 2 BST | 3 AVL | 4 Max-heap | 5 Comparacao | 0 Sair
Opcao:
```

Escolha um módulo e siga as opções do submenu para inserir, consultar, exibir, validar ou limpar a estrutura. A opção `5` do menu principal executa automaticamente o experimento de comparação entre BST e AVL.

## 6. Testes e resultados

Os cenários previstos no enunciado estão descritos em [docs/testes.md](docs/testes.md), com entradas, resultados esperados e obtidos e registros de execução. A análise do experimento está em [docs/comparacao.md](docs/comparacao.md).

Na validação manual realizada no Windows, foram conferidos, entre outros pontos:

- Os percursos do exemplo da árvore binária, com **6 nós, 3 folhas e altura 2**.
- A BST com as chaves `50, 30, 70, 20, 40, 60, 80`, incluindo busca e remoção nos três casos; também foram testadas árvore vazia e chave duplicada.
- As quatro sequências de rotação da AVL (LL, RR, LR e RL), com validação de altura e balanceamento.
- A inserção no max-heap de `50, 30, 40, 10, 20, 35, 60`, a extração sucessiva dos máximos e o tratamento de heap vazio.
- A comparação BST × AVL com os números de 1 a 15, confirmando **altura 14 na BST** e **altura 3 na AVL**.
- A correção da apresentação da quantidade de nós visitados nas buscas por meio de recompilação e repetição dos testes.

### Executar a entrada demonstrativa no Windows

Com o programa já compilado:

```powershell
Get-Content .\testes\entrada_demo.txt | .\laboratorio.exe
```

### Compilar e executar os testes automatizados no Windows

```powershell
gcc -std=c11 -Wall -Wextra -pedantic -I src testes/teste_estruturas.c src/arvore_binaria.c src/bst.c src/avl.c src/heap.c -o teste_estruturas.exe
.\teste_estruturas.exe
```

Em ambiente com shell compatível, também é possível executar:

```bash
sh scripts/verificar.sh
```

**Observação:** os resultados dos testes automatizados e os testes manuais no Windows são apresentados separadamente na documentação; nem todos os casos de limite foram repetidos manualmente.

## 7. Tratamento de erros e limitações

O programa trata entradas inválidas, duplicatas, busca ou remoção de chaves inexistentes, posições ocupadas na árvore binária, estrutura vazia e capacidade do heap. As árvores utilizam memória dinâmica, com liberação de nós nas operações de limpeza e no encerramento.

Não foram desenvolvidos interface gráfica, persistência em arquivos, banco de dados ou remoção na AVL, pois esses recursos não são exigidos pelo enunciado. O max-heap possui capacidade máxima de 128 elementos simultâneos.

## 8. Uso de inteligência artificial

Foi utilizada inteligência artificial como ferramenta de apoio ao planejamento, à **geração de versões iniciais de código**, à revisão de algoritmos, à depuração, aos testes automatizados e à documentação.

A compreensão dos conceitos, a execução de testes manuais no Windows, a análise dos resultados e a identificação de inconsistências durante essas execuções fizeram parte das atividades realizadas pelo aluno. Uma falha observada na contagem de nós visitados durante as buscas foi analisada com apoio da IA; a correção foi incorporada e validada em nova execução pelo aluno.

O registro das contribuições, com datas, arquivos afetados, verificações e commits relacionados, está disponível em [USO_IA.md](USO_IA.md).

## 9. Referências

- Enunciado fornecido pelo professor: *Trabalho Prático de Estruturas de Dados — Laboratório de Estruturas de Dados, Regime Especial*.
- Documentação e materiais de apoio consultados durante o desenvolvimento estão identificados, quando aplicável, nos registros de uso de IA e nos arquivos de documentação do projeto.

## 10. Vídeo de apresentação e entrega

O vídeo demonstra os percursos da árvore binária, a remoção de um nó com dois filhos na BST, uma rotação dupla na AVL, a inserção e a extração no max-heap, os resultados da comparação BST × AVL e uma contribuição da IA ao desenvolvimento.

**Link para assistir:** https://youtu.be/ybJ8TbhL_mc

Para a entrega, o vídeo deve estar acessível pelo link, ter duração entre **5 e 8 minutos**, e o repositório deve permanecer acessível ao professor.
