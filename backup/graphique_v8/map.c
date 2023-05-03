#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>   
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_test_images.h>

#include <ncurses.h>

#include "map.h"

MAPS mapInstance = {0};
MAPS* map = &mapInstance;


void allocation_memoire_tableau(MAPS* map)
{
  // Allocation dynamique de la mémoire pour le tableau à deux dimensions
  map->tableau = malloc(map->y * sizeof(char*));
  for (int i = 0; i < map->y; i++) {
    map->tableau[i] = malloc(map->x * sizeof(char));
  }
}





void ajout_mur_map(MAPS maps, SDL_Window *fenetre, SDL_Renderer *rendu)
{

    SDL_Surface *map = SDL_LoadBMP("assets/pacman_pacman.bmp");
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(rendu,map); ;

    SDL_Rect map_srcrect = { 16, 16, 15, 15 };
    SDL_Rect map_dstrect = { 300, 300, 15, 15 };

    if (map == NULL)
        printf("map NOOKAY MAPS");
    if (texture2 == NULL)
        printf( "map NOOKAY TEXTURE");
        
    SDL_FreeSurface(map);

    // if (SDL_RenderCopy(rendu, texture2, &map_srcrect, &map_dstrect) !=0)
    //     printf( "map NOOKAY AFFICHAGE TEXTURE");



  for (int i = 0; i < maps.y; i++) {
  for (int j = 0; j < maps.x; j++) {
      maps.tableau[i][j] = ' ' ;
      if (i == 0 || i == maps.y-16)
      {
        map_dstrect.x = j;
        map_dstrect.y = i;
        SDL_RenderCopy(rendu, texture2, &map_srcrect, &map_dstrect);
        // maps.tableau[i][j] = '-' ;
      }
      if (j == 0 || j == maps.x-16)
      {
        map_dstrect.x = j;
        map_dstrect.y = i;
        SDL_RenderCopy(rendu, texture2, &map_srcrect, &map_dstrect);
        // maps.tableau[i][j] = '|' ;
      }
  }
  }

}


void affiche_map(MAPS tableau)
{
  system("clear"); //clear le terminal
  //Affichage du tableau
  for (int i = 0; i < tableau.y; i++) {
  for (int j = 0; j < tableau.x; j++) {
      printf("%c ", tableau.tableau[i][j]);
  }
  printf("\n");
  }
}

// void affiche_map_ncurses(MAPS tableau) {
//     int row, col;
//     getmaxyx(stdscr, row, col);
//     for (int i = 0; i < tableau.y; i++) {
//         for (int j = 0; j < tableau.x; j++) {
//             mvprintw(row/2 - tableau.y/2 + i, col/2 - tableau.x + j*2, "%c ", tableau.tableau[i][j]);
//         }
//     }
//     mvprintw(row-1, 0, "Appuyer sur 'a' pour quitter");
//     refresh();
// }


void nettoyage_tableau(MAPS *tableau)
{
  // Libération de la mémoire allouée pour le tableau
  for (int i = 0; i < tableau->y; i++) {
    free(tableau->tableau[i]);
  }
  free(tableau->tableau);
}



void map_controller(MAPS map,SDL_Window *fenetre, SDL_Renderer *rendu) {

  allocation_memoire_tableau(&map);
//   ajout_mur_map(map, fenetre, rendu);

  system("clear"); //clear le terminal

  map.tableau[map.pacman[0]][map.pacman[1]] = 'C'; //spawn du pacman
  char touche;

  nettoyage_tableau(&map);
  return ;
}