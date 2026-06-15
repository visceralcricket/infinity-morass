#include "../tdas/list.h"
#include "../tdas/extra.h"
#include "../tdas/hashmap.h"

#include "../engine/game.h"

// crear objetos
/*
GameObject* generateObject(char name[MAX_OBJECT_NAME], char lore[])
{

}
*/


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
    if(strcmp(enemy->enemyName, "Zombi") == 0) {
        enemy->combatStats.attack    = 2  * difficulty;
        enemy->combatStats.defense   = 4  * difficulty;
        enemy->combatStats.maxHp     = 12 * difficulty;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed     = 2  * difficulty;
    }
    else if(strcmp(enemy->enemyName, "Esqueleto") == 0) {
        enemy->combatStats.attack    = 4 * difficulty;
        enemy->combatStats.defense   = 0 * difficulty;
        enemy->combatStats.maxHp     = 8 * difficulty;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed     = 5 * difficulty;
    }
    else if(strcmp(enemy->enemyName, "Slime") == 0) {
        enemy->combatStats.attack    = 1  * difficulty;
        enemy->combatStats.defense   = 2  * difficulty;
        enemy->combatStats.maxHp     = 35 * difficulty;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed     = 1  * difficulty;
    }
    else if(strcmp(enemy->enemyName, "Demonio") == 0) {
        enemy->combatStats.attack    = 6 * difficulty;
        enemy->combatStats.defense   = 6 * difficulty;
        enemy->combatStats.maxHp     = 6 * difficulty;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed     = 6 * difficulty;
    }
    else if(strcmp(enemy->enemyName, "Sucubo") == 0) {
        enemy->combatStats.attack    = 10 * difficulty;
        enemy->combatStats.defense   = 0  * difficulty;
        enemy->combatStats.maxHp     = 5  * difficulty;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed     = 10 * difficulty;
    }
    else if(strcmp(enemy->enemyName, "Goblin") == 0) {
        enemy->combatStats.attack    = 2 * difficulty;
        enemy->combatStats.defense   = 2 * difficulty;
        enemy->combatStats.maxHp     = 2 * difficulty;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed     = 2 * difficulty;
    }
}

void generateStatsBossEnemy(Enemy* enemy, int difficulty)
{
    if(strcmp(enemy->enemyName, "Bandolero") == 0) {
        enemy->combatStats.attack    = 12 * difficulty;
        enemy->combatStats.defense   = 4 * difficulty;
        enemy->combatStats.maxHp     = 18 * difficulty;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed     = 14 * difficulty;
    }
    else if(strcmp(enemy->enemyName, "Aberracion Cosmica") == 0) {
        enemy->combatStats.attack    = 9 * difficulty;
        enemy->combatStats.defense   = 13 * difficulty;
        enemy->combatStats.maxHp     = 40 * difficulty;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed     = 4 * difficulty;
    }
    else if(strcmp(enemy->enemyName, "Robot Antiguo") == 0) { // palabras de androide 16
        enemy->combatStats.attack    = 14 * difficulty;
        enemy->combatStats.defense   = 6 * difficulty;
        enemy->combatStats.maxHp     = 30 * difficulty;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed     = 1 * difficulty;
    }
    else if(strcmp(enemy->enemyName, "Jefe de carrera") == 0) { // te manda a repetir el semestre, fallas 2 muerte instantanea, si aciertas 5 pasas
        enemy->combatStats.attack    = 99 * difficulty;
        enemy->combatStats.defense   = 99 * difficulty;
        enemy->combatStats.maxHp     = 99* difficulty;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed     = 99 * difficulty;
    }
}




