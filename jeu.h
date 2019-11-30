#ifndef __JEU__H__
#define __JEU__H__

#include "declaration.h"

void clean_resources(SDL_Window *w, SDL_Renderer *r);
void clean_all_error_resources(Mario *mario, Objets *objets, SDL_Window *window, SDL_Renderer *renderer);

#endif