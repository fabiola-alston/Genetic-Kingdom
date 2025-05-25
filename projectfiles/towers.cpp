#include "towers.h"


Tower::Tower(int cat,int x, int y)
    :
        category(cat),
        posX(x),
        posY(y)
    {
        setAttributes();
    }

    int Tower::playerGold = 30;

    void Tower::setAttributes()
    {
        Image sprite;
    
        // arquero
        if (category == 1)
        {   
            sprite = LoadImage("resources/arquero1.png");
            ImageResize(&sprite, 30, 30);
            damage = 5;
            velocity = 0;
            timeRegenPower = 60.0f;
            timeRechargeAttack = 2.0f;
            cost = 5;
            attackRange = 5; 

        }

        // mago
        else if (category == 2)
        {
            sprite = LoadImage("resources/mago1.png");
            ImageResize(&sprite, 30, 30);
            damage = 7;
            velocity = 0;
            timeRegenPower = 80.0f;
            timeRechargeAttack = 3.0f;
            cost = 10;
            attackRange = 3; 

        }  

        // artillero
        else if (category == 3)
        {
            sprite = LoadImage("resources/artillero1.png");
            ImageResize(&sprite, 30, 30);
            damage = 10;
            velocity = 0;
            timeRegenPower = 100.0f;
            timeRechargeAttack = 5.0f;
            cost = 15;
            attackRange = 2; 

        }

        // unrecognized ?? 
        else
        {
            std::cout << "Error" << std::endl;
            return;

        }

        spriteTex = LoadTextureFromImage(sprite);
        UnloadImage(sprite);
    }

    void Tower::drawImage()
    {
        DrawTexture(spriteTex, posX, posY, WHITE);
    }

    void Tower::moveTower()
    {
        float interval = 1.0f;
        float deltaTime = GetFrameTime();
        timer += deltaTime;

        if (timer >= interval)
        {
            posX += 38 * velocity;
            timer -= interval;
        }
    }

    void Tower::upgrade()
    {
        level += 1; // obviouslyy gonna fix this later but it's 2:30 a.m. and i want to sleep
    }

