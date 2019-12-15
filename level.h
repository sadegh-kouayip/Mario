#ifndef __LEVEL__H__
#define __LEVEL__H__

#include "constante.h"

struct Level
{
    char l[NB_BLOCS_LARGEUR*NB_BLOCS_HAUTEUR+1];

}Level[MAX_LEVEL];

int chargement_niveau();
int niveau_jeux(unsigned int map[][NB_BLOCS_LARGEUR], int level, SDL_Rect *position_mario);
int save_level_fihier();
int save_modification(unsigned map[][NB_BLOCS_LARGEUR], int level);

#endif