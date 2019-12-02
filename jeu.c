/*Commande pour compiler sur Windows
>gcc src/*.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -W
*/

#include "jeu.h"
#include "level.h"

int play_games(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Texture *mario_actuel = NULL;
    SDL_Event event;
    SDL_Rect position = {0, 0, TAILLE_BLOC, TAILLE_BLOC}, position_mario = {0, 0, 0, 0};
    SDL_bool isOpen = SDL_TRUE;
    int i, j, objectifs_restants, level = 0;

    //CARTE DE REPERE DU JEU
    unsigned int map[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    //CHARGEMENT NIVEAU 1
    if (niveau_jeux(map, level, &position_mario) != EXIT_SUCCESS)
    {
        printf("ERREUR > chargement de niveau\n");
        return EXIT_FAILURE;
    }

    //PACKAGE MARIO
    Mario *mario = new_joueur();
    if (mario == NULL)
    {
        printf("Probleme d'allocation memoire\n");
        return EXIT_FAILURE;
    }

    //PACKAGE OBJECTS
    Objets *objets = new_Objets();
    if (objets == NULL)
    {
        printf("Probleme d'allocation memoire\n");
        destroy_mario(mario);
        return EXIT_FAILURE;
    }

    //CHARGEMENT DES TEXTURE D'IMAGE
    if (load_image_mario(renderer, mario) < 0)
    {
        clean_all_resources(mario, objets);
        return EXIT_FAILURE;
    }
    //CHARGEMENT DES TEXTURE D'OBJETS
    if (load_image_objets(renderer, objets) < 0)
    {
        clean_all_resources(mario, objets);
        return EXIT_FAILURE;
    }

    mario_actuel = mario->haut;

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
                case SDLK_SPACE:
                    if (niveau_jeux(map, level, &position_mario) != EXIT_SUCCESS)
                    {
                        printf("ERREUR > chargement de niveau");
                        clean_all_resources(mario, objets);
                        return EXIT_FAILURE;
                    }
                    break;
                }
                break;
            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        objectifs_restants = 0;

        //PLACEMENT DES OBJETS A L'ECRAN
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
                    if (SDL_RenderCopy(renderer, objets->mur, NULL, &position) != 0)
                    {
                        clean_all_resources(mario, objets);
                        return EXIT_FAILURE;
                    }
                    break;

                case CAISSE:
                    //POSITIONNE LA CAISSE
                    if (SDL_RenderCopy(renderer, objets->caisse, NULL, &position) != 0)
                    {
                        clean_all_resources(mario, objets);
                        return EXIT_FAILURE;
                    }
                    break;

                case CAISSE_OK:
                    //POSITIONNE LA CAISSE
                    if (SDL_RenderCopy(renderer, objets->caisse_ok, NULL, &position) != 0)
                    {
                        clean_all_resources(mario, objets);
                        return EXIT_FAILURE;
                    }
                    break;

                case OBJECTIF:
                    //POSITIONNE LA CAISSE
                    if (SDL_RenderCopy(renderer, objets->objectif, NULL, &position) != 0)
                    {
                        clean_all_resources(mario, objets);
                        return EXIT_FAILURE;
                    }
                    objectifs_restants++;

                    break;
                }
            }
        }

        //PLACE MARIO A lA BONNE POSITION
        position.x = position_mario.x * TAILLE_BLOC;
        position.y = position_mario.y * TAILLE_BLOC;

        if (SDL_RenderCopy(renderer, mario_actuel, NULL, &position) != 0)
        {
            clean_all_resources(mario, objets);
            return EXIT_FAILURE;
        }

        // MISE A JOUR Du RENDERER
        SDL_RenderPresent(renderer);

        //CHECK S'IL Y A ENCORE UN OBJECTIF SUR LA MAP
        if (objectifs_restants == 0)
        {
            //PASSE AU NIVEAU SUIVANT
            level++;

            printf("Vous avez gagnez le niveau %d\n", level);

            if (level < MAX_LEVEL)
            {
                SDL_Delay(3000);

                //CHARGEMENT NIVEAU SUIVANT
                if (niveau_jeux(map, level, &position_mario) != EXIT_SUCCESS)
                {
                    printf("ERREUR > chargement de niveau\n");
                    isOpen = SDL_FALSE;
                }
            }
            else if(level == MAX_LEVEL)
            {
                printf("FELICITATION VOUS AVEZ DELIVRER TOUS LES NIVEAUX !\n");
                SDL_Delay(2000);
                isOpen = SDL_FALSE;
            }
            
        }
    }

    destroy_mario(mario);
    destroy_objets(objets);

    return EXIT_SUCCESS;
}

void clean_all_resources(Mario *mario, Objets *objets)
{
    SDL_Log("ERREUR > %s\n", SDL_GetError());
    destroy_mario(mario);
    destroy_objets(objets);
}