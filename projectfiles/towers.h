#ifndef TOWERS_H
#define TOWERS_H

#include "raylib.h"
#include <iostream>

class Tower
{
    public: 
        int category;
        int damage;
        int velocity;
        float timeRegenPower;
        float timeRechargeAttack;
        int cost;
        int attackRange;
        int posX;
        int posY;
        Texture2D spriteTex;
        float timer = 0.0f;
        static int playerGold;

        // Constructor
        Tower(int cat, int x, int y);

        // Destructor
        //~Tower();

        // Loads the texture based on tower category
        void setAttributes();
        void drawImage();
        void moveTower();
};

#endif