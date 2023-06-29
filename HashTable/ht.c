#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"

int 
main() {
  htable_t* ht = HTCreate(20);

  HTInsert(ht, "Jacob", "Jacob node");
  HTInsert(ht, "Natalie", "Natalie node");
  HTInsert(ht, "Will", "Will node");
  HTInsert(ht, "Alex", "Alex node");
  HTInsert(ht, "Cade", "Cade node");
  HTInsert(ht, "John", "John node");
  HTInsert(ht, "Maddox", "Maddox node");
  HTInsert(ht, "Anna", "Anna node");
  HTInsert(ht, "Sonaz", "Sonaz node");
  HTInsert(ht, "Asal", "Asal node");
  HTInsert(ht, "Mary", "Mary node");
  HTInsert(ht, "Hamm", "Hamm node");

//  htnode_t* tmp;
//  tmp = HTFind(ht, "Sonaz");
//  if (tmp != NULL) {
//    printf("found sonaz\n");
//  } else {
//    printf("did not find sonaz\n");
//  }

  HTPrint(ht);
  printf("-----------\n");  
  htnode_t* tmp = HTDeleteNode(ht, "Sonaz");
  printf("tmp: %s\n", (char*)tmp->Data);

  HTPrint(ht);
  free(tmp);
  HTFree(ht);
  free(ht);
  return 0;
}
