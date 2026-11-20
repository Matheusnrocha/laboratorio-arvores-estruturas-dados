# Registro de utilizacao de inteligencia artificial

**Data de inicio:** 20/11/2026  
**Ferramenta:** ChatGPT — OpenAI  
**Modelo informado:** GPT-6  
**Pedido original, em resumo fiel:** analisar o esforco de um trabalho pratico de Estruturas de Dados, implementar o projeto em C com todos os modulos obrigatorios e preparar os materiais para entrega ate o dia seguinte, incluindo testes, documentacao e roteiro para o video. O enunciado em PDF foi fornecido na conversa.

## Transparencia e autoria

A implementacao inicial **dos quatro modulos, dos menus, da suite de testes e da documentacao foi produzida com apoio substancial de IA nesta sessao**. Os itens abaixo agrupam o trabalho por modulo/finalidade, sem alegar que apenas esses pontos receberam ajuda. Os comentarios no codigo remetem aos identificadores deste documento. Nao foram utilizadas bibliotecas prontas que implementem as estruturas.

**Modificacoes do aluno:** nenhuma revisao manual foi informada ate a criacao inicial deste registro. O aluno deve registrar aqui todas as modificacoes que fizer na fase de revisao e validacao, incluindo a data e o commit pertinente. Os testes executados neste ambiente nao substituem a conferencia no computador do aluno.

## Registros (consultas agrupadas por finalidade)

### IA-01 — Arvore binaria

- **Data/ferramenta/modelo:** 20/11/2026, ChatGPT (GPT-6).
- **Finalidade e pedido:** implementar uma arvore binaria nao ordenada em C, incluindo insercao por pai/lado, rejeicoes, exemplo do PDF, percursos, altura, contagem e limpeza, como parte do pedido de desenvolvimento integral do projeto.
- **Trechos afetados:** `src/arvore_binaria.c` e `.h`, especialmente `ab_inserir`, `ab_carregar_exemplo`, percursos e `ab_limpar`.
- **Aproveitamento:** implementacao proposta pela IA incorporada integralmente na versao inicial; nenhuma alteracao manual do aluno informada.
- **Verificacao:** exemplo do enunciado (3 percursos, 6 nos, 3 folhas, altura 2), insercao em posicao ocupada, duplicatas, pai inexistente, lado invalido, arvore vazia e limpeza — **PASSOU**.
- **Commit de implementacao:** `648aabb`.

### IA-02 — BST

- **Data/ferramenta/modelo:** 20/11/2026, ChatGPT (GPT-6).
- **Finalidade e pedido:** implementar BST com insercao, busca e contagem de visitas, remocao nos tres casos, percursos e validacao da regra de ordenacao em toda a arvore.
- **Trechos afetados:** `src/bst.c` e `.h`, especialmente `bst_inserir`, `bst_buscar`, `bst_remover`, `verificar_limites`.
- **Aproveitamento:** implementacao proposta pela IA incorporada integralmente na versao inicial; opcao adotada para dois filhos: **sucessor em ordem**.
- **Verificacao:** sequencia 50,30,70,20,40,60,80; buscas por 60 e 99 (3 visitas); exclusoes 20,30,50; raiz final 60; limites INT_MIN e INT_MAX — **PASSOU**.
- **Commit:** `7e215d0`.

### IA-03 — AVL

- **Data/ferramenta/modelo:** 20/11/2026, ChatGPT (GPT-6).
- **Finalidade e pedido:** implementar AVL com insercao balanceada, busca, atualizacao de alturas, fatores, rotacoes simples/duplas e verificacao completa apos cada insercao.
- **Trechos afetados:** `src/avl.c` e `.h`, em especial `rotacao_direita`, `rotacao_esquerda`, `inserir_rec`, `verificar_rec`.
- **Aproveitamento:** implementacao proposta pela IA incorporada integralmente na versao inicial, sem remocao na AVL porque o professor dispensa essa operacao.
- **Verificacao:** LL (30,20,10), RR (10,20,30), LR (30,10,20), RL (10,30,20); raiz 20, folhas 10/30, altura 1; validacao BST, FB e alturas apos cada insercao; 1..15 — **PASSOU**.
- **Commit:** `3919bd8`.

### IA-04 — Max-heap

