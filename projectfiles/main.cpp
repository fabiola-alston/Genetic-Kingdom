// code for opening folder for MSYS2 MINGW64
// cd "/c/Users/Fabiola/Documents/TEC/2025/I Semestre/Algoritmos y estructuras de datos II/II Proyecto/Genetic-Kingdom/projectfiles"
#include "raylib.h"
#include "colors.h"
#include "towers.h"
#include "enemies.h"
#include <iostream>
#include <vector>
#include <algorithm>

const int GRID_SIZE = 25;
const int BUTTON_SIZE = 34;
const int GAP = 4;
const int CELL_SIZE = BUTTON_SIZE + GAP;

// for checking if tower already at a position
bool IsTowerAtPosition(const std::vector<Tower>& towers, int x, int y)
{
    for (const Tower& tower : towers)
    {
        if (tower.posX == x && tower.posY == y)
        {
            return true;
        }
    }
    return false;
}

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

    // delete later :)
    int lastPosXClicked = 0;
    int lastPosYClicked = 0;

    // player gold variable from tower's variables
    int playerGold = 30;

    InitWindow(screenWidth, screenHeight, "Genetic Kingdom");
    SetTargetFPS(60);

    // tower list
    std::vector<Tower> towers;

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

    // grid block hover image
    Image grid_button_hover = LoadImage("resources/grid_block_hover.png");
    ImageResize(&grid_button, BUTTON_SIZE, BUTTON_SIZE);
    Texture2D gridHoverTexture = LoadTextureFromImage(grid_button_hover);
    UnloadImage(grid_button_hover);

    // show "Choose Tower" menu
    bool showTowerMenu = false;

    // show "not enough gold" error
    bool showGoldWarning = false;
    float warningTimer = 0.0f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(teal1);

        Vector2 mousePos = GetMousePosition();

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
                // DrawTexture(gridTexture, x, y, WHITE);

                Rectangle gridButtonRect = {(float)x, (float)y, (float)BUTTON_SIZE, (float)BUTTON_SIZE};

                bool hovered = CheckCollisionPointRec(mousePos, gridButtonRect);

                if (hovered)
                {
                    DrawTexture(gridHoverTexture, x, y, WHITE);

                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) and showTowerMenu == false)
                    {
                        if (IsTowerAtPosition(towers, x, y) == false)
                        {
                            // updates last clicked position
                            lastPosXClicked = x;
                            lastPosYClicked = y;

                            // and opens the little menu for the type of tower yayy
                            showTowerMenu = true;

                            // ignore this, it's painful proof i actually coded this thing :') 
                            // fabi note: so it only lasts a frame, what you should do is a list of towers that need to stay drawn and have them get drawn every frame.
                    
                        }

                        else
                        {
                            // idk play a sound or something here !!
                            // (for future reference, this is where the action for "tower already placed" goes)
                        }
                    }
                }

                else 
                {
                    DrawTexture(gridTexture, x, y, WHITE);
                }
            }
        }

        for (Tower& t : towers)
        {
            t.drawImage();
            t.moveTower();
        }

        DrawText(TextFormat("Last X Pos: %d Last Y Pos: %d", lastPosXClicked, lastPosYClicked), 10, 10, 20, WHITE);
        DrawText(TextFormat("Gold: %d", playerGold), 10, 30, 20, WHITE);

        // show tower menu code
        if (showTowerMenu)
        {
            int menuWidth = 200;
            int menuHeight = 150;
            int menuX = lastPosXClicked;
            int menuY = lastPosYClicked;

            DrawRectangle(menuX, menuY, menuWidth, menuHeight, Fade(purple1, 0.95f));
            DrawRectangleLines(menuX, menuY, menuWidth, menuHeight, purple2);
            DrawText("Choose Tower", menuX + 10, menuY + 10, 20, WHITE);

            Rectangle arqueroButton = {(float)menuX + 10, (float)menuY + 40, 180, 25};
            Rectangle magoButton = {(float)menuX + 10, (float)menuY + 70, 180, 25};
            Rectangle artilleroButton = {(float)menuX + 10, (float)menuY + 100, 180, 25};

            DrawRectangleRec(arqueroButton, CheckCollisionPointRec(mousePos, arqueroButton) ? pink1 : purple2);
            DrawRectangleRec(magoButton, CheckCollisionPointRec(mousePos, magoButton) ? pink1 : purple2);
            DrawRectangleRec(artilleroButton, CheckCollisionPointRec(mousePos, artilleroButton) ? pink1 : purple2);

            DrawText("Arquero (5G)", menuX + 20, menuY + 43, 20, WHITE);
            DrawText("Mago (10G)", menuX + 20, menuY + 73, 20, WHITE);
            DrawText("Arquero (15G)", menuX + 20, menuY + 103, 20, WHITE);

            // when respective button gets clicked
             if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (CheckCollisionPointRec(mousePos, arqueroButton))
                {
                    if (playerGold >= 5)
                    {
                        Tower tower(1, lastPosXClicked, lastPosYClicked);
                        towers.emplace_back(tower);
                        tower.playerGold -= 5;
                        playerGold = tower.playerGold;
                        showTowerMenu = false;
                    }

                    else
                    {
                        showGoldWarning = true;
                        warningTimer = 0.0f;
                    }
                    
                }
                else if (CheckCollisionPointRec(mousePos, magoButton))
                {
                    if (playerGold >= 10)
                    {
                        Tower tower(2, lastPosXClicked, lastPosYClicked);
                        towers.emplace_back(tower);
                        tower.playerGold -= 10;
                        playerGold = tower.playerGold;
                        showTowerMenu = false;
                    }

                    else 
                    {
                        showGoldWarning = true;
                        warningTimer = 0.0f;
                    }
                        
                }
                else if (CheckCollisionPointRec(mousePos, artilleroButton))
                {
                    if (playerGold >= 15)
                    {
                        Tower tower(3, lastPosXClicked, lastPosYClicked);
                        towers.emplace_back(tower);
                        tower.playerGold -= 15;
                        playerGold = tower.playerGold;
                        showTowerMenu = false;
                    }

                    else
                    {
                        showGoldWarning = true;
                        warningTimer = 0.0f;
                    }
                    
                }
            }
        }

        if (showGoldWarning)
        {
            showTowerMenu = false;
            warningTimer += GetFrameTime();
            if (warningTimer > 4.0f)
            {
                showGoldWarning = false;
                warningTimer = 0.0f;
            }

            float alpha = (warningTimer <= 2.0f) ? 1.0f : 1.0f - (warningTimer - 2.0f) / 2.0f;
            
            if (alpha < 0.0f)
            {
                alpha = 0.0f;
            }

            Color warningColor = {255, 0, 0, (unsigned char)(alpha * 255)};
            DrawRectangle(screenWidth / 2 - 150, screenHeight / 2 - 20, 300, 40, Fade(BLACK, alpha));
            DrawText("Not enough gold!", screenWidth / 2 - 130, screenHeight / 2 - 10, 30, warningColor);
        }

        // NOTE FOR LEAVING OFF
        // fix gold issue (going into negatives), make a pop up message for insufficient gold ?
        // ENEMIES class, once you got that go STRAIGHT to genetic algorithm. 
        // work on tower movement last ig ? make sure they're ranges and attacks work first. 
        // work on enemy pathfinding a*. 

        EndDrawing();

    }

    UnloadTexture(bridgeTexture);
    UnloadTexture(gridTexture);
    UnloadTexture(gridHoverTexture);
    CloseWindow();

    return 0;

}
    
