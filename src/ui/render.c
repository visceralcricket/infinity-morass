#include "render.h"

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