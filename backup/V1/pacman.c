#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MapPacman {
  char **tableau;
  int x, y;
} MAPS;

int menu(){
    int choice ;
    printf("Hello dans ce PACMAN --> Révolutionnaire \nLancer une partie entrée 1 : ");
    scanf("%d", &choice);
    return choice;
}

int main() {
    // if (menu() != 1){
    //     return 1;
    //     }
    // printf("READY ??? \n");


    int taille_Axe_X = 20; 
    int taille_Axe_Y = 10;

    char Tableau[taille_Axe_Y][taille_Axe_X];


    printf("%c\n", Tableau[0][0]);


    for (int i = 0; i < taille_Axe_Y; i++) {
    for (int j = 0; j < taille_Axe_X; j++) {
         Tableau[i][j] = 'x';   


         if (i == 0 || i == taille_Axe_Y-1) { //mur du haut et du bas du tableau
            Tableau[i][j] = '-';
         }
         if (j == 0 || j == taille_Axe_X-1) { //mur du haut et du bas du tableau
            Tableau[i][j] = '|';
         }         
    }
    }
    Tableau[2][3] = 'C';









    for (int i = 0; i < taille_Axe_Y; i++) {
    for (int j = 0; j < taille_Axe_X; j++) {
        printf("%c ", Tableau[i][j]);
    }
    printf("\n");
    }


    return 0;
}