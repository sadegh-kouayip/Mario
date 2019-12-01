#ifndef __LEVEL__H__
#define __LEVEL__H__

typedef struct Level
{
    int value[12][12];
    Level *next;

}Level;

Level *new_level();

#endif