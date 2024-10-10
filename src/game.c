#include  "../include/include.h"

volatile int flag = 1;

void *display_map(void *args)
{
    DisplayArgs *display_args = (DisplayArgs *)args;
    char **map = display_args->map;
    Player *player = display_args->player;
    start_color();
     init_color(COLOR_BLACK, 100, 100, 100);
    init_color(COLOR_MAGENTA, 1000, 500, 600);
    init_color(COLOR_GREEN, 500, 1000, 400);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
     init_pair(4, COLOR_CYAN, COLOR_BLACK);
     init_pair(5, COLOR_RED, COLOR_BLACK);

    while (flag)
    {
        int i = 0;
        int y = 0;
        clear();
        while (flag && map[i] != NULL)
        {
            int j = 0;
            int x = 0;

            while (flag && map[i][j] != '\0')
            {
                if (i == player->coord_x && j == player->coord_y) {
                    attron(COLOR_PAIR(1));
                    mvprintw(y, x, PLAYER);
                    attroff(COLOR_PAIR(1));
                } else if ( map[i][j] == BUSH ||  map[i][j] == TREE)
                {
                    attron(COLOR_PAIR(2));
                    mvprintw(y, x, "%c", map[i][j]);
                    attroff(COLOR_PAIR(2));
                } else if (map[i][j] == SAFE_ZONE){
                    attron(COLOR_PAIR(4));
                    mvprintw(y, x, "%c", map[i][j]);
                    attroff(COLOR_PAIR(4));
                } else if (map[i][j] == PUTE || map[i][j] == SMART_PUTE){
                    attron(COLOR_PAIR(3));
                    mvprintw(y, x, "%c", map[i][j]);
                    attroff(COLOR_PAIR(3));
                } else if (map[i][j] == FLOWER){
                    attron(COLOR_PAIR(5));
                    mvprintw(y, x, "%c", map[i][j]);
                    attroff(COLOR_PAIR(5));
                    }else{
                    mvprintw(y, x, "%c", map[i][j]);
                }
                x += 2;
                j++;
            }
            y++;
            i++;
        }
        mvprintw(y + 1, 0, "Nombre de munitions: %d", player->mun);
        refresh();
        usleep(70000);
    }
    free(display_args);
    pthread_exit(NULL);
}

void *player_move(void *args)
{
    Player_Args *player_args = (Player_Args *)args;
    Player *player = player_args->player;
    char ***map = player_args->map;
    int ch;
    while (flag)
    {
        ch = getch();
        (*map)[player->coord_x][player->coord_y] = ' ';
        if (flag)
        {
            switch (ch)
            {
            case 'a':
                flag = 0;
                break;
            case UP:
                player->coord_x--;
                if (check((*map)[player->coord_x][player->coord_y], 1))
                    player->coord_x++;
                break;
            case DOWN:
                player->coord_x++;
                if (check((*map)[player->coord_x][player->coord_y], 1))
                    player->coord_x--;
                break;
            case LEFT:
                player->coord_y--;
                if (check((*map)[player->coord_x][player->coord_y], 1))
                    player->coord_y++;
                break;
            case RIGHT:
                player->coord_y++;
                if (check((*map)[player->coord_x][player->coord_y], 1))
                    player->coord_y--;
                break;
            case '8':
            case '4':
            case '5':
            case '6':
                if (player->mun > 0)
                {
                    player_shotgun(player, map, ch);
                    player->mun -= 1;
                }
                break;
            }
        }
        usleep(10000);
    }
    free(player_args);
    pthread_exit(NULL);
}

void *pute_move(void *args)
{
    char ***map;
    int direction;
    int x;
    int y;
    Pute_args *putes_args = (Pute_args *)args;
    Pute *pute = putes_args->pute;
    Pute *head = putes_args->pute;
    map = putes_args->map;
    while (flag)
    {
        while (flag &&  pute != NULL)
        {
            if (pute->is_alive)
            {
                (*map)[pute->coord_x][pute->coord_y] = ' ';
                direction = rand() % 4;
                x = pute->coord_x;
                y = pute->coord_y;
                switch (direction)
                {
                case 0: // haut
                    case_move(map, &x, &y, 0, 1);
                    break;
                case 1: // bas
                    case_move(map, &x, &y, 1, 1);
                    break;
                case 2: // gauche
                    case_move(map, &x, &y, 0, 0);
                    break;
                case 3: // droite
                    case_move(map, &x, &y, 1, 0);
                    break;
                default:
                    break;
                }
                pute->coord_x = x;
                pute->coord_y = y;
                (*map)[x][y] = PUTE;
            }
            pute = pute->next;
            if (pute != NULL)
                usleep(pute->speed);
        }
        pute = head;
    }
    free(putes_args);
    pthread_exit(NULL);
}

