// code for opening folder for MSYS2 MINGW64
// cd "/c/Users/Fabiola/Documents/TEC/2025/I Semestre/Algoritmos y estructuras de datos II/II Proyecto/Genetic-Kingdom/projectfiles"

#include "raylib.h"
#include <iostream>


int main() {
    int screenWidth = 1000;
    int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Genetic Kingdom");
    SetTargetFPS(60); 

    int circlePosX = GetRandomValue(0, screenWidth);
    int circlePosY = GetRandomValue(0, screenHeight);
    int circleRadius = GetRandomValue(10, 50);

    Color blueTrue = {0, 0, 255, 255};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircle(circlePosX, circlePosY, circleRadius, PINK);

        std::string posMessage = "x pos: " + std::to_string(circlePosX) + ", y pos: " + std::to_string(circlePosY) + ", radius: " + std::to_string(circleRadius);
        DrawText(posMessage.c_str(), 10, 10, 20, blueTrue);

        if (IsKeyDown(KEY_LEFT))
        {
            circlePosX -= 10;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            circlePosX += 10;
        }
        if (IsKeyDown(KEY_UP))
        {
            circlePosY -= 10;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            circlePosY += 10;
        }

        EndDrawing();

    }

}
    
