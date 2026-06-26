#include "render.h"
#include "../tdas/hashmap.h"

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

            printf("%s [%s]", item->name, tipo);
            /* +++
             El especificador de formato %+d mostrará el signo del valor entero que se imprima, por
             ejemplo:
             * si item->stats.attack = -5, se imprimirá "-5",
             * si item->stats.speed = 5, se imprimirá "+5"
             --- */
            if(item->stats.maxHp) printf(" %+d HP", item->stats.maxHp);
            if(item->stats.attack) printf(" %+d ATK", item->stats.attack);
            if(item->stats.defense) printf(" %+d DEF", item->stats.defense);
            if(item->stats.speed) printf(" %+d SPD", item->stats.speed);

            currentRow++;
            item = (GameObject *) listNext(player->inventory);
        }

        // Pista de control: leer pergaminos
        SET_CURSOR_POS(currentRow+1, startCol);
        printf(FORMAT_DIM "Presiona 'e' para usar." FORMAT_RESET);
        
        if (selectedItem != NULL) {
            listFirst(player->inventory);
            while (listCurrent(player->inventory) != selectedItem && listCurrent(player->inventory) != NULL) {
                listNext(player->inventory);
            }
        }
    }
    SET_CURSOR_POS(N+4, 0);
}

/* +++
Pantalla de lectura de un pergamino. Imprime el lore con un word-wrap simple
para que el texto (hasta MAX_LORE_LENGTH caracteres en una sola línea) no se
desborde a lo ancho de la terminal.
--- */
void renderScrollOverlay(GameObject *scroll) {
    limpiarPantalla();
    separador1();
    printf("\t\t" FORMAT_BOLD COLOR_YELLOW "%s" FORMAT_RESET "\n", scroll->name);
    separador1();
    printf("\n\t");

    const int MAX_WIDTH = 60;   // columnas antes de cortar
    int lineLen = 0;
    const char *p = scroll->lore;
    char word[64];

    while (*p) {
        int wi = 0;
        // leer una palabra (hasta espacio o fin), con tope de seguridad
        while (*p && *p != ' ' && wi < (int)(sizeof(word) - 1)) {
            word[wi++] = *p++;
        }
        word[wi] = '\0';
        while (*p == ' ') p++;   // saltar espacios

        if (lineLen + wi > MAX_WIDTH) {   // no cabe: salto de línea
            printf("\n\t");
            lineLen = 0;
        }
        printf("%s ", word);
        lineLen += wi + 1;
    }

    printf("\n\n");
    separador1();
    printf("\t" FORMAT_DIM "Presiona ESC para volver al inventario." FORMAT_RESET "\n");
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

void renderGameOverScreen(const char *killerName) {
    limpiarPantalla();
    separador1();
    printf("\n\t\t" FORMAT_BOLD COLOR_RED "HAS SIDO DERROTADO!" FORMAT_RESET "\n");
    printf("\t   Caíste ante las garras de " FORMAT_BOLD "%s" FORMAT_RESET "\n\n", killerName);
    printf("\t\t\t   " FORMAT_DIM "GAME OVER" FORMAT_RESET "\n\n");
    printf("\t " FORMAT_DIM "La oscuridad de la mazmorra te arrastra hacia sus entrañas..." FORMAT_RESET "\n\n");
    separador1();
    printf("\n\tDeseas reencarnar e intentarlo de nuevo? (S/N)\n\t< ");
}

void showGlossary(Map *objectMap, Map *enemyMap) {
    limpiarPantalla();
    separador1();
    printf("\t\t === Archivos de las profundidades ===\n");
    separador1();

    printf("\n\t\t -- Enemigos de la mazmorra --\n\n");
    if (!enemyMap) {
        printf("\t El bestiario no está disponible.\n");
    } else {
        MapPair *enemyPair = mapFirst(enemyMap);
        while (enemyPair) {
            Enemy *enemy = (Enemy *) enemyPair->value;
            if (enemy->isBoss) printf("[JEFE] ");
            printf("\t- %s: HP %d | ATK %d | DEF %d | SPD %d\n", enemy->enemyName,
                enemy->combatStats.maxHp, enemy->combatStats.attack,
                enemy->combatStats.defense, enemy->combatStats.speed);
            enemyPair = mapNext(enemyMap);
        }
    }
    printf("\n");
    separador2();

    printf("\n\t\t -- Objetos de la mazmorra --\n\n");
    if (!objectMap) {
        printf("\t El inventario de objetos no está disponible.\n");
    } else {
        MapPair *objectPair = mapFirst(objectMap);
        while (objectPair) {
            GameObject *object = (GameObject *) objectPair->value;
            const char *tipo;
            switch (object->equip) {
                case ITEM_CONSUMABLE: tipo = "Consumible"; break;
                case ITEM_EQUIPPABLE: tipo = "Equipable";  break;
                case ITEM_KEY:        tipo = "Llave/Clave"; break;
                default:              tipo = "Desconocido"; break;
            }
            printf("\t- %s [%s]: %+d HP | %+d ATK | %+d DEF | %+d SPD\n", object->name, tipo,
                object->stats.maxHp, object->stats.attack,
                object->stats.defense, object->stats.speed);
            objectPair = mapNext(objectMap);
        }
    }
    printf("\n");
    presioneTeclaParaContinuar();
}