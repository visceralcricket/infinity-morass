#include "game.h"

void cleanGarbage(List *states) {
    State *tmpState = (State *) list_first(states);
    while(tmpState) {
        free(tmpState);
        tmpState = list_next(states);
    }
    list_clean(states);
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

                list_pushBack(adjacentList, validState);
            }
        }
    }
    return adjacentList;
}
// Faltaría implementar manejo de input para Linux
void handleWindowsInput(Player *player, bool *playing, int maze[N][N]) {
    bool playing = true;
    while(playing) {
        int key = _getch();

        // Verificar si es tecla especial (como las flechas)
        if(key == 0 || key == 224) {
            int specialCode = _getch();
            switch(specialCode) {
                default:
                    break;
            }
        }
        
        else if(key == ESC_KEY) *playing = false;
            
        else {
            switch(key) {
                case W_KEY_UPPER:
                case W_KEY_LOWER:
                    printf("\tMoviéndose al Norte..\n");
                    // jugador.y -= 1;
                    break;
                case A_KEY_UPPER:
                case A_KEY_LOWER:
                    printf("\tMoviéndose al Sur..\n");
                    // jugador.y += 1;
                    break;
                case S_KEY_UPPER:
                case S_KEY_LOWER:
                    printf("\tMoviéndose al Este..\n");
                    // jugador.x += 1;
                    break;
                case D_KEY_UPPER:
                case D_KEY_LOWER:
                    printf("\tMoviéndose al Oeste..\n");
                    // jugador.x -= 1;
                    break;
            }
        }
    }    
}
