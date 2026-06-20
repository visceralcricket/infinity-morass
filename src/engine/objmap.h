#ifndef OBJMAP_H
#define OBJMAP_H


typedef struct {
    const char *name;
    bool isConsumable;
    bool isKey;
} ObjectTemplate;

static const ObjectTemplate objectTemplates[] = {
    {"Poción pequeña", true, false},
    {"Poción mediana", true, false},
    {"Poción grande", true, false},
    {"Espada ligera", false, false},
    {"Espada pesada", false, false},
    {"Ultra espadón", false, false},
    {"Armadura ligera", false, false},
    {"Armadura pesada", false, false},
    {"Armadura berserker", false, false},
    {"Llave de calabozo", false, true},
    {"Rollo de historia", false, true}
};

GameObject* generateObject(const char *name);

GameObject *spawnRandomObject(void);

void generateStatsConsumable(GameObject* object);

void generateStatsEquipabble(GameObject* object);

void generateStatsKey(GameObject* object);

#endif