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



void collision(MAPS *map, SDL_Rect *pacman_dstrect, SDL_Rect *pacman_srcrect, Deplacement *rect_image)
{
    if ( rect_image->directionY == 1 && rect_image->vitesseY == 1 && map->tableau[pacman_dstrect->y+16][pacman_dstrect->x]  == '-'){
        rect_image->vitesseY = 0 ;
    }
    if ( rect_image->directionY == -1 && rect_image->vitesseY == 1 && map->tableau[pacman_dstrect->y-16][pacman_dstrect->x]  == '-'){
        rect_image->vitesseY = 0 ;
    }
    if ( rect_image->directionX == 1 && rect_image->vitesseX == 1 && map->tableau[pacman_dstrect->y][pacman_dstrect->x+16]  == '|'){
        rect_image->vitesseX = 0 ;
    }
    if ( rect_image->directionX == -1 && rect_image->vitesseX == 1 && map->tableau[pacman_dstrect->y][pacman_dstrect->x-16]  == '|'){
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
                    printf("Appui sur la touche B\n");
                    continue;
                case SDLK_z:
                    printf("Appui sur la touche Z\n");
                    pacman_control(pacman_srcrect, rect_image, 32, 0, 0, 1 ,-1);                  
                    continue;
                case SDLK_q:
                    printf("Appui sur la touche Q\n"); 
                    pacman_control(pacman_srcrect, rect_image, 0, 1, -1, 0 ,0);         
                    continue;
                case SDLK_d:
                    printf("Appui sur la touche D\n");
                    pacman_control(pacman_srcrect, rect_image, 16, 1, 1, 0 ,0);   
                    continue;
                case SDLK_s:
                    printf("Appui sur la touche S\n");
                    pacman_control(pacman_srcrect, rect_image, 48, 0, 0, 1 ,1);                  
                    continue; 
                case SDLK_SPACE:
                    printf("Appui sur la touche ESPACE\n");
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
                    printf("Relâche de la touche B\n");
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