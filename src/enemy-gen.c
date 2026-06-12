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
    float mult;


    switch(difficulty) 
    {
    case 1: mult = 0.80f; break;

    case 2: mult = 1.0f;  break;

    case 3: mult = 2.0f;  break;
    
    default: mult = 1.0f; break;
    }              mult = 2.0f;



    if(strcmp(enemy->enemyName, "Zombi") == 0) {
        enemy->combatStats.attack  = 2;
        enemy->combatStats.defense = 4;
        enemy->combatStats.maxHp   = 12;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed   = 2;
    }
    else if(strcmp(enemy->enemyName, "Esquelo") == 0) {
        enemy->combatStats.attack  = 4;
        enemy->combatStats.defense = 0;
        enemy->combatStats.maxHp   = 8;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed   = 5;
    }
    else if(strcmp(enemy->enemyName, "Slime") == 0) {
        enemy->combatStats.attack  = 1;
        enemy->combatStats.defense = 2;
        enemy->combatStats.maxHp   = 35;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed   = 1;
    }
    else if(strcmp(enemy->enemyName, "Demonio") == 0) {
        enemy->combatStats.attack  = 6;
        enemy->combatStats.defense = 6;
        enemy->combatStats.maxHp   = 6;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed   = 6;
    }
    else if(strcmp(enemy->enemyName, "Sucubo") == 0) {
        enemy->combatStats.attack  = 10;
        enemy->combatStats.defense = 0;
        enemy->combatStats.maxHp   = 5;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed   = 10;
    }
    else if(strcmp(enemy->enemyName, "Goblin") == 0) {
        enemy->combatStats.attack  = 2;
        enemy->combatStats.defense = 2;
        enemy->combatStats.maxHp   = 2;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed   = 2;
    }
}


// dificultad 1-3
// ["Zombi", "Esquelo", "Slime", "Demonio", "Sucubo", "Goblin"]
