#include "GameObject.h"
#include "TextureManager.h"

struct GameObject {
    int xpos;
    int ypos;
    SDL_Texture* objTexture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
};

GameObject* createGameObject(const char* texturesheet, int x, int y) {
    GameObject* gameObject = malloc(sizeof(GameObject));
    if (gameObject == NULL) {
        return NULL;
    }

    gameObject->objTexture = LoadTexture(texturesheet);

    gameObject->xpos = x;
    gameObject->ypos = y;

    gameObject->srcRect.h = 32;
    gameObject->srcRect.w = 32;
    gameObject->srcRect.x = 0;
    gameObject->srcRect.y = 0;

    gameObject->destRect.x = gameObject->xpos;
    gameObject->destRect.y = gameObject->ypos;
    gameObject->destRect.w = gameObject->srcRect.w * 2;
    gameObject->destRect.h = gameObject->srcRect.h * 2;

    return gameObject;
}

void destroyGameObject(GameObject* gameObject) {
    SDL_DestroyTexture(gameObject->objTexture);
    free(gameObject);
}

void updateGameObject(GameObject* gameObject) {
    gameObject->xpos++;
    gameObject->ypos++;

    gameObject->destRect.x = gameObject->xpos;
    gameObject->destRect.y = gameObject->ypos;
}

void renderGameObject(GameObject* gameObject) {
    SDL_RenderCopy(renderer, gameObject->objTexture, &gameObject->srcRect, &gameObject->destRect);
}
