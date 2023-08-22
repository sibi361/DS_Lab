#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int push(int stack[], int *top, int item);
int pop(int stack[], int *top);
int num_strlen(int input);
void decimal_to_base_less_than_10(int stack[], int *top, int base, unsigned input);
void decimal_to_octal(int stack[], int *top, unsigned input);
void decimal_to_hexadecimal(int stack[], int *top, unsigned input);

void main()
{
    printf("\nDecimal To Another Base Converter Using Stack\n");

    int top = -1, base_new, num_len, temp;
    unsigned num; // to allow large inputs

    printf("\nEnter number: ");
    scanf("%u", &num);
    printf("Enter new base: ");
    scanf("%d", &base_new);

    // printf("\n\n");
    // num = 1234, base_new = 16; // 4D2
    // (3735928559)2 -> (DEADBEEF)16

    num_len = num_strlen(num);
    int stack[num_len * 10];

    switch (base_new)
    {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        decimal_to_base_less_than_10(stack, &top, base_new, num);
        printf("\n# %u converted to base %d:\n", num, base_new);
        break;

    case 16:
        decimal_to_hexadecimal(stack, &top, num);
        printf("\n# %u converted to base 16:\n", num);
        break;

    default:
        printf("\n# Error: Invalid Base: valid bases are 2-9 and 16\n\n");
        exit(0);
    }

    // printing base converted number
    if (base_new == 16)
    {
        temp = pop(stack, &top);
        while (temp != -99999)
        {
            printf("%c", (char)temp);
            temp = pop(stack, &top);
        }
        printf("\n");
    }
    else
    {
        temp = pop(stack, &top);
        while (temp != -99999)
        {
            printf("%d", temp);
            temp = pop(stack, &top);
        }
        printf("\n");
    }

    printf("\n");
}

int push(int stack[], int *top, int item)
{
    if (*top == exp_len - 1) // stack overflow
        return 0;
    stack[++*top] = item;
    return 1;
}

int pop(int stack[], int *top)
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

void decimal_to_base_less_than_10(int stack[], int *top, int base, unsigned input)
{
    do
    {
        push(stack, top, input % base);
    } while (input /= base);
}

void decimal_to_octal(int stack[], int *top, unsigned input)
{
    do
    {
        push(stack, top, input % 8);
    } while (input /= 8);
}

void decimal_to_hexadecimal(int stack[], int *top, unsigned input)
{
    unsigned hex_int;
    char hex_char;
    do
    {
        hex_int = input % 16;
        switch (hex_int)
        {
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            hex_char = hex_int - 10 + 'A';
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            hex_char = (char)(hex_int + '0');
            break;
        default:
            printf("\n# decimal_to_hexadecimal() error: hex_int: %d\n", hex_int);
        }
        push(stack, top, (int)hex_char);
    } while (input /= 16);
}
