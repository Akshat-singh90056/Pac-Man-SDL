#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>

class Player
{
public:
    Player(SDL_Renderer *renderer); // Pass renderer to constructor
    ~Player();

    void render();
    void update();

private:
    SDL_Renderer *renderer; // Store the renderer
    SDL_Texture *playerTexture;
    SDL_Rect playerRect;
};

#endif // PLAYER_H
