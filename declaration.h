#ifndef __DECLARATION__H__
#define __DECLARATION__H__

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

#define TAILLE_BLOC 34

//DECLARATION MARIO
typedef struct Mario
{
    SDL_Texture *haut;
    SDL_Texture *bas;
    SDL_Texture *droite;
    SDL_Texture *gauche;

} Mario;

typedef enum Direction
{
    MARIO_HAUT,
    MARIO_BAS,
    MARIO_DROITE,
    MARIO_GAUCHE

} Direction_Mario;

//DECLARATION OBJECTS
typedef struct Objets
{
    SDL_Texture *mur;
    SDL_Texture *caisse_ok;
    SDL_Texture *caisse;
    SDL_Texture *objectif;

} Objets;

enum
{
    VIDE,
    MUR,
    CAISSE,
    CAISSE_OK,
    OBJECTIF,
    MARIO
};

/*
  ****CREATION DU MODEL****
*/

//Mario
Mario *new_joueur();

//Objets
Objets *new_Objets();

/*
  ****FONCTION DE MANIPULATION DU MODEL****
*/

//Mario
int load_image_mario(SDL_Renderer *renderer, Mario *mario);
void destroy_mario(Mario *mario);

//Objets
int load_image_objets(SDL_Renderer *renderer, Objets *objets);
void destroy_objets(Objets *objets);

#endif