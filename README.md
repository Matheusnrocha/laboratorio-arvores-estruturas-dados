# Laboratorio Interativo de Arvores

**Disciplina:** Laboratorio de Estruturas de Dados — Regime especial  
**Autor:** [PREENCHER NOME E RA ANTES DE ENTREGAR]  
**Linguagem:** C11, terminal  
**Enunciado:** `Trabalho_Pratico_Estruturas_de_Dados_Regime_Especial.pdf` (material fornecido pelo professor)  
**Video de demonstracao (5 a 8 minutos):** [INSERIR LINK APOS A GRAVACAO]

## Objetivo

Demonstrar quatro estruturas independentes, implementadas com `struct`, ponteiros, recursao e gerenciamento de memoria: arvore binaria (sem ordenacao), BST, AVL e max-heap representado por vetor. O programa apresenta um menu principal, submenus e um experimento comparativo entre BST e AVL.

## Funcionalidades

| Modulo | Operacoes |
|---|---|
| Arvore binaria | Criacao por pai/lado, exemplo obrigatorio, tres percursos, altura, nos, folhas, ligacoes, limpeza |
| BST | Insercao, busca com visitas, remocao de folha/um filho/dois filhos, tres percursos, verificacao de limites ancestrais, limpeza |
| AVL | Insercao, busca com visitas, LL/RR/LR/RL, rastreamento de rotacoes, alturas, fatores, verificacao BST e balanceamento, limpeza |
| Max-heap | Insercao com sift-up, consulta sem remocao, extracao com sift-down, registro de trocas, vetor indexado, validacao, limpeza |
| Comparacao | Insercoes de 1 a 15, buscas 1/8/15/99, alturas e visitas em BST e AVL, estruturas temporarias independentes |

Chaves inteiras negativas, zero e positivas sao aceitas, sem duplicatas. A altura usa **arestas**: arvore vazia = -1; folha = 0. A BST remove nos de dois filhos pelo **sucessor em ordem**. O max-heap possui **128 posicoes** e indices iniciados em zero. A AVL nao possui remocao, como permitido pelo enunciado.

## Arquivos

```text
src/
  main.c                 menus, leitura validada e comparacao
  arvore_binaria.c/.h    arvore binaria sem regra de ordenacao
  bst.c/.h               arvore binaria de busca
  avl.c/.h               arvore AVL
  heap.c/.h              max-heap
scripts/
  verificar.sh           compilacao e verificacoes (Linux/macOS/Git Bash)
testes/
  teste_estruturas.c     assert dos casos obrigatorios e limites
  entrada_demo.txt       sequencia reproduzivel para o menu
docs/
  testes.md              relatorio de testes
  comparacao.md          experimento e respostas tecnicas
  roteiro_video.md       roteiro para demonstracao
  publicacao_git.md      instrucoes para publicacao remota e commits
  evidencias/
    demo-terminal.txt    transcricao real do programa
    verificacao-terminal.txt resultados dos testes
USO_IA.md                contribuicoes de IA e verificacoes
README.md
.gitignore
```

## Compilacao e execucao

### Linux / macOS / Git Bash com GCC

```bash
gcc -std=c11 -Wall -Wextra -pedantic src/*.c -o laboratorio
./laboratorio
```

### Windows com GCC (PowerShell)

```powershell
gcc -std=c11 -Wall -Wextra -pedantic src/*.c -o laboratorio.exe
.\laboratorio.exe
```

> Se o GCC nao estiver instalado, configure um compilador MinGW-w64 ou use um terminal Linux com GCC. O projeto nao depende de bibliotecas externas alem da biblioteca padrao de C.

## Testes reproduziveis

Com GCC e shell compatível:

```bash
sh scripts/verificar.sh
```

Compilacao manual da suite em sistemas sem shell Unix:

```bash
gcc -std=c11 -Wall -Wextra -pedantic -I src testes/teste_estruturas.c src/arvore_binaria.c src/bst.c src/avl.c src/heap.c -o teste_estruturas
./teste_estruturas
```

No PowerShell, substitua a ultima linha por `.\teste_estruturas.exe` e compile com `-o teste_estruturas.exe`.

Para reproduzir a demonstracao completa do terminal (entrada predefinida, executada pelos menus reais):

```bash
./laboratorio < testes/entrada_demo.txt
```

No PowerShell: `Get-Content testes/entrada_demo.txt | .\laboratorio.exe`.

As entradas/saidas esperadas e obtidas constam em [docs/testes.md](docs/testes.md). A comparacao e sua interpretacao constam em [docs/comparacao.md](docs/comparacao.md).

## Casos de erro e limitacoes

- Entradas nao numericas e opcoes invalidas sao rejeitadas sem encerrar o processo.
- Chaves duplicadas sao rejeitadas nos quatro modulos.
- Posicao ocupada, pai inexistente e lado invalido sao rejeitados na arvore binaria.
- Buscas e remocoes de chave inexistente sao informadas.
- Insercao com capacidade cheia e consulta/extracao em heap vazio sao protegidas.
- `malloc` e verificado. Remocoes e limpeza liberam os nos; ao encerrar, as tres arvores sao liberadas.
- Nao ha GUI, persistencia em arquivo, banco de dados ou remocao AVL (dispensados pelo enunciado).
- O max-heap usa capacidade fixa de 128 elementos, o que limita o numero de chaves simultaneas.

## Referencias e IA

- Enunciado do professor: *Trabalho pratico de estruturas de dados — Laboratorio de Estruturas de Dados, Regime especial*, pp. 1–7.
- [USO_IA.md](USO_IA.md): registro da geracao assistida, trechos afetados e resultados dos testes. **O projeto foi implementado com apoio substancial de IA**; a declaracao nao deve ser reduzida a apenas um algoritmo.

## Conferencia de entrega

- [ ] Substituir os campos de autoria/RA e o link do video.
- [ ] Revisar o codigo e reproduzir os testes no proprio computador.
- [ ] Ler [docs/publicacao_git.md](docs/publicacao_git.md), conferir identidade Git, remoto e acesso do professor.
- [ ] Publicar as etapas de desenvolvimento e conferir o requisito de commits/pushes distribuidos.
- [ ] Gravar video de 5 a 8 minutos conforme `docs/roteiro_video.md`.
- [ ] Revisar/atualizar `USO_IA.md` com eventuais alteracoes manuais feitas pelo aluno.
