#ifndef RENDER_H
#define RENDER_H

#include "../engine/entities.h"
#include "../tdas/extra.h"
#include "../tdas/hashmap.h"
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

// Pantalla de lectura de un pergamino (muestra su lore con saltos de línea)
void renderScrollOverlay(GameObject *scroll);

// Sub-menu superpuesto para el combate
void renderCombatOverlay(Player *player, Enemy *enemy, void *currentTurn, int turnCounter, bool *fleeCondition);

void renderGameOverScreen(const char *killerName);

void showGlossary(Map *objectMap, Map *enemyMap);

#endif