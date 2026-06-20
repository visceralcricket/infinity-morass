#ifndef OBJMAP_H
#define OBJMAP_H

#include <stdbool.h>
#include "entities.h" // Hereda automáticamente GameObject, ItemType e ItemState
#include "../tdas/hashmap.h"

typedef struct {
    const char *name;
    bool isConsumable;
    bool isKey;
} ObjectTemplate;

GameObject* generateObject(const char *name);

GameObject *spawnRandomObject(void);

void generateStatsConsumable(GameObject* object);

void generateStatsEquipabble(GameObject* object);

void generateStatsKey(GameObject* object);

#endif