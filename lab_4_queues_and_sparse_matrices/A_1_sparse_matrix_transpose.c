#include <stdio.h>
#include <stdlib.h>

// #define DEFAULT_ROWS 0 // [if (non_zero_count > 0) ...] not required
// #define DEFAULT_COLUMNS 0
// #define DEFAULT_ROWS 3
// #define DEFAULT_COLUMNS 3
// #define DEFAULT_ROWS 5
// #define DEFAULT_COLUMNS 3
#define DEFAULT_ROWS 3
#define DEFAULT_COLUMNS 5

typedef struct
{
    int row, col, val;
} sparse;

int m, n;

int get_matrix(int mat[][n], int rows, int cols);
int get_matrix_non_zero_count(int mat[][n], int rows, int cols);
void convert_to_sparse_matrix(int mat[][n], int rows, int cols,
                              sparse mat_sparse[]);
void sparse_matrix_transpose(sparse mat_sparse[],
                             sparse mat_sparse_transpose[]);
void print_sparse_matrix(sparse mat_sparse[]);
void print_sparse_matrix_normally(sparse mat_sparse[]);
void print_matrix(int mat[][n], int rows, int cols);

void main()
{
    int non_zero_count, matrix_size;
    // printf("Enter number of rows and cols as m n\n");
    // scanf("%d %d", &m, &n);

    m = DEFAULT_ROWS;
    n = DEFAULT_COLUMNS;

    // int mat[m][n];
    // printf("Enter matrix:\n");
    // non_zero_count = get_matrix(mat, m, n);

    // test cases
    // int mat[][0] = {};
    // int mat[][DEFAULT_COLUMNS] = {{0, 1, 0}, {0, 0, 2}, {3, 0, 0}};
    // int mat[][DEFAULT_COLUMNS] = {{12, 10, 0},
    //                               {0, 0, 56},
    //                               {67, 0, 0},
    //                               {0, -2, 0},
    //                               {0, 2, 1}};
    int mat[][DEFAULT_COLUMNS] = {{12, 10, 0, 0, 0},
                                  {0, 0, 56, -7, 0},
                                  {67, 8, 0, 0, 39}};

    non_zero_count = get_matrix_non_zero_count(mat, m, n);
    matrix_size = m * n / 2;
    if (non_zero_count > matrix_size)
    {
        printf("\nERROR: Given matrix is NOT sparse as count(non-zero elements)\
[%d] is > half the matrix size[%d]\n\n",
               non_zero_count, matrix_size);
        exit(0);
    }

    sparse mat_sparse[non_zero_count]; // less than half will be non-zero

    printf("Given matrix:\n");
    print_matrix(mat, m, n);

    convert_to_sparse_matrix(mat, m, n, mat_sparse);

    printf("\nSparse matrix before transpose:\n");
    print_sparse_matrix(mat_sparse);

    sparse mat_sparse_transpose[non_zero_count];
    sparse_matrix_transpose(mat_sparse, mat_sparse_transpose);

    printf("\nSparse matrix after transpose:\n");
    print_sparse_matrix(mat_sparse_transpose);

    printf("\nGiven matrix after transpose:\n");
    print_sparse_matrix_normally(mat_sparse_transpose);

    printf("\n");
}

int get_matrix(int mat[][n], int rows, int cols)
{
    int non_zero_count = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            scanf("%d", &mat[i][j]);
            if (mat[i][j] != 0)
                ++non_zero_count;
        }
    return non_zero_count;
}

int get_matrix_non_zero_count(int mat[][n], int rows, int cols)
{
    int non_zero_count = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (mat[i][j] != 0)
                ++non_zero_count;
    return non_zero_count;
}

void convert_to_sparse_matrix(int mat[][n], int rows, int cols,
                              sparse mat_sparse[])
{
    int k = 0; // non-zero count
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (mat[i][j] != 0)
            {
                ++k;
                mat_sparse[k].row = i;
                mat_sparse[k].col = j;
                mat_sparse[k].val = mat[i][j];
            }

    // adding metadata
    mat_sparse[0].row = rows;
    mat_sparse[0].col = cols;
    mat_sparse[0].val = k;
}

void sparse_matrix_transpose(sparse mat_sparse[], sparse mat_sparse_transpose[])
{
    int rows = mat_sparse[0].row,
        cols = mat_sparse[0].col,
        non_zero_count = mat_sparse[0].val,
        k = 1; // mat_sparse_transpose index

    // swapping rows and columns in metadata
    mat_sparse_transpose[0].row = mat_sparse[0].col;
    mat_sparse_transpose[0].col = mat_sparse[0].row;
    mat_sparse_transpose[0].val = mat_sparse[0].val;

    for (int col = 0; col < cols; col++)
    {
        for (int i = 1; i <= non_zero_count; i++)
            if (mat_sparse[i].col == col)
            {
                mat_sparse_transpose[k].col = mat_sparse[i].row;
                mat_sparse_transpose[k].row = mat_sparse[i].col;
                mat_sparse_transpose[k].val = mat_sparse[i].val;
                k++;
            }
    }

    /*
    previous incorrect code:
    int end;
    if (cols > rows)
        end = cols;
    else
        end = rows;
    for (int row = 0; row < end; col++){ // row by row
        // ...
            if (mat_sparse[i].col == col)
    }

    We were going row by row instead of going by columns. This was
    the cause of the last few rows (in the result) being blank as
    the row variable never reached those columns
    (in the original matrix), in cases where COLS > ROW and hence
    they were never evaluated by the if block.

    Fix:
    for (int col = 0; col < cols; col++)
    Always go by columns since the if block is checking for column
    match. When cols > rows, all of them will be scanned and same
    goes for when cols < rows as the second loop i.e.
    for (int i = 1; i <= non_zero_count; i++)
    will go through every value and hence every row.
    */
}

void print_sparse_matrix(sparse mat_sparse[])
{
    int non_zero_count = mat_sparse[0].val;
    printf("id\tRow\tColumn\tValue\n");
    for (int i = 0; i <= non_zero_count; i++)
        printf("%d\t%d\t%d\t%d\n",
               i,
               mat_sparse[i].row,
               mat_sparse[i].col,
               mat_sparse[i].val);
}

void print_sparse_matrix_normally(sparse mat_sparse[])
{
    int rows = mat_sparse[0].row,
        cols = mat_sparse[0].col,
        non_zero_k = 1;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            if (i == mat_sparse[non_zero_k].row &&
                j == mat_sparse[non_zero_k].col)
                printf("%d\t", mat_sparse[non_zero_k++].val);
            else
                printf("0\t");
        printf("\n");
    }
}

void print_matrix(int mat[][n], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%d\t", mat[i][j]);
        printf("\n");
    }
}
