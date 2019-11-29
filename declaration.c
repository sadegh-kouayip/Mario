#include "declaration.h"

int load_image_mario(SDL_Renderer *renderer, Mario *mario)
{
    SDL_Surface *picture = NULL;
    int error = 0;

    //MARIO DIRECTION VERS LE HAUT
    picture = IMG_Load("src/assets/image_pack1/mario_haut.gif");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        error--;
    }
    mario->haut = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);

    //MARIO DIRECTION VERS LE BAS
    picture = IMG_Load("src/assets/image_pack1/mario_bas.gif");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        error--;
    }
    mario->bas = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);

    //MARIO DIRECTION VERS LA DROITE
    picture = IMG_Load("src/assets/image_pack1/mario_droite.gif");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        error--;
    }
    mario->droite = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);

    //MARIO DIRECTION VERS LA GAUCHE
    picture = IMG_Load("src/assets/image_pack1/mario_gauche.gif");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        error--;
    }
    mario->gauche = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);

    return error;
}

void destroy_mario(Mario *mario)
{
    if (mario->haut != NULL)
        SDL_DestroyTexture(mario->haut);

    if (mario->bas != NULL)
        SDL_DestroyTexture(mario->bas);

    if (mario->droite != NULL)
        SDL_DestroyTexture(mario->droite);

    if (mario->gauche != NULL)
        SDL_DestroyTexture(mario->gauche);

    free(mario);
    mario = NULL;
}

Mario *new_joueur()
{
    Mario *mario = malloc(sizeof(*mario));
    return mario;
}