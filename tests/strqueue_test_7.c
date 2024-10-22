#include "strqueue.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

int main() {
    unsigned long q1 = strqueue_new();
    strqueue_insert_at(q1, 0, "Hello world!");
    assert(strcmp(strqueue_get_at(q1, 0), "Hello world!") == 0);
    const char *s = strqueue_get_at(q1, 0);
    assert(strcmp(s, "Hello world!") == 0);
    for (size_t i = 0; i < 10; i++)
        strqueue_insert_at(q1, i + 1, "I love ice cream!");

    assert(strcmp(s, "Hello world!") == 0);

    strqueue_delete(q1);
}
