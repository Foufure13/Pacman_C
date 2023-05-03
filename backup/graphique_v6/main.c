#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_test_images.h>

#include "keybinding_action.h"



void GestErreur(char * message)
{
    SDL_Log("%s : %s !\n ",message,SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void verif_probleme_texture_rendu( SDL_Window *fenetre,  SDL_Renderer *rendu, char string[]) {

    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    char message[] = "PB CHARGEMENT ";
    strcat(message, string);
    GestErreur(message);

}

void initialisation_fenetre()     //Initialisation de la fenêtre
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR INIT SDL : %s !\n ",SDL_GetError());
        exit(EXIT_FAILURE);
    }
}


void stop_border_screen(SDL_Rect rectangle,int windowHauteur,int windowLargeur,Deplacement *rect_image)
{
    // Inverser la direction si le rectangle atteint les bords de la fenêtre
    if (rectangle.y <= 0 || rectangle.y >= windowHauteur - rectangle.h)
    {
        rect_image->directionY = -rect_image->directionY;
    }
    if (rectangle.x <= 0 || rectangle.x >= windowLargeur - rectangle.w)
    {
        rect_image->directionX = -rect_image->directionX;
    }
}




int main(int argc, char** argv)
{
    SDL_Window *fenetre=NULL;   // Pointeur de fenêtre
    SDL_Renderer *rendu=NULL;
    SDL_Rect rectangle;
    SDL_Surface *image=NULL;
    SDL_Texture *texture=NULL;
    SDL_bool programme=SDL_TRUE;
    SDL_Event event;

    int windowLargeur = 1080, windowHauteur = 800;


//INITIALISATION
initialisation_fenetre();
   //Création fenêtre + rendu
    if (SDL_CreateWindowAndRenderer(windowLargeur,windowHauteur,0, &fenetre, &rendu) != 0)
        GestErreur("ERREUR CREATION FENETRE + RENDU");

    image=SDL_LoadBMP("SDL2/test/testyuv.bmp");
    if (image == NULL)
        verif_probleme_texture_rendu(fenetre,rendu, "IMAGE");

    texture=SDL_CreateTextureFromSurface(rendu,image);
    if (texture == NULL)
        verif_probleme_texture_rendu(fenetre,rendu, "TEXTURE");
    SDL_FreeSurface(image);



    rectangle.x = 100;  
    rectangle.y = 10;        
    // rectangle.w = image->w / 4;  // La nouvelle largeur pour rogner de moitié
    // rectangle.h = image->h / 2;      // La hauteur reste inchangée
    rectangle.w =  image->w / 4;  
    rectangle.h =  image->h / 3;

    Deplacement rect_image;
    rect_image.directionY = 1;
    rect_image.vitesseY = 0;
    rect_image.directionX = 1;
    rect_image.vitesseX = 0;
    
    

    // if (SDL_QueryTexture(texture,NULL, NULL,&rectangle.w, &rectangle.h) != 0)
    //      verif_probleme_texture_rendu(fenetre,rendu, "TEXTURE");
    if (SDL_RenderCopy(rendu, texture, NULL, &rectangle) !=0)
        verif_probleme_texture_rendu(fenetre,rendu, "AFFICHAGE TEXTURE");

    SDL_RenderPresent(rendu);

    while (programme)
    {
        appuye_touche(event, &programme, &rect_image);

        // Modifier la position en y du rectangle source pour le déplacement vertical
        rectangle.y += rect_image.vitesseY *  rect_image.directionY;
        rectangle.x += rect_image.vitesseX *  rect_image.directionX;

        stop_border_screen(rectangle, windowHauteur, windowLargeur, &rect_image);





 

        // Effacer le rendu
        SDL_RenderClear(rendu);
        // // Afficher le rendu avec le rectangle source modifié
        SDL_RenderCopy(rendu, texture,  NULL,&rectangle);
        // // Afficher le rendu
        SDL_RenderPresent(rendu);
    }
 

//DESTRUCTION

    //Effacer le rendu
    if (SDL_RenderClear(rendu)!=0)
        GestErreur("Rendu non effacé");

    //Détruire du rendu
    SDL_DestroyRenderer(rendu);
    //Détruire la fenêtre
    SDL_DestroyWindow(fenetre);
    //Fermeture de la fenêtre
    SDL_Quit();
    return EXIT_SUCCESS;
}

 
