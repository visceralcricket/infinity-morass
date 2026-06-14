#include "storage.h"
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

    fwrite(player, sizeof(Player), 1, file);
    /* +++
    Aquí faltará el tamaño real del inventario del jugador además de
    un puntero a la dirección de memoria de player->inventory, por ahora
    se va a ignorar el puntero al inventario del jugador.
    --- */
    
    int inventorySize = 0;
    if(player->inventory) inventorySize = listSize(player->inventory);
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
    snprintf(filename, sizeof(filename), "saves/&s.sav", player->username);

    FILE *file = fopen(filename, "rb");
    if(!file) return false;
    // Leer estadísticas base del jugador
    fread(player, sizeof(Player), 1, file);
    // IMPORTANTE: el puntero player->inventory leído es basura, hay que crear una lista nueva
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