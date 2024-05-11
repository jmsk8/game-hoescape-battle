
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
    while (continu == 1)
    {
        char **map = NULL;
        Entity *entity = malloc(sizeof(Entity));
        entity->pute = NULL;
        entity->smartPute = NULL;
        Config *config = malloc(sizeof(Config));
        Result *result = malloc(sizeof(Result));
        setup_game(&map, entity, config);
        game(map, entity, config, result);
        if (result->check == 0)
            print_result();
        else if (result->check == 2)
            printf("Gagné, score : %f\n", result->score / 100);
        free_setup(entity, map, config);
        free(result);
        free(config);
        printf("1 pour restart, 0 pour quitter ");
        scanf("%d", &continu);
    }
    return 0;
}
