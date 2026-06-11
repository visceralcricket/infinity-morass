#ifndef HASHMAP_H
#define HASHMAP_H

/* +++
                        === Disclaimer ===
map.c fue reemplazado por una versión ligeramente modificada (in-house) del código
personal final del laboratorio n°3 de hashmap.c con el fin de hacer el programa
más eficiente y menos lento a la hora de hacer ciertas operaciones.
--- */

typedef struct Map Map;

typedef struct MapPair {
    void * key;
    void * value;
} MapPair;

Map * map_create(int (*is_equal)(void* key1, void* key2));

void map_insert(Map * map, void * key, void * value);

void map_remove(Map * map,  char * key);

MapPair * map_search(Map * map, void * key);

MapPair * map_first(Map * map);

MapPair * map_next(Map * map);

void map_clean(Map * map);

#endif