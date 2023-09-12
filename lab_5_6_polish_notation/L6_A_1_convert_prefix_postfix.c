// Polish Notation
// Conversion of prefix expression to postfix expression

/*
method: prefix -> infix followed by infix -> postfix
this code could have been flawed as during prefix -> infix
*BC becomes *CB instead of *BC

fixed by not saving op2 i.e. when operator found,
first one popped is appended first followed by the second one popped
opposite to how it was done in postfix -> infix
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 1000

int push_2d(char stack[][MAX_SIZE], int *top, char *item);
char *pop_2d(char stack[][MAX_SIZE], int *top);
char *convert_infix_postfix(char exp[]);
int push(char stack[], int *top, char item);
char pop(char stack[], int *top);
int input_precedence(char literal);
int output_precedence(char literal);
int is_operator(char operator);
char *reverse_string(char inp[]);

int main()
{
    // char _exp[1000];
    // printf("\nEnter prefix expression: ");
    // scanf("%[^\n]s", _exp);

    // char _exp[] = "+*d-bca"; // (a+(b-c)*d)

    // https://www.cs.kent.edu/~nmadi/CS23001/fix-Quiz.pdf
    // ( ( A + ( B * C ) ) / D )
    char _exp[] = "/ D + * B    C A";

    // ( ( H * ( ( ( ( A + ( ( B + C ) * D ) ) * F ) * G ) * E ) ) + J )
    // char _exp[] = "+ J * * E * G * F + * D + C B A H";

    char stack[MAX_SIZE][MAX_SIZE],
        temp_exp[MAX_SIZE],
        temp,
        op_push_temp[2];

    char *exp = reverse_string(_exp);

    int top, i, j;
    top = -1;
    i = 0;

    while ((temp = exp[i++]) != '\0')
    {
        if (temp == ' ')
            continue;

        else if (!is_operator(temp))
        {
            op_push_temp[0] = temp;
            op_push_temp[1] = '\0';
            push_2d(stack, &top, op_push_temp);
        }

        else
        {
            j = 0;
            temp_exp[j++] = '(';

            // necessary to prevent string.h functions from reading
            // too far
            temp_exp[j] = '\0';

            // append op1 (yes order got reversed)
            strcat(temp_exp, pop_2d(stack, &top));

            j = strlen(temp_exp);
            temp_exp[j++] = temp; // append operator
            temp_exp[j] = '\0';

            strcat(temp_exp, pop_2d(stack, &top)); // append op2

            j = strlen(temp_exp);
            temp_exp[j++] = ')';
            temp_exp[j] = '\0';

            push_2d(stack, &top, temp_exp);
        }
    }

    printf("Given prefix expression:\n%s\n", _exp);

    char *infix = pop_2d(stack, &top);
    printf("\nObtained infix expression:\n%s\n", infix);

    printf("\nObtained postfix expression:\n%s\n\n", convert_infix_postfix(infix));

    return 0;
}

int push_2d(char stack[][MAX_SIZE], int *top, char *item)
{
    if (*top == MAX_SIZE - 1) // stack overflow
        return 0;

    // printf("pushing %s\n", item);

    stack[++*top][0] = '\0';
    strcpy(stack[*top], item);
    stack[*top][strlen(stack[*top])] = '\0';

    return 1;
}

char *pop_2d(char stack[][MAX_SIZE], int *top)
{
    if (*top == -1) // stack underflow
        return NULL;
    // prefix and postfix ops have higher precedence
    // than dereference operator
    return stack[(*top)--];
}

int push(char stack[], int *top, char item)
{
    if (*top == MAX_SIZE - 1) // stack overflow
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

char *convert_infix_postfix(char exp[])
{
    char temp, stack_top;
    char stack[MAX_SIZE];
    int top, i, j;

    char *exp_postfix = (char *)malloc(sizeof(char) * strlen(exp));

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
            continue;
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

char *reverse_string(char inp[])
{
    int len = strlen(inp);

    char *rev = (char *)malloc(len);

    for (int i = len - 1; i >= 0; i--)
        rev[len - i - 1] = inp[i];
    rev[len] = '\0';

    return rev;
}