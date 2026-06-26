#ifndef HEAP_H
#define HEAP_H

typedef struct Heap Heap;

void* heapTop(Heap* pq);

void heapPush(Heap* pq, void* data, int priority);

void heapPop(Heap* pq);

Heap* heapCreate();

/* +++
Libera los datos de cada elemento utilizando la función de liberación de memoria proporcionada
para despues liberar la matriz interna y la propia estructura Heap. Si `freeData` es NULL, solo
se liberan la memoria interna y la estructura (los elementos no se liberan)
--- */
void heapDestroyWithFree(Heap *pq, void (*freeData)(void*));

void heapDestroy(Heap *pq);

#endif