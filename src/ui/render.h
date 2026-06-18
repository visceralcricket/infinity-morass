#ifndef RENDER_H
#define RENDER_H

#include "../engine/game.h"

#define MAX_SHIFT_ROW N+5
#define MAX_SHIFT_COL N+50

// Mostrar menú principal
void showMainMenu(char *username);

// Renderizar mazmorras
void renderExploration(int maze[N][N], Player player);

// Sub-menú superpuesto para los ajustes del juego
void renderSettingsOverlay();

// Sub-menú superpuesto para inventario del jugador
void renderInventoryOverlay(Player *player);

#endif