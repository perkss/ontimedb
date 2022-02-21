#include "hash_table.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    void *value;
} hash_table_entry;

struct hash_table {
    hash_table_entry *entries;  // hash slots
    size_t capacity;    // size of _entries array
    size_t length;      // number of items in hash table
};

#define INITIAL_CAPACITY 16  // must not be zero

hash_table *hash_table_create(void) {
    hash_table *table = malloc(sizeof(hash_table));

    if (table == NULL) {
        return NULL;
    }

    table->length = 0;
    table->capacity = INITIAL_CAPACITY;

    table->entries = calloc(table->capacity, sizeof(hash_table_entry));
    if (table->entries == NULL) {
        free(table); // error, free table before we return!
        return NULL;
    }
    return table;
}

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

static uint64_t hash_key(const char *key) {
    uint64_t hash = FNV_OFFSET;
    for (const char *p = key; *p; p++) {
        hash ^= (uint64_t) (unsigned char) (*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

void *hash_table_get(hash_table *table, const char *key) {
    // AND hash with capacity-1 to ensure it's within entries array.
    uint64_t hash = hash_key(key);
    size_t index = (size_t) (hash & (uint64_t) (table->capacity - 1));

    // Loop till we find an empty entry.
    while (table->entries[index].key != NULL) {
        if (strcmp(key, table->entries[index].key) == 0) {
            // Found key, return value.
            return table->entries[index].value;
        }
        // Key wasn't in this slot, move to next (linear probing).
        index++;
        if (index >= table->capacity) {
            // At end of entries array, wrap around.
            index = 0;
        }
    }
    return NULL;
}

// Internal function to set an entry (without expanding table).
static const char *hash_table_set_entry(hash_table_entry *entries, size_t capacity,
                                        const char *key, void *value, size_t *plength) {
    // AND hash with capacity-1 to ensure it's within entries array.
    uint64_t hash = hash_key(key);
    size_t index = (size_t) (hash & (uint64_t) (capacity - 1));

    // Loop till we find an empty entry.
    while (entries[index].key != NULL) {
        if (strcmp(key, entries[index].key) == 0) {
            // Found key (it already exists), update value.
            entries[index].value = value;
            return entries[index].key;
        }
        // Key wasn't in this slot, move to next (linear probing).
        index++;
        if (index >= capacity) {
            // At end of entries array, wrap around.
            index = 0;
        }
    }

    // Didn't find key, allocate+copy if needed, then insert it.
    if (plength != NULL) {
        key = strdup(key);
        if (key == NULL) {
            return NULL;
        }
        (*plength)++;
    }
    entries[index].key = (char *) key;
    entries[index].value = value;
    return key;
}

static bool hash_table_expand(hash_table *table) {
    // Allocate new entries array.
    size_t new_capacity = table->capacity * 2;
    if (new_capacity < table->capacity) {
        return false;  // overflow (capacity would be too big)
    }
    hash_table_entry *new_entries = calloc(new_capacity, sizeof(hash_table_entry));
    if (new_entries == NULL) {
        return false;
    }

    // Iterate entries, move all non-empty ones to new table's entries.
    for (size_t i = 0; i < table->capacity; i++) {
        hash_table_entry entry = table->entries[i];
        if (entry.key != NULL) {
            hash_table_set_entry(new_entries, new_capacity, entry.key,
                                 entry.value, NULL);
        }
    }

    // Free old entries array and update this table's details.
    free(table->entries);
    table->entries = new_entries;
    table->capacity = new_capacity;
    return true;
}

const char *hash_table_set(hash_table *table, const char *key, void *value) {
    assert(value != NULL);
    if (value == NULL) {
        return NULL;
    }

    // If length will exceed half of current capacity, expand it.
    if (table->length >= table->capacity / 2) {
        if (!hash_table_expand(table)) {
            return NULL;
        }
    }

    // Set entry and update length.
    return hash_table_set_entry(table->entries, table->capacity, key, value,
                                &table->length);
}

size_t hash_table_length(hash_table *table) {
    return table->length;
}

hti hash_table_iterator(hash_table *table) {
    hti it;
    it._table = table;
    it._index = 0;
    return it;
}

bool hash_table_next(hti *it) {
    // Loop till we've hit end of entries array.
    hash_table *table = it->_table;
    while (it->_index < table->capacity) {
        size_t i = it->_index;
        it->_index++;
        if (table->entries[i].key != NULL) {
            // Found next non-empty item, update iterator key and value.
            hash_table_entry entry = table->entries[i];
            it->key = entry.key;
            it->value = entry.value;
            return true;
        }
    }
    return false;
}

