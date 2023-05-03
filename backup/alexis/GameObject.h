#ifndef GameObject_h
#define GameObject_h

#include <SDL2/SDL.h>

typedef struct GameObject GameObject;

GameObject* createGameObject(const char* texturesheet, int x, int y);
void destroyGameObject(GameObject* gameObject);
void updateGameObject(GameObject* gameObject);
void renderGameObject(GameObject* gameObject);

#endif  