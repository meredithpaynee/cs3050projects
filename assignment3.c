#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"

//struct for creating linked lists, contains data, key, and next pointer
typedef struct Node{
    void * data;
    int key;
    struct Node * next;
}Node;

//creates node to add into linked list
Node * CreateNode(void * data, int key)
{
    Node * n = malloc(sizeof(Node));
    n->data = data;
    n->key = key;
    n->next = NULL;

    return n;
}


// These are stubs.  That is, you need to implement these functions.

int InsertFailCollision(void * hashtable, int elementSize, int elementCountMax, int key, void * element, int (*HashFunc)(int key))
{
    //create an index using passed in hash function
    int index = HashFunc(key);

    /*since the hashtable created in main is filled with 0s at initialization, this loop tests
    if the spot at index is empty or if there is a collision. memchr returns a pointer to the 
    matching byte (which we don't need), or NULL. If it returns NULL, then there is a not a 0 
    at the spot in the hashtable, a collision has occurred, and the function returns -1 (error
    case)*/
    for(int i = 0; i < elementSize; i++)
    {
        if (memchr(hashtable + (elementSize * index) + i, 0, 1) == NULL)
        {
            return -1;
        }
    }

    /*If there is not a collision, memcpy copies the passed in element to the spot in the hashtable*/
    memcpy(hashtable + (elementSize * index), element, elementSize);
    return 0;

}

void * SearchNoCollision(void * hashtable, int key, int elementSize, int (*HashFunc)(int key))
{
    //Index created using passed in hash function, return element at index in O(1) time
    int index = HashFunc(key);
    return hashtable + elementSize * index;
}


int DivMethod(int key)
{
    //create index based on key mod size of the hashtable and return
    int index = key % TABLESIZE;
	return index;
}

int MultMethod(int key)
{
    //create a value
    float a = (sqrt(5)-1)/2;
    //create index based on the size of hashtable, key, and a value and return
    int index = floor(TABLESIZE * (key * a - floor(key*a)));
    return index;
}


void * AllocateChainTable(int elementCountMax)
{
    /*creates a hashtable containing nodes that will not hold keys,
    but will just point to the linked list stored in that spot*/
    void * hashtable = malloc(sizeof(Node) * elementCountMax); 

    //return hashtable
    return hashtable;
}

void FreeChainTable(void * hashtable)
{
    //create traversal node and temp node
    Node * p, * temp;
    
    //for loop for hash table
    for (int i = 0; i < sizeof(hashtable)/sizeof(Node); i++)
    {
        //for loop for chain in hashtable spot
        for(p = hashtable + i; p->next != NULL; p = p->next)
        {
            //set temp to p->next so it isn't lost, free p, and set p to temp
            temp = p->next;
            free(p);
            p = temp;
            //printf("node freed\n");
        }
    }
}

int InsertChain(void * hashtable, int elementSize, int elementCountMax, int key, void * element, int (*HashFunc)(int key))
{
    //create an index with hash function, a node with element in it (a pointer to the customer structs in main), and a test variable
    int index = HashFunc(key);
    Node * n = CreateNode(element, key);
    int test = 1;

    for(int i = 0; i < elementSize; i++)
    {
        //if there isn't something at hashtable, test = 1, if there is, test = 0
        if (memchr(hashtable + sizeof(void *) * index + i, 0, 1) == NULL)
        {
            test = 0;
        }
    }

    //if there is something at hashtable, place node at "head" (after dummy node in hashtable) and move the other nodes up
    if (test == 0)
    {
        Node * temp = (hashtable + index * sizeof(void *));
        n->next = temp->next;
        temp->next = n;
        //printf("n key in node: %i\n", n->key);
    }

    //if there isnt something at hashtable, create a headnode, make it point to n, and put the head in the hashtable  
    else
    {
        Node * head = malloc(sizeof(void *));
        head->next = n;
        memcpy(hashtable + index * sizeof(void *), head, sizeof(Node)); //needs to be in n->data but memory?
        //printf("head key in node: %i\n", n->key);
    }  

    return test; //returning success or failure
}

void * SearchChain(void * hashtable, int key, int elementSize, int (*HashFunc)(int key))
{
    //printf("search chain?\n");
    //create index with hash and traversal node
    int index = HashFunc(key);
    Node * p;

    //go through chain, if p->key is equal to the key then return the satellite data
    for(p = hashtable + sizeof(void *) * index; p != NULL; p = p->next)
    {
        if (p->key == key)
        {
            return p->data;
        }
    }

    //otherwise return null
    return NULL;
}