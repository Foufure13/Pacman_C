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





void ajout_mur_map(MAPS *maps, SDL_Window *fenetre, SDL_Renderer *rendu)
{

    SDL_Surface *map = SDL_LoadBMP("assets/pacman_background.bmp");
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(rendu,map); ;

    SDL_Rect map_srcrect = { 0, 0, 4, 4 };
    SDL_Rect map_dstrect = { 300, 300, 16, 16 };

    if (map == NULL)
        printf("map NOOKAY MAPS");
    if (texture2 == NULL)
        printf( "map NOOKAY TEXTURE");
        
    SDL_FreeSurface(map);

    // if (SDL_RenderCopy(rendu, texture2, &map_srcrect, &map_dstrect) !=0)
    //     printf( "map NOOKAY AFFICHAGE TEXTURE");



  for (int i = 0; i < maps->y; i++) {
  for (int j = 0; j < maps->x; j++) {
      maps->tableau[i][j] = ' ' ;
      if (i == 0 || i == maps->y-16)
      {
        map_srcrect.x = 16;
        map_srcrect.y = 0;
        map_dstrect.x = j;
        map_dstrect.y = i;
        SDL_RenderCopy(rendu, texture2, &map_srcrect, &map_dstrect);
        maps->tableau[i][j] = '-' ;
      }
      if (j == 0 || j == maps->x-16)
      {
        map_srcrect.x = 0;
        map_srcrect.y = 16;
        map_dstrect.x = j;
        map_dstrect.y = i;
        SDL_RenderCopy(rendu, texture2, &map_srcrect, &map_dstrect);
        maps->tableau[i][j] = '|' ;
      }
  }
  }

}



void structur_map(MAPS *maps, SDL_Window *fenetre, SDL_Renderer *rendu)
{

    SDL_Surface *map = SDL_LoadBMP("assets/pacman_background.bmp");
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(rendu,map); ;

    SDL_Rect map_srcrect = { 0, 16, 4, 4 };
    SDL_Rect map_dstrect = { 0, 0, 16, 16 };

        
    // SDL_FreeSurface(map);

    //SDL_RenderCopy(rendu, texture2, &map_srcrect, &map_dstrect);



  int patern1[10][4] = {
    {' ',' ',' ',' '},
    {' ','|',' ',' '},
    {' ','|',' ',' '},
    {' ','|',' ',' '},
    {' ','|','-',' '},
    {' ','|','-',' '},
    {' ','|',' ',' '},
    {' ','|',' ',' '},
    {' ','|',' ',' '},
    {' ',' ',' ',' '},
  };

  int emplacementStructX = 16, emplacementStructY = 32;


  for (int i = 0; i < 10; i++) {
  for (int j = 0; j < 4; j++) {
    if (patern1[i][j]== '|')
    {
      map_dstrect.x = emplacementStructX+j*16;
      map_dstrect.y = emplacementStructY+i*16;
      SDL_Rect map_srcrect = { 0, 16, 4, 4 };
      SDL_RenderCopy(rendu, texture2, &map_srcrect, &map_dstrect);
      for (int k = 0; k < 32; k++)
      {
        maps->tableau[emplacementStructY+(i*16+k-16)][emplacementStructX + (j*16)] = '|';
      }

    }
    if (patern1[i][j]== '-')
    {
      map_dstrect.x = emplacementStructX+j*16;
      map_dstrect.y = emplacementStructY+i*16;
      SDL_Rect map_srcrect = { 16, 0, 4, 4 };
      SDL_RenderCopy(rendu, texture2, &map_srcrect, &map_dstrect);
      for (int k = 0; k < 32; k++)
      {
        maps->tableau[emplacementStructY+(i*16)][emplacementStructX + (j*16+j-16)] = '-';
      }

    }
  }
  }
}

void afficher_map_debug(MAPS maps){
  // system("clear"); //clear le terminal
  //Affichage du tableau
  for (int i = 0; i < maps.y; i++) {
  for (int j = 0; j < maps.x; j++) {
      printf("%c ", maps.tableau[i][j]);
  }
  printf("\n");
  }
}


void nettoyage_tableau(MAPS *tableau)
{
  // Libération de la mémoire allouée pour le tableau
  for (int i = 0; i < tableau->y; i++) {
    free(tableau->tableau[i]);
  }
  free(tableau->tableau);
}



