#include <stdbool.h>
#include "combat-system.h"
#include "tdas/heap.h"
#include "game.h"


void combatMode(Player *player, Enemy *enemy) {

    printf("\n\t¡Te has topado con un %s! ¡Comienza el combate!\n", enemy->enemyName);
    presioneTeclaParaContinuar();

    Heap *colaTurnos = heap_create();

    int playerPriority = 1000 / player->combatStats.speed;
    int enemyPriority = 1000 / enemy->combatStats.speed;

    int playerNextTurn = playerPriority;
    int enemyNextTurn = enemyPriority;

    int turnCounter = 0;
    bool fleeCondition = false;

    void *currentTurn = NULL;

    heap_push(colaTurnos, player, INT_MAX - playerNextTurn);
    heap_push(colaTurnos, enemy, INT_MAX - enemyNextTurn);

    while(player->combatStats.currentHp > 0 && enemy->combatStats.currentHp > 0) {
        turnCounter++;

        currentTurn = heap_top(colaTurnos);
        heap_pop(colaTurnos);

        showCombat(player, enemy, currentTurn, turnCounter, &fleeCondition);

        if (fleeCondition) break;

        if (currentTurn == player) {
            playerNextTurn += playerPriority;
            heap_push(colaTurnos, player, INT_MAX - playerNextTurn);
        } else {
            enemyNextTurn += enemyPriority;
            heap_push(colaTurnos, enemy, INT_MAX - enemyNextTurn);
        }

        fflush(stdout);
    }

    while(heap_top(colaTurnos) != NULL) {
        heap_pop(colaTurnos);
    }
    free(colaTurnos);

    limpiarPantalla();
    if (player->combatStats.currentHp <= 0) {
        printf("\n\t¡Has sido derrotado! Tal parece que no lograrás ser el más fuerte de la mazmorra...\n");
        printf("\n\t\tGAME OVER\n");
        printf("\n\t¡Inténtalo de nuevo! ¡No te rindas!\n");
    } else {
        printf("\n\t¡Has derrotado al %s! ¡Felicidades!\n", enemy->enemyName);

        // TODO: cuando el inventario esté implementado, recorrer enemy->drops
        // (List *) y agregar cada GameObject al player->inventory.
        // Ej:
        // void *drop;
        // list_first(enemy->drops);
        // while ((drop = list_current(enemy->drops)) != NULL) {
        //     list_pushBack(player->inventory, drop);
        //     drop = list_next(enemy->drops);
        // }
    }
    presioneTeclaParaContinuar();
}


void showCombat(Player *player, Enemy *enemy, void *currentTurn, int turnCounter, bool *fleeCondition) {

    int startRow = 5;
    int startCol = 75;
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

        SET_CURSOR_POS(startRow+11, startCol);
        printf(CLEAR_LINE_TO_END "Opción: ");
        fflush(stdout);
        scanf("%d", &option);
        while (getchar() != '\n');

        while (option < 1 || option > 3) {
            SET_CURSOR_POS(startRow+11, startCol);
            printf(CLEAR_LINE_TO_END "Opción inválida, intenta de nuevo: ");
            fflush(stdout);
            scanf("%d", &option);
            while (getchar() != '\n');
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

    presioneTeclaParaContinuarEnPos(startRow+15, startCol);

    SET_CURSOR_POS(N+4, 0);
}