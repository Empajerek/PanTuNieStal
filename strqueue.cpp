#include "strqueue.h"
#include <iostream>
#include <deque>
#include <unordered_map>
#include <string>
#include <cstddef>

#undef NDEBUG
using StringQueue = std::unordered_map<unsigned long, std::deque<std::string>>;

namespace cxx {

namespace {
#ifndef NDEBUG
    #define DEBUG_FAILED() std::cerr << __func__ << " failed \n"
    #define DEBUG_DNE(x) std::cerr << __func__ << ": queue " << x << " does not exist \n"
    #define DEBUG_DNC(x, y) std::cerr << __func__ << ": queue " << x << " does not contain string at position " << y << " \n"
    #define DEBUG_START(...) std::cerr << __func__ << "(" << argToStr(__VA_ARGS__) << ") \n"
    #define DEBUG_RETURN(x) std::cerr << __func__ << returnStr(x) << " \n"

    std::string argToStr() {
        return "";
    }

    std::string argToStr(const char* arg) {
        if (arg == nullptr)
            return "NULL";
        return  "\"" + std::string(arg) + "\"";
    }

    template<typename T>
    std::string argToStr(const T& arg) {
        return std::to_string(arg);
    }

    // Recursively printing all of the arguments.
    template<typename T, typename... Arg>
    std::string argToStr(const T& arg, const Arg&... rest) {
        return argToStr(arg) + ", " + argToStr(rest...);
    }

    std::string returnStr() {
        return " done";
    }

    template<typename Arg>
    std::string returnStr(Arg arg) {
        return " returns " + argToStr(arg);
    }

#else
    #define DEBUG_FAILED(...) {}
    #define DEBUG_DNE(...) {}
    #define DEBUG_DNC(...) {}
    #define DEBUG_START(...) {}
    #define DEBUG_RETURN(...) {}
#endif

    StringQueue queues;
} // namespace

unsigned long strqueue_new() {
    DEBUG_START();
    static unsigned long id = 0;
    queues[id] = std::deque<std::string>();
    DEBUG_RETURN(id);
    return id++;
}

void strqueue_delete(unsigned long id) {
    DEBUG_START(id);
    queues.erase(id);
    DEBUG_RETURN();
}

size_t strqueue_size(unsigned long id) {
    DEBUG_START(id);
    const auto iter = queues.find(id);
    size_t size;
    if (iter == queues.end()) {
        DEBUG_DNE(id);
        size = 0;
    } else {
        size = iter->second.size();
    }
    DEBUG_RETURN(size);
    return size;
}

void strqueue_insert_at(unsigned long id, size_t position, const char* str) {
    DEBUG_START(id, position, str);
    auto iter = queues.find(id);
    if (iter == queues.end()) {
        DEBUG_DNE(id);
        return;
    }

    if (str == NULL) {
        DEBUG_FAILED();
        return;
    }

    if (position >= iter->second.size())
        iter->second.push_back(str);
    else
        iter->second.insert(iter->second.begin() + position, str);
    DEBUG_RETURN();
}

void strqueue_remove_at(unsigned long id, size_t position) {
    DEBUG_START(id, position);
    auto iter = queues.find(id);
    if (iter == queues.end()) {
        DEBUG_DNE(id);
        return;
    }

    if (iter->second.size() <= position) {
        DEBUG_DNC(id, position);
        return;
    }

    iter->second.erase(iter->second.begin() + position);
    DEBUG_RETURN();
}

const char* strqueue_get_at(unsigned long id, size_t position) {
    DEBUG_START(id, position);
    auto iter = queues.find(id);
    const char* elem = (const char*) NULL;
    if (iter == queues.end())
        DEBUG_DNE(id);
    else if (iter->second.size() <= position)
        DEBUG_DNC(id, position);
    else
        elem = iter->second[position].c_str();
    DEBUG_RETURN(elem);
    return elem;
}

void strqueue_clear(unsigned long id) {
    DEBUG_START(id);
    auto iter = queues.find(id);
    if (iter == queues.end()) {
        DEBUG_DNE(id);
        return;
    }

    iter->second.clear();
    DEBUG_RETURN();
}

int strqueue_comp(unsigned long id1, unsigned long id2) {
    DEBUG_START(id1, id2);

    auto iter1 = queues.find(id1);
    auto iter2 = queues.find(id2);

    if (iter1 == queues.end() && iter2 == queues.end()) {
        DEBUG_DNE(id1);
        DEBUG_DNE(id2);
        DEBUG_RETURN(0);
        return 0;
    }

    if (iter1 == queues.end()) {
        DEBUG_DNE(id1);
        DEBUG_RETURN(-1);
        return -1;
    }

    if (iter2 == queues.end()) {
        DEBUG_DNE(id2);
        DEBUG_RETURN(1);
        return 1;
    }

    // Both queues exist and we begin to compare them lexicographically.
    const auto& queue1 = iter1->second;
    const auto& queue2 = iter2->second;

    size_t size1 = queue1.size();
    size_t size2 = queue2.size();

    size_t min_size = std::min(size1, size2);

    for (size_t i = 0; i < min_size; i++) {
        int cmp = queue1[i].compare(queue2[i]);
        if (cmp < 0) {
            DEBUG_RETURN(-1);
            return -1;
        } else if (cmp > 0) {
            DEBUG_RETURN(1);
            return 1;
        }
    }

    if (size1 < size2) {
        DEBUG_RETURN(-1);
        return -1;
    }
    else if (size1 > size2) {
        DEBUG_RETURN(1);
        return 1;
    }

    // Queues are equal.
    DEBUG_RETURN(0);
    return 0;
}

} // namespace cxx
