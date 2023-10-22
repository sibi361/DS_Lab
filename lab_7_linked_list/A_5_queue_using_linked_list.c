/*
Implementing queue using singly linked list

queue and front are one and the same here
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct node node;
struct node
{
    int data;
    node *next;
};

node *createNode(int data);
int insert(node **queue, int item);
int delete(node **queue);
void printQueue(node *queue);
void clearQueue(node *queue);

void main()
{
    node *queue;
    int option, temp;

    queue = NULL;
    option = 0;

    while (option != 4)
    {
        printQueue(queue);

        printf("Available queue operations: \n\
        1 Push \n\
        2 Pop \n\
        3 Peek \n\
        4 Exit \n");
        printf("# Enter option: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("Enter element to push: ");
            scanf("%d", &temp);
            if (!insert(&queue, temp))
                printf("# Error: Queue Overflow\n");
            else
                printf("Inserted: %d\n", temp);
            break;

        case 2:
            temp = delete (&queue);
            if (temp == -999)
                printf("# Error: Queue Underflow\n");
            else
                printf("Deleted: %d\n", temp);
            break;

        case 3:
            if (!queue)
                printf("# Error: Queue is empty\n");
            else
                printf("Peek: %d\n", queue->data);
            break;

        case 4:
            clearQueue(queue);
            printf("# Queue has been cleared\n# Exiting\n\n");
            break;

        default:
            printf("# Invalid option\n");
        }
    }
}

node *createNode(int data)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

int insert(node **queue, int item)
{
    node *temp = createNode(item), *n;
    int len = 0;

    if (!*queue)
    {
        *queue = temp;
        return 1;
    }

    n = *queue;
    while (n->next != NULL)
    {
        n = n->next;
        len++;
    }

    if (len + 1 == MAX) // queue overflow
        return 0;

    n->next = temp;

    return 1;
}

int delete(node **queue)
{
    node *deleted;
    int data;

    if (!*queue) // queue underflow
        return -999;

    deleted = *queue;
    data = deleted->data;
    *queue = (*queue)->next;
    free(deleted);
    return data;
}

void printQueue(node *queue)
{
    printf("\n");

    node *n = queue;
    while (n != NULL)
    {
        printf("%d ", n->data);
        n = n->next;
    };

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
    } while (n != NULL);
}
