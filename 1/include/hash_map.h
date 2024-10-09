#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdbool.h>
#include <stddef.h>

typedef struct _Hash_Map_Entry {
    char *key;
    char *value;
} Hash_Map_Entry;

typedef struct _Hash_Map {
    Hash_Map_Entry *entries;
    size_t size;
} Hash_Map;

Hash_Map *hash_map_create(size_t size);
Hash_Map *hash_map_insert(Hash_Map *map, 
                          const char *key, 
                          const char *value);
bool hash_map_has_key(Hash_Map *map, const char *key);
char *hash_map_at(Hash_Map *map, const char *key);
bool hash_map_remove(Hash_Map *map, const char *key);
void hash_map_print(Hash_Map *map);
void hash_map_free(Hash_Map *map);

#endif