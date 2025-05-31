#include "enemies.h"


Enemy::Enemy(int cat)
:
    category(cat)

    {
        setAttributes();
    }

    void Enemy::setAttributes()
    {
        Image sprite;

        // ogro
        if(category == 1)
        {
            sprite = LoadImage("resources/ogro1.png");
            ImageResize(&sprite, 30, 30);
            hp = 25;
            maxHP = 25;
            velocity = 2;
            resFlecha = 1;
            resMagia =  0;
            resArt = 0;
            goldDeath = 2; 
        }


        // elfo oscuro
        else if (category == 2)
        {
            sprite = LoadImage("resources/elfooscuro1.png");
            ImageResize(&sprite, 30, 30);
            hp = 30;
            maxHP = 30;
            velocity = 4;
            resFlecha = 0;
            resMagia = 1;
            resArt = 0;
            goldDeath = 5; 
        }


        // harpia
        else if (category == 3)
        {
            sprite = LoadImage("resources/harpia1.png");
            ImageResize(&sprite, 30, 30);
            hp = 30;
            maxHP = 30;
            velocity = 3;
            resFlecha = 1;
            resMagia = 1;
            resArt = 2; 
            goldDeath = 5;
        }


        // mercenario
        else if (category == 4)
        {
            sprite = LoadImage("resources/mercenario1.png");
            ImageResize(&sprite, 30, 30);
            hp = 40;
            maxHP = 40;
            velocity = 2;
            resFlecha = 0;
            resMagia = 1;
            resArt = 0;
            goldDeath = 10;
        }

        else
        {
            return;
        }

        spriteTex = LoadTextureFromImage(sprite);
        UnloadImage(sprite);
    }

    void Enemy::drawImage(int x, int y)
    {
        if (spriteTex.id > 0)
        {
            DrawTexture(spriteTex, x, y, WHITE);
        }
    }

    void Enemy::move()
    {
        if (!onGrid)
        {
            float pixelsPerSecond = velocity * static_cast<float>(CELL_SIZE); // translating velocity (blocks (CELL_SIZE) per second (velocity)) to pixels
            float deltaY = pixelsPerSecond * GetFrameTime(); // making it souper smooooth \(0 O 0)/

            posY -= deltaY;

            int gridTop = 747; // 747 because the island sprite starts at 800, 800 - 33 which is the cell block size (+ a lil space for graphics)

            // if the enemy reaches the area where the grid starts
            if (posY <= gridTop)
            {
                onGrid = true;
                DrawText("Enemy on grid", 10, 400, 20, RED);

                // turn pixel position to grid
                int startX = abs((posX - GRID_X) / CELL_SIZE);
                int startY = abs(((posY + 1) - GRID_Y) / CELL_SIZE);

                int goalX = GRID_SIZE / 2;
                int goalY = 0;

                path = AStarSearch(startX, startY, goalX, goalY);

                currentPathIndex = 0;
            }
        }

        // once the enemy reaches the grid area
        else
        {
            if (pathUpdate)
            {
                int startX = abs((posX - GRID_X) / CELL_SIZE);
                int startY = abs((posY - GRID_Y) / CELL_SIZE);

                int goalX = GRID_SIZE / 2;
                int goalY = 0;

                path = AStarSearch(startX, startY, goalX, goalY);
                currentPathIndex = 0;
                std::cout << "Enemy recalculated path due to new tower!\n";
            }

            if (!path.empty() && currentPathIndex < static_cast<int>(path.size()))
            {
                Node nextTile = path[currentPathIndex];

                Vector2 targetPos = GridToPixel(nextTile.x, nextTile.y);

                float pixelsPerSecond = velocity * CELL_SIZE;
                float step = pixelsPerSecond * GetFrameTime();

                Vector2 dir = 
                {
                    targetPos.x - posX,
                    targetPos.y - posY
                };

                float distance = sqrt(dir.x * dir.x + dir.y * dir.y);

                if (distance < step)
                {
                    posX = targetPos.x;
                    posY = targetPos.y;
                    currentPathIndex++;
                }

                else
                {
                    posX += (dir.x / distance) * step;
                    posY += (dir.y / distance) * step;
                }

            }
        }
    }

    void Enemy::healthBar()
    {
        float healthRatio = (float)(hp) / (float)(maxHP);
        int barWidth = CELL_SIZE;
        int barHeight = 5;
        int barX = posX;
        int barY = posY - 10;

        DrawRectangle(barX, barY, barWidth * healthRatio, barHeight, GREEN);

        DrawRectangle(barX + barWidth * healthRatio, barY, barWidth * (1 - healthRatio), barHeight, RED);
    }

    bool Enemy::isDead()
    {
        if (hp <= 0)
        {
            velocity = 0;
            return true;
        }
        else
        {
            return false;
        }
    }