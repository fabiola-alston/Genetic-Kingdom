#ifndef ENEMIES_H
#define ENEMIES_H

#include "raylib.h"

class Enemy
{
    public:
        int category = 0;
        int hp = 0;
        int velocity = 0;
        int resFlecha = 0;
        int resMagia = 0;
        int resArt = 0;
        int goldDeath = 0;
        int posX = 0;
        int posY = 0;
        Texture2D spriteTex;
        bool onGrid = false;

        float pixelsPerSecond = velocity * 38.0f; // translating velocity (blocks per second) to pixels
        float deltaY = pixelsPerSecond * GetFrameTime(); // making it souper smooooth \(0 O 0)/

        Enemy(int cat);

        void drawImage(int x, int y);
        void move();

    private:
        void setAttributes();

};

#endif