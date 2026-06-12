#ifndef STORAGE_H
#define STORAGE_H

#include "game.h"
#include <stdbool.h>

// Guardar el progreso de un jugador en un archivo binario (.sav)
bool saveGame(Player *player);

/* +++
Aquí faltará una función que permita cargar cada partida mediante
su correspondiente archivo .sav
--- */

// bool loadGame(Player *player, const char *username);

#endif