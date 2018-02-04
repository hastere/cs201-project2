/*
Code for binary search tree functions and statistics
By Andrew Stere
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "node.h"
#include "queue.h"
#include "bst.h"

node *insertNode(node *, char *);
void prune(node *);
node *successorSwap(node *);

// A utility function to create a new BST node
bst *createBST(void) {
  bst *b = (bst *)malloc(sizeof(bst));
  b->root = newNode(NULL, NULL);
  return b;
}
void insertBST(bst *b, char *w) {
  if(b->root->key == NULL){
    b->root = newNode(w, 0);
    b->root->parent = b->root;
  }
  else {
    insertNode(b->root, w);
  }
}

node *insertNode(node *curr, char *w) {
  int cmp = strcmp(w, curr->key);
  if(cmp == 0) {
    curr->freq++;
    return 0;
  }
  else if(cmp < 0) {
    if(!curr->left) {
      curr->left = newNode(w, curr);
      curr->left->parent = curr;
      return curr->left;
    }
    else
      return insertNode(curr->left, w);
  }
  else {
    if(!curr->right) {
      curr->right = newNode(w, curr);
      curr->right->parent = curr;
      return curr->right;
    }
    else
      return insertNode(curr->right, w);
  }
}

node *search(node *node, char *token) {
  if(node == NULL) {
    return 0;
  }
  if (strcmp(token,node->key) > 0){
    return search(node->right,token);
  }
  else if (strcmp(token,node->key) < 0) {
    return search(node->left,token);
  }
  else
    return node;

}

void deleteBST(bst *a , char *word) {
  node *n = search(a->root, word);
  if(n == NULL) {
    fprintf(stderr, "Unable to delete node: %s\n", word);
    return;
  }
  if (n->freq > 1)
    n->freq--;
  else {
    while(n->left || n->right) {
      n = successorSwap(n);
    }
    if (n == a->root)
      a->root = 0;
    else
      prune(n);
  }
}

node *findSuccessor(node *n) {
  if(n->right) {
    n = n->right;
    while(n->left) {
      n = n->left;
    }
    return n;
  }
  node *parent = n->parent;
  while(parent != parent->parent && n == parent->right) {
    n = parent;
    parent = parent->parent;
  }
  return parent;
}

int maxDepth(struct node* node){
   if (node==NULL)
       return -1;
   else
   {
       /* compute the depth of each subtree */
       int lDepth = maxDepth(node->left);
       int rDepth = maxDepth(node->right);

       /* use the larger one */
       if (lDepth > rDepth)
           return(lDepth+1);
       else return(rDepth+1);
   }
}

//Issues with copy/paste shit (god im an idiot for turning this in)
int minDepth(struct node* node){
   if (node==NULL)
       return -1;
   else
   {
       /* compute the depth of each subtree */
       int lDepth = minDepth(node->left);
       int rDepth = minDepth(node->right);

       /* use the larger one */
       if (lDepth < rDepth)
           return(lDepth+1);
       else return(rDepth+1);
   }
}
unsigned int count(struct node* node) {
  if(node == NULL)
    return 0;
  else
    return count(node->left)+count(node->right)+1;
}


node *successorSwap(node *n) {
  node *succ = findSuccessor(n);
  char *x = succ->key;
  int fr = succ->freq;
  succ->key = n->key;
  n->key = x;
  n->freq = fr;
  return succ;
}

void prune(node *n) {
  if(n->parent->left == n)
    n->parent->left = 0;
  else
    n->parent->right = 0;
}

void printTree(node *root) {
  int level = 0;
  int x = 0;
  Queue *q = createQueue();
  if(root)
    enQueue(q, root);
  else
    printf("Empty Tree\n");
  while(q->size > 0) {
    printf("%i: ", level);
    int nodes = q->size;
    while(nodes > 0) {
      node *n = deQueue(q);
      printNode(n);
       if(n->left)
         enQueue(q, n->left);
       if(n->right)
         enQueue(q, n->right);
      printf(" ");
    nodes--;
    }
    level++;
    printf("\n");
  }
  printf("\n");
}

void ghostPrintTree(node *root) {
  int level = 0;
  Queue *q = createQueue();
  if(root)
    enQueue(q, root);
  else
  while(q->size > 0) {
    int nodes = q->size;
    while(nodes > 0) {
      node *n = deQueue(q);
      printNode(n);
       if(n->left)
         enQueue(q, n->left);
       if(n->right)
         enQueue(q, n->right);
    nodes--;
    }
    level++;
  }
}
