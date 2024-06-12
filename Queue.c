#include "Queue.h"


//initialize a queue
Queue * initQueue()
{
    Queue * q = malloc(sizeof(Queue));

    if (q)
    {
        q->head = NULL;
        q->tail = NULL;
    }

    return q;
}

//create a node containing the number of a vertex
Node * createNode(int num)
{
    Node * n = malloc(sizeof(Node));

    if (n)
    {
        //n->v = v;
        n->next = NULL;
        n->num = num;
    }

    return n;
}

//enqueue a node
void enqueue(Node * v, Queue * q)
{
    //Node * n = createNode(v);
    if (q->head == NULL)
    {
        q->head = v;
        q->tail = v;
    }
    else
    {
        q->tail->next = v;
        q->tail = v;
    }
}

//dequeue a node and return a pointer to it
Node * dequeue(Queue * q)
{
    if (q->head == NULL)
    {
        return NULL;
    }

    Node * temp;
    temp = q->head;
    q->head = q->head->next;

    return temp;
}

//free a queue
void freeQueue(Queue * q)
{
    Node * ptr;
    for (ptr = q->head; ptr != NULL; ptr = q->head)
    {
        q->head = q->head->next;
        free(ptr);
    }
}

//free a node
void freeNode(Node * n)
{
    free(n);
}
