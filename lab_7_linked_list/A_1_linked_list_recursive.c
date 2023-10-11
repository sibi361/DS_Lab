#include <stdio.h>
#include <stdlib.h>

typedef struct node_ node;
struct node_
{
    int data;
    node *next;
};

node *createNode(int data);
node *createLinkedListRecursively(int index);
void traverseLinkedListRecursively(node *head);

void main()
{
    node *list;

    printf("\nEnter contents of linked list:\n\n");
    list = createLinkedListRecursively(1);
    printf("\n");

    printf("Traversing linked list recursively:\n");
    traverseLinkedListRecursively(list);
    printf("\n\n");
}

node *createNode(int data)
{
    node *temp = (node *)malloc(sizeof(node));

    temp->data = data;
    temp->next = NULL;
    return temp;
}

node *createLinkedListRecursively(int pos)
{
    int temp;
    printf("Enter element %d (-99 to stop): ", pos);
    scanf("%d", &temp);

    if (temp == -99)
        return NULL;

    node *new = createNode(temp);
    new->next = createLinkedListRecursively(pos + 1);
    return new;
}

void traverseLinkedListRecursively(node *n)
{
    if (n == NULL)
        return;
    printf("%d ", n->data);
    traverseLinkedListRecursively(n->next);
}
