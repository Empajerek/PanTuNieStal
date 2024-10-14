#include "strqueue.h"
#include <iostream>
#include <deque>
#include <unordered_map>
#include <string>
#include <cstddef>

#ifndef DNDEBUG
    #define DEBUG_FAILED() std::cerr << __func__ << " failed \n";
    #define DEBUG_DNE(x) std::cerr << __func__ << ": queue" << x << "does not exist \n";
    #define DEBUG_DNC(x, y) std::cerr << __func__ << ": queue " << x << " does not contain string at position " << y << " \n";
#endif

namespace {
    void printArg() { }

    void printArg(std::nullptr_t _) {
        std::cerr << "NULL";
    }

    void printArg(const char* arg) {
        std::cerr << "\"" << arg << "\"";
    }

    template<typename T>
    void printArg(const T& arg) {
        std::cerr << arg;
    }

    template<typename T, typename... Arg>
    void printArg(const T& arg, const Arg&... rest) {
        printArg(arg);
        std::cerr << ", ";
        printArg(rest...);
    }

    template<typename... Args>
    void printStartDebugInformation(const char* functionName, Args... args) {
#ifndef DNDEBUG
        std::cerr << functionName << "(";
        printArg(args...);
        std::cerr << ") \n";
#endif
    }

    void printReturnDebugInformation(const char* functionName) {
#ifndef DNDEBUG
        std::cerr << functionName<< " done \n";
#endif
    }

    template<typename Arg>
    void printReturnDebugInformation(const char* functionName, Arg arg) {
#ifndef DNDEBUG
        std::cerr << functionName << " returns ";
        printArg(arg);
        std::cerr << " \n";
#endif
    }

    std::unordered_map<unsigned long, std::deque<std::string>> queues;
    unsigned long next_id = 0;
} // namespace

unsigned long strqueue_new() {
    printStartDebugInformation(__func__);
    unsigned long id = next_id++;
    queues[id] = std::deque<std::string>();
    printReturnDebugInformation(__func__,id);
    return id;
}

void strqueue_delete(unsigned long id) {
    printStartDebugInformation(__func__,id);
    queues.erase(id);
    printReturnDebugInformation(__func__);
}

size_t strqueue_size(unsigned long id) {
    printStartDebugInformation(__func__, id);
    const auto iter = queues.find(id);
    size_t size;
    if (iter == queues.end()) {
        DEBUG_DNE(id)
        size = 0;
    } else {
        size = iter->second.size();
    }
    printReturnDebugInformation(__func__, size);
    return size;
}

void strqueue_insert_at(unsigned long id, size_t position, const char* str) {
    printStartDebugInformation(__func__, id, position, str);
    auto iter = queues.find(id);
    if (iter == queues.end()) {
        DEBUG_DNE(id)
        return;
    }
    if (str == NULL) {
        DEBUG_FAILED()
        return;
    }

    if (position >= iter->second.size())
        iter->second.push_back(str);
    else
        iter->second.insert(iter->second.begin() + position, str);
    printReturnDebugInformation(__func__);
}

void strqueue_remove_at(unsigned long id, size_t position) {
    printStartDebugInformation(__func__, id, position);
    auto iter = queues.find(id);
    if (iter == queues.end()) {
        DEBUG_DNE(id)
        return;
    }

    if (iter->second.size() <= position) {
        DEBUG_DNC(id, position)
        return;
    }

    iter->second.erase(iter->second.begin() + position);
    printReturnDebugInformation(__func__);
}

const char* strqueue_get_at(unsigned long id, size_t position) {
    printStartDebugInformation(__func__, id, position);
    auto iter = queues.find(id);
    if (iter == queues.end()) {
        DEBUG_DNE(id)
        printReturnDebugInformation(__func__, nullptr);
        return NULL;
    }

    if (iter->second.size() <= position) {
        DEBUG_DNC(id, position);
        printReturnDebugInformation(__func__, nullptr);
        return NULL;
    }

    const char* elem = iter->second[position].c_str();
    printReturnDebugInformation(__func__, elem);
    return elem;
}

void strqueue_clear(unsigned long id) {
    printStartDebugInformation(__func__, id);
    auto iter = queues.find(id);
    if (iter == queues.end()) {
        DEBUG_DNE(id)
        return;
    }

    iter->second.clear();
    printReturnDebugInformation(__func__);
}

int strqueue_comp(unsigned long id1, unsigned long id2) {
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
