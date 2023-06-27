#pragma once

#include <cstdint>
#include <stdlib.h>
#include <stdint.h>

typedef struct HashTable {
  uint32_t TableSize;
  void** Elements;
} htable_t;


/// PROTOTYPES ///
htable_t* init_hash_table(uint32_t table_size);

// Constructor for a new hash table with the desired size
htable_t*
init_hash_table(uint32_t table_size) {
  htable_t* ht;

  ht = (htable_t*)malloc(sizeof(htable_t));

  ht->TableSize = table_size;
  *ht->Elements = (void*)malloc(table_size);
  return ht;
}


