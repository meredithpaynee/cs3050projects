#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include "bst.h"

// Local functions

//create new node to be assigned to BST
Node * NewNode(int key, void * data)
{
    Node * node = malloc(sizeof(Node));

    if (node)
    {
        node->key = key;
        node->data = data;
    }
    return node;
}

//find the minimum value in a tree by finding the leftmost BST
BST * TreeMin(BST * pBST)
{
    while(pBST->left != NULL)
    {
        pBST = pBST->left;
    }
    return pBST;
}

//Find the successor for a node (used in deletion)
BST * Successor(BST * pBST)
{
    //if there's nothing to the right, return the minimum value of the right branch
    if (pBST->right == NULL)
    {
        return TreeMin(pBST->right);
    }

    //create BST that is the pBSTs parent
    BST * y = pBST->parent;
    /*while the parent is not NULL and pBST is equal to the right branch of the parent,
    make y pBST and make y its own parent*/
    while (y != NULL && pBST == y->right)
    {
        y = pBST;
        y = y->parent;
    }
    return y;
}

//Simple traversal function that returns a pointer to a BST that has the key value
BST * Traversal(BST * pBST, long long key)
{
    if (pBST->node->key == key)
    {
        return pBST;
    }
    else if (key < pBST->node->key)
    {
        return Traversal(pBST->left, key);
    }
    else
    {
        return Traversal(pBST->right, key);
    }
}

//transplant function, used in deletion, that moves tree with root v to spot u
void Transplant(BST * pBST, BST * u, BST * v)
{
    //if the parent is null, pBST root is u and move v there
    if (u->parent == NULL)
    {
        pBST = v;
    }
    //else if u is the left branch of its parent, move v there
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    //else u is the right branch of its parent
    else
    {
        u->parent->right = v;
    }

    //assign parent
    if (v != NULL)
    {
        v->parent = u->parent;
    }
}

// These are stubs.  That is, you need to implement these functions.

BST * NewBST()
{
    //malloc for pBST
    BST * pBST = malloc(sizeof(BST));

    //if malloc is successful, assign values and return
    if (pBST)
    {
        pBST->left = NULL;
        pBST->right = NULL;
        pBST->parent = NULL;
        return pBST;
    }

    return NULL;
}

void TreeInsert(BST * pBST, void * satellite, long long key)
{
    //x is current BST, y is parent
    BST * x = pBST;
    BST * y = NULL;
    Node * n = NewNode(key, satellite);

    //while current is not NULL and its node is not NULL
    while (x != NULL && x->node != NULL)
    {
        //make parent point to current 
        y = x;
        //if n's key is less than current's key, make current its own left branch
        if (n->key < x->node->key)
        {
            x = x->left;
        }
        //else make current its own right branch
        else{
            x = x->right;
        }
    }

    //if parent is NULL or its node is NULL, assign n to current
    if (y == NULL || y->node == NULL)
    {
        x->node = n;
    }
    /*else if n's key is less than parent's key, create a new BST, 
    assign node to it, make its parent equal to parent, and make
    parent's left branch the new node*/
    else if (n->key < y->node->key)
    {
        BST * z = NewBST();
        z->node = n;
        z->parent = y;
        y->left = z;
    }
    /*else create a new node and do the same as above, except the right branch*/
    else
    {
        BST * z = NewBST();
        z->node = n;
        z->parent = y;
        y->right = z;
    }
    
}

//print in order
void InOrder(BST * pBST, NODEVISITFUNC func)
{
    if(pBST != NULL && pBST->node != NULL)
    {
        InOrder(pBST->left, func);
        func(pBST->node->data);
        InOrder(pBST->right, func);
    }
}

//print pre order
void PreOrder(BST * pBST, NODEVISITFUNC func)
{
    if(pBST != NULL && pBST->node != NULL)
    {
        func(pBST->node->data);
        PreOrder(pBST->left, func);
        PreOrder(pBST->right, func);
    }
}

//print post order
void PostOrder(BST * pBST, NODEVISITFUNC func)
{
    if(pBST != NULL && pBST->node != NULL)
    {
        PostOrder(pBST->left, func);
        PostOrder(pBST->right, func);
        func(pBST->node->data);
    }
}

void * Search(BST * pBST, long long key)
{
    //if the BST is NULL or key is equal to the root's key, return
    if (pBST == NULL || key == pBST->node->key)
    {
        return pBST->node->data;
    }

    //traverse left if key is less than root's
    if (key < pBST->node->key)
    {
        return Search(pBST->left, key);
    }
    //traverse right if key is greater than or equal to roots
    else
    {
        return Search(pBST->right, key);
    }

    return NULL;
}

void TreeDelete(BST * pBST, long long key)
{
    //create BST equivalent to the one that will be deleted
    BST * z = Traversal(pBST, key);
    
    //if there is no left branch, move z->right up to z
    if(z->left == NULL)
    {
        Transplant(pBST, z, z->right);
    }
    //else if there is no right branch, move z->left up to z
    else if (z->right == NULL)
    {
        Transplant(pBST, z, z->left);
    }
    //else if there is two children, find successor
    else
    {
        BST * y = Successor(z->right);

        //if the successor is the child of the BST getting deleted, move it up from right
        if(y->parent == z)
        {
            Transplant(pBST, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        //else move it up from left
        Transplant(pBST, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}