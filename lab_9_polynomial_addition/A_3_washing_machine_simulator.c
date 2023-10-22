/*
Implementing queue using doubly circular linked list

queue and front are one and the same here
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct node node;
struct node
{
    node *previous;
    int data;
    node *next;
};

node *createNode(node *previous, int data);
int insert(node **queue, int item);
int delete(node **queue);
void printQueue(node *queue);
void clearQueue(node *queue);

void main()
{
    node *queue;
    int option, temp, token;

    queue = NULL;
    option = token = 0;

    printf("\nWashing Machine Simulator\n\n");

    while (option != 4)
    {
        printQueue(queue);

        printf("\nAvailable queue operations: \n\
        1 Add cloth into machine\n\
        2 Remove cloth from machine\n\
        3 Currently token number?\n\
        4 Exit \n");
        printf("# Enter option: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            if (!insert(&queue, ++token))
                printf("# Sorry the queue is full, please hold\n");
            else
                printf("Cloth put for wash. Your token number is %d\n", token);
            break;

        case 2:
            temp = delete (&queue);
            if (temp == -999)
                printf("# Error: No clothes present in machine\n");
            else
                printf("Finished washing token number %d\n", temp);
            break;

        case 3:
            if (!queue)
                printf("# Error: No clothes present in machine\n");
            else
                printf("Currently washing token number %d\n", queue->data);
            break;

        case 4:
            clearQueue(queue);
            printf("# All clothes have been dumped into the void\n\
Powering off the washing machine\n\n");
            break;

        default:
            printf("# Invalid option\n");
        }
    }
}

node *createNode(node *previous, int data)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->previous = previous;
    temp->data = data;
    temp->next = NULL;
    return temp;
}

int insert(node **queue, int item)
{
    node *temp, *n;
    int len = 0;

    if (!*queue)
    {
        temp = createNode(NULL, item), *n;
        temp->previous = temp;
        temp->next = temp;
        *queue = temp;
        return 1;
    }

    n = *queue;
    while (n->next != *queue)
    {
        n = n->next;
        len++;
    }

    if (len + 1 == MAX) // queue overflow
        return 0;

    temp = createNode(n, item);
    temp->next = n->next;
    n->next = temp;

    return 1;
}

int delete(node **queue)
{
    node *deleted, *n;
    int data;

    if (!*queue) // queue underflow
        return -999;

    deleted = *queue;
    data = deleted->data;

    // updating tail
    n = *queue;
    while (n->next != *queue)
        n = n->next;

    if (n == *queue) // i.e. head equals found tail
        *queue = NULL;
    else
        *queue = n->next = (*queue)->next;

    free(deleted);
    return data;
}

void printQueue(node *queue)
{
    if (!queue)
        return;

    printf("\nWashing machine queue: ");
    node *n = queue;
    do
    {
        printf("%d ", n->data);
        n = n->next;
    } while (n != queue);

    printf("\n");
}

void clearQueue(node *queue)
{
    if (!queue)
        return;

    node *n = queue, *toBeDeleted;

    do
    {
        toBeDeleted = n;
        n = n->next;
        free(toBeDeleted);
    } while (n != queue);
}
