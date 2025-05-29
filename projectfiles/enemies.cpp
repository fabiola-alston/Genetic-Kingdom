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
            velocity = 1;
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
            velocity = 3;
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
            velocity = 2;
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

            int gridTop = 767; // 767 because the island sprite starts at 800, 800 - 33 which is the cell block size

            // if the enemy hasn't reached the area where the grid starts
            if (posY <= gridTop)
            {
                onGrid = true;

                DrawText("Enemy on grid", 10, 400, 20, RED); 

                // snap to grid
                posY = ((posY - gridTop) / CELL_SIZE) * CELL_SIZE + gridTop;
            }
        }

        // once the enemy reaches the grid area
        else
        {

        }
    }

