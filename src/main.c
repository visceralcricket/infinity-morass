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

    for(int i=0; i<N; i++) {
        printf("\t");
        for(int j=0; j<N; j++) {
            if(i==player.y && j==player.x) printf("P "); // Jugador
            else {
                char tile = (maze[i][j] == 1) ? WALL : EMPTY;

                // Considerar cambiar esto luego por una generación aleatoria de punto de partida
                if(i==0 && j==0) tile = START;
                if(i== N-1 && j == N-1) tile = GOAL;
                printf("%c ", tile);
            }
        }
        printf("\n");
    }
    separador1();
}

void runExplorationMode(int maze[N][N], Player *player) {
    
    bool playing = true;
    // Considerar NO resetear las coordenadas del jugador
    player->x = player->y = 0;
    limpiarPantalla(); // Sólo limpiar pantalla una vez

    while(playing) {
        // Renderizar estado actual
        renderExploration(maze, *player);

        // Procesar el input de este frame (pasar punteros)
        handleWindowsInput(player, &playing, maze);

        if(player->y == N-1 && player->x == N-1) {
            renderExploration(maze, *player);
            printf("\n\tHas llegado a la " COLOR_YELLOW "meta" FORMAT_RESET "!\n");
            presioneTeclaParaContinuar();
            playing = false;
        }
    }
    printf(SHOW_CURSOR);
}

// void showGlossary() {}