#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int
main() {
  queue_t* queue = QueueInit();

  QueuePush(queue, (void*)"q1");
  QueuePush(queue, (void*)"q2");
  QueuePush(queue, (void*)"q3");
  QueuePush(queue, (void*)"q4");

  printf("Size: %d\n", queue->Size);

  QueueFree(queue);
  free(queue);
  return 0;
}
