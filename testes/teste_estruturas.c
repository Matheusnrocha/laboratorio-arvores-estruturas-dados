/* Testes elaborados com apoio de IA: ver IA-06 em USO_IA.md. */
#include "../src/arvore_binaria.h"
#include "../src/bst.h"
#include "../src/avl.h"
#include "../src/heap.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

static void confere_percurso(const char *esperado, void (*imprimir)(const void *, FILE *), const void *raiz) {
    FILE *f = tmpfile();
    assert(f != NULL);
    imprimir(raiz, f);
    rewind(f);
    char buffer[1024] = {0};
    size_t lidos = fread(buffer, 1, sizeof(buffer)-1, f);
    buffer[lidos] = '\0';
    assert(strcmp(buffer, esperado) == 0);
    fclose(f);
}
/* Adaptadores para testar impressao sem extensoes especificas do GCC. */
static void pre_bin(const void *r, FILE *f) { ab_pre_ordem(r, f); }
static void in_bin(const void *r, FILE *f) { ab_em_ordem(r, f); }
static void pos_bin(const void *r, FILE *f) { ab_pos_ordem(r, f); }
static void in_bst(const void *r, FILE *f) { bst_em_ordem(r, f); }
static void in_avl(const void *r, FILE *f) { avl_em_ordem(r, f); }

