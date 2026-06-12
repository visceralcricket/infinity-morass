#ifndef LIST_H
#define LIST_H

typedef struct List List;

// Creates a list and returns its pointer
List *list_create();

// Returns the pointer to the first node of the list
void *list_first(List *L);

// Moves pointer 'current' to the next node and returns its pointer
void *list_next(List *L);

// Inserts a new node at the start of the list
void list_pushFront(List *L, void *dato);

// Inserts a new node at the end of the list
void list_pushBack(List *L, void *dato);

// // Inserts a new node right after the 'current' one
void list_pushCurrent(List *L, void *dato);

// Deletes the first element of the list
void *list_popFront(List *L);

// Deletes the last element of the list
void *list_popBack(List *L);

// Deletes the node 'current' of the list
void *list_popCurrent(List *L);

// Deletes all the nodes and leaves the list clean
void list_clean(List *L);

// Returns the logical size of the list
int list_size(List* L);

#endif
