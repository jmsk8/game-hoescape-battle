#ifndef DEFINE_H
#define DEFINE_H
#pragma once
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define BUSH 'o'
#define PUTE 'p'
#define SMART_PUTE 'P'
#define PLAYER "Q"
#define GIRLFRIEND 'g'
#define PUTE_PLAYER 49
#define SAFE_ZONE 'X'
#define MAP_LIMITE '0'
#define BULLET 'x'


#define LEFT 'q'
#define RIGHT 'd'
#define UP 'z'
#define DOWN 's'

#define WON 0
#define LOST -1
#define CONTINUE 1
#define CONTAMINE - 2

typedef struct Player
{
    int coord_x;
    int coord_y;
} Player;

typedef struct
{
    int size_x;
    int size_y;
    int numb_of_pute;
    int numb_of_bush;
    int game_speed;
} Config;

typedef struct Pute
{
    int coord_x;
    int coord_y;
    int is_alive;
    int id;
    struct Pute *next;
   
} Pute;

typedef struct Entity
{
    Player *player;
    Pute *pute;
} Entity;

typedef struct {
    Player *player;
    char ***map;
    Config *config;
} Player_Args;

typedef struct {
    Pute *pute;
    char ***map;
    int game_speed;
}Pute_args;

typedef struct {
    char **map;
    Player *player;
} DisplayArgs;



#endif