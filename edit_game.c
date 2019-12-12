#include "edit_game.h"





void editeur(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Renderer *mur = NULL, *caisse = NULL, *objectif = NULL, *mario = NULL;
    SDL_Rect position;
    SDL_Event event;
    
    int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
    int objetActuel = MUR, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
    
    // Chargement des objets et du niveau
    mur = IMG_Load("assets/image_pack1/mur.png");
    caisse = IMG_Load("assets/image_pack1/caisse.jpg");
    objectif = IMG_Load("assets/image_pack1/objectif.png");
    mario = IMG_Load("assets/image_pack1/mario_bas.gif");
    
    if (!chargement_niveau())
        exit(EXIT_FAILURE);
    
    while( SDL_PollEvent( &event ) ) {
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            //case SDL_KEYDOWN:
               case SDL_MOUSEBUTTONDOWN:
                   switch(event.button.button)
                   {
                       case SDL_BUTTON_LEFT:
                             // On met l'objet actuellement choisi (mur, caisse...) à l'endroit du clic
                            carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
                            clicDroitEnCours = 1;// On retient qu'un bouton est enfonc
                           break;
                       case SDL_BUTTON_RIGHT:
                            carte[event.button.x / TAILLE_BLOC][event.button.y /TAILLE_BLOC] = VIDE;
                            clicDroitEnCours = 1;
                           break;
                       
                }
              case SDL_MOUSEBUTTONUP: // On désactive le booléen qui disait qu'un bouton était enfoncé
                   switch(event.button.button)
                   {
                       case SDL_BUTTON_LEFT:
                            clicDroitEnCours = 0;// On retient qu'un bouton n'est plus enfoncé
                           break;
                       case SDL_BUTTON_RIGHT:
                            clicDroitEnCours = 0;
                           break;
                       
                }
                 case SDL_MOUSEMOTION: // On désactive le booléen qui disait qu'un bouton était enfoncé
                    if (clicGaucheEnCours) // Si on déplace la souris et que le bouton gauche de la souris est enfoncé
                    {
                        carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objetActuel;
                    }
                    else if (clicDroitEnCours) // Pareil pour le bouton droit de la souris
                    {
                        carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
                    }
                    break;
                    
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {
                            case SDLK_ESCAPE:
                                continuer = 0;
                                break;
                            case SDLK_s:
                               niveau_jeux(carte, 0, &position);
                               break;
                            case SDLK_c:
                                chargement_niveau();
                                break;
                            case SDLK_KP_1:
                                objetActuel = MUR;
                                break;
                            case SDLK_KP_2:
                                objetActuel = CAISSE;
                                break;
                            case SDLK_KP_3:
                                objetActuel = OBJECTIF;
                                break;
                            case SDLK_KP_4:
                                objetActuel = MARIO;
                                break;
                        }
                    break;
                    
                    
                    
                   
             // Effacement de l'écran
                // Créer la fenêtre
            window = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
            if(window == NULL){
                printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
                SDL_Quit();
                return EXIT_FAILURE;
                
            }
            // Mettre en place un contexte de rendu de l’écran
            renderer = SDL_CreateRenderer(&window, -1, SDL_RENDERER_ACCELERATED);
            
            if (renderer == 0) {
                fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
            /* faire ce qu'il faut pour quitter proprement */
            }
            
            /* couleur de fond */
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderClear(renderer);
            
            // Placement des objets à l'écran
            for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
            {
                for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
                {
                    position.x = i * TAILLE_BLOC;
                    position.y = j * TAILLE_BLOC;

                    switch(carte[i][j])
                    {
                        case MUR:
                            SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, mur), &position, NULL);
                            break;
                        case CAISSE:
                             SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, caisse), &position, NULL);
                            break;
                        case OBJECTIF:
                             SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, objectif), &position, NULL);
                            break;
                        case MARIO:
                            SDL_RendereCopy(renderer, SDL_CreateTextureFromSurface(renderer, mario), &position, NULL);
                            break;
                    }
            }
        }

// Mise à jour de l'écran
        SDL_RenderPresent(renderer);
                    
                    
            
        }
        
    }
    
    
} 
