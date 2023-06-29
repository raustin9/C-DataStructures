/*
 *  Hash Table Implimentation and Structure in C
 *
 *  This is my implimentation of a hash table that uses the 
 *  SDBM hashing algorithm and quadratic probing.
 *
 *  There are a number of helper functions to aid
 *  the user in using the hash table
 *
 *  IMPORTANT NOTES:
 *    Calling the HTFree() function frees the nodes of the hash table but not the table itself
 *    If htnode->Data points to somewhere on the heap, HTFree() will not free that memory
 */

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct HTNode {
  const char* Key;
  void* Data;


} htnode_t;

// Structure for the hash table itself
typedef struct HashTable {
  uint32_t TableSize;
  htnode_t** Elements;
} htable_t;


/// PROTOTYPES ///
htable_t* HTCreate(uint32_t table_size);
void HTFree(htable_t* ht);
htnode_t* HTGet(htable_t* ht, const char* key);
htnode_t* HTSet(htable_t* ht, const char* key, void* data);
uint64_t HTLength(htable_t* ht);
uint64_t HTHash(htable_t* ht, const char* key);
void HTPrint(htable_t* ht);
int HTInsert(htable_t* ht, const char* key, void* data);
htnode_t* HTFind(htable_t* ht, const char* key);
htnode_t* HTDeleteNode(htable_t* ht, const char* key);

// The Hash function
// Takes a key as input and produces
// a uint64_t as output
// Uses the SBDM hash function
uint64_t 
HTHash(htable_t* ht, const char* key) {
  uint64_t hash_value;
  int32_t c;

  hash_value = 0;
  while (c = *key++)
    hash_value = c + (hash_value << 6) + (hash_value << 16) - hash_value;

  return hash_value % ht->TableSize;
}

// Constructor for a new hash table with the desired size
htable_t*
HTCreate(uint32_t table_size) {
  htable_t* ht;

  ht = (htable_t*)malloc(sizeof(htable_t));

  ht->TableSize = table_size;
  ht->Elements = (htnode_t**)malloc(sizeof(htnode_t*) * table_size);;

  for (int i = 0; i < table_size; i++) {
    ht->Elements[i] = NULL;
  }

  return ht;
}

// Frees all elements in the hash table
// DOES NOT FREE THE TABLE ITSELF
// DOES NOT FREE MEMORY POINTED TO BY THE ELEMENTS
void
HTFree(htable_t* ht) {
  uint64_t i;

  for (i = 0; i < ht->TableSize; i++) {
    free(ht->Elements[i]);
  }

  free(ht->Elements);
}

// Iterates through the table and prints out each element's key
void
HTPrint(htable_t* ht) {
  uint64_t i;

  for (i = 0; i < ht->TableSize; i++) {
    if (ht->Elements[i] != NULL) {
      printf(" - %s\n", (char*)ht->Elements[i]->Key);
    } else {
      printf("- NULL\n");
    }
  }
}

// Inserts a node in the hash table with its associated key
// Uses quadratic probing for collisions
int
HTInsert(htable_t* ht, const char* key, void* data) {
  htnode_t* node;
  uint64_t index;

  node = (htnode_t*)malloc(sizeof(htnode_t));
  if (node == NULL) return -1;

  node->Data = data;
  node->Key = key;

  index = HTHash(ht, key);

  if (ht->Elements[index] == NULL) {
    ht->Elements[index] = node;
  } else {
    // Quadratic probing
    uint64_t i;
    for (i = 0; i < ht->TableSize; i++) {
      uint64_t t = (index + i*i) % ht->TableSize;
      if (ht->Elements[t] == NULL) {
        ht->Elements[t] = node;
        return 1;
      }
    }
    free(node);
    return -1;
  }

  return 1;
}

// Finds and returns a node at the desired key in the 
// hash table if it exists
htnode_t*
HTFind(htable_t* ht, const char* key) {
  uint64_t index;

  index = HTHash(ht,key);
  
  if (ht->Elements[index] != NULL && strcmp(ht->Elements[index]->Key, key) == 0) {
    return ht->Elements[index];
  } else if (ht->Elements[index] != NULL && strcmp(ht->Elements[index]->Key, key) != 0) {
    // Quadratic Probing
    uint64_t i;
    for (i = 0; i < ht->TableSize; i++) {
      uint64_t t = (index + i*i) % ht->TableSize;
      if (ht->Elements[t] != NULL && strcmp(ht->Elements[i]->Key, key) == 0) {
        return ht->Elements[t];
      }
    }
    return NULL;
  } else {
    return NULL;
  }
}

// Deletes node at a key
// Uses quadratic probing for collisions
htnode_t*
HTDeleteNode(htable_t* ht, const char* key) {
  uint64_t index;
  htnode_t* node;

  index = HTHash(ht, key);

  if (ht->Elements[index] == NULL) {
    node = NULL;
  } else {
    if (strcmp(ht->Elements[index]->Key, key) == 0) {
      node = ht->Elements[index];
      ht->Elements[index] = NULL;
    } else {
      // Run into a collision
      uint64_t i;
      node = NULL;
      for (i = 0; i < ht->TableSize; i++) {
        uint64_t t = (index + i*i) % ht->TableSize;
        if (ht->Elements[t] != NULL && strcmp(ht->Elements[t]->Key, key) == 0) {
          node = ht->Elements[t];
          ht->Elements[t] = NULL;
          break;
        }
      }
    }
  }

  return node;
}
