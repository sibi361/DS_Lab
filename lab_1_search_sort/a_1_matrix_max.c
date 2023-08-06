#include <stdio.h>

int MAT_COLS = 2;

int read_matrix(int rows, int cols, int matrix[][MAT_COLS])
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < rows; j++)
        {
            printf("Enter element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
}

int print_matrix(int rows, int cols, int matrix[][MAT_COLS])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)

            printf("%d ", *(*(matrix + i) + j));

        printf("\n");
    }
    printf("\n");
}

int matrix_max(int rows, int cols, int a[][2], int b[][2])
{
    int c[rows][cols];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            if (a[i][j] > b[i][j])
                c[i][j] = a[i][j];
            else
                c[i][j] = b[i][j];
        }

    print_matrix(rows, cols, c);
    return &c;
}

int main()
{
    int m, n, o, p;
    // printf("Matrix A: Enter rows and cols as MxN: ");
    // scanf("%dx%d", &m, &n);

    m = n = 2;
    // int a[m][n];
    // int b[o][p];

    // read_matrix(m, n, a);
    // read_matrix(o, p, &b);

    int a[2][2] = {1, 2, 3, 4};
    int b[2][2] = {1, 1, 1, 1};

    printf("Matrix A:\n");
    print_matrix(m, n, a);
    printf("Matrix B:\n");
    print_matrix(m, n, b);

    printf("Matrix max():\n");
    matrix_max(m, n, a, b);
}
