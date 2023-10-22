/*
Implementing stack using singly linked list

stack and top are one and the same here
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
int push(node **stack, int item);
int pop(node **stack);
void printStack(node *stack);
void clearStack(node *stack);

void main()
{
    node *stack;
    int option, temp;

    stack = NULL;
    option = 0;

    while (option != 4)
    {
        printStack(stack);

        printf("Available stack operations: \n\
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
            if (!push(&stack, temp))
                printf("# Error: Stack Overflow\n");
            else
                printf("Pushed: %d\n", temp);
            break;

        case 2:
            temp = pop(&stack);
            if (temp == -999)
                printf("# Error: Stack Underflow\n");
            else
                printf("Popped: %d\n", temp);
            break;

        case 3:
            if (!stack)
                printf("# Error: Stack is empty\n");
            else
                printf("Peek: %d\n", stack->data);
            break;

        case 4:
            clearStack(stack);
            printf("# Stack has been cleared\n# Exiting\n\n");
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

int push(node **stack, int item)
{
    node *temp = createNode(item), *n;
    int len = 0;

    if (!*stack)
    {
        *stack = temp;
        return 1;
    }

    // finding current size
    n = *stack;
    while (n != NULL)
    {
        n = n->next;
        len++;
    }

    if (len == MAX) // stack overflow
        return 0;

    temp->next = *stack;

    *stack = temp;
    return 1;
}

int pop(node **stack)
{
    node *deleted;
    int data;

    if (!*stack) // stack underflow
        return -999;

    deleted = *stack;
    data = deleted->data;
    *stack = (*stack)->next;
    free(deleted);
    return data;
}

void printStack(node *stack)
{
    printf("\n");

    node *n = stack;
    while (n != NULL)
    {
        printf("%d ", n->data);
        n = n->next;
    };

    printf("\n");
}

void clearStack(node *stack)
{
    if (!stack)
        return;

    node *n = stack, *toBeDeleted;

    do
    {
        toBeDeleted = n;
        n = n->next;
        free(toBeDeleted);
    } while (n != NULL);
}
