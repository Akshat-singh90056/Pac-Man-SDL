#include "hitbox.h"

int arr[] = {155, 572, 432};
float boxArrayx[] = {65, 195, 425,  580};
float boxArrayy[] = {61, 154-1, 500, 638};
// int arr[] = {153, 572, 432};

void Hitbox::init()
{
    rect = {0, 0, 720, 17};
    hitboxes.emplace_back(rect);
    SDL_FRect leftWall = {0, 0, 13, 720};
    SDL_FRect topWall = {346, 7, 31, 101};
    SDL_FRect rightWall = {706, 0, 13, 720};
    SDL_FRect bottomWall = {0, 707, 720, 16};
    hitboxes.emplace_back(topWall);
    hitboxes.emplace_back(leftWall);
    hitboxes.emplace_back(rightWall);
    hitboxes.emplace_back(bottomWall);

    for (int i = 0; i < 3; i++)
    {
        SDL_FRect r2 = {346.0f, static_cast<float>(arr[i] - 2), 32.0f, 94.0f};
        SDL_FRect r1 = {271.0f, static_cast<float>(arr[i] - 2), 180.0f, 24.0f};

        hitboxes.emplace_back(r1);
        hitboxes.emplace_back(r2);
    }

    for (int i = 0; i < 4; i++)
    {
        float h = 46.0f;
        float w = 76.0f;
        for(int j = 0; j  < 4;j ++){
            int offset = 0;
            if((i == 1 && j == 1) || (i == 2 && j == 1)){
                continue;
            }
            if(j != 0){
                h = 25.0f;
            }
            if(i == 1 || i == 2){
                w = 102.0f;
            }
            else if(j == 3 && i == 3){
                // w = 0;
                offset = 53;
                w += 53;
                // SDL_Quit();
            }
            else if(j == 3 && i == 0){
                w = 127.0f;
            }
            else{
                w = 76.0f;
            }
            SDL_FRect r2 = {boxArrayx[i]- offset, boxArrayy[j], w, h};
            hitboxes.emplace_back(r2);
        }
    }

    if (hitboxes.size() == 2)
    {
        std::cout << "succesfull" << std::endl;
    }
}

void Hitbox::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 225, 0, 0, 0);
    int i = 0;
    for (auto it : hitboxes)
    {
        SDL_RenderRect(renderer, &it);
    }
}

bool Hitbox::checkForCollision(float playerX, float playerY)
{
    SDL_FRect player = {playerX, playerY, 35, 35};

    for (const auto &hitbox : hitboxes)
    {
        if ((player.x < hitbox.x + hitbox.w) &&
            (player.x + player.w > hitbox.x) &&
            (player.y < hitbox.y + hitbox.h) &&
            (player.y + player.h > hitbox.y))
        {
            return true;
        }
    }
    return false;
}