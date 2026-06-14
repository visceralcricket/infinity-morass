#ifndef LIST_H
#define LIST_H

typedef struct List List;

// Creates a list and returns its pointer
List *listCreate();

// Returns the pointer to the first node of the list
void *listFirst(List *L);

// Moves pointer 'current' to the next node and returns its pointer
void *listNext(List *L);

// Inserts a new node at the start of the list
void listPushFront(List *L, void *dato);

// Inserts a new node at the end of the list
void listPushBack(List *L, void *dato);

// // Inserts a new node right after the 'current' one
void listPushCurrent(List *L, void *dato);

// Deletes the first element of the list
void *listPopFront(List *L);

// Deletes the last element of the list
void *listPopBack(List *L);

// Deletes the node 'current' of the list
void *listPopCurrent(List *L);

// Deletes all the nodes and leaves the list clean
void listClean(List *L);

// Returns the logical size of the list
int listSize(List* L);

#endif
