#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} node;

node* insert_node(node *elem, int value) {
    node *new_elem = malloc(sizeof(node));
    new_elem->value = value;
    new_elem->next = elem->next;
    elem->next = new_elem;
    return new_elem;
}

node* delete_node(node *head, int i) {
    node *tmp;
    if (i == 0) {
        tmp = head->next;
        free(head);
        return tmp; // new head
    }

    node *ptr = head;
    for (int j = 0; (j < i-1) && (ptr != 0); j++) {
        ptr = ptr->next;
    }
    if (ptr != 0) {
        tmp = ptr->next->next;
        free(ptr->next);
        ptr->next = tmp;
    }
    return head;
}

void print_list(node* head) {
    node *ptr = head;
    while (ptr != 0) {
        printf("%d ", ptr->value);
        ptr = ptr->next;
    }
    printf("\n");
}

int main() {
    node *head = malloc(sizeof(node));
    head->value = 3;
    head->next = 0;

    node* ptr = insert_node(head, 10);
    ptr = insert_node(ptr, 2);
    ptr = insert_node(ptr, 1);

    print_list(head);

    head = delete_node(head, 2);

    print_list(head);

    head = delete_node(head, 0);

    print_list(head);

    return 0;
}
