#pragma once
#include "cache.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int
main() {
  lru_t* lru = LRUInit(5);

  return 0;
}
