
#include  "Headers/fonctions.h"
#include  "Headers/define.h"

void print_result()
{
        FILE *fichier;
    char ligne[1000];
    fichier = fopen("result_print/loose.txt", "r");
    printf("\033[2J\033[1;1H");
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        printf("%s", ligne);
    }
    fclose(fichier);
}

void free_setup(Entity *entity, char **map, Config *config)
{
    Pute *pute = entity->pute;
    Pute *smartPute = entity->smartPute;

    while (pute!= NULL)
    {
        Pute *temp = pute;
        pute = pute->next;
        free(temp);
    }
    while (smartPute!= NULL) 
    {
        Pute *temp = smartPute;
        smartPute = smartPute->next;
        free(temp);
    }
    for (int i = 0; map[i]; i++)
    {
        free(map[i]);
    }
    free(entity->player);
    free(entity);
    free(map);
}

int main(void)
{
    int continu = 1;
    srand(time(NULL));
    while (continu == 1)
    {
        Game *game = malloc(sizeof(Game));
        game->entity = malloc(sizeof(Entity));
        game->map = NULL;
        game->entity->pute = NULL;
        //game->entity->pute->next = NULL;
        game->entity->smartPute = NULL;
        //game->entity->smartPute->next = NULL;
        game->map_buffer = NULL;
        game->nextEntity = NULL;
        game->prevEntity = NULL;
        Config *config = malloc(sizeof(Config));
        Result *result = malloc(sizeof(Result));
        setup_game(game, config);
        if (config->is_adventure_mod)
        {
            adventur_game(game, config, result);
        }
        else 
            normal_game(game, config, result);
        printf("\033[2J\033[1;1H");
        if (result->check == -1)
            print_result();
        else if (result->check == 0)
            printf("Gagné, score : %f\n", result->score / 100);
        free_setup(game->entity, game->map, config);
        free(game);
        free(result);
        free(config);
        usleep(1000000);
        printf("1 pour restart, 0 pour quitter ");
        scanf("%d", &continu);
    }
    return 0;
}
