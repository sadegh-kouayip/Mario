#ifndef __CONSTANTE__H__
#define __CONSTANTE__H__

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define NB_BLOCS_LARGEUR 12
#define NB_BLOCS_HAUTEUR 12
#define TAILLE_BLOC 34

#define MAX_LEVEL 10

enum
{
    VIDE,
    MUR,
    CAISSE,
    CAISSE_OK,
    OBJECTIF,
    MARIO
};

#endif
