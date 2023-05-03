
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_test_images.h>

#include "printhello.c"
    




void appuye_touche(SDL_Event event, SDL_bool *programme)
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

    //Initialisation de la fenêtre
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR INIT SDL : %s !\n ",SDL_GetError());
        exit(EXIT_FAILURE);
    }



   //Création fenêtre + rendu
    if (SDL_CreateWindowAndRenderer(windowLargeur,windowHauteur,0, &fenetre, &rendu) != 0)
        GestErreur("ERREUR CREATION FENETRE + RENDU");

    

   /*
    * DESSINONS*
   */
    image=SDL_LoadBMP("SDL2/test/testyuv.bmp");
    if (image == NULL)
        verif_probleme_texture_rendu(fenetre,rendu, "IMAGE");

    texture=SDL_CreateTextureFromSurface(rendu,image);
    if (texture == NULL)
        verif_probleme_texture_rendu(fenetre,rendu, "TEXTURE");

    

    SDL_FreeSurface(image);

    
    // Modifier les coordonnées et les dimensions du rectangle source pour rogner de moitié en largeur
    rectangle.x = 200;  // La nouvelle position en x pour rogner de moitié
    rectangle.y = 100;           // La position en y reste inchangée
    rectangle.w = 400;  // La nouvelle largeur pour rogner de moitié
    rectangle.h = 200;      // La hauteur reste inchangée



    int vitesseY = 0;  // La vitesse de déplacement vertical
    int directionY = -1;  // La direction du déplacement (1 pour vers le haut, -1 pour vers le bas)




    if (SDL_QueryTexture(texture,NULL, NULL,&rectangle.w, &rectangle.h) != 0)
         verif_probleme_texture_rendu(fenetre,rendu, "TEXTURE");
    if (SDL_RenderCopy(rendu, texture, NULL, &rectangle) !=0)
         verif_probleme_texture_rendu(fenetre,rendu, "AFFICHAGE TEXTURE");


    



    ////VISUALISATION



    SDL_RenderPresent(rendu);//Afficher le rendu


    while (programme)
    {
        // Modifier la position en y du rectangle source pour le déplacement vertical
        rectangle.y += vitesseY * directionY;

        // Inverser la direction si le rectangle atteint les bords de la fenêtre
        if (rectangle.y <= 0 || rectangle.y >= windowHauteur - rectangle.h)
        {
            directionY = -directionY;
        }

        // // Effacer le rendu
        // SDL_RenderClear(rendu);

        // // Afficher le rendu avec le rectangle source modifié
        // SDL_RenderCopy(rendu, texture, &rectangle, NULL);

        // // Afficher le rendu
        // SDL_RenderPresent(rendu);
        


        appuye_touche(event, &programme);
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

 
