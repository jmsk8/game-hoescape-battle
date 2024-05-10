#include  "Headers/fonctions.h"
#include  "Headers/define.h"

void map_struct(char ***map, Config *config)
{
    int x;
    int y;

    x = 0;
    while (x < config->size_x)
    {
        y = 0;
        while (y < config->size_y)
        {
            (*map)[0][y ] = MAP_LIMITE;            // haut
            (*map)[config->size_x - 1][y] = MAP_LIMITE; // bas
            (*map)[x][0] = MAP_LIMITE;            // gauche 
            (*map)[x][config->size_y-1] = MAP_LIMITE; // droite 
            y++;
        }
        x++;
    }
    x = 0;
    while (x <= 4) 
    {
        y = 0;
        while (y <= 2) 
        {
            (*map)[config->size_x / 2 - 2][x + config->size_y - 9] = MAP_LIMITE; // haut
            (*map)[config->size_x / 2 - 2][y + config->size_y - 8] = SAFE_ZONE;
            (*map)[config->size_x / 2 - 1][y + config->size_y - 8] = SAFE_ZONE;

            (*map)[config->size_x / 2 + 2][x + config->size_y - 9] = MAP_LIMITE; // bas
            (*map)[config->size_x / 2 + 2][y + config->size_y - 8] = SAFE_ZONE;
            (*map)[config->size_x / 2 + 1][y + config->size_y - 8] = SAFE_ZONE;

            (*map)[x + config->size_x / 2 - 2][config->size_y - 9] = MAP_LIMITE; // gauche x
            (*map)[y + config->size_x / 2 - 1][config->size_y - 9] = SAFE_ZONE;
            (*map)[y + config->size_x / 2 - 1][config->size_y - 8] = SAFE_ZONE;

            (*map)[x + config->size_x / 2 - 2][config->size_y - 5] = MAP_LIMITE; // droite x
            (*map)[y + config->size_x / 2 - 1][config->size_y - 5] = SAFE_ZONE;
            (*map)[y + config->size_x / 2 - 1][config->size_y - 6] = SAFE_ZONE;
            y++;
        }
        x++;
    }
    x = 0;
    while (x <= 2)
    {
        (*map)[config->size_x / 2 + 1][x+3] = SAFE_ZONE;
        (*map)[config->size_x / 2 - 1][x+3] = SAFE_ZONE;
        (*map)[x + config->size_x/ 2 - 1][5] = SAFE_ZONE;
        (*map)[x + config->size_x/ 2 -1][3] = SAFE_ZONE;
        x++;
    }
    x = 0;
    y = 0;

    while (x <= 1)
    {
        while (y <= 2)
        {
            (*map)[(config->size_x - 2 ) - x][(config->size_y / 2 - 2) + y] = SAFE_ZONE; 
            y++;
        }
        y = 0;
        x++;
    }
    (*map)[(config->size_x - 2)][(config->size_y / 2) - 1] = FLOWER; 

}

void setup_map_memory(char ***map, Config *config)
{

    *map = malloc(sizeof(char*) * config->size_x);
    if (*map == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < config->size_x; i++) {
        (*map)[i] = malloc(sizeof(char) * (config->size_y + 1));
        if ((*map)[i] == NULL) {
            fprintf(stderr, "Erreur lors de l'allocation de mémoire.\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < config->size_y; j++) {
            (*map)[i][j] = ' ';
        }
        (*map)[i][config->size_y] = '\0'; 
    }
    map_struct(map, config);
}

void setup_config(Config *config)
{
    config->size_x = 40;
    config->size_y = 80;
    int check = 0;
    char rep[7];
      while (check == 0)
    {
        printf("quel mode de difficulté maggle? [easy,normal,hard] || tapez [size] pour donner une taille de map perso. pair uniquement, et pas en dessous de 20 sur 20\n");
        if (scanf("%7s", rep) != 1) {
            printf("Erreur de saisie. Veuillez réessayer.\n");
            continue;
        }
        if(ft_strcmp(rep,"size") == 0)
        {
            printf("Entrez la taille x : ");
            if (scanf("%d", &(config->size_x)) != 1) {
                printf("Erreur de saisie. Veuillez réessayer.\n");
                continue;
            }
            printf("Entrez la taille y : ");
            if (scanf("%d", &(config->size_y)) != 1) {
                printf("Erreur de saisie. Veuillez réessayer.\n");
                continue;
            }
        }
    
        if(ft_strcmp(rep,"easy") == 0)
        {
            config->numb_of_pute = ((config->size_x * config->size_y ) / 16);
            config->numb_of_bush = ((config->size_x * config->size_y ) / 14);
            config->numb_of_smartPute = ((config->size_x * config->size_y ) / 160);
            config->game_speed = 1000000 / ((config->size_x * config->size_y ) / 16);
            config->smartPute_speed = 900000 / ((config->size_x * config->size_y ) / 160);
            check = 1;
        }
        else if(ft_strcmp(rep,"normal") == 0)
        {
            config->numb_of_pute = ((config->size_x * config->size_y ) / 14);
            config->numb_of_bush = ((config->size_x * config->size_y ) / 12);
            config->numb_of_smartPute = ((config->size_x * config->size_y ) / 140);
            config->game_speed = 900000 / ((config->size_x * config->size_y ) / 14);
            config->smartPute_speed = 800000 / ((config->size_x * config->size_y ) / 140);
            check = 1;
        }
        else if(ft_strcmp(rep,"hard") == 0)
        {
            config->numb_of_pute = ((config->size_x * config->size_y ) / 12);
            config->numb_of_bush = ((config->size_x * config->size_y ) / 10);
            config->numb_of_smartPute = ((config->size_x * config->size_y ) / 120);
            config->game_speed = 800000 / ((config->size_x * config->size_y ) / 12);
            config->smartPute_speed = 700000 / ((config->size_x * config->size_y ) / 120);
            check = 1;
        }
        else if(ft_strcmp(rep,"test") == 0)
        {
            config->numb_of_pute = 0;
            config->numb_of_bush = 0;
            config->smartPute_speed = 1000000 / ((config->size_x * config->size_y ) / 160);
            config->numb_of_smartPute = ((config->size_x * config->size_y ) / 160);
            check = 1;
        }
        int result = system("clear");
        if (result == -1) 
            printf("Erreur lors de l'exécution de la commande 'clear'.\n");
    }
}

void setup_game(char ***map, Entity *entity, Config *config)
{   
    setup_config(config);
    setup_map_memory(map, config);
    entity->player = (Player*)player_spawn(config, map);
    girflfriend_spawn(map, config);
    bush_spawn(map, config);
    pute_spawn(map,&entity->pute, config);
    smartPute_spawn(map,&entity->smartPute,config);
    initscr();
    noecho();
    curs_set(0);
}