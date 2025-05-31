#ifndef ENEMIES_H
#define ENEMIES_H

#include "raylib.h"
#include "gridvars.h"
#include "pathfinding.h"
#include <iostream>

class Enemy
{
    public:
        int category = 0;
        int hp = 0;
        int maxHP = 0;
        int velocity = 0;
        int resFlecha = 0;
        int resMagia = 0;
        int resArt = 0;
        int goldDeath = 0;
        bool awardedGold = false;
        int posX = 0;
        int posY = 0;
        Texture2D spriteTex;
        bool onGrid = false;

        bool reachedGoal = false;

        std::vector<Node> path;
        int currentPathIndex = 0;

        Enemy(int cat);

        void drawImage(int x, int y);
        void move();
        void healthBar();
        bool isDead();

    private:
        void setAttributes();

};

#endif