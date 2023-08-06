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

int multiply_matrices(int rows_a, int cols_a, int rows_b, int cols_b,
                      int a[][2], int b[][2])
{
    int c[rows_a][cols_b];
    for (int i = 0; i < rows_a; i++)
        for (int j = 0; j < cols_b; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < rows_b; k++)
                c[i][j] += a[i][k] * b[k][i];
        }

    print_matrix(rows_a, cols_b, c);
}

int main()
{
    int m, n, o, p;
    // printf("Matrix A: Enter rows and cols as MxN: ");
    // scanf("%dx%d", &m, &n);
    // printf("Matrix B: Enter rows and cols as MxN: ");
    // scanf("%dx%d", &o, &p);

    m = n = o = p = 2;
    // int a[m][n];
    // int b[o][p];

    int a[2][2] = {1, 2, 3, 4};
    int b[2][2] = {1, 1, 1, 1};

    // read_matrix(m, n, &a);
    // read_matrix(o, p, &b);

    print_matrix(m, n, a);
    print_matrix(o, p, b);

    multiply_matrices(m, n, o, p, a, b);
}
