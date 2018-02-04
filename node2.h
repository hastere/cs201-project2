#ifndef NODE_H
#define NODE_H

typedef struct node
{
    char *key;
    struct node *left;
    struct node *right;
    struct node *parent;
    struct node *next;
    int height;
    int freq;
    char *favors;
} node;

struct node* newNode(char *, node *);
void printNode(node *);
void ghostPrintNode(node *);
#endif
