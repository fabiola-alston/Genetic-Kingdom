#include "towers.h"


Tower::Tower(int cat,int x, int y)
    :
        category(cat),
        posX(x),
        posY(y)
    {
        setAttributes();
    }

    int Tower::playerGold = 100;

    void Tower::setAttributes()
    {
        level = 0;
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
        DrawText(TextFormat("Lvl. %d", level), posX + 5, posY - 10, 14, BLACK);
    }

    void Tower::drawRange()
    {
        int centerX = posX + CELL_SIZE/2;
        int centerY = posY + CELL_SIZE/2;

        DrawCircle(centerX, centerY, attackRange * (CELL_SIZE / 2), Fade(RED, 0.2f));
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

    void Tower::attack(std::vector<Enemy>& enemies)
    {
        float deltaTime = GetFrameTime();
        timer += deltaTime;

        if (timer >= timeRechargeAttack)
        {
            int centerX = posX + CELL_SIZE / 2;
            int centerY = posY + CELL_SIZE / 2;

            for (Enemy& enemy : enemies)
            {
                if (!enemy.isDead()) 
                {
                    int enemyCenterX = enemy.posX + CELL_SIZE / 2;
                    int enemyCenterY = enemy.posY + CELL_SIZE / 2;

                    float dx = enemyCenterX - centerX;
                    float dy = enemyCenterY - centerY;
                    float distance = sqrt(dx * dx + dy * dy);

                    if (distance <= attackRange * CELL_SIZE)
                    {
                        enemy.hp -= damage;

                        timer = 0.0f;
                        break;
                    }
                }

            }
        }
    }

    void Tower::upgrade()
    {
        if (level < 3)  // limit to level 3
        {
            level++;
            damage += 2;
            attackRange += 1;
            timeRechargeAttack *= 0.8f;  // 20% faster
        }
    }