- **Data/ferramenta/modelo:** 20/11/2026, ChatGPT (GPT-6).
- **Finalidade e pedido:** implementar max-heap em vetor de indices iniciados em zero, consulta, insercao com sift-up, extracao com sift-down, trocas registradas, capacidade e verificacao.
- **Trechos afetados:** `src/heap.c` e `.h`, especialmente `heap_inserir`, `heap_extrair`, `heap_verificar`.
- **Aproveitamento:** implementacao proposta pela IA incorporada integralmente na versao inicial; capacidade escolhida: 128.
- **Verificacao:** vetor apos 50,30,40,10,20,35,60 = `60,30,50,10,20,35,40`; extraindo 60, vetor `50,30,40,10,20,35`; esvaziamento e tentativa de extrapolar capacidade — **PASSOU**.
- **Commit:** `2bdcc96`.

### IA-05 — Menus, tratamento de entrada e comparacao

- **Data/ferramenta/modelo:** 20/11/2026, ChatGPT (GPT-6).
- **Finalidade e pedido:** integrar as estruturas independentes em um unico executavel por submenus, permitir entradas interativas, rejeitar opcoes invalidas, liberar memoria e implementar experimento BST versus AVL.
- **Trechos afetados:** `src/main.c`, incluindo `ler_inteiro`, `menu_binaria`, `menu_bst`, `menu_avl`, `menu_heap`, `experimento` e `main`.
- **Aproveitamento:** codigo de integracao gerado com IA e incorporado. Foi usada leitura com `fgets`/`strtol` para recuperar entradas invalidas sem deixar dados pendentes no buffer.
- **Verificacao:** compilacao GCC C11 sem warnings, menu `abc` e opcao 999 com recuperacao, comparacao BST/AVL com 15 valores, alturas 14/3 e visitas respectivas — **PASSOU**.
- **Commits:** `e1c8726` (estrutura inicial) e `b5a8425` (integracao).

### IA-06 — Casos de teste automatizados e evidencias

- **Data/ferramenta/modelo:** 20/11/2026, ChatGPT (GPT-6).
- **Finalidade e pedido:** verificar todos os casos obrigatorios do PDF e gerar uma reproducao real das operacoes, com saídas observadas em terminal.
- **Trechos afetados:** `testes/teste_estruturas.c`, `scripts/verificar.sh`, `testes/entrada_demo.txt`, `docs/evidencias/demo-terminal.txt` e `docs/evidencias/verificacao-terminal.txt`.
- **Aproveitamento:** implementacao de testes e comandos proposta e executada pela IA. Nenhum resultado foi preenchido como hipotetico: os arquivos de evidencias foram gerados por execucoes reais.
- **Verificacao:** cinco grupos de testes com `assert` passaram e compilacao com `-Werror` ocorreu sem avisos. Tambem foi verificado fluxo real do menu.
- **Commit:** `e46b44e` (testes e documentacao).

### IA-07 — Documentacao, comparacao e roteiro do video

- **Data/ferramenta/modelo:** 20/11/2026, ChatGPT (GPT-6).
- **Finalidade e pedido:** estruturar os arquivos exigidos pelo enunciado, interpretar a comparacao de altura e visitas, registrar IA de forma rastreavel e preparar a gravacao do dia seguinte.
- **Trechos afetados:** `README.md`, `USO_IA.md`, `docs/testes.md`, `docs/comparacao.md`, `docs/roteiro_video.md`.
- **Aproveitamento:** textos iniciais produzidos com IA. Os campos de autoria, RA e link de video devem ser completados pelo aluno e a explicacao deve ser revisada por ele.
- **Verificacao:** conferencia de criterios das pp. 5–7 do enunciado, resultados tecnicos cotejados com a execucao. Antes de entregar, revisar toda a documentacao e os links.
- **Commit:** `e46b44e` (documentacao inicial).

## Como atualizar este documento durante a revisao

Ao corrigir um codigo, incluir em seu registro correspondente: **o que foi alterado**, **por quem**, **a justificativa**, **qual teste foi repetido** e **hash do commit**. Novas consultas de IA devem ser registradas aqui, incluindo ajuda conceitual ou na redacao, mesmo que nenhum codigo tenha sido copiado.

## Conclusao da verificacao inicial

- Implementacoes independentes: 4/4.
- Conjuntos de verificacoes automatizadas: 5/5 aprovados.
- Entradas do experimento: 1 a 15.
- Resultados: BST altura 14; AVL altura 3; ambas validas.
- Partes **pendentes de acao humana**: revisar/explicar os algoritmos, preencher autoria/RA, publicar no GitHub com acesso adequado, comprovar os envios distribuidos do historico e gravar/publicar video.
