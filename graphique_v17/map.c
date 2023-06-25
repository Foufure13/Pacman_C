#include <SDL2/SDL_surface.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>   
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_test_images.h>


#include "map.h"
#include "mapPatern.c"

MAPS mapInstance = {0};
MAPS* map = &mapInstance;


void allocation_memoire_tableau(MAPS* map)
{
  // Allocation dynamique de la mémoire pour le tableau à deux dimensions
  map->tableau = malloc(map->y * sizeof(char*));
  for (int i = 0; i < map->y; i++) {
    map->tableau[i] = malloc(map->x * sizeof(char));
  }

  int nombre_structure_hauteur = ((map->y - 16) /16)/10 ;
  int nombre_structure_largeur = ((map->x - 16) /16)/5;

  map->seedmap = malloc(nombre_structure_hauteur * sizeof(int*));
  for (int i = 0; i < nombre_structure_hauteur; i++) {
    map->seedmap[i] = malloc(nombre_structure_largeur * sizeof(int));
  }

}


int get_center_map_largeur(MAPS* map){
  int centre_map_largeur = (((map->x - 16) /16)/5)/2;
  return centre_map_largeur -1;
}
int get_center_map_hauteur(MAPS* map){
  int centre_map_hauteur = (((map->y - 16) /16)/10)/2 ;
  return centre_map_hauteur ;
}


void ajout_mur_map(MAPS *maps, SDL_Renderer *rendu)
{

  SDL_Surface *map = SDL_LoadBMP("assets/pacman_background.bmp");
  SDL_Texture *texture2 = SDL_CreateTextureFromSurface(rendu,map); 


  SDL_Rect map_srcrect = { 0, 0, 4, 4 };
  SDL_Rect map_dstrect = { 300, 300, 16, 16 };

  if (map == NULL)
      printf("map NOOKAY MAPS");
  if (texture2 == NULL)
      printf( "map NOOKAY TEXTURE");
      
  SDL_FreeSurface(map);

  // if (SDL_RenderCopy(rendu, texture2, &map_srcrect, &map_dstrect) !=0)
  //     printf( "map NOOKAY AFFICHAGE TEXTURE");
  


  //remplissage du tableau(map) pixel par pixel par rien
  for (int i = 0; i < maps->y; i++) {
  for (int j = 0; j < maps->x; j++) {
      // maps->tableau[i][j] = ' ' ;

      //si on est au bord plafond ou sol de la map alors on rajoute des mur '-' 
      if (i == 0 || i == maps->y-16-16)
      {
        map_srcrect.x = 16;
        map_srcrect.y = 0;
        
        if (i == maps->y-16-16)
          map_srcrect.y = -2;

        map_dstrect.x = j;
        map_dstrect.y = i;
        SDL_RenderCopy(rendu, texture2, &map_srcrect, &map_dstrect);
        maps->tableau[i][j] = '-' ;
      }

       //si on est au bord droit ou gauche de la map alors on rajoute des mur '|' 
      if (j == 0 || j == maps->x-16)
      {
        map_srcrect.x = 0;
        map_srcrect.y = 16;
        map_dstrect.x = j;
        map_dstrect.y = i;
        SDL_RenderCopy(rendu, texture2, &map_srcrect, &map_dstrect);
        maps->tableau[i][j] = '|' ;
      }
  }
  }
  SDL_DestroyTexture(texture2);
}



  void seedmap(MAPS *maps)  
  {
    srand((unsigned)time(NULL));
    // system("clear"); //clear le terminal
    int nomre_structure = 21;
    int nombre_structure_largeur = ((maps->x - 16) /16)/5;
    int nombre_structure_hauteur = ((maps->y - 16) /16)/10 ;

    for(int z =0;z < nombre_structure_hauteur; z++) {
    for(int p =0;p < nombre_structure_largeur; p++) {
      //création de la ssed
      maps->seedmap[z][p] = rand()%nomre_structure;
      // printf(",%d",maps->seedmap[z][p]);
      }
      }
  }

