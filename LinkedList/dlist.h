/*
 * dlist.h
 *
 * This file contains the structure AND implimentation of a
 * doubly linked list in C.
 *
 * There are a number of functions that make initializing, inserting, and removing
 * nodes from the list easier, though these can be done manually by the user
 * through their own implimentations.
 *
 * In order to free the list, call DListFree() on your list.
 * This function will only free the nodes in the list, but you need to free
 * the list pointer itself to completely free all memory
 *
 * THERE IS NO PROTECTION AGAINST REMOVING THE HEAD AND SENTINEL NODES
 * THERE IS NO PROTECTION AGAINST INSERTING A NODE BETWEEN THE HEAD AND SENTINEL NODES
 */

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// Structure for node in the 
// doubly linked list
typedef struct Node {
  void* Val;
  struct Node* Next; // Pointer to next element in dlist
  struct Node* Prev; // Pointer to previous element in dlist
} node_t;

// Structure of the DList
typedef struct DList {
  node_t* Head;
  node_t* Sentinel;
} dlist_t;

/// PROTOTYPES ///
dlist_t* DListInit();                                  // Initialize a new DList with only the head and sentinel nodes
void* DListPrint(dlist_t* l, int8_t n);                  // Iterate through and print the nodes' values in the DList
node_t* DListPush(dlist_t* l, void* val);              // Append a node with desired value to end of DList
node_t* DListFront(dlist_t* l, void* val);             // Prepend a node with desired value at the beginning of DList
node_t* DListInsertAfter(node_t* target, void* val);   // Insert a node after a desired node
node_t* DListInsertBefore(node_t* target, void* val);  // Insert a node before a desired node
node_t* DListPopFront(dlist_t* l);                     // Pop/remove the first node off of the list and return it
node_t* DListPopBack(dlist_t* l);                      // Pop/remove the last node off of the list and return it
node_t* DListRemoveNode(dlist_t* l, node_t* n);                    // Remove a specific node from the list and return it
void DListFree(dlist_t* l);

/// FUNCTION IMPLIMENTATIONS ///

// Creates a fresh DList and returns it
dlist_t* 
DListInit() {
  dlist_t* l = NULL;
  l = (dlist_t*)malloc(sizeof(dlist_t));
  if (l == NULL) {
    return NULL;
  }

  node_t* head = NULL;
  node_t* sentinel = NULL;

  head = (node_t*)malloc(sizeof(node_t));
  if (head == NULL) return NULL;

  sentinel = (node_t*)malloc(sizeof(node_t));
  if (sentinel == NULL) return NULL;

  head->Next = sentinel;
  head->Prev = sentinel;

  sentinel->Next = head;
  sentinel->Prev = head;

  head->Val = (void*)"HEAD";
  sentinel->Val = (void*)"SENTINEL";

  l->Head = head;
  l->Sentinel = sentinel;

  return l;
}

// Prints all nodes except the sentinel node in the DList
// Lines of printing are broken every "n" elements in the list
void*
DListPrint(dlist_t* l, int8_t n) {
  int i;
  node_t* cur;

  if (n < 1) {
    n = 1;
  }

  for (cur = l->Head->Next, i = 1; cur != l->Sentinel; cur = cur->Next, i++) {
    printf("[%s]", (char*)cur->Val);
    if (i % n == 0) printf("\n");
  }
  printf("\n");

  return (void*)cur;
}

// Pushes a node onto the end of the list
node_t*
DListPush(dlist_t* l, void* v) {
  node_t* n = DListInsertBefore(l->Sentinel, v);
  return n;
}

// Pushes a node onto the end of the list
node_t*
DListPushFront(dlist_t* l, void* v) {
  node_t* n = DListInsertAfter(l->Head, v);
  return n;
}

// Insert a node after a desired node
node_t*
DListInsertAfter(node_t* target, void* val) {
  node_t* n = (node_t*)malloc(sizeof(node_t));
  n->Val = val;
  n->Next = target->Next;
  n->Prev = target;

  target->Next->Prev = n;

  target->Next = n;

  return n;
}

// Insert a node before a desired node
node_t*
DListInsertBefore(node_t *target, void* val) {
  node_t* n = (node_t*)malloc(sizeof(node_t));

  n->Val = val;
  n->Next = target;
  n->Prev = target->Prev;

  target->Prev->Next = n;

  target->Prev = n;

  return n;
}

// Removes the first item in the DList and returns it
node_t*
DListPopFront(dlist_t* l) {
  return DListRemoveNode(l, l->Head->Next);
}

// Removes the last item in the DList and returns it
node_t*
DListPopBack(dlist_t* l) {
  return DListRemoveNode(l, l->Sentinel->Prev);
}

node_t*
DListRemoveNode(dlist_t* l, node_t* node) {
  if (node == l->Head || node == l->Sentinel)
    return NULL;

  node->Prev->Next = node->Next;
  node->Next->Prev = node->Prev;

  node->Next = NULL;
  node->Prev = NULL;
  return node;
}

void
DListFree(dlist_t* l) {
  node_t *n;

  n = DListPopBack(l);

  while (n != NULL) {
    printf("Freeing %s\n", (char*)n->Val);
    free(n);
    n = DListPopBack(l);
  }

  free(l->Head);
  free(l->Sentinel);
  return;
}
