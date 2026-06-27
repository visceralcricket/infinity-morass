#include "player.h"
#include "../tdas/list.h"
#include <stdio.h>
#include <stdlib.h>

void useItemExploration(Player *player, GameObject *item) {
    if (!player || !player->inventory) return;

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
        if (item == player->equippedWeapon || item == player->equippedArmor) {
            printf("\n\tEl objeto ya está equipado.\n");
            return;
        }

        if (item->equipSlot == SLOT_WEAPON) {
            // Quitar stats del arma anterior, si había una
            if (player->equippedWeapon) {
                player->combatStats.attack  -= player->equippedWeapon->stats.attack;
                player->combatStats.speed   -= player->equippedWeapon->stats.speed;
            }
            player->equippedWeapon = item;
            player->combatStats.attack  += item->stats.attack;
            player->combatStats.speed   += item->stats.speed;

            printf("\n\tHas equipado %s como arma.\n", item->name);

        } else if (item->equipSlot == SLOT_ARMOR) {
            // Quitar stats de la armadura anterior, si había una
            if (player->equippedArmor) {
                player->combatStats.attack  -= player->equippedArmor->stats.attack;
                player->combatStats.defense -= player->equippedArmor->stats.defense;
                player->combatStats.speed   -= player->equippedArmor->stats.speed;
                player->combatStats.maxHp   -= player->equippedArmor->stats.maxHp;
                if (player->combatStats.currentHp > player->combatStats.maxHp)
                    player->combatStats.currentHp = player->combatStats.maxHp;
            }
            player->equippedArmor = item;
            player->combatStats.attack  += item->stats.attack;
            player->combatStats.defense += item->stats.defense;
            player->combatStats.speed   += item->stats.speed;
            player->combatStats.maxHp   += item->stats.maxHp;

            printf("\n\tHas equipado %s como armadura.\n", item->name);
        }
    }
}