# Relatorio de testes — 20/11/2026

**Ambiente de execucao:** Debian Linux, GCC 14.2.0, C11.  
**Compilacao utilizada:** `gcc -std=c11 -Wall -Wextra -pedantic -Werror src/*.c -o laboratorio`.  
**Teste principal:** `sh scripts/verificar.sh`.  
**Evidencias reais:** [saida da suite](evidencias/verificacao-terminal.txt) e [transcricao do menu](evidencias/demo-terminal.txt).

**Status:** todos os testes descritos abaixo passaram na execucao registrada; no dia da entrega, executar novamente no computador do aluno.

| Entrada | Operacao | Resultado esperado | Obtido na execucao | Situacao |
|---|---|---|---|---|
| Exemplo 10/30/5/20/40/15 | Binaria, pre-ordem | 10, 30, 20, 40, 5, 15 | Igual ao esperado | PASSOU |
| Mesmo exemplo | Binaria, em ordem | 20, 30, 40, 10, 5, 15 | Igual ao esperado | PASSOU |
| Mesmo exemplo | Binaria, pos-ordem | 20, 40, 30, 15, 5, 10 | Igual ao esperado | PASSOU |
| Mesmo exemplo | Altura, nos e folhas | 2, 6, 3 | 2, 6, 3 | PASSOU |
| Inserir 77 como filho esquerdo de 30 | Binaria, posicao ocupada | Rejeitar e preservar 20 | Rejeitou; filho 20 preservado | PASSOU |
| Pai 1234, lado `?`, chave 5 repetida | Binaria, entradas invalidas | Rejeitar sem alteracao | 3 rejeicoes corretas | PASSOU |
| BST: 50,30,70,20,40,60,80 | Percurso em ordem e altura | 20,30,40,50,60,70,80; altura 2 | Igual; altura 2 | PASSOU |
| Buscar 60 / 99 | BST, contagem de visitas | 3 / 3 (99 ausente) | 3 / 3, com ausencia informada | PASSOU |
| Remover 20, 30, 50 | BST: folha, um filho, dois filhos | 40,60,70,80; BST valida | Igual; raiz final 60 | PASSOU |
| Remover chave 200; raiz minima/maxima | BST, extremos | Ausencia e remocoes corretas | Conforme esperado | PASSOU |
| 30,20,10 | AVL, caso LL | Raiz 20, 10/30, altura 1, FB 0 | Igual; rotacao LL | PASSOU |
| 10,20,30 | AVL, caso RR | Raiz 20, 10/30, altura 1, FB 0 | Igual; rotacao RR | PASSOU |
| 30,10,20 | AVL, caso LR | Raiz 20, 10/30, altura 1, FB 0 | Igual; rotacao LR | PASSOU |
| 10,30,20 | AVL, caso RL | Raiz 20, 10/30, altura 1, FB 0 | Igual; rotacao RL | PASSOU |
| Todos os casos AVL | Percurso + verificacao | 10,20,30; BST, FB e alturas validas | Igual e validado apos insercao | PASSOU |
| Heap: 50,30,40,10,20,35,60 | Insercao sift-up | 60,30,50,10,20,35,40 | Vetor identico | PASSOU |
| Heap acima | Consultar maximo | 60, sem remover | 60, tamanho 7 | PASSOU |
| Heap acima | Extrair uma vez | Retorno 60; vetor 50,30,40,10,20,35 | Retorno e vetor corretos | PASSOU |
| Extrair ate ficar vazio | Heap, sift-down | 60,50,40,35,30,20,10 | Sequencia correta | PASSOU |
| Heap vazio | Consultar/extrair | Informar vazio, sem acesso invalido | `HEAP_VAZIO` | PASSOU |
| Heap com 128 elementos | Exceder capacidade | Rejeitar 129.o elemento | `HEAP_CHEIO` | PASSOU |
| Limpar e inserir novamente | Todos os modulos | Estruturas reutilizaveis | Reutilizacao validada | PASSOU |
| Inserir chave existente | Todos os modulos | Rejeitar duplicata | Rejeitada nos quatro | PASSOU |
| Menu: `abc`, `999`, `0` | Entrada nao numerica e opcao invalida | Recuperar e encerrar com limpeza | Mensagens e encerramento correto | PASSOU |
| Inserir 1 a 15; buscar 1/8/15/99 | Experimento BST vs AVL | BST: altura14/1,8,15,15; AVL equilibrada | AVL: altura3/4,1,4,4; validas | PASSOU |

## Trechos literais capturados do terminal

```text
Pre-ordem: 10, 30, 20, 40, 5, 15
Em ordem:  20, 30, 40, 10, 5, 15
Pos-ordem: 20, 40, 30, 15, 5, 10
Nos: 6 | Folhas: 3 | Altura: 2

Em ordem:  40, 60, 70, 80
Nos: 4 | Altura: 2 | Propriedade BST: VALIDA

Rotacao LR: esquerda no filho e direita no no (1 vez(es)).
Rotacao RL: direita no filho e esquerda no no (1 vez(es)).

Valores: 60, 30, 50, 10, 20, 35, 40
Maximo extraido: 60. Propriedade heap: VALIDA
Valores: 50, 30, 40, 10, 20, 35
```

Os trechos acima foram extraidos de `docs/evidencias/demo-terminal.txt`. A suite em `testes/teste_estruturas.c` verifica os quatro casos AVL, os tres tipos de remocao BST, vetores do heap, limites, duplicatas e experimento. Os outputs completos nao foram abreviados nos arquivos de evidencias.

## Verificacao de memoria com sanitizadores

A suite tambem foi compilada com `-g -fsanitize=address,undefined -fno-omit-frame-pointer` e executada com `ASAN_OPTIONS=detect_leaks=1`. O processo terminou com codigo 0, apresentou **cinco grupos de testes aprovados** e nao relatou erros do AddressSanitizer, do UndefinedBehaviorSanitizer ou vazamentos detectados. Saida real em [evidencias/sanitizer-terminal.txt](evidencias/sanitizer-terminal.txt). Esse teste nao assegura ausencia de todo possivel defeito; cobre os caminhos executados pela suite.
