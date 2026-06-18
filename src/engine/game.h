#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> // Necesario para identificadores/flags
#include <string.h>
// #include <ctype.h>
#include <limits.h> // Necessary for using INF (infinity)
#include "../tdas/list.h"
#include "../tdas/extra.h"
#include "../tdas/hashmap.h"
// #include "tdas/heap.h"

// ======== General definitions ========
#define INF INT_MAX
#define INT_ERROR -1
#define MAX_ID 30
#define MAX_USERNAME 20
#define MAX_FILENAME (MAX_USERNAME+15)
#define MAX_OBJECT_NAME 25
#define MAX_LORE_LENGTH 256
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

typedef enum {
    ITEM_CONSUMABLE,
    ITEM_EQUIPPABLE,
    ITEM_KEY
} ItemType;

typedef enum {
    OBJECT_MAP,
    OBJECT_INVENTORY
} ItemState;

// Structures' definitions
typedef struct State State;
typedef struct Stats Stats;
typedef struct GameObject GameObject;
typedef struct Enemy Enemy;
typedef struct Player Player;
// Estructura para guardar progreso del jugador o jugadores
// typedef struct PlayerData PlayerData;

// El laberinto comienza desde la esquina SUPERIOR-IZQUIERDA (UPPER-LEFT), considerar
// cambiar esto a un inicio generado aleatoriamente
 struct State {
    int currentRow; // modifies "y" axis
    int currentColumn; // modifies "x" axis
    // int accumulated; // Real cost (g) of moves
    State *parent; // Pointer to predecessor state
};

struct Stats {
    // int level <- Considerar añadir esta mecánica
    int currentHp, maxHp, speed, attack, defense;
};

struct GameObject {
    char name[MAX_OBJECT_NAME];
    int x, y;
    Stats stats;
    char lore[MAX_LORE_LENGTH];
    ItemType equip;
    ItemState state;

    union 
    {
        struct { int x, y; };    // si está en el mapa
        struct { int slot; };    // si está en inventario
    } pos;
    
};

struct Enemy {
    int x, y;
    Stats combatStats;
    List *drops;
    char enemyName[MAX_USERNAME];
};

struct Player {
    char username[MAX_USERNAME];
    int x, y;
    Stats combatStats;
    List *inventory;
};

/*
struct PlayerData {
    // char username[MAX_USERNAME];
    State *currentState;
    Player *player;
    int level, floor;
};
*/

// ==================== Prototypes ====================

// Reduce code-writing in cleaning Lists (like garbageCollector) that store data of the type State
void cleanGarbage(List *states);

// Implicit-graph functions
int isFinal(State *currentState, int targetRow, int targetColumn);
State *createNewState();
State *transition(State *currentState, Action accion);
List *getAdjacentNodes(State *currentState, int maze[N][N]);

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