#include <stdio.h>
#include <string.h>

#define OPENING_TAG "<T>"
#define CLOSING_TAG "</T>"

void push(char stack[][5], int *top, char item[]);
char *pop(char stack[][5], int *top);
int is_opening(char str[], int start_i);
int is_closing(char str[], int start_i);

int MAX;

void main()
{
    int top, i, str_len, closing_invalid = 0;
    char temp;
    // char str[100]; // input string
    // printf("Enter input string: ");
    // scanf("%[^\n]s", str);

    // test cases
    // char str[100] = "<T></T>abc</T><T>def";
    // char str[100] = "catalan<T></T></T></T><T></T>fd";
    char str[100] = "c</T>def";
    // char str[100] = "</T></T><T></T>def</T><T>ghi</T>";

    MAX = str_len = strlen(str);
    char stack[str_len][5];
    top = -1;
    i = 0;

    while (str[i++] != '\0')
        if (str[i] == '<')
            if (is_opening(str, i))
                push(stack, &top, "<T>");
            else if (is_closing(str, i))
                if (strcmp(pop(stack, &top), "\0") == 0)
                    closing_invalid++;

    printf("\ncount = %d\n\n",
           top + closing_invalid + 1);
}

void push(char stack[][5], int *top, char item[])
{
    if (*top == MAX - 1) // stack overflow
        return;
    strcpy(stack[++*top], item);
}

char *pop(char stack[][5], int *top)
{
    if (*top == -1) // stack underflow
        return "\0";

    // prefix and postfix ops have higher precedence
    // than dereference operator
    return stack[(*top)--];
}

int is_opening(char str[], int i)
{
    char temp[4] = "\0";
    int len = strlen(str);

    if (len - i < 3)
        return 0;

    // copy 3 characters starting from index i
    strncpy(temp, &str[i], 3);

    if (strcmp(OPENING_TAG, temp) == 0)
        return 1;
    return 0;
}

int is_closing(char str[], int i)
{
    char temp[5] = "\0";
    int len = strlen(str);

    if (len - i < 4)
        return 0;

    strncpy(temp, &str[i], 4);

    if (strcmp(CLOSING_TAG, temp) == 0)
        return 1;
    return 0;
}
