#include "Drawable.h"

#include <glm/gtc/type_ptr.hpp>

glm::mat4 Drawable::getModelMatrix() {
  glm::mat4 mat = glm::mat4(1.0);

  mat = glm::scale(mat, scale);
  
  mat = glm::rotate(mat, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
  mat = glm::rotate(mat, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
  mat = glm::rotate(mat, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));

  return glm::translate(mat, position);
}