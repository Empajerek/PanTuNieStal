#include "strqueue.h"

#include <assert.h>
#include <string.h>

int main() {

    // No queues.
    strqueue_delete(0);
    strqueue_insert_at(0, 0, "a");
    assert(strqueue_get_at(0, 0) == NULL);
    strqueue_remove_at(0, 0);
    assert(strqueue_comp(0, 122432) == 0);
    assert(strqueue_size(0) == 0);
    strqueue_clear(0);

    // Single queue.
    unsigned long q1 = strqueue_new();
    assert(strqueue_size(q1) == 0); // q1: []
    strqueue_insert_at(q1, 0, "a");
    assert(strqueue_size(q1) == 1); // q1: ["a"]
    strqueue_insert_at(q1, 1, "b");
    assert(strqueue_size(q1) == 2); // q1: ["a", "b"]
    strqueue_insert_at(q1, 2, "c");
    assert(strqueue_size(q1) == 3); // q1: ["a", "b", "c"]

    assert(strqueue_comp(q1, q1) == 0);
    assert(strqueue_comp(q1, q1 + 1) == 1);

    assert(strcmp(strqueue_get_at(q1, 0), "a") == 0);
    assert(strcmp(strqueue_get_at(q1, 1), "b") == 0);
    assert(strcmp(strqueue_get_at(q1, 2), "c") == 0);
    assert(strqueue_get_at(q1, 3) == NULL);

    strqueue_remove_at(q1, 1);

    assert(strqueue_size(q1) == 2); // q1: ["a", "c"]
    assert(strcmp(strqueue_get_at(q1, 0), "a") == 0);
    assert(strcmp(strqueue_get_at(q1, 1), "c") == 0);

    strqueue_clear(q1);
    assert(strqueue_size(q1) == 0); // q1: []
    assert(strqueue_get_at(q1, 0) == NULL);

    strqueue_delete(q1);
    assert(strqueue_size(q1) == 0); // q1: []
    assert(strqueue_get_at(q1, 0) == NULL);
    assert(strqueue_comp(q1, q1) == 0);


    // Multiple queues.
    
    unsigned long q2 = strqueue_new();
    strqueue_insert_at(q2, 0, "a");
    strqueue_insert_at(q2, 0, "a");
    assert(strqueue_comp(q1, q2) == -1);
    assert(strqueue_comp(q2, q1) == 1);
    assert(strqueue_comp(q2, q2) == 0);
    strqueue_clear(q2);
    assert(strqueue_comp(q1, q2) == 0);
    assert(strqueue_size(q2) == 0); // q2: []
    

    unsigned long q3 = strqueue_new();

    strqueue_insert_at(q2, 0, "What");
    strqueue_insert_at(q2, 1, "is");
    strqueue_insert_at(q2, 2, "the");
    strqueue_insert_at(q2, 3, "airspeed");
    strqueue_insert_at(q2, 4, "velocity");
    strqueue_insert_at(q2, 5, "of");
    strqueue_insert_at(q2, 6, "an");
    strqueue_insert_at(q2, 7, "unladen");
    strqueue_insert_at(q2, 8, "swift");

    assert(strqueue_size(q2) == 9); // q2: ["What", "is", "the", "airspeed", "velocity", "of", "an", "unladen", "swift"]

    strqueue_insert_at(q3, 0, "What");
    strqueue_insert_at(q3, 1, "is");
    strqueue_insert_at(q3, 2, "the");
    strqueue_insert_at(q3, 3, "airspeed");
    strqueue_insert_at(q3, 4, "velocity");
    strqueue_insert_at(q3, 5, "of");
    strqueue_insert_at(q3, 6, "an");
    strqueue_insert_at(q3, 7, "unladen");
    strqueue_insert_at(q3, 8, "swallow");

    assert(strqueue_size(q3) == 9); // q3: ["What", "is", "the", "airspeed", "velocity", "of", "an", "unladen", "swallow"]

    assert(strqueue_comp(q2, q3) == 1);

    strqueue_remove_at(q2, 5);

    assert(strqueue_comp(q2, q3) == -1); // q2: ["What", "is", "the", "airspeed", "velocity", "an", "unladen", "swift"]

    strqueue_remove_at(q3, 5);

    assert(strqueue_comp(q2, q3) == 1); // q3: ["What", "is", "the", "airspeed", "velocity", "an", "unladen", "swallow"]

    strqueue_remove_at(q2, 7);

    strqueue_insert_at(q2, 7, "swallow");

    assert(strqueue_comp(q2, q3) == 0); // q2: ["What", "is", "the", "airspeed", "velocity", "an", "unladen", "swallow"]
}