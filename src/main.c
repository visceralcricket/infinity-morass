#include "engine/game.h"
#include "io/storage.h"
#include "ui/render.h"

// --------------- Utilities ---------------
// separador1, separador2 y readCharOption se movieron al archivo extra.c para 
// mantener portabilidad y reducir copy-paste de los mismos en cada código fuente.

// ======== Prototypes ========
void showMainMenu(char *username);
void renderExploration(int maze[N][N], Player player);
void runExplorationMode(int maze[N][N], Player *player);
// void showGlossary();

// ==================== Main ====================

int main() {

    Player sessionPlayer = {
        "", 0, 0,
        {100, 10, 5, 5, 5},
        NULL  // IMPORTANTE: aquí debería llamarse a listCreate() para inicializar inventario
    };

    int maze[N][N] = {0};
    int mazeGenerated = 0;
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

    
    if(loadGame(&sessionPlayer)) {
        printf("\n\t\t" COLOR_GREEN "Perfil encontrado. Partida cargada exitosamente." FORMAT_RESET "\n");
    }
    
    else {
        printf("\n\t\t" COLOR_CYAN "Perfil nuevo. Inicializando matriz de datos.." FORMAT_RESET "\n");
        // Solo incializamos una lista nueva si el jugador es nuevo
        sessionPlayer.inventory = listCreate();
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
                // Función redundante de lectura de nombre eliminada
                
                if(!mazeGenerated) {
                    generateMaze(maze, 20);
                    // Generar salidas, con MAX_NUM_EXITS = 3 (game.h)
                    placeExits(maze, MAX_NUM_EXITS);
                    mazeGenerated = 1;
                }

                runExplorationMode(maze, &sessionPlayer);

                if(saveGame(&sessionPlayer)) {
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

void runExplorationMode(int maze[N][N], Player *player) {
    
    bool playing = true;
    int prevX = 0, prevY = 0;
    GameMode currentSubMode = MODE_EXPLORATION;

    player->x = player->y = 0;
    limpiarPantalla(); // Sólo limpiar pantalla una vez

    while(playing) {

        // ============== Fase 1: Renderizar estado actual ==============
        renderExploration(maze, *player);
        
        // Dibujar menús superpuestos si es necesario
        switch(currentSubMode) {

            case MODE_SETTINGS:
                renderSettingsOverlay();
                break;

            case MODE_INVENTORY_VIEW:
                renderInventoryOverlay(player);
                break;

            case MODE_EXPLORATION:
                break;

            default:
                break;
        }
        // Lógica e input general (controllers)
        switch(currentSubMode) {
            case MODE_SETTINGS:
                // handleSettingsInput(&playing, currentSubMode);
                break;
            case MODE_INVENTORY_VIEW:
                // handleInventoryInput(&playing, currentSubMode);
                break;

            case MODE_EXPLORATION:
                // Guardar coordenadas ANTES de procesar movimiento
                prevX = player->x;
                prevY = player->y;
                // Procesar el input de este frame (pasar punteros)
                handleWindowsInput(player, maze, &currentSubMode);

                if(maze[player->y][player->x] == EXIT_TILE) {
                    renderExploration(maze, *player); // Actualizar pantalla
                    printf("\n\t" FORMAT_BOLD COLOR_YELLOW "Una puerta misteriosa se revela ante ti." FORMAT_RESET);
                    printf("\n\tDeseas descender al siguiente nivel? (S/N)\n\t< ");

                    char choice = readCharOption();
                    if(choice=='S' || choice == 's') {
                        printf("\n\tDescendiendo a las " COLOR_BLUE "profundidades.." FORMAT_RESET);
                        printf("\n\t");
                        presioneTeclaParaContinuar();

                        generateMaze(maze, 20);
                        placeExits(maze, MAX_NUM_EXITS);

                        player->x = player->y = 0;
                        limpiarPantalla();
                    }
                    else {
                        player->x = prevX;
                        player->y = prevY;
                        limpiarPantalla();
                    }
                }
                break;
            
            default:
                break;
        }
    }
    printf(SHOW_CURSOR);
}

// void showGlossary() {}