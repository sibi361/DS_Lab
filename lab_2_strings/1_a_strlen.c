#include <stdio.h>

int get_string_length(char st[]){
    int i = 0;
    while(st[i] != '\0')
            i++;
    return i;
}

int main()
{
    //char str[1000];
    //printf("\nEnter string: ");
    //gets(str);
    char str[1000] = "test  space 1$%&*\n 5678";

    int strlen = get_string_length(str);
    printf("The length of the given string is %d characters", strlen);

    printf("\n\n");
}
