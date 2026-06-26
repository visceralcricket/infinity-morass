#ifndef HASHMAP_H
#define HASHMAP_H

#define MAX_MAP_SIZE 101

/* +++
                        === Disclaimer ===
Este archivo, inicialmente llamado map.c, fue reemplazado por una versión
ligeramente modificada (in-house) del código personal final del laboratorio
n°3 de hashmap.c con el fin de hacer el programa más eficiente y menos lento
a la hora de hacer ciertas operaciones.
--- */

typedef struct Map Map;

typedef struct MapPair {
    void * key;
    void * value;
} MapPair;

Map * mapCreate();

void mapInsert(Map *map, char *key, void *value);

void mapRemove(Map *map,  char *key);

MapPair * mapSearch(Map *map, char *key);

MapPair * mapFirst(Map *map);

MapPair * mapNext(Map *map);

void mapClean(Map *map);

#endif