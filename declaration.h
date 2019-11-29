#ifndef __DECLARATION__H__
#define __DECLARATION__H__

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

#define TAILLE_BLOC 34

typedef struct Mario
{
    SDL_Texture *haut;
    SDL_Texture *bas;
    SDL_Texture *droite;
    SDL_Texture *gauche;

} Mario;

typedef struct Object
{
    SDL_Texture *haut;
    SDL_Texture *bas;
    SDL_Texture *gauche;
    SDL_Texture *droit;

} Object;

Mario *new_joueur();
int load_image_mario(SDL_Renderer *renderer, Mario *mario);
void destroy_mario(Mario *mario);

#endif