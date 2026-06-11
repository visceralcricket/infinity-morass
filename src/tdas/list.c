#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  void *data;
  struct Node *next;
} Node;

struct List {
  Node *head;
  Node *tail;
  Node *current;
  int size;
};

typedef List List;

List *list_create() {
  List *newList = (List *)malloc(sizeof(List));
  if (newList == NULL) {
    return NULL; // Memory allocation failed
  }
  newList->head = NULL;
  newList->tail = NULL;
  newList->current = NULL;
  newList->size = 0;
  return newList;
}

void *list_first(List *L) {
  if (L == NULL || L->head == NULL) {
    return NULL; // Empty list or without a head
  }
  L->current = L->head;
  return L->current->data;
}

void *list_next(List *L) {
  if (L == NULL || L->current == NULL || L->current->next == NULL) {
    return NULL; // Same as previous + no node to next
  }
  L->current = L->current->next;
  return L->current->data;
}

void list_pushFront(List *L, void *data) {
  if (L == NULL) {
    return;
  }
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    return;
  }
  newNode->data = data;
  newNode->next = L->head;
  L->head = newNode;
  if (L->tail == NULL) { // If the list was empty => has no tail
    L->tail = newNode;
  }
  L->size++;
}

void list_pushBack(List *L, void *data) {
  if (L == NULL) {
    return; // Non-initialized list
  }
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    return;
  }
  newNode->data = data;
  newNode->next = NULL;
  if (L->tail == NULL) { // Same empty list with no tail as before
    L->head = newNode;
    L->tail = newNode;
  } else {
    L->tail->next = newNode;
    L->tail = newNode;
  }
  L->size++;
}

void list_pushCurrent(List *L, void *data) {
  if (L == NULL || L->current == NULL) {
    return; // Empty list or current node not defined
  }
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    return;
  }
  newNode->data = data;
  newNode->next = L->current->next;
  L->current->next = newNode;
  if (L->current == L->tail) {
    L->tail = newNode; // Update tail if it's added at the end of the list
  }
  L->size++;
}



void *list_popFront(List *L) {
  if (L == NULL || L->head == NULL) {
    return NULL;
  }
  Node *temp = L->head;

  L->head = L->head->next;
  if (L->head == NULL) {
    L->tail = NULL; // Update tail to make it a fully-empty list
  }
  void *data = temp->data;
  free(temp);
  L->size--;
  return data;
}

void *list_popBack(List *L) {
  if (L == NULL || L->head == NULL) {
    return NULL;
  }
  if (L->head == L->tail) { // Only 1 node in the list
    return list_popFront(L);
  }
  Node *current = L->head;
  while (current->next != L->tail) {
    current = current->next;
  }
  void *data = L->tail->data;
  free(L->tail);
  current->next = NULL;
  L->tail = current;
  L->size--;
  return data;
}

int list_size(List *L){
    return L->size;
}

void *list_popCurrent(List *L) {
  if (L == NULL || L->current == NULL) {
    return NULL;
  }
  if (L->current == L->head) {
    return list_popFront(L);
  }
  Node *temp = L->head;
  if(!temp) return NULL;

  while (temp != NULL && temp->next != L->current) {
    temp = temp->next;
  }

  if(!temp) return NULL;

  temp->next = L->current->next;
  if (L->current == L->tail) {
    L->tail = temp; // Update tail if it's equal to the node to delete
  }
  void *data = L->current->data;
  free(L->current);
  L->current = temp->next;
  L->size--;
  return data;
}

void list_clean(List *L) {
  if (L == NULL) {
    return;
  }
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
