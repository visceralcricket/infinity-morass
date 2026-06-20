#include "../tdas/list.h"
#include "../tdas/extra.h"
#include "../tdas/hashmap.h"
#include "../engine/game.h"
#include "objmap.h"

GameObject* generateObject(const char *name)
{
    GameObject *object = (GameObject*) malloc(sizeof(GameObject));
    if(!object) return NULL;

    object->x = -1;
    object->y = -1;
    object->stats.attack = -1;
    object->stats.currentHp = -1;
    object->stats.defense = -1;
    object->stats.maxHp = -1;
    object->stats.speed = -1;
    strncpy(object->name, name, MAX_OBJECT_NAME - 1);
    object->name[MAX_OBJECT_NAME - 1] = '\0';

    return object;
}

GameObject *spawnRandomObject(void) {
    int count = sizeof(objectTemplates) / sizeof(objectTemplates[0]);
    int randomIndex = rand() % count;
    const ObjectTemplate *tpl = &objectTemplates[randomIndex];

    GameObject *object = generateObject((char *)tpl->name);
    if(!object) return NULL;

    object->x = -1;
    object->y = -1;

    if(tpl->isConsumable) generateStatsConsumable(object);
    else if(tpl->isKey) generateStatsKey(object);
    else generateStatsEquipabble(object);

    return object;
}

void generateStatsConsumable(GameObject* object)
{
    if(strcmp(object->name, "Pocion pequeña") == 0) {
        object->stats.attack = 0;
        object->stats.defense = 0;
        object->stats.maxHp = 20;
        object->stats.currentHp = object->stats.maxHp;
        object->stats.speed = 0;
    }
    else if(strcmp(object->name, "Pocion mediana") == 0) {
        object->stats.attack = 0;
        object->stats.defense = 0;
        object->stats.maxHp = 50;
        object->stats.currentHp = object->stats.maxHp;
        object->stats.speed = 0;
    }
    else if(strcmp(object->name, "Pocion grande") == 0) {
        object->stats.attack = 0;
        object->stats.defense = 0;
        object->stats.maxHp = 80;
        object->stats.currentHp = object->stats.maxHp;
        object->stats.speed = 0;
    }
}

void generateStatsEquipabble(GameObject* object)
{
    if(strcmp(object->name, "Espada ligera") == 0) {
        object->stats.attack = 3;
        object->stats.defense = 0;
        object->stats.maxHp = 0;
        object->stats.currentHp = 0;
        object->stats.speed = 4;
    }
    else if(strcmp(object->name, "Espada pesada") == 0) {
        object->stats.attack = 5;
        object->stats.defense = 0;
        object->stats.maxHp = 0;
        object->stats.currentHp = 0;
        object->stats.speed = 0;
    }
    if(strcmp(object->name, "Ultra espadón") == 0) {
        object->stats.attack = 7;
        object->stats.defense = 0;
        object->stats.maxHp = 0;
        object->stats.currentHp = 0;
        object->stats.speed = -2;
    }
    else if(strcmp(object->name, "Armadura ligera") == 0) {
        object->stats.attack = 0;
        object->stats.defense = 5;
        object->stats.maxHp = 10;
        object->stats.currentHp = object->stats.maxHp;
        object->stats.speed = 2;
    }
    else if(strcmp(object->name, "Armadura pesada") == 0) {
        object->stats.attack = 0;
        object->stats.defense = 7;
        object->stats.maxHp = 14;
        object->stats.currentHp = object->stats.maxHp;
        object->stats.speed = -2;
    }
    else if(strcmp(object->name, "Armadura berserker") == 0) {
        object->stats.attack = 7;
        object->stats.defense = 0;
        object->stats.maxHp = 20;
        object->stats.currentHp = object->stats.maxHp;
        object->stats.speed = 0;
    }
}

void generateStatsKey(GameObject* object)
{
    if(strcmp(object->name, "Llave de calabozo") == 0) {
        object->stats.attack = 0;
        object->stats.defense = 0;
        object->stats.maxHp = 0;
        object->stats.currentHp = 0;
        object->stats.speed = 0;
    }
    if(strcmp(object->name, "Rollo de historia") == 0) {
        object->stats.attack = 0;
        object->stats.defense = 0;
        object->stats.maxHp = 0;
        object->stats.currentHp = 0;
        object->stats.speed = 0;
    }
}

Map *createObjectsMap(void) {
    Map *map = mapCreate();
    if(!map) return NULL;
    int count = sizeof(objectTemplates) / sizeof(objectTemplates[0]);

    for(int i=0; i < count; ++i) {
        const ObjectTemplate *tpl = &objectTemplates[i];

        GameObject *object = generateObject(tpl->name);
        if(!object) continue;

        if(tpl->isConsumable) generateStatsConsumable(object);
        else if(tpl->isKey) generateStatsKey(object);
        else generateStatsEquipabble(object);

        mapInsert(map, object->name, object);
    }
    return map;
}