
#include  "Headers/fonctions.h"
#include  "Headers/define.h"
void print_result()
{
        FILE *fichier;
    char ligne[1000];
    fichier = fopen("result_print/loose.txt", "r");
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        printf("%s", ligne);
    }
    fclose(fichier);
}

void free_setup(Entity *entity, char **map, Config *config)
{
    Pute *pute = entity->pute;
    Pute *smartPute = entity->smartPute;
    int x = 0;

    while (pute!= NULL)
    {
        Pute *temp = pute;
        pute = pute->next;
        free(temp);
        x++;
    }
    printf("pute free : %d\n", x);

    x = 0; 
    while (smartPute!= NULL && x < config->numb_of_smartPute) 
    {
        Pute *temp = smartPute;
        smartPute = smartPute->next;
        free(temp);
        x++;
    }
    printf("smart pute free : %d\n", x);

    x = 0; 
    for (int i = 0; map[i]; i++)
    {
        free(map[i]);
        x++;
    }
    printf("check map free : %d\n", x);

    free(entity->player);
    free(entity);
    free(map);
}

int main(void)
{
    int continu = 1;
    while (continu)
    {
        char **map;
        Entity *entity = malloc(sizeof(Entity));
        Config *config = malloc(sizeof(Config));
        Result *result = malloc(sizeof(Result));
        setup_game(&map, entity, config);
        game(map, entity, config, result);
        endwin();
        if (result->check == 0)
            print_result();
        else if (result->check == 2)
            printf("Gagné, score : %f\n", result->score / 100);
        free_setup(entity, map, config);
        free(result);
        free(config);
        //printf("continue: ");
        //scanf("%d", &continu);
    }
    return 0;
}