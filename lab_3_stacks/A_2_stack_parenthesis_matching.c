#include <stdio.h>
#include <string.h>

void push(char stack[], int *top, int expression_length, int item);
char pop(char stack[], int *top);

void print_stack(int stack[], int top)
{
    for (int i = 0; i <= top; i++)
        printf("%d ", stack[i]);
    printf("\n");
}

void main()
{
    printf("\nParenthesis Matching Using Stack\n\n");

    int top, exp_len, valid = 1;
    char temp, popped;
    // char exp[100]; // expression

    printf("Enter expression: ");
    // scanf("%[^\n]s", exp);

    char exp[100] = "{[}]";
    printf("\n");

    exp_len = strlen(exp);

    char stack_opening[exp_len];
    top = -1;

    // pushing characters from expression to stack
    for (int i = 0; i < exp_len; i++)
    {
        temp = exp[i];
        if (temp == '(' || temp == '[' || temp == '{')
        {
            push(stack_opening, &top, exp_len, exp[i]);
            printf("PUSH %c\n", temp);
        }
        else if (temp == ')' || temp == ']' || temp == '}')
        {
            popped = pop(stack_opening, &top);

            printf("POP %c %c %d\n", temp, popped, temp != popped);

            if (temp == ')' && popped != '(' | temp == ']' && popped != '[' | temp == '}' && popped != '{')
            {
                valid = 0;
                break;
            }
        }
    }

    if (valid && top == -1)
        printf("Given expression is valid\n");
    else
        printf("Given expression is INVALID\n");

    printf("\n");
}

void push(char stack[], int *top, int expression_length, int item)
{
    if (*top == expression_length - 1) // stack overflow
        return;
    stack[++*top] = item;
}

char pop(char stack[], int *top)
{
    if (*top == -1) // stack underflow
        return '\0';

    // prefix and postfix ops have higher precedence
    // than dereference operator
    return stack[(*top)--];
}
