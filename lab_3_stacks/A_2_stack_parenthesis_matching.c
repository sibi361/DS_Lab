#include <stdio.h>
#include <string.h>

void push(char stack[], int *top, int expression_length, int item);
char pop(char stack[], int *top);

void main()
{
    printf("\nParenthesis Matching Using Stack\n\n");

    int top, exp_len, valid = 1;
    char temp, popped;
    char exp[100]; // expression
    printf("Enter expression: ");
    scanf("%[^\n]s", exp);

    // test cases
    // char exp[100] = "b * (c + [d / e] * f)";
    // char exp[100] = "b * (c + [d / e) * f]";
    // char exp[100] = "b * (c + [d / e] * f) * 2)";
    // printf("%s\n", exp);

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

            // reason for wrong output i.e. "{[}]" being returned
            // as valid:
            // if (temp == ')' && popped != '(' |
            // temp == ']' && popped != '[' |
            // temp == '}' && popped != '{') {...}

            // [ | ] > [ && ] in precedence hence it would
            // evaluate as follows:
            // if(temp == ')' && 0 && 0 && popped != '{' = 0) {...}

            // fixed it by switching to short-circuit OR [ || ]
            // as if any one of the bracket mismatch conditions evaluates
            // to true, the expression is to be declared invalid

            // another possible fix:
            // if ((temp == ')' && popped != '(') |
            //     (temp == ']' && popped != '[') |
            //     (temp == '}' && popped != '{')) {...}
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
