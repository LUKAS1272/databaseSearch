#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char* nodeValue;
    struct node* leftBranch;
    struct node* rightBranch;
} node;

node* createNode(char* value) {
    node* result = malloc(sizeof(node));

    if (result != NULL) {
        result->nodeValue = value;
        result->leftBranch = NULL;
        result->rightBranch = NULL;
    }

    printf("Stored\n");
    return result;
}

void findNode(node* root, char* value) {
    node* currentNode = root;

    while (1) {
        if (strcmp(currentNode->nodeValue, value) < 0) { // Lower than value
            if (currentNode->rightBranch != NULL) {
                currentNode = currentNode->rightBranch;
            } else {
                printf("Not found\n");
                free(value);
                return;
            }
        } else if (strcmp(currentNode->nodeValue, value) > 0) { // Higher than value
            if (currentNode->leftBranch != NULL) {
                currentNode = currentNode->leftBranch;
            } else {
                printf("Not found\n");
                free(value);
                return;
            }
        } else { // Same as value
            printf("Found\n");
            free(value);
            return;
        }
    }
}

node* storeNode(node* root, char* value) {
    if (strcmp(root->nodeValue, value) < 0) { // Lower than value
        if (root->rightBranch != NULL) {
            root->rightBranch = storeNode(root->rightBranch, value);
            return root;
        } else {
            root->rightBranch = createNode(value);
            return root;
        }
    } else if (strcmp(root->nodeValue, value) > 0) { // Higher than value
        if (root->leftBranch != NULL) {
            root->leftBranch = storeNode(root->leftBranch, value);
            return root;
        } else {
            root->leftBranch = createNode(value);
            return root;
        }
    } else { // Same as value
        printf("Already stored\n");
        free(value);
        return root;
    }
}

node* mostTo(node* root) {
    if (root->rightBranch != NULL) {
        return mostTo(root->rightBranch);
    } else {
        return root;
    }
}

node* deleteNode(node* root, char* value) {
    if (strcmp(root->nodeValue, value) < 0) { // Lower than value
        if (root->rightBranch != NULL) {
            root->rightBranch = deleteNode(root->rightBranch, value);
        } else {
            printf("Not found\n");
        }

        return root;
    } else if (strcmp(root->nodeValue, value) > 0) { // Higher than value
        if (root->leftBranch != NULL) {
            root->leftBranch = deleteNode(root->leftBranch, value);
        } else {
            printf("Not found\n");
        }

        return root;
    } else { // Same as value
        if (root->leftBranch == NULL && root->rightBranch == NULL) { // Leaf node - no children
            printf("Deleted\n");

            free(root->nodeValue);
            free(root);
            return NULL;
        } else if (root->leftBranch != NULL && root->rightBranch != NULL) { // Both children
            char* temp = mostTo(root->leftBranch)->nodeValue;
            char* valueCopy = malloc(sizeof(temp));
            strcpy(valueCopy, temp);

            root = deleteNode(root, temp);
            free(root->nodeValue);
            root->nodeValue = valueCopy;

            return root;
        } else if (root->leftBranch != NULL) { // Only left child
            printf("Deleted\n");

            node* temp = root->leftBranch;
            free(root->nodeValue);
            free(root);
            return temp;
        } else if (root->rightBranch != NULL) { // Only right child
            printf("Deleted\n");

            node* temp = root->rightBranch;
            free(root->nodeValue);
            free(root);
            return temp;
        }
    }
}

node* freeAll(node* root) {
    //printf(". ");
    if (root->leftBranch != NULL) {
        root->leftBranch = freeAll(root->leftBranch);
    }

    if (root->rightBranch != NULL) {
        root->rightBranch = freeAll(root->rightBranch);
    }

    free(root->leftBranch);
    free(root->rightBranch);
    free(root->nodeValue);
    return root;
}

int main() {
    node* root = NULL;

    //printf("%ld\n", sizeof(node));

    char action;
    while (scanf("%c: ", &action) != EOF) {

        // Node value scan
        char* value = realloc(NULL, 1);
        int valueLength = 0;
        char tempChar;

        do {
            scanf("%c", &tempChar);

            value = realloc(value, ++valueLength);
            value[valueLength - 1] = tempChar;
        } while (tempChar != '\n');
        value[valueLength - 1] = '\0';

        switch (action) {
            case 'S':
                if (root != NULL)
                    root = storeNode(root, value);
                else
                    root = createNode(value);

                break;
            case 'F':
                if (root != NULL) {
                    findNode(root, value);

                } else {
                    printf("Not found\n");
                    free(value);
                }

                break;
            case 'D':
                if (root == NULL) {
                    printf("Not found\n");
                } else if (root->leftBranch == NULL && root->rightBranch == NULL) {
                    if (strcmp(root->nodeValue, value) == 0) {
                        free(root->nodeValue);
                        free(root);
                        root = NULL;
                        printf("Deleted\n");
                    } else {
                        printf("Not found\n");
                    }
                } else if (root != NULL) {
                    root = deleteNode(root, value);
                }

                free(value);
                break;
        }
    }

    if (root != NULL) {
        root = freeAll(root);
    }
    free(root);
    return 0;
}