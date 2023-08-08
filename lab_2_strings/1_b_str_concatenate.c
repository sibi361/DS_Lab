#include <stdio.h>

int get_string_length(char st[]){
    int i = 0;
    while(st[i] != '\0')
            i++;
    return i;
}

int str_concat(char s1[], char s2[], char s3[]){
    int l1 = get_string_length(s1);
    int l2 = get_string_length(s2);
    int l3 = l1 + l2;
    int i = 0, j = 0;

    for (; i < l1; i++)
        s3[i] = s1[i];
    for (; i < l3; i++, j++)
        s3[i] = s2[j];
    s3[l3] = '\0';
}

int main()
{
    //char str1[1000];
    //char str2[1000];
    //printf("\nEnter string 1: ");
    //gets(str1);
    //printf("\nEnter string 2: ");
    //gets(str2);
    char str1[1000] = "<this is first string >";
    char str2[1000] = "<and this is 2nd string>";

    char str3[2000];
    str_concat(str1, str2, str3);

    printf("\nConcatenated string:\n");
    puts(str3);

    printf("\n");
}
