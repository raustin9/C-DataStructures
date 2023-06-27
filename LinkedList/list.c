#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>

// This is just to test the 
// functionality of the Dlist library I made
int
main() {
  dlist_t* list;

  list = DListInit();

  DListPush(list, (void*)"v1");
  DListPush(list, (void*)"v2");
  DListPush(list, (void*)"v3");
  DListPush(list, (void*)"v4");
  DListPush(list, (void*)"v5");
  DListPush(list, (void*)"v6");
  DListPush(list, (void*)"v7");

  DListPrint(list, 0);
  DListFree(list);

  free(list);
}
