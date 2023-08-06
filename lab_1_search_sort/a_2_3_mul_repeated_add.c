#include <stdio.h>

int multiply(int sum, int times_left)
{
    if (times_left < 2)
        return sum;
    return sum + multiply(sum, times_left - 1);
}

int main()
{
    int a, b;
    a = 2, b = 10;
    // printf("Enter A and B as AxB: ");
    // scanf("%dx%d", &a, &b);

    printf("%d * %d = %d\n", a, b, multiply(a, b));
}
