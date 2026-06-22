#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heapTop(Heap* pq){
    if(pq->size==0) return NULL;
    return pq->heapArray[0].data;
}

void heapPush(Heap* pq, void* data, int priority){

    if(pq->size+1>pq->capac){
        //printf("se expande de %i a ", pq->capac);
        pq->capac=(pq->capac)*2+1;
        //printf("%i * %lu", pq->capac, sizeof(heapElem));
        pq->heapArray=realloc(pq->heapArray, (pq->capac)*sizeof(heapElem));
    }

    /*Flotación*/
    int now = pq->size;
    while(now>0 && pq->heapArray[(now-1)/2].priority > priority)
        {
                pq->heapArray[now] = pq->heapArray[(now-1)/2];
                now = (now -1)/2;
        }
    pq->heapArray[now].priority = priority;
    pq->heapArray[now].data = data;
    pq->size++;
}


void heapPop(Heap* pq){
        if (pq->size == 0) return;

        pq->size--;
        if (pq->size == 0) return;

        pq->heapArray[0] = pq->heapArray[pq->size];

        int now = 0;
        while (1) {
            int left = 2 * now + 1;
            int right = 2 * now + 2;
            int smallest = now;

            if (left < pq->size && pq->heapArray[left].priority < pq->heapArray[smallest].priority) {
                smallest = left;
            }
            if (right < pq->size && pq->heapArray[right].priority < pq->heapArray[smallest].priority) {
                smallest = right;
            }
            if (smallest == now) break;

            heapElem tmp = pq->heapArray[now];
            pq->heapArray[now] = pq->heapArray[smallest];
            pq->heapArray[smallest] = tmp;
            now = smallest;
        }
        //printf("size = %i, top = %i\n", pq->size, pq->heapArray[0].data );
}

Heap* heapCreate(){
   Heap *pq=(Heap*) malloc(sizeof(Heap));
   pq->heapArray=(heapElem*) malloc(3*sizeof(heapElem));
   pq->size=0;
   pq->capac=3; //capacidad inicial
   return pq;
}

void heapDestroyWithFree(Heap *pq, void (*freeData)(void*)) {
    if (!pq) return;
    if (freeData) {
        for (int i = 0; i < pq->size; ++i) {
            if (pq->heapArray[i].data)
                freeData(pq->heapArray[i].data);
        }
    }
    free(pq->heapArray);
    free(pq);
}

void heapDestroy(Heap *pq) {
    heapDestroyWithFree(pq, NULL);
}