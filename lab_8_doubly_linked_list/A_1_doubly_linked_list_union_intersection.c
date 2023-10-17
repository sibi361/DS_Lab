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
int isPresentInArray(int len, int arr[], int item);
void findUnion(node *a, node *b);
void findIntersection(node *a, node *b);

void main()
{
    int x1_arr[] = {5, 10, 20};
    int x2_arr[] = {-3, -2, 0, 5, 10, 11, 25};

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

    findUnion(x1, x2);
    findIntersection(x1, x2);
}

node *createNode(node *previous, int data)
{
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

    if (n == NULL)
        return 0;

    while ((n = n->next) != NULL)
        length++;

    return length;
}

node *insert(node *head, int index, int item)
{
    node *n = head, *newNode;
    int i = 1;

    if (!head)
    {
        newNode = createNode(NULL, item);
        newNode->next = newNode;
        newNode->previous = newNode;
        return newNode;
    }
    else if (index == 0)
    {
        node *newNode = createNode(head->previous, item);
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

int isPresentInArray(int len, int arr[], int item)
{
    for (int i = 0; i < len; i++)
        if (arr[i] == item)
            return 1;
    return 0;
}

void findUnion(node *a, node *b)
{
    int len1 = getLength(a);
    int len2 = getLength(b);
    int union_arr[len1 + len2];
    int arr_i = 0;
    node *n = a;

    while (n != NULL)
    {
        union_arr[arr_i++] = n->data;
        n = n->next;
    }

    n = b;
    while (n != NULL)
    {
        if (!isPresentInArray(arr_i, union_arr, n->data))
            union_arr[arr_i++] = n->data;
        n = n->next;
    }

    printf("Union: \n");
    for (int i = 0; i < arr_i; i++)
        printf("%d ", union_arr[i]);
    printf("\n\n");
}

void findIntersection(node *a, node *b)
{
    int len1 = getLength(a);
    int len2 = getLength(b);
    int intersect_arr[len1 + len2];
    int arr_i = 0, matchFound = 0;
    node *n1 = a, *n2;

    while (n1 != NULL)
    {
        n2 = b;
        while (n2 != NULL)
        {
            if (n2->data == n1->data)
            {
                matchFound = 1;
                break;
            }
            n2 = n2->next;
        }
        if (matchFound && !isPresentInArray(arr_i, intersect_arr, n1->data))
        {
            intersect_arr[arr_i++] = n1->data;
            matchFound = 0;
        }
        n1 = n1->next;
    }

    printf("Intersection: \n");
    for (int i = 0; i < arr_i; i++)
        printf("%d ", intersect_arr[i]);
    printf("\n\n");
}
