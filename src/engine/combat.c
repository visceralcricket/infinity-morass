#include "combat.h"
#include "game.h"
#include "../tdas/heap.h"
#include "../ui/render.h"

void combatMode(Player *player, Enemy *enemy) {

    printf("\n\t¡Te has topado con un %s! ¡Comienza el combate!\n", enemy->enemyName);
    presioneTeclaParaContinuar();

    Heap *colaTurnos = heapCreate();

    int playerPriority = 1000 / player->combatStats.speed;
    int enemyPriority = 1000 / enemy->combatStats.speed;

    int playerNextTurn = playerPriority;
    int enemyNextTurn = enemyPriority;

    int turnCounter = 0;
    bool fleeCondition = false;

    void *currentTurn = NULL;

    heapPush(colaTurnos, player, INT_MAX - playerNextTurn);
    heapPush(colaTurnos, enemy, INT_MAX - enemyNextTurn);

    while(player->combatStats.currentHp > 0 && enemy->combatStats.currentHp > 0) {
        turnCounter++;

        currentTurn = heapTop(colaTurnos);
        heapPop(colaTurnos);

        renderCombatOverlay(player, enemy, currentTurn, turnCounter, &fleeCondition);

        if (fleeCondition) break;

        if (currentTurn == player) {
            playerNextTurn += playerPriority;
            heapPush(colaTurnos, player, INT_MAX - playerNextTurn);
        } else {
            enemyNextTurn += enemyPriority;
            heapPush(colaTurnos, enemy, INT_MAX - enemyNextTurn);
        }

        fflush(stdout);
    }
    
    heapDestroy(colaTurnos);

    limpiarPantalla();
    if (player->combatStats.currentHp <= 0) {
        printf("\n\t¡Has sido derrotado! Tal parece que no lograrás ser el más fuerte de la mazmorra...\n");
        printf("\n\t\tGAME OVER\n");
        printf("\n\t¡Inténtalo de nuevo! ¡No te rindas!\n");
    } else {
        printf("\n\t¡Has derrotado al %s! ¡Felicidades!\n", enemy->enemyName);

        if (rand() % 100 < 30) 
        { 
            GameObject *potionDrop = chooseRandomPotion();
            if (potionDrop)
            {
                listPushBack(player->inventory, potionDrop);
                printf("\n\tHas obtenido: %s\n", potionDrop->name);
            }
        }
       
        // TODO: cuando el inventario esté implementado, recorrer enemy->drops
        // (List *) y agregar cada GameObject al player->inventory.
        // Ej:
        // void *drop;
        // listFirst(enemy->drops);
        // while ((drop = listCurrent(enemy->drops)) != NULL) {
        //     listPushBack(player->inventory, drop);
        //     drop = listNext(enemy->drops);
        // }
    }
    printf("\t");
    presioneTeclaParaContinuar();
}
