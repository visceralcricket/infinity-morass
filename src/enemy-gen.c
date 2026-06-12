#include <limits.h> // Necessary for using INF (infinity)
#include "tdas/list.h"
#include "tdas/extra.h"
#include "tdas/hashmap.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> // Necesario para identificadores/flags
#include <string.h>
#include "game.h"



#define INF INT_MAX
#define INT_ERROR -1
#define MAX_ID 30
#define MAX_USERNAME 20
#define MAX_OBJECT_NAME 25
#define MAX_LORE_LENGTH 256
#define N 30 // <- Maze's fixed size

Enemy* generateEnemy(char name[MAX_USERNAME])
{
    Enemy *enemy = (Enemy*) malloc(sizeof(Enemy));
    if(!enemy) return NULL;

    enemy->x = -1;
    enemy->y = -1;
    enemy->combatStats.attack = -1;
    enemy->combatStats.currentHp = -1;
    enemy->combatStats.defense = -1;
    enemy->combatStats.maxHp = -1;
    enemy->combatStats.speed = -1;
    strncpy(enemy->enemyName, name, MAX_USERNAME - 1);
    enemy->enemyName[MAX_USERNAME - 1] = '\0';

    return enemy;
}

void generateStatsCommonEnemy(Enemy* enemy, int difficulty)
{

}

//
// ["Zombi", "Esquelo", "Pipe"]
