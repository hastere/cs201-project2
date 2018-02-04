/*
AVL code for self balancing search tree
by Andrew Stere
*/

#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static void insertFix(bst *, node *);
static void delFix(bst *a, node *);
static void setBal(node *);
static node *getSib(node *);
static int isLinear(node *, node *, node *);
static void rotateUp(bst *, node *);
node *getFavChild(node *);


void insertAVL(bst *a , char *word) {
  if(a->root->key == NULL) {
    a->root = newNode(word, 0);
    a->root->parent = a->root;
  }
  else {
    insertFix(a, insertNode(a->root, word));
  }
}

void deleteAVL(bst *a , char *word) {
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
    delFix(a, n);
    if (n == a->root)
      a->root = 0;
    else
      prune(n);
  }
}

static void insertFix(bst *a, node *i) {
  if(!i)
    return;
  while (i != a->root) {
    if (getFavChild(i->parent) && getFavChild(i->parent) == getSib(i)) {
      setBal(i->parent);
      return;
    }
    else if (!getFavChild(i->parent)) {
      setBal(i->parent);
      i = i->parent;
    }
    else {
      node *fav = getFavChild(i);
      node *parent = i->parent;
      if(fav && !isLinear(fav, i, parent)) {
        rotateUp(a, fav);
        rotateUp(a, fav);
        setBal(i);
        setBal(parent);
        setBal(fav);
      }
      else {
        rotateUp(a, i);
        setBal(parent);
        setBal(i);
      }
      return;
    }
  }
}

static void delFix(bst *a, node *d) {
  d->height = 0;
  while(d != a->root) {
    if(getFavChild(d->parent) == d) {
      setBal(d->parent);
      d = d->parent;
    }
    else if(!getFavChild(d->parent)) {
      setBal(d->parent);
      return;
    }
    else {
      node *parent = d->parent;
      node *sib = getSib(d);
      node *fav = getFavChild(sib);
      if(fav && !isLinear(fav, sib, parent)) {
        rotateUp(a, fav);
        rotateUp(a, fav);
        setBal(parent);
        setBal(sib);
        setBal(fav);
        d = fav;
      }
      else {
        rotateUp(a, sib);
        setBal(parent);
        setBal(sib);
        if(!fav) return;
        d = sib;
      }
    }
  }
}

int max(int a, int b) {
  return a > b ? a : b;
}

static void setBal(node* n) {
  int left = maxDepth(n->left);//n->left ? n->left->height : 0;
  int right = maxDepth(n->right);//n->right ? n->right->height : 0;

  n->height = max(left, right) + 1;
  if (left == right) {
    n->favors = "";
  }
  else if (left > right) {
    n->favors = "-";
  }
  else {
    n->favors = "+";
  }
}

static node *getSib(node *n) {
  if(n == n->parent->left)
    return n->parent->right;
  else
    return n->parent->left;
}

static int isLinear(node *child, node* n, node *p) {
  return((p->left == n && n->left == child) || (p->right == n && n->right == child));
}

node *getFavChild(node *n) {
  if(strcmp(n->favors, "-") == 0)
    return n->left;

  else if(strcmp(n->favors, "+") == 0)
    return n->right;
  else
    return NULL;
}

static void rotateUp(bst *a, node *n) {
  node *parent = n->parent;
  node *gp = parent->parent;
  node *i;
  if(n == n->parent->left) {
    i = n->right;
    n->right = parent;
    parent->left = i;
  }
  else {
    i = n->left;
    n->left = parent;
    parent->right = i;
  }
  parent->parent = n;
  if(i) i->parent = parent;
  if(parent == a->root) {
    a->root = n;
    n->parent = n;
  }
  else {
    if(gp->left == parent) gp->left = n;
    else gp->right = n;
    n->parent = gp;
  }
}
