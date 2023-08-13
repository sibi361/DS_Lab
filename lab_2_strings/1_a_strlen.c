#include <stdio.h>

int get_string_length(char st[])
{
    int i = 0;
    for (; st[i] != '\0'; i++)
        ;
    return i;
}

void main()
{
    // char str[1000];
    // printf("\nEnter string: ");
    // gets(str);
    char str[1000] = "spaces and symbols @#";

    int strlen = get_string_length(str);
    printf("The length of the given string is %d characters", strlen);

    printf("\n\n");
}
