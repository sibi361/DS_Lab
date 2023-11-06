
#include <stdio.h>
#include <stdlib.h>

typedef struct node_ node;
struct node_
{
    int data;
    node *next;
};

node *createNode(int data);
node *createCircularLinkedListFromUserInput();
void traverseLinkedList(node *head);
node *removePrimes(node *head);
int isPrime(int n);

void main()
{
    node *list = createCircularLinkedListFromUserInput();

    // traverseLinkedList(list);

    list = removePrimes(list);

    printf("\nAfter removing primes:\n");
    traverseLinkedList(list);
}

node *createNode(int data)
{
    node *temp = (node *)malloc(sizeof(node));

    temp->data = data;
    temp->next = NULL;
    return temp;
}

node *createCircularLinkedListFromUserInput()
{
    int c, inp;
    printf("Enter number of elements: ");
    scanf("%d", &c);

    printf("Enter elements:\n");
    scanf("%d", &inp);
    node *head = createNode(inp), *n, *temp;
    n = head->next = head;

    for (int i = 0; i < c - 1; i++)
    {
        scanf("%d", &inp);
        temp = createNode(inp);
        temp->next = head;
        n = n->next = temp;
    }

    return head;
}

int getLength(node *head)
{
    node *n = head;
    int i = 1;

    if (!n)
        return 0;

    if (n->next == head)
        return 1;

    while ((n = n->next) != head)
        i++;

    return i;
}

void traverseLinkedList(node *head)
{
    node *n = head;

    if (!n)
        return;

    if (n->next == head)
    {
        printf("%d\n\n", n->data);
        return;
    }

    do
        printf("%d ", n->data);
    while ((n = n->next) != head);

    printf("\n\n");
}

node *removePrimes(node *head)
{
    node *n = head, *del;

    if (!head)
        return NULL;

    if (isPrime(head->data))
    {
        if (head->next == head)
        {
            free(head);
            return NULL;
        }

        while (n->next != head)
            n = n->next;

        del = head;
        head = n->next = head->next;

        free(del);
        n = head;
    }

    while (n->next != head)
        if (isPrime(n->next->data))
        {
            // printf("prime: %d\n", n->next->data);

            del = n->next;
            n->next = n->next->next;
            free(del);
        }
        else
            n = n->next;

    return head;
}

int isPrime(int n)
{
    if (n < 2)
        return 0;

    for (int i = 2; i < n; i++)
        if (!(n % i))
            return 0;
    return 1;
}
