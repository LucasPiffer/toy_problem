#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *data;
    struct node *next;
} node_t;

void push(node_t * head, char * line) {
    node_t * current = head;

    while(current->next != NULL) {
        current = current->next;
    }

    node_t * new_node = (node_t *) malloc(sizeof(node_t));
    new_node->data = line;
    current->next = new_node;
    new_node->next = NULL;
}

void print_list(node_t * head) {
    node_t * current = head;

    printf("%s", current->data);
    
    if(current->next != NULL) {
        print_list(current->next);
    }
}

int main(void) {
    int index;

    node_t * head = (node_t *)malloc(sizeof(node_t));
    
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    char str[150];

    fp = fopen("./file", "r");
    
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while (fgets(str, 150, fp)) {
        if(strstr(str, "network")) {
            if(head->data == NULL) {
                head->data = strdup(str);
                head->next = NULL;
            } else {
                push(head, strdup(str));
            }    
        }   
    }
    
    fclose(fp);
    
    print_list(head);

    exit(EXIT_SUCCESS);
}