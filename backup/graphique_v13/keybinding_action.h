#include <SDL2/SDL_keycode.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_test_images.h>

#include "map.h"

#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

typedef struct SuperVitesse {
float vitesseY;  // La vitesse de déplacement vertical
int directionY;  // La direction du déplacement (1 pour vers le haut, -1 pour vers le bas)
float vitesseX;
int directionX;
int point_joueur;
} Deplacement;



// Déclaration de la fonction

void appuye_touche(SDL_Event event, SDL_bool *programme, Deplacement *rect_image, SDL_Rect *srcrect,  SDL_Rect *pacman_dstrect, MAPS *map);
void collision(MAPS *map, SDL_Rect *pacman_dstrect, SDL_Rect *pacman_srcrect, Deplacement *rect_image);
void collision_point(MAPS *map, SDL_Rect *pacman_dstrect, SDL_Rect *pacman_srcrect, Deplacement *rect_image);

extern Deplacement* deplacement;


#endif // MAFONCTION_H
