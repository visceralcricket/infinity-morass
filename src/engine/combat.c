#include "combat.h"
#include "game.h"
#include "../ui/render.h"

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

        renderCombatOverlay(player, enemy, currentTurn, turnCounter, &fleeCondition);

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
