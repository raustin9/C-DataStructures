#include <stdio.h>
#include <stdlib.h>
#include "threadpool.h"

void*
Action(void* args) {
  printf("thread created\n");
  return NULL;
}

int 
main() {
  tpool_t* pool = ThreadPoolInit(10, Action);

  char* string = "test string";
  ThreadPoolStart(pool, NULL);

  printf("Num threads: %d\n", pool->NumThreads);

  ThreadPoolJoin(pool);
  free(pool);
}
