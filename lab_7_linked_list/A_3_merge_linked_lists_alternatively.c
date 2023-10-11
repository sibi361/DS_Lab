// program to merge two linked lists while taking elements
// from both lists alternatively

#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node
{
    int data;
    node *next;
};

node *createNode(int data);
node *createLinkedListFromArray(int length, int array[]);
node *insert(node *head, int index, int item);
void append(node *head, int item);
void traverseLinkedList(node *head);
int getLength(node *head);
node *alternateMerge(node *head1, node *head2);

void main()
{
    int list1_arr[] = {5, 10, 15};
    // int list1_arr[] = {5, 10, 15, 20, 453};
    int list2_arr[] = {20, -3, 55, 76};

    node *list1 = createLinkedListFromArray(
        sizeof(list1_arr) / sizeof(list1_arr[0]),
        list1_arr);
    node *list2 = createLinkedListFromArray(
        sizeof(list2_arr) / sizeof(list2_arr[0]),
        list2_arr);

    printf("\nList 1:\n");
    traverseLinkedList(list1);
    printf("List 2:\n");
    traverseLinkedList(list2);

    node *list3 = alternateMerge(list1, list2);
    printf("List 3 obtained after alternate merging:\n");
    traverseLinkedList(list3);
}

node *createNode(int data)
{
    node *temp = (node *)malloc(sizeof(node));

    temp->data = data;
    temp->next = NULL;
    return temp;
}

node *createLinkedListFromArray(int length, int array[])
{
    if (length == 0)
    {
        printf("Array should have at least one element\n");
        exit(0);
    }

    node *head = createNode(array[0]);

    for (int i = 1; i < length; i++)
        append(head, array[i]);

    return head;
}

node *insert(node *head, int index, int item)
{
    node *n = head;
    int i = 1;
    node *newNode = createNode(item);

    if (index == 0)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        while (i++ < index)
            n = n->next;

        newNode->next = n->next;
        n->next = newNode;
    }

    return head;
}

void append(node *head, int item)
{
    insert(head, getLength(head), item);
}

void traverseLinkedList(node *head)
{
    node *n = head;

    do
        printf("%d ", n->data);
    while ((n = n->next) != NULL);
    printf("\n\n");
}

int getLength(node *head)
{
    node *n = head;
    int i = 1;

    while ((n = n->next) != NULL)
        i++;

    return i;
}

node *alternateMerge(node *list1, node *list2)
{
    node *merged, *n1, *n2;

    n1 = list1;
    n2 = list2;

    merged = createNode(n1->data);
    append(merged, n2->data);

    while (n1->next && n2->next)
    {
        n1 = n1->next;
        n2 = n2->next;
        append(merged, n1->data);
        append(merged, n2->data);
    }

    while (n1 && (n1 = n1->next))
        append(merged, n1->data);

    while (n2 && (n2 = n2->next))
        append(merged, n2->data);

    return merged;
}
