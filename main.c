#include "jeu.h"
#include "level.h"
#include "edition.h"

#define WINDOW_WIDTH 408
#define WINDOW_HEIGHT 408

void clean_resources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t, SDL_Texture *v);

int main(int argc, char **argv)
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *picture = NULL, *icon = NULL;
    SDL_Texture *menu = NULL, *winner;
    SDL_Rect dest_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    SDL_bool continuer = SDL_TRUE;

    //PREPARATION DES DIFFERENTS NIVEAU
    if (chargement_niveau() != EXIT_SUCCESS)
    {
        printf("Error chargement de niveau");
        SDL_Delay(3000);
        exit(EXIT_FAILURE);
    }

    //Lancement SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //Création fenêtre
    window = SDL_CreateWindow("Mario Sokoban", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_resources(window, NULL, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    //ICON DU JEU
    icon = IMG_Load("assets/icon/peticone.PNG");
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    //MENU DE DEMARRAGE
    picture = IMG_Load("assets/menu/menu.PNG");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_resources(window, renderer, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    menu = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);
    if (menu == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_resources(window, renderer, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    //WINNER FELICITATION
    picture = IMG_Load("assets/menu/fin.PNG");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_resources(window, renderer, menu, NULL);
        exit(EXIT_FAILURE);
    }

    winner = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);
    if (winner == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_resources(window, renderer, menu, NULL);
        exit(EXIT_FAILURE);
    }

    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = SDL_FALSE;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_1:
                switch (play_games(window, renderer))
                {
                case EXIT_WINNER:
                    printf("Felicitation vous avez delivrer le jeux\n");
                    if (SDL_RenderCopy(renderer, winner, NULL, &dest_rect) != 0)
                    {
                        SDL_Log("ERREUR color> %s\n", SDL_GetError());
                        clean_resources(window, renderer, menu, winner);
                        exit(EXIT_FAILURE);
                    }
                    SDL_RenderPresent(renderer);
                    SDL_Delay(6000);
                    break;
                case EXIT_SUCCESS:
                    printf("Vous n'avez pas fini l'aventure continuer ou modifier les niveaux pour plus de dificulter\n");
                    break;
                default:
                    printf("ERREUR > Le jeu a rencontrer une ou plusieurs erreurs\n");
                    break;
                }
                break;
            case SDLK_2:
                if (edit_game(window, renderer) != EXIT_SUCCESS)
                    printf("ERREUR > Le jeu a rencontrer une ou plusieurs erreurs\n");
                break;
            }
            break;
        }

        if (SDL_RenderCopy(renderer, menu, NULL, &dest_rect) != 0)
        {
            SDL_Log("ERREUR color> %s\n", SDL_GetError());
            clean_resources(window, renderer, menu, winner);
            exit(EXIT_FAILURE);
        }

        SDL_RenderPresent(renderer);
    }

    clean_resources(window, renderer, menu, winner);

    return EXIT_SUCCESS;
}

void clean_resources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t, SDL_Texture *v)
{
    if (v != NULL)
        SDL_DestroyTexture(v);
    if (t != NULL)
        SDL_DestroyTexture(t);
    if (r != NULL)
        SDL_DestroyRenderer(r);

    if (w != NULL)
        SDL_DestroyWindow(w);

    SDL_Quit();
}