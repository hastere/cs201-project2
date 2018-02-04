/*
**
Created by Andrew Stere for use in Calculon
**
*/
#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"


typedef struct queueObject
{
    node *front;
    node *rear;
    int size;
} Queue;

extern Queue *createQueue();
extern void enQueue(Queue *q, node *v);
extern node *deQueue(Queue *q);

#endif
