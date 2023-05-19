#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_stdinc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>   
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_test_images.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


#include "keybinding_action.h"
#include "map.h"
#include "affichage.h"


// #define spawn_pacman_x 16
// #define spawn_pacman_y 16
// #define windows_settings_width 10
// #define windows_settings_height 5

void nettoyage_sdl(SDL_Window *fenetre, SDL_Renderer *renderer1 ) {

    SDL_RenderClear(renderer1);
    SDL_DestroyRenderer(renderer1);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

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

void initialisation_fenetre()     //Initialisation de la fenêtre
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR INIT SDL : %s !\n ",SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

int count_point_joueur (MAPS maps) {
    int nombre_point_restant =0;

    for (int y = 0 ; y < maps.y ; y ++) {
        for (int x =0 ; x < maps.x ; x++) {
            if (maps.tableau[y][x] == 'x') {
                nombre_point_restant+=1;
            }
        }
    }
    if (nombre_point_restant == 0) {
        return 0;
    } else {
        return 1;
    }

}

void active_fantom( MAPS map,Ghost *fantom) {
    fantom->fantom_dstrect.x = (map.x-32)/2;
    fantom->fantom_dstrect.y = (map.y-48)/2;
    fantom->actif =1;
}

void clear_menu(TTF_Font* font, SDL_Texture *texture_pacman_image,SDL_Texture *texture_ultimate, SDL_Texture *texture_pacman, SDL_Texture *texture_space, SDL_Renderer *renderer, SDL_Window *fenetre) {
    


    TTF_CloseFont(font);
    // SDL_FreeSurface(surface_space);
    // SDL_FreeSurface(surface_pacman);
    // SDL_FreeSurface(surface_ultimate);
    SDL_DestroyTexture(texture_pacman);
    SDL_DestroyTexture(texture_space);
    SDL_DestroyTexture(texture_pacman_image);
    SDL_DestroyTexture(texture_ultimate);

    SDL_RenderClear(renderer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
}




SDL_bool menu_game() {
    int windowLargeur =600, windowHauteur = 500;

    SDL_Window *fenetre=SDL_CreateWindow("Menu Pacman",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowLargeur, windowHauteur, 0);
    SDL_Renderer *renderer=SDL_CreateRenderer(fenetre, -1, 0);

    SDL_bool programme=SDL_TRUE, choice = SDL_FALSE ;
    SDL_Event event;

    

    SDL_Surface *image_pacman = SDL_LoadBMP("assets/menu.bmp");
    SDL_Texture *texture_pacman_image = SDL_CreateTextureFromSurface(renderer,image_pacman); 
    SDL_FreeSurface(image_pacman);

    SDL_Rect map_srcrect = { 16, 16, 2600, 2000 };
    SDL_Rect map_dstrect = { (windowLargeur/2)-150, 100, 250, 250 };


  SDL_Color textColor = { 255, 255, 255 }; // couleur blanche

  if (TTF_Init() == -1) {
    printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
  }

  TTF_Font* font = TTF_OpenFont("font/DS-DIGI.TTF", 24);
  if (font == NULL) {
    printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
  }


  SDL_Surface* surface_pacman = TTF_RenderText_Solid(font, "Pacman", textColor);
  SDL_Surface* surface_ultimate = TTF_RenderText_Solid(font, "Ultimate", textColor);
  SDL_Surface* surface_space = TTF_RenderText_Solid(font, "Appuyer sur Espace pour commencer", textColor);

  SDL_Texture* texture_ultimate = SDL_CreateTextureFromSurface(renderer, surface_ultimate);
  SDL_Texture* texture_pacman = SDL_CreateTextureFromSurface(renderer, surface_pacman);
  SDL_Texture* texture_space = SDL_CreateTextureFromSurface(renderer, surface_space);
    SDL_FreeSurface(surface_pacman);
    SDL_FreeSurface(surface_ultimate);
    SDL_FreeSurface(surface_space);


  SDL_Rect dstrect_ultimate = { 100, 50, 400, 40 };
  SDL_Rect dstrect_pacman = { 100, 10, 400, 40 };
  SDL_Rect dstrect_space = { 50, windowHauteur-100, 500, 40 };



    //INITIALISATION
    initialisation_fenetre();

    while (programme) {

        int choice =0;
        while (SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        programme=SDL_FALSE;
                        choice=SDL_FALSE;
                    break;
                    case SDLK_SPACE:
                        programme=SDL_FALSE;
                        choice=SDL_TRUE;
                         clear_menu(font,texture_ultimate, texture_pacman_image, texture_pacman, texture_space, renderer, fenetre);
                        return choice;
                    break;
                    default:                
                        continue;
                    }
                    case SDL_QUIT:
                        programme=SDL_FALSE;
                        choice=SDL_FALSE;
                    break;
                    default:
                        break;
                }
            }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture_pacman, NULL, &dstrect_pacman);
        SDL_RenderCopy(renderer, texture_space, NULL, &dstrect_space);
        SDL_RenderCopy(renderer, texture_pacman_image, &map_srcrect, &map_dstrect);
        SDL_RenderCopy(renderer, texture_ultimate, NULL, &dstrect_ultimate);

        SDL_RenderPresent(renderer);
        
    }

    clear_menu(font,texture_ultimate, texture_pacman_image, texture_pacman, texture_space, renderer, fenetre);
    return choice;
}