void *smartPute_move(void *args)
{
    char ***map;
    int direction;
    unsigned int seed = time(NULL);
    int x;
    int y;
    Pute_args *smartPutes_args = (Pute_args *)args;
    Pute *pute = smartPutes_args->smartPute;
    Pute *head = smartPutes_args->smartPute;
    Player *player = smartPutes_args->player;
    map = smartPutes_args->map;

    while (flag)
    {
        while (flag && pute != NULL)
        {
            if (flag && pute->is_alive)
            {
                (*map)[pute->coord_x][pute->coord_y] = ' ';
                if (find_target(pute, player) <= 15)
                    direction = target_tracking(pute, player);
                else
                    direction = rand_r(&seed) % 4 + 1;
                x = pute->coord_x;
                y = pute->coord_y;
                switch (direction)
                {
                case 1: // haut
                    case_move(map, &x, &y, 0, 1);
                    break;
                case 3: // bas
                    case_move(map, &x, &y, 1, 1);
                    break;
                case 2: // droite
                    case_move(map, &x, &y, 0, 0);
                    break;
                case 4: // gauche
                    case_move(map, &x, &y, 1, 0);
                    break;
                case 5: // haut
                    case_move(map, &x, &y, 0, 1);
                    break;
                default:
                    break;
                }
                pute->coord_x = x;
                pute->coord_y = y;
                (*map)[x][y] = SMART_PUTE;
            }
            pute = pute->next;
            if (pute != NULL)
                usleep(pute->speed);
        }
        pute = head;
    }
    free(smartPutes_args);
    pthread_exit(NULL);
}

int checkpos(Entity *entity, char ***map)
{
    int x;
    int y;
    Pute *current_pute = entity->pute;
    Pute *current_smartPute = entity->smartPute;
    Player *player = entity->player;

    x = player->coord_x;
    y = player->coord_y;
    if ((*map)[x][y] == AMMO)
    {
        (*map)[x][y] = ' ';
        player->mun += 3;
    }
    if ((*map)[x][y] == FLOWER)
        player->flower = 1;
    if ((*map)[x][y] == GIRLFRIEND)
    {
        if (player->flower)
            return (0);
        else
            return (-1);
    }
    if ((*map)[x][y] == GO_RIGHT)
        return (2);
    if ((*map)[x][y] == GO_LEFT)
        return (3);
    while (current_pute != NULL)
    {
        if (x == current_pute->coord_x && y == current_pute->coord_y)
            return (-1);
        current_pute = current_pute->next;
    }
    while (current_smartPute != NULL)
    {
        if (x == current_smartPute->coord_x && y == current_smartPute->coord_y)
            return (-1);
        current_smartPute = current_smartPute->next;
    }
        return (1);
}

void *shotgun_clear(void *args)
{
    Player_Args *shotgunArgs = (Player_Args *)args;
    char ***map = shotgunArgs->map;
    int x;
    int y;

    x = 0;
    while (flag)
    {
          while ((*map)[x])
            {
                y = 0;
                while ((*map)[x][y])
                {
                    if ((*map)[x][y] == BULLET)
                        (*map)[x][y] = ' ';
                    y++;
                }
                x++;
            }
            x = 0;
        usleep(150000);
    }
    free(shotgunArgs);
    pthread_exit(NULL);
}

void *check_dead_pute(void *args)
{
    Pute_args *pute_args = (Pute_args *)args;
    Pute *pute = pute_args->pute;
    Pute *smartPute = pute_args->smartPute;
    Pute *pute_head = pute;
    Pute *smartPute_head = smartPute;
    char ***map = pute_args->map;
    while (flag)
    {
        while (flag && pute != NULL)
        {
            if ((*map)[pute->coord_x][pute->coord_y] == BULLET)
            {
                pute->is_alive = 0;
                pute->coord_x = 0;
                pute->coord_y = 0;
            }
            pute = pute->next;
        }
        while (flag && smartPute != NULL)
        {
            if ((*map)[smartPute->coord_x][smartPute->coord_y] == BULLET)
            {
                (*map)[smartPute->coord_x][smartPute->coord_y] = AMMO;
                smartPute->is_alive = 0;
                smartPute->coord_x = 0;
                smartPute->coord_y = 0;
            }
            smartPute = smartPute->next;
        }
        pute = pute_head;
        smartPute = smartPute_head;
        usleep(10);
    }
    free(pute_args);
    pthread_exit(NULL);
}

