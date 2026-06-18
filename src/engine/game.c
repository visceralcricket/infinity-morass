#include "game.h"
#include "io/storage.h"

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
// Función para generar salidas / entradas a siguiente nivel aleatoriamente
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

/* +++
Aquí idealmente debería ir el nivel de dificultar para afectar directamente la
cantidad de enemigos que se van a generar por mazmorra, pero a fines de conveniencia
y para comprobar que la generación de enemigos funciona correctamente, se va a ignorar.
--- */
void placeEnemies(int maze[N][N]) {
    int placed = 0;
    while(placed < MAX_ENEMIES_PER_DUNGEON) {
        int randomX = rand() % N;
        int randomY = rand() % N;

        if(maze[randomY][randomX] == 0 && (randomX != 0 || randomY != 0)) {
            maze[randomY][randomX] = ENEMY_TILE;
            placed++;
        }
    }
}

// Faltaría implementar manejo de input para Linux
// Actualizamos la firma para recibir el puntero del jugador y el flag del bucle
void handleWindowsInput(Player *player, int maze[N][N], GameMode *currentSubMode) {
    int key = _getch();

    // Normalizar letras mayúsculas
    if(key >= 'A' && key <= 'Z') key += 32;

    if(key == ESC_KEY) {
        *currentSubMode = MODE_SETTINGS;
    } 
    else {
        switch(key) {
            case W_KEY_LOWER:
                if(player->y > 0 && maze[player->y - 1][player->x] != 1)
                    player->y -= 1;
                break;

            case A_KEY_LOWER:
                if(player->x > 0 && maze[player->y][player->x - 1] != 1)
                    player->x -= 1;
                break;
                
            case S_KEY_LOWER:
                if(player->y < N - 1 && maze[player->y + 1][player->x] != 1)
                    player->y += 1;
                break;

            case D_KEY_LOWER:
                if(player->x < N - 1 && maze[player->y][player->x + 1] != 1)
                    player->x += 1;
                break;
        }
    }
    if(maze[player->y][player->x] == ENEMY_TILE) {
        Enemy *enemy = spawnRandomEnemy();
        if(enemy) {
            enemy->x = player->x;
            enemy->y = player->y;
            printf("\n\tHas encontrado a: %s\n\t", enemy->enemyName);
            presioneTeclaParaContinuar();
            limpiarPantalla();
            free(enemy);
            maze[player->y][player->x] = EMPTY;
            // *currentSubMode = MODE_COMBAT;
        }
    }
}

void handleSettingsInput(Player *player, bool *playing, GameMode *currentSubMode) {
    int key = _getch();

    switch(key) {
        case '1': // Continuar

        // Presionar ESC de nuevo para salir de las opciones
        case ESC_KEY:
            limpiarPantalla();
            *currentSubMode = MODE_EXPLORATION;
            break;

        case '2':
            limpiarPantalla();
            *currentSubMode = MODE_INVENTORY_VIEW;
            break;

        case '3':
            // Guardamos la partida sin cambiar de GameMode y sin limpiar pantalla
            saveGame(player);

            SET_CURSOR_POS(12, 75);
            printf(FORMAT_BOLD COLOR_GREEN "Guardado completado." FORMAT_RESET);
            break;

        case '4':
            *playing = false;
            break;
    }
}

// Manejar input dentro del sub-submenú inventario en pausa
void handleInventoryInput(Player *player, GameMode *currentSubMode) {
    int key = _getch();

    // Normalizar letras mayúsculas
    if(key >= 'A' && key <= 'Z') key += 32;

    switch(key) {
        case ESC_KEY:
            limpiarPantalla();
            *currentSubMode = MODE_SETTINGS;
            break;

        case 'a':
            if(player->inventory) listPrev(player->inventory);
            break;

        case 'd':
            if(player->inventory) listNext(player->inventory);
            break;
    }
}
