
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


#include "affichage.h"

void game_over_pacman (MAPS *maps, SDL_Renderer *rendu, int niveau)
{
  SDL_Color textColor = { 255, 255, 255 ,SDL_ALPHA_OPAQUE}; // couleur blanche
  // TTF_Font* font = TTF_OpenFont("font/DS-DIGII.TTF", 24); // Charge une police nommée "myfont.ttf" avec une taille de 24 points
  if (TTF_Init() == -1) {
    printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
  // gestion de l'erreur
  }
  TTF_Font* font = TTF_OpenFont("font/DS-DIGI.TTF", 100);
  if (font == NULL) {
    printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
  // gestion de l'erreur
  }
  SDL_Surface* surface_lettre = TTF_RenderText_Solid(font, "Game Over", textColor);
  SDL_Surface* surface_espace = TTF_RenderText_Solid(font, "Appuyer sur espace pour revenir au menu", textColor);

  SDL_Texture* texture_lettre = SDL_CreateTextureFromSurface(rendu, surface_lettre);
  SDL_Texture* texture_espace = SDL_CreateTextureFromSurface(rendu, surface_espace);

  SDL_Rect dstrect_lettre = { (maps->x/2)-200, (maps->y/2)-72, 400, 40 };
  SDL_Rect dstrect_espace = { (maps->x/2)-205, (maps->y/2)+50, 400, 32 };


  SDL_RenderCopy(rendu, texture_lettre, NULL, &dstrect_lettre);
  SDL_RenderCopy(rendu, texture_espace, NULL, &dstrect_espace);

  TTF_CloseFont(font);
  SDL_FreeSurface(surface_lettre);
  SDL_DestroyTexture(texture_lettre);
  SDL_FreeSurface(surface_espace);
  SDL_DestroyTexture(texture_espace);
}

void Affichage_niveau (MAPS *maps, SDL_Renderer *rendu, int niveau)
{
  SDL_Color textColor = { 255, 255, 255 ,SDL_ALPHA_OPAQUE}; // couleur blanche
  // TTF_Font* font = TTF_OpenFont("font/DS-DIGII.TTF", 24); // Charge une police nommée "myfont.ttf" avec une taille de 24 points

  if (TTF_Init() == -1) {
    printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
  // gestion de l'erreur
  }

  TTF_Font* font = TTF_OpenFont("font/DS-DIGI.TTF", 100);
  if (font == NULL) {
    printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
  // gestion de l'erreur
  }
  char numberStr[16];
  sprintf(numberStr, "%d", niveau);



  SDL_Surface* surface = TTF_RenderText_Solid(font, (numberStr), textColor);
  SDL_Surface* surface_lettre = TTF_RenderText_Solid(font, "niveau :", textColor);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);
  SDL_Texture* texture_lettre = SDL_CreateTextureFromSurface(rendu, surface_lettre);

  SDL_Rect dstrect_lettre = { (maps->x/2)-64, maps->y-24, 96, 24 };
  SDL_Rect dstrect = { (maps->x/2)+32, maps->y-24, 20, 24 };

  SDL_RenderCopy(rendu, texture_lettre, NULL, &dstrect_lettre);
  SDL_RenderCopy(rendu, texture, NULL, &dstrect);

  TTF_CloseFont(font);
  SDL_FreeSurface(surface_lettre);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
  SDL_DestroyTexture(texture_lettre);
}


