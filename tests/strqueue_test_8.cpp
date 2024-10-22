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

// Testing every type of log output

int main() {
    unsigned long q1 = strqueue_new();
    strqueue_delete(q1 + 1);  
    strqueue_insert_at(q1, 0, "c");
    strqueue_delete(q1);
    
    q1 = strqueue_new();
    assert(strqueue_size(q1) == 0);
    assert(strqueue_size(q1 + 1) == 0);
    
    strqueue_insert_at(q1, 0, "a");
    strqueue_insert_at(q1, 0, "b");
    strqueue_size(q1);
    
    strqueue_insert_at(q1 + 1, 0, "a");
    strqueue_insert_at(q1, 0, NULL);
    
    strqueue_remove_at(q1 + 1, 0);
    strqueue_remove_at(q1, 11);
    strqueue_remove_at(q1, 1);
    
    assert(strqueue_get_at(q1 - 1, 0) == NULL);
    assert(strqueue_get_at(q1, 11) == NULL);
    assert(strcmp(strqueue_get_at(q1, 0), "b") == 0);
    
    strqueue_clear(q1 - 1);
    strqueue_clear(q1);
    
    assert(strqueue_comp(q1, q1) == 0);
    assert(strqueue_comp(q1, q1 - 1) == 0);
    assert(strqueue_comp(q1 + 1, q1 - 1) == 0);
}
