#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> // Necesario para identificadores/flags
// #include <string.h>
// #include <ctype.h>
#include <limits.h> // Necessary for using INF (infinity)
#include "tdas/list.h"
#include "tdas/extra.h"
#include "tdas/hashmap.h"
#include "tdas/heap.h"

// ======== General definitions ========
#define INF INT_MAX
#define INT_ERROR -1
#define MAX_ID 30

// ======== Maze symbols ========
#define WALL '#' // Obstacle
#define EMPTY ' ' // Empty/free tile
#define PATH '.' // Path for the agent
#define START 'I' // Starting position of the agent
#define GOAL 'M' // Goal tile

// ======== Menu modes ========
#define MAIN_MENU 0
#define EXPLORATION_MODE 1
#define MAP_VIEW 2
#define INVENTORY_VIEW 3
#define COMBAT_MODE 4
#define SETTINGS_MODE 5

// ======== Gameplay inputs ========
#define ESC_KEY 27
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77

// Estructura simple para enumerar movimientos/acciones
typedef enum {
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
} Action;

// Structures' definitions
typedef struct State State;
typedef struct Stats Stats;
typedef struct Enemy Enemy;
typedef struct Player Player;


// ==================== Prototypes ====================

// Reduce code-writing in cleaning Lists (like garbageCollector) that store data of the type State
void cleanGarbage(List *states);

// Implicit-graph functions
int isFinal(State *currentState, int targetRow, int targetColumn);
State *createNewState();
State *transition(State *currentState, Action accion);
List *getAdjacentNodes(State *currentState, int maze[N][N], int targetRow, int targetColumn);

// Format, aka output/input functions
void manejarInputWindows();

#endif