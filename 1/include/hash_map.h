#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stddef.h>
#include <stdbool.h>

typedef struct _hash_map_t hash_map_t;
hash_map_t *hash_map_create(size_t size);
hash_map_t *hash_map_insert(hash_map_t *map,
                            const char *key,
                            long value);
bool hash_map_hash_key(hash_map_t *map, const char *key);
long hash_map_at(hash_map_t *map, const char *key);
void hash_map_free(hash_map_t *map);

#endif