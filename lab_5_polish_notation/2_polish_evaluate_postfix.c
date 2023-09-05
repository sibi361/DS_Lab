/*
Polish Notation
Evaluation of reverse Polish i.e. postfix expression
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

int eval_postfix(char exp[]);
int is_operator(char operator);
int push(int stack[], int *top, int item);
int pop(int stack[], int *top);

void main()
{
    // char exp[MAX_SIZE];
    // printf("\nEnter postfix expression: ");
    // scanf("%[^\n]s", exp);

    // test cases
    // 9-((8/2)*(2+3)) = -11
    // 63-45+* = 27
    char exp[MAX_SIZE] = "982/ 23+*-";

    printf("\nResult = %d\n\n", eval_postfix(exp));
}

int eval_postfix(char exp[])
{
    char temp, op1, op2;
    int stack[MAX_SIZE];
    int top = -1, i = 0, result = 0;

    while ((temp = exp[i++]) != '\0')
    {
        if (temp == ' ')
            continue;
        else if (!is_operator(temp))
        {
            // temp - '0' is converted character number to integer
            if (!push(stack, &top, temp - '0'))
            {
                printf("Stack Overflow\n");
                exit(0);
            }
        }
        else
        {
            op2 = pop(stack, &top); // order is important
            op1 = pop(stack, &top);

            switch (temp)
            {
            case '^':
                result = op1 ^ op2;
                break;
            case '%':
                result = op1 % op2;
                break;
            case '/':
                result = op1 / op2;
                break;
            case '*':
                result = op1 * op2;
                break;
            case '+':
                result = op1 + op2;
                break;
            case '-':
                result = op1 - op2;
                break;
            default:
                printf("Invalid operator: %c\n", temp);
                exit(0);
            }

            // push result to stack
            if (!push(stack, &top, result))
            {
                printf("Stack Overflow\n");
                exit(0);
            }
        }
    }
    return result;
}

int is_operator(char operator)
{
    switch (operator)
    {
    case '^':
    case '%':
    case '/':
    case '*':
    case '+':
    case '-':
        return 1;
    }
    return 0;
}

int push(int stack[], int *top, int item)
{
    if (*top == MAX_SIZE - 1) // stack overflow
        return 0;
    stack[++*top] = item;
    return 1;
}

int pop(int stack[], int *top)
{
    if (*top == -1) // stack underflow
        return -99999;

    // prefix and postfix ops have higher precedence
    // than dereference operator
    return stack[(*top)--];
}
