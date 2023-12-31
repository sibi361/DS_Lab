#include <stdio.h>

void get_array(int len, int *array)
{
    printf("\nEnter the elements:\n");
    for (int i = 0; i < len; i++)
    {
        scanf("%d", &array[i]);
    }
}

void print_array(int len, int *array)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", *(array + i));
    }
    printf("\n\n");
}

void copy_array(int len, int *src, int *dest)
{
    for (int i = 0; i < len; i++)
        dest[i] = src[i];
}

void swap(int *a, int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void bubble_sort(int len, int *src_array, int *array)
{
    printf("Bubble sorting\n\n");
    copy_array(len, src_array, array);

    int swapped = 0;
    // int ops = 0;
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            // ops++;
            if (array[j] > array[j + 1])
            {
                swapped = 1;
                swap(&array[j], &array[j + 1]);
            }
        }
        if (!swapped)
            break;
    }
    // printf("# bubble sort: total runs: %d\n\n", ops);
}

int main()
{
    // int n;
    // printf("Enter length of integer array: ");
    // scanf("%d", &n);
    // int arr[n];
    // get_array(n, arr);

    // int arr[] = {1, 2, 3, 4, 5}; // reason for swapped test
    int arr[] = {20, 40, 3, -10, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Before bubble sort:\n");
    print_array(n, arr);

    int sorted_arr[n];
    bubble_sort(n, arr, sorted_arr);

    printf("After bubble sort:\n");
    print_array(n, sorted_arr);
}
