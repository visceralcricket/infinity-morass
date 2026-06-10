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
    int currentMode = MAIN_MENU;
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
                // currentMode = EXPLORATION_MODE;
                break;
            case '2':
                // ...
                break;
            case '3':
                // currentMode = SETTINGS_MODE;
                break;
        }

    } while(currentMode == MAIN_MENU && option != '4');

    limpiarPantalla();
    printf("Cerrando programa.. gracias por su paciencia.\n");

    return 0;
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

void showMainMenu() {
    limpiarPantalla();
    separador1();
    puts("\t|---- Infinity-Morass: A hyper-link to the Future ----|");
    separador2();
    puts("\n\tOpciones de juego\n< ");
    puts("\t1) Iniciar nueva partida");
    puts("\t2) Ver glosario");
    puts("\t3) Opciones");
    puts("\t4) Salir del juego");

    separador2();
}

// void showGlossary() {}