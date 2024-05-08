#include  "Headers/fonctions.h"
#include  "Headers/define.h"

void create_player_thread(Entity *entity, char ***map) {
    pthread_t player_thread;
    Player_Args *player_args = (Player_Args *)malloc(sizeof(Player_Args));
    player_args->player = entity->player;
    player_args->map = map;
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

void creat_smartPute_thread(Entity *entity, Config *config, char ***map)
{
    pthread_t smartPute_thread;
    Pute_args *smartPute_args = (Pute_args *)malloc(sizeof(Pute_args));
    smartPute_args->smartPute = entity->smartPute;
    smartPute_args->player = entity->player;
    smartPute_args->map = map;
    smartPute_args->game_speed = config->smartPute_speed;
    pthread_create(&smartPute_thread, NULL, smartPute_move,(void *)smartPute_args);
}
void creat_display_thread(char **map, Player *player) {
    pthread_t display_thread;
    DisplayArgs *display_args = (DisplayArgs *)malloc(sizeof(DisplayArgs));
    display_args->map = map;
    display_args->player = player;

    pthread_create(&display_thread, NULL, display_map, (void *)display_args);
}

void creat_shotgun_check_thread (char ***map)
{
    pthread_t shotgun_check_thread;
    Player_Args *shotgun_check_args = (Player_Args *)malloc(sizeof(Player_Args));
    shotgun_check_args->map = map;
    shotgun_check_args->player = NULL;
    pthread_create(&shotgun_check_thread, NULL, shotgun_clear, (void *)shotgun_check_args);

}

void creat_check_dead_pute(Pute *pute, Pute *smartPute,  char ***map)
{
    pthread_t checkDeadPute_thread;
    Pute_args *checkDeadPute_Args = (Pute_args *)malloc(sizeof(Pute_args));
    checkDeadPute_Args->smartPute = smartPute;
    checkDeadPute_Args->pute = pute;
    checkDeadPute_Args->map = map;
    pthread_create(&checkDeadPute_thread, NULL, check_dead_pute, (void *)checkDeadPute_Args);
}

void creat_threads(Config *config, Entity * entity, char ***map)
{
    creat_display_thread(*map, entity->player);
    create_player_thread(entity, map);
    create_pute_thread(entity,map, config);
    creat_smartPute_thread(entity, config,map);
    creat_shotgun_check_thread(map);
    creat_check_dead_pute(entity->pute, entity->smartPute, map);
}