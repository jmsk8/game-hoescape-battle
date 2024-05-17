#ifndef FONCTIONS_H
#define FONCTIONS_H
#include "define.h"

void setup_game(Game *game, Config *config);

struct Player *player_spawn(Config *config, char ***map);

void map_struct(char ***map, Config *config);

void allocate_memory_and_read_file(char ***map, int *x, int *y, int map_num, int lvl);

void girflfriend_spawn(char ***map, Config * config);

void bush_spawn(char ***map, Config *config);

void pute_spawn(char ***map, struct Pute **pute, Config *config);

void smartPute_spawn(char ***map, Pute **smartPute, Config *config);

void coord_generator (char ***map, int *x, int *y, Config *config);

void pushPute (Pute **head, int x, int y, int speed);

void ft_range(int ***tab, int min, int max);

int ft_strcmp(char *s1, char*s2);

int target_tracking(Pute *smartPute, Player *target);

void print_tab(int *tab);

int check(char c, int is_player);

void normal_game(Game *game, Config *config, Result *result);

void adventur_game(Game *game, Config *config, Result *result);

void *pute_move(void *args);

void *smartPute_move(void *args);

void *player_move(void *args);

void *display_map(void *args);

void creat_threads(Entity *entity, char ***map, pthread_t *threads);

void *check_dead_pute(void * args);

void player_shotgun(Player *player, char ***map,int ch);

void *shotgun_clear(void *args);

void case_move(char ***map, int *x, int *y, int direction, int is_col);

int find_target(Pute *smartPute, Player *player);

void read_file_to_map(char ***map, int x, int y, int map_num, int lvl);

void map_refresh(char ***map, char ***map_buffer);

void map_copy(char ***map, char ***map_buffer);

void clear_input_buffer();

#endif
