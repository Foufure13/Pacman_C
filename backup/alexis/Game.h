#ifndef Game_h
#define Game_h

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

typedef struct Game {
    int cnt;
    int isRunning;
    SDL_Window *window;
} Game;

Game* createGame();

void init(Game *game, const char* title, int xpos, int ypos, int width, int height, int fullscreen); 
void handleEvents(Game *game); 
void update(Game *game);
void render(Game *game);
void clean(Game *game);

int running(Game *game);

extern SDL_Renderer *renderer;

#endif
