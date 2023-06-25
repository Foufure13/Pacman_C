#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>   
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_test_images.h>


#include "keybinding_action.h"

#ifndef AFFICHAGE_H
#define AFFICHAGE_H


void Affichage_score(MAPS *maps, SDL_Renderer *rendu, Deplacement pacman);
void Affichage_vie (MAPS *maps, SDL_Renderer *rendu, Deplacement pacman);
void Affichage_pacman ( SDL_Renderer *rendu, Deplacement pacman, SDL_Rect *pacman_srcrect, SDL_Rect *pacman_dstrect);
void Affichage_fantom (MAPS *maps, SDL_Renderer *rendu,  Ghost *fantomRed, SDL_Rect pacman_dstrect);
void Affichage_niveau (MAPS *maps, SDL_Renderer *rendu, int niveau);
void game_over_pacman (MAPS *maps, SDL_Renderer *rendu, int niveau);

void reset_game (MAPS *maps,SDL_Rect *pacman_dstrect, Ghost *fantomRed, Ghost *fantomPink, Ghost *fantomBlue, Ghost *fantomOrange, Deplacement *pacman,  int *game_start);
void hit_reset_game (MAPS *maps,SDL_Rect *pacman_dstrect,int *game_start, Ghost *fantomRed, Ghost *fantomPink, Ghost *fantomBlue, Ghost *fantomOrange, Ghost *fantomRedSpe, Ghost *fantomPinkSpe, Ghost *fantomBlueSpe, Ghost *fantomOrangeSpe);


#endif // AFFICHAGE_H