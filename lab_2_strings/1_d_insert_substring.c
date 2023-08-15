#include <stdio.h>

int get_string_length(char st[])
{
    int i = 0;
    while (st[i] != '\0')
        i++;
    return i;
}

void insert_substring(char main_str[], char sub_str[], int pos)
{
    int l_main = get_string_length(main_str);
    int l_sub = get_string_length(sub_str);
    int index = pos - 1;
    int new_len = l_main + l_sub;

    if (index < 0 || index > l_main)
    {
        printf("ERROR: given position outside first string\n\n");
        return;
    }

    for (int i = l_main; i >= index; i--)
    {
        // shift all chars after from index
        // by <length of inserted str> characters
        main_str[i + l_sub] = main_str[i];
    }

    for (int i = 0; i < l_sub; i++)
    {
        main_str[index + i] = sub_str[i];
    }

    main_str[new_len] = '\0';
}

void main()
{
    int pos_to_insert;
    // char main[1000];
    // char sub[1000];
    // printf("\nEnter main string: ");
    // gets(main);
    // printf("\nEnter sub string to insert: ");
    // gets(sub);
    // printf("\nEnter position to insert main string in sub string: ");
    // scanf("%d", &pos_to_insert);

    char main[1000] = "12345 678";
    char sub[1000] = "XXX";
    pos_to_insert = 3;

    printf("\nInserting sub string: ");
    puts(sub);
    printf("at position %d in main string: ", pos_to_insert);
    puts(main);
    printf("\n");

    insert_substring(main, sub, pos_to_insert);

    printf("Main string after insertion: ");
    puts(main);

    printf("\n");
}
