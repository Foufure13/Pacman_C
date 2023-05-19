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

typedef struct Pacman_attribue {
float vitesseY;  // La vitesse de déplacement vertical
int directionY;  // La direction du déplacement (1 pour vers le haut, -1 pour vers le bas)
float vitesseX;
int directionX;
int point_joueur;
int vie, invincible;
} Deplacement;


typedef struct fantom_attribue {
SDL_Rect fantom_srcrect ,fantom_dstrect ;
float vitesseY, vitesseX;  
int directionY, directionX;  
int vision_H, vision_D, vision_B, vision_G;
int Gtype, actif;
} Ghost;


// Déclaration de la fonction

void appuye_touche(SDL_Event event,int *niveau, SDL_bool *programme, Deplacement *rect_image, SDL_Rect *pacman_srcrect,SDL_Rect *pacman_dstrect, MAPS *map, Ghost *fantomRed, Ghost *fantomPink, Ghost*fantomBlue, Ghost *fantomOrange,int *game_start);
void collision(MAPS *map, SDL_Rect *pacman_dstrect,  Deplacement *rect_image);
void collision_point(MAPS *map, SDL_Rect *pacman_dstrect,Deplacement *rect_image);
int collision_fantom_pacman(MAPS *map, SDL_Rect *pacman_dstrect, Deplacement *pacman, Ghost fantomRed, Ghost fantomPink, Ghost fantomBlue, Ghost fantomOrange);

void fantom_deplacement(MAPS *map,  Ghost *fantomRed, SDL_Rect pacman_dstrect);

extern Ghost* ghost;
extern Deplacement* deplacement;


#endif // MAFONCTION_H
