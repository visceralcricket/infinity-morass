#include "storage.h"
#include "../engine/game.h"
#include <string.h>

// Macros para crear directorios correctamente dependiendo del OS
#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
#else
    #include <sys/stat.h>
    #define MKDIR(path) mkdir(path, 0777)
#endif

bool saveGame(Player *player, sessionFloor *currentSession) {
    if(!currentSession->isMapDirty) return true;
    MKDIR("saves");

    // Modificar ruta para guardar progreso dentro de carpeta saves
    // Buffer aumentado con MAX_FILENAME (MAX_USERNAME+15) para que pueda contener "saves/"
    char filename[MAX_FILENAME];
    snprintf(filename, sizeof(filename), "saves/%s.sav", player->username);
    
    // Abrir archivo y guardar
    FILE *file = fopen(filename, "wb");
    if(!file) return false;

    fwrite(player->username, sizeof(player->username), 1, file);
    fwrite(&player->x, sizeof(player->x), 1, file);
    fwrite(&player->y, sizeof(player->y), 1, file);
    fwrite(&player->combatStats, sizeof(player->combatStats), 1, file);
    
    int weaponIndex = -1;
    int armorIndex = -1;

    if(player->inventory) {
        int currentIndex = 0;
        GameObject *item = (GameObject *) listFirst(player->inventory);
        while(item) {
            if(item == player->equippedWeapon) weaponIndex = currentIndex;
            if(item == player->equippedArmor) armorIndex = currentIndex;
            item = (GameObject *) listNext(player->inventory);
            currentIndex++;
        }
    }
    fwrite(&weaponIndex, sizeof(int), 1, file);
    fwrite(&armorIndex, sizeof(int), 1, file);

    int inventorySize = player->inventory ? listSize(player->inventory) : 0;
    fwrite(&inventorySize, sizeof(int), 1, file);

    if(inventorySize > 0) {
        GameObject *currentItem = (GameObject *) listFirst(player->inventory);
        while(currentItem) {
            // Escribir el puntero del objeto real, no el puntero void*
            fwrite(currentItem, sizeof(GameObject), 1, file);
            currentItem = (GameObject *) listNext(player->inventory);
        }
    }
    fwrite(currentSession, sizeof(sessionFloor), 1, file);
    currentSession->isMapDirty = false;
    fclose(file);
    return true;
}

bool loadGame(Player *player, sessionFloor *currentSession) {
    char filename[MAX_FILENAME];
    snprintf(filename, sizeof(filename), "saves/%s.sav", player->username);

    FILE *file = fopen(filename, "rb");
    if(!file) return false;
    // Leer estadísticas base del jugador
    
    fread(player->username, sizeof(player->username), 1, file);
    fread(&player->x, sizeof(player->x), 1, file);
    fread(&player->y, sizeof(player->y), 1, file);
    fread(&player->combatStats, sizeof(player->combatStats), 1, file);

    int weaponIndex = -1;
    int armorIndex = -1;
    fread(&weaponIndex, sizeof(int), 1, file);
    fread(&armorIndex, sizeof(int), 1, file);

    player->equippedWeapon = NULL;
    player->equippedArmor = NULL;

    // IMPORTANTE: Guardamos el inventario objeto por objeto, es decir, el puntero al inventario del jugador
    // podría ser puntero colgante, por ende debemos crear un puntero nuevo y volver a almacenarlo en el heap
    player->inventory = listCreate();

    int inventorySize = 0;
    fread(&inventorySize, sizeof(int), 1, file);

    for(int i=0; i<inventorySize; i++) {
        GameObject *item = (GameObject *) malloc(sizeof(GameObject));
        fread(item, sizeof(GameObject), 1, file);
        listPushBack(player->inventory, item);
    }

    if (player->inventory) {
        int currentIndex = 0;
        GameObject *item = (GameObject *)listFirst(player->inventory);
        while (item != NULL) {
            if (currentIndex == weaponIndex) player->equippedWeapon = item;
            if (currentIndex == armorIndex) player->equippedArmor = item;
            item = (GameObject *)listNext(player->inventory);
            currentIndex++;
        }
    }
    
    if(fread(currentSession, sizeof(sessionFloor), 1, file) != 1) {
        fclose(file);
        return false;
    }
    fclose(file);
    return true;
}