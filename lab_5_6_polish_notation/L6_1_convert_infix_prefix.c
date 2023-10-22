// Polish Notation
// Conversion of infix expression to Polish i.e. prefix notation

/*
method:
- reverse given infix
- perform infix -> postfix while exchanging the precedence values for
opening and closing parenthesis
- reverse the obtained flawed postfix exp to get proper infix exp
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max_size;

int push(char stack[], int *top, char item);
char pop(char stack[], int *top);
int input_precedence(char literal);
int output_precedence(char literal);
char *reverse_string(char inp[]);

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

    char exp2[] = "(a+(b-c)*d)"; // +*d-bca
    // char exp[] = "a * b - c"; // -c*ba

    // step 1: reverse the given infix expression
    char *exp = reverse_string(exp2);

    max_size = strlen(exp);
    char exp_postfix[max_size], temp, stack_top;
    char stack[max_size];
    int top, i, j;

    top = i = j = 0;
    stack[0] = '#'; // placeholder to indicate empty stack

    // step 2: convert reversed infix to postfix while exchanging the
    // precedence values for opening and closing parenthesis
    // note that this will give kind of a postfix expression with all
    // terms reversed; for e.g. (b-c) becomes cb- instead of bc-
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

    printf("\nObtained terms reversed postfix expression:\n%s\n", exp_postfix);

    // final step 3: reverse the obtained weird postfix expression
    char *exp_prefix = reverse_string(exp_postfix);
    printf("\nObtained prefix expression after reversing above expression:\n%s\n\n", exp_prefix);

    // print_stack(stack, top);
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
    case '(':
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
    case ')':
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
    case ')':
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
    case '(':
        return 100;
    default:
        return 8;
    }
}

char *reverse_string(char inp[])
{
    int len = strlen(inp);

    char *rev = (char *)malloc(len);

    for (int i = len - 1; i >= 0; i--)
        rev[len - i - 1] = inp[i];
    rev[len] = '\0';

    return rev;
}
