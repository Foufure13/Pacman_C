#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_NAME "ProjetPacman"
#define SCREEN_WIDTH 928
#define SCREEN_HEIGHT 832

Game *game = NULL;

int SDL_main(int argc, char *argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS; 

    Uint32 frameStart;
    int frameTime;  

    game = createGame();
    init(game, WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    while (running(game))
    {
        frameStart = SDL_GetTicks();

        handleEvents(game);
        update(game);
        render(game);

        frameTime = SDL_GetTicks() - frameStart;
        
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    clean(game);
    
    return 0;
}