void ajout_structur_map(MAPS *maps, SDL_Renderer *rendu)
{
  
  int nombre_structure_largeur = ((maps->x - 16) /16)/5;
  int nombre_structure_hauteur = ((maps->y - 16) /16)/10 ;

  
  // printf("struct largeur %d \n", nombre_structure_largeur);
  // printf("struct hauteur %d \n", nombre_structure_hauteur);
  
  SDL_Surface *map = SDL_LoadBMP("assets/strucure.bmp");
  SDL_Texture *texture2 = SDL_CreateTextureFromSurface(rendu,map); ;

  SDL_Rect map_dstrect = { 0, 0, 16, 16 };

  SDL_FreeSurface(map);

  int tableau2D[10][5];
  int emplacementStructX = 16, emplacementStructY =16;
  

  //parcour de chaque structure de la map a fin de les affiché et les ajouter au tableau final 

  // printf("\nStructure\n");
  for(int z =0;z < nombre_structure_hauteur; z++) {
    if (z != 0)
    {
    emplacementStructX =16;
    emplacementStructY += 10*16;
    } 
    //  printf("\nColonne %d-->",z);

  for(int p =0;p < nombre_structure_largeur; p++) {
    if (p != 0)
    {
    emplacementStructX += 5*16;
    } 
    // printf(">%d",maps->seedmap[z][p]);


    int (*tableau1D)[5];


    //création de la map structure par structure par rapport a la seedmap
    if ( (p != get_center_map_largeur(maps) && p != (get_center_map_largeur(maps)+1) ) || z != get_center_map_hauteur(maps))
    {
    switch(maps->seedmap[z][p]) {
        case 0:
            tableau1D = patern0();
            break;
        case 1:
            tableau1D = patern1();
            break;
        case 2:
            tableau1D = patern2();
            break;
        case 3:
            tableau1D = patern3();
            break;
        case 4:
            tableau1D = patern4();
            break;
        case 5:
            tableau1D = patern5();
            break;
        case 6:
            tableau1D = patern6();
            break;
        case 7:
            tableau1D = patern7();
            break;
        case 8:
            tableau1D = patern8();
            break;
        case 9:
            tableau1D = patern9();
            break;
        case 10:
            tableau1D = patern10();
            break;
        case 11:
            tableau1D = patern11();
            break;
        case 12:
            tableau1D = patern12();
            break;
        case 13:
            tableau1D = patern13();
            break;
        case 14:
            tableau1D = patern14();
            break;
        case 15:
            tableau1D = patern15();
            break;
        case 16:
            tableau1D = patern16();
            break;
        case 17:
            tableau1D = patern17();
            break;
        case 18:
            tableau1D = patern18();
            break;
        case 19:
            tableau1D = patern19();
            break;
        case 20:
            tableau1D = patern20();
            break;
    
    }

    // Copie les éléments du tableau 1D dans le tableau 2D
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 5; j++) {
            tableau2D[i][j] = tableau1D[i][j];
        }
    }

    //placement du spawn des fantom
    } else if ( p == get_center_map_largeur(maps))
      {
        tableau1D = fantom1();
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 5; j++) {
                tableau2D[i][j] = tableau1D[i][j];
            }
        }
    }else if ( p == get_center_map_largeur(maps) +1)
      {
        tableau1D = fantom2();
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 5; j++) {
                tableau2D[i][j] = tableau1D[i][j];
            }
        }

    }


    

    //On parcours la structure qui est a créer
    for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 5; j++) {
      
      //si on a un MUR = M alors on afficher une image de 16 pixel par 16 pixel a l'emplacement voulu
      if (tableau2D[i][j]== 'M')
      {
        map_dstrect.x = emplacementStructX+j*16;
        map_dstrect.y = emplacementStructY+i*16;
        SDL_Rect map_srcrect = { 0, 0, 4, 4 };
        SDL_RenderCopy(rendu, texture2, &map_srcrect, &map_dstrect);

        //on parcours chaque MUR pour les remplirs de M a fin de faire un mur plein et de bloquer tous passage
        for (int k = 0; k < 31; k++) {
        for (int o = 0; o < 31; o++) {
          maps->tableau[emplacementStructY+(i*16+k-15)][emplacementStructX + (j*16+o-15)] = 'M';
          }
        }
      }
    }
    }
    }
  }

  SDL_DestroyTexture(texture2);
}

