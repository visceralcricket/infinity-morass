#ifndef RENDER_H
#define RENDER_H

#include "../engine/game.h"

// Mostrar menú principal
void showMainMenu(char *username);

// Renderizar mazmorras
void renderExploration(int maze[N][N], Player player);

#endif