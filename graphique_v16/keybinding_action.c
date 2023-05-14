#include <SDL2/SDL_keycode.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_test_images.h>


#include "keybinding_action.h"
#include "map.h"

Deplacement deplacementInstance = {0};
Deplacement* deplacement = &deplacementInstance;

Ghost ghostInstance = {0};
Ghost* ghost = &ghostInstance;


void collision_fantom_pacman(MAPS *map, SDL_Rect *pacman_dstrect, Deplacement *pacman,  Ghost fantom )
{
    for (int y =-8; y <14; y++) {
    for (int x =-8; x <14; x++) {
        
    if ((pacman_dstrect->y +y == fantom.fantom_dstrect.y && pacman_dstrect->x +x == fantom.fantom_dstrect.x) || (pacman_dstrect->y  == fantom.fantom_dstrect.y +y && pacman_dstrect->x == fantom.fantom_dstrect.x +x) ) {
        pacman->vie +=1;
    }
    }
    }
}

void collision_point(MAPS *map, SDL_Rect *pacman_dstrect, SDL_Rect *pacman_srcrect, Deplacement *rect_image)
{
    for (int y =-9; y <11; y++) {
    for (int x =-9; x <11; x++) {
        
    if (map->tableau[pacman_dstrect->y +y][pacman_dstrect->x +x]  == 'x' && (rect_image->directionX == 1 || rect_image->directionY ==1 || rect_image->directionX == -1 || rect_image->directionY == -1)) {
        map->tableau[pacman_dstrect->y+y][pacman_dstrect->x+x] = ' ';
        rect_image->point_joueur +=1;
    }
    }
    }
}

void collision(MAPS *map, SDL_Rect *pacman_dstrect, SDL_Rect *pacman_srcrect, Deplacement *rect_image)
{
    if ( rect_image->directionY == 1 && rect_image->vitesseY == 1 && (map->tableau[pacman_dstrect->y+16][pacman_dstrect->x]  == '-' || map->tableau[pacman_dstrect->y+1][pacman_dstrect->x]  == 'M')){
        rect_image->vitesseY = 0 ;
        
    }
    if ( rect_image->directionY == -1 && rect_image->vitesseY == 1 && (map->tableau[pacman_dstrect->y-16][pacman_dstrect->x]  == '-' || map->tableau[pacman_dstrect->y-1][pacman_dstrect->x]  == 'M')){
        rect_image->vitesseY = 0 ;
    }
    if ( rect_image->directionX == 1 && rect_image->vitesseX == 1 && (map->tableau[pacman_dstrect->y][pacman_dstrect->x+16]  == '|' || map->tableau[pacman_dstrect->y][pacman_dstrect->x+1]  == 'M')){
        rect_image->vitesseX = 0 ;
    }
    if ( rect_image->directionX == -1 && rect_image->vitesseX == 1 && (map->tableau[pacman_dstrect->y][pacman_dstrect->x-16]  == '|' || map->tableau[pacman_dstrect->y][pacman_dstrect->x-1]  == 'M')){
        rect_image->vitesseX = 0 ;
    }
}

void pacman_control(SDL_Rect *pacman_srcrect, Deplacement *rect_image, int icone, int vitesseX, int directionX,int vitesseY, int directionY)
{
    pacman_srcrect->y = icone;
    rect_image->vitesseX = vitesseX;
    rect_image->vitesseY = vitesseY ;
    rect_image->directionX = directionX;               
    rect_image->directionY = directionY;

}

