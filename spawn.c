#include  "Headers/fonctions.h"
#include  "Headers/define.h"

struct Player *player_spawn(Config *config)
{
    Player *newplayer = malloc(sizeof(Player));
    if (newplayer == NULL) {
        fprintf(stderr, "Erreur : impossible d'allouer de la mémoire pour newplayer\n");
        return NULL;
    }
    newplayer->coord_x = config->size_x / 2;
    newplayer->coord_y = 4;
    return newplayer; 
}

void girflfriend_spawn(char ***map, Config * config)
{
     (*map)[config->size_x  / 2][config->size_y - 7] = GIRLFRIEND;
}

void bush_spawn(char ***map, Config *config)
{
    int x;
    int y;
    int i;

    i = 0;
    srand(time(NULL));
    while ( i < config->numb_of_bush)
    {
    do
    {
        x = rand() % (config->size_x- 2) + 1;
        y = rand() % (config->size_y -2) + 1;
    }
    while((*map)[x][y] != ' ');
    (*map)[x][y] = BUSH;
    i++;
   }     
}

void pute_spawn(char ***map, Pute **pute, Config *config)
{
    int x;
    int y;
    int i;

    i = 0;
    while(i < config->numb_of_pute)
	{
	    coord_generator (map, &x, &y, config);
	    pushPute (pute, x, y, i);
	    (*map)[x][y] = PUTE;
        i++;
	}
}