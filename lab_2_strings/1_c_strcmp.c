#include <stdio.h>

int get_string_length(char st[]){
    int i = 0;
    while(st[i] != '\0')
            i++;
    return i;
}

int str_cmp(char s1[], char s2[]){
    int l1 = get_string_length(s1);
    int l2 = get_string_length(s2);
    int max = l1;
    if (l1 < l2)
        max = l2;

    for (int i = 0; i < max; i++)
        if ((s1[i] == '\0' && s2[i] != '\0') || s1[i] < s2[i])
            return -1;
        else if ((s1[i] != '\0' && s2[i] == '\0') ||  s1[i] > s2[i])
            return 1;

    return 0;
}

int main()
{
    //char str1[1000];
    //char str2[1000];
    //printf("\nEnter string 1: ");
    //gets(str1);
    //printf("\nEnter string 2: ");
    //gets(str2);
    char str1[1000] = "aaa";
    char str2[1000] = "b";

    printf("Given first string: ");
    puts(str1);
    printf("Given second string: ");
    puts(str2);
    printf("\n");

    int result = str_cmp(str1, str2);

    switch(result){
    case 0:
        printf("Both strings are equal\n");
        break;
    case -1:
        printf("str_1 < str_2\n");
        break;
    case 1:
        printf("str_1 > str_2\n");
        break;
    default:
        printf("str_cmp() error\n");
    }

    printf("\n");
}
