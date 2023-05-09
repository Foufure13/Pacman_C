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

int random_patern(MAPS *maps)
{

  int nombre_structure_largeur = ((maps->x - 16) /16)/5;
  int nombre_structure_hauteur = ((maps->y - 16) /16)/10 ;

  int tableau[nombre_structure_largeur][nombre_structure_hauteur];
  srand((unsigned)time(NULL));

  for (int i = 0; i < nombre_structure_largeur*nombre_structure_hauteur; i++) {
    for(int j =0; j< 10; j++) {
      tableau[i][j]= rand()%10;
    }
  }

  return 1;
}


int (*patern1())[4]
{
    static int tableau[10][4] = {
        {' ',' ',' ',' '},
        {' ','M',' ',' '},
        {' ','M',' ',' '},
        {' ','M',' ',' '},
        {' ','M','M',' '},
        {' ','M','M',' '},
        {' ','M',' ',' '},
        {' ','M',' ',' '},
        {' ','M',' ',' '},
        {' ',' ',' ',' '},
    };
    
    return tableau;
}

int (*patern2())[4]
{
    static int tableau[10][4] = {
        {' ',' ',' ',' '},
        {' ','M','M',' '},
        {' ',' ','M',' '},
        {' ',' ','M',' '},
        {' ',' ','M',' '},
        {' ',' ',' ',' '},
        {' ',' ',' ',' '},
        {' ','M','M',' '},
        {' ','M','M',' '},
        {' ',' ',' ',' '},
    };
    
    return tableau;
}

int (*patern3())[4]
{
    static int tableau[10][4] = {
        {' ',' ',' ',' '},
        {' ','M','M',' '},
        {' ','M','M',' '},
        {' ','M','M',' '},
        {' ','M','M',' '},
        {' ','M','M',' '},
        {' ',' ',' ',' '},
        {'M','M','M','M'},
        {' ',' ',' ',' '},
        {' ',' ',' ',' '},
    };
    
    return tableau;
}

void structur_map(MAPS *maps, SDL_Window *fenetre, SDL_Renderer *rendu)
{

  int nombre_structure_largeur = ((maps->x - 16) /16)/5;
  int nombre_structure_hauteur = ((maps->y - 16) /16)/10 ;
  // printf("struct largeur %d \n", nombre_structure_possible_largeur);
  // printf("struct hauteur %d \n", nombre_structure_possible_hauteur);
  
  SDL_Surface *map = SDL_LoadBMP("assets/pacman_background.bmp");
  SDL_Texture *texture2 = SDL_CreateTextureFromSurface(rendu,map); ;

  SDL_Rect map_srcrect = { 0, 16, 4, 4 };
  SDL_Rect map_dstrect = { 0, 0, 16, 16 };




        
  
  // int paternX[10][4] = radom_patern();
 


    int tableau2D[10][4];
    int (*tableau1D)[4] = patern2();

    // Copie les éléments du tableau 1D dans le tableau 2D
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 4; j++) {
            tableau2D[i][j] = tableau1D[i][j];
        }
    }

  int emplacementStructX = 16, emplacementStructY = 16;


  for (int i = 0; i < 10; i++) {
  for (int j = 0; j < 4; j++) {
    if (tableau2D[i][j]== '|')
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
    if (tableau2D[i][j]== '-')
    {
      map_dstrect.x = emplacementStructX+j*16;
      map_dstrect.y = emplacementStructY+i*16;
      SDL_Rect map_srcrect = { 16, 0, 4, 4 };
      SDL_RenderCopy(rendu, texture2, &map_srcrect, &map_dstrect);
      for (int k = 0; k < 32; k++)
      {
        maps->tableau[emplacementStructY+(i*16)][emplacementStructX + (j*16+k-16)] = '-';
      }
    }
    if (tableau2D[i][j]== 'M')
    {
      map_dstrect.x = emplacementStructX+j*16;
      map_dstrect.y = emplacementStructY+i*16;
      SDL_Rect map_srcrect = { 0, 16, 4, 4 };
      SDL_RenderCopy(rendu, texture2, &map_srcrect, &map_dstrect);
      for (int k = 0; k < 31; k++) {
      for (int o = 0; o < 31; o++) {
        maps->tableau[emplacementStructY+(i*16+k-15)][emplacementStructX + (j*16+o-15)] = 'M';
        }
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



