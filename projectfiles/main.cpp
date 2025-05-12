// code for opening folder for MSYS2 MINGW64
// cd "/c/Users/Fabiola/Documents/TEC/2025/I Semestre/Algoritmos y estructuras de datos II/II Proyecto/Genetic-Kingdom/projectfiles"
#include "raylib.h"
#include "colors.h"
#include <iostream>

const int GRID_SIZE = 25;
const int BUTTON_SIZE = 34;
const int GAP = 4;
const int CELL_SIZE = BUTTON_SIZE + GAP;

int main() {
    // screen size
    const int screenWidth = 1920;
    const int screenHeight = 1250;

    // island dimensions
    const int islandWidth = 1000;
    const int islandHeight = 1000;

    // grid dimensions
    const int GRID_X = (screenWidth/2) - ((CELL_SIZE*GRID_SIZE)/2);
    const int GRID_Y = (screenHeight/2) - (CELL_SIZE*GRID_SIZE/2); 

    InitWindow(screenWidth, screenHeight, "Genetic Kingdom");
    SetTargetFPS(60);

    // bridge asset image
    Image bridge = LoadImage("resources/Bridge.png");
    ImageResize(&bridge, 100, 134);
    Texture2D bridgeTexture = LoadTextureFromImage(bridge);
    UnloadImage(bridge);

    // grid button asset image
    Image grid_button = LoadImage("resources/grid_block.png");
    ImageResize(&grid_button, BUTTON_SIZE, BUTTON_SIZE);
    Texture2D gridTexture = LoadTextureFromImage(grid_button);
    UnloadImage(grid_button);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(teal1);

        // main island shadow
        DrawRectangle((screenWidth/2) - ((islandWidth+60)/2), (screenHeight/2) - ((islandHeight+60)/2), islandWidth+60, islandHeight+60, teal2); // shadow 1
        DrawRectangle((screenWidth/2) - ((islandWidth+30)/2), (screenHeight/2) - ((islandHeight+30)/2), islandWidth+30, islandHeight+30, teal3); // shadow 2

        // main island rectangle
        DrawRectangle((screenWidth/2) - (islandWidth/2), (screenHeight/2) - (islandHeight/2), islandWidth, islandHeight, tan1);

        // island grass
        DrawRectangle((screenWidth/2) - ((islandWidth-30)/2), (screenHeight/2) - ((islandHeight-30)/2), islandWidth-30, islandHeight-30, green1);

        // bridges in game
        DrawTexture(bridgeTexture, (screenWidth/2) - (bridgeTexture.width)/2, 0, WHITE);
        DrawTexture(bridgeTexture, (screenWidth/2) - (bridgeTexture.width)/2, 1116, WHITE);

        // draw grid of buttons
        for (int row = 0; row < GRID_SIZE; row++)
        {
            for (int col = 0; col < GRID_SIZE; col++)
            {
                int x = GRID_X + (col * CELL_SIZE);
                int y = GRID_Y + (row * CELL_SIZE);
                DrawTexture(gridTexture, x, y, WHITE);
            }
        }

        EndDrawing();

    }

    UnloadTexture(bridgeTexture);
    CloseWindow();

    return 0;

}
    
