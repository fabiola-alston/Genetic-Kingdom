#ifndef GRIDVARS_H
#define GRIDVARS_H

#include "raylib.h"

#define GRID_SIZE 20
#define BUTTON_SIZE 30
#define GAP 3
#define CELL_SIZE (BUTTON_SIZE + GAP)

// screen size
#define screenWidth 1800
#define screenHeight 900

// island size
#define islandWidth 700
#define islandHeight 700

// // grid positions
// #define GRID_X (screenWidth/2) - ((CELL_SIZE*GRID_SIZE)/2) // = 570
// #define GRID_Y (screenHeight/2) - ((CELL_SIZE*GRID_SIZE)/2) // = 120

extern int GRID_X;
extern int GRID_Y;

extern int score;


extern int gridMap[GRID_SIZE][GRID_SIZE];
extern bool pathUpdate;

Vector2 GridToPixel(int col, int row);
Vector2 PixelToGrid(int x, int y);

void InitGridMap();

#endif