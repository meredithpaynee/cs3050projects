#ifndef _bst_h
#define _bst_h

//node struct
typedef struct {
    int key;
    void * data;
}Node;

//BST struct
typedef struct _BST{
    Node * node;
    struct _BST * left;
    struct _BST * right;
    struct _BST * parent;
} BST;

typedef void (*NODEVISITFUNC)(void * parm);

// Prototypes
BST * NewBST();
void TreeInsert(BST * pBST, void * satellite, long long key);
void InOrder(BST * pBST, NODEVISITFUNC func);
void PreOrder(BST * pBST, NODEVISITFUNC func);
void PostOrder(BST * pBST, NODEVISITFUNC func);
void * Search(BST * pBST, long long key);
void TreeDelete(BST * pBST, long long key);
BST * TreeMin(BST * pBST);
BST * Traversal(BST * pBST, long long key);
void Transplant(BST * pBST, BST * u, BST * v);
Node * NewNode(int key, void * data);
BST * Successor(BST * pBST);



#endif
