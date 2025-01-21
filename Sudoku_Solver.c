// Libraries
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Global variables
#define N 9
int count = 0;


// Functions
int print(int grid[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", grid[i][j]);
            if ((j + 1) % 3 == 0)
            {
                printf("| ");
            }
        }
        printf("\n");
        if ((i + 1) % 3 == 0 && i != 0)
        {
            printf("------------------------\n");
        }
    }
}

bool checkBox(int grid[N][N], int row, int col, int num)
{
    int horizontalShift = floor(row / 3);
    int verticalShift = floor(col / 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i + 3 * horizontalShift][j + 3 * verticalShift] == num)
            {
                return true;
            }
        }
    }
    return false;
}

bool checkRow(int grid[N][N], int row, int num)
{
    for (int i = 0; i < N; i++)
    {
        if (grid[row][i] == num)
        {
            return true;
        }
    }
    return false;
}

bool checkCol(int grid[N][N], int col, int num)
{
    for (int i = 0; i < N; i++)
    {
        if (grid[i][col] == num)
        {
            return true;
        }
    }
    return false;
}

bool checkPoint(int grid[N][N], int row, int col, int num)
{
    if (!checkBox(grid, row, col, num) && !checkCol(grid, col, num) && !checkRow(grid, row, num))
    {
        return true;
    }
    return false;
}


bool solveSudoku(int grid[N][N], int row, int col)
{
    count += 1;
    if (row == 9)
    {
        return true;
    }

    else if (col == 9)
    {
        return (solveSudoku(grid, row+1, 0));
    }

    else if (grid[row][col] != 0)
    {
        solveSudoku(grid, row, col + 1);
    }

    else
    {
        for (int x = 1; x < 10; x++)
        {
            if (checkPoint(grid, row, col, x))
            {
                grid[row][col] = x;

                if(solveSudoku(grid,row,col + 1))
                {
                    return true;
                }
                grid[row][col] = 0;
            }
        } 
        return false;
    }
}

int main()
{
    // This is hard coding to receive the ”grid "
    int grid[N][N] = {
        {0, 0, 0, 6, 0, 0, 4, 0, 0},
        {7, 0, 0, 0, 0, 3, 6, 0, 0},
        {0, 0, 0, 0, 9, 1, 0, 8, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 5, 0, 1, 8, 0, 0, 0, 3},
        {0, 0, 0, 3, 0, 6, 0, 4, 5},
        {0, 4, 0, 2, 0, 0, 0, 6, 0},
        {9, 0, 3, 0, 0, 0, 0, 0, 0},
        {0, 2, 0, 0, 0, 0, 1, 0, 0}};

    printf("The input Sudoku puzzle: \n");
    print(grid);
    if (solveSudoku(grid, 0, 0))
    {
        printf("Solution found after %d iterations: \n", count);
        print(grid);
    }
    else
    {
        printf("No solution exists.\n");
    }
    return 0;
}