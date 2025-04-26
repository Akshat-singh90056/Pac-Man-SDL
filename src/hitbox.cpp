#include "hitbox.h"

int arr[] = {155, 572, 432};
// int arr[] = {153, 572, 432};

void Hitbox::init()
{
    rect = {0, 0, 720, 17};
    hitboxes.emplace_back(rect);
    SDL_FRect r2 = {346, 7, 31, 101};
    hitboxes.emplace_back(r2);

    for (int i = 0; i < 3; i++)
    {
        SDL_FRect r3 = {346.0f, static_cast<float>(arr[i] - 2), 32.0f, 94.0f};
        SDL_FRect r4 = {271.0f, static_cast<float>(arr[i] - 2), 180.0f, 24.0f};

        hitboxes.emplace_back(r4);
        hitboxes.emplace_back(r3);
    }

    if (hitboxes.size() == 2)
    {
        std::cout << "succesfull" << std::endl;
    }
}

void Hitbox::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 225, 225, 225, 0);
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
