#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char* nodeValue;
    struct node *leftBranch;
    struct node *rightBranch;
} node;

node* createNode(char* value) {
    node* result = malloc(sizeof(node));

    if (result != NULL) {
        result->nodeValue = value;
        result->leftBranch = NULL;
        result->rightBranch = NULL;
    }

    return result;
}

void findNode(node* root, char* value) {
    node* currentNode = root;

    while (1) {
        if (strcmp(currentNode->nodeValue, value) < 0) { // Lower than value
            if (currentNode->rightBranch != NULL) {
                currentNode = currentNode->rightBranch;
            } else {
                printf("Not found");
                return;
            }
        } else if (strcmp(currentNode->nodeValue, value) > 0) { // Higher than value
            if (currentNode->leftBranch != NULL) {
                currentNode = currentNode->leftBranch;
            } else {
                printf("Not found");
                return;
            }
        } else { // Same as value
            printf("Found\n");
            return;
        }
    }
}

node* storeNode(node* root, char* value) {
    printf("storeNode, root value - %s\n", root->nodeValue);

    while (1) {
        if (strcmp(root->nodeValue, value) < 0) { // Lower than value
            if (root->rightBranch != NULL) {
                return storeNode(root->rightBranch, value);
            } else {
                printf("Stored\n");
                return createNode(value);
            }
        } else if (strcmp(root->nodeValue, value) > 0) { // Higher than value
            if (root->leftBranch != NULL) {
                return storeNode(root->leftBranch, value);
            } else {
                printf("Stored\n");
                return createNode(value);
            }
        } else { // Same as value
            printf("Already stored - %s - %s\n", value, root->nodeValue);
            return root;
        }
    }

    // Find, whether the node exists
    // If it does, write out "Already stored"
    // Else store the node
}

void deleteNode(node* root, char* value) {
    // Find, whether the node exists
}

int main() {
    node* root = NULL;

    printf("%d", strcmp("30", "20"));

    while (1) {
        // Action scan
        char action;
        scanf("%c: ", &action);

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
                printf("Store reached\n");
                if (root != NULL) {
                    root = storeNode(root, value);
                }
                else {
                    root = createNode(value);
                    printf("First store - %s\n", root->nodeValue);
                }
                break;
            case 'F':
                findNode(root, value);
                break;
            case 'D':
                printf("Not implemented yet\n");
                break;
        }


        //free(value);
    }

    return 0;
}