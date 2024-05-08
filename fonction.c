#include  "Headers/fonctions.h"
#include  "Headers/define.h"

int ft_strcmp(char *s1, char*s2)
{
    while (*s1 ==*s2 && *s1)
    {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

struct Pute *creatPute (int x, int y, int id)
{
  Pute *newPute = malloc (sizeof (Pute));
  newPute->coord_x = x;
  newPute->coord_y = y;
  newPute->id = id;
  newPute->next = NULL;
  return newPute;
}

void pushPute (Pute **head, int x, int y, int id)
{
  Pute *newpute = creatPute (x, y, id);
  newpute->is_alive = 1;
  if (*head == NULL)
	{
	  *head = newpute;
	  return;
	}
  Pute *current = *head;
  while (current->next != NULL)
	{
	  current = current->next;
	}
  current->next = newpute;
}

void coord_generator(char ***map, int *x, int *y, Config *config)
{
  srand (time (NULL));
  do
	{
	  *x = rand () %  (config->size_x - 2) + 1;		
	  *y = rand () % (config->size_y - 2) + 1;
	}
  while ((*map)[*x][*y] != ' ');
}

int check(char c, int is_player)
{
  if (is_player)
  {
    if (c == BUSH || c == MAP_LIMITE)
      return 1;
    return 0;
  }
  else
  {
    if (c == PUTE || c == MAP_LIMITE || c == SAFE_ZONE || c == SMART_PUTE || c == SMART_PUTE || c == AMMO)
      return 1;
    else if (c == BUSH)
      return 2;
  }
  return 0;
}

void case_move(char ***map, int *x, int *y, int direction, int is_col)
{
    int tmp = 0;

    if (is_col)
    {
        direction ? ++(*x) : --(*x); 
        if (check((*map)[*x][*y], 0) == 1)
        {
            direction ? --(*x) : ++(*x); 
        }
        else if (check((*map)[*x][*y], 0) == 2)
        {
            while (check((*map)[*x][*y], 0) == 2)
            {
                direction ? ++(*x) : --(*x); 
                tmp++;
                if (check((*map)[*x][*y], 0) == 1)
                {
                    direction ? (*x -= (tmp + 1)) : (*x += (tmp + 1)); 
                }
            }
        }
    }
    else
    {
        
        direction ? --(*y) : ++(*y); 
        if (check((*map)[*x][*y], 0) == 1)
        {
            direction ? ++(*y) : --(*y);
        }
        else if (check((*map)[*x][*y], 0) == 2)
        {
            while (check((*map)[*x][*y], 0) == 2)
            {
                direction ? --(*y) : ++(*y); 
                tmp++;
                if (check((*map)[*x][*y], 0) == 1)
                {
                    direction ? (*y += (tmp + 1)) : (*y -= (tmp + 1)); 
                }
            }
        }
    }
}

void player_shotgun(Player *player, char ***map, int ch)
{
    int bullet = 1;
    switch (ch)
    {
    case '8':
        if ((!check((*map)[player->coord_x - 1][player->coord_y], 1)))
        {
            while (bullet < 3)
            {
                if (bullet == 2 && (!(check((*map)[player->coord_x - 2][player->coord_y], 1))))
                {
                    (*map)[player->coord_x - bullet][player->coord_y] = BULLET;
                    if ((!check((*map)[player->coord_x - 2][player->coord_y + 1], 1)))
                        (*map)[player->coord_x - bullet][player->coord_y + 1] = BULLET;
                    if ((!check((*map)[player->coord_x - 2][player->coord_y - 1], 1)))
                        (*map)[player->coord_x - bullet][player->coord_y - 1] = BULLET;
                }
                else if ((!check((*map)[player->coord_x - bullet][player->coord_y], 1)))
                    (*map)[player->coord_x - bullet][player->coord_y] = BULLET;
                bullet++;
            }
        }
        break;
    case '5':
        if ((!check((*map)[player->coord_x + 1][player->coord_y], 1)))
        {
            while (bullet < 3)
            {
                if (bullet == 2 && (!(check((*map)[player->coord_x + 2][player->coord_y], 1))))
                {
                    (*map)[player->coord_x + bullet][player->coord_y] = BULLET;
                    if ((!check((*map)[player->coord_x + 2][player->coord_y + 1], 1)))
                        (*map)[player->coord_x + bullet][player->coord_y + 1] = BULLET;
                    if ((!check((*map)[player->coord_x + 2][player->coord_y - 1], 1)))
                        (*map)[player->coord_x + bullet][player->coord_y - 1] = BULLET;
                }
                else if ((!check((*map)[player->coord_x + bullet][player->coord_y], 1)))
                    (*map)[player->coord_x + bullet][player->coord_y] = BULLET;
                bullet++;
            }
        }
        break;
    case '4':
        if ((!check((*map)[player->coord_x][player->coord_y - bullet], 1)))
        {
            while (bullet < 3)
            {
                if (bullet == 2 && (!(check((*map)[player->coord_x][player->coord_y - bullet], 1))))
                {
                    (*map)[player->coord_x][player->coord_y - bullet] = BULLET;
                    if ((!check((*map)[player->coord_x + 1][player->coord_y - bullet], 1)))
                        (*map)[player->coord_x + 1][player->coord_y - bullet] = BULLET;
                    if ((!check((*map)[player->coord_x - 1][player->coord_y - bullet], 1)))
                        (*map)[player->coord_x - 1][player->coord_y - bullet] = BULLET;
                }
                else if ((!check((*map)[player->coord_x][player->coord_y - bullet], 1)))
                    (*map)[player->coord_x][player->coord_y - bullet] = BULLET;
                bullet++;
            }
        }
        break;
    case '6':
        if ((!check((*map)[player->coord_x][player->coord_y + bullet], 1)))
        {
            while (bullet < 3)
            {
                if (bullet == 2 && (!(check((*map)[player->coord_x][player->coord_y + bullet], 1))))
                {
                    (*map)[player->coord_x][player->coord_y + bullet] = BULLET;
                    if ((!check((*map)[player->coord_x + 1][player->coord_y + bullet], 1)))
                        (*map)[player->coord_x + 1][player->coord_y + bullet] = BULLET;
                    if ((!check((*map)[player->coord_x - 1][player->coord_y + bullet], 1)))
                        (*map)[player->coord_x - 1][player->coord_y + bullet] = BULLET;
                }
                else if ((!check((*map)[player->coord_x][player->coord_y + bullet], 1)))
                    (*map)[player->coord_x][player->coord_y + bullet] = BULLET;
                bullet++;
            }
        }
        break;
    }
}

int target_tracking(Pute *smartPute, Player *target)
{
    int direction = 0;
    int x;
    int y;
    int tx;
    int ty;

    x = smartPute->coord_x;
    y = smartPute->coord_y;
    tx = target->coord_x;
    ty = target->coord_y;
    srand( time( NULL ) );
    if (y <= ty && x == tx)
        direction = 2;
    else if (y >= ty && x == tx)
        direction = 4;
    else if (y == ty && x <= tx)
        direction = 3;
    else if (y == ty && x >= tx)
        direction = 1;
    else if (y <= ty && x >= tx)
        direction = rand() % 2 + 1; // 1 ou 2 en haut a droite
    else if (y >= ty && x >= tx)
        direction = rand() % 2 + 4;  // 4 ou 5 en haut a gauche
    else if (y >= ty && x <= tx)
        direction = rand() % 2 + 3;  //3 ou 4 en bas a gauche
    else if (y <= ty && x <= tx)
        direction = rand() % 2 + 2;  //2 ou 3 en bas a droite

        //1 = haut x--
        //2 =gauche  y-- 
        // 3 = bas x++
        //4 = droite y++
        
    return (direction);
}

int find_target(Pute *smartPute, Player *player)
{
    int sum = 0;
    sum += abs(smartPute->coord_x - player->coord_x);
    sum += abs(smartPute->coord_y - player->coord_y);
    return (sum);
}