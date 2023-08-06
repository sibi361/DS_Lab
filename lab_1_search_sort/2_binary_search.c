#include <stdio.h>

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

int binary_search(int len, int array[], int query)
{
    printf("Binary search\n");

    int lo = 0, hi = len - 1;
    int mid, key;

    do
    {
        mid = lo + (hi - lo) / 2;
        key = array[mid];

        if (key < query)
            lo = mid + 1;
        else if (key > query)
            hi = mid - 1;
    } while (lo <= hi && key != query);

    if (key == query)
        return mid;
    return -1;
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

    printf("\nGiven array having %d elements:\n", n);
    print_array(n, arr);

    int sorted_arr[n];
    bubble_sort(n, arr, sorted_arr);

    printf("\nGiven array after sorting\n");
    print_array(n, sorted_arr);

    int search;
    // printf("Enter search query: ");
    // scanf("%d", &search);
    search = 40;

    int found_index = binary_search(n, sorted_arr, search);
    found_index == -1 ? printf("query %d NOT found in array", search)
                      : printf("query %d found at index %d", search, found_index);

    printf("\n\n");
}
