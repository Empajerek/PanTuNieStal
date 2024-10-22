#include "strqueue.h"

#ifdef NDEBUG
  #undef NDEBUG
#endif

#include <assert.h>
#include <stdbool.h>
#include <string.h>

static bool streq(const char* s1, const char* s2) {
  if (s1 == s2)
    return true;

  if (s1 == NULL || s2 == NULL)
    return false;

  if (strcmp(s1, s2) == 0)
    return true;

  return false;
}

int main() {
  unsigned long d1, d2, d3;

  d1 = strqueue_new();
  strqueue_insert_at(d1, 0, "a");
  assert(streq(strqueue_get_at(d1, 0), "a"));

  strqueue_insert_at(d1, 8, "aa");
  assert(streq(strqueue_get_at(d1, 1), "aa"));

  strqueue_remove_at(d1, 1);
  assert(strqueue_get_at(d1, 1) == NULL);
  assert(streq(strqueue_get_at(d1, 0), "a"));

  strqueue_insert_at(d1, 0, NULL);
  assert(streq(strqueue_get_at(d1, 0), "a"));
  assert(strqueue_size(d1) == 1);

  strqueue_remove_at(d1, 1);
  assert(strqueue_size(d1) == 1);

  strqueue_delete(d1);
  strqueue_insert_at(d1, 0, "b");
  assert(strqueue_size(d1) == 0);
  assert(strqueue_get_at(d1, 0) == NULL);

  d2 = strqueue_new();
  d3 = strqueue_new();
  strqueue_insert_at(d2, 0, "c");
  strqueue_insert_at(d2, 0, "cc");
  strqueue_insert_at(d2, 0, "ccc");
  strqueue_insert_at(d3, 100, "ccc");
  strqueue_insert_at(d3, 1000, "cc");
  strqueue_insert_at(d3, 10000, "c");
  assert(strqueue_comp(d2, d3) == 0);

  strqueue_remove_at(d2, 0);
  assert(strqueue_comp(d2, d3) == -1);

  strqueue_delete(d3);
  assert(strqueue_comp(d2, d3) == 1);

  strqueue_delete(d2);
  assert(strqueue_comp(d2, d3) == 0);
}
