/*
**
Created by Andrew Stere for use in trees
**
*/
#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "queue.h"

Queue *createQueue()
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

void enQueue(Queue *q, node *v)
{
    node *temp = v;
    if (q->front == NULL)
    {
       q->front = temp;
       q->rear = temp;
       q->size = 1;
       return;
    }
    q->rear->next = temp;
    q->rear = temp;
    q->size++;
}

node *deQueue(Queue *q)
{
    if (q->front == NULL)
    {
      return NULL;
    }

    node *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
    {
       q->rear = NULL;
    }
    q->size--;
    return temp;
}
