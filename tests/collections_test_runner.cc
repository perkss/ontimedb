#include <iostream>
#include <gtest/gtest.h>

extern "C" {
#include "hash_table.h"
}

TEST(TESTCOLLECTION, TestHashTableGet) {
    hash_table *counts = hash_table_create();
    if (counts == NULL) {
        //exit_nomem();
    }

    char word[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    // Why cannot define this with malloc?
    int jx = 1;
    int *j = &jx;
    if (hash_table_set(counts, word, j) == NULL) {
//        exit_nomem();
    }

    void *found = hash_table_get(counts, word);

    ASSERT_EQ(1, *((int *) found));
}
