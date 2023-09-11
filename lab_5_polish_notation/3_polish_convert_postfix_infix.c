// Polish Notation
// Conversion of postfix expression to infix expression

// WIP

#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

int is_operator(char operator);
int push(char stack[], int *top, char item);
char pop(char stack[], int *top);

int main()
{
    // char exp[1000]; // input infix expression
    // printf("\nEnter infix expression: ");
    // scanf("%[^\n]s", exp);

    // https://www.cs.kent.edu/~nmadi/CS23001/fix-Quiz.pdf
    char exp[] = "abc-d*+"; // (a+(b-c)*d)
    // char exp[] = "A B    C * + D /"; // : ( ( A + ( B * C ) ) / D )

    char exp_infix[MAX_SIZE],
        stack[MAX_SIZE],
        temp_exp[MAX_SIZE],
        op1,
        op2,
        temp;

    int top, i, j, first_run;
    top = -1;
    i = 0, first_run = 1;

    while ((temp = exp[i++]) != '\0')
    {
        if (temp == ' ')
            continue;

        if (!is_operator(temp))
            push(stack, &top, temp);

        else
        {
            j = 0;
            temp_exp[j++] = '(';

            op2 = pop(stack, &top);
            if (first_run)
            {
                op1 = pop(stack, &top);
                temp_exp[j++] = op1;
                first_run = 0;
            }
            else
            {
                temp_exp[j] = '\0';
                strcat(temp_exp, exp_infix);
                j += strlen(exp_infix);
            }

            temp_exp[j++] = temp;
            temp_exp[j++] = op2;
            temp_exp[j++] = ')';
            temp_exp[j] = '\0';

            strcpy(exp_infix, temp_exp);
            exp_infix[strlen(exp_infix)] = '\0';
        }
    }

    printf("\nObtained infix expression:\n%s\n\n", exp_infix);
    return 0;
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
