#include "game.h"

// --------------- Utilities ---------------
// separador1, separador2 y readCharOption se movieron al archivo extra.c para 
// mantener portabilidad y reducir copy-paste de los mismos en cada código fuente.

// ======== Prototypes ========
void showMainMenu();
void renderExploration(int maze[N][N], Player player);
void runExplorationMode(int maze[N][N]);
// void showGlossary();

// ==================== Main ====================

int main() {
    char option;
    GameMode currentMode = MODE_MAIN_MENU;
    int maze[N][N] = {0};
    int mazeGenerated = 0;
    // Inicializar semilla aleatoria para generar laberintos únicos
    srand(time(NULL));

    do {
        showMainMenu();
        printf("\n\t\t" FORMAT_BOLD "Ingrese su opción\n\t\t" FORMAT_RESET FORMAT_DIM "<" FORMAT_RESET " ");
        option = readCharOption();

        if(option == '3') break;

        switch(option) {

            case '1':
                if(!mazeGenerated) {
                    generateMaze(maze, 20);
                    mazeGenerated = 1;
                }
                runExplorationMode(maze);
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

void showMainMenu() {
    limpiarPantalla();
    separador1();
    puts(" \t|---- Infinity-" COLOR_CYAN FORMAT_BOLD "Morass" FORMAT_RESET ": A hyper-link to the Future ----|");
    separador2();
    // \033[1m -> Comienza a escribir texto en bold(negrita)
    // \033[0m -> Esto resetea el formato de nueva a su estado normal
    puts("\n\t\t" FORMAT_BOLD "Opciones de juego" FORMAT_RESET "\n");
    puts("\t\t1) Iniciar nueva partida");
    puts("\t\t2) Ver glosario");
    puts("\t\t3) Salir del juego");

    separador2();
}

void renderExploration(int maze[N][N], Player player) {
    limpiarPantalla();
    separador1();
    printf("\tPresione " FORMAT_BOLD "ESC" FORMAT_RESET " para salir\n");
    separador1();

    for(int i=0; i<N; i++) {
        printf("\t");
        for(int j=0; j<N; j++) {
            if(i==player.y && j==player.x) printf("P "); // Jugador
            else {
                char tile = (maze[i][j] == 1) ? WALL : EMPTY;
                if(i==0 && j==0) tile = START; // Considerar cambiar esto luego
                if(i== N-1 && j == N-1) tile = GOAL;
                printf("%c ", tile);
            }
        }
        printf("\n");
    }
    separador1();
}

void runExplorationMode(int maze[N][N]) {
    /* +++
        Aquí falta hacer una funcionalidad donde se pueda leer
        el username del jugador para almacenarlo en la estructura
        y luego usarlo para guardar su progreso.
    
    --- */
    Player player = {
        "tmpName",
        0, 0,
        {100, 10, 5, 5},
        NULL
    }; // Considerar cambiar por casilla aleatoria
    bool playing = true;

    while(playing) {
        // Renderizar estado actual
        renderExploration(maze, player);
        // Procesar el input de este frame (pasar punteros)
        handleWindowsInput(&player, &playing, maze);

        if(player.y == N-1 && player.x == N-1) {
            renderExploration(maze, player);
            printf("\n\tHas llegado a la meta!\n");
            presioneTeclaParaContinuar();
            playing = false;
        }
    }
}

// void showGlossary() {}