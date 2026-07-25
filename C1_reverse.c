#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *reverse_list(Node *head) {
    Node *prev = NULL;
    Node *curr = head;
    Node *next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}