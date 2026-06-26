#ifndef COMBAT_H
#define COMBAT_H

/* +++
Utilizar 1000 directamente en la fórmula matemática para la prioridad de cada
combatiente lo hace ver como un número mágico, por ende es mejor hacer uso de
un macro de tal forma que también disminuya la necesidad de repetir código.
--- */
#define BASE_TURN_TICKS 1000

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "../ui/render.h"
#include "objmap.h"

void combatMode(Player *player, Enemy *enemy);

#endif