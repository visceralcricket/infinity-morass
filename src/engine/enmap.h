#ifndef ENEMYGEN_H
#define ENEMYGEN_H
/*
Sólo incluir encabezado del motor principal del juego. Sólo es necesario
hacer #include "game.h" y no "../engine/game.h" porque los archivos game y
combat-system se encuentran en la misma carpeta
*/

#include "../engine/game.h"

typedef struct {
    const char *name;
    bool isBoss;
    int difficulty;
} EnemyTemplate;

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

// Función para generar el nodo de la entidad Enemy
Enemy* generateEnemy(const char *name);

Enemy *spawnRandomEnemy(void);

// Función para comenzar a crear manualmente los enemigos y sus stats
void generateStatsCommonEnemy(Enemy* enemy, int difficulty);

void generateStatsBossEnemy(Enemy* enemy, int difficulty);

// Función para comenzar a mapear los enemigos por una plantilla general e
// insertarlos dentro del mapa de enemigos
Map *createEnemiesMap(void);

#endif