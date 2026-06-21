#ifndef ENTITIES_H
#define ENTITIES_H

#include <stdbool.h>
#include "../tdas/list.h"

// ======== Límites de memoria ========
#define MAX_ID 30
#define MAX_USERNAME 20
#define MAX_OBJECT_NAME 25
#define MAX_LORE_LENGTH 256

// ======== Enumeraciones ========
typedef enum {
    ITEM_CONSUMABLE = 0,
    ITEM_EQUIPPABLE,
    ITEM_KEY
} ItemType;

typedef enum {
    OBJECT_MAP = 0,
    OBJECT_INVENTORY
} ItemState;

typedef struct Stats Stats;
typedef struct GameObject GameObject;
typedef struct Enemy Enemy;
typedef struct Player Player;

// ======== Estructuras ========
struct Stats {
    // int level <- Considerar añadir esta mecánica
    int currentHp, maxHp, speed, attack, defense;
};

struct GameObject {
    char name[MAX_OBJECT_NAME];
    int x, y;
    Stats stats;
    char lore[MAX_LORE_LENGTH];
    ItemState state;
    ItemType equip;
    
    union 
    {
        struct { int x, y; };    // si está en el mapa
        struct { int slot; };    // si está en inventario
    } pos;  
};

struct Enemy {
    char enemyName[MAX_USERNAME];
    int x, y;
    Stats combatStats;
    List *drops;
};

struct Player {
    char username[MAX_USERNAME];
    int x, y;
    Stats combatStats;
    List *inventory;
};

#endif