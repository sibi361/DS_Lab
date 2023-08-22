#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// short circuit AND / OR [ && / | ] stops checking i.e. evaluating
// once [ falsy / truthy ] value is encountered

// logical AND / OR [ & / | ]

int main()
{
    int m, n, o;
    m = n = o = 1;
    // n = 2;
    // o = 3;

    // first one was true, so next not checked
    if (m++ == 1 || n++ == 1 || o++ == 1)
        printf("|| %d  %d %d\n", m, n, n);

    // logical checks all
    m = n = o = 1;
    if (m++ == 1 | n++ == 1 | o++ == 1)
        printf("| %d  %d %d\n", m, n, n);

    m = n = o = 0;
    if (m++ == 1 && n++ == 1 && o++ == 1)
        printf("&& %d %d %d\n", m, n, 0);
    printf("&& %d %d %d\n", m, n, 0);

    m = n = o = 0;
    if (m++ == 1 & n++ == 1 & o++ == 1)
        printf("& %d %d %d\n", m, n, 0);
    printf("& %d %d %d\n", m, n, 0);

    printf("\n");

    m = n = o = 1;
    printf("%d \n", m++ | n++ | o++); // evaluates all
    printf("%d %d %d \n", m, n, o);

    m = n = o = 1;
    printf("%d \n", m++ || n++ || o++); // evaluates only first one i.e. m++
    printf("%d %d %d \n", m, n, o);
}
