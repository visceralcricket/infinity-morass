#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> // Necesario para identificadores/flags
#include <string.h>
#include <limits.h> // Necesario para usar INF (infinity)

#include "../tdas/extra.h"
#include "entities.h"
#include "../tdas/hashmap.h" 

// ======== Definiciones generales ========
#define INF INT_MAX
#define INT_ERROR -1
#define MAX_FILENAME (MAX_USERNAME+15)
#define MAX_NUM_EXITS 2 // Máximo 2 salidas por mazmorra

// ======== Gameplay inputs ========
#define ESC_KEY 27

// ======== WASD key codes ========
// Sólo en minúsculas porque las normalizamos en las funciones de manejo de input
#define W_KEY_LOWER 119
#define A_KEY_LOWER 97
#define S_KEY_LOWER 115
#define D_KEY_LOWER 100

// ==================== Prototipos ====================

// Función recursiva DSF para construir un camino seguro
int buildSafePath(int x, int y, int safe[N][N], int visited[N][N]);

// ========== Funciones relacinadas con poblar la mazmorra ========== 
// Esta función utiliza el algoritmo DSF para comenzar a poblar el mapa con obstáculos
void generateMaze(int maze[N][N], int difficulty);
// Esta función coloca salidas al siguiente nivel de forma aleatoria
void placeExits(int maze[N][N], int numExits);
/* +++
Estas funciones idealmente deberían verse de la siguiente forma:
void placeEntity(int maze[N][N], Map *entityMap, List *spawnedEntities);
lo cual permitiría trackear y mantener la persistencia de los enemigos
tanto durante el gameplay como a la hora de guardar la partida, pero
por fines prácticos y limitaciones de tiempo se va a dejar así.
--- */
void placeEnemies(int maze[N][N], int floorCount);
void placeObjects(int maze[N][N]);

// ==================== Manejo de input ====================
void handleWindowsInput(Player *player, int maze[N][N], GameMode *currentSubMode, Enemy **currentEnemy, Map *enemyMap);
void handleSettingsInput(Player *player, bool *playing, GameMode *currentSubMode, sessionFloor *currentSession);
void handleInventoryInput(Player *player, GameMode *currentSubMode);

#include "enmap.h"

#endif