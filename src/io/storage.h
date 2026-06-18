#ifndef STORAGE_H
#define STORAGE_H

#include "../engine/game.h"
#include <stdbool.h>

// Guardar el progreso de un jugador en un archivo binario (.sav)
bool saveGame(Player *player);

bool loadGame(Player *player);

#endif