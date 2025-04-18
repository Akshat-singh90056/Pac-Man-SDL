#include "game.h"
#include "map.h"
#include <iostream>

#define TILE_SIZE 35
#define PLAYER_SPEED 5.0

int tile;

Game::Game(int width, int height)
    : WINDOW_W(width), WINDOW_H(height), isRunning(false), currentDirection(NONE) {}

Game::~Game()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::init(const char *title)
{
    if (SDL_Init(SDL_INIT_VIDEO) == 0)
    {
        SDL_Log("SDL Init failed: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(title, WINDOW_W, WINDOW_H, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        return false;
    }

    player = {(float)(WINDOW_W - TILE_SIZE) / 2, (float)(WINDOW_H - TILE_SIZE) / 2, TILE_SIZE, TILE_SIZE};

    isRunning = true;
    return true;
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            isRunning = false;
        }
        else if (event.type == SDL_EVENT_KEY_DOWN)
        {
            switch (event.key.key)
            {
            case SDLK_W:
                currentDirection = UP;
                break;
            case SDLK_S:
                currentDirection = DOWN;
                break;
            case SDLK_A:
                currentDirection = LEFT;
                break;
            case SDLK_D:
                currentDirection = RIGHT;
                break;
            }
        }
    }
}

void Game::movePlayer()
{

    float distance = PLAYER_SPEED * deltaTime ;

    switch (currentDirection)
    {
    case UP:
        player.y -= PLAYER_SPEED;
        break;
    case DOWN:
        player.y += PLAYER_SPEED;
        break;
    case LEFT:
        player.x -= PLAYER_SPEED;
        break;
    case RIGHT:
        player.x += PLAYER_SPEED;
        break;
    default:
        break;
    }
}

void Game::update()
{

    Uint64 currentTime = SDL_GetPerformanceCounter();
    deltaTime = (float)(currentTime - lastTime) / SDL_GetPerformanceFrequency();
    lastTime = currentTime;

    movePlayer();
    collision();
    
}

void Game::renderPlayer()
{
    SDL_SetRenderDrawColor(renderer, 255, 225, 225, 255);
    SDL_RenderFillRect(renderer, &player);
}

void Game::render()
{
    // Set background color (dark gray to make walls/tiles stand out)
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    renderMap();
    renderPlayer();

    SDL_RenderPresent(renderer);
}

void Game::renderMap()
{

    for (int row = 0; row < 31; ++row)
    {
        for (int col = 0; col < 28; ++col)
        {
            tile = pacmanMap[row][col];

            SDL_FRect rect;
            rect.x = col * TILE_SIZE;
            rect.y = row * TILE_SIZE;
            rect.w = TILE_SIZE;
            rect.h = TILE_SIZE;

            // Choose color based on tile type
            switch (tile)
            {
            case 0:
                SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
                break; // path
            case 1:
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

                break; // wall
            default:
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                break;
            }

            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void Game::collision()
{

    int tileX = (int)(player.x / TILE_SIZE);
    int tileY = (int)(player.y / TILE_SIZE);
    std::cout << tileX << " " << tileY << std::endl;

    if (player.x < 0 + TILE_SIZE)
    {
        player.x = TILE_SIZE + 2;
        currentDirection = NONE;
    }
    else if (player.x > WINDOW_W - TILE_SIZE)
    {
        player.x = (WINDOW_W - 2*TILE_SIZE) - 2;
        currentDirection = NONE;
    }
    else if (player.y < 0 + TILE_SIZE)
    {
        player.y = TILE_SIZE + 2;
        currentDirection = NONE;
    }
    else if (player.y > WINDOW_H - 2 * TILE_SIZE)
    {
        player.y = WINDOW_H - 2*TILE_SIZE - 2;
        currentDirection = NONE;
    }
}

SDL_Texture *Game::playerTexture()
{

    SDL_Surface *playerSurface = SDL_LoadBMP("assets/images/png/pacman.png");
    SDL_Texture *playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
    SDL_DestroySurface(playerSurface);
    return playerTexture;
}

void Game::clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}