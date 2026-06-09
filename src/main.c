#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <string.h>
// #include <ctype.h>
#include <limits.h> // Necessary for using INF (infinity)
#define INF INT_MAX
#define INT_ERROR -1
#include "tdas/list.h"
#include "tdas/extra.h"
#include "tdas/heap.h"

// Maze symbols
#define WALL '#' // Obstacle
#define EMPTY ' ' // Empty/free tile
#define PATH '.' // Path for the agent
#define START 'I' // Starting position of the agent
#define GOAL 'M' // Goal tile

// Estructura simple para enumerar movimientos/acciones
typedef enum {
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
} Action;


typedef struct State State;
// El laberinto comienza desde la esquina SUPERIOR-IZQUIERDA (UPPER-LEFT)
 struct State {
    int currentRow; // modifies "y" axis
    int currentColumn; // modifies "x" axis
    int accumulated; // Real cost (g) of moves
    int estimated; // Total estimated cost (f = g + h), essential for best-first / A* algorithm
    State *parent; // Pointer to predecessor state
};

// --------------- Utilities ---------------
// separador1, separador2 y readCharOption se movieron al archivo extra.c para 
// mantener portabilidad y reducir copy-paste de los mismos en cada código fuente.

// Reduce code-writing in cleaning Lists (like garbageCollector) that store data of the type State
void cleanGarbage(List *states) {
    State *tmpState = (State *) list_first(states);
    while(tmpState) {
        free(tmpState);
        tmpState = list_next(states);
    }
    list_clean(states);
    free(states);
}

// ==================== Prototypes ====================

// Implicit-graph functions
int isFinal(State *currentState, int targetRow, int targetColumn);
int getL1Distance(int currentRow, int currentColumn, int targetRow, int targetColumn);
State *createNewState();
State *transition(State *currentState, Action accion);
List *getAdjacentNodes(State *currentState, int maze[N][N], int targetRow, int targetColumn);

// Format / outputting functions
void printRawMaze(int maze[N][N]);
void mostrarMenuPrincipal();

// ==================== Main ====================

int main() {
    char option;
    int maze[N][N] = {0};
    int mazeGenerated = 0;
    // Inicializar semilla aleatoria para generar laberintos únicos
    srand(time(NULL));

    do {
        mostrarMenuPrincipal();
        printf("\nIngrese su opción\n< ");
        option = readCharOption();

        if(option == '5') break;

        if(option == '1') {

            generate_maze(maze, 90);
            mazeGenerated = 1;
            printRawMaze(maze);
            }
        else if (option>='2' && option<='4') {
            limpiarPantalla();
            if(!mazeGenerated) {
                printf("Error: debe generar un laberinto primero (opción 1)\n");
                presioneEnterParaContinuar();
            }
            else {
                printRawMaze(maze);
                switch(option) {
                    case '2':
                        runDFS(maze);
                        break;
                    case '3':
                        runBFS(maze);
                        break;
                    case '4':
                        runAStar(maze);
                        break;
                }
            }
        }
    } while(option != '5');

    limpiarPantalla();
    printf("Cerrando programa.. gracias por su paciencia.\n");

    return 0;
}

// Determine if the current state of the agent reached the goal
int isFinal(State *currentState, int targetRow, int targetColumn) {
    if(!currentState) return INT_ERROR;
    return(currentState->currentRow == targetRow && currentState->currentColumn == targetColumn);
}

// Manhattan distance
int getL1Distance(int currentRow, int currentColumn, int targetRow, int targetColumn) {
    if(currentRow<0 || currentColumn<0) return INT_ERROR;
    return abs(currentRow - targetRow) + abs(currentColumn - targetColumn);
}

// Generic function to creade new States
State *createNewState() {
    State *newState = (State *) malloc(sizeof(*newState));
    if(!newState) return NULL;

    newState->currentRow = newState->currentColumn = newState->accumulated = 0;
    newState->estimated = getL1Distance(0, 0, N-1, N-1);
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
    newState->accumulated = currentState->accumulated + 1;
    newState->estimated = 0;
    newState->parent = currentState;

    return newState;
}

// Return a list with all the valid, adjacent State(s) to the current one
List *getAdjacentNodes(State *currentState, int maze[N][N], int targetRow, int targetColumn) {
    if(!currentState) return NULL;

    List *adjacentList = list_create();
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

                int h = getL1Distance(validState->currentRow, validState->currentColumn,
                    targetRow, targetColumn);
                validState->estimated = validState->accumulated + h;

                list_pushBack(adjacentList, validState);
            }
        }
    }
    return adjacentList;
}

void printRawMaze(int maze[N][N]) {

    char tile;
    separador1();
    printf("    Topología actual del Laberinto\n");
    separador1();
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            tile = (maze[i][j] == 1) ? WALL : EMPTY;
            if(i==0 && j==0) tile = START;
            if(i==N-1 && j==N-1) tile = GOAL;
            printf("%c ", tile);
        }
        printf("\n");
    } 
    separador1();
    presioneEnterParaContinuar();
}

void mostrarMenuPrincipal() {
    limpiarPantalla();
    separador1();
    puts("|---- Maze-Mapper: laberinto 10x10 ----|");
    separador2();
    puts("\nOpciones de control\n< ");
    puts("1) Generar nuevo laberinto (Dificultad 90)");
    puts("2) Resolver usando DFS (Profundidad)");
    puts("3) Resolver usando BFS (Anchura)");
    puts("4) Resolver usando A* (Heurística)");
    puts("5) Salir del programa\n");

    separador2();
}