#ifndef QUEUE_H
#define QUEUE_H

#include "linkedlist/linkedlist.h"
typedef struct linkedlist queue;

queue * new_queue();
void queue_enqueue(queue *queue, void* ptr);
void *queue_dequeue(queue *queue);
void queue_delete_first(queue *queue);
void queue_free(queue *queue, int item_type);

#endif // !QUEUE_H