void appuye_touche(SDL_Event event, SDL_bool *programme, Deplacement *rect_image, SDL_Rect *pacman_srcrect,SDL_Rect *pacman_dstrect, MAPS *map)
{
    

    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_b:
                    // printf("Appui sur la touche B\n");
                    continue;
                case SDLK_z:
                    // printf("Appui sur la touche Z\n");
                    pacman_control(pacman_srcrect, rect_image, 32, 0, 0, 1 ,-1);                  
                    continue;
                case SDLK_q:
                    // printf("Appui sur la touche Q\n"); 
                    pacman_control(pacman_srcrect, rect_image, 0, 1, -1, 0 ,0);         
                    continue;
                case SDLK_d:
                    // printf("Appui sur la touche D\n");
                    pacman_control(pacman_srcrect, rect_image, 16, 1, 1, 0 ,0);   
                    continue;
                case SDLK_s:
                    // printf("Appui sur la touche S\n");
                    pacman_control(pacman_srcrect, rect_image, 48, 0, 0, 1 ,1);                  
                    continue; 
                case SDLK_SPACE:
                    // printf("Appui sur la touche ESPACE\n");
                    rect_image->vitesseY = 0;
                    rect_image->vitesseX = 0;     
                    continue;
                
                default:                
                    continue;
                }
                case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_b:
                    // printf("Relâche de la touche B\n");
                    continue;
                
                default:
                    continue;
                }
                case SDL_QUIT:
                *programme=SDL_FALSE;
                break;
            default:
                break;
        }
    }
}

void fantom_deplacement(MAPS *map,  Ghost *fantomRed,SDL_Rect pacman_dstrect){

                fantomRed->vision_H =1 ;
                fantomRed->vision_D =1 ;
                fantomRed->vision_B =1 ;
                fantomRed->vision_G =1 ;

                // for (int i =0; i <6; i++) {
                //regarde en bas
                if (map->tableau[fantomRed->fantom_dstrect.y+1][fantomRed->fantom_dstrect.x]  == 'M'){
                    fantomRed->vision_B =0 ;

                }
                //regarde en haut
                if ( map->tableau[fantomRed->fantom_dstrect.y-1][fantomRed->fantom_dstrect.x]  == 'M'){
                    fantomRed->vision_H =0 ;                   
                }
                //regarde a droite
                if ( map->tableau[fantomRed->fantom_dstrect.y][fantomRed->fantom_dstrect.x+1]  == 'M'){
                    fantomRed->vision_D =0 ;                     
                }
                //regarde a gauche
                if ( map->tableau[fantomRed->fantom_dstrect.y][fantomRed->fantom_dstrect.x-1]  == 'M'){
                    fantomRed->vision_G =0 ;
                }
                // }
                // printf("vision haut %d \n", fantomRed->vision_H);
                // printf("vision droite %d \n", fantomRed->vision_D);
                // printf("vision bas %d \n", fantomRed->vision_B);
                // printf("vision gauche %d \n", fantomRed->vision_G);
                
                
                int direction_aleatoire, boucle =1;

                while (boucle == 1)
                {
                    direction_aleatoire = rand()%4;
                    if (direction_aleatoire == 0 && fantomRed->vision_H !=0) {
                        fantomRed->vitesseX =0;
                        fantomRed->directionX =0;
                        fantomRed->vitesseY =1;
                        fantomRed->directionY =-1;
                        fantomRed->fantom_srcrect.x = 0;
                        boucle = 0;
                    }
                    if (direction_aleatoire == 1 && fantomRed->vision_D !=0) {
                        fantomRed->vitesseX =1;
                        fantomRed->directionX =1;
                        fantomRed->vitesseY = 0;
                        fantomRed->directionY =0;
                        fantomRed->fantom_srcrect.x = 96;
                        boucle = 0;
                    }
                    if (direction_aleatoire ==2 && fantomRed->vision_B !=0) {
                        fantomRed->vitesseX =0;
                        fantomRed->directionX =0;
                        fantomRed->vitesseY =1;
                        fantomRed->directionY =1;
                        fantomRed->fantom_srcrect.x = 32;
                        boucle = 0;
                    }
                    if (direction_aleatoire ==3 && fantomRed->vision_G !=0) {
                        fantomRed->vitesseX =1;
                        fantomRed->directionX =-1;
                        fantomRed->vitesseY =0;
                        fantomRed->directionY =0;
                        fantomRed->fantom_srcrect.x = 64;
                        boucle = 0;
                    }
                }

}