int main(int argc, char** argv)
{
    int game_type = 1;

    for (int niveau = 1; niveau < 4; niveau++) {

    SDL_bool programme = SDL_TRUE;
    if (niveau == 1) {
        programme = menu_game();
    if (programme == SDL_FALSE) {
        return 1;
    }
    }


    int windows_settings_width = 6;
    int windows_settings_height = 3;

    if (game_type == 1) { 
        if (niveau == 2) {
            windows_settings_width = 8;
            windows_settings_height = 3;       
        } else if (niveau == 3) {
            windows_settings_width = 8;
            windows_settings_height = 5; 
        }
    }

    MAPS map;
    map.gameover=0;

    int windowLargeur = map.x = 32 + (windows_settings_width * 16 *5);
    int windowHauteur = map.y = 16 + 32 + (windows_settings_height * 16 * 10 );

    int clock_fantome =1;

    allocation_memoire_tableau(&map);
    seedmap(&map);

    SDL_Window *fenetre=SDL_CreateWindow("Pacman",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowLargeur, windowHauteur, 0);
    SDL_Renderer *rendu=SDL_CreateRenderer(fenetre, -1, 0);
    

    SDL_Event event;
    
    Uint32 ticks = SDL_GetTicks();
    Uint32 seconds = ticks / 1000 ;
    // Uint32 sprite = seconds % 8;

    SDL_Rect pacman_srcrect = { 16, 16, 15, 15 };
    SDL_Rect pacman_dstrect = { (map.x-32)/2-78, ((map.y-48)/2-78), 15, 15 };


    Ghost fantomRed = {
    {0, 0, 15, 15},  // initialisation de fantom_srcrect
    { (map.x-32)/2, (map.y-48)/2, 15, 15 },  // initialisation de fantom_dstrect   
    0.0, 0.0, //vitesse
    0, 0,     //direction
    0, 0, 0, 0, //vision
    1,1}; //Gtype
    
    Ghost fantomPink = {
    {0, 16, 15, 15},  // initialisation de fantom_srcrect
    { (map.x-32)/2, (map.y-48)/2, 15, 15 },  // initialisation de fantom_dstrect   
    0.0, 0.0, //vitesse
    0, 0,     //direction
    0, 0, 0, 0, //vision
    2,1}; //Gtype

    Ghost fantomBlue = {
    {0, 32, 15, 15},  // initialisation de fantom_srcrect
    { (map.x-32)/2, (map.y-48)/2, 15, 15 },  // initialisation de fantom_dstrect   
    0.0, 0.0, //vitesse
    0, 0,     //direction
    0, 0, 0, 0, //vision
    3,1}; //Gtype

    Ghost fantomOrange = {
    {0, 48, 15, 15},  // initialisation de fantom_srcrect
    { (map.x-32)/2, (map.y-48)/2, 15, 15 },  // initialisation de fantom_dstrect   
    0.0, 0.0, //vitesse
    0, 0,     //direction
    0, 0, 0, 0, //vision
    4,1}; //Gtype

    Ghost fantomRedSpe = {
    {0, 0, 15, 15},  // initialisation de fantom_srcrect
    { 0, 0, 15, 15 },  // initialisation de fantom_dstrect   
    0.0, 0.0, //vitesse
    0, 0,     //direction
    0, 0, 0, 0, //vision
    0,0}; //Gtype
    
    Ghost fantomPinkSpe = {
    {0, 16, 15, 15},  // initialisation de fantom_srcrect
    { 0, 0, 15, 15 },  // initialisation de fantom_dstrect   
    0.0, 0.0, //vitesse
    0, 0,     //direction
    0, 0, 0, 0, //vision
    0,0}; //Gtype

    Ghost fantomBlueSpe = {
    {0, 32, 15, 15},  // initialisation de fantom_srcrect
    { 0, 0, 15, 15 },  // initialisation de fantom_dstrect   
    0.0, 0.0, //vitesse
    0, 0,     //direction
    0, 0, 0, 0, //vision
    0,0}; //Gtype

    Ghost fantomOrangeSpe = {
    {0, 48, 15, 15},  // initialisation de fantom_srcrect
    { 0, 0, 15, 15 },  // initialisation de fantom_dstrect   
    0.0, 0.0, //vitesse
    0, 0,     //direction
    0, 0, 0, 0, //vision
    0,0}; //Gtype

    clock_t debut, fin, timer, invicible_timer, game_timer;
    double temps_ecoule, compteur_invicible;
    debut = timer = clock();  // enregistrer l'heure de début

    
  // system("clear"); //clear le terminal

//INITIALISATION
initialisation_fenetre();


    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    Deplacement rect_image;
    rect_image.directionY = 0;
    rect_image.vitesseY = 0;
    rect_image.directionX = 0;
    rect_image.vitesseX = 0;
    rect_image.point_joueur =0;
    rect_image.vie = 3;
    rect_image.invincible =0;

    création_point_map(&map);
    // afficher_map_debug(map);
    int game_start = 0;
    reset_game (&map, &pacman_dstrect,  &fantomRed,  &fantomPink,  &fantomBlue,  &fantomOrange,  &rect_image, &game_start);


    game_timer = clock();
    while (programme )
    {
        fin = clock();  // enregistrer l'heure de fin
        temps_ecoule = ((double) (fin - debut)) / CLOCKS_PER_SEC;
        if ( rect_image.invincible == 1) {
            invicible_timer = clock();
            pacman_srcrect.x =-16;
            pacman_srcrect.y = 0;
            compteur_invicible = ((double) (invicible_timer - game_timer)) / CLOCKS_PER_SEC; 
            if (compteur_invicible >= 1) {
                rect_image.invincible = 0;
            }
        }


        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());
        // printf("deltatime -> %f \n",deltaTime);
        

        // stop_border_screen(pacman_dstrect, windowHauteur, windowLargeur, &rect_image);
        appuye_touche(event,&niveau, &programme, &rect_image, &pacman_srcrect,&pacman_dstrect, &map, &fantomRed, &fantomPink, &fantomBlue, &fantomOrange,&game_start);
        if (map.gameover == 0) {

            collision(&map, &pacman_dstrect,    &rect_image);
            collision_point(&map, &pacman_dstrect,    &rect_image);

        if (game_start ==1 && rect_image.invincible == 0) {
            game_timer = clock();
            if (1 == collision_fantom_pacman(&map, &pacman_dstrect,  &rect_image, fantomRed,  fantomPink,  fantomBlue, fantomOrange)) {
                hit_reset_game (&map, &pacman_dstrect,&game_start,  &fantomRed,  &fantomPink,  &fantomBlue,  &fantomOrange,&fantomRedSpe, &fantomPinkSpe, &fantomBlueSpe ,&fantomOrangeSpe);

            }
            if (1 == collision_fantom_pacman(&map, &pacman_dstrect,  &rect_image, fantomRedSpe,  fantomPinkSpe,  fantomBlueSpe, fantomOrangeSpe)) {
                hit_reset_game (&map, &pacman_dstrect,&game_start,  &fantomRed,  &fantomPink,  &fantomBlue,  &fantomOrange,&fantomRedSpe, &fantomPinkSpe, &fantomBlueSpe ,&fantomOrangeSpe);
            }
        }


        

        // printf("temps_ecoule : %f\n",temps_ecoule);
        // printf("vitesse %f et direction %d X fantom\n", fantomRed.vitesseX, fantomRed.directionX);
        // printf("vitesse %f et direction %d Y fantom\n", fantomRed.vitesseY, fantomRed.directionY);

        // printf("map map Y %d, map X %d \n", map.y, map.x);

        
        if (temps_ecoule >= 0.22 && game_start == 1) {
            
            fantom_deplacement(&map, &fantomRed, pacman_dstrect);
            fantom_deplacement(&map, &fantomPink, pacman_dstrect);
            fantom_deplacement(&map, &fantomBlue, pacman_dstrect);
            fantom_deplacement(&map, &fantomOrange, pacman_dstrect);



            if (rect_image.point_joueur > 50 && niveau > 2) {
                if (fantomRedSpe.actif == 0) {
                    active_fantom( map,&fantomRedSpe);
                }
                fantom_deplacement(&map, &fantomRedSpe, pacman_dstrect);
            }
            if (rect_image.point_joueur > 100 && niveau > 1) {
                if (fantomPinkSpe.actif == 0) {
                    active_fantom( map,&fantomPinkSpe);
                }
                fantom_deplacement(&map, &fantomPinkSpe, pacman_dstrect);
            }
            if (rect_image.point_joueur > 150) {
                if (fantomBlueSpe.actif == 0) {
                    active_fantom( map,&fantomBlueSpe);
                }
                fantom_deplacement(&map, &fantomBlueSpe, pacman_dstrect);
            }
            if (rect_image.point_joueur > 200) {
                if (fantomOrangeSpe.actif == 0) {
                    active_fantom( map,&fantomOrangeSpe);
                }
                fantom_deplacement(&map, &fantomOrangeSpe, pacman_dstrect);
            }


            debut = clock();
            }
        }
        // printf("Point du joueur : %d \n",rect_image.point_joueur);
        // printf("position X du pacman -> %d \n",pacman_dstrect.x );
        // printf("position Y du pacman -> %d \n",pacman_dstrect.y );
        // printf("Dans le tableau -> %c \n",   map.tableau[pacman_dstrect.y][pacman_dstrect.x]);

        // printf("centre largeur map -> %d\n",get_center_map_largeur(&map));
        // printf("centre hauteur map -> %d\n",get_center_map_hauteur(&map));

        // Effacer le rendu
        SDL_RenderClear(rendu);

        // // Afficher le rendu avec le rectangle source modifié
        // SDL_RenderCopy(rendu, texture,  &pacman_srcrect,&pacman_dstrect);
        


        ajout_mur_map(&map,rendu);
        if ( map.gameover == 0) {
            ajout_structur_map(&map,rendu);
            ajout_point_map(&map,rendu);
        }


        Affichage_niveau (&map, rendu, niveau);
        Affichage_score(&map, rendu, rect_image);
        Affichage_vie (&map, rendu, rect_image);
        Affichage_pacman (rendu,  rect_image, &pacman_srcrect, &pacman_dstrect);

        if ((temps_ecoule >= 1 || game_start ==1 && map.gameover == 0)) {
            Affichage_fantom (&map,rendu,  &fantomRed, pacman_dstrect);
            Affichage_fantom (&map,rendu,  &fantomPink, pacman_dstrect);
            Affichage_fantom (&map,rendu,  &fantomBlue, pacman_dstrect);
            Affichage_fantom (&map,rendu,  &fantomOrange, pacman_dstrect);
            game_start =1;
        }
        if (rect_image.point_joueur > 50 && niveau > 2) {
             Affichage_fantom (&map,rendu,  &fantomRedSpe, pacman_dstrect);
        }
        if (rect_image.point_joueur > 100 && niveau > 1) {
             Affichage_fantom (&map,rendu,  &fantomPinkSpe, pacman_dstrect);
        }
        if (rect_image.point_joueur > 150) {
             Affichage_fantom (&map,rendu,  &fantomBlueSpe, pacman_dstrect);
        }
        if (rect_image.point_joueur > 200) {
             Affichage_fantom (&map,rendu,  &fantomOrangeSpe, pacman_dstrect);
        }


        if ( rect_image.vie == 0) {
            map.gameover =1;
            // niveau=666;
            // programme =SDL_FALSE;
            game_over_pacman (&map, rendu, niveau);
            // return 0;
        }

        // // Afficher le rendu
        SDL_RenderPresent(rendu);
        
        // std::cout << "Delta Time: " << deltaTime << std::endl;
        // std::cout << "FPS: " << 60.0 - deltaTime << std::endl;
        SDL_Delay(1000.0f / (200.0 - deltaTime));
        
        

        if (0 == count_point_joueur (map)) {
            programme = SDL_FALSE ;
        }


    }
 

//DESTRUCTION



    nettoyage_tableau(&map);

    // SDL_RenderClear(rendu);
    // SDL_DestroyRenderer(rendu);
    // SDL_DestroyWindow(fenetre);
    // SDL_Quit();
    nettoyage_sdl(fenetre, rendu);

    }
    return EXIT_SUCCESS;
}

 
