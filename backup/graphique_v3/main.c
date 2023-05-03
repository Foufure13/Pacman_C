#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <stdlib.h>


void GestErreur(char * message)
{
    SDL_Log("%s : %s !\n ",message,SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    SDL_Window *fen=NULL;   // Pointeur de fenêtre
    SDL_Renderer *rendu=NULL;
    SDL_Rect rectangle;
    SDL_Surface *chat=NULL;
    SDL_Texture *texture=NULL;
    SDL_bool programme=SDL_TRUE;
    SDL_Event event;
   
//INITIALISATION

    //Initialisation de la fenêtre
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR INIT SDL : %s !\n ",SDL_GetError());
        exit(EXIT_FAILURE);
    }

   //Création fenêtre + rendu
    if (SDL_CreateWindowAndRenderer(800,600,0, &fen, &rendu) != 0)
        GestErreur("ERREUR CREATION FENETRE + RENDU");

   /*
    * DESSINONS*
   */
    chat=SDL_LoadBMP("SDL2/test/testyuv.bmp");

    if (chat == NULL)
    {
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fen);
        GestErreur("PB IMAGE");
    }

 
    texture=SDL_CreateTextureFromSurface(rendu,chat);

    if (texture == NULL)
    {
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fen);
        GestErreur("PB TEXTURE");
    }

    SDL_FreeSurface(chat);

    //Afficher le rendu

    rectangle.x=200;
    rectangle.y=200;
    rectangle.w=50;
    rectangle.h=50;

    if (SDL_QueryTexture(texture,NULL, NULL,&rectangle.w, &rectangle.h) != 0)
    {
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fen);
        GestErreur("PB CHARGEMENT TEXTURE");
    }

    if (SDL_RenderCopy(rendu, texture, NULL, &rectangle) !=0)
    {
        SDL_DestroyRenderer(rendu);
        SDL_DestroyWindow(fen);
        GestErreur("PB AFFICHAGE TEXTURE");
    }

    //Afficher le rendu
    SDL_RenderPresent(rendu);
//VISUALISATION

    while (programme)
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
                    programme=SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
    }
 

//DESTRUCTION

    //Effacer le rendu
    if (SDL_RenderClear(rendu)!=0)
        GestErreur("Rendu non effacé");

    //Détruire du rendu
    SDL_DestroyRenderer(rendu);
    //Détruire la fenêtre
    SDL_DestroyWindow(fen);
    //Fermeture de la fenêtre
    SDL_Quit();
    return EXIT_SUCCESS;
}

 
