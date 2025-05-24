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
            ImageResize(&sprite, 34, 34);
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
            ImageResize(&sprite, 34, 34);
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
            ImageResize(&sprite, 34, 34);
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
            ImageResize(&sprite, 34, 34);
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
            float pixelsPerSecond = velocity * 38.0f; // translating velocity (blocks per second) to pixels
            float deltaY = pixelsPerSecond * GetFrameTime(); // making it souper smooooth \(0 O 0)/

            posY -= deltaY;

            int gridTop = (1250 / 2) - (1000 / 2);

            if (posY <= gridTop)
            {
                onGrid = true; 
                posY = ((posY - gridTop) / 38) * 38 + gridTop;

                // to - do later : A* path and following it
            }
        }
        else
        {
            // to - do : pathfinding movement along grid
        }
    }

