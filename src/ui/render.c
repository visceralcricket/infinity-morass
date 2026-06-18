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
    
    separador1();
    printf("\t\tPresione " COLOR_MAGENTA "ESC" FORMAT_RESET " para pausar el juego\n");
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
                char tile;
                if(maze[i][j] == 1) tile = WALL;
                else if(maze[i][j] == EXIT_TILE) tile = GOAL;
                else if(maze[i][j] == ENEMY_TILE) tile = 'E';
                else tile = EMPTY;
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
}

void renderSettingsOverlay() {

    int startRow = 5;
    int startCol = 75;

    SET_CURSOR_POS(startRow, startCol);
    printf(FORMAT_BOLD COLOR_YELLOW "=== PAUSA ===" FORMAT_RESET);

    SET_CURSOR_POS(startRow+2, startCol);
    printf("1) Continuar");

    SET_CURSOR_POS(startRow+3, startCol);
    printf("2) Ver Inventario");;

    SET_CURSOR_POS(startRow+4, startCol);
    printf("3) Guardar Partida");

    SET_CURSOR_POS(startRow+5, startCol);
    printf("4) Salir al menú principal");

    SET_CURSOR_POS(N+4, 0);
}

void renderInventoryOverlay(Player *player) {

    int startRow = 5;
    int startCol = 75;

    SET_CURSOR_POS(startRow, startCol);
    printf(FORMAT_BOLD COLOR_CYAN "==== INVENTARIO ====" FORMAT_RESET);

    int currentRow = startRow+2;
    if(!(player->inventory) || listSize(player->inventory) == 0) {
        SET_CURSOR_POS(currentRow, startCol);
        printf(FORMAT_DIM "El inventario está vacío.." FORMAT_RESET);
    }

    else {

    }    
    SET_CURSOR_POS(N+4, 0);
}