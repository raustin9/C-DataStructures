/*
 *  This file contains the structure and implimentation 
 *  for a FIFO queue in C
 *
 *  A node in this queue contains a Data field that 
 *  allows the user to put a pointer to their desired data
 *
 *  There are a number of helper functions that allow the user to 
 *  interact with the queue. 
 *
 *  The only way to insert an item into the queue is to use QueuePush()
 *  which will append it to the back of the queue. The only way to remove
 *  from the queue is to use QueuePop(), and this will return and remove the
 *  top item from the queue.
 *
 */

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct Node {
  void* Data;
  struct Node* Next;
} qnode_t;

typedef struct Queue {
  qnode_t* Head;
  qnode_t* Rear;
  uint32_t Size;
} queue_t;

/// PROTOTYPES ///
queue_t* QueueInit();
qnode_t* QueuePush(queue_t* queue, void* data);
qnode_t* QueuePop(queue_t* queue);
void QueueFree(queue_t* queue);

/// FUNCTION IMPLIMENTATIONS ///
queue_t*
QueueInit() {
  queue_t* q;
  q = (queue_t*)malloc(sizeof(queue_t));
  if (q == NULL)
    return NULL;

  q->Head = NULL;
  q->Rear = NULL;
  q->Size = 0;

  return q;
}

// Creates a node from the given data
// and appends it to the end of the queue
qnode_t*
QueuePush(queue_t* queue, void* data) {
  qnode_t* node;
  node = (qnode_t*)malloc(sizeof(qnode_t));

  node->Data = data;
  node->Next = NULL;

  if (queue->Rear == NULL) {
    queue->Head = node;
  } else {
    queue->Rear->Next = node;
  }

  queue->Rear = node;
  queue->Size++;

  return node;
}

// Pops the first element off of the 
// front of the queue and returns it
// Returns NULL if queue is empty
qnode_t*
QueuePop(queue_t* queue) {
  if (queue->Head == NULL) {
    // Queue is empty
    return NULL;
  } else {
    qnode_t* node = queue->Head;
    queue->Head = queue->Head->Next;

    if (queue->Head == NULL) {
      queue->Rear = NULL;
    }
    queue->Size--;
    return node;
  }
}

void
QueueFree(queue_t* queue) {
  qnode_t* node;

  node = QueuePop(queue);

  while (node != NULL) {
    printf("Freeing %s\n", (char*)node->Data);
    free(node);
    node = QueuePop(queue);
  }

  free(queue->Head);
  free(queue->Rear);
  return;
}
