#include "Shader.h"
#include <GL/glew.h>
// #include <GL/glut.h>
#include "../util/Log.h"
#include <fstream>
#include <sstream>
#include <cstring>

#include <glm/gtc/type_ptr.hpp>
#include <filesystem>

namespace ge {

Shader::Shader(const std::string& file_path) {
  auto prefix =
      std::filesystem::canonical("/proc/self/exe").parent_path().string() + "/";
  uint vertex_id = createShader(prefix + file_path + ".vs", GL_VERTEX_SHADER);
  uint fragment_id = createShader(prefix + file_path + ".fs", GL_FRAGMENT_SHADER);
  shader_id = glCreateProgram();

  glAttachShader(shader_id, vertex_id);
  glAttachShader(shader_id, fragment_id);
  glLinkProgram(shader_id);

  int success;
  glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
  if(!success) {
    char info_log[512];
    glGetProgramInfoLog(shader_id, 512, NULL, info_log);
    LOG("ERROR failed to link: " + file_path + " " + std::string(info_log));
  } else {
    LOG("Created shader program from: " + file_path);
  }
  
  glDeleteShader(vertex_id);
  glDeleteShader(fragment_id);
}

void Shader::bind() {
  glUseProgram(shader_id);
}

void Shader::unbind() {
  glUseProgram(0);
}

uint Shader::createShader(const std::string& file_path, uint type) {
  auto vertex_src = readFromFile(file_path);
  uint id = glCreateShader(type);
  
  LOG("Created shader type: " + std::to_string(type));
  
  char* c_string_src = new char [vertex_src.length() + 1];
  std::strcpy(c_string_src, vertex_src.c_str());

  glShaderSource(id, 1, &c_string_src, NULL);
  glCompileShader(id);
  delete[] c_string_src;

  int success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if(!success) {
    char info_log[512];
    glGetShaderInfoLog(id, 512, NULL, info_log);
    LOG("ERROR failed to compile: " + file_path + " " + std::string(info_log));
  } else {
    LOG("Compiled " + std::to_string(type));
  } 
  
  return id;
}

std::string Shader::readFromFile(const std::string& file_path) {
  std::ifstream file(file_path);
  if (!file.is_open()) {
    LOG("ERROR file: " + file_path + " does not exist");
    exit(1);
  }
    std::stringstream ss;
    ss << file.rdbuf();
    file.close();
    return ss.str();
}

void Shader::setUniformVec4(const std::string& name, glm::vec4 v) {
  glUniform4f(glGetUniformLocation(shader_id, name.c_str()), 
              v.x, v.y, v.z, v.w);
}

void Shader::setUniformMat4(const std::string& name, glm::mat4 m) {
  glUniformMatrix4fv(glGetUniformLocation(shader_id, name.c_str()), 1, GL_FALSE,
                     glm::value_ptr(m));
}

} // namespace ge