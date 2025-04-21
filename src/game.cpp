#include "game.h"
#include <iostream>
#include<time.h>

#define TILE_SIZE 35
#define PLAYER_SPEED 5.0
int randH, randW;
int ROATATION_ANGLE = 0;

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
    srand(time(NULL));

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

    playerTex = IMG_LoadTexture(renderer, "assets/images/png/pacman.png");

    if (!playerTex)
    {
        SDL_Log("Failed to load player texture: %s", SDL_GetError());
        return false;
    }

    SDL_Texture *enemyTexture = IMG_LoadTexture(renderer, "assets/images/png/pacmanIMG.png");
    if (!enemyTexture)
    {
        SDL_Log("Failed to load sprite sheet: %s", SDL_GetError());
    }

    for(int i = 0; i < 4; i++){


        randH = rand() % 632 + 32;
        randW = rand() % 980 +32;
        if(randH > 632 - TILE_SIZE - TILE_SIZE){
            randH = 632 - 64;
        }
        if(randW > 980 - TILE_SIZE - TILE_SIZE){
            randW = 980 - 2 * TILE_SIZE;
        }

        Enemy * enemy = new Enemy(renderer, TILE_SIZE * i, TILE_SIZE * i * 2);
        arrayOfEnemy.push_back(enemy);
        arrayOfEnemy.back()->init(renderer, "assets/images/png/pacmanIMG.png", randW, randH, TILE_SIZE, i);
    }

    mapTex = loadTexture("map.png");
    if(!mapTex){
        std::cout<<"Cannot laod map"<<std::endl;
        return false;
    }

    hitbox.init();
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
        else if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
            float mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            std::cout<<mouseX <<"--->"<<mouseY<<std::endl;
        }
    }
}

void Game::movePlayer()
{

    float distance = PLAYER_SPEED * deltaTime;

    switch (currentDirection)
    {
    case UP:
        player.y -= PLAYER_SPEED;
        ROATATION_ANGLE = -90;
        break;
    case DOWN:
        player.y += PLAYER_SPEED;
        ROATATION_ANGLE = 90;
        break;
    case LEFT:
        player.x -= PLAYER_SPEED;
        ROATATION_ANGLE = 180;
        break;
    case RIGHT:
        player.x += PLAYER_SPEED;
        ROATATION_ANGLE = 0;
        break;
    default:
        break;
    }
}

void Game::update()
{


    for(auto it: arrayOfEnemy){
        // it->update(player.x, player.y);
        if(it->collision(player.x, player.y)){
            std::cout<<"COLLIDER"<<std::endl;

            randH = rand() % (632 - 2 * TILE_SIZE) + TILE_SIZE;
            randW = rand() % (980 - 2 * TILE_SIZE) + TILE_SIZE;
            it->changePos(randH, randW);
        }        
    }

    Uint64 currentTime = SDL_GetPerformanceCounter();
    deltaTime = (float)(currentTime - lastTime) / SDL_GetPerformanceFrequency();
    lastTime = currentTime;

    movePlayer();

    if(hitbox.checkForCollision(player.x, player.y)){
        std::cout<<"COLLIDED"<<std::endl;
        int offset = 0;
        if(currentDirection == UP){
            currentDirection = NONE;
            player.y += 5;
            return;
        }
        else if(currentDirection == LEFT){
            currentDirection = NONE;
            player.x += 5;
            return;
        }
        else if(currentDirection == RIGHT){
            currentDirection = NONE;
            player.x -= 5;
            return;
        }
        else if(currentDirection == DOWN){
            currentDirection = NONE;
            player.y -= 5;
            return;
        }
    }
}

void Game::render()
{   


    // Set background color (dark gray to make walls/tiles stand out)
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    renderMap();
    hitbox.render(renderer);
    for(int i= 0; i < 4; i++){
        arrayOfEnemy[i]->render(renderer);
    }

    renderPlayer();

    SDL_RenderPresent(renderer);
}

void Game::renderPlayer()
{
    SDL_FlipMode PARA = SDL_FLIP_NONE;
    SDL_SetRenderDrawColor(renderer, 255, 225, 225, 255);
    if(ROATATION_ANGLE == 180){
        PARA = SDL_FLIP_VERTICAL;
    }
    SDL_RenderTextureRotated(renderer, playerTex, nullptr, &player, ROATATION_ANGLE, NULL, PARA);
    // SDL_RenderTexture(renderer, playerTex, nullptr, &player);
}


void Game::clean()
{

    if (playerTex)
    {
        SDL_DestroyTexture(playerTex);
        playerTex = nullptr;
    }

    for(auto it: arrayOfEnemy){
        delete it;
        it = nullptr;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Texture * Game::loadTexture(const char *path){
    SDL_Surface * surface = IMG_Load(path);
    SDL_Texture * tex = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_DestroySurface(surface);

    return tex;
}

void Game::renderMap(){

    SDL_SetTextureScaleMode(mapTex, SDL_SCALEMODE_NEAREST);
    // "0" = nearest pixel sampling


    SDL_FRect src = {0, 7, 224, 256};
    SDL_FRect dest = {0,0,720,720};

    SDL_RenderTexture(renderer, mapTex, &src, &dest);

}