#ifndef __LOG_H__
#define __LOG_H__

#include <iostream>
#include "stdarg.h"
#include <string>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>

inline void log(const std::string& file, const int line, const std::string& message) {
  std::cout << "[" << file << ":" << line << "] " << message << std::endl;
}

#ifdef SILENT
#define LOG(message)
#else
#define LOG(message) log(__FILE__, __LINE__, message)
#endif

namespace std {
  inline string to_string(const ::glm::vec3& v) {
    return "(" + to_string(v.x) + ", " + to_string(v.y) + ", " + to_string(v.z) + ")";
  }
}

template <typename T> std::string to_string(const std::vector<T>& v) {
  if (v.empty()) {
    return "()";
  }
  std::stringstream ss;
  ss << "(" << std::to_string(v[0]);
  for (auto e = ++v.begin(); e != v.end(); e ++) {
    ss << ", " << std::to_string(*e); // std::to_string(*e);
  }
  ss << ")";
  return ss.str();
}

#endif // __LOG_H__