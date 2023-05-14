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


//création de la map
void ajout_mur_map(MAPS *maps, SDL_Renderer *rendu);
void ajout_structur_map(MAPS *maps, SDL_Renderer *rendu);
void ajout_point_map(MAPS *maps, SDL_Renderer *rendu);
void création_point_map(MAPS *maps);

//création des tableau map
void allocation_memoire_tableau(MAPS *map);


//création du seedmap aléatoire 
void seedmap(MAPS *maps);

//nettoyage des tableau
void nettoyage_tableau(MAPS *map);
void nettoyage_seedmap(MAPS *maps);

//recupération centre
int get_center_map_largeur(MAPS* map);
int get_center_map_hauteur(MAPS* map);

//debugage
void afficher_map_debug(MAPS maps);

extern MAPS* map;

#endif // MAPS_H