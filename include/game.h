#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "enemy.h"
#include "map.h"
#include<vector>
#include"hitbox.h"
class Game
{
public:
    Game(int width, int height);
    ~Game();


    enum Direction
    {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    Direction currentDirection;
    
    Uint64 lastTime = 0;
    float deltaTime = 0.0f;

    bool init(const char *title);
    void handleEvents();
    void render();
    void renderPlayer();
    void movePlayer();
    void update();

    SDL_Texture *loadTexture(const char *path);

    bool running() const { return isRunning; }
    void clean();
    void renderMap();

private:
    int WINDOW_W;
    int WINDOW_H;
    bool isRunning;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    SDL_Texture *playerTex = nullptr;
    SDL_Texture *mapTex = nullptr;


    std::vector<Enemy *> arrayOfEnemy;

    Hitbox hitbox;

    SDL_FRect player;
};