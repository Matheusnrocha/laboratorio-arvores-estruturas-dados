#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H
#include <stdio.h>

typedef struct NoBinario {
    int chave;
    struct NoBinario *esquerda, *direita;
} NoBinario;

typedef enum {
    AB_OK, AB_DUPLICADA, AB_PAI_AUSENTE, AB_LADO_INVALIDO,
    AB_POSICAO_OCUPADA, AB_SEM_MEMORIA, AB_NAO_VAZIA
} AbResultado;

AbResultado ab_inserir(NoBinario **raiz, int chave, int pai, char lado);
AbResultado ab_carregar_exemplo(NoBinario **raiz);
const NoBinario *ab_buscar(const NoBinario *raiz, int chave);
int ab_altura(const NoBinario *raiz);
int ab_contar_nos(const NoBinario *raiz);
int ab_contar_folhas(const NoBinario *raiz);
void ab_pre_ordem(const NoBinario *raiz, FILE *saida);
void ab_em_ordem(const NoBinario *raiz, FILE *saida);
void ab_pos_ordem(const NoBinario *raiz, FILE *saida);
void ab_ligacoes(const NoBinario *raiz, FILE *saida);
void ab_limpar(NoBinario **raiz);
#endif