static void teste_binaria(void) {
    NoBinario *r = NULL;
    assert(ab_altura(r) == -1 && ab_contar_nos(r) == 0 && ab_contar_folhas(r) == 0);
    assert(ab_carregar_exemplo(&r) == AB_OK);
    assert(ab_carregar_exemplo(&r) == AB_NAO_VAZIA);
    assert(r->chave == 10 && r->esquerda->chave == 30 && r->direita->chave == 5);
    confere_percurso("10, 30, 20, 40, 5, 15", pre_bin, r);
    confere_percurso("20, 30, 40, 10, 5, 15", in_bin, r);
    confere_percurso("20, 40, 30, 15, 5, 10", pos_bin, r);
    assert(ab_contar_nos(r) == 6 && ab_contar_folhas(r) == 3 && ab_altura(r) == 2);
    assert(ab_inserir(&r, 77, 30, 'E') == AB_POSICAO_OCUPADA);
    assert(r->esquerda->esquerda->chave == 20);
    assert(ab_inserir(&r, 77, 1234, 'D') == AB_PAI_AUSENTE);
    assert(ab_inserir(&r, 77, 30, '?') == AB_LADO_INVALIDO);
    assert(ab_inserir(&r, 5, 30, 'E') == AB_DUPLICADA);
    ab_limpar(&r);
    assert(r == NULL);
    assert(ab_inserir(&r, INT_MIN, 0, 'E') == AB_OK);
    assert(ab_altura(r) == 0 && ab_contar_folhas(r) == 1);
    ab_limpar(&r);
    puts("PASS Arvore binaria: exemplo, 3 percursos, rejeicoes, casos limites, limpeza");
}
static void teste_bst(void) {
    NoBST *r = NULL;
    int visitas = -1;
    assert(bst_altura(r) == -1 && bst_verificar(r));
    assert(bst_buscar(r, 10, &visitas) == NULL && visitas == 0);
    assert(bst_remover(&r, 99) == BST_AUSENTE);
    int dados[] = {50, 30, 70, 20, 40, 60, 80};
    for (size_t i = 0; i < sizeof(dados)/sizeof(dados[0]); ++i)
        assert(bst_inserir(&r, dados[i]) == BST_OK);
    assert(bst_inserir(&r, 50) == BST_DUPLICADA);
    assert(bst_altura(r) == 2 && bst_contar_nos(r) == 7);
    assert(bst_verificar(r));
    /* Viola apenas o limite de um ancestral (100 > raiz 50, mas > pai 30). */
    r->esquerda->direita->chave = 100;
    assert(!bst_verificar(r));
    r->esquerda->direita->chave = 40;
    assert(bst_verificar(r));
    confere_percurso("20, 30, 40, 50, 60, 70, 80", in_bst, r);
    assert(bst_buscar(r, 60, &visitas) != NULL && visitas == 3);
    assert(bst_buscar(r, 99, &visitas) == NULL && visitas == 3);
    assert(bst_remover(&r, 20) == BST_OK); /* folha */
    assert(bst_remover(&r, 30) == BST_OK); /* um filho */
    assert(bst_remover(&r, 50) == BST_OK); /* raiz com dois filhos */
    assert(r->chave == 60 && bst_verificar(r));
    confere_percurso("40, 60, 70, 80", in_bst, r);
    assert(bst_remover(&r, 200) == BST_AUSENTE);
    /* Um no, raiz, valores extremos e reinsercao depois da limpeza. */
    bst_limpar(&r);
    assert(r == NULL);
    assert(bst_inserir(&r, INT_MIN) == BST_OK);
    assert(bst_inserir(&r, INT_MAX) == BST_OK);
    assert(bst_verificar(r));
    assert(bst_remover(&r, INT_MIN) == BST_OK && r->chave == INT_MAX);
    assert(bst_remover(&r, INT_MAX) == BST_OK && r == NULL);
    bst_limpar(&r);
    puts("PASS BST: busca visitados, tres remocoes, raiz, limites, ordenacao, limpeza");
}
static void teste_avl(void) {
    const int sequencias[4][3] = {{30,20,10},{10,20,30},{30,10,20},{10,30,20}};
    for (int tipo = 0; tipo < 4; ++tipo) {
        NoAVL *r = NULL;
        AvlRotacoes rot = {0};
        assert(avl_altura(r) == -1 && avl_verificar(r));
        for (int i = 0; i < 3; ++i) {
            assert(avl_inserir(&r, sequencias[tipo][i], &rot) == AVL_OK);
            assert(avl_verificar(r));
        }
        int casos[4] = {rot.ll, rot.rr, rot.lr, rot.rl};
        assert(casos[tipo] == 1);
        assert(r->chave == 20 && r->esquerda->chave == 10 && r->direita->chave == 30);
        assert(r->altura == 1 && avl_fator(r) == 0);
        assert(avl_fator(r->esquerda) == 0 && avl_fator(r->direita) == 0);
        confere_percurso("10, 20, 30", in_avl, r);
        assert(avl_inserir(&r, 10, &rot) == AVL_DUPLICADA && avl_verificar(r));
        avl_limpar(&r);
        assert(r == NULL);
    }
    NoAVL *a = NULL;
    int visitados;
    for (int i = 1; i <= 15; ++i) {
        assert(avl_inserir(&a, i, NULL) == AVL_OK);
        assert(avl_verificar(a));
    }
    assert(avl_altura(a) == 3 && avl_contar_nos(a) == 15);
    ++a->altura; /* Inconsistencia armazenada de altura deve ser detectada. */
    assert(!avl_verificar(a));
    --a->altura;
    assert(avl_verificar(a));
    int esperado[] = {4, 1, 4, 4};
    int busca[] = {1, 8, 15, 99};
    for (int i = 0; i < 4; ++i) {
        avl_buscar(a, busca[i], &visitados);
        assert(visitados == esperado[i]);
    }
    avl_limpar(&a);
    assert(a == NULL);
    puts("PASS AVL: LL/RR/LR/RL, FB, alturas, busca, duplicatas, comparacao");
}
static void teste_heap(void) {
    MaxHeap heap;
    int maximo;
    heap_inicializar(&heap);
    assert(heap_extrair(&heap, &maximo, NULL) == HEAP_VAZIO);
    assert(heap_consultar(&heap, &maximo) == HEAP_VAZIO);
    int entrada[] = {50, 30, 40, 10, 20, 35, 60};
    for (size_t i = 0; i < sizeof(entrada)/sizeof(entrada[0]); ++i) {
        assert(heap_inserir(&heap, entrada[i], NULL) == HEAP_OK);
        assert(heap_verificar(&heap));
    }
    int esperado_vetor[] = {60, 30, 50, 10, 20, 35, 40};
    assert(memcmp(heap.dados, esperado_vetor, sizeof(esperado_vetor)) == 0);
    heap.dados[1] = 1000; /* Filho maior que o pai deve invalidar o heap. */
    assert(!heap_verificar(&heap));
    heap.dados[1] = 30;
    assert(heap_verificar(&heap));
    assert(heap_consultar(&heap, &maximo) == HEAP_OK && maximo == 60 && heap.tamanho == 7);
    assert(heap_inserir(&heap, 20, NULL) == HEAP_DUPLICADA);
    assert(heap_extrair(&heap, &maximo, NULL) == HEAP_OK && maximo == 60);
    int esperado_apos[] = {50, 30, 40, 10, 20, 35};
    assert(memcmp(heap.dados, esperado_apos, sizeof(esperado_apos)) == 0);
    int ordem[] = {50, 40, 35, 30, 20, 10};
    for (int i = 0; i < 6; ++i) {
        assert(heap_extrair(&heap, &maximo, NULL) == HEAP_OK && maximo == ordem[i]);
        assert(heap_verificar(&heap));
    }
    assert(heap_extrair(&heap, &maximo, NULL) == HEAP_VAZIO);
    assert(heap_inserir(&heap, INT_MIN, NULL) == HEAP_OK);
    assert(heap_extrair(&heap, &maximo, NULL) == HEAP_OK && maximo == INT_MIN);
    for (int i = 0; i < HEAP_CAPACIDADE; ++i)
        assert(heap_inserir(&heap, i, NULL) == HEAP_OK);
    assert(heap_inserir(&heap, HEAP_CAPACIDADE, NULL) == HEAP_CHEIO);
    assert(heap_verificar(&heap));
    heap_inicializar(&heap);
    assert(heap.tamanho == 0);
    assert(heap_inserir(&heap, 123, NULL) == HEAP_OK);
    puts("PASS Heap: sift-up/down, vetor, extracoes decrescentes, capacidade, vazios");
}
static void teste_comparacao(void) {
    NoBST *b = NULL;
    NoAVL *a = NULL;
    int procurados[] = {1, 8, 15, 99};
    int esperado_b[] = {1, 8, 15, 15}, esperado_a[] = {4, 1, 4, 4};
    for (int i = 1; i <= 15; ++i) {
        assert(bst_inserir(&b, i) == BST_OK);
        assert(avl_inserir(&a, i, NULL) == AVL_OK);
    }
    assert(bst_altura(b) == 14 && avl_altura(a) == 3);
    for (int i = 0; i < 4; ++i) {
        int vb = 0, va = 0;
        bst_buscar(b, procurados[i], &vb);
        avl_buscar(a, procurados[i], &va);
        assert(vb == esperado_b[i] && va == esperado_a[i]);
    }
    assert(bst_verificar(b) && avl_verificar(a));
    bst_limpar(&b);
    avl_limpar(&a);
    puts("PASS Comparacao: alturas 14/3 e visitas 1,8,15,15 / 4,1,4,4");
}
int main(void) {
    teste_binaria();
    teste_bst();
    teste_avl();
    teste_heap();
    teste_comparacao();
    puts("TOTAL: 5 conjuntos de testes APROVADOS.");
    return 0;
}
