#include "game.h"

// --------------- Utilities ---------------
// separador1, separador2 y readCharOption se movieron al archivo extra.c para 
// mantener portabilidad y reducir copy-paste de los mismos en cada código fuente.

void printRawMaze(int maze[N][N]);
void showMainMenu();
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
        printf("\nIngrese su opción\n< ");
        option = readCharOption();

        if(option == '4') break;

        switch(option) {

            case '1':
                mazeGenerated = 1;
                runExplorationMode(maze[N][N]);
                break;
            case '2':
                // void showGlossary(maze);
                break;
            case '3':
                // currentMode = MODE_SETTINGS;
                break;
        }

    } while(currentMode == MODE_MAIN_MENU && option != '4');

    limpiarPantalla();
    printf("Cerrando programa.. gracias por su paciencia.\n");

    return 0;
}

void showMainMenu() {
    limpiarPantalla();
    separador1();
    puts("\t|---- Infinity-Morass: A hyper-link to the Future ----|");
    separador2();
    puts("\n\tOpciones de juego\n\t< ");
    puts("\t1) Iniciar nueva partida");
    puts("\t2) Ver glosario");
    puts("\t3) Opciones");
    puts("\t4) Salir del juego");

    separador2();
}

void renderExploration(int maze[N][N], Player player) {
    limpiarPantalla();
    separador1();
    printf("\tModo exploración - Presione ESC para salir\n");
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
    Player player = {
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
            printf("\n\t¡Has llegado a la meta!\n");
            presioneTeclaParaContinuar();
            playing = false;
        }
    }
}

// void showGlossary() {}