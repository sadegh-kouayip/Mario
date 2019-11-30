/*Commande pour compiler sur Windows
>gcc src/*.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
*/

#include "jeu.h"

int main(int argc, char **argv)
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *mario_actuel = NULL;
    SDL_Event event;
    SDL_Rect position = {0,0,TAILLE_BLOC,TAILLE_BLOC}, position_mario = {0,0};
    SDL_bool isOpen = SDL_TRUE;
    int i, j;

    //CARTE DE REPERE DU JEU
    unsigned int map[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    //TEST
    map[5][5] = MUR;
    map[8][3] = CAISSE;
    map[3][5] = CAISSE_OK;
    map[9][7] = OBJECTIF;

    //PACKAGE MARIO
    Mario *mario = new_joueur();
    if (mario == NULL)
    {
        printf("Probleme d'allocation memoire");
        exit(EXIT_FAILURE);
    }

    //PACKAGE OBJECTS
    Objets *objets = new_Objets();
    if (objets == NULL)
    {
        printf("Probleme d'allocation memoire");
        destroy_mario(mario);
        exit(EXIT_FAILURE);
    }

    //Lancement SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        destroy_mario(mario);
        destroy_objets(objets);
        exit(EXIT_FAILURE);
    }

    //Création fenêtre
    if (SDL_CreateWindowAndRenderer(NB_BLOCS_LARGEUR * TAILLE_BLOC, NB_BLOCS_HAUTEUR * TAILLE_BLOC, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        destroy_mario(mario);
        destroy_objets(objets);
        exit(EXIT_FAILURE);
    }

    //CHARGEMENT DES TEXTURE D'IMAGE
    if (load_image_mario(renderer, mario) < 0)
        clean_all_error_resources(mario, objets, window, renderer);

    //CHARGEMENT DES TEXTURE D'OBJETS
    if (load_image_objets(renderer, objets) < 0)
        clean_all_error_resources(mario, objets, window, renderer);

    mario_actuel = mario->droite;

    while (isOpen)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isOpen = SDL_FALSE;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    mario_actuel = mario->haut;
                    deplacer_mario(map, &position_mario, MARIO_HAUT);
                    break;
                case SDLK_DOWN:
                    mario_actuel = mario->bas;
                    deplacer_mario(map, &position_mario, MARIO_BAS);
                    break;
                case SDLK_RIGHT:
                    mario_actuel = mario->droite;
                    deplacer_mario(map, &position_mario, MARIO_DROITE);
                    break;
                case SDLK_LEFT:
                    mario_actuel = mario->gauche;
                    deplacer_mario(map, &position_mario, MARIO_GAUCHE);
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (i = 0; i < NB_BLOCS_LARGEUR; i++)
        {
            for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch (map[i][j])
                {
                    case MUR:
                        //POSITIONNE LE MUR
                        if (SDL_SetRenderTarget(renderer, NULL) != 0)
                            clean_all_error_resources(mario, objets, window, renderer);

                        if (SDL_RenderCopy(renderer, objets->mur, NULL, &position) != 0)
                            clean_all_error_resources(mario, objets, window, renderer);

                        break;

                    case CAISSE:
                        //POSITIONNE LA CAISSE
                        if (SDL_SetRenderTarget(renderer, NULL) != 0)
                            clean_all_error_resources(mario, objets, window, renderer);

                        if (SDL_RenderCopy(renderer, objets->caisse, NULL, &position) != 0)
                            clean_all_error_resources(mario, objets, window, renderer);

                        break;

                    case CAISSE_OK:
                        //POSITIONNE LA CAISSE
                        if (SDL_SetRenderTarget(renderer, NULL) != 0)
                            clean_all_error_resources(mario, objets, window, renderer);

                        if (SDL_RenderCopy(renderer, objets->caisse_ok, NULL, &position) != 0)
                            clean_all_error_resources(mario, objets, window, renderer);

                        break;

                    case OBJECTIF:
                        //POSITIONNE LA CAISSE
                        if (SDL_SetRenderTarget(renderer, NULL) != 0)
                            clean_all_error_resources(mario, objets, window, renderer);

                        if (SDL_RenderCopy(renderer, objets->objectif, NULL, &position) != 0)
                            clean_all_error_resources(mario, objets, window, renderer);

                        break;

                    default:
                        break;
                }
            }
        }

        //PLACE MARIO A lA BONNE POSITION
        position.x =  position_mario.x * TAILLE_BLOC;
        position.y =  position_mario.y * TAILLE_BLOC;

        if (SDL_SetRenderTarget(renderer, NULL) != 0)
            clean_all_error_resources(mario, objets, window, renderer);

        if (SDL_RenderCopy(renderer, mario_actuel, NULL, &position) != 0)
            clean_all_error_resources(mario, objets, window, renderer);

        // MISE A JOUR Du RENDERER
        SDL_RenderPresent(renderer);
    }

    destroy_mario(mario);
    destroy_objets(objets);
    clean_resources(window, renderer);

    return EXIT_SUCCESS;
}

void clean_resources(SDL_Window *w, SDL_Renderer *r)
{
    if (r != NULL)
        SDL_DestroyRenderer(r);

    if (w != NULL)
        SDL_DestroyWindow(w);

    SDL_Quit();
}

void clean_all_error_resources(Mario *mario, Objets *objets, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Log("ERREUR > %s\n", SDL_GetError());
    destroy_mario(mario);
    destroy_objets(objets);
    clean_resources(window, renderer);
    exit(EXIT_FAILURE);
}