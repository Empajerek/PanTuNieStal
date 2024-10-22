#include "strqueue.h"

#include <cassert>
#include <cstring>
#include <vector>
#include <random>

using cxx::strqueue_new;
using cxx::strqueue_insert_at;
using cxx::strqueue_get_at;
using cxx::strqueue_remove_at;
using cxx::strqueue_comp;
using cxx::strqueue_clear;
using cxx::strqueue_delete;
using cxx::strqueue_size;

using qid = unsigned long;

namespace {
    std::string get_rand_string() {
        static std::mt19937 rng(23243424);
        static const std::string alphanum =
            "AB"
            "ab";

        std::string s;
        size_t len = rng() % 10 + 1;
        for (size_t i = 0; i < len; i++) {
            s.push_back(alphanum[rng() % alphanum.size()]);
        }
        return s;
    }

    int compare_vectors(std::vector<std::string> &v1,
                        std::vector<std::string> &v2) {
        if (v1 == v2)
            return 0;
        return v1 < v2 ? -1 : 1;
    }
}


int main() {
    const size_t N = 13;
    const size_t M = 300;
    std::vector<qid> ids(N);
    std::vector<std::vector<std::string>> qs(N);

    for (size_t i = 0; i < N; i++) {
        ids[i] = strqueue_new();
    }

    for (size_t j = 0; j < M; j++) {
        for (size_t i = 0; i < N; i++) {
            size_t ind = (i * j) % N;
            std::string s = get_rand_string();
            strqueue_insert_at(ids[ind], strqueue_size(ids[ind]), s.c_str());
            qs[ind].push_back(s);
        }
    }

    for (size_t i = 0; i < N; i++) {
        assert(strqueue_size(ids[i]) == qs[i].size());
        for (size_t j = 0; j < qs[i].size(); j++) {
            assert(strcmp(strqueue_get_at(ids[i], j), qs[i][j].c_str()) == 0);
        }
    }

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            assert(strqueue_comp(ids[i], ids[j]) == compare_vectors(qs[i], qs[j]));
        }
    }

    for (size_t i = 0; i < N; i++) {
        strqueue_clear(ids[i]);
        assert(strqueue_size(ids[i]) == 0);
    }

}