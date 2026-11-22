# Registro de utilização de inteligência artificial

**Projeto:** Laboratório Interativo de Árvores — Estruturas de Dados  
**Período:** 20 a 22/11/2026  
**Ferramenta:** ChatGPT (OpenAI) — GPT-6  
**Repositório:** https://github.com/Matheusnrocha/laboratorio-arvores-estruturas-dados

## 1. Como a IA foi utilizada

A inteligência artificial foi utilizada como **ferramenta de apoio ao desenvolvimento**, especialmente para organizar os requisitos do enunciado, produzir versões iniciais de código e teste e revisar comportamentos.


A **compreensão dos conceitos, a execução de testes manuais no Windows, a análise dos resultados obtidos, a identificação de problemas durante essas execuções e a apresentação final** ficaram sob responsabilidade do aluno, com consulta à ferramenta quando necessário. Na correção do contador de visitas, especificamente, o aluno identificou o erro no terminal; a IA explicou a causa e forneceu a alteração sugerida; o aluno aplicou a versão corrigida, recompilou e confirmou o resultado. Os testes automatizados iniciais, por sua vez, também tiveram contribuição da IA.

Nenhuma biblioteca pronta de BST, AVL ou heap foi empregada para substituir a implementação exigida pelo trabalho.

## 2. Registros de uso por finalidade

### IA-01 — Árvore binária

- **Data:** 20/11/2026.
- **Consulta (resumo fiel):** desenvolver trechos iniciais do módulo de árvore binária em C conforme o enunciado, com inserção por pai/lado, percursos, altura, contagem de nós e folhas, exemplo obrigatório e limpeza.
- **Arquivos/funções:** `src/arvore_binaria.c` e `src/arvore_binaria.h`; `ab_inserir`, `ab_carregar_exemplo`, percursos e `ab_limpar`.
- **Aproveitamento:** versão inicial do módulo gerada com apoio da IA e incorporada ao projeto.
- **Conferência:** o aluno executou o exemplo no Windows e confirmou os três percursos, 6 nós, 3 folhas e altura 2. Os demais casos limites constam na suíte de testes.
- **Commit:** `648aabb`.

### IA-02 — BST

- **Data:** 20/11/2026.
- **Consulta (resumo fiel):** implementar BST com inserção, busca com contagem de visitas, remoção nos três casos, percursos e verificação global da propriedade de ordenação.
- **Arquivos/funções:** `src/bst.c` e `src/bst.h`; `bst_inserir`, `bst_buscar`, `bst_remover` e rotina de verificação por limites.
- **Aproveitamento:** versão inicial produzida com apoio da IA; foi adotado o sucessor em ordem na remoção de nós com dois filhos.
- **Conferência:** o aluno inseriu `50, 30, 70, 20, 40, 60, 80`, verificou altura 2 e ordenação, executou buscas por 60 e 99 e removeu 20, 30 e 50. Confirmou percurso final `40, 60, 70, 80` e propriedade BST válida. Também testou estrutura vazia e chave duplicada.
- **Commit:** `7e215d0`.


### IA-03 — Max-heap

- **Data:** 22/11/2026.
- **Consulta (resumo fiel):** implementar heap máximo em vetor, com inserção (`sift-up`), consulta, extração (`sift-down`), registro de trocas, validação e tratamento de capacidade.
- **Arquivos/funções:** `src/heap.c` e `src/heap.h`; `heap_inserir`, `heap_extrair` e `heap_verificar`.
- **Aproveitamento:** versão inicial do módulo gerada com apoio da IA; capacidade definida em 128 posições.
- **Conferência:** o aluno inseriu `50, 30, 40, 10, 20, 35, 60`, confirmou o vetor `60, 30, 50, 10, 20, 35, 40`, extraiu sucessivamente os máximos e verificou o aviso de heap vazio. O limite de capacidade também consta nos testes automatizados.
- **Commit:** `2bdcc96`.



### IA-04 — Testes automatizados e documentação técnica

- **Data:** 22/11/2026.
- **Consulta (resumo fiel):** criar testes reproduzíveis, exemplos de entrada, evidências de execução e relatórios dos resultados exigidos no enunciado.
- **Arquivos:** `testes/teste_estruturas.c`, `testes/entrada_demo.txt`, `scripts/verificar.sh`, `docs/testes.md`, `docs/comparacao.md` e `docs/evidencias/`.
- **Aproveitamento:** estrutura inicial dos testes automatizados e dos relatórios produzida com apoio da IA. O aluno realizou posteriormente uma rodada própria de testes manuais no Windows, conferindo os resultados apresentados pelo terminal.
- **Conferência:** testes automatizados iniciais aprovados no ambiente de desenvolvimento; verificações manuais do aluno detalhadas nos registros IA-01 a IA-05. Esses dois tipos de teste são distintos e não devem ser confundidos.
- **Commit:** `e46b44e`.



### IA-05 — Identificação e correção de falha na busca

- **Data:** 22/11/2026.
- **Origem:** ao buscar o valor 60 na BST, o aluno observou no Windows a mensagem incorreta `Nos visitados: 32767`, embora a chave fosse encontrada.
- **Consulta (resumo fiel):** analisar por que o contador era exibido incorretamente e corrigir a busca no menu da BST, verificando se a AVL tinha o mesmo problema.
- **Arquivos/funções:** `src/main.c`, opções de busca de `menu_bst` e `menu_avl`; `scripts/verificar.sh`.
- **Aproveitamento:** a IA identificou a leitura do contador no mesmo `printf` que executava a busca e sugeriu separar as operações. O aluno incorporou a correção e repetiu a compilação e os testes no Windows.
- **Conferência:** busca por 60 = 3 visitas; busca por 99 = 3 visitas; compilação sem erros ou avisos com `-std=c11 -Wall -Wextra -pedantic`.
- **Commit realizado pelo aluno:** `4830934`.


