/*
 *  This is an implimentation for cacheing based on strings (char*)
 *  
 *  This cache uses a Least Recently Used (LRU) algorithm
 *
 */

#pragma once
#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Nodes that go in the LRU
typedef struct CNode {
  struct CNode *Next;
  struct CNode *Prev;

  char* Data;
} cnode_t;

// Structure for the LRU cache itself
typedef struct LRUCache {
  cnode_t *Head;
  cnode_t *Rear;

  uint64_t Capacity;
  uint64_t Size;
} lru_t;

lru_t*
LRUInit(uint64_t capacity) {
  lru_t* lru = NULL;

  lru = (lru_t*)malloc(sizeof(lru_t));
  if (lru == NULL) {
    return NULL;
  }

  cnode_t *head = NULL;
  
  head = (cnode_t*)malloc(sizeof(cnode_t));
  if (head == NULL) {
    return NULL;
  }
  head->Prev = NULL;
  head->Next = NULL;

  lru->Head = head;
  lru->Rear = head;

  lru->Capacity = capacity;
  lru->Size = 0;

  return lru;
}

// Insert a node with desired string into
// the LRU
// If the string is already in the LRU, move that node to the front and shift the rest
cnode_t*
LRUInsertString(lru_t* lru, char* data) {
  cnode_t* cur = lru->Head;
  cnode_t* node;
  //for (cur = lru->Head; cur != NULL || cur != lru->Rear; cur = cur->Next) {
    
  //}

  // Insert node at top of cache
  node = (cnode_t*)malloc(sizeof(cnode_t));
  node->Data = data;

  node->Next = lru->Head;
  node->Prev = NULL;

  lru->Head->Prev = node;
  lru->Head = node;

  

  return node;
}