void Affichage_score(MAPS *maps, SDL_Renderer *rendu, Deplacement pacman)
{
  SDL_Color textColor = { 255, 255, 255,SDL_ALPHA_OPAQUE }; // couleur blanche
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

void Affichage_pacman ( SDL_Renderer *rendu, Deplacement pacman, SDL_Rect *pacman_srcrect, SDL_Rect *pacman_dstrect)
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

void fantom_Gtype (MAPS *maps, Ghost *fantomRed) {
  if (fantomRed->Gtype == 1) {
      if (fantomRed->fantom_dstrect.y > (maps->y-80)/2 && maps->tableau[fantomRed->fantom_dstrect.y-1][fantomRed->fantom_dstrect.x]  != 'M') {
        fantomRed->vitesseX = 0 ;
        fantomRed->vitesseY = 1 ;
        fantomRed->directionX = 0 ;
        fantomRed->directionY = -1 ;
  }
  }
  if (fantomRed->Gtype == 2) {
      if (fantomRed->fantom_dstrect.y < (maps->y)/2 && maps->tableau[fantomRed->fantom_dstrect.y+1][fantomRed->fantom_dstrect.x]  != 'M') {
        fantomRed->vitesseX = 0 ;
        fantomRed->vitesseY = 1 ;
        fantomRed->directionX = 0 ;
        fantomRed->directionY = 1 ;
  }
  }

  if (fantomRed->Gtype == 3) {
      if (fantomRed->fantom_dstrect.x < (maps->x)/2 && maps->tableau[fantomRed->fantom_dstrect.y][fantomRed->fantom_dstrect.x+1]  != 'M') {
        fantomRed->vitesseX = 1 ;
        fantomRed->vitesseY = 0 ;
        fantomRed->directionX = 1 ;
        fantomRed->directionY = 0 ;
  }
  }

  if (fantomRed->Gtype == 4) {
      if (fantomRed->fantom_dstrect.x > (maps->x-80)/2 && maps->tableau[fantomRed->fantom_dstrect.y][fantomRed->fantom_dstrect.x-1]  != 'M') {
        fantomRed->vitesseX = 1 ;
        fantomRed->vitesseY = 0 ;
        fantomRed->directionX = -1 ;
        fantomRed->directionY = 0 ;
  }
  }
}

void fantom_collision_mur(MAPS *maps, Ghost *fantomRed) {

  if (fantomRed->fantom_dstrect.y < 32 || fantomRed->fantom_dstrect.y > maps->y-48-16 ) {
    // printf("emplacement fantom Y %d + maxi map %d\n", fantom_dstrect->y, map->y-48);
    fantomRed->directionY *= -1;
  }
  if (fantomRed->fantom_dstrect.x < 32 || fantomRed->fantom_dstrect.x > maps->x-48 ) {
    // printf("emplacement fantom X %d + maxi map %d\n", fantom_dstrect->y,  map->x-48);
    fantomRed->directionX *= -1;
  }

  //regarde en bas
  if ( fantomRed->directionY == 1 && fantomRed->vitesseY == 1 &&  maps->tableau[fantomRed->fantom_dstrect.y+1][fantomRed->fantom_dstrect.x]  == 'M'){
      fantomRed->vision_B =0 ;
      fantomRed->vitesseY = 0 ;
  }
  //regarde en haut
  if ( fantomRed->directionY == -1 && fantomRed->vitesseY == 1 &&  maps->tableau[fantomRed->fantom_dstrect.y-1][fantomRed->fantom_dstrect.x]  == 'M'){
      fantomRed->vision_H =0 ;                   
      fantomRed->vitesseY = 0 ;
  }
  //regarde a droite
  if ( fantomRed->directionX == 1 && fantomRed->vitesseX == 1 && maps->tableau[fantomRed->fantom_dstrect.y][fantomRed->fantom_dstrect.x+1]  == 'M'){
      fantomRed->vision_D =0 ;                     
      fantomRed->vitesseX = 0 ;
  }
  //regarde a gauche
  if ( fantomRed->directionX == -1 && fantomRed->vitesseX == 1 &&  maps->tableau[fantomRed->fantom_dstrect.y][fantomRed->fantom_dstrect.x-1]  == 'M'){
      fantomRed->vision_G =0 ;
      fantomRed->vitesseX = 0 ;
  }
}

void fantom_follow_pacman ( Ghost *fantomRed, SDL_Rect pacman_dstrect) {
  for (int f =-8; f<8 ; f++) {
    if (fantomRed->fantom_dstrect.x+f == pacman_dstrect.x) {
      if (fantomRed->fantom_dstrect.y > pacman_dstrect.y && (fantomRed->fantom_dstrect.y-pacman_dstrect.y < 100)) {
        fantomRed->vitesseX =0;
        fantomRed->directionX =0;
        fantomRed->vitesseY = 1;
        fantomRed->directionY =-1;
        fantomRed->fantom_srcrect.x = 0;
        // printf("je tevois y1\n");
      } else if (fantomRed->fantom_dstrect.y - pacman_dstrect.y < -100) {
        fantomRed->vitesseX =0;
        fantomRed->directionX =0;
        fantomRed->vitesseY = 1;
        fantomRed->directionY =1;
        fantomRed->fantom_srcrect.x = 32;
        // printf("je tevois y2\n");
      }
    }
    if (fantomRed->fantom_dstrect.y+f == pacman_dstrect.y  ) {
      if (fantomRed->fantom_dstrect.x > pacman_dstrect.x && (fantomRed->fantom_dstrect.x - pacman_dstrect.x < 100)) {
        fantomRed->vitesseX =1;
        fantomRed->directionX =-1;
        fantomRed->vitesseY = 0;
        fantomRed->directionY =0;
        fantomRed->fantom_srcrect.x = 64;
        // printf("je tevois x1\n");
      } else if (fantomRed->fantom_dstrect.x - pacman_dstrect.x < -100) {
        fantomRed->vitesseX =1;
        fantomRed->directionX =1;
        fantomRed->vitesseY = 0;
        fantomRed->directionY =0;
        fantomRed->fantom_srcrect.x = 96;
        // printf("je tevois x2\n");
    }
  }
}
}


void Affichage_fantom (MAPS *maps, SDL_Renderer *rendu, Ghost *fantomRed, SDL_Rect pacman_dstrect)
{
  SDL_Surface *image_fantom = SDL_LoadBMP("assets/pacman_ghost.bmp");
  SDL_Texture *texture_fantom = SDL_CreateTextureFromSurface(rendu,image_fantom); 

  // fantom_longue_vision(maps, fantomRed, pacman_dstrect) ;
  fantom_follow_pacman ( fantomRed, pacman_dstrect);

  fantom_Gtype(maps, fantomRed);
  fantom_collision_mur( maps, fantomRed) ;

  fantomRed->fantom_dstrect.x += fantomRed->directionX * fantomRed->vitesseX;
  fantomRed->fantom_dstrect.y +=  fantomRed->directionY * fantomRed->vitesseY;

  SDL_RenderCopy(rendu, texture_fantom, &fantomRed->fantom_srcrect, &fantomRed->fantom_dstrect);

  SDL_FreeSurface(image_fantom);
  SDL_DestroyTexture(texture_fantom);
}



void reset_game (MAPS *maps,SDL_Rect *pacman_dstrect, Ghost *fantomRed, Ghost *fantomPink, Ghost *fantomBlue, Ghost *fantomOrange, Deplacement *pacman,  int *game_start)
{
  *game_start =0;
  for (int i = 0; i < maps->y; i++) {
  for (int j = 0; j < maps->x; j++) {
      maps->tableau[i][j] = ' ' ;
  }
  }

  seedmap(maps);
  création_point_map(maps);

  pacman->vie =3;
  pacman->point_joueur = 0;

  pacman_dstrect->x = (maps->x-32)/2-78;
  pacman_dstrect->y = ((maps->y-48)/2-78);

  fantomRed->fantom_dstrect.x =(maps->x-32)/2;
  fantomRed->fantom_dstrect.y = (maps->y-48)/2;

  fantomPink->fantom_dstrect.x =(maps->x-32)/2;
  fantomPink->fantom_dstrect.y = (maps->y-48)/2;

  fantomBlue->fantom_dstrect.x =(maps->x-32)/2;
  fantomBlue->fantom_dstrect.y = (maps->y-48)/2;

  fantomOrange->fantom_dstrect.x =(maps->x-32)/2;
  fantomOrange->fantom_dstrect.y = (maps->y-48)/2;

}

void hit_reset_game (MAPS *maps,SDL_Rect *pacman_dstrect,int *game_start, Ghost *fantomRed, Ghost *fantomPink, Ghost *fantomBlue, Ghost *fantomOrange, Ghost *fantomRedSpe, Ghost *fantomPinkSpe, Ghost *fantomBlueSpe, Ghost *fantomOrangeSpe)
{
  *game_start =0;

  pacman_dstrect->x = (maps->x-32)/2-78;
  pacman_dstrect->y = ((maps->y-48)/2-78);

  fantomRed->fantom_dstrect.x =(maps->x-32)/2;
  fantomRed->fantom_dstrect.y = (maps->y-48)/2;

  fantomPink->fantom_dstrect.x =(maps->x-32)/2;
  fantomPink->fantom_dstrect.y = (maps->y-48)/2;

  fantomBlue->fantom_dstrect.x =(maps->x-32)/2;
  fantomBlue->fantom_dstrect.y = (maps->y-48)/2;

  fantomOrange->fantom_dstrect.x =(maps->x-32)/2;
  fantomOrange->fantom_dstrect.y = (maps->y-48)/2;

  if (fantomRedSpe->actif == 1) {
    fantomRedSpe->fantom_dstrect.x =(maps->x-32)/2;
    fantomRedSpe->fantom_dstrect.y = (maps->y-48)/2;
  }

  if (fantomPinkSpe->actif == 1) {
    fantomPinkSpe->fantom_dstrect.x =(maps->x-32)/2;
    fantomPinkSpe->fantom_dstrect.y = (maps->y-48)/2;
  }

  if (fantomBlueSpe->actif == 1) {
    fantomBlueSpe->fantom_dstrect.x =(maps->x-32)/2;
    fantomBlueSpe->fantom_dstrect.y = (maps->y-48)/2;
  }

  if (fantomOrangeSpe->actif == 1) {
    fantomOrangeSpe->fantom_dstrect.x =(maps->x-32)/2;
    fantomOrangeSpe->fantom_dstrect.y = (maps->y-48)/2;
  }
}