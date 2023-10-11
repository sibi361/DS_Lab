#include <stdio.h>
#include <string.h>

void push(char stack[], int *top, int expression_length, int item);
char pop(char stack[], int *top);
int is_operator(char operator);

void main()
{
    int top, exp_len, valid = 1;
    char temp, popped;
    // char exp[100]; // expression
    // printf("Enter expression: ");
    // scanf("%[^\n]s", exp);

    // test cases
    // char exp[100] = "a +";
    char exp[100] = "a + b";
    // char exp[100] = "+ a + b"; // doesn't work for this
    // char exp[100] = " + a + b"; // doesn't work for this
    // char exp[100] = "(a + b";
    // char exp[100] = "(a + b  )";
    // printf("%s\n", exp);

    exp_len = strlen(exp);
    char stack_opening[exp_len];
    top = -1;

    // pushing characters from expression to stack
    for (int i = 0; i < exp_len; i++)
    {
        if ((i == 0 || i == exp_len - 1) && is_operator(exp[i]))
        {
            valid = 0;
            break;
        }

        temp = exp[i];
        if (temp == '(' || temp == '[' || temp == '{')
        {
            push(stack_opening, &top, exp_len, exp[i]);
            // printf("PUSH %c\n", temp);
        }
        else if (temp == ')' || temp == ']' || temp == '}')
        {
            popped = pop(stack_opening, &top);
            // printf("POP %c %c\n", temp, popped);

            if (temp == ')' && popped != '(' ||
                temp == ']' && popped != '[' ||
                temp == '}' && popped != '{')
            {
                valid = 0;
                break;
            }
        }
    }

    if (valid && top == -1)
        printf("Given expression is balanced\n");
    else
        printf("Given expression is NOT balanced\n");

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