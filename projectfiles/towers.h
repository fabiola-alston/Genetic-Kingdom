#ifndef TOWERS_H
#define TOWERS_H

#include "raylib.h"
#include <iostream>
#include "gridvars.h"
#include <vector>
#include "enemies.h"

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
        void drawRange();
        void attack(std::vector<Enemy>& enemies);

    private: 
        void setAttributes();

        // notas: agregar int level = 0; y fn de upgrade !!
};

#endif