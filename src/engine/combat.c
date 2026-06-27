#include "combat.h"
#include "../tdas/heap.h"

void combatMode(Player *player, Enemy *enemy) {

    printf("\n\t¡Te has topado con un %s! ¡Comienza el combate!\n", enemy->enemyName);
    printf("\n\t");
    presioneTeclaParaContinuar();

    Heap *colaTurnos = heapCreate();

    int playerPriority = BASE_TURN_TICKS / player->combatStats.speed;
    int enemyPriority = BASE_TURN_TICKS / enemy->combatStats.speed;

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
    if (fleeCondition) {
        printf("\n\t¡Has huido del %s! Vives para luchar otro día...\n", enemy->enemyName);
    }
    
    else if (enemy->combatStats.currentHp <= 0) {
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

        /* +++
        Drop de jefe: al derrotar un jefe, suelta un pergamino de historia.
        Por ahora 100% garantizado; para bajarlo a 30% basta con envolverlo en
        if(rand() % 100 < 30) igual que el drop de poción de arriba.
        --- */
        if (enemy->isBoss) {
            GameObject *scrollDrop = chooseRandomScroll();
            if (scrollDrop) {
                listPushBack(player->inventory, scrollDrop);
                printf("\n\t" FORMAT_BOLD COLOR_YELLOW "El jefe ha dejado caer: %s" FORMAT_RESET "\n", scrollDrop->name);
            }
        }

       /* +++
       No se incluye objmap.h actualmente desde combat.h, considerar esto.
       
       TODO: cuando el inventario esté implementado, recorrer enemy->drops
       (List *) y agregar cada GameObject al player->inventory.
       Ej:
        void *drop;
        listFirst(enemy->drops);
        while ((drop = listCurrent(enemy->drops)) != NULL) {
            listPushBack(player->inventory, drop);
            drop = listNext(enemy->drops);  
        }
        --- */
    }

    // Pausa siempre, también al morir, para que el mensaje de GAME OVER
    // pueda leerse antes de volver al flujo principal.
    if(player->combatStats.currentHp > 0) {
        printf("\t");
        presioneTeclaParaContinuar();
    }
}