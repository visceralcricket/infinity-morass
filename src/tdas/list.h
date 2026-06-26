#ifndef LIST_H
#define LIST_H

typedef struct List List;

// Crear una lista y retornar puntero a la misma
List *listCreate();

// Retornar puntero al nodo actual
void *listCurrent(List *L);

// Retornar puntero al primer nodo de la lista
void *listFirst(List *L);

// Mueve el puntero current (actual) al siguiente y lo retorna
void *listNext(List *L);

// Mueve el puntero current (actual) al anterior y lo retorna
void *listPrev(List *L);

// Inserta un nuevo nodo al inicio de la lista
void listPushFront(List *L, void *data);

// Inserta un nuevo nodo al final de la lista
void listPushBack(List *L, void *data);

// Inserta un nuevo nodo justo después del nodo current (actual)
void listPushCurrent(List *L, void *data);

// Elimina el primer elemento de la lista
void *listPopFront(List *L);

// Elimina el último elemento de la lista
void *listPopBack(List *L);

// Elimina el elemento current (actual) de la lista
void *listPopCurrent(List *L);

// Elimina todos los nodos y libera la lista
void listClean(List *L);

// Retorna el tamaño lógico de la lista
int listSize(List *L);

#endif