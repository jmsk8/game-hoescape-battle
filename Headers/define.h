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
#define PUTE 'h'
#define SMART_PUTE 'H'
#define PLAYER "Q"
#define GIRLFRIEND 'g'
#define PUTE_PLAYER 49
#define SAFE_ZONE 'X'
#define MAP_LIMITE '0'
#define FLOWER '*'
#define BULLET 'x'
#define AMMO 'I'


#define LEFT 'q'
#define RIGHT 'd'
#define UP 'z'
#define DOWN 's'

#define WON 0
#define LOST -1
#define CONTINUE 1
#define CONTAMINE - 2

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



#endif