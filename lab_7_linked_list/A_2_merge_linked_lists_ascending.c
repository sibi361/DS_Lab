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
node *mergeAscendingOrder(node *head1, node *head2);

void main()
{
    int list1_arr[] = {-99, 50, 100, 150, 232};
    int list2_arr[] = {-2, 40, 76};

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

    node *list3 = mergeAscendingOrder(list1, list2);
    printf("List 3 obtained after merging ascending:\n");
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

node *mergeAscendingOrder(node *list1, node *list2)
{
    node *head, *n, *n1, *n2;

    n1 = list1;
    n2 = list2;

    int l1 = getLength(list1);
    int l2 = getLength(list2);
    int newLen = l1 + l2;
    int pointedTo;

    if (n1->data < n2->data)
    {
        n = n1;
        n1 = n1->next;
        pointedTo = 0;
    }
    else
    {
        n = n2;
        n2 = n2->next;
        pointedTo = 1;
    }

    head = n;

    // printf("## %d %d %d %d\n\n", n->data, n->next->data, n1->data, n2->data);

    int i = 0;
    while (n1 && n2)
    {

        // printf("i: %d | n: %d | n1: %d | n2: %d\n", i, n->next->data, n1->data, n2->data);

        // node *smaller;
        // smaller = n1->data < n2->data ? n1 : n2;
        // printf("%d is smaller   \n\n", smaller->data);

        if (pointedTo == 0)
        {
            printf("%d ", 0);

            if (n1->next->data > n2->data)
            {
                n = n->next = n2;
                n2 = n2->next;
                pointedTo = 0;
            }
            else
            {
                n = n->next;
                n1 = n1->next;
            }
        }
        else
        {
            printf("%d ", 1);

            if (n1->data < n2->next->data)
            {
                n = n->next = n1;
                n1 = n1->next;
                pointedTo = 1;
            }
            else
            {
                n = n->next;
                n2 = n2->next;
            }
        }

        printf("# %d \n\n", n->data);
    }
    printf("\n");

    // printf("\n\n333     %d\n", n->data);

    // i = 0;
    // n = head;
    // while (i++ < newLen)
    //     n = n->next;
    // n->next = NULL;

    while (n1 && (n1 = n1->next))
        append(head, n1->data);

    while (n2 && (n2 = n2->next))
        append(head, n2->data);

    return head;
}
