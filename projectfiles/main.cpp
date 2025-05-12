// code for opening folder for MSYS2 MINGW64
// cd "/c/Users/Fabiola/Documents/TEC/2025/I Semestre/Algoritmos y estructuras de datos II/II Proyecto/Genetic-Kingdom/projectfiles"

#include "raylib.h"
#include "colors.h"
#include <iostream>

int main() {
    // screen size
    const int screenWidth = 1200;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Genetic Kingdom");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(teal);
        EndDrawing();

    }

    CloseWindow();

    return 0;
}
    
