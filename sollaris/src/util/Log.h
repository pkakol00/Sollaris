#ifndef __LOG_H__
#define __LOG_H__

#include <iostream>
#include "stdarg.h"

inline void log() {
    std::cerr << std::endl;
}

template <typename T, typename... TAIL>
inline void log(T head, TAIL... tail) {
    std::cerr << head;
    log(tail...);
}

#ifdef SILENT
#define LOG(...)
#else
#define LOG(...) log("[", __FILE__, ":", __LINE__, "] ", __VA_ARGS__)
#endif

#endif // __LOG_H__
