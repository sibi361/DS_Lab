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

int linear_search(int len, int *array, int query)
{
    printf("Linear search: ");
    for (int i = 0; i < len; i++)
    {
        if (array[i] == query)
        {
            return i;
        }
    }
    return -1;
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

    printf("\nGiven array having %d elements:\n", n);
    print_array(n, arr);

    int search;
    // printf("Enter search query: ");
    // scanf("%d", &search);
    search = -10;

    int found_index = linear_search(n, arr, search);
    found_index == -1 ? printf("query %d NOT found in array", search)
                      : printf("query %d found at index %d", search, found_index);

    printf("\n\n");
}
