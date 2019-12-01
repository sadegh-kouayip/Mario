/*
>gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
*/

#include "jeu.h"

#define WINDOW_WIDTH 408
#define WINDOW_HEIGHT 408

void clean_resources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);

int main(int argc, char **argv)
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *picture = NULL;
    SDL_Texture *menu = NULL;
    SDL_Rect dest_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    SDL_bool continuer = SDL_TRUE;

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
        clean_resources(window, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    picture = IMG_Load("src/assets/menu/menu.PNG");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_resources(window, renderer, NULL);
        exit(EXIT_FAILURE);
    }

    menu = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);
    if (menu == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_resources(window, renderer, NULL);
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
            case SDLK_SPACE:
                if(play_games(window, renderer) != EXIT_SUCCESS)
                    printf("ERREUR > vérifier vos repertoires et images\n");
                break;
            }
            break;
        }

        if(SDL_SetRenderTarget(renderer, NULL) != 0)
        {
            SDL_Log("ERREUR color> %s\n", SDL_GetError());
            clean_resources(window, renderer, menu);
            exit(EXIT_FAILURE);
        }

        if (SDL_RenderCopy(renderer, menu, NULL, &dest_rect) != 0)
        {
            SDL_Log("ERREUR color> %s\n", SDL_GetError());
            clean_resources(window, renderer, menu);
            exit(EXIT_FAILURE);
        }

        SDL_RenderPresent(renderer);
    }

    clean_resources(window, renderer, menu);

    return EXIT_SUCCESS;
}

void clean_resources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t)
{
    if (t != NULL)
        SDL_DestroyTexture(t);
    if (r != NULL)
        SDL_DestroyRenderer(r);

    if (w != NULL)
        SDL_DestroyWindow(w);

    SDL_Quit();
}