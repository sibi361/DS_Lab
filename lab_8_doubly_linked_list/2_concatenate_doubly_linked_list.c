#include <stdio.h>
#include <stdlib.h>

typedef struct node_ node;
struct node_
{
    node *previous;
    int data;
    node *next;
};

node *createNode(node *previous, int data);
node *createLinkedListFromArray(int length, int array[]);
node *createLinkedListFromUserInput();
int getLength(node *head);
node *insert(node *head, int index, int item);
void append(node *head, int item);
void traverseLinkedList(node *head);
node *concatenateDoublyLinkedList(node *a, node *b);

void main()
{
    int x1_arr[] = {5, 10, 15};
    int x2_arr[] = {20, -3, 55, 9};

    // creating
    node *x1 = createLinkedListFromArray(
        sizeof(x1_arr) / sizeof(x1_arr[0]),
        x1_arr);
    // node *x1 = NULL;
    node *x2 = createLinkedListFromArray(
        sizeof(x2_arr) / sizeof(x2_arr[0]),
        x2_arr);
    // node *x1 = createLinkedListFromUserInput();
    // node *x2 = createLinkedListFromUserInput();

    printf("X1:\n");
    traverseLinkedList(x1);

    printf("X2:\n");
    traverseLinkedList(x2);

    x1 = concatenateDoublyLinkedList(x1, x2);

    printf("X1 after concatenation:\n");
    traverseLinkedList(x1);

    printf("X2 remains the same:\n");
    traverseLinkedList(x2);
}

node *createNode(node *previous, int data)
{
    /*
    unlike local variables, variables initialised with malloc()
    are not destroyed after function exit
    they also have new memory addresses as compared to doing:
    node temp;
    */
    node *temp = (node *)malloc(sizeof(node));

    temp->previous = previous;
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

    node *head = createNode(NULL, array[0]);

    for (int i = 1; i < length; i++)
        append(head, array[i]);

    return head;
}

node *createLinkedListFromUserInput()
{
    int n, temp;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    scanf("%d", &temp);
    node *head = createNode(NULL, temp);

    for (int i = 0; i < n - 1; i++)
    {
        scanf("%d", &temp);
        append(head, temp);
    }

    return head;
}

int getLength(node *head)
{
    node *n = head;
    int length = 1;

    while ((n = n->next) != NULL)
        length++;

    return length;
}

node *insert(node *head, int index, int item)
{
    node *n = head;
    int i = 1;

    if (index == 0)
    {
        node *newNode = createNode(NULL, item);
        newNode->next = head;
        head = newNode;
    }
    else
    {
        while (i++ < index)
            n = n->next;

        node *newNode = createNode(n, item);
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

    while (n != NULL)
    {
        printf("%d ", n->data);
        n = n->next;
    }
    printf("\n\n");
}

node *concatenateDoublyLinkedList(node *a, node *b)
{
    if (a == NULL)
        return b;

    node *n = a;
    do
        n = n->next;
    while (n->next != NULL);

    n->next = b;

    return a;
}
