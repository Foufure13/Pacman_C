
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>   
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_test_images.h>
#include <SDL2/SDL_ttf.h>

#include <ncurses.h>
#include "affichage.h"





void Affichage_score(MAPS *maps, SDL_Renderer *rendu, Deplacement pacman)
{
  SDL_Color textColor = { 255, 255, 255 }; // couleur blanche
  // TTF_Font* font = TTF_OpenFont("font/DS-DIGII.TTF", 24); // Charge une police nommée "myfont.ttf" avec une taille de 24 points

  if (TTF_Init() == -1) {
    printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
  // gestion de l'erreur
  }

  TTF_Font* font = TTF_OpenFont("font/DS-DIGI.TTF", 24);
  if (font == NULL) {
    printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
  // gestion de l'erreur
  }
  char numberStr[16];
  sprintf(numberStr, "%d", pacman.point_joueur);



  SDL_Surface* surface = TTF_RenderText_Solid(font, (numberStr), textColor);
  SDL_Surface* surface_lettre = TTF_RenderText_Solid(font, "score :", textColor);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);
  SDL_Texture* texture_lettre = SDL_CreateTextureFromSurface(rendu, surface_lettre);

  SDL_Rect dstrect_lettre = { maps->x-128, maps->y-24, 48, 24 };
  SDL_RenderCopy(rendu, texture_lettre, NULL, &dstrect_lettre);

  SDL_Rect dstrect = { maps->x-64, maps->y-24, 20, 24 };
  if (pacman.point_joueur > 99)
  {
    dstrect.w = 32;
  } 
  if (pacman.point_joueur > 999)
  {
    dstrect.w = 38;
  }
  SDL_RenderCopy(rendu, texture, NULL, &dstrect);

  TTF_CloseFont(font);
  SDL_FreeSurface(surface_lettre);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
  SDL_DestroyTexture(texture_lettre);
}

void Affichage_vie (MAPS *maps, SDL_Renderer *rendu, Deplacement pacman)
{

  SDL_Surface *map = SDL_LoadBMP("assets/pacman_pacman.bmp");
  SDL_Texture *texture2 = SDL_CreateTextureFromSurface(rendu,map); 

      
  for (int i =0; i < pacman.vie; i++)
  {
    SDL_Rect map_srcrect = { 16, 16, 15, 15 };
    SDL_Rect map_dstrect = { 24 + i*24, maps->y -20, 15, 15 };

    SDL_RenderCopy(rendu, texture2, &map_srcrect, &map_dstrect);
  }



  SDL_FreeSurface(map);
  SDL_DestroyTexture(texture2);
}

void Affichage_pacman (MAPS *maps, SDL_Renderer *rendu, Deplacement pacman, SDL_Rect *pacman_srcrect, SDL_Rect *pacman_dstrect)
{
  SDL_Surface *image_pacman = SDL_LoadBMP("assets/pacman_pacman.bmp");
  SDL_Texture *texture_pacman = SDL_CreateTextureFromSurface(rendu,image_pacman); 

  pacman_dstrect->y += pacman.vitesseY *  pacman.directionY ;
  pacman_dstrect->x += pacman.vitesseX *  pacman.directionX ;

  //animation pacman
  pacman_srcrect->x += 16; 
  if (pacman_srcrect->x > 49)
      pacman_srcrect->x = 0;

  SDL_RenderCopy(rendu, texture_pacman, pacman_srcrect, pacman_dstrect);

  SDL_FreeSurface(image_pacman);
  SDL_DestroyTexture(texture_pacman);
}

void Affichage_fantom (MAPS *maps, SDL_Renderer *rendu, SDL_Rect *fantom_srcrect, SDL_Rect *fantom_dstrect)
{
  SDL_Surface *image_fantom = SDL_LoadBMP("assets/pacman_ghost.bmp");
  SDL_Texture *texture_fantom = SDL_CreateTextureFromSurface(rendu,image_fantom); 

  // fantom_dstrect->y += pacman.vitesseY *  pacman.directionY ;
  // fantom_dstrect->x += pacman.vitesseX *  pacman.directionX ;

  //animation pacman
  // pacman_srcrect->x += 16; 
  // if (pacman_srcrect->x > 49)
  //     pacman_srcrect->x = 0;

  SDL_RenderCopy(rendu, texture_fantom, fantom_srcrect, fantom_dstrect);

  SDL_FreeSurface(image_fantom);
  SDL_DestroyTexture(texture_fantom);
}