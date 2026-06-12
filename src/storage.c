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
    // Buffer aumentado de +5 a +15 para que pueda contener "saves/"
    char filename[MAX_USERNAME + 15];
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
    if(player->inventory) inventorySize = list_size(player->inventory);
    fwrite(&inventorySize, sizeof(int), 1, file);

    if(inventorySize > 0) {
        GameObject *currentItem = (GameObject *) list_first(player->inventory);
        while(currentItem) {
            // Escribir el puntero del objeto real, no el puntero void*
            fwrite(currentItem, sizeof(GameObject), 1, file);
            currentItem = (GameObject *) list_next(player->inventory);
        }
    }
    fclose(file);
    return true;
}