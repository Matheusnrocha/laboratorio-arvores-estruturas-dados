/* Interfaces elaboradas com apoio de IA: ver IA-04 em USO_IA.md. */
#ifndef HEAP_H
#define HEAP_H
#include <stdio.h>
#define HEAP_CAPACIDADE 128
typedef struct { int dados[HEAP_CAPACIDADE]; int tamanho; } MaxHeap;
typedef enum { HEAP_OK, HEAP_DUPLICADA, HEAP_CHEIO, HEAP_VAZIO } HeapResultado;
void heap_inicializar(MaxHeap *heap);
HeapResultado heap_inserir(MaxHeap *heap, int chave, FILE *log);
HeapResultado heap_consultar(const MaxHeap *heap, int *maximo);
HeapResultado heap_extrair(MaxHeap *heap, int *maximo, FILE *log);
int heap_verificar(const MaxHeap *heap);
void heap_exibir(const MaxHeap *heap, FILE *saida);
#endif