void création_point_map(MAPS *maps)
{
   srand((unsigned)time(NULL));
   int shadow_number;
    // on parcours la map 
    for(int y =0; y < maps->y ; y+=16) {
      for(int x =0; x < maps->x; x+=16) {
        // on vérifie qu'on nest pas sur un mur extérieur de la map
        if (y > 16 && y < maps->y-48 && x > 16 && x < maps->x -32) {
          // on vérifi qu'on pas sur un mur de structure de la map
          shadow_number = rand()%105;
          if (shadow_number != 5) {
            if (maps->tableau[y][x] != 'M'){
                  maps->tableau[y+4][x+4] = 'x';
                  // printf("bug y -> %d / x -> %d\n",y,x);
                  // printf("vérification %c\n",maps->tableau[y+5][x+5]);

            } 
          } else if (maps->tableau[y][x] != 'M') {
              maps->tableau[y+4][x+4] = 'X';
          }

        }
      }
    }

}


void ajout_point_map(MAPS *maps, SDL_Renderer *rendu)
{

    SDL_Surface *point = SDL_LoadBMP("assets/structure2.bmp");

    SDL_Texture *point_texture = SDL_CreateTextureFromSurface(rendu,point);
    SDL_Texture *boost_texture = SDL_CreateTextureFromSurface(rendu,point); 
    SDL_Rect point_srcrect = { 5, 0, 4, 5 };
    SDL_Rect boost_srcrect = { 5, 0, 4, 5 };


    if (point == NULL)
        printf("map NOOKAY MAPS");
    if (point_texture == NULL)
        printf( "map NOOKAY TEXTURE");
        
    SDL_FreeSurface(point);

    // on parcours la map 
    for(int y =0; y < maps->y ; y++) {
      for(int x =0; x < maps->x; x++) {
        if (y > 16 && y < maps->y-48 && x > 16 && x < maps->x -16-16) {
          if (maps->tableau[y][x] == 'x') {
            SDL_Rect map_dstrect = { 0, 0, 4, 4 };
            map_dstrect.x = x+5;
            map_dstrect.y = y+5;
            SDL_RenderCopy(rendu, point_texture, &point_srcrect, &map_dstrect);
          } else if (maps->tableau[y][x] == 'X'){
            SDL_Rect map_dstrect = { 0, 0, 10,10 };
            map_dstrect.x = x+5;
            map_dstrect.y = y+5;
            SDL_RenderCopy(rendu, boost_texture, &boost_srcrect, &map_dstrect);            
          }
        }
      }
    }
  SDL_DestroyTexture(point_texture);
  SDL_DestroyTexture(boost_texture);
}









void afficher_map_debug(MAPS maps){
  // system("clear"); //clear le terminal
  //Affichage du tableau
  for (int i = 0; i < maps.y; i++) {
  for (int j = 0; j < maps.x; j++) {
      printf("%c ", maps.tableau[i][j]);
  }
  printf("\n");
  }
}


void nettoyage_tableau(MAPS *tableau)
{
  // Libération de la mémoire allouée pour le tableau
  for (int i = 0; i < tableau->y; i++) {
    free(tableau->tableau[i]);
  }
  free(tableau->tableau);

    int nombre_structure_hauteur = ((tableau->y - 16) /16)/10 ;
    // Libérer la mémoire allouée pour le tableau seedmap
    for (int i = 0; i < nombre_structure_hauteur; i++) {
      free(tableau->seedmap[i]);
    }
    free(tableau->seedmap);

}







