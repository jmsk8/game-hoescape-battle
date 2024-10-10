#ifndef INCLUDE_H
#define INCLUDE_H

/*define and struct*/

#pragma once
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define BUSH '*'
#define TREE 'o'
#define PUTE 'h'
#define SMART_PUTE 'H'
#define PLAYER "Q"
#define GIRLFRIEND 'g'
#define PUTE_PLAYER 49
#define SAFE_ZONE 'X'
#define MAP_LIMITE '0'
#define FLOWER '+'
#define BULLET 'x'
#define AMMO 'I'
#define GO_LEFT '<'
#define GO_RIGHT '>'
#define GO_UP '^'
#define GO_DOWN 'v'


#define LEFT 'q'
#define RIGHT 'd'
#define UP 'z'
#define DOWN 's'

#define WON 0
#define LOST -1
#define CONTINUE 1
#define CONTAMINE - 2

#define NUM_OF_THREAD 6
#define SIZE_X 80
#define SIZE_Y 80


typedef struct result
{
    int check;
    float score;
}  Result;

typedef struct Player
{
    int coord_x;
    int coord_y;
    int mun;
    int flower;
} Player;

typedef struct
{
    int size_x;
    int size_y;
    int numb_of_pute;
    int numb_of_bush;
    int numb_of_smartPute;
    int game_speed;
    int smartPute_speed;
    int is_adventure_mod;
} Config;

typedef struct Pute
{
    int coord_x;
    int coord_y;
    int is_alive;
    int speed;
    int id;
    struct Pute *next;

} Pute;

typedef struct Entity
{
    Player *player;
    Pute *pute;
    Pute *smartPute;
} Entity;

typedef struct Game
{
    char **map;
    char **map_buffer;
    struct Entity *prevEntity;
    struct Entity *entity;
    struct Entity *nextEntity;


}Game;

typedef struct {
    Player *player;
    char ***map;
} Player_Args;

typedef struct {
    Pute *pute;
    Player *player;
    Pute *smartPute;
    char ***map;
}Pute_args;

typedef struct {
    char **map;
    Player *player;
} DisplayArgs;


/*func*/
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

void allocate_memory_and_read_file2(char ***map, int *x, int *y, int map_num, int lvl);

/*gnl*/

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1, size_t size, int is_stash);
void	ft_strcat(char *dst, const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_free_stash(char **stash, int create_line);


#endif
