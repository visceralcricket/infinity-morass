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
    int option;
    int damage;
    bool fleeCondition = false;

    void *currentTurn = NULL;

    heap_push(colaTurnos, player, INT_MAX - playerNextTurn);
    heap_push(colaTurnos, enemy, INT_MAX - enemyNextTurn);

    while(player->combatStats.currentHp > 0 && enemy->combatStats.currentHp > 0) {
        turnCounter++;

        currentTurn = heap_top(colaTurnos);
        heap_pop(colaTurnos);

        printf("\n\tTurno %d: ", turnCounter);
        if (currentTurn == player) {
            printf("\n\t¡Es tu turno! Elige una acción:\n");
            scanf("%d", &option);
            while (option < 1 || option > 3) {
                scanf("%d", &option);
            }
            switch(option) {
                case 1:
                    damage = player->combatStats.attack - enemy->combatStats.defense;
                    if (damage <= 0) damage = 1;
                    enemy->combatStats.currentHp -= damage;
                    printf("\n\tHas infligido %d puntos de daño.", damage);
                    break;
                case 2:
                    printf("En espera de implementación: usar objeto");
                    break;
                case 3:
                    if (player->combatStats.speed > enemy->combatStats.speed) {
                        printf("\n\tHas huido exitosamente del combate.");
                        fleeCondition = true;
                        break;
                    } else {
                        printf("\n\tHas intentado huir, pero el enemigo es más rápido. ¡No puedes escapar!");
                        break;
                    }
                default:
                    break;
            }

            if (fleeCondition) break;
            
            playerNextTurn += playerPriority;
            heap_push(colaTurnos, player, INT_MAX - playerNextTurn);
        }
        else {
            damage = enemy->combatStats.attack - player->combatStats.defense;
            if (damage <= 0) damage = 1;
            player->combatStats.currentHp -= damage;
            printf("\n\tEl enemigo te ha infligido %d puntos de daño.", damage);

            enemyNextTurn += enemyPriority;
            heap_push(colaTurnos, enemy, INT_MAX - enemyNextTurn);
        }

        fflush(stdout);
        presioneTeclaParaContinuar();
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
    }
    presioneTeclaParaContinuar();
}