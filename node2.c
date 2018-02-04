/*Various BST Node functions
By Andrew Stere
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"


struct node *newNode(char *key, node *p) {
    struct node *node = (struct node*) malloc(sizeof(struct node));
    node->parent = p;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;
    node->next = NULL;
    node->freq = 1;
    node->favors = "";
    return(node);
}
//messed up brackets - X conditional was in the R conditional
void printNode(node *n) {
  if(n->left == NULL && n->right == NULL)
    printf("=");
  node *l = NULL;
  l = n->parent->left;
  node *r = NULL;
  r = n->parent->right;
  printf("%s%s(%s%s)%i",n->key,n->favors,n->parent->key,n->parent->favors,n->freq);
  if (l != NULL) {
    int i = strcmp(l->key, n->key);
    if (i == 0)
    printf("L");
  }
  if (r != NULL) {
    int i = strcmp(r->key, n->key);
    if (i == 0)
      printf("R"); }
  else if (strcmp(n->parent->key,n->key) == 0)
    printf("X");

}

void ghostPrintNode(node *n) {
return;
}
