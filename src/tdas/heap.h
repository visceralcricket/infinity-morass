#ifndef HEAP_H
#define HEAP_H

typedef struct Heap Heap;

void* heapTop(Heap* pq);

void heapPush(Heap* pq, void* data, int priority);

void heapPop(Heap* pq);

Heap* heapCreate();

void heapDestroy(Heap *pq);

#endif