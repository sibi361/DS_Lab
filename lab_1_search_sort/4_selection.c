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

void selection_sort(int len, int *src_array, int *array)
{
    printf("Selection sorting\n\n");
    copy_array(len, src_array, array);

    int smallest_index;
    // int ops = 0;
    for (int i = 0; i < len - 1; i++)
    {
        smallest_index = i;
        for (int j = i + 1; j < len; j++)
        {
            // ops++;
            if (array[j] < array[smallest_index])
                smallest_index = j;
        }
        if (smallest_index != i)
            swap(&array[i], &array[smallest_index]);
    }
    // printf("# Selection sort: total runs: %d\n\n", ops);
}

int main()
{
    // int n;
    // printf("Enter length of integer array: ");
    // scanf("%d", &n);
    // int arr[n];
    // get_array(n, arr);

    int arr[] = {20, 40, 3, -10, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Before selection sort:\n");
    print_array(n, arr);

    int sorted_arr[n];
    selection_sort(n, arr, sorted_arr);

    printf("After selection sort:\n");
    print_array(n, sorted_arr);
}
