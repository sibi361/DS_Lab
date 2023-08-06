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

void move_within_array(int len, int *array, int i_get, int i_put)
{
    int element = array[i_get];
    for (int i = i_get; i > i_put; i--)
    {
        array[i] = array[i - 1];
    }
    array[i_put] = element;
}

void insertion_sort(int len, int *src_array, int *array)
{
    printf("Insertion sorting\n\n");
    copy_array(len, src_array, array);

    int key, j;
    // int ops = 0;
    for (int i = 1; i < len; i++)
    {
        key = array[i];
        for (j = i; array[j - 1] > key && j >= 1; j--)
            ;
        // ops++;
        if (j < i) // j: index of last element from right which is > key
        {
            // one element to the right of the sorted sub-array,
            // (which starts from left), i.e. the key, is placed
            // in it's right place within the sorted sub-array
            move_within_array(len, array, i, j);
        }
    }
    // printf("# Insertion sort: total runs: %d\n\n", ops);
}

int main()
{
    // int n;
    // printf("Enter length of integer array: ");
    // scanf("%d", &n);
    // int arr[n];
    // get_array(n, arr);

    // int arr[] = {1, 3, 2, 4, 5};
    int arr[] = {20, 40, 3, -10, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Before insertion sort:\n");
    print_array(n, arr);

    int sorted_arr[n];
    insertion_sort(n, arr, sorted_arr);

    printf("After insertion sort:\n");
    print_array(n, sorted_arr);
}
