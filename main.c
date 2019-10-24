/*
main.c
------------ 

Rôle : contient la fonction main du programme 
*/


#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "jeu.h"
#include "constantes.h"


int main(int argc, char *argv[])
{  
   
    SDL_Window* fenetre;
    SDL_Event evenements;
    bool terminer = false;
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    
    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
    
    if(fenetre == NULL) 
    {
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
        
    while(!terminer){
        while( SDL_PollEvent( &evenements ) )
            switch(evenements.type)
            {
                case SDL_QUIT:
                    terminer = true; 
                break;
                case SDL_KEYDOWN:
                    switch(evenements.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            terminer = true;
                        break;
            
                    }
            }
        
    }
    
    SDL_DestroyWindow(fenetre);

    SDL_Quit();
        
    return EXIT_SUCCESS;
}
