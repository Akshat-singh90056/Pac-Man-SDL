#ifndef PLAYER_H
#define PLAYER_H


class Player {
    public:
        Player();
        ~Player();

        void render();
        void update();

    private:

    SDL_GetWindowSurface(window);

    SDL_Texture * playerTexture;
    SDL_Rect playerRect;

};


#endif