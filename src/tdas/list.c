#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct List List;

struct Node {
  void *data;
  Node *next;
  Node *prev;
};

struct List {
  Node *head;
  Node *tail;
  Node *current;
  int size;
};

List *listCreate() {
  List *newList = (List *)malloc(sizeof(List));
  if (!newList) {
    return NULL; // Memory allocation failed
  }

  newList->head = NULL;
  newList->tail = NULL;
  newList->current = NULL;
  newList->size = 0;
  return newList;
}

void *listCurrent(List *L) {
  if (!L || !L->current) return NULL;
  return L->current->data;
}

void *listFirst(List *L) {
  if (!L || !L->head) {
    return NULL; // Empty list or without a head
  }
  L->current = L->head;
  return L->current->data;
}

void *listNext(List *L) {
  if (!L || !L->current || !L->current->next) {
    return NULL; // Same as previous + no node to next
  }
  L->current = L->current->next;
  return L->current->data;
}

void *listPrev(List *L) {
  if(!L || !L->current || !L->current->prev) return NULL;
  L->current = L->current->prev;
  return L->current->data;
}

void listPushFront(List *L, void *data) {
  if (!L) return;

  Node *newNode = (Node *)malloc(sizeof(Node));
  if (!newNode) return;

  newNode->data = data;
  newNode->next = L->head;
  newNode->prev = NULL;

  if(L->head) L->head->prev = newNode;
  L->head = newNode;
  // If the list was empty => has no tail
  if(!L->tail) L->tail = newNode;

  L->size++;
}

void listPushBack(List *L, void *data) {
  if (!L) return;

  Node *newNode = (Node *)malloc(sizeof(Node));
  if (!newNode) return;

  newNode->data = data;
  newNode->next = NULL;
  newNode->prev = L->tail;

  if (!L->tail) { // Same empty list with no tail as before
    L->head = newNode;
    L->tail = newNode;
  }

  else {
    L->tail->next = newNode;
    L->tail = newNode;
  }
  L->size++;
}

void listPushCurrent(List *L, void *data) {
  if (!L || !L->current) return;

  Node *newNode = (Node *)malloc(sizeof(Node));
  if (!newNode) return;

  newNode->data = data;
  newNode->next = L->current->next;
  newNode->prev = L->current;

  if(L->current->next) L->current->next->prev = newNode;

  L->current->next = newNode;

  // Update tail if it's added at the end of the list
  if (!newNode->next) L->tail = newNode;

  L->size++;
}



void *listPopFront(List *L) {
  if (!L || !L->head) return NULL;
  
  Node *tmp = L->head;
  L->head = L->head->next;

  if (!L->head) L->tail = NULL;
  else L->head->prev = NULL;

  void *data = tmp->data;
  free(tmp);
  L->size--;
  return data;
}

void *listPopBack(List *L) {
  if (!L || !L->head) return NULL;

  Node *tmp = L->tail;
  L->tail = L->tail->prev;

  if(!L->tail) L->head = NULL;
  else L->tail->next = NULL;
  
  void *data = tmp->data;
  free(tmp);
  L->size--;
  return data;
}

void *listPopCurrent(List *L) {
  if (!L || !L->current) return NULL;

  Node *tmp = L->current;
  if(tmp->prev) tmp->prev->next = tmp->next;
  else L->head = tmp->next;
  
  if(tmp->next) tmp->next->prev = tmp->prev;
  else L->tail = tmp->prev;

  void *data = tmp->data;
  L->current = tmp->next;
  free(tmp);
  L->size--;

  return data;
}

int listSize(List *L){
  if(!L) return 0;
    return L->size;
}

void listClean(List *L) {
  if (!L) return;

  Node *current = L->head;
  Node *next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
  L->head = NULL;
  L->tail = NULL;
  L->current = NULL;
  L->size = 0;
}
