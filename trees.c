/*Main body for trees program
By Andrew Stere
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "node.h"
#include "bst.h"
#include "scanner.h"
#include "avl.h"
/* options */
int tree = 0;    // option -a/-b
int fileRead = 0;

char *processToken(char *);
void bstStuff(FILE *, FILE *);
void avlStuff(FILE *, FILE *);
void ProcessOptions(int , char **);
void Fatal(char *, ...);
void report(bst *);

int main(int argc,char **argv) {
    //Process Options from input
  ProcessOptions(argc,argv);
  FILE *corpus = fopen(argv[2],"r");
  if (corpus == NULL) {
      Fatal("Unable to open file for read");
    }
  FILE *instr = fopen(argv[3],"r");
  if (instr == NULL) {
      Fatal("Unable to open file for read");
  }

  if (tree == 0)
    bstStuff(corpus,instr);
  else if (tree == 1)
    avlStuff(corpus,instr);
  return 0;
}

// Changes Made
// 1. delete logic for nodes w/freq < 1 was included in logic for nodes
//    w/freq > 1
// 2. misc problems with reading double quoted strings from the instr file
//    mostly stringpending
// 3. using strlen to check empty strings instead of comparing to NULL
void bstStuff(FILE *corpus, FILE *instr) {
  char *token;
  bst *bstree = createBST();
  node *temp;
  if (stringPending(corpus)) token = readString(corpus);
  else token = readToken(corpus);

  while (!feof(corpus)){
    token = processToken(token);
    if (strlen(token) != 0) {
      insertBST(bstree, token);
    }
    if (stringPending(corpus))
      token = readString(corpus);
    else
      token = readToken(corpus);
  }

  if (stringPending(instr))
    token = readString(instr);
  else
    token = readToken(instr);

  while (!feof(instr)) {
    token = processToken(token);
    if (strcmp(token,"i") == 0) {
      token = processToken(readToken(instr));
      if(strlen(token) != 0) {
        insertBST(bstree, token);
      }
    }
    else if (strcmp(token,"d") == 0) {
      if (stringPending(instr))
        token = readString(instr);
      else
        token = readToken(instr);
      token = processToken(token);
      if (strlen(token) != 0)
        deleteBST(bstree, token);

    }
    else if (strcmp(token,"f") == 0) {
      token = processToken(readToken(instr));
      if (token != NULL) {
        temp = search(bstree->root, token);
        if (temp != NULL)
          printf("\n%s is found %d times in the tree\n", temp->key, temp->freq);
        else
          printf("\n%s is not found in the tree\n", token);
      }
    }
    else if (strcmp(token,"s") == 0) {
      ghostPrintTree(bstree->root);
      printTree(bstree->root);
     }
    else if (strcmp(token,"r") == 0) {
      report(bstree);
    }
    else
      Fatal("Unknown Command.");
    if (stringPending(instr))
      token = readString(instr);
    else
      token = readToken(instr);
  }
}

void avlStuff(FILE *corpus, FILE *instr) {
  char *token;
  bst *bbstree = createBST();
  node *temp;
  if (stringPending(corpus))
    token = readString(corpus);
  else
    token = readToken(corpus);
  while (!feof(corpus)){
    token = processToken(token);
    if (strlen(token) != 0) {
      insertAVL(bbstree, token);
    }
    if (stringPending(corpus))
      token = readString(corpus);
    else
      token = readToken(corpus);
  }
  if (stringPending(instr))
    token = readString(instr);
  else
    token = readToken(instr);
  while (!feof(instr)) {
    processToken(token);
    if (strcmp(token,"i") == 0) {
      token = processToken(readToken(instr));
      if (strlen(token) != 0)
        insertAVL(bbstree, token);
    }
    else if (strcmp(token,"d") == 0)
      deleteAVL(bbstree, processToken(readToken(instr)));
    else if (strcmp(token,"f") == 0) {
      token = processToken(readToken(instr));
      temp = search(bbstree->root, token);
      if (temp != NULL)
        printf("\n%s is found %d times in the tree\n", temp->key, temp->freq);
      else
        printf("\n%s is not found in the tree\n", token);
    }
    else if (strcmp(token,"s") == 0) {
      ghostPrintTree(bbstree->root);
      printTree(bbstree->root);
     }
    else if (strcmp(token,"r") == 0) {
      report(bbstree);
    }
    else
      Fatal("Unknown Command.");
    if (stringPending(instr))
      token = readString(instr);
    else
      token = readToken(instr);
  }
}

void report(bst *b){
  if(b->root == NULL) {
    printf("Empty Tree!\n");
    return;
  }
  printf("Distance from root to furthest node ");
  printf("w/a null child: %i\n", (maxDepth(b->root)));
  printf("Distance from root to closest node ");
  printf("w/a null child: %i\n", (minDepth(b->root)));
  printf("Number of nodes in tree: %i\n", count(b->root));

}
//modified tolower, isAlpha
char *processToken(char *token) {
  int length, c, d;
  char *start;
  c = d = 0;
  length = strlen(token);
  start = (char*)malloc(length+1);
  if (start == NULL)
       Fatal("Failure to allocate new array");
  //TODO NEEDS TO REMOVE ALL SPACES
  while (token[c] != '\0') {
    if (isspace(token[c])) {
        int temp = c + 1;
        if (token[temp] != '\0') {
          while (isspace(token[temp]) && token[temp] != '\0') {
              if (isspace(token[temp])) {
                 c++;
              }
              temp++;
           }
        }
        start[d] = tolower(token[c]);
        c++;
        d++;
     }
    else if (!isalpha(token[c]))
      c++;
    else {
      start[d] = tolower(token[c]);
      c++;
      d++;
    }
  }
  start[d]= '\0';
  return start;
}

void ProcessOptions(int argc, char **argv) {
  int argIndex = 1;

  while (argIndex < argc) {
    if (strcmp(argv[argIndex], "-a") == 0)
      tree = 1;
    else if (strcmp(argv[argIndex], "-b") == 0) {
      tree = 0;
      return;
    }
    ++argIndex;
  }
  return;
}

void Fatal(char *fmt, ...) {
  va_list ap;
  fprintf(stderr,"An error occured: ");
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  exit(-1);
}
