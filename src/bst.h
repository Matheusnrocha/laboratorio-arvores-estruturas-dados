/* Interfaces elaboradas com apoio de IA: ver IA-02 em USO_IA.md. */
#ifndef BST_H
#define BST_H
#include <stdio.h>
typedef struct NoBST {
    int chave;
    struct NoBST *esquerda, *direita;
} NoBST;
typedef enum { BST_OK, BST_DUPLICADA, BST_AUSENTE, BST_SEM_MEMORIA } BstResultado;
BstResultado bst_inserir(NoBST **raiz, int chave);
const NoBST *bst_buscar(const NoBST *raiz, int chave, int *visitados);
BstResultado bst_remover(NoBST **raiz, int chave);
int bst_verificar(const NoBST *raiz);
int bst_altura(const NoBST *raiz);
int bst_contar_nos(const NoBST *raiz);
void bst_pre_ordem(const NoBST *raiz, FILE *saida);
void bst_em_ordem(const NoBST *raiz, FILE *saida);
void bst_pos_ordem(const NoBST *raiz, FILE *saida);
void bst_ligacoes(const NoBST *raiz, FILE *saida);
void bst_limpar(NoBST **raiz);
#endif
