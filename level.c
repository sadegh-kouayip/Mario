#include <stdio.h>
#include <stdlib.h>
#include "level.h"

int chargement_niveau()
{
    int i = 0;

    FILE *fichier = NULL;

    fichier = fopen("level.lvl", "r");

    if (fichier != NULL)
    {
        for (i = 0; i < MAX_LEVEL; i++)
        {
            int c, ligne = 1;

            rewind(fichier);
            while (c != EOF && ligne < i + 1)
            {
                c = fgetc(fichier);
                if (c == '\n')
                    ligne++;
            }

            fgets(Level[i].l, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);
        }

        fclose(fichier);

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

int niveau_jeux(unsigned int map[][NB_BLOCS_LARGEUR], int level, SDL_Rect *position_mario)
{
    int x = 0, y = 0, i = 0;

    if(level > MAX_LEVEL - 1)
        return EXIT_FAILURE;

    for (x = 0; x < NB_BLOCS_HAUTEUR; x++)
    {
        for (y = 0; y < NB_BLOCS_LARGEUR; y++)
        {
            if(map[x][y] != VIDE)
                map[x][y] = VIDE;

            switch (Level[level].l[i])
            {
            case '1':
                map[x][y] = MUR;
                break;

            case '2':
                map[x][y] = CAISSE;
                break;
            
            case '3':
                map[x][y] = CAISSE_OK;
                break;
            
            case '4':
                map[x][y] = OBJECTIF;
                break;

            case '5':
                position_mario->x = x;
                position_mario->y = y;
                break;
            }
            i++;
        }
    }

    return EXIT_SUCCESS;
}

int save_modification(unsigned map[][NB_BLOCS_LARGEUR], int level)
{
    int x = 0, y = 0, i = 0;
 
    for(x=0; x<NB_BLOCS_HAUTEUR; x++)
    {
        for(y=0; y<NB_BLOCS_LARGEUR; y++)
        {
            switch(map[x][y])
            {
               case VIDE:
                    Level[level].l[i] = '0';
                    break;
 
               case MUR:
                    Level[level].l[i] = '1';
                    break;
 
               case CAISSE:
                    Level[level].l[i] = '2';
                    break;
 
               case CAISSE_OK:
                    Level[level].l[i] = '3';
                    break;
 
               case OBJECTIF:
                    Level[level].l[i] = '4';
                    break;
 
               case MARIO:
                    Level[level].l[i] = '5';
                    break;
            }
            i++;
        }
    }
 
    return EXIT_SUCCESS;
 
}
 
int save_level_fihier()
{
    int i;
 
    FILE *fichier = NULL;
 
    fichier = fopen("level.lvl","w");
 
    if(fichier != NULL)
    {
        for(i = 0; i<10; i++)
        {
            fprintf(fichier,"%s\n",Level[i].l);
        }
 
        fclose(fichier);
 
        return EXIT_SUCCESS;
    }
    else return EXIT_FAILURE;
 
}