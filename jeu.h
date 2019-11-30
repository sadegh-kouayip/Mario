#ifndef __JEU__H__
#define __JEU__H__

#include "declaration.h"

#define NB_BLOCS_LARGEUR 12
#define NB_BLOCS_HAUTEUR 12

void clean_resources(SDL_Window *w, SDL_Renderer *r);
void clean_all_error_resources();

#endif