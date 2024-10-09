#include "has_map.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

// Вспомогательная хэш-функция
static size_t hash(const char *key) {
    size_t hash = 0;
    size_t prime = 31;

    while (*key) {
        hash = hash * prime + (unsigned char)(*key);
        key++;
    }

    return hash;
}

// Вспомогательная функция для расширения хэш-таблицы
static Hash_Map *hash_map_expand(Hash_Map *map) {
    assert(map != NULL);
    Hash_Map *expanded = hash_map_create(map->size * 2);

    for (size_t idx = 0; idx < map->size; idx++) {
        if (map->entries[idx].key != NULL) {
            expanded = hash_map_insert(expanded, 
                                       map->entries[idx].key, 
                                       map->entries[idx].value);
        }
    }
    hash_map_free(map);

    return expanded;
}

// Создание хэш-таблицы заданного размера
Hash_Map *hash_map_create(size_t size) {
    Hash_Map *map = malloc(sizeof(Hash_Map));
    assert(map != NULL);

    map->size = size;
    map->entries = calloc(map->size, sizeof(Hash_Map_Entry));
    assert(map->entries != NULL);

    return map;
}

// Вставка ключа и значения в хэш-таблицу
Hash_Map *hash_map_insert(Hash_Map *map, const char *key, const char *value) {
    assert(map != NULL);
    assert(key != NULL);

    size_t idx = hash(key) % map->size;

    // Линейное пробирование для поиска свободного места
    while (map->entries[idx].key != NULL) {
        idx += 1;

        if (idx == map->size) {
            return hash_map_insert(hash_map_expand(map), key, value);
        }
    }

    // Копируем ключ
    map->entries[idx].key = calloc(strlen(key) + 1, sizeof(char));
    strcpy(map->entries[idx].key, key);

    // Копируем значение
    map->entries[idx].value = calloc(strlen(value) + 1, sizeof(char));
    strcpy(map->entries[idx].value, value);

    return map;
}

// Проверка, содержит ли хэш-таблица ключ
bool hash_map_has_key(Hash_Map *map, const char *key) {
    assert(map != NULL);
    assert(key != NULL);

    for (size_t idx = hash(key) % map->size; idx < map->size; idx++) {
        char *current = map->entries[idx].key;

        if (current == NULL) continue;

        if (!strcmp(current, key)) return true;
    }

    return false;
}

// Получение значения по ключу
char *hash_map_at(Hash_Map *map, const char *key) {
    assert(map != NULL);
    assert(key != NULL);
    assert(hash_map_has_key(map, key));

    for (size_t idx = hash(key) % map->size; idx < map->size; idx++) {
        char *current = map->entries[idx].key;

        if (current == NULL) continue;

        if (!strcmp(current, key)) return map->entries[idx].value;
    }

    assert(false && "Key not found in hash map.");
    return NULL;
}

void hash_map_print(Hash_Map *map) {
    assert(map != NULL);

    printf("Hash Map Contents:\n");
    for (size_t idx = 0; idx < map->size; idx++) {
        if (map->entries[idx].key != NULL) {
            printf("Index %zu: Key: %s, Value: %s\n", idx, map->entries[idx].key, map->entries[idx].value);
        } else {
            printf("Index %zu: (empty)\n", idx);
        }
    }
}

// Освобождение памяти, выделенной для хэш-таблицы
void hash_map_free(Hash_Map *map) {
    assert(map != NULL);

    for (size_t idx = 0; idx < map->size; idx++) {
        if (map->entries[idx].key != NULL) {
            free(map->entries[idx].key);
            free(map->entries[idx].value);  // Освобождаем память для значения
        }
    }

    free(map->entries);
    free(map);
}

int main() {
    // Создаем хэш-таблицу размером 10
    Hash_Map *map = hash_map_create(10);

    // Вставляем несколько ключей и значений
    map = hash_map_insert(map, "apple", "green");
    map = hash_map_insert(map, "banana", "yellow");
    map = hash_map_insert(map, "cherry", "red");
    map = hash_map_insert(map, "grape", "purple");
    map = hash_map_insert(map, "orange", "orange");

    // Выводим содержимое хэш-таблицы
    hash_map_print(map);

    // Проверяем, существует ли ключ в таблице
    const char *key = "banana";
    if (hash_map_has_key(map, key)) {
        printf("Key '%s' is in the hash map with value '%s'.\n", key, hash_map_at(map, key));
    } else {
        printf("Key '%s' not found in the hash map.\n", key);
    }

    // Освобождаем память, выделенную для хэш-таблицы
    hash_map_free(map);

    return 0;
}
