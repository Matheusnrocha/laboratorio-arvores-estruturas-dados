/* Modulo elaborado com apoio de IA: ver IA-01 em USO_IA.md. */
#include "arvore_binaria.h"
#include <stdlib.h>

static NoBinario *novo_no(int chave) {
    NoBinario *no = malloc(sizeof(*no));
    if (no != NULL) {
        no->chave = chave;
        no->esquerda = NULL;
        no->direita = NULL;
    }
    return no;
}

const NoBinario *ab_buscar(const NoBinario *raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave) return raiz;
    const NoBinario *no = ab_buscar(raiz->esquerda, chave);
    return no != NULL ? no : ab_buscar(raiz->direita, chave);
}

AbResultado ab_inserir(NoBinario **raiz, int chave, int pai, char lado) {
    if (ab_buscar(*raiz, chave) != NULL) return AB_DUPLICADA;
    if (*raiz == NULL) {
        *raiz = novo_no(chave);
        return *raiz != NULL ? AB_OK : AB_SEM_MEMORIA;
    }
    if (lado != 'E' && lado != 'e' && lado != 'D' && lado != 'd') return AB_LADO_INVALIDO;
    NoBinario *no_pai = (NoBinario *)ab_buscar(*raiz, pai);
    if (no_pai == NULL) return AB_PAI_AUSENTE;
    NoBinario **destino = (lado == 'E' || lado == 'e') ? &no_pai->esquerda : &no_pai->direita;
    if (*destino != NULL) return AB_POSICAO_OCUPADA;
    *destino = novo_no(chave);
    return *destino != NULL ? AB_OK : AB_SEM_MEMORIA;
}

/* Exemplo exigido no enunciado. Implementacao e testes: IA-01. */
AbResultado ab_carregar_exemplo(NoBinario **raiz) {
    if (*raiz != NULL) return AB_NAO_VAZIA;
    struct Ligacao { int chave, pai; char lado; } dados[] = {
        {10, 0, 'E'}, {30, 10, 'E'}, {5, 10, 'D'},
        {20, 30, 'E'}, {40, 30, 'D'}, {15, 5, 'D'}
    };
    for (size_t i = 0; i < sizeof(dados)/sizeof(dados[0]); ++i) {
        AbResultado resultado = ab_inserir(raiz, dados[i].chave, dados[i].pai, dados[i].lado);
        if (resultado != AB_OK) {
            ab_limpar(raiz);
            return resultado;
        }
    }
    return AB_OK;
}

int ab_altura(const NoBinario *raiz) {
    if (raiz == NULL) return -1;
    int e = ab_altura(raiz->esquerda), d = ab_altura(raiz->direita);
    return 1 + (e > d ? e : d);
}
int ab_contar_nos(const NoBinario *raiz) {
    return raiz == NULL ? 0 : 1 + ab_contar_nos(raiz->esquerda) + ab_contar_nos(raiz->direita);
}
int ab_contar_folhas(const NoBinario *raiz) {
    if (raiz == NULL) return 0;
    if (raiz->esquerda == NULL && raiz->direita == NULL) return 1;
    return ab_contar_folhas(raiz->esquerda) + ab_contar_folhas(raiz->direita);
}

static void imprimir_chave(int chave, FILE *saida, int *primeira) {
    fprintf(saida, "%s%d", *primeira ? "" : ", ", chave);
    *primeira = 0;
}
static void percurso(const NoBinario *no, FILE *saida, int *primeira, int modo) {
    if (no == NULL) return;
    if (modo == 0) imprimir_chave(no->chave, saida, primeira);
    percurso(no->esquerda, saida, primeira, modo);
    if (modo == 1) imprimir_chave(no->chave, saida, primeira);
    percurso(no->direita, saida, primeira, modo);
    if (modo == 2) imprimir_chave(no->chave, saida, primeira);
}
void ab_pre_ordem(const NoBinario *raiz, FILE *saida) { int primeira = 1; percurso(raiz, saida, &primeira, 0); }
void ab_em_ordem(const NoBinario *raiz, FILE *saida) { int primeira = 1; percurso(raiz, saida, &primeira, 1); }
void ab_pos_ordem(const NoBinario *raiz, FILE *saida) { int primeira = 1; percurso(raiz, saida, &primeira, 2); }

void ab_ligacoes(const NoBinario *raiz, FILE *saida) {
    if (raiz == NULL) return;
    fprintf(saida, "%-12d", raiz->chave);
    if (raiz->esquerda) fprintf(saida, "%-12d", raiz->esquerda->chave);
    else fprintf(saida, "%-12s", "NULL");
    if (raiz->direita) fprintf(saida, "%d\n", raiz->direita->chave);
    else fprintf(saida, "NULL\n");
    ab_ligacoes(raiz->esquerda, saida);
    ab_ligacoes(raiz->direita, saida);
}
void ab_limpar(NoBinario **raiz) {
    if (*raiz == NULL) return;
    ab_limpar(&(*raiz)->esquerda);
    ab_limpar(&(*raiz)->direita);
    free(*raiz);
    *raiz = NULL;
}
