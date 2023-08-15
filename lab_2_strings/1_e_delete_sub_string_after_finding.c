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
    int l_main = get_string_length(main);
    int l_sub = get_string_length(sub);
    int in = 0, found = 1;
    int new_len = l_main - l_sub;

    for (int i = 0, j = 0; i <= l_main; i++)
    {
        // printf("%d %d %d\n", i, j, in);
        if (in == 1)
        { // inside a probable match
            for (; j < l_sub; j++)
                // printf("## %d %d %c %c\n", i + j - 1, j, main[i + j - 1], sub[j]);

                // traverse main and sub simultaneously
                if (main[i + j - 1] != sub[j])
                {
                    found = 0;
                    break;
                }
            if (found == 1)
                return i - 1;
            else
                in = j = 0; // reset sub's index to its first char
        }
        if (main[i] == sub[j])
            in = j = 1;
    }
    return -1;
}

void delete_substring(char main[], char sub[], int start_i)
{
    int str_len = get_string_length(main);
    int sub_len = get_string_length(sub);
    int new_len = str_len - sub_len;

    for (int i = start_i; i < new_len; i++)
        main[i] = main[i + sub_len];

    main[new_len] = '\0';
}

void main()
{
    // char main[1000];
    // char sub[1000];
    // printf("\nEnter main string: ");
    // gets(main);
    // printf("\nEnter sub string to find: ");
    // gets(sub);

    char main[1000] = "test 01234 5_6789";
    char sub[1000] = "34 5";

    int index_sub = find_substring(main, sub);
    if (index_sub != -1)
        delete_substring(main, sub, index_sub);

    printf("\nMain string after deletion of sub string:\n%s\n", main);
    printf("\n");
}
