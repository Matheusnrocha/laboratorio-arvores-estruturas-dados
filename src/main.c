/* Integracao de menus e experimento com apoio de IA: ver IA-05 em USO_IA.md. */
#include "arvore_binaria.h"
#include "bst.h"
#include "avl.h"
#include "heap.h"
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* Leitura de menus e inteiros sem scanf: recupera entradas invalidas. Ver IA-05. */
static int ler_inteiro(const char *mensagem, int *valor) {
    char linha[128];
    for (;;) {
        printf("%s", mensagem);
        fflush(stdout);
        if (fgets(linha, sizeof(linha), stdin) == NULL) return 0;
        size_t i = 0;
        while (linha[i] != '\0' && linha[i] != '\n') ++i;
        if (linha[i] == '\0' && i == sizeof(linha) - 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            puts("Entrada muito longa. Tente novamente.");
            continue;
        }
        char *fim;
        errno = 0;
        long numero = strtol(linha, &fim, 10);
        while (isspace((unsigned char)*fim)) ++fim;
        if (fim == linha || *fim != '\0' || errno == ERANGE || numero < INT_MIN || numero > INT_MAX) {
            puts("Entrada invalida. Digite um numero inteiro.");
            continue;
        }
        *valor = (int)numero;
        return 1;
    }
}
static int ler_lado(char *lado) {
    char linha[64];
    printf("Lado (E=esquerdo, D=direito): ");
    fflush(stdout);
    if (fgets(linha, sizeof(linha), stdin) == NULL) return 0;
    size_t i = 0;
    while (isspace((unsigned char)linha[i])) ++i;
    *lado = linha[i];
    if (linha[i] != '\0') ++i;
    while (isspace((unsigned char)linha[i])) ++i;
    if (linha[i] != '\0') *lado = '?';
    return 1;
}
static void mostrar_binaria(const NoBinario *raiz) {
    if (!raiz) puts("Arvore vazia (raiz NULL).");
    else {
        printf("Raiz: %d\n", raiz->chave);
        puts("No          Esquerdo    Direito");
        ab_ligacoes(raiz, stdout);
    }
    printf("Pre-ordem: "); ab_pre_ordem(raiz, stdout); puts("");
    printf("Em ordem:  "); ab_em_ordem(raiz, stdout); puts("");
    printf("Pos-ordem: "); ab_pos_ordem(raiz, stdout); puts("");
    printf("Nos: %d | Folhas: %d | Altura: %d\n", ab_contar_nos(raiz), ab_contar_folhas(raiz), ab_altura(raiz));
}
static void menu_binaria(NoBinario **raiz) {
    int op, chave, pai;
    char lado;
    for (;;) {
        puts("\n--- ARVORE BINARIA ---\n1 Inserir | 2 Carregar exemplo | 3 Exibir | 4 Limpar | 0 Voltar");
        if (!ler_inteiro("Opcao: ", &op) || op == 0) return;
        switch (op) {
            case 1: {
                if (!ler_inteiro("Nova chave: ", &chave)) return;
                pai = 0; lado = 'E';
                if (*raiz != NULL && (!ler_inteiro("Chave do pai: ", &pai) || !ler_lado(&lado))) return;
                AbResultado r = ab_inserir(raiz, chave, pai, lado);
                if (r == AB_OK) puts("Insercao realizada.");
                else if (r == AB_DUPLICADA) puts("Rejeitada: chave duplicada.");
                else if (r == AB_PAI_AUSENTE) puts("Rejeitada: pai inexistente.");
                else if (r == AB_LADO_INVALIDO) puts("Rejeitada: lado invalido.");
                else if (r == AB_POSICAO_OCUPADA) puts("Rejeitada: posicao ocupada (subarvore preservada).");
                else puts("Erro: memoria insuficiente.");
                break;
            }
            case 2: {
                AbResultado r = ab_carregar_exemplo(raiz);
                if (r == AB_OK) puts("Exemplo carregado.");
                else if (r == AB_NAO_VAZIA) puts("Limpe a arvore antes de carregar o exemplo.");
                else puts("Nao foi possivel carregar o exemplo.");
                break;
            }
            case 3: mostrar_binaria(*raiz); break;
            case 4: ab_limpar(raiz); puts("Arvore limpa. Raiz = NULL."); break;
            default: puts("Opcao invalida."); break;
        }
    }
}
static void mostrar_bst(const NoBST *raiz) {
    if (!raiz) puts("BST vazia (raiz NULL).");
    else {
        printf("Raiz: %d\n", raiz->chave);
        puts("No          Esquerdo    Direito");
        bst_ligacoes(raiz, stdout);
    }
    printf("Pre-ordem: "); bst_pre_ordem(raiz, stdout); puts("");
    printf("Em ordem:  "); bst_em_ordem(raiz, stdout); puts("");
    printf("Pos-ordem: "); bst_pos_ordem(raiz, stdout); puts("");
    printf("Nos: %d | Altura: %d | Propriedade BST: %s\n",
           bst_contar_nos(raiz), bst_altura(raiz), bst_verificar(raiz) ? "VALIDA" : "INVALIDA");
}
static void menu_bst(NoBST **raiz) {
    int op, chave, visitas;
    for (;;) {
        puts("\n--- BST ---\n1 Inserir | 2 Buscar | 3 Remover | 4 Exibir | 5 Verificar | 6 Limpar | 0 Voltar");
        if (!ler_inteiro("Opcao: ", &op) || op == 0) return;
        switch (op) {
            case 1: {
                if (!ler_inteiro("Nova chave: ", &chave)) return;
                BstResultado r = bst_inserir(raiz, chave);
                puts(r == BST_OK ? "Insercao realizada." : r == BST_DUPLICADA ? "Rejeitada: chave duplicada." : "Erro: memoria insuficiente.");
                break;
            }
            case 2: {
                if (!ler_inteiro("Buscar chave: ", &chave)) return;
                /* Busca concluida antes de ler o contador. Correcao: ver IA-08. */
                visitas = 0;
                const NoBST *resultado = bst_buscar(*raiz, chave, &visitas);
                printf("%s. Nos visitados: %d\n",
                       resultado != NULL ? "Encontrada" : "Nao encontrada", visitas);
                break;
            }
            case 3: {
                if (!ler_inteiro("Remover chave: ", &chave)) return;
                BstResultado r = bst_remover(raiz, chave);
                puts(r == BST_OK ? "Removida (sucessor em ordem quando dois filhos)." : "Chave inexistente; nenhuma alteracao.");
                break;
            }
            case 4: mostrar_bst(*raiz); break;
            case 5: printf("Propriedade BST global: %s\n", bst_verificar(*raiz) ? "VALIDA" : "INVALIDA"); break;
            case 6: bst_limpar(raiz); puts("BST limpa. Raiz = NULL."); break;
            default: puts("Opcao invalida."); break;
        }
    }
}
static void mostrar_avl(const NoAVL *raiz) {
    if (!raiz) puts("AVL vazia (raiz NULL).");
    else {
        printf("Raiz: %d\n", raiz->chave);
        puts("No        Esquerdo  Direito   Altura  FB");
        avl_ligacoes(raiz, stdout);
    }
    printf("Em ordem: "); avl_em_ordem(raiz, stdout); puts("");
    printf("Nos: %d | Altura: %d | BST + balanceamento + alturas: %s\n",
           avl_contar_nos(raiz), avl_altura(raiz), avl_verificar(raiz) ? "VALIDOS" : "INVALIDOS");
}
static void mostrar_rotacoes(const AvlRotacoes *r) {
    if (r->ll) printf("Rotacao LL: direita (%d vez(es)).\n", r->ll);
    if (r->rr) printf("Rotacao RR: esquerda (%d vez(es)).\n", r->rr);
    if (r->lr) printf("Rotacao LR: esquerda no filho e direita no no (%d vez(es)).\n", r->lr);
    if (r->rl) printf("Rotacao RL: direita no filho e esquerda no no (%d vez(es)).\n", r->rl);
    if (!r->ll && !r->rr && !r->lr && !r->rl) puts("Rotacoes: nenhuma nesta insercao.");
}
static void menu_avl(NoAVL **raiz) {
    int op, chave, visitas;
    for (;;) {
        puts("\n--- AVL ---\n1 Inserir | 2 Buscar | 3 Exibir | 4 Verificar | 5 Limpar | 0 Voltar");
        if (!ler_inteiro("Opcao: ", &op) || op == 0) return;
        switch (op) {
            case 1: {
                if (!ler_inteiro("Nova chave: ", &chave)) return;
                AvlRotacoes rotacoes;
                AvlResultado r = avl_inserir(raiz, chave, &rotacoes);
                if (r == AVL_OK) {
                    puts("Insercao realizada.");
                    mostrar_rotacoes(&rotacoes);
                    printf("Validacao apos insercao: %s\n", avl_verificar(*raiz) ? "OK" : "FALHA");
                } else puts(r == AVL_DUPLICADA ? "Rejeitada: chave duplicada." : "Erro: memoria insuficiente.");
                break;
            }
            case 2: {
                if (!ler_inteiro("Buscar chave: ", &chave)) return;
                /* Busca concluida antes de ler o contador. Correcao: ver IA-08. */
                visitas = 0;
                const NoAVL *resultado = avl_buscar(*raiz, chave, &visitas);
                printf("%s. Nos visitados: %d\n",
                       resultado != NULL ? "Encontrada" : "Nao encontrada", visitas);
                break;
            }
            case 3: mostrar_avl(*raiz); break;
            case 4: printf("BST + balanceamento + alturas: %s\n", avl_verificar(*raiz) ? "VALIDOS" : "INVALIDOS"); break;
            case 5: avl_limpar(raiz); puts("AVL limpa. Raiz = NULL."); break;
            default: puts("Opcao invalida."); break;
        }
    }
}
static void menu_heap(MaxHeap *heap) {
    int op, chave;
    for (;;) {
        puts("\n--- MAX-HEAP ---\n1 Inserir | 2 Consultar maximo | 3 Extrair maximo | 4 Exibir | 5 Verificar | 6 Limpar | 0 Voltar");
        if (!ler_inteiro("Opcao: ", &op) || op == 0) return;
        switch (op) {
            case 1: {
                if (!ler_inteiro("Nova chave: ", &chave)) return;
                HeapResultado r = heap_inserir(heap, chave, stdout);
                if (r == HEAP_OK) printf("Inserido. Propriedade heap: %s\n", heap_verificar(heap) ? "VALIDA" : "INVALIDA");
                else puts(r == HEAP_DUPLICADA ? "Rejeitada: chave duplicada." : "Rejeitada: capacidade atingida.");
                break;
            }
            case 2:
                if (heap_consultar(heap, &chave) == HEAP_OK) printf("Maximo: %d\n", chave);
                else puts("Heap vazio.");
                break;
            case 3:
                if (heap_extrair(heap, &chave, stdout) == HEAP_OK)
                    printf("Maximo extraido: %d. Propriedade heap: %s\n", chave, heap_verificar(heap) ? "VALIDA" : "INVALIDA");
                else puts("Heap vazio: extracao indisponivel.");
                break;
            case 4: heap_exibir(heap, stdout); break;
            case 5: printf("Propriedade heap: %s\n", heap_verificar(heap) ? "VALIDA" : "INVALIDA"); break;
            case 6: heap_inicializar(heap); puts("Heap limpo (tamanho = 0)."); break;
            default: puts("Opcao invalida."); break;
        }
    }
}
/* Experimento reproduzivel, sem modificar as estruturas interativas. Ver IA-05. */
static void experimento(void) {
    NoBST *b = NULL;
    NoAVL *a = NULL;
    const int chaves[] = {1, 8, 15, 99};
    int visitas_b[4], visitas_a[4];
    for (int i = 1; i <= 15; ++i) {
        AvlRotacoes rotacoes;
        if (bst_inserir(&b, i) != BST_OK || avl_inserir(&a, i, &rotacoes) != AVL_OK) {
            puts("Falha de memoria no experimento.");
            bst_limpar(&b); avl_limpar(&a);
            return;
        }
    }
    for (int i = 0; i < 4; ++i) {
        bst_buscar(b, chaves[i], &visitas_b[i]);
        avl_buscar(a, chaves[i], &visitas_a[i]);
    }
    puts("\n--- COMPARACAO COM INSERCOES 1..15 ---");
    puts("Medida              BST    AVL");
    printf("Quantidade nos       %-6d %d\n", bst_contar_nos(b), avl_contar_nos(a));
    printf("Altura               %-6d %d\n", bst_altura(b), avl_altura(a));
    for (int i = 0; i < 4; ++i)
        printf("Busca %-3d            %-6d %d\n", chaves[i], visitas_b[i], visitas_a[i]);
    printf("BST valida: %s | AVL valida: %s\n", bst_verificar(b) ? "SIM" : "NAO", avl_verificar(a) ? "SIM" : "NAO");
    puts("A BST ordenada pela insercao 1..15 torna-se uma cadeia.");
    puts("A AVL rebalanceia e diminui a altura; buscas pontuais podem favorecer a BST.");
    bst_limpar(&b);
    avl_limpar(&a);
}
int main(void) {
    NoBinario *arvore_binaria = NULL;
    NoBST *bst = NULL;
    NoAVL *avl = NULL;
    MaxHeap heap;
    heap_inicializar(&heap);
    int opcao;
    puts("=== LABORATORIO INTERATIVO DE ARVORES ===");
    for (;;) {
        puts("\n1 Arvore binaria | 2 BST | 3 AVL | 4 Max-heap | 5 Comparacao | 0 Sair");
        if (!ler_inteiro("Opcao: ", &opcao) || opcao == 0) break;
        switch (opcao) {
            case 1: menu_binaria(&arvore_binaria); break;
            case 2: menu_bst(&bst); break;
            case 3: menu_avl(&avl); break;
            case 4: menu_heap(&heap); break;
            case 5: experimento(); break;
            default: puts("Opcao invalida. Escolha uma das opcoes do menu."); break;
        }
    }
    ab_limpar(&arvore_binaria);
    bst_limpar(&bst);
    avl_limpar(&avl);
    puts("Recursos liberados. Encerrando o laboratorio.");
    return 0;
}
