#include "declaration.h"

/*
    MARIO
*/

Mario *new_joueur()
{
    Mario *mario = malloc(sizeof(*mario));
    return mario;
}

int load_image_mario(SDL_Renderer *renderer, Mario *mario)
{
    SDL_Surface *picture = NULL;
    int error = 0;

    //MARIO DIRECTION VERS LE HAUT
    picture = IMG_Load("src/assets/image_pack1/mario_haut.gif");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        error--;
    }
    mario->haut = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);

    //MARIO DIRECTION VERS LE BAS
    picture = IMG_Load("src/assets/image_pack1/mario_bas.gif");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        error--;
    }
    mario->bas = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);

    //MARIO DIRECTION VERS LA DROITE
    picture = IMG_Load("src/assets/image_pack1/mario_droite.gif");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        error--;
    }
    mario->droite = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);

    //MARIO DIRECTION VERS LA GAUCHE
    picture = IMG_Load("src/assets/image_pack1/mario_gauche.gif");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        error--;
    }
    mario->gauche = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);

    return error;
}

void deplacer_mario(unsigned int map[][NB_BLOCS_HAUTEUR], SDL_Rect *position, Direction_Mario direction)
{
    switch (direction)
    {
        case MARIO_HAUT:
            //SI NOUS SOMME DEJA A LA LIMITE DU JEU
            if(position->y - 1 < 0)
                break;

            //S'IL Y A UN MUR 
            if(map[position->x][position->y - 1] == MUR)
                break;

            //S'IL Y A UNE CAISSE OK OU UNE SIMPlE CAISSE ET DEVANT IL Y'A UN OBSTACLE
            if((map[position->x][position->y - 1] == CAISSE || map[position->x][position->y - 1] == CAISSE_OK)
                     && ((map[position->x][position->y - 2] != VIDE && map[position->x][position->y - 2] != OBJECTIF)  || position->y - 2 < 0))
                break;
            
            //S'IL Y A UNE CAISSE OK OU UNE SIMPlE CAISSE ET DEVANT IL N'Y A PAS UN OBSTACLE
            if(map[position->x][position->y - 1] == CAISSE || map[position->x][position->y - 1] == CAISSE_OK)
                deplacer_caisse(&map[position->x][position->y - 1], &map[position->x][position->y - 2]);

            position->y--;
            break;

        case MARIO_BAS:
            if(position->y + 1 >= NB_BLOCS_HAUTEUR)
                break;

            //S'IL Y A UN MUR 
            if(map[position->x][position->y + 1] == MUR)
                break;

            //S'IL Y A UNE CAISSE OK OU UNE SIMPlE CAISSE ET DEVANT IL Y'A UN OBSTACLE
            if((map[position->x][position->y + 1] == CAISSE || map[position->x][position->y + 1] == CAISSE_OK)
                     && ((map[position->x][position->y + 2] != VIDE && map[position->x][position->y + 2] != OBJECTIF)  || position->y + 2 >= NB_BLOCS_HAUTEUR))
                break;

            //S'IL Y A UNE CAISSE OK OU UNE SIMPlE CAISSE ET DEVANT IL N'Y A PAS UN OBSTACLE
            if(map[position->x][position->y + 1] == CAISSE || map[position->x][position->y + 1] == CAISSE_OK)
                deplacer_caisse(&map[position->x][position->y + 1], &map[position->x][position->y + 2]);

            position->y++;
            break;

        case MARIO_DROITE:
            if(position->x + 1 >= NB_BLOCS_LARGEUR)
                break;

            //S'IL Y A UN MUR 
            if(map[position->x + 1][position->y] == MUR)
                break;

            //S'IL Y A UNE CAISSE OK OU UNE SIMPlE CAISSE ET DEVANT IL Y'A UN OBSTACLE
            if((map[position->x + 1][position->y] == CAISSE || map[position->x + 1][position->y] == CAISSE_OK)
                     && ((map[position->x + 2][position->y] != VIDE && map[position->x + 2][position->y] != OBJECTIF)  || position->x + 2 >= NB_BLOCS_HAUTEUR))
                break;

            //S'IL Y A UNE CAISSE OK OU UNE SIMPlE CAISSE ET DEVANT IL N'Y A PAS UN OBSTACLE
            if(map[position->x + 1][position->y] == CAISSE || map[position->x + 1][position->y] == CAISSE_OK)
                deplacer_caisse(&map[position->x + 1][position->y], &map[position->x + 2][position->y]);

            position->x++;
            break;

        case MARIO_GAUCHE:
            if(position->x - 1 < 0)
                break;

            //S'IL Y A UN MUR 
            if(map[position->x - 1][position->y] == MUR)
                break;

            //S'IL Y A UNE CAISSE OK OU UNE SIMPlE CAISSE ET DEVANT IL Y'A UN OBSTACLE
            if((map[position->x - 1][position->y] == CAISSE || map[position->x - 1][position->y] == CAISSE_OK)
                     && ((map[position->x - 2][position->y] != VIDE && map[position->x - 2][position->y] != OBJECTIF)  || position->x - 2 < 0))
                break;

            //S'IL Y A UNE CAISSE OK OU UNE SIMPlE CAISSE ET DEVANT IL N'Y A PAS UN OBSTACLE
            if(map[position->x - 1][position->y] == CAISSE || map[position->x - 1][position->y] == CAISSE_OK)
                deplacer_caisse(&map[position->x - 1][position->y], &map[position->x - 2][position->y]);

            position->x--;
            break;
        
        default:
            break;
    }
}

void destroy_mario(Mario *mario)
{
    if (mario->haut != NULL)
        SDL_DestroyTexture(mario->haut);

    if (mario->bas != NULL)
        SDL_DestroyTexture(mario->bas);

    if (mario->droite != NULL)
        SDL_DestroyTexture(mario->droite);

    if (mario->gauche != NULL)
        SDL_DestroyTexture(mario->gauche);

    free(mario);
    mario = NULL;
}

/*
    OBJETS
*/

Objets *new_Objets()
{
    Objets *objets = malloc(sizeof(*objets));
    return objets;
}

int load_image_objets(SDL_Renderer *renderer, Objets *objets)
{
    SDL_Surface *picture = NULL;
    int error = 0;

    //OBJET MUR
    picture = IMG_Load("src/assets/image_pack1/mur.png");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        error--;
    }
    objets->mur = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);

    //OBJET CAISSE
    picture = IMG_Load("src/assets/image_pack1/caisse.png");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        error--;
    }
    objets->caisse = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);

    //OBJET CAISSE OK
    picture = IMG_Load("src/assets/image_pack1/caisse_ok.png");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        error--;
    }
    objets->caisse_ok = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);

    //OBJECT OBJECTIF
    picture = IMG_Load("src/assets/image_pack1/objectif.png");
    if (picture == NULL)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        error--;
    }
    objets->objectif = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);

    return error;
}

void deplacer_caisse(int *position_un, int *position_deux)
{
    if(*position_deux == OBJECTIF)
        *position_deux = CAISSE_OK;
    else
        *position_deux = CAISSE;
    
    if(*position_un == CAISSE_OK)
        *position_un = OBJECTIF;
    else
        *position_un = VIDE; 
}

void destroy_objets(Objets *objets)
{
    if (objets->mur != NULL)
        SDL_DestroyTexture(objets->mur);

    if (objets->caisse != NULL)
        SDL_DestroyTexture(objets->caisse);

    if (objets->caisse_ok != NULL)
        SDL_DestroyTexture(objets->caisse_ok);

    if (objets->objectif != NULL)
        SDL_DestroyTexture(objets->objectif);

    free(objets);
    objets = NULL;
}