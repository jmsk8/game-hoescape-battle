#include  "Headers/fonctions.h"
#include  "Headers/define.h"

void create_player_thread(Entity *entity, char ***map, Config *config) {
    pthread_t player_thread;
    Player_Args *player_args = (Player_Args *)malloc(sizeof(Player_Args));
    player_args->player = entity->player;
    player_args->map = map;
    player_args->config = config;
    pthread_create(&player_thread, NULL, player_move, (void *)player_args);
}

void create_pute_thread(Entity *entity, char ***map, Config *config)
{
    pthread_t putes_thread;
    Pute_args *putes_args = (Pute_args *)malloc(sizeof(Pute_args));
    putes_args->pute = entity->pute;
    putes_args->map = map;
    putes_args->game_speed = config->game_speed;
    pthread_create(&putes_thread, NULL, pute_move,(void *)putes_args);
}

void creat_display_thread(char **map, Player *player) {
    pthread_t display_thread;
    DisplayArgs *display_args = (DisplayArgs *)malloc(sizeof(DisplayArgs));
    display_args->map = map;
    display_args->player = player;

    pthread_create(&display_thread, NULL, display_map, (void *)display_args);
}

void creat_shotgun_check_thread(Pute *pute, char ***map)
{
    pthread_t shotgun_check_thread;
    Pute_args *shotgun_check_args = (Pute_args *)malloc(sizeof(Pute_args));
    shotgun_check_args->pute = pute;
    shotgun_check_args->map = map;
    pthread_create(&shotgun_check_thread, NULL, shotgun_clear, (void *)shotgun_check_args);

}

//void creat_check_dead_pute(Pute)
