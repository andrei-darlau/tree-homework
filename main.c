/* DARLAU Andrei - 315CB */

#include "functii.h"

int main(int argc, char *argv[]) {
    char cerinta = argv[1][2] - '0';
    char k = 0;

    FILE *input;
    FILE *output;


    if (cerinta != 2) {
        input = fopen(argv[2], "r");
        output = fopen(argv[3], "w");
    } else {
        sscanf(argv[2], "%hhd", &k);
        input = fopen(argv[3], "r");
        output = fopen(argv[4], "w");
    }

    // FILE *input = fopen("test.in", "r");
    // FILE *output = fopen("test.out", "w");
    // int cerinta = 4;
    // int k = 0;

    // arbore principal
    Tree arbore = (Tree) calloc(1, sizeof(Node));
    if (arbore == NULL)
        return 1;

    arbore->children[0] = (Tree) calloc(1, sizeof(Node));
    if (arbore->children[0] == NULL)
        return 1;

    arbore->children[0]->string = (char *)calloc(2, sizeof(char));
    if (arbore->children[0]->string == NULL)
        return 1;
    arbore->children[0]->string[0] = '$';

    int N = 0;
    fscanf(input, "%d\n", &N);

    int M = 0;
    if (cerinta == 3)
        fscanf(input, "%d\n", &M);

    for (int i = 0; i < N; i++) {
        char string[69];
        fscanf(input, "%68s", string);

        bool succesCerinta1 = buildTree(arbore, string);
        if (succesCerinta1 == false)
            return 1;
    }

    // fac un for separat pentru ca switch-ul sa fie mai compact
    char *suffixes = (char *)calloc(M, sizeof(char));
    for (int i = 0; i < M; i++) {
        char string[69];
        fscanf(input, "%68s\n", string);
        int len = strlen(string);
        string[len] = '$';
        string[len + 1] = '\0';
        suffixes[i] = checkSuffix(arbore, string);
    }

    int leafCer2 = 0;
    int suffK = 0;
    int descendants = 0;
    switch (cerinta) {
        case 1:
            printCerinta1(arbore, output);
            break;
        case 2:
            nrLeaves(arbore, &leafCer2);
            fprintf(output, "%d\n", leafCer2);
            suffDimK(arbore, k, 0, &suffK);
            fprintf(output, "%d\n", suffK);
            nrDescendants(arbore, &descendants);
            fprintf(output, "%d\n", descendants);
            break;
        case 3:
            printValues(suffixes, M, output);
            break;
        case 4:
            compressTree(arbore);
            printCerinta4(arbore, output);
            break;
    }

    free(suffixes);
    freeArbore(arbore);
    fclose(input);
    fclose(output);
}
