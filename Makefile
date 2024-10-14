++ = g++
cc = gcc
CPPFLAGS = -Wall -Wextra -Wpedantic -O2 -std=c++17
CFLAGS = -Wall -Wextra -Wpedantic -O2 -std=c17

tests = strqueue_test_1_dbg strqueue_test_2_dbg_a strqueue_test_2_dbg_b
tests_ndb = strqueue_test_2_nodbg strqueue_test_1_nodbg

.PHONY = clean all test

all: clean $(tests) $(tests_ndb)

build/strqueue_dbg.o: strqueue.cpp
	$(++) $(CPPFLAGS) -c -o $@ $<

build/strqueue_nodbg.o: strqueue.cpp
	$(++) $(CPPFLAGS) -DNDEBUG -c -o $@ $<

build/%.o: %.c
	$(cc) $(CFLAGS) -c -o $@ $<

build/%.o: tests/%.cpp
	$(++) $(CPPFLAGS) -c -o $@ $<

strqueue_test_1_dbg: build/strqueue_test_1.o build/strqueue_dbg.o
	$(++) -o build/$@ $^

strqueue_test_2_dbg_a: strqueue_test_2.o strqueue_dbg.o
	$(++) -o build/$@ $^

strqueue_test_2_dbg_b: strqueue_dbg.o strqueue_test_2.o
	$(++) -o build/$@ $^

strqueue_test_2_nodbg: strqueue_test_2.o strqueue_nodbg.o
	$(++) -o build/$@ $^

clean:
	rm -rf build/*
