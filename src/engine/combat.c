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

bool usePotionInCombat(Player *player, int startRow, int startCol) {
    if (!player || !player->inventory) return false;

    GameObject *potions[64];
    int potionCount = 0;

    GameObject *item = (GameObject *) listFirst(player->inventory);
    while (item != NULL && potionCount < 64) {
        if (item->equip == ITEM_CONSUMABLE) {
            potions[potionCount++] = item;
        }
        item = (GameObject *) listNext(player->inventory);
    }

    int rowsUsed = potionCount + 6;

    if (potionCount == 0) {
        return false;
    }

    SET_CURSOR_POS(startRow, startCol);
    printf(CLEAR_LINE_TO_END "Elige una poción:");
    for (int i = 0; i < potionCount; i++) {
        SET_CURSOR_POS(startRow+1+i, startCol);
        printf(CLEAR_LINE_TO_END "%d) %s (+%d HP)", i+1, potions[i]->name, potions[i]->stats.currentHp);
    }
    SET_CURSOR_POS(startRow+1+potionCount, startCol);
    printf(CLEAR_LINE_TO_END "0) Cancelar");
    SET_CURSOR_POS(startRow+3+potionCount, startCol);
    printf(CLEAR_LINE_TO_END "Opción: ");
    fflush(stdout);

    int choice = -1;
    while (choice < 0) {
        int key = _getch();
        if (key == '0') {
            choice = 0;
        } else if (key >= '1' && key <= '9') {
            int n = key - '0';
            if (n <= potionCount) choice = n;
        }
    }

    bool used = false;

    if (choice > 0) {
        GameObject *chosen = potions[choice - 1];

        player->combatStats.currentHp += chosen->stats.currentHp;
        if (player->combatStats.currentHp > player->combatStats.maxHp) {
            player->combatStats.currentHp = player->combatStats.maxHp;
        }

        listFirst(player->inventory);
        while (listCurrent(player->inventory) != chosen && listCurrent(player->inventory) != NULL) {
            listNext(player->inventory);
        }
        if (listCurrent(player->inventory) == chosen) {
            listPopCurrent(player->inventory);
            free(chosen);
        }
        used = true;
    }

    for (int r = 0; r <= rowsUsed; r++) {
        SET_CURSOR_POS(startRow+r, startCol);
        printf(CLEAR_LINE_TO_END);
    }
    fflush(stdout);    
    return used;
}