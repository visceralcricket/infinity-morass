#ifndef COMBAT_SYSTEM_H
#define COMBAT_SYSTEM_H
#include "game.h"

void combatMode(Player *player, Enemy *enemy);


void showCombat(Player *player, Enemy *enemy, void *currentTurn, int turnCounter, bool *fleeCondition);
#endif