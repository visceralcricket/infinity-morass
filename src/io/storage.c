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

bool saveGame(Player *player) {

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
    fclose(file);
    return true;
}

bool loadGame(Player *player) {

    char filename[MAX_FILENAME];
    snprintf(filename, sizeof(filename), "saves/%s.sav", player->username);

    FILE *file = fopen(filename, "rb");
    if(!file) return false;
    // Leer estadísticas base del jugador
    
    fread(player->username, sizeof(player->username), 1, file);
    fread(&player->x, sizeof(player->x), 1, file);
    fread(&player->y, sizeof(player->y), 1, file);
    fread(&player->combatStats, sizeof(player->combatStats), 1, file);

    // IMPORTANTE: Guardamos el inventario objeto por objeto, por ende el puntero al inventario del jugador
    // podría ser puntero colgante, por ende debemos crear un puntero nuevo
    player->inventory = listCreate();

    int inventorySize = 0;
    fread(&inventorySize, sizeof(int), 1, file);

    for(int i=0; i<inventorySize; i++) {
        GameObject *item = (GameObject *) malloc(sizeof(GameObject));
        fread(item, sizeof(GameObject), 1, file);
        listPushBack(player->inventory, item);
    }

    fclose(file);
    return true;
}