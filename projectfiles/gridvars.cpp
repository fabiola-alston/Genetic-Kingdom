#include "gridvars.h"

int GRID_X = 0;
int GRID_Y = 0;

int gridMap[GRID_SIZE][GRID_SIZE];
bool pathUpdate = false;

Vector2 GridToPixel(int col, int row)
{
    return {
        (float)(GRID_X + col * CELL_SIZE),
        (float)(GRID_Y + row * CELL_SIZE)
    };
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


