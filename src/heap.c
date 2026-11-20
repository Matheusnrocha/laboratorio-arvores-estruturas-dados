#include "heap.h"

void heap_inicializar(MaxHeap *heap) { heap->tamanho = 0; }
static void trocar(MaxHeap *heap, int i, int j, FILE *log) {
    if (log != NULL) fprintf(log, "Troca: indice %d (%d) <-> indice %d (%d)\n",
                             i, heap->dados[i], j, heap->dados[j]);
    int auxiliar = heap->dados[i];
    heap->dados[i] = heap->dados[j];
    heap->dados[j] = auxiliar;
}

/* Sift-up e sift-down com rastreamento das trocas. Ver IA-04. */
HeapResultado heap_inserir(MaxHeap *heap, int chave, FILE *log) {
    for (int i = 0; i < heap->tamanho; ++i)
        if (heap->dados[i] == chave) return HEAP_DUPLICADA;
    if (heap->tamanho >= HEAP_CAPACIDADE) return HEAP_CHEIO;
    int i = heap->tamanho++;
    heap->dados[i] = chave;
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (heap->dados[pai] >= heap->dados[i]) break;
        trocar(heap, pai, i, log);
        i = pai;
    }
    return HEAP_OK;
}
HeapResultado heap_consultar(const MaxHeap *heap, int *maximo) {
    if (heap->tamanho == 0) return HEAP_VAZIO;
    if (maximo) *maximo = heap->dados[0];
    return HEAP_OK;
}
HeapResultado heap_extrair(MaxHeap *heap, int *maximo, FILE *log) {
    if (heap->tamanho == 0) return HEAP_VAZIO;
    if (maximo) *maximo = heap->dados[0];
    --heap->tamanho;
    if (heap->tamanho == 0) return HEAP_OK;
    heap->dados[0] = heap->dados[heap->tamanho];
    int i = 0;
    while (1) {
        int maior = i;
        int esquerda = 2 * i + 1;
        int direita = 2 * i + 2;
        if (esquerda < heap->tamanho && heap->dados[esquerda] > heap->dados[maior])
            maior = esquerda;
        if (direita < heap->tamanho && heap->dados[direita] > heap->dados[maior])
            maior = direita;
        if (maior == i) break;
        trocar(heap, i, maior, log);
        i = maior;
    }
    return HEAP_OK;
}
int heap_verificar(const MaxHeap *heap) {
    if (heap->tamanho < 0 || heap->tamanho > HEAP_CAPACIDADE) return 0;
    for (int i = 0; i < heap->tamanho; ++i) {
        int e = i * 2 + 1, d = i * 2 + 2;
        if (e < heap->tamanho && heap->dados[e] > heap->dados[i]) return 0;
        if (d < heap->tamanho && heap->dados[d] > heap->dados[i]) return 0;
    }
    return 1;
}
void heap_exibir(const MaxHeap *heap, FILE *saida) {
    fprintf(saida, "Tamanho: %d / %d\n", heap->tamanho, HEAP_CAPACIDADE);
    if (heap->tamanho == 0) { fprintf(saida, "Heap vazio.\n"); return; }
    fprintf(saida, "Indices: ");
    for (int i = 0; i < heap->tamanho; ++i) fprintf(saida, "%s%d", i ? ", " : "", i);
    fprintf(saida, "\nValores: ");
    for (int i = 0; i < heap->tamanho; ++i) fprintf(saida, "%s%d", i ? ", " : "", heap->dados[i]);
    fprintf(saida, "\n");
}
