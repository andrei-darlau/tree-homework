/* DARLAU Andrei - 315CB */

#include "functii.h"

bool addLeaf(Tree arbore, char info) {
    if (info == '$') {
        if (arbore->children[0] == NULL) {
            arbore->children[0] = (Tree)calloc(1, sizeof(Node));
            if (arbore->children[0] == NULL)
                return false;
            arbore->children[0]->string = (char *)calloc(2, sizeof(char));
            if (arbore->children[0]->string == NULL)
                return false;
            arbore->children[0]->string[0] = '$';
        }
    } else if (arbore->children[info - ASCII] == NULL) {
        char c = info - ASCII;
        arbore->children[c] = (Tree)calloc(1, sizeof(Node));
        if (arbore->children[c] == NULL)
            return false;
        arbore->children[c]->string = (char *)calloc(2, sizeof(char));
        if (arbore->children[c]->string == NULL)
            return false;
        arbore->children[c]->string[0] = info;
    }

    return true;
}

bool buildTree(Tree arbore, char *string) {
    int len = strlen(string);

    for (int i = 0; i < len; i++) {
        char *suffix = string + i;

        Tree curr = arbore;

        for (int j = 0; j < strlen(suffix); j++) {
            char info = suffix[j];

            bool succesAddLeaf = addLeaf(curr, info);
            if (succesAddLeaf == false)
                return false;
            curr = curr->children[info - ASCII];
        }
        bool succesAdd$ = addLeaf(curr, '$');
        if (succesAdd$ == false)
            return false;
    }

    return true;
}

void printCerinta1(Tree arbore, FILE *output) {
       if (arbore == NULL)
        return;

    // coada de adaugat elementele de la nivelul urm
    Tree queue[1000];
    int fata = 0, spate = 1;
    queue[spate] = arbore;

    while (fata < spate) {
        int nrNivelCurrent = spate - fata;
        bool hasCharacter = false;
        // pentru a nu incepe cu un newline

        // printam nivelul curent
        for (int i = 0; i < nrNivelCurrent; i++) {
            fata++;
            Tree current = queue[fata];
            if (current->string) {
                fprintf(output, "%c ", current->string[0]);
                hasCharacter = true;
            }

            // adaugam in queue plozii
            for (int j = 0; j < 27; j++) {
                if (current->children[j]) {
                    spate++;
                    queue[spate] = current->children[j];
                }
            }
        }

        if (hasCharacter == true)
            fprintf(output, "\n");
    }
}

void freeArbore(Tree arbore) {
    if (arbore == NULL)
        return;
    if (arbore->string)
        free(arbore->string);

    for (int i = 0; i < 27; i++)
        freeArbore(arbore->children[i]);
    free(arbore);
}

void nrLeaves(Tree arbore, int *leaves) {
    if (arbore == NULL)
        return;
    bool leaf = true;
    for (int i = 0; i < 27; i++) {
        if (arbore->children[i]) {
            leaf = false;
            nrLeaves(arbore->children[i], leaves);
        }
    }
    if (leaf == true)
        (*leaves)++;
}

void suffDimK(Tree arbore, int k, int level, int *nr) {
    // ideea e: k + 1 == level sa fie $, adica tocmai s-a terminat un sufix
    if (arbore == NULL || level > k + 1)
        return;

    if (k + 1 == level && arbore->string[0] == '$')
        (*nr)++;

    for (int i = 0; i < 27; i++)
        suffDimK(arbore->children[i], k, level + 1, nr);
}

void nrDescendants(Tree arbore, int *maxDescendants) {
    if (arbore == NULL)
        return;

    int nrCurr = 0;
    for (int i = 0; i < 27; i++) {
        if (arbore->children[i])
            nrCurr++;
        if (nrCurr > *maxDescendants)
            *maxDescendants = nrCurr;
        nrDescendants(arbore->children[i], maxDescendants);
    }
}

char checkSuffix(Tree arbore, char *suffix) {
    Tree curr = arbore;
    if (curr == NULL)
        return false;
    for (int i = 0; i < strlen(suffix); i++) {
        if (suffix[i] == '$' && curr->children[0])
            return true;  // ultimul element
        int idx = suffix[i] - ASCII;
        // daca nu pun conditiile ca idx e [0, 27] imi crapa valgrindu
        if (idx >= 0 && idx <= 27 && curr->children[idx])
            curr = curr->children[idx];
        else
            return false;
    }
    return true;
}

void printValues(char *suffixes, int M, FILE *output) {
    for (int i = 0; i < M; i++)
        fprintf(output, "%d\n", suffixes[i]);
}

void compressTree(Tree arbore) {
    if (arbore == NULL)
        return;

    int nrChildren = 0;
    int idx = 0;

    for (int i = 1; i < 27; i++) {
        if (arbore->children[i]) {
            nrChildren++;
            idx = i;
        }
        compressTree(arbore->children[i]);
    }

    if (nrChildren == 1 && arbore->children[0] == NULL) {
        Tree plod = arbore->children[idx];
        for (int i = 0; i < 27; i++)
            arbore->children[i] = plod->children[i];

        // char *aux = calloc(1, strlen(arbore->string) + strlen(plod->string) + 1);
        // strcpy(aux, arbore->string);
        // strcat(aux, plod->string);
        // free(arbore->string);

        // arbore->string = aux;

        arbore->string = realloc(arbore->string,
        (strlen(arbore->string) + strlen(plod->string) + 1) * sizeof(char));
        arbore->string = strcat(arbore->string, plod->string);

        free(plod->string);
        free(plod);
    }
}

void printCerinta4(Tree arbore, FILE *output) {
       if (arbore == NULL)
        return;

    // coada de adaugat elementele de la nivelul urm
    Tree queue[1000];
    int fata = 0, spate = 1;
    queue[spate] = arbore;

    while (fata < spate) {
        int nrNivelCurrent = spate - fata;
        bool hasCharacter = false;
        // pentru a nu incepe cu un newline

        // printam nivelul curent
        for (int i = 0; i < nrNivelCurrent; i++) {
            fata++;
            Tree current = queue[fata];
            if (current->string) {
                /*
                int j = 0;
                
                while (current->string[j] != '\0') {
                    fprintf(output, "%c", current->string[j]);
                    j++;
                } 
                fprintf(output, " ");
                */

                fprintf(output, "%s ", current->string);
                hasCharacter = true;
            }

            // adaugam in queue plozii
            for (int j = 0; j < 27; j++) {
                if (current->children[j]) {
                    spate++;
                    queue[spate] = current->children[j];
                }
            }
        }

        if (hasCharacter == true)
            fprintf(output, "\n");
    }
}
