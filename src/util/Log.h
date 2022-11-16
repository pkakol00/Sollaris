#ifndef __LOG_H__
#define __LOG_H__

#include <iostream>
#include "stdarg.h"

inline void log(const std::string& file, const int line, const std::string& message) {
  std::cout << "[" << file << ":" << line << "] " << message << std::endl;
}

#ifdef SILENT
#define LOG(message)
#else
#define LOG(message) log(__FILE__, __LINE__, message)
#endif

#endif // __LOG_H__