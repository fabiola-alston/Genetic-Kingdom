// code for opening folder for MSYS2 MINGW64
// cd "/c/Users/Fabiola/Documents/TEC/2025/I Semestre/Algoritmos y estructuras de datos II/II Proyecto/Genetic-Kingdom/projectfiles"
#include "raylib.h"
#include "colors.h"
#include "towers.h"
#include "enemies.h"
#include "gridvars.h"
#include <iostream>
#include <vector>
#include <algorithm>

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
    // initialize grid array from the heather file we made :)
    InitGridMap();
    GRID_X = (screenWidth / 2) - ((CELL_SIZE * GRID_SIZE) / 2);
    GRID_Y = (screenHeight / 2) - ((CELL_SIZE * GRID_SIZE) / 2);

    // game timer
    int gameTimer = 0;
    float gameFrameTimer = 0.0f;

    // delete later :) (DONT DELETE LATER ANYMORE)
    int lastPosXClicked = 0;
    int lastPosYClicked = 0;

    // player gold variable from tower's variables
    int playerGold = 100;

    InitWindow(screenWidth, screenHeight, "Genetic Kingdom");
    SetTargetFPS(60);

    // tower list
    std::vector<Tower> towers;

    // enemy list
    std::vector<Enemy> enemies;

    // enemy wave variables !!
    int currentWave = 0;
    bool spawningWave = false;
    float waveCooldownTimer = 0.0f;
    // this is the time between the waves of enemies
    float waveDelay = 15.0f;
    int enemiesPerWave = 3;
    int enemiesSpawnedCurrWave = 0;
    // this is how often enemies spawn INSIDE of the wave
    float enemySpawnInterval = 0.5f; 
    float enemySpawnTimer = 0.0f;

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

        playerGold = Tower::playerGold;

        // main island shadow
        DrawRectangle((screenWidth/2) - ((islandWidth+60)/2), (screenHeight/2) - ((islandHeight+60)/2), islandWidth+60, islandHeight+60, teal2); // shadow 1
        DrawRectangle((screenWidth/2) - ((islandWidth+30)/2), (screenHeight/2) - ((islandHeight+30)/2), islandWidth+30, islandHeight+30, teal3); // shadow 2

        // main island rectangle
        DrawRectangle((screenWidth/2) - (islandWidth/2), (screenHeight/2) - (islandHeight/2), islandWidth, islandHeight, tan1);

        // island grass
        DrawRectangle((screenWidth/2) - ((islandWidth-30)/2), (screenHeight/2) - ((islandHeight-30)/2), islandWidth-30, islandHeight-30, green1);

        // bridges in game
        DrawTexture(bridgeTexture, (screenWidth/2) - (bridgeTexture.width)/2, 0, WHITE);
        DrawTexture(bridgeTexture, (screenWidth/2) - (bridgeTexture.width)/2, screenHeight - bridgeTexture.height, WHITE);

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

                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) and showTowerMenu == false and playerGold != 0)
                    {
                        if (IsTowerAtPosition(towers, x, y) == false)
                        {
                            // updates last clicked position
                            lastPosXClicked = x;
                            lastPosYClicked = y;

                            int col = abs((lastPosXClicked - GRID_X) / CELL_SIZE);
                            int row = abs((lastPosYClicked - GRID_Y) / CELL_SIZE);

                            if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE)
                            {
                                gridMap[row][col] = 1;
                                pathUpdate = true;
                            }

                            std::cout << "Placed tower at col=" << col << ", row=" << row << "\n";

                            // and opens the little menu for the type of tower yayy
                            showTowerMenu = true;

                            // ignore this, it's painful proof i actually coded this thing :') 
                            // fabi note: so it only lasts a frame, what you should do is a list of towers that need to stay drawn and have them get drawn every frame.
                    
                        }

                        else if (playerGold == 0 or playerGold < 5)
                        {

                            showGoldWarning = true;
                        }


                        else
                        {
                            // idk play a sound or something here !!
                            // (for future reference, this is where the action for "tower already placed" goes)
                        }
                    }
                
                    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
                    {
                        for (Tower& tower : towers)
                        {
                            Rectangle bounds = {(float)tower.posX, (float)tower.posY, (float)CELL_SIZE, (float)CELL_SIZE};
                            if (CheckCollisionPointRec(GetMousePosition(), bounds))
                            {
                                if (playerGold >= (tower.level * 10))
                                {
                                    tower.upgrade();
                                    Tower::playerGold-=(tower.level * 10);
                                }
                                else if (playerGold < (tower.level * 10))
                                {
                                    showGoldWarning = true;
                                }
                                
                            }
                        }
                    }
                }

                else 
                {
                    DrawTexture(gridTexture, x, y, WHITE);
                }

            }
        }

        // ENEMY SPAWN CODE
        if (!spawningWave)
        {
            waveCooldownTimer += GetFrameTime(); // starts counting frames until it gets to amount of time indicated

            if (waveCooldownTimer >= waveDelay)
            {
                spawningWave = true;
                waveCooldownTimer = 0.0f;
                enemiesSpawnedCurrWave = 0;
                currentWave++;
            }

        }

        if (spawningWave)
        {
            
            enemySpawnTimer += GetFrameTime(); // starts counting frames until it gets to the amount of time indicated

            if (enemySpawnTimer >= enemySpawnInterval && enemiesSpawnedCurrWave < enemiesPerWave)
            {
                int randomType = GetRandomValue(1, 4);
                Enemy enemy(randomType);

                enemy.posX = screenWidth / 2;
                enemy.posY = screenHeight - 10;

                std::cout << "X" << enemy.posX << "Y" << enemy.posY << "\n";

                enemies.push_back(enemy);

                enemiesSpawnedCurrWave++;
                enemySpawnTimer = 0.0f;
            }

            if (enemiesSpawnedCurrWave >= enemiesPerWave)
            {
                enemiesPerWave += 1;
                spawningWave = false;
            }
        }

        // draw stats on game
        DrawText(TextFormat("Wave #%d currently in process", currentWave), 10, 60, 20, DARKPURPLE);
        DrawText(TextFormat("Enemies spawned: %d", enemiesSpawnedCurrWave), 10, 80, 20, DARKPURPLE);
        DrawText(TextFormat("Time: %d", gameTimer), 10, 100, 20, DARKPURPLE);
        DrawText(TextFormat("Enemies slain: %d", Enemy::deadEnemiesTotal), 10, 120, 20, DARKPURPLE);
        DrawText(TextFormat("Enemies that won: %d", Enemy::victories), 10, 140, 20, DARKPURPLE);


        // draw each created enemy
        for (Enemy& e : enemies)
        {
            if (!e.isDead())
            {
                e.move();
                e.drawImage(e.posX, e.posY);
                e.healthBar();
            }

            if (e.isDead() and !e.awardedGold)
            {
                Tower::playerGold += e.goldDeath;
                Enemy::deadEnemiesTotal += 1;
                score += e.category * 5;
                e.awardedGold = true;
            }

            if (!e.isDead() and e.reachedGoal)
            {
                score -= e.category * 10;
                Enemy::victories +=1 ;
                e.reachedGoal = false;

                e.hp = 0;
            }
        }

        // similarly, draws each created tower
        for (Tower& t : towers)
        {
            t.drawImage();
            t.drawRange();
            t.attack(enemies);
        }

        DrawText(TextFormat("Last X Pos: %d Last Y Pos: %d", lastPosXClicked, lastPosYClicked), 10, 10, 20, WHITE);
        DrawText(TextFormat("Gold: %d", playerGold), 10, 30, 20, WHITE);
        DrawText(TextFormat("SCORE: %d", score), 1550, 10, 40, WHITE);

        // GAME INSTRUCTIONS
        DrawText("Place towers anywhere on the \n grid (prices in menu). \n Right click for upgrades. \n Tower Upgrades: \n Level 1 - 10G \n Level 2 - 20G \n Level 3 - 30G", 10, 600, 20, WHITE);

        // show tower menu code
        if (showTowerMenu)
        {
            int menuWidth = 160;
            int menuHeight = 130;
            int menuX = lastPosXClicked;
            int menuY = lastPosYClicked;

            DrawRectangle(menuX, menuY, menuWidth, menuHeight, Fade(purple1, 0.95f));
            DrawRectangleLines(menuX, menuY, menuWidth, menuHeight, purple2);
            DrawText("Choose Tower", menuX + 10, menuY + 10, 18, WHITE);

            Rectangle arqueroButton = {(float)menuX + 10, (float)menuY + 40, 140, 20};
            Rectangle magoButton = {(float)menuX + 10, (float)menuY + 70, 140, 20};
            Rectangle artilleroButton = {(float)menuX + 10, (float)menuY + 100, 140, 20};

            DrawRectangleRec(arqueroButton, CheckCollisionPointRec(mousePos, arqueroButton) ? pink1 : purple2);
            DrawRectangleRec(magoButton, CheckCollisionPointRec(mousePos, magoButton) ? pink1 : purple2);
            DrawRectangleRec(artilleroButton, CheckCollisionPointRec(mousePos, artilleroButton) ? pink1 : purple2);

            DrawText("Arquero (5G)", menuX + 20, menuY + 43, 18, WHITE);
            DrawText("Mago (10G)", menuX + 20, menuY + 73, 18, WHITE);
            DrawText("Arquero (15G)", menuX + 20, menuY + 103, 18, WHITE);

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

        gameFrameTimer += GetFrameTime();
        if (gameFrameTimer >= 1.0f)
        {
            gameTimer++;
            gameFrameTimer = 0.0f;
        }

        pathUpdate = false;

        EndDrawing();

    }

    UnloadTexture(bridgeTexture);
    UnloadTexture(gridTexture);
    UnloadTexture(gridHoverTexture);
    CloseWindow();

    return 0;

}
    
