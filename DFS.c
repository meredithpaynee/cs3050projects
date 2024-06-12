// You might want some more includes here
#include "MUCSGraph.h"
#include "DFS.h"
#include <stdlib.h>
#include <stdio.h>

void DFSVisit(Vertex * V, Vertex * u, int * time)
{
    //set u color to grey
    u->color = GRAY;
    //increment time and set u's distance to time
    (*time)++;
    u->d = *time;
    //create variable to traverse adjacency list
    Adjacency * p;

    //for every vertice in the adjacency list
    for(p = u->list; p != NULL; p = p->next)
    {
        //test for if the edge is to or from
        int edge; 
        if(p->pEdge->to == u->number)
        {
            edge = p->pEdge->from;
        }
        else
        {
            edge = p->pEdge->to;
        }

        //variable for adjacent vertex
        Vertex * adjacent = V + edge - 1;

        //if the vertex hasn't been visited, visit it
        if(adjacent->color == WHITE)
        {
            DFSVisit(V, adjacent, time);
        }
    }

    //after it's been visited turn the vertex black
    u->color = BLACK;
    //increment time and set u's f to time
    (*time)++;
    u->f = *time;
    //print u
    printf("%d(%d) ", u->number, u->f);
}


// Implement your function here
void PrintDFS(Vertex * V, int countV, Edge * E, int countE)
{
    printf("DFS: \n");

    //vertex to traverse through V
    Vertex * u;
    int i = 0;

    while(i < countV)
    {
        //set all vertices to white
        u = V + i;
        u->color = WHITE;
        i++;
    }

    //reset u to beginning of V and time to 0
    u = V;
    int time = 0;
    i = 0;

    //for every vertex, go through and visit it if it is white
    while (i < countV)
    {
        u = V + i;

        if (u->color == WHITE)
        {
            DFSVisit(V, u, &time);
        }
        i++;
    }

    printf("\n\n");
}