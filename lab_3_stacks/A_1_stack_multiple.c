#include <stdio.h>
#include <stdlib.h>

// multiple stacks in a single array

// for demonstration purpose
#define MAX_SIZE 20
#define NUM_STACKS 5
#define DELTA MAX_SIZE / NUM_STACKS

int initialise_stack(int stack[], int top[], int boundary[]);
int stackSelection(int *stack_pos, int *stack_index);
int push(int stack[], int stack_index, int top[], int bound[], int item);
int pop(int stack[], int stack_index, int top[], int bound[]);
int getSize(int stack_index, int top[], int bound[]);
int isEmpty(int stack[], int stack_index, int top[], int bound[]);
int isFull(int stack[], int stack_index, int top[], int bound[]);
int clearStack(int stack_index, int top[], int bound[]);
int clearAllStacks(int top[], int bound[]);
void printStack(int stack[], int top[], int bound[]);

void printStack(int stack[], int top[], int bound[])
{
    printf("\n");
    for (int i = 0; i < NUM_STACKS; i++)
    {
        for (int j = bound[i]; j < top[i]; j++)
            printf("%d ", stack[j + 1]);
        printf(" | ");
    }
    printf("\n\n");
}

void main()
{
    printf("\nMultiple Integer Stack Demonstration\n\n");

    int stack[MAX_SIZE], top[NUM_STACKS], boundary[NUM_STACKS];
    initialise_stack(stack, top, boundary);

    int stack_pos, stack_index, option, temp, output;

    if (!stackSelection(&stack_pos, &stack_index))
        exit(0);

    while (option != 6)
    {
        printStack(stack, top, boundary); // for debugging

        printf("Available stack operations: \n\
        1 Push \n\
        2 Pop \n\
        3 Get Size \n\
        4 Clear \n\
        5 Change selected stack \n\
        6 Exit \n");
        printf("# Enter option: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("# Enter element to push: ");
            scanf("%d", &temp);

            output = push(stack, stack_index, top, boundary, temp);
            if (output)
                printf("# %d pushed successfully into stack %d\n", temp, stack_pos);
            else
                printf("# ERROR: STACK OVERFLOW in stack %d\n", stack_pos);
            break;

        case 2:
            temp = pop(stack, stack_index, top, boundary);
            if (temp == -99999)
                printf("# ERROR: STACK UNDERFLOW in stack %d\n", stack_pos);
            else
                printf("# popped %d from stack %d\n", temp, stack_pos);
            break;

        case 3:
            printf("# stack %d size: %d\n", stack_pos, getSize(stack_index, top, boundary));
            break;

        case 4:
            output = clearStack(stack_index, top, boundary);
            if (output)
                printf("# stack %d has been cleared\n", stack_pos);
            else
                printf("# ERROR: stack %d is already empty\n", stack_pos);
            break;

        case 5:
            stackSelection(&stack_pos, &stack_index);
            break;

        case 6:
            clearAllStacks(top, boundary);
            printf("# All stacks have been cleared\n");
            printf("# Exiting\n\n");
            break;

        default:
            printf("# INVALID OPTION\n");
        }
    }
}

int initialise_stack(int stack[], int top[], int bound[])
{
    for (int i = 0; i < NUM_STACKS; i++)
        top[i] = bound[i] = i * DELTA - 1;

    for (int i = 0; i < MAX_SIZE; i++)
        stack[i] = 0;
}

int stackSelection(int *stack_pos, int *stack_index)
{
    int temp_stack_pos;
    printf("Enter stack number: ");
    scanf("%d", &temp_stack_pos);
    if (temp_stack_pos < 1 || temp_stack_pos > NUM_STACKS)
    {
        printf("# ERROR: Invalid stack number\n");
        printf("Available stacks: 1 to %d\n\n", NUM_STACKS);
        return 0;
    }
    *stack_pos = temp_stack_pos;
    *stack_index = temp_stack_pos - 1;
    return 1;
}

int push(int stack[], int stack_i, int top[], int bound[], int item)
{
    if ((stack_i == NUM_STACKS - 1 &&
         top[stack_i] == MAX_SIZE - 1) ||
        top[stack_i] == bound[stack_i + 1])
        return 0; // stack overflow
    stack[++top[stack_i]] = item;
    return 1;
}

int pop(int stack[], int stack_i, int top[], int bound[])
{
    if (top[stack_i] == bound[stack_i]) // stack underflow
        return -99999;
    return stack[top[stack_i]--];
}

int getSize(int stack_i, int top[], int bound[])
{
    return top[stack_i] - bound[stack_i];
}

int isEmpty(int stack[], int stack_i, int top[], int bound[])
{
    if (getSize(stack_i, top, bound) == 0)
        return 1;
    return 0;
}

int clearStack(int stack_i, int top[], int bound[])
{
    if (top[stack_i] == bound[stack_i])
        return 0;
    top[stack_i] = -1;
    return 1;
}

int clearAllStacks(int top[], int bound[])
{
    int cleared = 0;
    for (int i = 0; i < NUM_STACKS; i++)
        if (top[i] != bound[i])
        {
            cleared = 1;
            top[i] = bound[i];
        }
    return cleared;
}
