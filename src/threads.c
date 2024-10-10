#include  "../include/include.h"

void creat_player_thread(Entity *entity, char ***map, pthread_t *threads) {
    Player_Args *player_args = (Player_Args *)malloc(sizeof(Player_Args));
    player_args->player = entity->player;
    player_args->map = map;
    pthread_create(&threads[0], NULL, player_move, (void *)player_args);
}

void creat_pute_thread(Entity *entity, char ***map, pthread_t *threads) {
    Pute_args *putes_args = (Pute_args *)malloc(sizeof(Pute_args));
    putes_args->pute = entity->pute;
    putes_args->map = map;
    pthread_create(&threads[1], NULL, pute_move, (void *)putes_args);
}

void creat_smartPute_thread(Entity *entity, char ***map, pthread_t *threads) {
    Pute_args *smartPute_args = (Pute_args *)malloc(sizeof(Pute_args));
    smartPute_args->smartPute = entity->smartPute;
    smartPute_args->player = entity->player;
    smartPute_args->map = map;
    pthread_create(&threads[2], NULL, smartPute_move, (void *)smartPute_args);
}

void creat_display_thread(char **map, Player *player, pthread_t *threads) {
    DisplayArgs *display_args = (DisplayArgs *)malloc(sizeof(DisplayArgs));
    display_args->map = map;
    display_args->player = player;
    pthread_create(&threads[3], NULL, display_map, (void *)display_args);
}

void creat_shotgun_check_thread(char ***map, pthread_t *threads) {
    Player_Args *shotgun_check_args = (Player_Args *)malloc(sizeof(Player_Args));
    shotgun_check_args->map = map;
    shotgun_check_args->player = NULL;
    pthread_create(&threads[4], NULL, shotgun_clear, (void *)shotgun_check_args);
}

void creat_check_dead_pute(Pute *pute, Pute *smartPute,  char ***map, pthread_t *threads) {
    Pute_args *checkDeadPute_Args = (Pute_args *)malloc(sizeof(Pute_args));
    checkDeadPute_Args->smartPute = smartPute;
    checkDeadPute_Args->pute = pute;
    checkDeadPute_Args->map = map;
    pthread_create(&threads[5], NULL, check_dead_pute, (void *)checkDeadPute_Args);
}

void creat_threads (Entity *entity, char ***map, pthread_t *threads) {
    creat_display_thread(*map, entity->player, threads);
    creat_player_thread(entity, map, threads);
    creat_shotgun_check_thread(map, threads);
    creat_smartPute_thread(entity, map, threads);
    creat_pute_thread(entity, map, threads);
    creat_check_dead_pute(entity->pute, entity->smartPute, map, threads);
}
