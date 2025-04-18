#pragma once

#include <SDL3/SDL.h>

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
    void collision();
    void movePlayer();
    void update();

    SDL_Texture *playerTexture();
    SDL_FRect playerRect();

    bool running() const { return isRunning; }
    void clean();

private:
    void renderMap();

    int WINDOW_W;
    int WINDOW_H;
    bool isRunning;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    SDL_FRect player;
};
