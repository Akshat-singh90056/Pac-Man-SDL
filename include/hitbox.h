#ifndef HITBOX_H
#define HITBOX_H

#include<SDL3/SDL.h>
#include<iostream>
#include<vector>
#include<utility>


class Hitbox{

    public:
        void init();
        void render(SDL_Renderer * renderer);
        void update();
        bool checkForCollision(float playerX, float playerY);
        // bool checkForCollisionAll(float playerX, float playerY, SDL_FRect )
        std::vector<SDL_FRect> hitboxes;
    private:

        SDL_FRect rect;

};

#endif