#include "enmap.h"

static const EnemyTemplate enemyTemplates[] = {
    {"Zombi", false, 1},
    {"Esqueleto", false, 1},
    {"Slime", false, 1},
    {"Demonio", false, 1},
    {"Súcubo", false, 1},
    {"Goblin", false, 1},
    {"Bandolero", true, 1},
    {"Aberración Cósmica", true, 1},
    {"Gólem Antiguo", true, 1},
    {"Jefe de carrera", true, 1}
};

Enemy* generateEnemy(const char *name)
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
    enemy->drops = NULL;
    enemy->isBoss = false;
    strncpy(enemy->enemyName, name, MAX_USERNAME - 1);
    enemy->enemyName[MAX_USERNAME - 1] = '\0';

    return enemy;
}

// ==================== Selección de nombres al azar ====================

// Devuelve el nombre de un enemigo común (no jefe) al azar
const char *randomCommonName(void) {
    int count = sizeof(enemyTemplates) / sizeof(enemyTemplates[0]);
    int commonIndices[count];
    int commonCount = 0;
    for(int i = 0; i < count; i++)
        if(!enemyTemplates[i].isBoss) commonIndices[commonCount++] = i;
    if(commonCount == 0) return NULL;
    return enemyTemplates[commonIndices[rand() % commonCount]].name;
}

// Devuelve el nombre de un jefe al azar
const char *randomBossName(void) {
    int count = sizeof(enemyTemplates) / sizeof(enemyTemplates[0]);
    int bossIndices[count];
    int bossCount = 0;
    for(int i = 0; i < count; i++)
        if(enemyTemplates[i].isBoss) bossIndices[bossCount++] = i;
    if(bossCount == 0) return NULL;
    return enemyTemplates[bossIndices[rand() % bossCount]].name;
}

// ==================== Clonado ====================

/* +++
Copia un enemigo "maestro" del hashmap a una instancia nueva e independiente
para usar en combate. El maestro nunca se modifica: peleamos siempre con la copia
y liberamos sólo la copia al terminar.
OJO: drops se setea en NULL para evitar que la copia y el maestro compartan
la misma lista (aliasing). Cuando se implementen los drops del enemigo, aquí
habrá que clonar la lista, no copiar el puntero.
--- */
Enemy *cloneEnemy(const Enemy *src) {
    if(!src) return NULL;
    Enemy *copy = (Enemy*) malloc(sizeof(Enemy));
    if(!copy) return NULL;
    *copy = *src;                                          // copia stats, nombre, x, y
    copy->combatStats.currentHp = copy->combatStats.maxHp; // HP lleno al spawnear
    copy->drops = NULL;                                    // evitar aliasing de la lista
    return copy;
}

// ==================== Spawn desde el hashmap ====================

Enemy *spawnEnemyFromMap(Map *enemyMap) {
    if(!enemyMap) return NULL;
    const char *name = randomCommonName();
    if(!name) return NULL;

    MapPair *pair = mapSearch(enemyMap, (char*)name);
    if(!pair) return NULL;

    Enemy *master = (Enemy*) pair->value;
    Enemy *copy = cloneEnemy(master);
    if(copy) copy->isBoss = false;
    return copy;
}

Enemy *spawnBossFromMap(Map *enemyMap) {
    if(!enemyMap) return NULL;
    const char *name = randomBossName();
    if(!name) return NULL;

    MapPair *pair = mapSearch(enemyMap, (char*)name);
    if(!pair) return NULL;

    Enemy *master = (Enemy*) pair->value;
    Enemy *boss = cloneEnemy(master);
    if(boss) boss->isBoss = true;
    return boss;
}

// ==================== Generación de stats ====================

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
    else if(strcmp(enemy->enemyName, "Súcubo") == 0) {
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
    else if(strcmp(enemy->enemyName, "Aberración Cósmica") == 0) {
        enemy->combatStats.attack    = 9 * difficulty;
        enemy->combatStats.defense   = 13 * difficulty;
        enemy->combatStats.maxHp     = 40 * difficulty;
        enemy->combatStats.currentHp = enemy->combatStats.maxHp;
        enemy->combatStats.speed     = 4 * difficulty;
    }
    else if(strcmp(enemy->enemyName, "Gólem Antiguo") == 0) { // palabras de androide 16
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

// ==================== Construcción del hashmap maestro ====================

Map *createEnemiesMap(void) {
    Map *map = mapCreate();
    if(!map) return NULL;
    int count = sizeof(enemyTemplates) / sizeof(enemyTemplates[0]);

    for(int i=0; i < count; ++i) {
        const EnemyTemplate *tpl = &enemyTemplates[i];

        Enemy *enemy = generateEnemy((char *)tpl->name);
        if(!enemy) continue;

        if(tpl->isBoss) generateStatsBossEnemy(enemy, tpl->difficulty);
        else generateStatsCommonEnemy(enemy, tpl->difficulty);

        mapInsert(map, enemy->enemyName, enemy);
    }
    return map;
}