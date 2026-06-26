#include "render.h"

void showMainMenu(char *username) {
    limpiarPantalla();
    separador1();
    puts(" \t|---- Infinity-" COLOR_CYAN FORMAT_BOLD "Morass" FORMAT_RESET ": A hyper-link to the Future ----|");
    printf("\t\t Bienvenido, " FORMAT_BOLD "%s" FORMAT_RESET "\n", username);
    separador2();
    puts("\n\t\t" FORMAT_BOLD "Opciones de juego" FORMAT_RESET "\n");
    puts("\t\t1) Iniciar partida");
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
            else if(maze[i][j] == BOSS_TILE) 
            {
                printf(FORMAT_BOLD COLOR_RED "B" FORMAT_RESET " ");
            }
            else {
                char tile;
                if(maze[i][j] == 1) tile = WALL;
                else if(maze[i][j] == EXIT_TILE) tile = GOAL;
                else if(maze[i][j] == ENEMY_TILE) tile = ENEMY_TILE;
                else if(maze[i][j] == OBJECT_TILE) tile = OBJECT_TILE;
                else if(maze[i][j] == BOSS_TILE) tile = BOSS_TILE;
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
    printf("2) Ver Inventario");

    SET_CURSOR_POS(startRow+4, startCol);
    printf("3) Guardar Partida");

    SET_CURSOR_POS(startRow+5, startCol);
    printf("4) Salir al menú principal");

    SET_CURSOR_POS(N+4, 0);
}

void renderInventoryOverlay(Player *player) {

    int startRow = OVERLAY_ROW;
    int startCol = OVERLAY_COL;

    SET_CURSOR_POS(startRow, startCol);
    printf(FORMAT_BOLD COLOR_CYAN "==== INVENTARIO ====" FORMAT_RESET);

    int currentRow = startRow+2;
    if(!(player->inventory) || listSize(player->inventory) == 0) {
        SET_CURSOR_POS(currentRow, startCol);
        printf(FORMAT_DIM "El inventario está vacío.." FORMAT_RESET);
    }
    else {
        GameObject *selectedItem = (GameObject *) listCurrent(player->inventory);
        GameObject *item = (GameObject *) listFirst(player->inventory);
        while (item != NULL) {
            SET_CURSOR_POS(currentRow, startCol);
            printf(CLEAR_LINE_TO_END);
            
            if (item == selectedItem) {
                printf("-> ");
            }
            else {
                printf(" ");
            }

            const char *tipo;
            switch (item->equip) {
                case ITEM_CONSUMABLE: tipo = "Consumible"; break;
                case ITEM_EQUIPPABLE: tipo = "Equipable";  break;
                case ITEM_KEY:        tipo = "Llave/Clave"; break;
                default:              tipo = "Desconocido"; break;
            }
            
            if  (strcmp(tipo, "Consumible") == 0) {
                printf("%s [%s] - HP:%d/%d",
                   item->name,
                   tipo,
                   item->stats.currentHp,
                   item->stats.maxHp);
            }
            else if (strcmp(tipo, "Equipable") == 0) {
                printf("%s [%s] - ", item->name, tipo);
                if (item->stats.attack != 0) {
                    printf(" ATK: %d", item->stats.attack);
                }
                if (item->stats.defense != 0) {
                    printf(" DEF: %d", item->stats.defense);
                }
                if (item->stats.maxHp != 0) {
                    printf(" HP: %d/%d", item->stats.currentHp, item->stats.maxHp);
                }
                if (item->stats.speed != 0) {
                    printf(" SPD: %d", item->stats.speed);
                }
            }
            else if (strcmp(tipo, "Clave") == 0) {
                printf("%s [%s]", item->name, tipo);
            }

            currentRow++;
            item = (GameObject *) listNext(player->inventory);
        }
        
        if (selectedItem != NULL) {
            listFirst(player->inventory);
            while (listCurrent(player->inventory) != selectedItem && listCurrent(player->inventory) != NULL) {
                listNext(player->inventory);
            }
        }
    }
    SET_CURSOR_POS(N+4, 0);
}

void renderCombatOverlay(Player *player, Enemy *enemy, void *currentTurn, int turnCounter, bool *fleeCondition) {

    limpiarInputPendiente();

    int startRow = OVERLAY_ROW;
    int startCol = OVERLAY_COL;
    int option;
    int damage;

    SET_CURSOR_POS(startRow, startCol);
    printf(CLEAR_LINE_TO_END FORMAT_BOLD COLOR_YELLOW "=== COMBATE ===" FORMAT_RESET);

    SET_CURSOR_POS(startRow+1, startCol);
    printf(CLEAR_LINE_TO_END "Turno %d", turnCounter);

    SET_CURSOR_POS(startRow+3, startCol);
    printf(CLEAR_LINE_TO_END "HP %s: %d", player->username, player->combatStats.currentHp);

    SET_CURSOR_POS(startRow+4, startCol);
    printf(CLEAR_LINE_TO_END "HP %s: %d", enemy->enemyName, enemy->combatStats.currentHp);

    if (currentTurn == player) {

        SET_CURSOR_POS(startRow+6, startCol);
        printf(CLEAR_LINE_TO_END "¡Es tu turno! Elige una acción:");

        SET_CURSOR_POS(startRow+7, startCol);
        printf(CLEAR_LINE_TO_END "1) Atacar");

        SET_CURSOR_POS(startRow+8, startCol);
        printf(CLEAR_LINE_TO_END "2) Usar objeto");

        SET_CURSOR_POS(startRow+9, startCol);
        printf(CLEAR_LINE_TO_END "3) Huir");

        fflush(stdin);
        
        SET_CURSOR_POS(startRow+11, startCol);
        printf(CLEAR_LINE_TO_END "Opción: ");
        fflush(stdout);

        int validInput = 0;
        while(!validInput) {
            int key = _getch();
            
            if(key >= '1' && key <= '3') {
                option = key - '0';
                printf("%c", key);
                fflush(stdout);
                validInput = 1;
            }
            /* +++
            Si presiona Enter, letras o símbolos, el código NO hace nada.
            El cursor se mantiene congelado y protegido tras "Opción: ".
            Leer cambios realizados en extra.c para más detalles
            --- */
        }

        SET_CURSOR_POS(startRow+13, startCol);
        printf(CLEAR_LINE_TO_END);
        switch(option) {
            case 1:
                damage = player->combatStats.attack - enemy->combatStats.defense;
                if (damage <= 0) damage = 1;
                enemy->combatStats.currentHp -= damage;
                printf("Has infligido %d puntos de daño.", damage);
                break;
            case 2:
                printf("En espera de implementación: usar objeto");
                break;
            case 3:
                if (player->combatStats.speed > enemy->combatStats.speed) {
                    printf("Has huido exitosamente del combate.");
                    *fleeCondition = true;
                } else {
                    printf("Has intentado huir, pero el enemigo es más rápido. ¡No puedes escapar!");
                }
                break;
            default:
                break;
        }

    } else {

        damage = enemy->combatStats.attack - player->combatStats.defense;
        if (damage <= 0) damage = 1;
        player->combatStats.currentHp -= damage;

        SET_CURSOR_POS(startRow+6, startCol);
        printf(CLEAR_LINE_TO_END "El enemigo te ha infligido %d puntos de daño.", damage);

        // Limpia las filas del menú que en el turno del jugador quedaron
        // ocupadas, para que no aparezcan residuos visuales.
        for (int row = startRow+7; row <= startRow+13; row++) {
            SET_CURSOR_POS(row, startCol);
            printf(CLEAR_LINE_TO_END);
        }

        // Evita que el jugador "adelante" teclas mientras se muestra
        // el daño del enemigo; esas teclas no deben filtrarse al
        // siguiente turno del jugador.
        fflush(stdin);
    }
    SET_CURSOR_POS(startRow+15, startCol);
    presioneTeclaParaContinuar();

    SET_CURSOR_POS(N+4, 0);
}
