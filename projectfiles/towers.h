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
        int level;
 
        Tower(int cat, int x, int y);

        void drawImage();
        void moveTower();
        void upgrade();

    private: 
        void setAttributes();

        // notas: agregar int level = 0; y fn de upgrade !!
};

#endif