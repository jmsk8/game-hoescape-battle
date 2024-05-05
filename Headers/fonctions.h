#ifndef FONCTIONS_H
#define FONCTIONS_H
#include "define.h"

void setup_game(char ***map, Entity *entity, Config *config);

struct Player *player_spawn(char ***map, Config *config);

void map_struct(char ***map, Config *config);

void girflfriend_spawn(char ***map, Config * config);

void bush_spawn(char ***map, Config *config);

void pute_spawn(char ***map, struct Pute **pute, Config *config);

void coord_generator (char ***map, int *x, int *y, Config *config);

void pushPute (Pute **head, int x, int y, int id);

void ft_range(int ***tab, int min, int max);

int ft_strcmp(char *s1, char*s2);

void print_tab(int *tab);

int check(char c, int is_player);

int game(char **map, Entity *entity, Config *config);

void *pute_move(void *args);

void *player_move(void *args);

void *display_map(void *args);

void create_player_thread(Entity *entity, char ***map, Config *config);

void create_pute_thread(Entity *entity, char ***map, Config *config);

void creat_shotgun_check_thread(Pute *pute, char ***map);

void creat_display_thread(char **map, Player *player);

void player_shotgun(Player *player, char ***map,int ch);

void *shotgun_clear(void *args);

void case_move(char ***map, int *x, int *y, int direction, int is_col);

#endif