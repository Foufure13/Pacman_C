#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>   
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_test_images.h>
#include <ncurses.h>

#ifndef MAPS_H
#define MAPS_H


typedef struct MapPacman {
  char **tableau;
  int x, y;
  int pacman[2];
  int *pacman_x, *pacman_y;
  int **seedmap;
} MAPS;


// void map_controller(MAPS maps, SDL_Window *fenetre, SDL_Renderer *rendu);
void ajout_mur_map(MAPS *maps, SDL_Window *fenetre, SDL_Renderer *rendu);
void structur_map(MAPS *maps, SDL_Window *fenetre, SDL_Renderer *rendu);


void allocation_memoire_tableau(MAPS *map);
void allocation_memoire_tableau_int(int **Tableau,int hauteur,int largeur);
void seedmap(MAPS *maps);

void nettoyage_memoire_tableau_int(int **Tableau,int hauteur);
void nettoyage_tableau(MAPS *map);


void nettoyage_seedmap(MAPS *tableau);
void afficher_map_debug(MAPS maps);

extern MAPS* map;

#endif // MAPS_H