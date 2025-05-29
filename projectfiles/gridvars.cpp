#include "gridvars.h"

int gridMap[GRID_SIZE][GRID_SIZE];

Vector2 GridToPixel(int col, int row)
    {
        return {(float)(col * CELL_SIZE), (float)(row * CELL_SIZE)};
    }

Vector2 PixelToGrid(int x, int y)
{
    return {(float)(x / CELL_SIZE), (float)(y / CELL_SIZE)};
}

void InitGridMap()
{
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            gridMap[row][col] = 0; 
        }
    }
}


