#include "Orbit.h"

#include <GL/glew.h>

#include <vector>
#include <glm/gtc/constants.hpp>

Orbit::Orbit(std::deque<Vec3>* orbit_points) : orbit_points(orbit_points) {
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // glGenBuffers(1, &EBO);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indecies.size() * sizeof(uint),
  //              indecies.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, 3 * vertecies.size() * sizeof(float),
  //              vertecies.data(), GL_STATIC_DRAW);
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  LOG("Created model: " + std::to_string(VAO));
}

void Orbit::draw() {
  glBindVertexArray(VAO);

  std::vector<Vec3> vertecies =
      std::vector<Vec3>(orbit_points->begin(), orbit_points->end());

  //LOG(std::to_string(position) + " " + std::to_string(rotation) + " " + std::to_string(scale));

  glBufferData(GL_ARRAY_BUFFER, 3 * vertecies.size() * sizeof(double),
             vertecies.data(), GL_STREAM_DRAW);
  glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void*)0);

  glDrawArrays(GL_LINE_STRIP, 0, orbit_points->size());
}