/*
>gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
*/

#include "jeu.h"

int main(int argc, char **argv)
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *mario_actuel = NULL;
    SDL_Rect position = {0, 0, TAILLE_BLOC, TAILLE_BLOC};

    //PACKAGE MARIO
    Mario *mario = new_joueur();
    if (mario == NULL)
    {
        printf("Probleme d'alocation memoire");
        exit(EXIT_FAILURE);
    }

    //Lancement SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //Création fenêtre
    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //CHARGEMENT DES TEXTURE D'IMAGE
    if (load_image_mario(renderer, mario) < 0)
    {
        destroy_mario(mario);
        clean_resources(window, renderer);
        exit(EXIT_FAILURE);
    }
    mario_actuel = mario->droite;
    SDL_bool isOpen = SDL_TRUE;
    SDL_Event event;
    while (isOpen)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isOpen = SDL_FALSE;
                break;
            case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                mario_actuel = mario->haut;
                position.y-= TAILLE_BLOC;
                break;
            case SDLK_DOWN:
                mario_actuel = mario->bas;
                position.y+= TAILLE_BLOC;
                break;
            case SDLK_RIGHT:
                mario_actuel = mario->droite;
                position.x+= TAILLE_BLOC;
                break;
            case SDLK_LEFT:
                mario_actuel = mario->gauche;
                position.x-= TAILLE_BLOC;
                break;
            default:
                break;
            }
            break;
            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        if (SDL_QueryTexture(mario_actuel, NULL, NULL, &position.w, &position.h) != 0)
        {
            SDL_Log("ERREUR > %s\n", SDL_GetError());
            destroy_mario(mario);
            clean_resources(window, renderer);
            exit(EXIT_FAILURE);
        }

        if (SDL_RenderCopy(renderer, mario_actuel, NULL, &position) != 0)
        {
            SDL_Log("ERREUR > %s\n", SDL_GetError());
            destroy_mario(mario);
            clean_resources(window, renderer);
            exit(EXIT_FAILURE);
        }

        SDL_RenderPresent(renderer);
    }

    destroy_mario(mario);
    clean_resources(window, renderer);

    return EXIT_SUCCESS;
}

void clean_resources(SDL_Window *w, SDL_Renderer *r)
{
    if (r != NULL)
        SDL_DestroyRenderer(r);

    if (w != NULL)
        SDL_DestroyWindow(w);

    SDL_Quit();
}