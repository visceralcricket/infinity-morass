#ifndef STORAGE_H
#define STORAGE_H

#include  <stdbool.h>

typedef struct Player Player;

// Guardar el progreso de un jugador en un archivo binario (.sav)
bool saveGame(Player *player);

bool loadGame(Player *player);

#endif