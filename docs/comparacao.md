# Comparacao entre BST e AVL

## Procedimento

1. Criar uma BST vazia e uma AVL vazia, independentes dos menus interativos.
2. Inserir os inteiros de **1 a 15** em ordem crescente em ambas.
3. Buscar as chaves 1, 8, 15 e 99 e contar os nos cuja chave foi examinada; ponteiros `NULL` nao contam.
4. Comparar quantidade de nos e altura (numero de arestas). Validar as propriedades de ambas.

## Resultados executados

| Medida | BST | AVL |
|---|---:|---:|
| Nos | 15 | 15 |
| Altura | 14 | 3 |
| Nos visitados — buscar 1 | 1 | 4 |
| Nos visitados — buscar 8 | 8 | 1 |
| Nos visitados — buscar 15 | 15 | 4 |
| Nos visitados — buscar 99 | 15 | 4 |
| Propriedades verificadas | Valida | Validada (BST + equilibrio + alturas) |

**Interpretacao:** a BST recebe numeros em ordem crescente e fica degenerada, como uma lista encadeada para a direita, com altura 14. A AVL realiza rotacoes e mantém altura 3, reduzindo significativamente o pior caminho. **Nem toda busca isolada favorece a AVL:** o valor 1 esta na raiz da BST, visitando um unico no, mas exige quatro visitas na AVL. O valor 8, por outro lado, fica na raiz da AVL, com uma visita.

## Respostas tecnicas solicitadas

### 1. Por que o percurso em ordem e crescente na BST e na AVL?

Em ambas, qualquer valor da subarvore esquerda e menor que a chave do no e qualquer valor da direita e maior. O percurso **esquerda, no, direita** visita os valores em ordem crescente. A arvore binaria comum nao obriga essa ordenacao; no exemplo do professor, o percurso retorna `20, 30, 40, 10, 5, 15`.

### 2. Como remover um no com dois filhos sem perder a propriedade BST?

O algoritmo utiliza o **sucessor em ordem**, isto e, o menor no da subarvore direita. Substitui a chave do no removido pela chave desse sucessor e exclui o sucessor de sua posicao anterior, ligando seu eventual filho direito ao antigo pai. Como o sucessor e o menor valor maior que a chave removida, a ordenacao permanece valida. Na sequencia do enunciado, a raiz 50 passa a 60.

### 3. Quando ocorrem as rotacoes AVL e quais atualizacoes sao necessarias?

Considere `FB = altura(esquerda) - altura(direita)`.

- **LL (30, 20, 10):** peso excessivo na esquerda do filho esquerdo: rotacao simples a direita.
- **RR (10, 20, 30):** peso excessivo na direita do filho direito: rotacao simples a esquerda.
- **LR (30, 10, 20):** excesso na direita do filho esquerdo: rotacao a esquerda nesse filho e depois a direita no no.
- **RL (10, 30, 20):** excesso na esquerda do filho direito: rotacao a direita nesse filho e depois a esquerda no no.

As rotacoes reorganizam ponteiros entre raiz local, filho e subarvore intermediaria sem perder a ordenacao. As **alturas devem ser atualizadas de baixo para cima**: primeiro o antigo no desbalanceado, depois a nova raiz da subarvore. A funcao de insercao devolve a nova raiz local ao pai, incluindo quando muda a raiz global.

### 4. Por que extracoes consecutivas do max-heap retornam valores decrescentes?

O maior valor esta sempre no indice zero; ao extraí-lo, o ultimo elemento passa para a raiz e desce via `sift-down` ate recuperar a propriedade pai maior ou igual a filhos. A proxima extracao novamente retorna o maior dos elementos restantes. Assim, os **retornos** formam uma sequencia decrescente, apesar de o **vetor interno** nao estar totalmente ordenado.

## Evidencia

Reproduzir `./laboratorio < testes/entrada_demo.txt` e procurar a secao `COMPARACAO COM INSERCOES 1..15` em [evidencias/demo-terminal.txt](evidencias/demo-terminal.txt).
