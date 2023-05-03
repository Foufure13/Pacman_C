#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>


typedef struct MapPacman {
  char **tableau;
  int x, y;
  int pacman[2];
  int *pacman_x, *pacman_y;
} MAPS;

void allocation_memoire_tableau(MAPS* map)
{
  // Allocation dynamique de la mémoire pour le tableau à deux dimensions
  map->tableau = malloc(map->y * sizeof(char*));
  for (int i = 0; i < map->y; i++) {
    map->tableau[i] = malloc(map->x * sizeof(char));
  }
}

void ajout_mur_map(MAPS maps)
{

  for (int i = 0; i < maps.y; i++) {
  for (int j = 0; j < maps.x; j++) {
      maps.tableau[i][j] = 'x' ;
      if (i == 0 || i == maps.y-1)
      {
        maps.tableau[i][j] = '-' ;
      }
      if (j == 0 || j == maps.x-1)
      {
        maps.tableau[i][j] = '|' ;
      }
  }
  }
}


void affiche_map(MAPS tableau)
{
  system("clear"); //clear le terminal
  //Affichage du tableau
  for (int i = 0; i < tableau.y; i++) {
  for (int j = 0; j < tableau.x; j++) {
      printf("%c ", tableau.tableau[i][j]);
  }
  printf("\n");
  }
}

void affiche_map_ncurses(MAPS tableau) {
    int row, col;
    getmaxyx(stdscr, row, col);
    for (int i = 0; i < tableau.y; i++) {
        for (int j = 0; j < tableau.x; j++) {
            mvprintw(row/2 - tableau.y/2 + i, col/2 - tableau.x + j*2, "%c ", tableau.tableau[i][j]);
        }
    }
    mvprintw(row-1, 0, "Appuyer sur 'a' pour quitter");
    refresh();
}


void nettoyage_tableau(MAPS tableau)
{
  // Libération de la mémoire allouée pour le tableau
  for (int i = 0; i < tableau.y; i++) {
    free(tableau.tableau[i]);
  }
  free(tableau.tableau);
}

void pacman_deplacement(MAPS* map,int move_x, int move_y) {
  char Pacman= 'C';

  if (move_x == 1)
  { Pacman = '<'; map->tableau[map->pacman[0]][map->pacman[1]] = Pacman;
  } else if (move_x == -1)
  { Pacman = '>'; map->tableau[map->pacman[0]][map->pacman[1]] = Pacman;
  }

  if (move_y == 1)
  { Pacman = '^'; map->tableau[map->pacman[0]][map->pacman[1]] = Pacman;
  } else if (move_y == -1)
  { Pacman = 'v'; map->tableau[map->pacman[0]][map->pacman[1]] = Pacman;
  }
  
  if (map->pacman[1]+move_x != 0 && map->pacman[0]+move_y != 0 && map->pacman[0]+move_y != map->y-1 && map->pacman[1]+move_x != map->x-1)
  {
  map->tableau[map->pacman[0]][map->pacman[1]] = ' ';
  map->pacman[1]+=move_x;
  map->pacman[0]+=move_y;
  map->tableau[map->pacman[0]][map->pacman[1]] = Pacman; 
  }

}


int main() {
    int jeu =1;


  MAPS map;
  map.x = 20;
  map.y = 10;
  map.pacman[0] = 2;
  map.pacman[1] = 3;







  allocation_memoire_tableau(&map);
  ajout_mur_map(map);

  system("clear"); //clear le terminal
  printf(" ____  \n");
  printf("|  _ \\ __ _  ___ _ __ ___   __ _ _ __   \n");
  printf("| |_) / _` |/ __| '_ ` _ \\ / _` | '_ \\ \n");
  printf("|  __/ (_| | (__| | | | | | (_| | | | |  \n");
  printf("|_|   \\__,_|\\___|_| |_| |_|\\__,_|_| |_|  \n\n");
  printf(" Appuyer sur une Touche Pour Commencer  \n");


  map.tableau[map.pacman[0]][map.pacman[1]] = 'C'; //spawn du pacman
  char touche;
  initscr();// Ouvrire ncurses
  while (jeu ==1) {
    touche = getchar();
    if (touche == 'a') jeu = 0;
    else {
      if (touche == 'z')pacman_deplacement(&map, 0, -1);
      
      if (touche == 'q')pacman_deplacement(&map, -1, 0);
      
      if (touche == 'd')pacman_deplacement(&map, 1, 0);
      
      if (touche == 's')pacman_deplacement(&map, 0, 1);
      
    }
    
    affiche_map_ncurses(map);
  }
  endwin();// Fermer ncurses




  nettoyage_tableau(map);
  

  return 0;
}