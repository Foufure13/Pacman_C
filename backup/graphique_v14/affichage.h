#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>   
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_test_images.h>

#include <ncurses.h>
#include "keybinding_action.h"

#ifndef AFFICHAGE_H
#define AFFICHAGE_H


void Affichage_score(MAPS *maps, SDL_Renderer *rendu, Deplacement pacman);
void Affichage_vie (MAPS *maps, SDL_Renderer *rendu, Deplacement pacman);
void Affichage_pacman (MAPS *maps, SDL_Renderer *rendu, Deplacement pacman, SDL_Rect *pacman_srcrect, SDL_Rect *pacman_dstrect);
void Affichage_fantom (MAPS *maps, SDL_Renderer *rendu, SDL_Rect *fantom_srcrect, SDL_Rect *fantom_dstrect);


#endif // AFFICHAGE_H