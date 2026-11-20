/* Interfaces elaboradas com apoio de IA: ver IA-03 em USO_IA.md. */
#ifndef AVL_H
#define AVL_H
#include <stdio.h>
typedef struct NoAVL {
    int chave;
    int altura;
    struct NoAVL *esquerda, *direita;
} NoAVL;
typedef enum { AVL_OK, AVL_DUPLICADA, AVL_SEM_MEMORIA } AvlResultado;
typedef struct {
    int ll, rr, lr, rl;
} AvlRotacoes;
AvlResultado avl_inserir(NoAVL **raiz, int chave, AvlRotacoes *rotacoes);
const NoAVL *avl_buscar(const NoAVL *raiz, int chave, int *visitados);
int avl_altura(const NoAVL *raiz);
int avl_contar_nos(const NoAVL *raiz);
int avl_fator(const NoAVL *no);
int avl_verificar(const NoAVL *raiz);
void avl_em_ordem(const NoAVL *raiz, FILE *saida);
void avl_ligacoes(const NoAVL *raiz, FILE *saida);
void avl_limpar(NoAVL **raiz);
#endif
