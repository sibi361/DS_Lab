// Polish Notation
// Conversion of postfix expression to infix expression

#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

int is_operator(char operator);
int push_2d(char stack[][MAX_SIZE], int *top, char *item);
char *pop_2d(char stack[][MAX_SIZE], int *top);

int main()
{
    // char exp[1000]; // input infix expression
    // printf("\nEnter infix expression: ");
    // scanf("%[^\n]s", exp);

    char exp[] = "abc-d*+"; // (a+(b-c)*d)

    // https://www.cs.kent.edu/~nmadi/CS23001/fix-Quiz.pdf
    // ( ( A + ( B * C ) ) / D )
    // char exp[] = "A B    C * + D /";

    // ( ( H * ( ( ( ( A + ( ( B + C ) * D ) ) * F ) * G ) * E ) ) + J )
    // char exp[] = "H A B C + D * + F * G * E * * J +";

    char exp_infix[MAX_SIZE][MAX_SIZE],
        temp_exp[MAX_SIZE],
        op2[MAX_SIZE],
        temp,
        op_push_temp[2];

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
            push_2d(exp_infix, &top, op_push_temp);
        }

        else
        {
            j = 0;
            temp_exp[j++] = '(';

            // necessary to prevent string.h functions from reading
            // too far
            temp_exp[j] = '\0';

            strcpy(op2, pop_2d(exp_infix, &top)); // save op2

            strcat(temp_exp, pop_2d(exp_infix, &top)); // append op1

            j = strlen(temp_exp);
            temp_exp[j++] = temp; // append operator
            temp_exp[j++] = '\0';

            strcat(temp_exp, op2); // append op2

            j = strlen(temp_exp);
            temp_exp[j++] = ')';
            temp_exp[j] = '\0';

            push_2d(exp_infix, &top, temp_exp);
        }
    }

    printf("Given postfix expression:\n%s\n", exp);

    printf("\nObtained infix expression:\n%s\n\n", pop_2d(exp_infix, &top));
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
