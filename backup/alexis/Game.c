#include <stdio.h>
#include <stdlib.h>

#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"


GameObject *player;
GameObject *ennemy;
Map* map;

SDL_Renderer *renderer = NULL;

Game* createGame() {
    Game* game = (Game*)malloc(sizeof(Game));
    game->cnt = 0;
    game->isRunning = 0;
    game->window = NULL;
    return game;
}

void init(Game *game, const char* title, int xpos, int ypos, int width, int height, int fullscreen)
{
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        game->window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (!game->window) {
            printf("Failed to create window: %s\n", SDL_GetError());
            clean(game);
            exit(1);
        }

        renderer = SDL_CreateRenderer(game->window, -1, 0);
        if (!renderer) {
            printf("Failed to create renderer: %s\n", SDL_GetError());
            clean(game);
            exit(1);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        game->isRunning = 1;
    }

    player = createGameObject("images/key.png", 0, 0);
    ennemy = createGameObject("images/momo.png", 200, 200);
    map = CreateMap();

}

void handleEvents(Game *game)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT:
            game->isRunning = 0;
            break;

        default:
            break;
    }
}

void update(Game *game)
{
    // TODO: add update logic here
    //game->cnt++;

    updateGameObject(player);
    updateGameObject(ennemy);

    //printf("%d\n", game->cnt);
}

void render(Game *game)
{
    SDL_RenderClear(renderer);

    // TODO: add render logic here
    DrawMap(map);
    renderGameObject(player);
    renderGameObject(ennemy);

    SDL_RenderPresent(renderer);
}

void clean(Game *game)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
    free(game);
}

int running(Game *game)
{
    return game->isRunning;
}
