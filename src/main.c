#include "game.h"
#include "storage.h"

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
        {100, 10, 5, 5},
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

void showMainMenu(char *username) {
    limpiarPantalla();
    separador1();
    puts(" \t|---- Infinity-" COLOR_CYAN FORMAT_BOLD "Morass" FORMAT_RESET ": A hyper-link to the Future ----|");
    printf("\t\t Bienvenido, " FORMAT_BOLD "%s" FORMAT_RESET "\n", username);
    separador2();
    puts("\n\t\t" FORMAT_BOLD "Opciones de juego" FORMAT_RESET "\n");
    puts("\t\t1) Iniciar nueva partida");
    puts("\t\t2) Ver glosario");
    puts("\t\t3) Salir del juego");

    separador2();
}

void renderExploration(int maze[N][N], Player player) {
    printf(MOVE_CURSOR HIDE_CURSOR);
    
    limpiarPantalla();
    separador1();
    printf("\t\t\tPresione " COLOR_MAGENTA "ESC" FORMAT_RESET " para salir\n");
    separador1();

    printf("\t.");
    for(int k=0; k<N; k++) {
        if(k % 4 == 0) printf("- ");
        else printf("  ");
    }
    printf(".\n");

    for(int i=0; i<N; i++) {
        printf("\t");
        if(i % 3 == 0) printf("| ");
        else printf("  ");

        for(int j=0; j<N; j++) {
            if(i==player.y && j==player.x) {
                printf("P "); // Jugador
            }
            else {
                char tile = (maze[i][j] == 1) ? WALL : EMPTY;

                if(maze[i][j] == EXIT_TILE) tile = GOAL;
                if(i==0 && j==0) tile = START;
                printf("%c ", tile);
            }
        }
        if(i % 3 == 0) printf("|");
        printf("\n");
    }
    printf("\t");
    for(int k=0; k<N; k++) {
        if(k % 4 == 0) printf("- ");
        else printf("  ");
    }
    printf("\n");
    separador1();
}

void runExplorationMode(int maze[N][N], Player *player) {
    
    bool playing = true;
    int prevX = 0, prevY = 0;

    player->x = player->y = 0;
    limpiarPantalla(); // Sólo limpiar pantalla una vez

    while(playing) {
        // Renderizar estado actual
        renderExploration(maze, *player);
        prevX = player->x;
        prevY = player->y;
        // Procesar el input de este frame (pasar punteros)
        handleWindowsInput(player, &playing, maze);

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
    }
    printf(SHOW_CURSOR);
}

// void showGlossary() {}