/* DARLAU Andrei - 315CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ASCII 96
// astfel incat 1 = a - ASCII

typedef struct node {
    char *string;
    struct node *children[27];
} Node, *Tree;


bool buildTree(Tree, char*);
bool addLeaf(Tree, char);
void printCerinta1(Tree, FILE*);
void freeArbore(Tree);
void nrLeaves(Tree, int*);
void suffDimK(Tree, int, int, int*);
void nrDescendants(Tree, int*);
char checkSuffix(Tree, char*);
void printValues(char*, int, FILE*);
void compressTree(Tree);
void printCerinta4(Tree, FILE*);
