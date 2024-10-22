#include "strqueue.h"

#include <cassert>
#include <cstring>

using cxx::strqueue_new;
using cxx::strqueue_insert_at;
using cxx::strqueue_get_at;
using cxx::strqueue_remove_at;
using cxx::strqueue_comp;
using cxx::strqueue_clear;
using cxx::strqueue_delete;
using cxx::strqueue_size;

int main() {

    // No queues.
    strqueue_delete(04032);
    strqueue_insert_at(123, 234, "a");
    assert(strqueue_get_at(1243, 432) == NULL);
    strqueue_remove_at(0, 0);
    assert(strqueue_comp(2433, 424324) == 0);
    assert(strqueue_size(0) == 0);
    strqueue_clear(0);

    // Single queue.
    unsigned long q1 = strqueue_new(); // q1: []

    assert(strqueue_size(q1) == 0);
    strqueue_clear(q1);

    strqueue_insert_at(q1, 0, "a"); // q1: ["a"]
    assert(strqueue_size(q1) == 1);

    strqueue_insert_at(q1, 0, "b"); // q1: ["b", "a"]
    assert(strqueue_size(q1) == 2);

    strqueue_insert_at(q1, 1, "c"); // q1: ["b", "c", "a"]
    assert(strqueue_size(q1) == 3);

    assert(strqueue_comp(q1, q1) == 0);
    assert(strcmp(strqueue_get_at(q1, 0), "b") == 0);
    assert(strcmp(strqueue_get_at(q1, 1), "c") == 0);
    assert(strcmp(strqueue_get_at(q1, 2), "a") == 0);
    assert(strqueue_get_at(q1, 3) == NULL);

    strqueue_remove_at(q1, 1); // q1: ["b", "a"]
    assert(strqueue_size(q1) == 2);
    assert(strcmp(strqueue_get_at(q1, 0), "b") == 0);
    assert(strcmp(strqueue_get_at(q1, 1), "a") == 0);
    assert(strqueue_get_at(q1, 2) == NULL);

    strqueue_clear(q1); // q1: []
    assert(strqueue_size(q1) == 0);
    assert(strqueue_get_at(q1, 0) == NULL);

    // Multiple queues.
    unsigned q2 = strqueue_new(); // q2: []
    strqueue_insert_at(q2, 0, "abcde"); // q2: ["abcde"]
    strqueue_insert_at(q2, 0, "fghij"); // q2: ["fghij", "abcde"]
    assert(strqueue_size(q2) == 2);
    assert(strcmp(strqueue_get_at(q2, 0), "fghij") == 0);
    assert(strcmp(strqueue_get_at(q2, 1), "abcde") == 0);

    assert(strqueue_comp(q1, q2) == -1);

    strqueue_insert_at(q1, 0, "fghij"); // q1: ["fghij"]
    strqueue_insert_at(q1, 1, "abcde"); // q1: ["fghij", "abcde"]

    assert(strqueue_comp(q1, q2) == 0);

    strqueue_remove_at(q2, 10); // q2: ["fghij", "abcde"]
    strqueue_remove_at(q2, 3); // q2: ["fghij", "abcde"]
    strqueue_remove_at(q2, 2); // q2: ["fghij", "abcde"]
    strqueue_remove_at(q1, 2); // q1: ["fghij", "abcde"]
    strqueue_remove_at(q2, -1); // q2: ["fghij", "abcde"]
    strqueue_remove_at(q1, -1); // q1: ["fghij", "abcde"]

    assert(strqueue_size(q1) == 2);
    assert(strqueue_size(q2) == 2);
    assert(strqueue_comp(q1, q2) == 0);

    assert(strcmp(strqueue_get_at(q2, 0), "fghij") == 0);
    assert(strcmp(strqueue_get_at(q2, 1), "abcde") == 0);

    strqueue_remove_at(q2, 0); // q2: ["abcde"]
    strqueue_remove_at(q2, 0); // q2: []

    strqueue_insert_at(q2, 0, "abcde"); // q2: ["abcde"]
    strqueue_insert_at(q2, 1, "fghij"); // q2: ["abcde", "fghij"]

    assert(strqueue_comp(q1, q2) == 1);

    strqueue_delete(q1); // q1: deleted

    assert(strqueue_comp(q1, q2) == -1);

    strqueue_delete(q2); // q2: deleted

    assert(strqueue_comp(q1, q2) == 0);

    unsigned long q3 = strqueue_new(); // q3: []

    strqueue_insert_at(q3, 0, "apple"); // q3: ["apple"]
    strqueue_insert_at(q3, 0, "banana"); // q3: ["banana", "apple"]
    strqueue_insert_at(q3, 0, "orange"); // q3: ["orange", "banana", "apple"]

    assert(strqueue_size(q3) == 3);
    assert(strcmp(strqueue_get_at(q3, 0), "orange") == 0);
    assert(strcmp(strqueue_get_at(q3, 1), "banana") == 0);
    assert(strcmp(strqueue_get_at(q3, 2), "apple") == 0);
    assert(strqueue_get_at(q3, 3) == NULL);
    assert(strqueue_get_at(q3, -1) == NULL);
    assert(strqueue_comp(q3, q3) == 0);

    unsigned long q4 = strqueue_new(); // q4: []

    assert(strqueue_comp(q3, q4) == 1);
    strqueue_insert_at(q4, 0, "apple"); // q4: ["apple"]
    assert(strqueue_comp(q3, q4) == 1);
    strqueue_insert_at(q4, 0, "orange"); // q4: ["orange", "apple"]
    assert(strqueue_comp(q3, q4) == 1);
    strqueue_insert_at(q4, 1, "banana"); // q4: ["orange", "banana", "apple"]
    assert(strqueue_comp(q3, q4) == 0);

    assert(strqueue_size(q4) == 3);
    assert(strcmp(strqueue_get_at(q4, 0), "orange") == 0);
    assert(strcmp(strqueue_get_at(q4, 1), "banana") == 0);
    assert(strcmp(strqueue_get_at(q4, 2), "apple") == 0);
    assert(strqueue_get_at(q4, 3) == NULL);

    strqueue_remove_at(q4, 2434243); // q4: ["orange", "banana", "apple"]
    assert(strqueue_comp(q3, q4) == 0);
    strqueue_remove_at(q4, 1); // q4: ["orange", "apple"]

    assert(strqueue_size(q4) == 2);
    assert(strcmp(strqueue_get_at(q4, 0), "orange") == 0);
    assert(strcmp(strqueue_get_at(q4, 1), "apple") == 0);

    assert(strqueue_comp(q3, q4) == 1);

    strqueue_delete(q3); // q3: deleted
    assert(strqueue_comp(q3, q4) == -1);

    strqueue_clear(q4); // q4: []

    assert(strqueue_comp(q3, q4) == 0);
    assert(strqueue_size(q4) == 0);

    strqueue_delete(q4); // q4: deleted
}
