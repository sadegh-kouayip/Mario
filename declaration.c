#include "declaration.h"

/*
    MARIO
*/

Mario *new_joueur()
{
    Mario *mario = malloc(sizeof(*mario));
    return mario;
}

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

/*
    OBJETS
*/

Objets *new_Objets()
{
    Objets *objets = malloc(sizeof(*objets));
    return objets;
}

int load_image_objets(SDL_Renderer *renderer, Objets *objets)
{
    SDL_Surface *picture = NULL;
    int error = 0;

    //OBJET MUR
    picture = IMG_Load("src/assets/image_pack1/mur.png");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        error--;
    }
    objets->mur = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);

    //OBJET CAISSE
    picture = IMG_Load("src/assets/image_pack1/caisse.png");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        error--;
    }
    objets->caisse = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);

    //OBJET CAISSE OK
    picture = IMG_Load("src/assets/image_pack1/caisse_ok.png");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        error--;
    }
    objets->caisse_ok = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);

    //OBJECT OBJECTIF
    picture = IMG_Load("src/assets/image_pack1/objectif.png");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        error--;
    }
    objets->objectif = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);

    return error;
}

void destroy_objets(Objets *objets)
{
    if (objets->mur != NULL)
        SDL_DestroyTexture(objets->mur);

    if (objets->caisse != NULL)
        SDL_DestroyTexture(objets->caisse);

    if (objets->caisse_ok != NULL)
        SDL_DestroyTexture(objets->caisse_ok);

    if (objets->objectif != NULL)
        SDL_DestroyTexture(objets->objectif);

    free(objets);
    objets = NULL;
}