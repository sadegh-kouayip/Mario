#include "edition.h"
#include "level.h"

int edit_game(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Event event;
    SDL_bool isOpen = SDL_TRUE;
    SDL_Rect position = {0, 0, TAILLE_BLOC, TAILLE_BLOC}, position_mario = {0, 0, 0, 0};

    int i, j, level = 0, objet_actuel = MUR, clicGaucheEnCours = 0, clicDroitEnCours = 0;

    //CARTE DE REPERE DU JEU
    unsigned int map[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    //CHARGEMENT NIVEAU 1
    if (niveau_jeux(map, level, &position_mario) != EXIT_SUCCESS)
    {
        printf("ERREUR > chargement de niveau\n");
        return EXIT_FAILURE;
    }

    map[position_mario.x][position_mario.y] = MARIO;

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
        clean_package(mario, objets);
        return EXIT_FAILURE;
    }
    //CHARGEMENT DES TEXTURE D'OBJETS
    if (load_image_objets(renderer, objets) < 0)
    {
        clean_package(mario, objets);
        return EXIT_FAILURE;
    }

    while (isOpen)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isOpen = SDL_FALSE;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    map[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objet_actuel;
                    clicGaucheEnCours = 1;
                    break;
                case SDL_BUTTON_RIGHT:
                    map[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = VIDE;
                    clicDroitEnCours = 1;
                    break;
                }
                break;

            case SDL_MOUSEBUTTONUP: // On désactive le booléen qui disait qu'un bouton était enfoncé
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    clicGaucheEnCours = 0; // On retient qu'un bouton n'est plus enfoncé
                    break;
                case SDL_BUTTON_RIGHT:
                    clicDroitEnCours = 0;
                    break;
                }

            case SDL_MOUSEMOTION:      // On désactive le booléen qui disait qu'un bouton était enfoncé
                if (clicGaucheEnCours) // Si on déplace la souris et que le bouton gauche de la souris est enfoncé
                {
                    map[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objet_actuel;
                }
                else if (clicDroitEnCours) // Pareil pour le bouton droit de la souris
                {
                    map[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
                }
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    if (level + 1 < MAX_LEVEL)
                    {
                        level++;
                        if (niveau_jeux(map, level, &position_mario) != EXIT_SUCCESS)
                        {
                            printf("ERREUR > chargement de niveau");
                            clean_package(mario, objets);
                            return EXIT_FAILURE;
                        }

                        map[position_mario.x][position_mario.y] = MARIO;
                    }

                    break;
                case SDLK_LEFT:
                    if (level - 1 >= 0)
                    {
                        level--;
                        if (niveau_jeux(map, level, &position_mario) != EXIT_SUCCESS)
                        {
                            printf("ERREUR > chargement de niveau");
                            clean_package(mario, objets);
                            return EXIT_FAILURE;
                        }
                        map[position_mario.x][position_mario.y] = MARIO;
                    }
                    break;
                case SDLK_s:
                    if (save_level_fihier() != EXIT_SUCCESS){
                        printf("ERREUR > sauvegarde des niveaux");
                    }
                    break;
                case SDLK_SPACE:
                    if (save_modification(map, level) != EXIT_SUCCESS){
                        printf("ERREUR > sauvegarde des modification du niveau %d", level);
                    }
                        break;
                case SDLK_r:
                    if (niveau_jeux(map, level, &position_mario) != EXIT_SUCCESS)
                    {
                        printf("ERREUR > chargement de niveau");
                        clean_package(mario, objets);
                        return EXIT_FAILURE;
                    }
                    map[position_mario.x][position_mario.y] = MARIO;
                    break;
                case SDLK_KP_1:
                    objet_actuel = MUR;
                    break;
                case SDLK_KP_2:
                    objet_actuel = CAISSE;
                    break;
                case SDLK_KP_3:
                    objet_actuel = CAISSE_OK;
                    break;
                case SDLK_KP_4:
                    objet_actuel = OBJECTIF;
                    break;
                case SDLK_KP_5:
                    objet_actuel = MARIO;
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

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
                        clean_package(mario, objets);
                        return EXIT_FAILURE;
                    }
                    break;

                case CAISSE:
                    //POSITIONNE LA CAISSE
                    if (SDL_RenderCopy(renderer, objets->caisse, NULL, &position) != 0)
                    {
                        clean_package(mario, objets);
                        return EXIT_FAILURE;
                    }
                    break;

                case CAISSE_OK:
                    //POSITIONNE LA CAISSE
                    if (SDL_RenderCopy(renderer, objets->caisse_ok, NULL, &position) != 0)
                    {
                        clean_package(mario, objets);
                        return EXIT_FAILURE;
                    }
                    break;

                case OBJECTIF:
                    //POSITIONNE LA CAISSE
                    if (SDL_RenderCopy(renderer, objets->objectif, NULL, &position) != 0)
                    {
                        clean_package(mario, objets);
                        return EXIT_FAILURE;
                    }
                    break;
                case MARIO:
                    if (SDL_RenderCopy(renderer, mario->haut, NULL, &position) != 0)
                    {
                        clean_package(mario, objets);
                        return EXIT_FAILURE;
                    }
                    break;
                }
            }
        }

        // MISE A JOUR Du RENDERER
        SDL_RenderPresent(renderer);
    }

    destroy_mario(mario);
    destroy_objets(objets);

    return EXIT_SUCCESS;
}