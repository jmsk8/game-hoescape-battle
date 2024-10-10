#include  "../include/include.h"

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

    *map = malloc(sizeof(char*) * (config->size_x));
    if (*map == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < (config->size_x); i++) {
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
    if (!config->is_adventure_mod)
        map_struct(map, config);
}

void allocate_memory_and_read_file(char ***map, int *x, int *y, int map_num, int lvl)
{
    char filename[40];
    sprintf(filename, "map/niveau_%d/map%d.txt", lvl, map_num);
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s.\n", filename);
        return;
    }

    *x = 0;
    *y = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            (*x)++;
        }
        else
        {
            (*y)++;
        }
    }
    fseek(file, 0, SEEK_SET);

    *map = (char **)malloc((*x) * sizeof(char *));
    if (*map == NULL)
    {
        printf("Erreur d'allocation de mémoire pour le tableau de pointeurs.\n");
        fclose(file);
        return;
    }
    for (int i = 0; i < *x; i++)
    {
        (*map)[i] = malloc((*y) + 1);
        if ((*map)[i] == NULL)
        {
            printf("Erreur d'allocation de mémoire pour la ligne %d.\n", i);
            fclose(file);
            free(*map);
            return;
        }
        if (fgets((*map)[i], *y + 1, file) == NULL)
        {
            printf("Erreur lors de la lecture du fichier.\n");
            fclose(file);
            free(*map);
            return;
        }
    }
    fclose(file);
}

void allocate_memory_and_read_file2(char ***map, int *x, int *y, int map_num, int lvl)
{
    char filename[40];
    sprintf(filename, "map/niveau_%d/map%d.txt", lvl, map_num);
    int fd = open(filename, O_RDONLY);
    char **tab = NULL;
	char *line;
	int i = 0;
    if (*map != NULL)
	{
		for (int j = 0; (*map)[j] != NULL; j++)
			free((*map)[j]);
		free(*map);
	}
    *map = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		char **new_tab = (char **)realloc(tab, (i + 1) * sizeof(char *));
		if (new_tab == NULL)
		{
			printf("Memory allocation failed.\n");
			for (int j = 0; j < i; j++)
			{
				free(tab[j]);
			}
			free(tab);
			close(fd);
			return;
		}
		tab = new_tab;
		tab[i] = line;
		i++;
	}
	close(fd);
	char **new_tab = (char **)realloc(tab, (i + 1) * sizeof(char *));
	if (new_tab == NULL)
	{
		printf("Memory allocation failed.\n");
		for (int j = 0; j < i; j++)
		{
			free(tab[j]);
		}
		free(tab);
		return;
	}
	tab = new_tab;
	tab[i] = NULL;
	*x = i;
	*y = i > 0 ? ft_strlen(tab[0]) : 0;
	*map = tab;
}

void map_refresh(char ***map, char ***map_buffer)
{
    int y;
    int i;

    i = 0;
    y = 0;
    while ((*map)[i])
    {
        while ((*map)[i][y])
        {
            if ((*map_buffer)[i][y] == MAP_LIMITE || (*map_buffer)[i][y] == BUSH || (*map_buffer)[i][y] == FLOWER
            || (*map_buffer)[i][y] == GIRLFRIEND || (*map_buffer)[i][y] == GO_LEFT || (*map_buffer)[i][y] == GO_RIGHT
            || (*map_buffer)[i][y] == GO_UP || (*map_buffer)[i][y] == GO_DOWN ||  (*map_buffer)[i][y] == SAFE_ZONE || (*map_buffer)[i][y] == TREE)
                (*map)[i][y] = (*map_buffer)[i][y];
            y++;
        }
        y = 0;
        i++;
    }
}

void map_copy(char ***map, char ***map_buffer)
{
    int y;
    int i;

    i = 0;
    y = 0;
    while ((*map)[i])
    {
        while ((*map)[i][y])
        {
                (*map)[i][y] = ' ';
            y++;
        }
        y = 0;
        i++;
    }

    while ((*map)[i])
    {
        while ((*map)[i][y])
        {
            if ((*map_buffer)[i][y] == MAP_LIMITE || (*map_buffer)[i][y] == BUSH || (*map_buffer)[i][y] == FLOWER
            || (*map_buffer)[i][y] == GIRLFRIEND || (*map_buffer)[i][y] == GO_LEFT || (*map_buffer)[i][y] == GO_RIGHT
            || (*map_buffer)[i][y] == GO_UP || (*map_buffer)[i][y] == GO_DOWN || (*map_buffer)[i][y] == SAFE_ZONE)
                (*map)[i][y] = (*map_buffer)[i][y];
            y++;
        }
        y = 0;
        i++;
    }
}

