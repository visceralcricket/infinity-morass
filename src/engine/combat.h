#ifndef COMBAT_H
#define COMBAT_H
#include "objmap.h"

typedef struct Player Player;
typedef struct Enemy Enemy;

void combatMode(Player *player, Enemy *enemy);

/* +++
void showCombat(Player *player, Enemy *enemy, void *currentTurn, int turnCounter, bool *fleeCondition);
Esta función de aquí tiene que ver más con render que con lógica procedural de combat-system.
La moví a render.c; recordar NO usar números mágicos como startRow = 5 y 
startCol = 75, revisar render.h, ahí creé macros para los submenús superpuestos (como ajustes)
--- */

void freeGameObject(void *p);


#endif