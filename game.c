#include  "Headers/fonctions.h"
#include  "Headers/define.h"
volatile int flag = 1;

void *display_map(void *args)
{
    DisplayArgs *display_args = (DisplayArgs *)args;
    char **map = display_args->map;
    Player *player = display_args->player;

    while (flag)
    {
        int i = 0;
        int y = 0;
        clear();
        while (map[i] != NULL)
        {
            int j = 0;
            int x = 0;

            while (map[i][j] != '\0')
            {
                if (i == player->coord_x && j == player->coord_y) {
                    mvprintw(y, x, PLAYER);
                } else {
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
        usleep(45000);
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
                player ->mun -= 1;
            }
            break;
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
    Pute *current = putes_args->pute;
    Pute *head = putes_args->pute;
    map = putes_args->map;
    while (flag)
    {
        while (current != NULL)
        {
            if (current->is_alive)
            {
                (*map)[current->coord_x][current->coord_y] = ' ';
                direction = rand() % 4;
                x = current->coord_x;
                y = current->coord_y;
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
                current->coord_x = x;
                current->coord_y = y;
                (*map)[x][y] = PUTE;
            }
            current = current->next;
            if (current != NULL)
                usleep(current->speed);
        }
        current = head;
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
    Pute *current = smartPutes_args->smartPute;
    Pute *head = smartPutes_args->smartPute;
    Player *player = smartPutes_args->player;
    map = smartPutes_args->map;

    while (flag)
    {
        while (current != NULL)
        {
            if (current->is_alive)
            {
                (*map)[current->coord_x][current->coord_y] = ' ';
                if (find_target(current, player) <= 15)
                    direction = target_tracking(current, player);
                else
                    direction = rand_r(&seed) % 4 + 1;
                x = current->coord_x;
                y = current->coord_y;
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
                current->coord_x = x;
                current->coord_y = y;
                (*map)[x][y] = SMART_PUTE;
            }
            current = current->next;
            if (current != NULL)
                usleep(current->speed);
        }
        current = head;
    }
    free(smartPutes_args);
    pthread_exit(NULL);
}

int checkpos(Entity *entity, Config *config, char ***map)
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
        player->mun += 5;
    }
    if ((*map)[x][y] == FLOWER)
        player->flower = 1;
    if (x == config->size_x  / 2 && y == config->size_y - 7)
    {
        if (player->flower)
            return (2);
        else
            return (0);
    }
    while (current_pute != NULL)
    {
        if (x == current_pute->coord_x && y == current_pute->coord_y)
            return (0);
        current_pute = current_pute->next;
    }
    while (current_smartPute != NULL)
    {
        if (x == current_smartPute->coord_x && y == current_smartPute->coord_y)
            return (0);
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
        while (pute != NULL)
        {
            if ((*map)[pute->coord_x][pute->coord_y] == BULLET)
            {
                pute->is_alive = 0;
                pute->coord_x = 0;
                pute->coord_y = 0;
            }
            pute = pute->next;
        }
        while (smartPute != NULL)
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

void game(char **map, Entity *entity, Config *config, Result *result) 
{
    flag = 1;
    result->check = 1;
    pthread_t threads[NUM_OF_THREAD];
    creat_threads(entity, &map, threads);
    while (result->check == 1 && flag != 0) {
        if (!config->is_adventure_mod)
            map_struct(&map, config);
        result->check = checkpos(entity, config, &map);
        result->score += 0.0065;
        usleep(10);
    } 
    flag = 0;
     for (int i = 0; i < NUM_OF_THREAD; i++) {
        pthread_join(threads[i], NULL);
    }
    endwin();
}