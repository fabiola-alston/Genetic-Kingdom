#ifndef ENEMIES_H
#define ENEMIES_H

#include "raylib.h"

class Enemy
{
    public:
        int category;
        int hp;
        int velocity;
        int resFlecha;
        int resMagia;
        int resArt;
        int goldDeath;
        int posX;
        int posY;
        Texture2D spriteTex;

        Enemy(int cat);

        void drawImage(int x, int y);


    private:
        void setAttributes();

};

#endif