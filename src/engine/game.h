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
#define N 25 // <- Maze's fixed size
#define MAX_NUM_EXITS 2 // Máximo 2 salidas por mazmorra
#define MAX_ENEMIES_PER_DUNGEON 5

// ======== Maze symbols ========
#define WALL '#' // Obstacle
#define EMPTY ' ' // Empty/free tile
#define PATH '.' // Path for the agent
#define START 'I' // Starting position of the agent
#define GOAL 'M' // Goal tile
#define ENEMY_TILE 'E'
#define EXIT_TILE 2

// ======== Menu modes enum structure ========

typedef enum {
    MODE_MAIN_MENU = 0,
    MODE_EXPLORATION,
    MODE_SETTINGS,
    MODE_INVENTORY_VIEW,
    MODE_COMBAT
} GameMode;

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

// Estructura simple para enumerar movimientos/acciones
typedef enum {
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
} Action;

// Structures' definitions
typedef struct State State;

// El laberinto comienza desde la esquina SUPERIOR-IZQUIERDA (UPPER-LEFT), considerar
// cambiar esto a un inicio generado aleatoriamente
 struct State {
    int currentRow; // modifies "y" axis
    int currentColumn; // modifies "x" axis
    State *parent; // Pointer to predecessor state
};

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

// ==================== Input handlers ====================
void handleWindowsInput(Player *player, int maze[N][N], GameMode *currentSubMode);
void handleSettingsInput(Player *player, bool *playing, GameMode *currentSubMode);
void handleInventoryInput(Player *player, GameMode *currentSubMode);

#include "enmap.h"

#endif