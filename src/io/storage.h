#ifndef STORAGE_H
#define STORAGE_H

#include <stdbool.h>
#include "../engine/entities.h"

typedef struct Player Player;

// Guardar el progreso de un jugador en un archivo binario (.sav)
bool saveGame(Player *player, sessionFloor *currentSession);

bool loadGame(Player *player, sessionFloor *currentSession);

#endif