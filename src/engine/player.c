#include "player.h"
#include "../tdas/list.h"
#include <stdio.h>
#include <stdlib.h>

void useItemExploration(Player *player, GameObject *item) {
    if (!player || !player->inventory) return;

    GameObject *currentItem = (GameObject *) listCurrent(player->inventory);

    if (!item) return;

    if (item->equip == ITEM_CONSUMABLE) {
        if (player->combatStats.currentHp == player->combatStats.maxHp) {
            printf("\n\tYa cuentas con la máxima salud.\n");
            return;
        }

        player->combatStats.currentHp += item->stats.currentHp;
        if (player->combatStats.currentHp > player->combatStats.maxHp) {
            player->combatStats.currentHp = player->combatStats.maxHp;
        }
        printf("\n\tHas usado %s. HP actual: %d/%d\n", item->name,
            player->combatStats.currentHp, player->combatStats.maxHp);
        
        // Eliminar el consumible del inventario
        listPopCurrent(player->inventory);
        free(item); 

    } else if (item->equip == ITEM_EQUIPPABLE) {
        if (currentItem == player->equippedWeapon || currentItem == player->equippedArmor) {
            printf("\n\tEl objeto ya está equipado.\n");
            return;
        }
        if (item->stats.attack > 0) {
            if (player->equippedWeapon) {
                player->combatStats.attack -= player->equippedWeapon->stats.attack;
                player->combatStats.speed -= player->equippedWeapon->stats.speed;
            }
            player->equippedWeapon = item;
            player->combatStats.attack += player->equippedWeapon->stats.attack;
            player->combatStats.speed += player->equippedWeapon->stats.speed;

            printf("\n\tHas equipado %s como arma.\n", item->name);
        } else if (item->stats.defense > 0) {
            if (player->equippedArmor) {
                player->combatStats.defense -= player->equippedArmor->stats.defense;
                player->combatStats.speed -= player->equippedArmor->stats.speed;
            }
            player->equippedArmor = item;
            player->combatStats.defense += player->equippedArmor->stats.defense;
            player->combatStats.speed += player->equippedArmor->stats.speed;

            printf("\n\tHas equipado %s como armadura.\n", item->name);
        }
    } 
}