void setup_config(Config *config)
{
    int check = 0;
    char rep[7];
    config->size_x = 40;
    config->size_y = 80;
    while (check == 0)
    {
        printf("fait 1 pour le mode aventure, ou 0 pour le mode generation aleatoir\n");
        if (scanf("%d", &(config->is_adventure_mod)) != 1)
        {
            printf("Erreur de saisie. Veuillez réessayer.\n");
            continue;
        }
        if (!(config->is_adventure_mod >= 0) || !(config->is_adventure_mod <= 1))
        {
            //printf("Erreur de saisie. Veuillez réessayer.\n");
            printf("\033[2J\033[1;1H");
            clear_input_buffer();
            continue;
        }

        printf("quel mode de difficulté maggle? [easy,normal,hard] || tapez [size] pour donner une taille de map perso. pair uniquement, et pas en dessous de 20 sur 20\n");
        if (scanf("%7s", rep) != 1)
        {
            printf("Erreur de saisie. Veuillez réessayer.\n");
            continue;
        }
        if (ft_strcmp(rep, "size") == 0)
        {
            printf("Entrez la taille x : ");
            if (scanf("%d", &(config->size_x)) != 1)
            {
                printf("Erreur de saisie. Veuillez réessayer.\n");
                continue;
            }
            printf("Entrez la taille y : ");
            if (scanf("%d", &(config->size_y)) != 1)
            {
                printf("Erreur de saisie. Veuillez réessayer.\n");
                continue;
            }
        }
        if (ft_strcmp(rep, "easy") == 0)
        {
            config->numb_of_pute = ((config->size_x * config->size_y) / 18);
            config->numb_of_bush = ((config->size_x * config->size_y) / 14);
            config->numb_of_smartPute = ((config->size_x * config->size_y) / 180);
            config->game_speed = 1000000 / ((config->size_x * config->size_y) / 16);
            config->smartPute_speed = 900000 / ((config->size_x * config->size_y) / 180);
            check = 1;
        }
        else if (ft_strcmp(rep, "normal") == 0)
        {
            config->numb_of_pute = ((config->size_x * config->size_y) / 14);
            config->numb_of_bush = ((config->size_x * config->size_y) / 12);
            config->numb_of_smartPute = ((config->size_x * config->size_y) / 140);
            config->game_speed = 900000 / ((config->size_x * config->size_y) / 14);
            config->smartPute_speed = 800000 / ((config->size_x * config->size_y) / 140);
            check = 1;
        }
        else if (ft_strcmp(rep, "hard") == 0)
        {
            config->numb_of_pute = ((config->size_x * config->size_y) / 12);
            config->numb_of_bush = ((config->size_x * config->size_y) / 10);
            config->numb_of_smartPute = ((config->size_x * config->size_y) / 120);
            config->game_speed = 800000 / ((config->size_x * config->size_y) / 12);
            config->smartPute_speed = 700000 / ((config->size_x * config->size_y) / 120);
            check = 1;
        }
        else if (ft_strcmp(rep, "test") == 0)
        {
            config->numb_of_pute = 3;
            config->numb_of_bush = 0;
            config->smartPute_speed = 1000000 / (5);
             config->game_speed = 800000 / (3);
            config->numb_of_smartPute = (5);
            check = 1;
        }
        int result = system("clear");
        if (result == -1)
            printf("Erreur lors de l'exécution de la commande 'clear'.\n");
    }
}

void setup_adventure_game(Game *game, Config *config)
{
    allocate_memory_and_read_file2(&game->map, &config->size_x, &config->size_y, 1, 1);
    allocate_memory_and_read_file2(&game->map_buffer, &config->size_x, &config->size_y, 1, 1);
    game->entity->player = (Player *)player_spawn(config, &game->map);
    game->prevEntity = NULL;
    game->nextEntity = NULL;
    pute_spawn(&game->map,&game->entity->pute, config);
    smartPute_spawn(&game->map,&game->entity->smartPute,config);
    initscr();
    cbreak();
    curs_set(0);
}

void setup_game(Game *game, Config *config)
{
    setup_config(config);
    if (config->is_adventure_mod)
    {
        setup_adventure_game(game, config);
    }

    else
    {
        setup_map_memory(&game->map, config);
        game->entity->player = (Player *)player_spawn(config, &game->map);
        girflfriend_spawn(&game->map, config);
        bush_spawn(&game->map, config);
        pute_spawn(&game->map, &game->entity->pute, config);
        smartPute_spawn(&game->map, &game->entity->smartPute, config);
        initscr();
        noecho();
        curs_set(0);
    }
}
