/* Modulo elaborado com apoio de IA: ver IA-03 em USO_IA.md. */
#include "avl.h"
#include <stdlib.h>
#include <limits.h>

int avl_altura(const NoAVL *raiz) { return raiz == NULL ? -1 : raiz->altura; }
int avl_fator(const NoAVL *no) {
    return no == NULL ? 0 : avl_altura(no->esquerda) - avl_altura(no->direita);
}
static void atualizar_altura(NoAVL *no) {
    int e = avl_altura(no->esquerda), d = avl_altura(no->direita);
    no->altura = (e > d ? e : d) + 1;
}
/* Rotacoes alteram os ponteiros e atualizam as alturas de baixo para cima. Ver IA-03. */
static NoAVL *rotacao_direita(NoAVL *y) {
    NoAVL *x = y->esquerda;
    NoAVL *meio = x->direita;
    x->direita = y;
    y->esquerda = meio;
    atualizar_altura(y);
    atualizar_altura(x);
    return x;
}
static NoAVL *rotacao_esquerda(NoAVL *x) {
    NoAVL *y = x->direita;
    NoAVL *meio = y->esquerda;
    y->esquerda = x;
    x->direita = meio;
    atualizar_altura(x);
    atualizar_altura(y);
    return y;
}
static NoAVL *inserir_rec(NoAVL *raiz, int chave, AvlResultado *resultado, AvlRotacoes *eventos) {
    if (raiz == NULL) {
        NoAVL *novo = malloc(sizeof(*novo));
        if (novo == NULL) { *resultado = AVL_SEM_MEMORIA; return NULL; }
        novo->chave = chave;
        novo->altura = 0;
        novo->esquerda = novo->direita = NULL;
        *resultado = AVL_OK;
        return novo;
    }
    if (chave == raiz->chave) { *resultado = AVL_DUPLICADA; return raiz; }
    if (chave < raiz->chave) {
        raiz->esquerda = inserir_rec(raiz->esquerda, chave, resultado, eventos);
    } else {
        raiz->direita = inserir_rec(raiz->direita, chave, resultado, eventos);
    }
    if (*resultado != AVL_OK) return raiz;
    atualizar_altura(raiz);
    int fb = avl_fator(raiz);
    if (fb > 1 && chave < raiz->esquerda->chave) {
        if (eventos) ++eventos->ll;
        return rotacao_direita(raiz);
    }
    if (fb < -1 && chave > raiz->direita->chave) {
        if (eventos) ++eventos->rr;
        return rotacao_esquerda(raiz);
    }
    if (fb > 1 && chave > raiz->esquerda->chave) {
        if (eventos) ++eventos->lr;
        raiz->esquerda = rotacao_esquerda(raiz->esquerda);
        return rotacao_direita(raiz);
    }
    if (fb < -1 && chave < raiz->direita->chave) {
        if (eventos) ++eventos->rl;
        raiz->direita = rotacao_direita(raiz->direita);
        return rotacao_esquerda(raiz);
    }
    return raiz;
}
AvlResultado avl_inserir(NoAVL **raiz, int chave, AvlRotacoes *rotacoes) {
    AvlResultado resultado = AVL_OK;
    if (rotacoes != NULL) *rotacoes = (AvlRotacoes){0, 0, 0, 0};
    *raiz = inserir_rec(*raiz, chave, &resultado, rotacoes);
    return resultado;
}
const NoAVL *avl_buscar(const NoAVL *raiz, int chave, int *visitados) {
    if (visitados) *visitados = 0;
    while (raiz != NULL) {
        if (visitados) ++*visitados;
        if (raiz->chave == chave) return raiz;
        raiz = chave < raiz->chave ? raiz->esquerda : raiz->direita;
    }
    return NULL;
}
int avl_contar_nos(const NoAVL *raiz) {
    return raiz == NULL ? 0 : 1 + avl_contar_nos(raiz->esquerda) + avl_contar_nos(raiz->direita);
}
static int verificar_rec(const NoAVL *no, long long minimo, long long maximo, int *altura_real) {
    if (no == NULL) { *altura_real = -1; return 1; }
    if ((long long)no->chave <= minimo || (long long)no->chave >= maximo) return 0;
    int he = -1, hd = -1;
    if (!verificar_rec(no->esquerda, minimo, no->chave, &he)) return 0;
    if (!verificar_rec(no->direita, no->chave, maximo, &hd)) return 0;
    *altura_real = 1 + (he > hd ? he : hd);
    return (he - hd >= -1 && he - hd <= 1 && no->altura == *altura_real);
}
int avl_verificar(const NoAVL *raiz) { int h; return verificar_rec(raiz, LLONG_MIN, LLONG_MAX, &h); }
static void percorrer(const NoAVL *raiz, FILE *saida, int *primeira) {
    if (!raiz) return;
    percorrer(raiz->esquerda, saida, primeira);
    fprintf(saida, "%s%d", *primeira ? "" : ", ", raiz->chave);
    *primeira = 0;
    percorrer(raiz->direita, saida, primeira);
}
void avl_em_ordem(const NoAVL *raiz, FILE *saida) { int primeira = 1; percorrer(raiz, saida, &primeira); }
void avl_ligacoes(const NoAVL *raiz, FILE *saida) {
    if (!raiz) return;
    fprintf(saida, "%-10d", raiz->chave);
    if (raiz->esquerda) fprintf(saida, "%-10d", raiz->esquerda->chave);
    else fprintf(saida, "%-10s", "NULL");
    if (raiz->direita) fprintf(saida, "%-10d", raiz->direita->chave);
    else fprintf(saida, "%-10s", "NULL");
    fprintf(saida, "%-8d%d\n", raiz->altura, avl_fator(raiz));
    avl_ligacoes(raiz->esquerda, saida);
    avl_ligacoes(raiz->direita, saida);
}
void avl_limpar(NoAVL **raiz) {
    if (!*raiz) return;
    avl_limpar(&(*raiz)->esquerda);
    avl_limpar(&(*raiz)->direita);
    free(*raiz);
    *raiz = NULL;
}
