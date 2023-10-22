// Polish Notation
// Conversion of prefix expression to infix expression

/*
method: reverse prefix followed by modified postfix -> infix

modification: do not save op2 i.e. when operator found,
first one popped is appended to final expression right away
followed by the second one popped
opposite to how it was done in postfix -> infix
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 1000

int is_operator(char operator);
int push_2d(char stack[][MAX_SIZE], int *top, char *item);
char *pop_2d(char stack[][MAX_SIZE], int *top);
char *reverse_string(char inp[]);

void main()
{
    // char _exp[1000];
    // printf("\nEnter prefix expression: ");
    // scanf("%[^\n]s", _exp);

    // char _exp[] = "+*d-bca"; // (a+(b-c)*d)

    // https://www.cs.kent.edu/~nmadi/CS23001/fix-Quiz.pdf
    // ( ( A + ( B - C ) ) / D )
    char _exp[] = "+ A / - B C D";

    // ( ( H * ( ( ( ( A + ( ( B + C ) * D ) ) * F ) * G ) * E ) ) + J )
    // char _exp[] = "+ J * * E * G * F + * D + C B A H";

    char stack[MAX_SIZE][MAX_SIZE],
        temp_exp[MAX_SIZE],
        op2[MAX_SIZE],
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

            strcat(temp_exp, pop_2d(stack, &top)); // append op1

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

    printf("\nObtained infix expression:\n%s\n\n", pop_2d(stack, &top));
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
