#include "Drawable.h"

#include <glm/gtc/type_ptr.hpp>

Drawable::Drawable()
  : position(0.0), scale(1.0), rotation(0.0) {}

glm::mat4 Drawable::getModelMatrix() {
  glm::mat4 mat = glm::mat4(1.0);
  mat = glm::translate(mat, position);
  
  mat = glm::rotate(mat, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
  mat = glm::rotate(mat, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
  mat = glm::rotate(mat, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));

  mat = glm::scale(mat, scale);

  return mat;
}