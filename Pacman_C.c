#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // Pour récupérer les touches du clavier

#define GRID_WIDTH 20
#define GRID_HEIGHT 15

// Les directions possibles pour Pac-Man
enum Direction { UP, DOWN, LEFT, RIGHT };

// Le personnage Pac-Man
struct PacMan {
    int x;
    int y;
    enum Direction direction;
};

// La grille de jeu
char grid[GRID_HEIGHT][GRID_WIDTH];

// Initialise la grille de jeu avec des points
void initGrid() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            grid[i][j] = '.';
        }
    }
}

// Affiche la grille de jeu avec Pac-Man
void display() {
    system("cls");  // Efface la console
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (i == pacman.y && j == pacman.x) {
                printf("C");  // Pac-Man
            } else {
                printf("%c", grid[i][j]);
            }
        }
        printf("\n");
    }
}

// Met à jour la position de Pac-Man en fonction de sa direction
void updatePosition() {
    switch (pacman.direction) {
        case UP:
            pacman.y--;
            break;
        case DOWN:
            pacman.y++;
            break;
        case LEFT:
            pacman.x--;
            break;
        case RIGHT:
            pacman.x++;
            break;
    }
    // Vérifie si Pac-Man sort de la grille
    if (pacman.x < 0) {
        pacman.x = GRID_WIDTH - 1;
    } else if (pacman.x >= GRID_WIDTH) {
        pacman.x = 0;
    }
    if (pacman.y < 0) {
        pacman.y = GRID_HEIGHT - 1;
    } else if (pacman.y >= GRID_HEIGHT) {
        pacman.y = 0;
    }
}

// Gère les événements de la boucle de jeu
void handleEvents() {
    if (kbhit()) {  // Si une touche est enfoncée
        switch (getch()) {
            case 'z':
            case 'Z':
            case 72:  // Flèche du haut
                pacman.direction = UP;
                break;
            case 's':
            case 'S':
            case 80:  // Flèche du bas
                pacman.direction = DOWN;
                break;
            case 'q':
            case 'Q':
            case 75:  // Flèche de gauche
                pacman.direction = LEFT;
                break;
            case 'd':
            case 'D':
            case 77:  // Flèche de droite
                pacman.direction = RIGHT;
                break;
            case 27:  // Touche Échap pour quitter le jeu
                exit(0);
        }
    }
}

int main() {
    // Initialise Pac-Man
    struct PacMan pacman = {GRID_WIDTH/2, GRID_HEIGHT/2, RIGHT};

    // Initialise la grille de jeu
    initGrid();

    // Boucle de jeu
    while (1) {
        handleEvents();
        updatePosition();
        display();
    }

    return 0;
}
