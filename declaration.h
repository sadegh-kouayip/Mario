#ifndef __DECLARATION__H__
#define __DECLARATION__H__

#include "constante.h"

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
void deplacer_mario(unsigned int map[][NB_BLOCS_HAUTEUR], SDL_Rect *position, Direction_Mario direction);

//Objets
int load_image_objets(SDL_Renderer *renderer, Objets *objets);
void destroy_objets(Objets *objets);
void deplacer_caisse(unsigned int *position_un, unsigned int *position_deux);

void clean_package(Mario *mario, Objets *objets);

#endif