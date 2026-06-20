#ifndef ENEMYGEN_H
#define ENEMYGEN_H

#include "entities.h"
#include "../tdas/hashmap.h"

typedef struct {
    const char *name;
    bool isBoss;
    int difficulty;
} EnemyTemplate;

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