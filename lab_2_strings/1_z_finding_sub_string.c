#include <stdio.h>

int get_string_length(char st[])
{
    int i = 0;
    while (st[i] != '\0')
        i++;
    return i;
}

int find_substring(char main[], char sub[])
{
    // returns index of first match

    int l_main = get_string_length(main);
    int l_sub = get_string_length(sub);
    int in = 0, found = 1, i, j;
    int new_len = l_main - l_sub;

    for (i = 0, j = 0; i <= l_main; i++)
    {
        // printf("%d %d %d\n", i, j, in);
        if (in == 1)
        {
            for (; j < l_sub; j++)
            {
                // printf("## %d %c %c\n", j, main[i + j - 1], sub[j]);
                if (main[i + j - 1] != sub[j])
                {
                    found = 0;
                    break;
                }
            }
            if (found == 1)
                return i - 1;
            else
                in = j = 0;
        }
        if (main[i] == sub[j])
            in = j = 1;
    }
    return -1;
}

int main()
{
    // char main[1000];
    // char sub[1000];
    // printf("\nEnter main string: ");
    // gets(main);
    // printf("\nEnter sub string to find: ");
    // gets(sub);

    char main[1000] = "01234 5678 testing\nnext line";
    char sub[1000] = "4 5678";

    printf("\nFinding sub string: ");
    puts(sub);
    printf("in main string: ");
    puts(main);
    printf("\n");

    int index = find_substring(main, sub);

    // printf("Main string after deleting of sub string: ");
    // puts(main);

    printf("Index of substring: %d\n", index);
}
