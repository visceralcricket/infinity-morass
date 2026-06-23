#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> // Necesario para identificadores/flags
#include <string.h>
// #include <ctype.h>
#include <limits.h> // Necessary for using INF (infinity)

#include "../tdas/extra.h"
#include "entities.h"

// ======== General definitions ========
#define INF INT_MAX
#define INT_ERROR -1
#define MAX_FILENAME (MAX_USERNAME+15)
#define MAX_NUM_EXITS 2 // Máximo 2 salidas por mazmorra

// ======== Gameplay inputs ========
#define ESC_KEY 27

// ======== Arrow keys ========
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77

// ======== WASD key codes ========
#define W_KEY_UPPER 87
#define W_KEY_LOWER 119
#define A_KEY_UPPER 65
#define A_KEY_LOWER 97
#define S_KEY_UPPER 83
#define S_KEY_LOWER 115
#define D_KEY_UPPER 68
#define D_KEY_LOWER 100

// Estructura para poder almacenar el mapa actual con el sistema de guardado de partidas

// ==================== Prototypes ====================
// Función recursiva BSF para construir un camino seguro
int buildSafePath(int x, int y, int safe[N][N], int visited[N][N]);

// Maze-handling functions
void generateMaze(int maze[N][N], int difficulty);
void placeExits(int maze[N][N], int numExits);
/* +++
Esta función se verá de la siguiente forma en el futuro:
void placeEnemies(int maze[N][N], Map *enemyMap, List *spawnedEnemies);
Pero por fines prácticos se van a ignorar los últimos 2 parámetros.
--- */
void placeEnemies(int maze[N][N]);
void placeObjects(int maze[N][N]);

// ==================== Input handlers ====================
void handleWindowsInput(Player *player, int maze[N][N], GameMode *currentSubMode, Enemy **currentEnemy);
void handleSettingsInput(Player *player, bool *playing, GameMode *currentSubMode, sessionFloor *currentSession);
void handleInventoryInput(Player *player, GameMode *currentSubMode);

#include "enmap.h"

#endif