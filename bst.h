#ifndef BST_H
#define BST_H
#include "node.h"
 typedef struct bst {
   node *root;
 } bst;
extern struct bst *createBST(void);
extern void insertBST(bst *, char *);
extern struct node *search(struct node*, char *);
extern void deleteBST(bst *, char *);
extern node *insertNode(node *, char *);
extern node *successorSwap(node *);
int maxDepth(struct node* node);
int minDepth(struct node* node);
unsigned int count(struct node* node);
void prune(node *);
void printTree(node *);
void ghostPrintTree(node *);
#endif
