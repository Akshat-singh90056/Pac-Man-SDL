#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Enemy
{
public:
    Enemy(SDL_Renderer *renderer, float x, float y);
    ~Enemy()
    {
        if (texture)
            SDL_DestroyTexture(texture);
    }

    void init(SDL_Renderer *renderer, const char *filePath, float x, float y, int SIZE, int i);
    void update(float x, float y);
    void render(SDL_Renderer *renderer);
    void clean();
    bool collision(float playerX, float playerY);
    void changePos(int x, int y);

private:
    SDL_Texture *texture = nullptr;
    SDL_FRect position;
    SDL_FRect srcRect;
};