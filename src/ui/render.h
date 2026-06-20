#ifndef RENDER_H
#define RENDER_H

#include "../engine/game.h"
/*
#define MAX_SHIFT_ROW N+5
#define MAX_SHIFT_COL N+50
*/
#define OVERLAY_ROW 5
#define OVERLAY_COL 75

// Mostrar menú principal
void showMainMenu(char *username);

// Renderizar mazmorras
void renderExploration(int maze[N][N], Player player);

// Sub-menú superpuesto para los ajustes del juego
void renderSettingsOverlay();

// Sub-menú superpuesto para inventario del jugador
void renderInventoryOverlay(Player *player);

// Sub-menu superpuesto para el combate
void renderCombatOverlay(Player *player, Enemy *enemy, void *currentTurn, int turnCounter, bool *fleeCondition);

#endif