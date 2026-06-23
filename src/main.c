#include "engine/game.h"
#include "io/storage.h"
#include "engine/combat.h"
#include "ui/render.h"

// --------------- Utilities ---------------
// separador1, separador2 y readCharOption se movieron al archivo extra.c para 
// mantener portabilidad y reducir copy-paste de los mismos en cada código fuente.

// ======== Prototypes ========
void showMainMenu(char *username);
void renderExploration(int maze[N][N], Player player);
void runExplorationMode(int maze[N][N], Player *player, sessionFloor *currentSession);
// void showGlossary();

// ==================== Main ====================

int main() {

    Player sessionPlayer = {
        .username = "",
        .x = 0,
        .y=  0,
        .combatStats = {100, 100, 5, 5, 5},
        .inventory = NULL,  // IMPORTANTE: aquí debería llamarse a listCreate() para inicializar inventario
    };
    // Inicializar estructura que almacene propiedades clave del mapa actual
    struct sessionFloor currentSession = {0};

    int mazeGenerated = false;
    // Inicializar semilla aleatoria para generar laberintos únicos
    srand(time(NULL));

    limpiarPantalla();
    separador1();
    printf("\t\t" FORMAT_BOLD "Inicio de Sistema - Infinity Morass" FORMAT_RESET "\n");
    puts("\t\tPor favor, ingrese su" FORMAT_BOLD COLOR_RED " nombre.." FORMAT_RESET);
    separador1();
    printf("\n\t\t" FORMAT_DIM COLOR_RED "< " FORMAT_RESET);
    
    if(fgets(sessionPlayer.username, sizeof(sessionPlayer.username), stdin)) {
        sessionPlayer.username[strcspn(sessionPlayer.username, "\n")] = 0;
    }
    else strcpy(sessionPlayer.username, "Guest");

    
    if(loadGame(&sessionPlayer, &currentSession)) {
        printf("\n\t\t" COLOR_GREEN "Perfil encontrado. Partida cargada exitosamente." FORMAT_RESET "\n");
        mazeGenerated = true;
    }
    
    else {
        printf("\n\t\t" COLOR_CYAN "Perfil nuevo. Inicializando matriz de datos.." FORMAT_RESET "\n");
        // Solo incializamos una lista nueva si el jugador es nuevo / no tiene inventario
        if(!sessionPlayer.inventory) sessionPlayer.inventory = listCreate();
        currentSession.isMapDirty = true;
    }
    
    printf("\t\t");
    presioneTeclaParaContinuar();
    char option;
    GameMode currentMode = MODE_MAIN_MENU;

    do {
        showMainMenu(sessionPlayer.username);
        printf("\n\t\t" FORMAT_BOLD "Ingrese su opción\n\t\t" FORMAT_RESET FORMAT_DIM "<" FORMAT_RESET " ");
        option = readCharOption();

        if(option == '3') break;

        switch(option) {

            case '1':
                
                if(!mazeGenerated) {
                    generateMaze(currentSession.maze, 20);
                    // Generar salidas, con MAX_NUM_EXITS = 3 (game.h)
                    placeExits(currentSession.maze, MAX_NUM_EXITS);
                    // Map *enemyMap = createEnemiesMap();
                    placeEnemies(currentSession.maze);
                    // List spawnedEnemies = listCreate();
                    placeObjects(currentSession.maze);
                    mazeGenerated = true;
                }

                runExplorationMode(currentSession.maze, &sessionPlayer, &currentSession);

                if(saveGame(&sessionPlayer, &currentSession)) {
                    printf("\n\t" FORMAT_BOLD COLOR_GREEN "Autoguardado completado." FORMAT_RESET "\n");
                }
                else {
                    printf("\n\t" FORMAT_BOLD COLOR_RED "Error al autoguardar la partida." FORMAT_RESET "\n");
                }
                presioneTeclaParaContinuar();
                break;

            case '2':
                // void showGlossary(maze);
                break;
        }

    } while(currentMode == MODE_MAIN_MENU && option != '3');

    limpiarPantalla();
    printf("Cerrando programa.. gracias por su paciencia.\n");

    return 0;
}

void runExplorationMode(int maze[N][N], Player *player, sessionFloor *currentSession) {
    
    bool playing = true;
    int prevX = 0, prevY = 0;
    GameMode currentSubMode = MODE_EXPLORATION;
    Enemy *currentEnemy = NULL;   // <-- nuevo

    limpiarPantalla();

    while(playing) {

        renderExploration(maze, *player);
        
        switch(currentSubMode) {
            case MODE_SETTINGS:
                renderSettingsOverlay();
                break;
            case MODE_INVENTORY_VIEW:
                renderInventoryOverlay(player);
                break;
            case MODE_EXPLORATION:
                break;
            case MODE_COMBAT:
                break;   // combatMode maneja su propio render, acá no hace falta nada
            default:
                break;
        }

        fflush(stdout);

        switch(currentSubMode) {
            case MODE_SETTINGS:
                handleSettingsInput(player, &playing, &currentSubMode, currentSession);
                break;
            case MODE_INVENTORY_VIEW:
                handleInventoryInput(player, &currentSubMode);
                break;

            case MODE_EXPLORATION:
                prevX = player->x;
                prevY = player->y;
                handleWindowsInput(player, maze, &currentSubMode, &currentEnemy);  // <-- pasa el puntero

                if(maze[player->y][player->x] == EXIT_TILE) {
                    renderExploration(maze, *player);
                    printf("\n\t" FORMAT_BOLD COLOR_YELLOW "Una puerta misteriosa se revela ante ti." FORMAT_RESET);
                    printf("\n\tDeseas descender al siguiente nivel? (S/N)\n\t< ");

                    char choice = readCharOption();
                    if(choice=='S' || choice == 's') {
                        printf("\n\t" FORMAT_BOLD "Descendiendo a las " COLOR_BLUE "profundidades. . ." FORMAT_RESET);
                        printf("\n\t");
                        presioneTeclaParaContinuar();

                        generateMaze(maze, 20);
                        placeExits(maze, MAX_NUM_EXITS);
                        placeEnemies(maze);
                        placeObjects(maze);

                        player->x = player->y = 0;
                        currentSession->isMapDirty = true;
                        limpiarPantalla();
                    }
                    else {
                        player->x = prevX;
                        player->y = prevY;
                        limpiarPantalla();
                    }
                }
                break;

            case MODE_COMBAT:
                combatMode(player, currentEnemy);   // <-- acá se llama el sistema de combate completo
                free(currentEnemy);
                currentEnemy = NULL;
                currentSubMode = MODE_EXPLORATION;
                limpiarPantalla();
                break;
            
            default:
                break;
        }
    }
    printf(SHOW_CURSOR);
}

// void showGlossary() {}