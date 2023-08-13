#include <stdio.h>

int get_string_length(char st[])
{
    int i = 0;
    while (st[i] != '\0')
        i++;
    return i;
}

void str_concat(char a[], char b[])
{
    int len_a = get_string_length(a);
    int len_b = get_string_length(b);
    int len_new = len_a + len_b;

    for (int i = 0; i < len_b; i++)
        a[len_a + i] = b[i];
    a[len_new] = '\0';
}

void main()
{
    // char str1[1000];
    // char str2[1000];
    // printf("\nEnter string 1: ");
    // gets(str1);
    // printf("\nEnter string 2: ");
    // gets(str2);
    char str1[2000] = "<this is first string >";
    char str2[1000] = "<and this is 2nd string>";

    str_concat(str1, str2);

    printf("\nFirst string after concatenation:\n");
    puts(str1);

    printf("\n");
}
