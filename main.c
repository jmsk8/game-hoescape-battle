
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
int main(void)
{
    char **map = NULL;
    int check;
    Entity *entity = malloc(sizeof(Entity));
    Config *config = malloc(sizeof(Config));
    Result *result = malloc(sizeof(Result));
    setup_game(&map, entity, config);
    game(map, entity, config, result);
    if (result->check == 0)
        print_result();
    else if (result->check == 2)
        printf("gagné, score : %f\n", result->score);
    free(map);
    free(entity);
    free(config);

    return 0;
}