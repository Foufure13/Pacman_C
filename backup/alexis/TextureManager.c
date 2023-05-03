#include "TextureManager.h"
#include "Map.h"

SDL_Texture *LoadTexture(const char* texture)
{
    SDL_Surface *tempSurface = IMG_Load(texture);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
}

void DrawTexture(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(renderer, tex, &src, &dest);
}