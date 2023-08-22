#include <stdio.h>
#include <string.h>

int push(char stack[], int *top, int item);
int pop(char stack[], int *top);
int string_len;

void main()
{
    printf("\nPalindrome Checking Using Stack\n");

    char str[1000];
    int top = -1, palindrome = 1;

    printf("\nEnter string: ");
    fgets(str, 1000, stdin);

    string_len = strlen(str);
    char stack[string_len - 1];

    // i < string_len - 1 in order to exclude the null character
    for (int i = 0; i < string_len - 1; i++)
        push(stack, &top, str[i]);

    for (int i = 0; i < string_len / 2; i++)
        if (pop(stack, &top) != str[i])
        {
            palindrome = 0;
            break;
        }

    if (palindrome == 1)
        printf("\nGiven string is a palindrome\n");
    else
        printf("\nGiven string is NOT a palindrome\n");
    printf("\n");
}

int push(char stack[], int *top, int item)
{
    if (*top == string_len - 1) // stack overflow
        return 0;
    stack[++*top] = item;
    return 1;
}

int pop(char stack[], int *top)
{
    if (*top == -1) // stack underflow
        return -99999;

    // prefix and postfix ops have higher precedence
    // than dereference operator
    return stack[(*top)--];
}
