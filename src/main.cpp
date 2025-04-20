#include "game.h"

Game game(980, 632);

int main(int argc, char *argv[])
{
    if (!game.init("Pacman Map"))
    {
        return -1;
    }

    while (game.running())
    {
        game.handleEvents();
        game.update();
        game.render();

        SDL_Delay(16); 
    }

    game.clean();

    return 0;
}