#include "game.h"

void cleanGarbage(List *states) {
    State *tmpState = (State *) listFirst(states);
    while(tmpState) {
        free(tmpState);
        tmpState = listNext(states);
    }
    listClean(states);
    free(states);
}

// Determine if the current state of the agent reached the goal
int isFinal(State *currentState, int targetRow, int targetColumn) {
    if(!currentState) return INT_ERROR;
    return(currentState->currentRow == targetRow && currentState->currentColumn == targetColumn);
}

// Generic function to creade new States
State *createNewState() {
    State *newState = (State *) malloc(sizeof(*newState));
    if(!newState) return NULL;

    newState->currentRow = newState->currentColumn = 0;
    newState->parent = NULL;

    return newState;
}

// Create the new state after executing a specific move/action
State *transition(State *currentState, Action accion) {
    if(!currentState) return NULL;
    
    State *newState = (State *) malloc(sizeof(*newState));
    if(!newState) return NULL;

    newState->currentColumn = currentState->currentColumn;
    newState->currentRow = currentState->currentRow;

    switch(accion) {
        case UP:
            --newState->currentRow;
            break;
        case DOWN:
            ++newState->currentRow;
            break;
        case LEFT:
            --newState->currentColumn;
            break;
        case RIGHT:
            ++newState->currentColumn;
            break;
    }

    newState->parent = currentState;

    return newState;
}

// Return a list with all the valid, adjacent State(s) to the current one
List *getAdjacentNodes(State *currentState, int maze[N][N]) {
    if(!currentState) return NULL;

    List *adjacentList = listCreate();
    if(!adjacentList) return NULL;
    Action actions[] = {UP, DOWN, LEFT, RIGHT};

    for(int i=0; i<4; i++) {
        Action tmpAction = actions[i];
        int nextColumn = currentState->currentColumn;
        int nextRow = currentState->currentRow;

        switch(tmpAction) {
            case UP:
            --nextRow;
            break;
        case DOWN:
            ++nextRow;
            break;
        case LEFT:
            --nextColumn;
            break;
        case RIGHT:
            ++nextColumn;
            break;
        }

        if(nextRow >= 0 && nextRow < N && nextColumn >= 0 && nextColumn < N) {
            // wall | obstace: 1, free spot: 0
            if(maze[nextRow][nextColumn] != 1) {
                State *validState = transition(currentState, tmpAction);
                if(!validState) continue;

                listPushBack(adjacentList, validState);
            }
        }
    }
    return adjacentList;
}

// Función recursiva (DFS) para encontrar un camino aleatorio garantizado
int buildSafePath(int x, int y, int safe[N][N], int visited[N][N]) {
    // Verificar límites y si ya visitamos la celda
    if (x < 0 || y < 0 || x >= N || y >= N || visited[x][y]) {
        return 0;
    }

    visited[x][y] = 1;
    safe[x][y] = 1; // Lo marcamos temporalmente como parte del camino

    // Condición de éxito: Llegamos a la meta
    if (x == N - 1 && y == N - 1) {
        return 1;
    }

    // Direcciones: Derecha, Abajo, Izquierda, Arriba
    int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // Mezclar las direcciones aleatoriamente para que el camino no sea predecible
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int tempX = dirs[i][0];
        int tempY = dirs[i][1];
        dirs[i][0] = dirs[r][0];
        dirs[i][1] = dirs[r][1];
        dirs[r][0] = tempX;
        dirs[r][1] = tempY;
    }

    // Explorar los vecinos en el orden aleatorio
    for (int i = 0; i < 4; i++) {
        int nx = x + dirs[i][0];
        int ny = y + dirs[i][1];
        if (buildSafePath(nx, ny, safe, visited)) {
            return 1; // Si este camino llega a la meta, detenemos la búsqueda
        }
    }

    // Backtracking: Si llegamos a un callejón sin salida, desmarcamos el camino
    safe[x][y] = 0;
    return 0;
}

// Función principal para generar el laberinto
void generateMaze(int maze[N][N], int difficulty) {
    int safe[N][N] = {0};
    int visited[N][N] = {0};

    // 1. Trazar el camino seguro desde el inicio (0,0) a la meta (N-1, N-1)
    buildSafePath(0, 0, safe, visited);

    // 2. Rellenar el resto de la matriz basándonos en la dificultad
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (safe[i][j] == 1) {
                // Si es parte del camino seguro, obligatoriamente es espacio libre
                maze[i][j] = 0; 
            } else {
                // Si no es el camino seguro, tiramos un dado de 0 a 99
                // 'difficulty' actúa como el porcentaje de aparición de obstáculos
                int r = rand() % 100;
                if (r < difficulty) {
                    maze[i][j] = 1; // Pared / Obstáculo
                } else {
                    maze[i][j] = 0; // Espacio libre
                }
            }
        }
    }
}

void placeExits(int maze[N][N], int numExits) {

    int placed = 0;
    while(placed < numExits) {
        int randomX = rand() % N;
        int randomY = rand() % N;

        if(maze[randomY][randomX] == 0 && (randomX != 0 || randomY != 0)) {
            maze[randomY][randomX] = EXIT_TILE;
            placed++;
        }
    }
}

// Faltaría implementar manejo de input para Linux
// Actualizamos la firma para recibir el puntero del jugador y el flag del bucle
void handleWindowsInput(Player *player, bool *playing, int maze[N][N]) {
    int key = _getch();

    if(key == 0 || key == 224) {
        int specialCode = _getch();
        switch(specialCode) {
            default:
                break;
        }
    } 
    else if(key == ESC_KEY) {
        *playing = false; // Modificar booleano original mediante su puntero
    } 
    else {
        switch(key) {
            case W_KEY_UPPER:
            case W_KEY_LOWER:
                if(player->y > 0 && maze[player->y - 1][player->x] != 1)
                    player->y -= 1;
                break;

            case A_KEY_UPPER:
            case A_KEY_LOWER:
                if(player->x > 0 && maze[player->y][player->x - 1] != 1)
                    player->x -= 1;
                break;
                
            case S_KEY_UPPER:
            case S_KEY_LOWER:
                if(player->y < N - 1 && maze[player->y + 1][player->x] != 1)
                    player->y += 1;
                break;

            case D_KEY_UPPER:
            case D_KEY_LOWER:
                if(player->x < N - 1 && maze[player->y][player->x + 1] != 1)
                    player->x += 1;
                break;
        }
    }
}