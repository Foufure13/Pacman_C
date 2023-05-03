#include <SDL2/SDL_keycode.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_test_images.h>

#include "printhello.c"

#include "keybinding_action.h"

Deplacement deplacementInstance = {0};
Deplacement* deplacement = &deplacementInstance;



void appuye_touche(SDL_Event event, SDL_bool *programme, Deplacement *rect_image, SDL_Rect *srcrect)
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
                    printtest();
                    continue;
                case SDLK_z:
                    printf("Appui sur la touche Z\n");
                    srcrect->y = 32;
                    rect_image->vitesseX = 0;
                    rect_image->vitesseY = 1 ;               
                    rect_image->directionY = -1;                    
                    continue;
                case SDLK_q:
                    printf("Appui sur la touche Q\n"); 
                    srcrect->y = 0;
                    rect_image->vitesseY = 0 ;                                       
                    rect_image->vitesseX = 1;
                    rect_image->directionX = -1;         
                    continue;
                case SDLK_d:
                    printf("Appui sur la touche D\n");
                    srcrect->y = 16;
                    rect_image->vitesseY = 0 ;                     
                    rect_image->vitesseX = 1;
                    rect_image->directionX = 1;    
                    continue;
                case SDLK_s:
                    printf("Appui sur la touche S\n");
                    srcrect->y = 48;
                    rect_image->vitesseX = 0;
                    rect_image->vitesseY = 1;
                    rect_image->directionY = 1;                      
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