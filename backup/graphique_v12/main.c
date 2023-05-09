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


#define spawn_pacman_x 16
#define spawn_pacman_y 16
#define windows_settings_width 10
#define windows_settings_height 3


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
    MAPS map;
    int nombre_structure_largeur = ((map.x - 16) /16)/5;
    int nombre_structure_hauteur = (((map.y - 16) /16)/10) ;

    int windowLargeur = map.x = 32 + (windows_settings_width * 16 *5);
    int windowHauteur = map.y = 16 + 32 + (windows_settings_height * 16 * 10 );

    allocation_memoire_tableau(&map);
    seedmap(&map);


    SDL_Window *fenetre=SDL_CreateWindow("SDL2 Sprite Sheets",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowLargeur, windowHauteur, 0);
    SDL_Renderer *rendu=SDL_CreateRenderer(fenetre, -1, 0);

    SDL_Surface *image = SDL_LoadBMP("assets/pacman_pacman.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rendu,image); 
    SDL_bool programme=SDL_TRUE;
    SDL_Event event;
    
    Uint32 ticks = SDL_GetTicks();
    Uint32 seconds = ticks / 1000 ;
    Uint32 sprite = seconds % 8;


    SDL_Rect pacman_srcrect = { 16, 16, 15, 15 };
    SDL_Rect pacman_dstrect = { spawn_pacman_x, spawn_pacman_y, 15, 15 };

    création_point_map(&map, fenetre,rendu);
    
  // system("clear"); //clear le terminal

//INITIALISATION
initialisation_fenetre();
    if (image == NULL)
        verif_probleme_texture_rendu(fenetre,rendu, "IMAGE");
    if (texture == NULL)
        verif_probleme_texture_rendu(fenetre,rendu, "TEXTURE");



    SDL_FreeSurface(image);

    if (SDL_RenderCopy(rendu, texture, &pacman_srcrect, &pacman_dstrect) !=0)
        verif_probleme_texture_rendu(fenetre,rendu, "AFFICHAGE TEXTURE");

    SDL_RenderPresent(rendu);







    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    Deplacement rect_image;
    rect_image.directionY = 1;
    rect_image.vitesseY = 0;
    rect_image.directionX = 1;
    rect_image.vitesseX = 0;


    // afficher_map_debug(map);

    while (programme)
    {

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());
        // printf("deltatime -> %f \n",deltaTime);

        // Modifier la position en y du rectangle source pour le déplacement vertical
        pacman_dstrect.y += rect_image.vitesseY *  rect_image.directionY ;
        pacman_dstrect.x += rect_image.vitesseX *  rect_image.directionX ;


        //animation pacman
        pacman_srcrect.x += 16; 
        if (pacman_srcrect.x > 49)
            pacman_srcrect.x = 0;

        

        stop_border_screen(pacman_dstrect, windowHauteur, windowLargeur, &rect_image);
        appuye_touche(event, &programme, &rect_image, &pacman_srcrect,&pacman_dstrect, &map);
        collision(&map, &pacman_dstrect,  &pacman_srcrect,  &rect_image);



        // printf("position X du pacman -> %d \n",pacman_dstrect.x );
        // printf("position Y du pacman -> %d \n",pacman_dstrect.y );
        // printf("Dans le tableau -> %c \n",   map.tableau[pacman_dstrect.y][pacman_dstrect.x]);

        // printf("centre largeur map -> %d\n",get_center_map_largeur(&map));
        // printf("centre hauteur map -> %d\n",get_center_map_hauteur(&map));

        // Effacer le rendu
        SDL_RenderClear(rendu);
        // // Afficher le rendu avec le rectangle source modifié
        SDL_RenderCopy(rendu, texture,  &pacman_srcrect,&pacman_dstrect);
        
        ajout_mur_map(&map, fenetre,rendu);
        ajout_structur_map(&map, fenetre,rendu);
        ajout_point_map(&map,fenetre,rendu);
        
        // // Afficher le rendu
        SDL_RenderPresent(rendu);
        
        // std::cout << "Delta Time: " << deltaTime << std::endl;
        // std::cout << "FPS: " << 60.0 - deltaTime << std::endl;
        SDL_Delay(1000.0f / (200.0 - deltaTime));
    }
 

//DESTRUCTION

    nettoyage_tableau(&map);
    nettoyage_seedmap(&map);
    nettoyage_pointMap(&map);


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

 
