#include "Camera.h"

Camera::Camera() : position(0.0, 0.0, 3.0), rotation(0.0, 0.0, 0.0) {}

glm::mat4 Camera::getProjectionViewMatrix() {
  glm::mat4 proj = glm::perspective(glm::radians(70.0), 4.0/3.0, 0.1, 100.0);
  glm::mat4 mat = glm::mat4(1.0);

  mat = glm::rotate(mat, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
  mat = glm::rotate(mat, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
  mat = glm::rotate(mat, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));

  return proj * glm::translate(mat, -position);
}