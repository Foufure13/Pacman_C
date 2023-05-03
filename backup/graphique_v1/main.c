#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

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

//INITIALISATION

   

    //Initialisation de la fenêtre
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR INIT SDL : %s !\n ",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Création de la fenêtre
    fen=SDL_CreateWindow("Ma première fenêtre",
                          SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED,
                          800,
                          800,
                          0);

    //vérification si la fênetre a pas d'erreur
    if (fen == NULL)
    {
        SDL_Log("ERREUR OUVERTURE FENETRE : %s!\n",SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    //création d'un rendu
    rendu = SDL_CreateRenderer(fen,
                                -1,
                                SDL_RENDERER_SOFTWARE); 

    // vérifier que le rendu a pas derreur
    if (rendu == NULL)  
    {
        SDL_Log("ERREUR INIT rendu : %s !\n ",SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }


    SDL_RenderPresent(rendu); // afficher notre rendu a la fenêtre


    SDL_Delay(2000);

    if (SDL_RenderClear(rendu)!=0)
        {GestErreur("Rendu non effacé");}
        

    SDL_DestroyRenderer(rendu);    //détruire le rendu
    SDL_DestroyWindow(fen);     //Détruire la fenêtre
    //Fermeture de la fenêtre
    SDL_Quit();
    return EXIT_SUCCESS;
}

 
