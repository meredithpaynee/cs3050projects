#ifndef _QUEUE_H
#define _QUEUE_H
#include "MUCSGraph.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" 
{
#endif

// Data types
//node structure contains a next pointer and a number for a vertex
typedef struct nodestruct{
    struct nodestruct * next;
    int num;
}Node;

//queue contains two pointers to the head and tail
typedef struct {
    Node * head;
    Node * tail;
}Queue;

//Prototypes
Queue * initQueue();
Node * createNode(int num);
void enqueue(Node * n, Queue * q);
Node * dequeue(Queue * q);
void freeQueue(Queue * q);
void freeNode(Node * n);




#ifdef __cplusplus
}
#endif

#endif