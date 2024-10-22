#include "strqueue.h"

#ifdef NDEBUG
  #undef NDEBUG
#endif

#include <cassert>
#include <cstddef>
#include <cstring>

namespace {
  bool streq(const char* s1, const char* s2) {
    if (s1 == s2)
      return true;

    if (s1 == NULL || s2 == NULL)
      return false;

    if (strcmp(s1, s2) == 0)
      return true;

    return false;
  }

  unsigned long test() {
    unsigned long id = ::cxx::strqueue_new();
    ::cxx::strqueue_insert_at(id, 0, "napis");
    return id;
  }

  unsigned long id = test();
}

int main() {
  const char* str = ::cxx::strqueue_get_at(id, 0);
  assert(streq(str, "napis"));
  ::cxx::strqueue_delete(id);
}
