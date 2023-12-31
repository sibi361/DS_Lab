// Polish Notation
// Conversion of infix expression to reverse Polish i.e.
// postfix notation

#include <stdio.h>
#include <string.h>

int max_size;

char *convert_infix_postfix(char exp[]);
int push(char stack[], int *top, char item);
char pop(char stack[], int *top);
int input_precedence(char literal);
int output_precedence(char literal);

void print_stack(char stack[], int top)
{
    printf("stack: ");
    for (int i = 0; i <= top; i++)
        printf("%c ", stack[i]);
    printf("\n");
}

void main()
{
    // char exp[1000]; // input infix expression
    // printf("\nEnter infix expression: ");
    // scanf("%[^\n]s", exp);

    // char exp[] = "(a+(b-c)*d)"; // abc-d*+
    char exp[] = "a * b - c"; // ab*c-

    printf("\nObtained postfix expression:\n%s\n\n", convert_infix_postfix(exp));
}

char *convert_infix_postfix(char exp[])
{
    max_size = strlen(exp);
    char temp, stack_top;
    char stack[max_size];
    int top, i, j;

    char *exp_postfix = (char *)malloc(sizeof(exp));

    top = i = j = 0;
    stack[0] = '#'; // placeholder to indicate empty stack

    while ((temp = exp[i++]) != '\0')
    {
        if (temp == ' ') // skip spaces
            continue;

        stack_top = pop(stack, &top);

        // // debug
        // puts(exp_postfix);
        // printf("stack_top: %c | temp:  %c | top: %d\n", stack_top, temp, top);
        // print_stack(stack, top);
        // printf("\n");

        if (output_precedence(stack_top) > input_precedence(temp))
        {
            exp_postfix[j++] = stack_top;
            i--; // make sure to compare current literal on next iteration
        }
        else if (output_precedence(stack_top) == input_precedence(temp))
            ;
        else
        {
            push(stack, &top, stack_top);
            push(stack, &top, temp);
        }
    }

    while (top != 0) // exclude '#'
        exp_postfix[j++] = pop(stack, &top);
    exp_postfix[j] = '\0';

    return exp_postfix;
}

int push(char stack[], int *top, char item)
{
    if (*top == max_size - 1) // stack overflow
        return 0;
    stack[++*top] = item;
    return 1;
}

char pop(char stack[], int *top)
{
    if (*top == -1) // stack underflow
        return '\0';
    // prefix and postfix ops have higher precedence
    // than dereference operator
    return stack[(*top)--];
}

int input_precedence(char literal)
{
    switch (literal)
    {
    case ')':
        return 0;
    case '+':
    case '-':
        return 1;
    case '%':
    case '/':
    case '*':
        return 3;
    case '^':
        return 6;
    case '(':
        return 9;
    default:
        return 7;
    }
}

int output_precedence(char literal)
{
    switch (literal)
    {
    case '#': // placeholder to indicate empty stack
        return -1;
    case '(':
        return 0;
    case '+':
    case '-':
        return 2;
    case '%':
    case '/':
    case '*':
        return 4;
    case '^':
        return 5;
    case ')':
        return 100;
    default:
        return 8;
    }
}