struct Entity *creat_and_copy_entity(Entity *src)
{

    Entity *tmp = malloc(sizeof(Entity));
    tmp->player = malloc(sizeof(Player));
    *tmp->player = *src->player;
    while(src->pute)
    {
        tmp->pute = malloc(sizeof(Pute));
        *tmp->pute = *src->pute;
        tmp->pute = tmp->pute->next;
        src->pute = src->pute->next;
    }

    while(src->smartPute)
    {
        tmp->smartPute = malloc(sizeof(Pute));
        *tmp->smartPute = *src->smartPute;
        tmp->smartPute = tmp->smartPute->next;
        src->smartPute = src->smartPute->next;
    }

    return tmp;
}

void pute_spawn_2(Pute *pute, char **map, Config * config)
{
    int x;
    int y;

    while (pute != NULL)
    {
        pute->is_alive = 1;
        coord_generator(&map, &x, &y, config);
        pute->coord_x = x;
        pute->coord_y = y;
        pute = pute->next;
    }
}

void copy_entity(Entity *src, Entity *dest)
{
    while (src->pute)
    {
        *dest->pute = *src->pute;
        dest->pute = dest->pute->next;
        src->pute = src->pute->next;
    }

    while   (src->smartPute)
    {
        *dest->smartPute = *src->smartPute;
        dest->smartPute = dest->smartPute->next;
        src->smartPute = src->smartPute->next;
    }

}

void change_map(Game *game, Config *config, int map_num, int lvl, int is_right)
{
    allocate_memory_and_read_file2(&game->map_buffer, &config->size_x, &config->size_y, map_num, lvl);
    map_copy(&game->map,&game->map_buffer);
    if(is_right)
    {
        if (game->nextEntity == NULL)
        {
            game->prevEntity = (Entity *)creat_and_copy_entity(game->entity);
            pute_spawn_2(game->entity->pute, game->map, config);
            pute_spawn_2(game->entity->smartPute, game->map, config);
            if (is_right == 1)
                game->entity->player->coord_y = 1;
            else
                game->entity->player->coord_y = 77;
        }
        else
        {
            copy_entity(game->nextEntity, game->entity);
            game->nextEntity = NULL;
            game->entity->player->coord_y = 78;

        }
    }
    else
    {
        game->nextEntity = (Entity *)creat_and_copy_entity(game->entity);
        copy_entity(game->prevEntity, game->entity);
        game->entity->player->coord_y = 78;
    }
}

void normal_game(Game *game, Config *config, Result *result)
{
    flag = 1;
    result->check = 1;
    pthread_t threads[NUM_OF_THREAD];
    creat_threads(game->entity, &game->map, threads);
    while (result->check == 1 && flag)
    {
        map_struct(&game->map, config);
        result->check = checkpos(game->entity, &game->map);
        if (result->check != 1)
        {
            flag = 0;
            break ;
        }
        result->score += 0.0065;
        usleep(10);
    }
     endwin();
     for (int i = 0; i < NUM_OF_THREAD; i++) {
         printf("flag = %d arret du thread %d sur %d\n", flag, i + 1, NUM_OF_THREAD);
        pthread_join(threads[i], NULL);
    }
}

void adventur_game(Game *game, Config *config, Result *result)
{
    int map_num;
    int lvl;

    map_num = 1;
    lvl = 1;
    flag = 1;
    result->check = 1;
    pthread_t threads[NUM_OF_THREAD];
    creat_threads(game->entity, &game->map, threads);
    while (result->check > 0 && flag != 0)
    {
        int dir;
        if (result->check >= 2)
        {
           (result->check == 2) ? (map_num++, dir = 1) : (map_num--, dir = 2);
            change_map(game, config, map_num, lvl, dir);
            result->check = 1;
        }

        map_refresh(&game->map,&game->map_buffer);
        result->check = checkpos(game->entity, &game->map);
        result->score += 0.0065;
        usleep(10);
    }
    flag = 0;
     endwin();
     for (int i = 0; i < NUM_OF_THREAD; i++) {
        printf("arret du thread %d\n", i);
        pthread_join(threads[i], NULL);
    }
}
