#pragma once

#include<SDL3/SDL.h>

class Hitbox{

    
    public:

    Hitbox();
    ~Hitbox();

    void init();
    void render();
    void update();
    void forCollision();

    private:

    SDL_Rect hitbox;
};
