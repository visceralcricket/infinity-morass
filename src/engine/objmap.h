#ifndef OBJMAP_H
#define OBJMAP_H

#include <stdbool.h>
#include "entities.h" // Hereda automáticamente GameObject, ItemType e ItemState
#include "../tdas/hashmap.h"

typedef struct {
    const char *name;
    bool isConsumable;
    bool isEquippable;
    EquipSlot slot;   // Slot de equipo: SLOT_WEAPON, SLOT_ARMOR o SLOT_NONE
} ObjectTemplate;

Map *createObjectsMap(void);

GameObject* generateObject(const char *name);

GameObject *chooseRandomObject(void);

GameObject *chooseRandomPotion(void);

// Drop de jefe: devuelve un pergamino de historia al azar (objeto tipo ITEM_KEY con lore)
GameObject *chooseRandomScroll(void);

void generateStatsConsumable(GameObject* object);

void generateStatsEquipabble(GameObject* object);

#endif