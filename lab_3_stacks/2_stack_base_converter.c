#include <stdio.h>
#include <stdlib.h>

int push(char stack[], int *top, int item);
int pop(char stack[], int *top);
int num_strlen(int input);
void change_base(char stack[], int *top, int base, unsigned input);
int num_len, max_size;

void main()
{
    printf("\nBase Converter Using Stack\n");

    int top = -1, base_new, temp;
    unsigned long num; // to allow large inputs

    printf("\nEnter number: ");
    scanf("%u", &num);
    printf("Enter new base: ");
    scanf("%d", &base_new);

    printf("\n");
    // num = 1234, base_new = 16; // 4D2
    //                            // (3735928559)10 = (DEADBEEF)16

    num_len = num_strlen(num);
    max_size = num_len * 10; // assumption
    char stack[max_size];

    if (base_new < 2 || base_new > 36)
    {
        printf("\n# Error: Invalid Base\nValid bases are 2 to 36\n\n");
        exit(0);
    }
    else
        change_base(stack, &top, base_new, num);
    printf("\n%u converted to base %d:\n", num, base_new);

    // printing base converted number
    temp = pop(stack, &top);
    while (temp != -99999)
    {
        printf("%c", temp);
        temp = pop(stack, &top);
    }

    printf("\n\n");
}

int push(char stack[], int *top, int item)
{

    if (*top == max_size - 1) // stack overflow
        return 0;
    stack[++*top] = item;
    return 1;
}

int pop(char stack[], int *top)
{
    if (*top == -1) // stack underflow
        return -99999;

    // prefix and postfix ops have higher precedence
    // than dereference operator
    return stack[(*top)--];
}

int num_strlen(int input)
{
    int len = 1;
    while (input /= 10)
        len++;
    return len;
}

void change_base(char stack[], int *top, int base, unsigned input)
{
    unsigned long num;
    char character;
    do
    {
        num = input % base;

        if (num >= 0 && num <= 9)
            character = num + '0';
        else if (num >= 10 && num <= 36)
            character = num - 10 + 'A';

        push(stack, top, character);
    } while (input /= base);
}
