// You might want some more includes here
#include "MUCSGraph.h"
#include "Queue.h"
#include "BFS.h"
#include <stdlib.h>
#include <stdio.h>

// Implement your function here
void PrintBFS(Vertex * V, int countV, Edge * E, int countE, int s)
{
    printf("BFS: \n");
    //initialize queue, node for starter vertex
    Queue * q = initQueue();
    Node * n = createNode(s);
    //enqueue n into q
    enqueue(n, q);
    //create temp Node
    Node * u;

    while(q->head)
    {
        //dequeue into temp node, initialize temp vertex and create traversal for the adjacency list
        u = dequeue(q);
        Vertex * ver = V + u->num - 1;
        Adjacency * p;

        //for every vertex in adjacency list
        for (p = ver->list; p != NULL; p = p->next)
        {
            //test for if the edge is to or from
            int edge;
            if(p->pEdge->to == ver->number)
            {
                edge = p->pEdge->from;
            }
            else 
            {
                edge = p->pEdge->to; 
            }

            //pointer to adjacent vertex
            Vertex * adjacent = V + edge - 1;

            //if vertex is white
            if (adjacent->color == WHITE)
            {
                //change to grey, make predecessor ver, set distance to the predecessor's distance plus 1
                adjacent->color = GRAY;
                adjacent->predecessor = ver->number;
                adjacent->d = (V + (adjacent->predecessor) - 1)->d + 1;

                //create new node with adjacent vertex and enqueue it
                Node * new = createNode(adjacent->number);
                enqueue(new, q);
            }
        }

        //set ver to black (fully visited) and print
        ver->color = BLACK;
        printf("%d(%d) ", ver->number, ver->d);
        freeNode(u);
    }
    printf("\n\n");
    freeQueue(q);
}
