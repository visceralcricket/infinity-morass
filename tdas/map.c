#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "map.h"

/* +++
                        === Disclaimer ===
map.c reemplazado por una versión ligeramente modificada (a mano) del código
personal final del laboratorio n°3 de hashmap.c con el fin de hacer el programa
más eficiente y menos lento a la hora de hacer ciertas operaciones.
--- */

struct Map {
    MapPair ** buckets;
    long size; 
    long capacity; 
    long current; 
};


static long hash(char * key, long capacity) {
    unsigned long hash = 0;
    char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash * 32 + *ptr;
    }
    return hash % capacity;
}


Map * map_create(int (*is_equal)(void* key1, void* key2)) {
    Map * map = (Map *)malloc(sizeof(Map));
    map->capacity = 101; // Capacidad inicial por defecto
    map->buckets = (MapPair **)calloc(map->capacity, sizeof(MapPair *));
    map->size = 0;
    map->current = -1;
    return map;
}


MapPair * map_search(Map * map, void * key) {
    long idx = hash((char *)key, map->capacity);
    while (map->buckets[idx] != NULL) {
        if (map->buckets[idx]->key != NULL && 
            strcmp(map->buckets[idx]->key, (char *)key) == 0) {
            map->current = idx;
            return map->buckets[idx];
        }
        idx = (idx + 1) % map->capacity;
    }
    return NULL;
}

void map_remove(Map * map,  char * key) {    
    MapPair *tmp = map_search(map, key); // Buscar key en mapa
    if(tmp!=NULL) { // Si el par existe
        tmp->key = NULL; // Invalidar dicho par
        map->size--; // Actualizar size del arreglo
    }
}

static void enlarge(Map * map) {
    MapPair ** old_buckets = map->buckets;
    long old_capacity = map->capacity;
    map->capacity *= 2;
    map->buckets = (MapPair **)calloc(map->capacity, sizeof(MapPair *));
    map->size = 0;

    for (long i = 0; i < old_capacity; i++) {
        if (old_buckets[i] != NULL) {
            map_insert(map, old_buckets[i]->key, old_buckets[i]->value);
            free(old_buckets[i]);
        }
    }
    free(old_buckets);
}

void map_insert(Map * map, void * key, void * value) {
    if (map->size > map->capacity * 0.7) enlarge(map);
    
    long idx = hash((char *)key, map->capacity);
    while (map->buckets[idx] != NULL) {
        if(map->buckets[idx]->key != NULL && (strcmp(map->buckets[idx]->key, (char *)key) == 0)) {
            map->buckets[idx]->value = value;
            return;
        }
        idx = (idx + 1) % map->capacity;
    }
    
    MapPair * new_pair = (MapPair *)malloc(sizeof(MapPair));
    new_pair->key = key;
    new_pair->value = value;
    map->buckets[idx] = new_pair;
    map->size++;
}

// Iteradores
MapPair * map_first(Map * map) {
    for (long i = 0; i < map->capacity; i++) {
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {  // Verificación necesaria
            map->current = i;
            return map->buckets[i];
        }
    }
    return NULL;
}

MapPair * map_next(Map * map) {
    for (long i = map->current + 1; i < map->capacity; i++) {
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {  // Verificación necesaria
            map->current = i;
            return map->buckets[i];
        }
    }
    return NULL;
}

void map_clean(Map * map) {
    for (long i = 0; i < map->capacity; i++) {
        if (map->buckets[i] != NULL) free(map->buckets[i]);
    }
    free(map->buckets);
    free(map);
}