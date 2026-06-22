#ifndef HEAP_H
#define HEAP_H

typedef struct Heap Heap;

void* heapTop(Heap* pq);

void heapPush(Heap* pq, void* data, int priority);

void heapPop(Heap* pq);

Heap* heapCreate();

/*
 * Frees each element's data using the provided callback, then frees
 * the internal array and the Heap struct itself. If `freeData` is NULL
 * only the internal memory and struct are freed (elements are not freed).
 */
void heapDestroyWithFree(Heap *pq, void (*freeData)(void*));

void heapDestroy(Heap *pq);

#endif