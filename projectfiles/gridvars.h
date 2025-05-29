#ifndef GRIDVARS_H
#define GRIDVARS_H

#include "raylib.h"

#define GRID_SIZE 20
#define BUTTON_SIZE 30
#define GAP 3
#define CELL_SIZE (BUTTON_SIZE + GAP)

extern int gridMap[GRID_SIZE][GRID_SIZE];

Vector2 GridToPixel(int col, int row);
Vector2 PixelToGrid(int x, int y);

void InitGridMap();

#endif