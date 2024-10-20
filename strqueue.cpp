#include "strqueue.h"
#include <iostream>
#include <deque>
#include <unordered_map>
#include <string>
#include <cstddef>

#undef NDEBUG

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

    std::unordered_map<unsigned long, std::deque<std::string>> queues;
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
    if (iter == queues.end()) {
        DEBUG_DNE(id);
        DEBUG_RETURN((const char*) NULL);
        return NULL;
    }

    if (iter->second.size() <= position) {
        DEBUG_DNC(id, position);
        DEBUG_RETURN((const char*) NULL);
        return NULL;
    }

    const char* elem = iter->second[position].c_str();
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
    (void) id1;
    (void) id2;
    return 0;
}

namespace cxx {
    unsigned long strqueue_new() { return ::strqueue_new(); }
    void strqueue_delete(unsigned long id) { ::strqueue_delete(id); }
    size_t strqueue_size(unsigned long id) { return ::strqueue_size(id); }
    void strqueue_insert_at(unsigned long id, size_t position, const char* str) { ::strqueue_insert_at(id, position, str); }
    void strqueue_remove_at(unsigned long id, size_t position) { ::strqueue_remove_at(id, position); }
    const char* strqueue_get_at(unsigned long id, size_t position) { return ::strqueue_get_at(id, position); }
    void strqueue_clear(unsigned long id) { ::strqueue_clear(id); }
    int strqueue_comp(unsigned long id1, unsigned long id2) { return ::strqueue_comp(id1, id2); }
}
