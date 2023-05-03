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
    SDL_version nb;
    SDL_Window *fen=NULL;   // Pointeur de fenêtre
    SDL_Renderer *rendu=NULL;
    SDL_Rect rectangle;
    SDL_VERSION(&nb);
    printf("Nous sommes sur la SDL %d.%d.%d ...",nb.major, nb.minor,nb.patch);

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

    if (SDL_SetRenderDrawColor(rendu,0,255,255,SDL_ALPHA_OPAQUE) !=0)
        GestErreur("PB COULEUR");

    if (SDL_RenderDrawPoint(rendu,244,141) !=0)
        GestErreur("PB POINT");
    if (SDL_RenderDrawPoint(rendu,235,141) !=0)
        GestErreur("PB POINT");
    if (SDL_RenderDrawPoint(rendu,225,141) !=0)
        GestErreur("PB POINT");

    if (SDL_RenderDrawLine(rendu,100,100,300,300) !=0)
        GestErreur("PB TRAIT");  

     if (SDL_SetRenderDrawColor(rendu,71,214,84,SDL_ALPHA_OPAQUE) !=0)
        GestErreur("PB COULEUR");

    rectangle.x=500;
    rectangle.y=300;
    rectangle.w=200;
    rectangle.h=100;

    //if (SDL_RenderDrawRect(rendu,&rectangle) !=0)
    //    GestErreur("PB RECTANGLE");  

    if (SDL_RenderFillRect(rendu,&rectangle) !=0)
        GestErreur("PB RECTANGLE");

    //Afficher le rendu
    SDL_RenderPresent(rendu);


//VISUALISATION
    SDL_Delay(5000);

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

 
