#include "bst.h"
#include <stdlib.h>
#include <limits.h>

BstResultado bst_inserir(NoBST **raiz, int chave) {
    NoBST **atual = raiz;
    while (*atual != NULL) {
        if ((*atual)->chave == chave) return BST_DUPLICADA;
        atual = chave < (*atual)->chave ? &(*atual)->esquerda : &(*atual)->direita;
    }
    NoBST *novo = malloc(sizeof(*novo));
    if (novo == NULL) return BST_SEM_MEMORIA;
    novo->chave = chave;
    novo->esquerda = novo->direita = NULL;
    *atual = novo;
    return BST_OK;
}
const NoBST *bst_buscar(const NoBST *raiz, int chave, int *visitados) {
    if (visitados != NULL) *visitados = 0;
    while (raiz != NULL) {
        if (visitados != NULL) ++*visitados;
        if (raiz->chave == chave) return raiz;
        raiz = chave < raiz->chave ? raiz->esquerda : raiz->direita;
    }
    return NULL;
}

/* Remocao usa o sucessor em ordem: menor chave da subarvore direita. Ver IA-02. */
BstResultado bst_remover(NoBST **raiz, int chave) {
    NoBST **destino = raiz;
    while (*destino != NULL && (*destino)->chave != chave) {
        destino = chave < (*destino)->chave ? &(*destino)->esquerda : &(*destino)->direita;
    }
    if (*destino == NULL) return BST_AUSENTE;
    NoBST *no = *destino;
    if (no->esquerda == NULL || no->direita == NULL) {
        *destino = no->esquerda != NULL ? no->esquerda : no->direita;
        free(no);
        return BST_OK;
    }
    NoBST **sucessor = &no->direita;
    while ((*sucessor)->esquerda != NULL) sucessor = &(*sucessor)->esquerda;
    NoBST *extraido = *sucessor;
    no->chave = extraido->chave;
    *sucessor = extraido->direita;
    free(extraido);
    return BST_OK;
}

static int verificar_limites(const NoBST *no, long long minimo, long long maximo) {
    if (no == NULL) return 1;
    if ((long long)no->chave <= minimo || (long long)no->chave >= maximo) return 0;
    return verificar_limites(no->esquerda, minimo, no->chave) &&
           verificar_limites(no->direita, no->chave, maximo);
}
int bst_verificar(const NoBST *raiz) { return verificar_limites(raiz, LLONG_MIN, LLONG_MAX); }
int bst_altura(const NoBST *raiz) {
    if (!raiz) return -1;
    int e = bst_altura(raiz->esquerda), d = bst_altura(raiz->direita);
    return (e > d ? e : d) + 1;
}
int bst_contar_nos(const NoBST *raiz) {
    return raiz == NULL ? 0 : 1 + bst_contar_nos(raiz->esquerda) + bst_contar_nos(raiz->direita);
}
static void imprimir_chave(int chave, FILE *saida, int *primeira) {
    fprintf(saida, "%s%d", *primeira ? "" : ", ", chave);
    *primeira = 0;
}
static void percurso(const NoBST *no, FILE *saida, int *primeira, int modo) {
    if (no == NULL) return;
    if (modo == 0) imprimir_chave(no->chave, saida, primeira);
    percurso(no->esquerda, saida, primeira, modo);
    if (modo == 1) imprimir_chave(no->chave, saida, primeira);
    percurso(no->direita, saida, primeira, modo);
    if (modo == 2) imprimir_chave(no->chave, saida, primeira);
}
void bst_pre_ordem(const NoBST *raiz, FILE *saida) { int primeira = 1; percurso(raiz, saida, &primeira, 0); }
void bst_em_ordem(const NoBST *raiz, FILE *saida) { int primeira = 1; percurso(raiz, saida, &primeira, 1); }
void bst_pos_ordem(const NoBST *raiz, FILE *saida) { int primeira = 1; percurso(raiz, saida, &primeira, 2); }
void bst_ligacoes(const NoBST *raiz, FILE *saida) {
    if (raiz == NULL) return;
    fprintf(saida, "%-12d", raiz->chave);
    if (raiz->esquerda) fprintf(saida, "%-12d", raiz->esquerda->chave);
    else fprintf(saida, "%-12s", "NULL");
    if (raiz->direita) fprintf(saida, "%d\n", raiz->direita->chave);
    else fprintf(saida, "NULL\n");
    bst_ligacoes(raiz->esquerda, saida);
    bst_ligacoes(raiz->direita, saida);
}
void bst_limpar(NoBST **raiz) {
    if (*raiz == NULL) return;
    bst_limpar(&(*raiz)->esquerda);
    bst_limpar(&(*raiz)->direita);
    free(*raiz);
    *raiz = NULL;
}
