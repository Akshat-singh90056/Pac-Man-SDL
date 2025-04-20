#include "enemy.h"
#include <iostream>

#include<cmath>
float ENEMY_SPEED  = 5;

Enemy::Enemy(SDL_Renderer* renderer, float x, float y){}

void Enemy::init(SDL_Renderer *renderer, const char *filePath, float x, float y, int SIZE, int i)
{   
    SDL_Surface * surface = IMG_Load("assets/images/png/pacmanIMG.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    // texture = IMG_LoadTexture(renderer, filePath);
    if (!texture)
    {
        SDL_Log("Failed to load enemy texture: %s", SDL_GetError());
        return;
    }

    if(i == 3){
        i = 1;
    }
    if(i == 2){
        i = 0;
    }

    srcRect.x = i * 160;      // starting x in the sprite sheet
    srcRect.y = 0;      // starting y
    srcRect.w = 160;     // width of 1 sprite (adjust based on your image)
    srcRect.h = 140;     // height of 1 sprite

    // Position where enemy will be drawn
    position.x = x;
    position.y = y;
    position.w = SIZE;
    position.h = SIZE;
}

void Enemy::render(SDL_Renderer *renderer)
{   
    SDL_RenderTexture(renderer, texture, &srcRect, &position);
}

void Enemy::clean()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Enemy::update(float playerX, float playerY){
    float angle = atan2((playerX - position.x) ,(playerY - position.y));
    angle = -angle;
    angle = angle + 90;
    position.x += ENEMY_SPEED * cos(angle);
    position.y += ENEMY_SPEED * sin(angle);

}

bool Enemy::collision(float playerX, float playerY){
    return (playerX < position.x + 32 &&
        playerX + 32 > position.x &&
        playerY < position.y + 32 &&
        playerY + 32 > position.y);
}

void Enemy::changePos(int x, int y){
    position.x = x;
    position.y = y;
}