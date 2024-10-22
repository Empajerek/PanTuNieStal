#include "strqueue.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int sgn(int x) {
    if (x == 0)
        return 0;
    return x < 0 ? -1 : 1;
}

int main() {
    const size_t N = 53;
    const size_t M = 150;
    unsigned long *ids = (unsigned long *)malloc(N * sizeof(unsigned long));

    for (size_t i = 0; i < N; i++) {
        ids[i] = strqueue_new();
    }

    for (size_t i = 0; i < N; i++) {
        assert(strqueue_size(ids[i]) == 0);
    }

    for (size_t i = 0; i < N; i++) {
        size_t j = (i * 9 + 43) % N;
        strqueue_insert_at(ids[j], 0, "a");
    }

    for (size_t i = 0; i < N; i++) {
        assert(strqueue_size(ids[i]) == 1);
        assert(strcmp(strqueue_get_at(ids[i], 0), "a") == 0);
    }

    for (size_t i = 0; i + 1 < N; i++) {
        assert(strqueue_comp(ids[i], ids[i + 1]) == 0);
    }

    for (size_t i = 0; i < N; i++) {
        strqueue_clear(ids[i]);
        assert(strqueue_size(ids[i]) == 0);
    }

    const char *strings[] = { "string1", "string2", "string3", "string4", "string5" };


    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            assert(strqueue_comp(ids[i], ids[j]) == 0);
        }
    }

    for (size_t i = 0; i < N; i++) {
        strqueue_insert_at(ids[i], 0, strings[i % 5]);
    }

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            assert(sgn(strqueue_comp(ids[i], ids[j])) == sgn(strcmp(strings[i % 5], strings[j % 5])));
        }
    }

    for (size_t i = 0; i < N; i++) {
        assert(strcmp(strqueue_get_at(ids[i], 0), strings[i % 5]) == 0);
    }

    for (size_t i = 0; i < N; i++) {
        strqueue_clear(ids[i]);
    }


    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < M; j++) {
            strqueue_insert_at(ids[i], 0, strings[(i * j) % 5]);
        }
    }

    for (size_t i = 0; i < N; i++) {
        strqueue_delete(ids[i]);
    }
}