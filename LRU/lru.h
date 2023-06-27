/*
 *  LRU Cache Implimentation
 *
 *  This is a Least Recently Used Cache implimentation in C
 *  
 */

#include <stdint.h>

typedef struct CNode {
  struct CNode *next, *prev;
  void *Data;
} cnode_t;

typedef struct LRUCache {
  cnode_t *Head;     // Head node of cache
  cnode_t *Rear;     // Rear node of cache
  uint64_t Capacity; // Maximum capacity of the cache
  uint64_t Size;     // Current number of elements in the cache
} lru_t;


