/*
Polish Notation
Evaluation of prefix expression

method: convert prefix to postfix and evaluate postfix with a modification

 /*
Since the input postfix exp is obtained by reversing a valid prefix expression,
terms get swapped eg. bc- => (b - c) when reversed would be -cb => (c - b)
to fix this operands have to be swapped
so the first value popped will become the first operand for the evaluation
and the second one will be op2
opposite to what was done in the normal postfix evaluate script
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 1000

int eval_postfix_ie_reversed_prefix(char exp[]);
int is_operator(char operator);
int push(int stack[], int *top, int item);
int pop(int stack[], int *top);
char *reverse_string(char inp[]);

void main()
{
    // char _exp[MAX_SIZE];
    // printf("\nEnter prefix expression: ");
    // scanf("%[^\n]s", _exp);

    // test cases
    // 9-((8/2)*(2+3)) = -11
    char _exp[MAX_SIZE] = "-9*/82+23";

    // (6 - 3) * (4 + 5) = 27
    // char _exp[MAX_SIZE] = "*-63+45"; // correct prefix exp doesn't

    char *exp = reverse_string(_exp);

    printf("\nResult = %d\n\n", eval_postfix_ie_reversed_prefix(exp));
}

int eval_postfix_ie_reversed_prefix(char exp[])
{
    char temp, op1, op2;
    int stack[MAX_SIZE];
    int top = -1, i = 0;
    double result = 0;

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
            op1 = pop(stack, &top);
            op2 = pop(stack, &top);

            switch (temp)
            {
            case '^':
                result = pow(op1, op2);
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

char *reverse_string(char inp[])
{
    int len = strlen(inp);

    char *rev = (char *)malloc(len);

    for (int i = len - 1; i >= 0; i--)
        rev[len - i - 1] = inp[i];
    rev[len] = '\0';

    return rev;
}
