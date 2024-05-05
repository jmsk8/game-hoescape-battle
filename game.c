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
                // Vérifier si les coordonnées actuelles correspondent à celles du joueur
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
        refresh();
        usleep(45000);
    }
    pthread_exit(NULL);
}

void *player_move(void *args)
{
    Player_Args *player_args = (Player_Args *)args;
    Player *player = player_args->player;
    char ***map = player_args->map;
    Config *config = player_args->config;
    int x_tmp;
    int y_tmp;
    int ch;
    int bullet;
    while (flag)
    {
        x_tmp = player->coord_x;
        y_tmp = player->coord_y;

        bullet = 1;
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
            player_shotgun(player, map, ch);
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
    int speed = putes_args->game_speed;
    while (flag)
    {
        while (current != NULL)
        {
            (*map)[current->coord_x][current->coord_y] = ' ';
            if (!current->is_alive)
            {
                current->coord_x = 0;
                current->coord_x = 0;
                (*map)[current->coord_x][current->coord_y] = MAP_LIMITE;
            }
            else
            {
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
            usleep(speed);
        }
        current = head;
        // usleep(speed);
    }
    free(putes_args);
    pthread_exit(NULL);
}

int checkpos(Player *player, Pute *pute, Config *config)
{
    int x;
    int y;
    Pute *current = pute;
    x = player->coord_x;
    y = player->coord_y;
    if (x == config->size_x  / 2 && y == config->size_y - 7)
        return (2);
    while (current != NULL)
    {
        if (x == current->coord_x && y == current->coord_y)
            return (0);
        current = current->next;
    }
       
        return (1);
}

void *shotgun_clear(void *args)
{
    Pute_args *putes_args = (Pute_args *)args;
    Pute *current = putes_args->pute;
    char ***map = putes_args->map;
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
    free(putes_args);
    pthread_exit(NULL);
}

void check_dead_pute(Pute *pute, char ***map)
 {
     while (pute != NULL)
        {
            if ((*map)[pute->coord_x][pute->coord_y] == BULLET)
                pute->is_alive = 0;
            pute = pute->next;
        }
 }
int game(char **map, Entity *entity, Config *config) {
    int check = 1;
    create_player_thread(entity, &map, config);
    create_pute_thread(entity,&map, config);
    creat_display_thread(map, entity->player);
    creat_shotgun_check_thread(entity->pute, &map);
    //creat_check_dead_pute(entity->pute, map);
    while (check == 1 && flag == 1) {
        map_struct(&map, config);
        check_dead_pute(entity->pute, &map);
        check = checkpos(entity->player, entity->pute, config);
        usleep(10);
    } 
    flag = 0;
    endwin();
    return (check);
}