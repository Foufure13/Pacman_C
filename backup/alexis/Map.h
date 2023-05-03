#ifndef Map_h
#define Map_h

#include "Game.h"

typedef struct Map{
    SDL_Rect src, dest;
    SDL_Texture *wall;
    SDL_Texture *cornerwall;

    int map[26][29];
}Map;

Map* CreateMap();
void LoadMap(Map *map, int arr[26][29]);
void DrawMap(Map *map);

#endif