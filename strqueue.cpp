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

    static StringQueue& get_queue() {
        static StringQueue queue;
        return queue;
    }
} // namespace

unsigned long strqueue_new() {
    DEBUG_START();
    static unsigned long id = 0;
    get_queue()[id] = std::deque<std::string>();
    DEBUG_RETURN(id);
    return id++;
}

void strqueue_delete(unsigned long id) {
    DEBUG_START(id);
    get_queue().erase(id);
    DEBUG_RETURN();
}

size_t strqueue_size(unsigned long id) {
    DEBUG_START(id);
    const auto iter = get_queue().find(id);
    size_t size;
    if (iter == get_queue().end()) {
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
    auto iter = get_queue().find(id);
    if (iter == get_queue().end()) {
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
    auto iter = get_queue().find(id);
    if (iter == get_queue().end()) {
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
    auto iter = get_queue().find(id);
    const char* elem = (const char*) NULL;
    if (iter == get_queue().end())
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
    auto iter = get_queue().find(id);
    if (iter == get_queue().end()) {
        DEBUG_DNE(id);
        return;
    }

    iter->second.clear();
    DEBUG_RETURN();
}

int strqueue_comp(unsigned long id1, unsigned long id2) {
    short ret;
    DEBUG_START(id1, id2);

    auto iter1 = get_queue().find(id1);
    auto iter2 = get_queue().find(id2);

    const auto& queue1 = iter1->second;
    const auto& queue2 = iter2->second;

    if (
    (iter1 == get_queue().end() || !queue1.size()) && 
    (iter2 == get_queue().end() || !queue2.size())
    ) {
        DEBUG_DNE(id1);
        DEBUG_DNE(id2);
        ret = 0;
    } else if (iter1 == get_queue().end()) {
        DEBUG_DNE(id1);
        ret = -1;
    } else if (iter2 == get_queue().end()) {
        DEBUG_DNE(id2);
        ret = 1;
    } else {
        // Both get_queue() exist and we begin to compare them lexicographically.
        if (queue1 < queue2)
            ret = -1;
        else if (queue1 > queue2)
            ret = 1;
        else
            ret = 0;
    }

    DEBUG_RETURN(ret);
    return ret;
}

} // namespace cxx
